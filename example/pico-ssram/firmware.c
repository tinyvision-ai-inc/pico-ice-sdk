#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "boards/pico_ice.h"
#include "ice/usb.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/spi.h"
#include "ice/sdk.h"
#include "ice/fpga.h"
#include "ice/ssram.h"

#define DATA_LEN 8
#define START_ADDR 0

static volatile int g_sequence_count;

void async_callback(void) {
    ++g_sequence_count;
}

int main() {
    ice_sdk_init();
    stdio_init_all();
    ice_ssram_init(10*1000*1000, DMA_IRQ_1 /* Pass -1 for synchronous mode */);
    ice_ssram_set_async_callback(async_callback);

    // Dont let the FPGA on the bus so we get exclusive access
    ice_fpga_halt();

    static uint8_t write_data[DATA_LEN];
    static uint8_t read_data[DATA_LEN];
    for (uint16_t i = 0; i < DATA_LEN; i++) {
        write_data[i] = i;
    }

    for (;;) {
        ice_usb_task();
        ice_ssram_write_async(ICE_SSRAM_SPI_CS_PIN, START_ADDR, write_data, sizeof(write_data));
        ice_ssram_read_async(ICE_SSRAM_SPI_CS_PIN, read_data, START_ADDR, sizeof(read_data));
        ice_ssram_await_async_completion();

        for (size_t i = 0; i < DATA_LEN; i++) {
            if (read_data[i] != i) {
                printf("Error at 0x%x", i);
            }
        }
    }
}
