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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "boards/pico_ice.h"
#include "ice_spi.h"

volatile static bool g_transfer_done = true;
volatile static void (*g_async_callback)(volatile void *);
volatile static void *g_async_context;
static int dma_tx, dma_rx;
static uint32_t dma_word;
static bool spi_is_initialized;

static void spi_irq_handler(void) {
    if (dma_channel_get_irq1_status(dma_rx)) {
        if (g_async_callback != NULL) {
            (*g_async_callback)(g_async_context);
        }
        g_transfer_done = true;
        dma_channel_acknowledge_irq1(dma_rx);
    }
}

void ice_spi_init(void) {
    // This driver is only focused on one particular SPI bus
    gpio_init(ICE_SPI_SCK_PIN);
    gpio_init(ICE_SPI_TX_PIN);
    gpio_init(ICE_SPI_RX_PIN);

    // Everything in high impedance before a transaction occurs
    gpio_set_dir(ICE_SPI_SCK_PIN, GPIO_IN);
    gpio_set_dir(ICE_SPI_TX_PIN, GPIO_IN);
    gpio_set_dir(ICE_SPI_RX_PIN, GPIO_IN);

    if (spi_is_initialized) { 
        spi_set_baudrate(spi1, ICE_SPI_BAUDRATE);
        irq_set_enabled(DMA_IRQ_1, true);
        return;
    }
    spi_is_initialized = true;

    // Initialize SPI, but don't yet assign the pins SPI function so they stay in high impedance mode.
    // Use 33MHz as that is the fastest the SRAM supports a 03h read command.
    spi_init(spi1, ICE_SPI_BAUDRATE);

    // Setup DMA channel and interrupt handler
    dma_tx = dma_claim_unused_channel(true);
    dma_rx = dma_claim_unused_channel(true);

    dma_channel_set_irq1_enabled(dma_rx, true);
    irq_set_exclusive_handler(DMA_IRQ_1, spi_irq_handler);
    irq_set_enabled(DMA_IRQ_1, true);
}

void ice_spi_init_cs_pin(uint8_t csn_pin, bool active_high) {
    gpio_init(csn_pin);
    if (active_high) {
        // When CS is active high: invert the pin output with hardware
        gpio_set_outover(csn_pin, GPIO_OVERRIDE_INVERT);
    }
    ice_spi_chip_deselect(csn_pin);
}

void ice_spi_chip_select(uint8_t csn_pin) {
    // Take control of the bus
    gpio_set_function(ICE_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_SPI_TX_PIN, GPIO_FUNC_SPI);

    // Start an SPI transaction
    gpio_put(csn_pin, false);
    gpio_set_dir(csn_pin, GPIO_OUT);
    sleep_us(1);
}

void ice_spi_chip_deselect(uint8_t csn_pin) {
    // Busy wait until SCK goes low
    while (gpio_get(ICE_SPI_SCK_PIN)) {
        tight_loop_contents();
    }

    // Terminate the transaction
    gpio_put(csn_pin, true);
    sleep_us(1);

    // Release the bus by connecting back to the CPU GPIO, ensuring the IOs are back to high-impedance mode
    gpio_set_dir(ICE_SPI_SCK_PIN, GPIO_IN);
    gpio_set_dir(ICE_SPI_TX_PIN, GPIO_IN);
    gpio_set_dir(ICE_SPI_RX_PIN, GPIO_IN);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SIO);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SIO);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SIO);

    switch (csn_pin) {
    case ICE_LED_RED_PIN:
    case ICE_LED_GREEN_PIN:
    case ICE_LED_BLUE_PIN:
        gpio_set_dir(csn_pin, GPIO_IN);
        break;
    default:
        gpio_put(csn_pin, true);
        break;
    }
}

static void prepare_transfer(void (*callback)(volatile void *), void *context) {
    uint32_t status;

    ice_spi_wait_completion();

    status = save_and_disable_interrupts();
    g_async_callback = callback;
    g_async_context = context;
    g_transfer_done = false;
    restore_interrupts(status);
}

void ice_spi_write_async(uint8_t const *data, size_t data_size, void (*callback)(volatile void *), void *context) {
    prepare_transfer(callback, context);

    dma_channel_config c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(spi1, true));
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    dma_channel_configure(dma_tx, &c,
                          &spi_get_hw(spi1)->dr, // write address
                          data,                  // read address
                          data_size,             // element count
                          false);

    c = dma_channel_get_default_config(dma_rx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(spi1, false));
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, false);
    dma_channel_configure(dma_rx, &c,
                          &dma_word,             // write address
                          &spi_get_hw(spi1)->dr, // read address
                          data_size,
                          false);

    dma_start_channel_mask((1u << dma_tx) | (1u << dma_rx));
}

void ice_spi_read_async(uint8_t *data, size_t data_size, void (*callback)(volatile void *), void *context) {
    prepare_transfer(callback, context);

    // Byte to transmit during the read
    dma_word = 0xFF;

    dma_channel_config c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(spi1, true));
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, false);
    dma_channel_configure(dma_tx, &c,
                          &spi_get_hw(spi1)->dr, // write address
                          &dma_word,             // read address
                          data_size,             // element count
                          false);

    c = dma_channel_get_default_config(dma_rx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_dreq(&c, spi_get_dreq(spi1, false));
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);
    dma_channel_configure(dma_rx, &c,
                          data,                  // write address
                          &spi_get_hw(spi1)->dr, // read address
                          data_size,
                          false);

    dma_start_channel_mask((1u << dma_tx) | (1u << dma_rx));
}

bool ice_spi_is_async_complete(void) {
    return g_transfer_done;
}

void ice_spi_wait_completion(void) {
    while (!ice_spi_is_async_complete()) {
        __wfe();
    }
}

void ice_spi_read_blocking(uint8_t *data, size_t data_size) {
    ice_spi_read_async(data, data_size, NULL, NULL);
    ice_spi_wait_completion();
}

void ice_spi_write_blocking(uint8_t const *data, size_t data_size) {
    ice_spi_write_async(data, data_size, NULL, NULL);
    ice_spi_wait_completion();
}
