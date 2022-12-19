#include "pico/stdlib.h"
#include "pico/stdio.h"

#include "boards/pico_ice.h"

#include "hardware/dma.h"
#include "hardware/irq.h"
#include "hardware/spi.h"

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
    ice_fpga_halt();

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
