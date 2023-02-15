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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "hardware/sync.h"
#include "pico/stdlib.h"
#include "boards/pico_ice.h"
#include "ice_spi.h"

volatile static bool g_transfer_done = true;
volatile static void (*g_async_callback)(volatile void *);
volatile static void *g_async_context;

static uint8_t g_spi_tx_pin;
static uint8_t g_spi_rx_pin;

void ice_spi_init(void) {
    // This driver is only focused on one particular SPI bus
    gpio_init(ICE_DEFAULT_SPI_SCK_PIN);
    gpio_init(ICE_DEFAULT_SPI_TX_PIN);
    gpio_init(ICE_DEFAULT_SPI_RX_PIN);

    // Everything in high impedance before a transaction occurs
    gpio_set_dir(ICE_DEFAULT_SPI_SCK_PIN, GPIO_IN);
    gpio_set_dir(ICE_DEFAULT_SPI_TX_PIN, GPIO_IN);
    gpio_set_dir(ICE_DEFAULT_SPI_RX_PIN, GPIO_IN);
}

static uint8_t transfer_byte(uint8_t tx) {
    uint8_t rx;

    for (uint8_t i = 0; i < 8; i++) {
        // Update TX and immediately set negative edge.
        gpio_put(ICE_DEFAULT_SPI_SCK_PIN, false);
        gpio_put(g_spi_tx_pin, tx >> 7);
        tx <<= 1;

        // stable for a while with clock low
        sleep_us(1);

        // Sample RX as we set positive edge.
        rx <<= 1;
        rx |= gpio_get(g_spi_rx_pin);
        gpio_put(ICE_DEFAULT_SPI_SCK_PIN, true);

        // stable for a while with clock high
        sleep_us(1);
    }
    return rx;
}

void ice_spi_chip_select(uint8_t csn_pin, bool tx_rx_swapped) {
    // used for device with alternate pinouts in different modes
    if (tx_rx_swapped) {
        g_spi_rx_pin = ICE_DEFAULT_SPI_TX_PIN;
        g_spi_tx_pin = ICE_DEFAULT_SPI_RX_PIN;
    } else {
        g_spi_rx_pin = ICE_DEFAULT_SPI_RX_PIN;
        g_spi_tx_pin = ICE_DEFAULT_SPI_TX_PIN;
    }

    // Drive the bus, going out of high-impedance mode
    gpio_put(ICE_DEFAULT_SPI_SCK_PIN, false);
    gpio_put(g_spi_tx_pin, true);
    gpio_set_dir(ICE_DEFAULT_SPI_SCK_PIN, GPIO_OUT);
    gpio_set_dir(g_spi_tx_pin, GPIO_OUT);

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
    gpio_set_dir(g_spi_tx_pin, GPIO_IN);
}

static void prepare_transfer(void (*callback)(volatile void *), void *context) {
    uint32_t status;

    ice_spi_await_async_completion();

    status = save_and_disable_interrupts();
    g_async_callback = callback;
    g_async_context = context;
    g_transfer_done = false;
    restore_interrupts(status);
}

// TODO: this is not yet called from interrupt yet
static void spi_irq_handler(void) {
    if (true) { // TODO: check for pending bytes to transfer
        if (g_async_callback != NULL) {
            (*g_async_callback)(g_async_context);
        }
        g_transfer_done = true;
    }
}

void ice_spi_write_async(uint8_t const *buf, size_t len, void (*callback)(volatile void *), void *context) {
    // TODO: we could just call callback(context) directly but this is to mimick the future behavior
    prepare_transfer(callback, context);

    for (; len > 0; len--, buf++) {
        transfer_byte(*buf);
    }
    spi_irq_handler();
}

void ice_spi_read_async(uint8_t tx, uint8_t *buf, size_t len, void (*callback)(volatile void *), void *context) {
    // TODO: we could just call callback(context) directly but this is to mimick the future behavior
    prepare_transfer(callback, context);

    for (; len > 0; len--, buf++) {
        *buf = transfer_byte(tx);
    }
    spi_irq_handler();
}

bool ice_spi_is_async_complete(void) {
    return g_transfer_done;
}

void ice_spi_await_async_completion(void) {
    while (!ice_spi_is_async_complete()) {
        // _WFE(); // TODO: uncomment this while switching to interrupt-based implementation
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
