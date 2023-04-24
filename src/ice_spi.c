/*
 * MIT License
 * 
 * Copyright (c) 2023 tinyVision.ai
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// TODO: For now, this is a bit-banged library which is sub-optimal.
// We could use the hardware SPI for when in forward pin order, and
// a PIO state machine for reverse pin order. But since we are going
// to need the reverse pin order anyway, we might as well make use
// of the PIO state machine right away. This way only one PIO state
// machine is used and no extra SPI peripheral.
//
// So the next evolution of this driver is to use PIO, and after that
// DMA channels along with PIO.

// libc
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

// pico-sdk
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/spi.h"

// pico-ice-sdk
#include "boards/pico_ice.h"
#include "ice_spi.h"

static int g_dummy;
static volatile int g_tx_dma_channel = -1;
static volatile int g_rx_dma_channel = -1;
static volatile bool g_init_done = true;
static volatile bool g_transfer_done = true;
static volatile void (*g_async_callback)(volatile void *);
static volatile void *g_async_context;

void ice_sram_init(void)
{
    // Invert the SSRAM CS so that all SPI is active low in software.
    gpio_set_outover(ICE_SRAM_SPI_CS_PIN, GPIO_OVERRIDE_INVERT);
}

static void spi_irq_handler(void) {
    g_transfer_done = true;

    if (g_async_callback != NULL) {
        (*g_async_callback)(g_async_context);
    }
}

void ice_spi_init(uint baudrate_hz) {
    dma_channel_config cfg;

    // It is going to be called from multiple other init functions
    if (g_init_done) {
        return;
    }

    spi_init(spi_default, baudrate_hz);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);

    g_tx_dma_channel = dma_claim_unused_channel(true);
    g_rx_dma_channel = dma_claim_unused_channel(true);

    // This DMA channel transfers from internal RAM to SPI.
    cfg = dma_channel_get_default_config(g_tx_dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_dreq(&cfg, spi_get_dreq(spi_default, true));
    channel_config_set_write_increment(&cfg, false);
    dma_channel_configure(g_tx_dma_channel, &cfg, &spi_get_hw(spi_default)->dr, 0, 0, false);

    // This DMA channel transfers from SPI to internal RAM.
    cfg = dma_channel_get_default_config(g_rx_dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_dreq(&cfg, spi_get_dreq(spi_default, false));
    channel_config_set_read_increment(&cfg, false);
    dma_channel_configure(g_rx_dma_channel, &cfg, 0, &spi_get_hw(spi_default)->dr, 0, false);

    // An interrupt that asserts when DMA transfers complete.
    dma_irqn_set_channel_enabled(ICE_SPI_IRQ_NUMBER - DMA_IRQ_0, g_rx_dma_channel, true);
    irq_add_shared_handler(ICE_SPI_IRQ_NUMBER, spi_irq_handler, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
    irq_set_enabled(ICE_SPI_IRQ_NUMBER, true);

    g_init_done = true;
}

// Not using the SPI peripheral to control CS because it only knows how to
// toggle it every 4-16 bits while we need to keep the PSRAM selected for a
// multi-byte read or write sequence.
void ice_spi_chip_select(uint8_t csn_pin) {
    // Drive the bus, going out of high-impedance mode
    gpio_put(ICE_DEFAULT_SPI_SCK_PIN, false);
    gpio_put(ICE_DEFAULT_SPI_TX_PIN, true);
    gpio_set_dir(ICE_DEFAULT_SPI_SCK_PIN, GPIO_OUT);
    gpio_set_dir(ICE_DEFAULT_SPI_TX_PIN, GPIO_OUT);

    // Start an SPI transaction
    gpio_put(csn_pin, false);
    gpio_set_dir(csn_pin, GPIO_OUT);
    sleep_us(1);
}

void ice_spi_chip_deselect(uint8_t csn_pin) {
    // Terminate the transaction
    gpio_put(csn_pin, true);

    // Release the bus by putting it high-impedance mode
    gpio_set_dir(csn_pin, GPIO_IN);
    gpio_set_dir(ICE_DEFAULT_SPI_SCK_PIN, GPIO_IN);
    gpio_set_dir(ICE_DEFAULT_SPI_TX_PIN, GPIO_IN);
}

void ice_spi_write_async(const void *data, size_t data_size, void (*callback)(volatile void *), void *context) {
    uint32_t status;

    ice_spi_await_async_completion();

    assert(g_transfer_done == true);

    status = save_and_disable_interrupts();
    g_async_callback = callback;
    g_async_context = context;
    g_transfer_done = false;
    restore_interrupts(status);

    assert(g_tx_dma_channel >= 0);
    assert(g_rx_dma_channel >= 0);
    assert(data_size > 0);

    // Must start the RX first to make sure both TX and RX are set when
    // starting: it will wait for TX to start as it drives the clock.

    // Disable the address increment: always read to the same byte
    hw_clear_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
    dma_channel_transfer_to_buffer_now(g_rx_dma_channel, &g_dummy, data_size);

    // Enable the address increment: increase the address at every write
    hw_set_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
    dma_channel_transfer_from_buffer_now(g_tx_dma_channel, data, data_size);
}

void ice_spi_read_async(uint8_t dummy, uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context) {
    uint32_t status;

    ice_spi_await_async_completion();

    assert(g_transfer_done == true);

    status = save_and_disable_interrupts();
    g_async_callback = callback;
    g_async_context = context;
    g_transfer_done = false;
    restore_interrupts(status);

    assert(g_tx_dma_channel >= 0);
    assert(g_rx_dma_channel >= 0);
    assert(data_size > 0);

    // Must start the RX first to make sure both TX and RX are set when
    // starting: it will wait for TX to start as it drives the clock.

    g_dummy = dummy;

    // Enable the address increment: increase the address at every read
    hw_set_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
    dma_channel_transfer_from_buffer_now(g_rx_dma_channel, data, data_size);

    // Disable the address increment: always write to the same byte
    hw_clear_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
    dma_channel_transfer_to_buffer_now(g_tx_dma_channel, &g_dummy, data_size);
}

bool ice_spi_is_async_complete(void) {
    return g_transfer_done;
}

void ice_spi_await_async_completion(void) {
    while (!ice_spi_is_async_complete()) {
        __wfe();
    }
}

void ice_spi_read_blocking(uint8_t tx, uint8_t *buf, size_t len) {
    ice_spi_read_async(tx, buf, len, NULL, NULL);
    ice_spi_await_async_completion();
}

void ice_spi_write_blocking(uint8_t const *buf, size_t len) {
    ice_spi_write_async(buf, len, NULL, NULL);
    ice_spi_await_async_completion();
}
