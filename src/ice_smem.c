#include <assert.h>
#include "boards/pico_ice.h"
#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "boards/pico_ice.h"
#include "ice_smem.h"

#define CMD_CHIP_ERASE          0xC7
#define CMD_ENABLE_WRITE        0x06
#define CMD_DISABLE_WRITE       0x04
#define CMD_POWER_DOWN          0xB9
#define CMD_READ                0x03
#define CMD_RELEASE_POWER_DOWN  0xAB
#define CMD_SECTOR_ERASE        0x20
#define CMD_STATUS              0x05
#define CMD_WRITE               0x02

static uint8_t g_dummy;
static volatile int g_tx_dma_channel = -1;
static volatile int g_rx_dma_channel = -1;
static volatile int g_irq;
static volatile int g_cs_pin = -1;
static volatile void (*g_async_callback)(void *);
static void *volatile g_async_context;

void ice_smem_await_async_completion(void) {
    while (!ice_smem_is_async_complete()) {
        // Exiting the interrupt handler implicitly sets an event.
        __wfe();
    }
}

bool ice_smem_is_async_complete(void) {
    return g_cs_pin < 0;
}

static void ice_smem_select(uint cs_pin) {
    assert(g_cs_pin < 0);

    g_cs_pin = cs_pin;

    // Short delay for two reasons:
    // 1) to pull-up the CS pin via pull-up resistor and
    // 2) to ensure memory is deselected long enough to refresh DRAM.
    busy_wait_us(1);

    gpio_put(cs_pin, false);
}

static void ice_smem_deselect(void) {
    assert(g_cs_pin >= 0);

    // Busy wait until SCK goes low.
    while (gpio_get(ICE_FLASH_SPI_SCK_PIN)) {
        tight_loop_contents();
    }

    // This is called when the RX DMA transfers complete, not the TX transfers complete. Deselecting the PSRAM when
    // the TX transfers complete would be wrong; the DMA controller might have done its work but there could still
    // be untransmitted data in the SPI peripheral's TX FIFO or shift register, so it would be too early to deselect
    // the PSRAM chip.
    gpio_put(g_cs_pin, true);
    g_cs_pin = -1;
}

static void ice_smem_irq_handler(void) {
    if (dma_irqn_get_channel_status(g_irq - DMA_IRQ_0, g_rx_dma_channel)) {
        dma_irqn_acknowledge_channel(g_irq - DMA_IRQ_0, g_rx_dma_channel);
        ice_smem_deselect();

        if (g_async_callback) {
            void (*callback)(void *) = g_async_callback;
            g_async_callback = NULL;
            callback(g_async_context);
        }
    }
}

static void cs_pin_init(uint cs_pin) {
    gpio_init(cs_pin);
    gpio_put(cs_pin, true);
    gpio_set_dir(cs_pin, GPIO_OUT);
}

