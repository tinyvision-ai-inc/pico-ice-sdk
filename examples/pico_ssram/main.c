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

#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice_usb.h"
#include "ice_sdk.h"
#include "ice_fpga.h"
#include "ice_smem.h"

#define DATA_LEN 8
#define START_ADDR 0

static uint8_t write_data[DATA_LEN];
static uint8_t read_data[DATA_LEN];

void write_callback(void* context) {
    ice_smem_read_async(ICE_SSRAM_SPI_CS_PIN, read_data, START_ADDR, sizeof(read_data), NULL, NULL);
}

int main() {
    ice_sdk_init();
    stdio_init_all();
    ice_smem_init(10*1000*1000, DMA_IRQ_1 /* Pass -1 for synchronous mode */);

    // Dont let the FPGA on the bus so we get exclusive access
    ice_halt();

    for (uint16_t i = 0; i < DATA_LEN; i++) {
        write_data[i] = i;
    }

    for (;;) {
        tud_task();

        // The write callback chains a read sequence immediately after the write sequence from an interrupt handler,
        // without any interaction with the main thread.
        ice_smem_write_async(ICE_SSRAM_SPI_CS_PIN, START_ADDR, write_data, sizeof(write_data), write_callback, NULL);

        // This doesn't return until both the write operation and the read operation chained after it complete.
        ice_smem_await_async_completion();

        for (size_t i = 0; i < DATA_LEN; i++) {
            if (read_data[i] != i) {
                printf("Error at 0x%x", i);
            }
        }
    }
}