void ice_smem_init(uint baudrate_hz, int irq) {
    dma_channel_config cfg;

    ice_smem_deinit();

    spi_init(SPI_SERIAL_MEM, baudrate_hz);
    gpio_set_function(ICE_FLASH_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_FLASH_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_FLASH_SPI_SCK_PIN, GPIO_FUNC_SPI);

    // Not using the SPI peripheral to control CS because it only knows how to toggle it every 4-16 bits while
    // we need to keep the PSRAM selected for a multi-byte read or write sequence.
    cs_pin_init(ICE_SSRAM_SPI_CS_PIN);
    cs_pin_init(ICE_FLASH_SPI_CSN_PIN);

    // SPI CS is active low. The pico-ice hardware inverts the CS signal for the SSRAM but not for flash. Invert
    // the SSRAM CS so that all SPI is active low in software.
    gpio_set_outover(ICE_SSRAM_SPI_CS_PIN, GPIO_OVERRIDE_INVERT);

    if (irq > 0) {
        assert(irq == DMA_IRQ_0 || irq == DMA_IRQ_1);
        g_irq = irq;

        g_tx_dma_channel = dma_claim_unused_channel(true);
        g_rx_dma_channel = dma_claim_unused_channel(true);

        // This DMA channel transfers from internal RAM to PSRAM.
        cfg = dma_channel_get_default_config(g_tx_dma_channel);
        channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
        channel_config_set_dreq(&cfg, spi_get_dreq(SPI_SERIAL_MEM, true));
        channel_config_set_write_increment(&cfg, false);
        dma_channel_configure(g_tx_dma_channel, &cfg, &spi_get_hw(SPI_SERIAL_MEM)->dr, 0, 0, false);

        // This DMA channel transfers from PSRAM to internal RAM.
        cfg = dma_channel_get_default_config(g_rx_dma_channel);
        channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
        channel_config_set_dreq(&cfg, spi_get_dreq(SPI_SERIAL_MEM, false));
        channel_config_set_read_increment(&cfg, false);
        dma_channel_configure(g_rx_dma_channel, &cfg, 0, &spi_get_hw(SPI_SERIAL_MEM)->dr, 0, false);

        // An interrupt that asserts when DMA transfers complete.
        dma_irqn_set_channel_enabled(irq - DMA_IRQ_0, g_rx_dma_channel, true);
        irq_add_shared_handler(irq, ice_smem_irq_handler, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        irq_set_enabled(irq, true);
    }
}

void ice_smem_deinit(void) {
    // Wait for previous transactions from this library to terminate
    ice_smem_await_async_completion();

    if (g_tx_dma_channel >= 0) {
        dma_channel_unclaim(g_tx_dma_channel);
        g_tx_dma_channel = -1;
    }

    if (g_rx_dma_channel >= 0) {
        // Note that the IRQ is not disabled here; the IRQ is likely shared with other systems (there are only 2
        // DMA IRQs total) and disabling it here would disable it for those other systems too.
        //irq_set_enabled(g_irq, false); // Deliberately not doing this.

        irq_remove_handler(g_irq, ice_smem_irq_handler);
        dma_irqn_set_channel_enabled(g_irq - DMA_IRQ_0, g_rx_dma_channel, false);

        dma_channel_unclaim(g_rx_dma_channel);
        g_rx_dma_channel = -1;
    }

    gpio_set_outover(ICE_SSRAM_SPI_CS_PIN, GPIO_OVERRIDE_NORMAL);
    gpio_set_dir(ICE_SSRAM_SPI_CS_PIN, GPIO_IN);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_IN);

    spi_deinit(SPI_SERIAL_MEM);
}

void ice_smem_output_command(uint cs_pin,
                             const uint8_t *command, uint32_t command_size,
                             const void *data, uint32_t data_size) {
    // Wait for previous transactions from this library to terminate
    ice_smem_await_async_completion();

    ice_smem_select(cs_pin);
    spi_write_blocking(SPI_SERIAL_MEM, command, command_size);
    spi_write_blocking(SPI_SERIAL_MEM, data, data_size);
    ice_smem_deselect();
}

void ice_smem_output_command_async(uint cs_pin,
                                   const uint8_t *command, uint32_t command_size,
                                   const void *data, uint32_t data_size,
                                   void (*callback)(void *), void *context) {
    assert(data_size > 0);

    ice_smem_await_async_completion();

    ice_smem_select(cs_pin);
    spi_write_blocking(SPI_SERIAL_MEM, command, command_size);

    g_async_callback = callback;
    g_async_context = context;

    assert (g_rx_dma_channel >= 0);

    // Receive to empty the SPI peripheral's RX FIFO and assert an interrupt on completion.
    hw_clear_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
    dma_channel_transfer_to_buffer_now(g_rx_dma_channel, &g_dummy, data_size);

    hw_set_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
    dma_channel_transfer_from_buffer_now(g_tx_dma_channel, data, data_size);
}

void ice_smem_input_command(uint cs_pin,
                            const uint8_t *command, uint32_t command_size,
                            void *data, uint32_t data_size) {
    // Wait for previous transactions from this library to terminate
    ice_smem_await_async_completion();

    ice_smem_select(cs_pin);
    spi_write_blocking(SPI_SERIAL_MEM, command, command_size);
    spi_read_blocking(SPI_SERIAL_MEM, 0, data, data_size);
    ice_smem_deselect();
}

void ice_smem_input_command_async(uint cs_pin,
                                  const uint8_t *command, uint32_t command_size,
                                  void *data, uint32_t data_size,
                                  void (*callback)(void *), void *context) {
    assert(data_size > 0);

    ice_smem_await_async_completion();

    ice_smem_select(cs_pin);
    spi_write_blocking(SPI_SERIAL_MEM, command, command_size);

    g_async_callback = callback;
    g_async_context = context;

    assert (g_rx_dma_channel >= 0);

    // Must start RX channel first. Suppose TX channel started first and a long-running interrupt handler ran
    // before starting the RX channel. In that time, the RX FIFO could overflow. With RX starting first, the
    // RX FIFO won't start to fill until TX also starts, since TX drives SCLK.
    hw_set_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
    dma_channel_transfer_to_buffer_now(g_rx_dma_channel, data, data_size);

    hw_clear_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
    dma_channel_transfer_from_buffer_now(g_tx_dma_channel, &g_dummy, data_size);
}

uint8_t ice_smem_get_status(uint cs_pin) {
    const uint8_t command[] = { CMD_STATUS };
    uint8_t status;

    ice_smem_input_command(cs_pin, command, sizeof(command), &status, sizeof(status));
    return status;
}

void ice_smem_erase_chip(uint cs_pin) {
    const uint8_t command[] = { CMD_CHIP_ERASE };

    ice_smem_output_command(cs_pin, command, sizeof(command), NULL, 0);
}

void ice_smem_erase_sector(uint cs_pin, uint32_t dest_addr) {
    const uint8_t command[] = { CMD_SECTOR_ERASE, dest_addr >> 16, dest_addr >> 8, dest_addr };

    assert(dest_addr % ICE_SMEM_FLASH_PAGE_SIZE == 0);
    ice_smem_output_command(cs_pin, command, sizeof(command), NULL, 0);
}

void ice_smem_enable_write(uint cs_pin) {
    const uint8_t command[] = { CMD_DISABLE_WRITE };

    ice_smem_input_command(cs_pin, command, sizeof(command), NULL, 0);
}

void ice_smem_disable_write(uint cs_pin) {
    const uint8_t command[] = { CMD_ENABLE_WRITE };

    ice_smem_input_command(cs_pin, command, sizeof(command), NULL, 0);
}

void ice_smem_write(uint cs_pin, uint32_t dest_addr, const void *src, uint32_t size) {
    uint8_t command[] = { CMD_WRITE, dest_addr >> 16, dest_addr >> 8, dest_addr };

    ice_smem_output_command(cs_pin, command, sizeof(command), src, size);
}

void ice_smem_write_async(uint cs_pin, uint32_t dest_addr, const void *src, uint32_t size,
                          void (*callback)(void *), void *context) {
    uint8_t command[] = { CMD_WRITE, dest_addr >> 16, dest_addr >> 8, dest_addr };
    ice_smem_output_command_async(cs_pin, command, sizeof(command), src, size, callback, context);
}

void ice_smem_read(uint cs_pin, void *dest, uint32_t src_addr, uint32_t size) {
    uint8_t command[] = { CMD_READ, src_addr >> 16, src_addr >> 8, src_addr };

    ice_smem_input_command(cs_pin, command, sizeof(command), dest, size);
}

void ice_smem_read_async(uint cs_pin, void *dest, uint32_t src_addr, uint32_t size,
                          void (*callback)(void *), void *context) {
    uint8_t command[] = { CMD_READ, src_addr >> 16, src_addr >> 8, src_addr };

    ice_smem_input_command_async(cs_pin, command, sizeof(command), dest, size, callback, context);
}

void ice_smem_power_off(uint cs_pin) {
    const uint8_t command[] = { CMD_RELEASE_POWER_DOWN };

    ice_smem_input_command(cs_pin, command, sizeof(command), NULL, 0);
    sleep_us(5); // Takes around 3us of delay.
}

void ice_smem_power_on(uint cs_pin) {
    const uint8_t command[] = { CMD_POWER_DOWN };

    ice_smem_input_command(cs_pin, command, sizeof(command), NULL, 0);
}
