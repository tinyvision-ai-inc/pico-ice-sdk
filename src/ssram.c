#include <assert.h>

#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "boards/pico_ice.h"

#include "ice/ssram.h"

#define CMD_WRITE              0x02
#define CMD_READ               0x03

#define RESELECT_DELAY_US 2

static uint8_t g_dummy;
static volatile int g_tx_dma_channel = -1;
static volatile int g_rx_dma_channel = -1;
static volatile int g_irq;
static volatile int g_cs_pin = -1;

/// Wait that our own ongoing transaction completes.
void ice_ssram_wait(void) {
    while (ice_ssram_is_busy()) {
        // Exiting the interrupt handler implicitly sets an event.
        __wfe();
    }
}

bool ice_ssram_is_busy(void) {
    return g_cs_pin >= 0;
}

/// Select the SRAM for SPI transaction.
static void ice_ssram_select(int cs_pin) {
    g_cs_pin = cs_pin;

    // Short delay for two reasons: 1) to pull-up SS_SSRAM via pull-up resistor and
    // 2) to ensure memory is deselected long enough to refresh DRAM.
    sleep_us(1);

    gpio_put(cs_pin, false);
}

/// Select the SRAM for SPI transaction.
static void ice_ssram_deselect(void) {
    assert(g_cs_pin >= 0);
    
    // Busy wait until SCK goes low.
    while (gpio_get(ICE_FLASH_SPI_SCK_PIN)) {
        tight_loop_contents();
    }

    // This is called when the RX DMA transfers complete, not the TX transfers complete. Deselecting the PSRAM when
    // the TX transfers complete would be wrong. The DMA controller might have done its work but there could still
    // be untransmitted data in the SPI peripheral's TX FIFO or shift register, so it would be too early to deselect
    // the PSRAM chip.
    gpio_put(g_cs_pin, true);
    g_cs_pin = -1;
}

/// In a more complete application, this might invoke DMA complete callback or, if an RTOS were in use,
/// wake up a task blocked waiting for the DMA to finish.
static void ice_ssram_irq_handler(void) {
    if (dma_irqn_get_channel_status(g_irq - DMA_IRQ_0, g_rx_dma_channel)) {
        dma_irqn_acknowledge_channel(g_irq - DMA_IRQ_0, g_rx_dma_channel);
        ice_ssram_deselect();
    }
}

static void cs_pin_init(int cs_pin) {
    gpio_init(cs_pin);
    gpio_put(cs_pin, true);
    gpio_set_dir(cs_pin, GPIO_OUT);
}

void ice_ssram_init(int irq) {
    dma_channel_config cfg;

    ice_ssram_deinit();

    spi_init(SPI_SSRAM, 10 * 1000 * 1000);
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
        channel_config_set_dreq(&cfg, spi_get_dreq(SPI_SSRAM, true));
        channel_config_set_write_increment(&cfg, false);
        dma_channel_configure(g_tx_dma_channel, &cfg, &spi_get_hw(SPI_SSRAM)->dr, 0, 0, false);

        // This DMA channel transfers from PSRAM to internal RAM.
        cfg = dma_channel_get_default_config(g_rx_dma_channel);
        channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
        channel_config_set_dreq(&cfg, spi_get_dreq(SPI_SSRAM, false));
        channel_config_set_read_increment(&cfg, false);
        dma_channel_configure(g_rx_dma_channel, &cfg, 0, &spi_get_hw(SPI_SSRAM)->dr, 0, false);

        // An interrupt that asserts when DMA transfers complete.
        dma_irqn_set_channel_enabled(irq - DMA_IRQ_0, g_rx_dma_channel, true);
        irq_add_shared_handler(irq, ice_ssram_irq_handler, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        irq_set_enabled(irq, true);
    }
}

// Release hardware resources for SSRAM
void ice_ssram_deinit(void) {
    // Wait for previous transactions from this library to terminate
    ice_ssram_wait();

    if (g_tx_dma_channel >= 0) {
        dma_channel_unclaim(g_tx_dma_channel);
        g_tx_dma_channel = -1;
    }

    if (g_rx_dma_channel >= 0) {
        // Note that the IRQ is not disabled here; the IRQ is likely shared with other systems (there are only 2
        // DMA IRQs total) and disabling it here would disable it for those other systems too.
        //irq_set_enabled(g_irq, false); // Deliberately not doing this.

        irq_remove_handler(g_irq, ice_ssram_irq_handler);
        dma_irqn_set_channel_enabled(g_irq - DMA_IRQ_0, g_rx_dma_channel, false);

        dma_channel_unclaim(g_rx_dma_channel);
        g_rx_dma_channel = -1;
    }

    gpio_set_outover(ICE_SSRAM_SPI_CS_PIN, GPIO_OVERRIDE_NORMAL);
    gpio_set_dir(ICE_SSRAM_SPI_CS_PIN, GPIO_IN);
    gpio_set_dir(ICE_FLASH_SPI_CSN_PIN, GPIO_IN);

    spi_deinit(SPI_SSRAM);
}

/// Enqueue a SPI write operation performed asynchronously.
/// Call ice_ssram_wait() after this to perform a blocking write until completion.
void ice_ssram_write(int cs_pin, uint32_t dest_addr, const void* src, uint32_t size) {
    // Wait for previous transactions from this library to terminate
    ice_ssram_wait();

    ice_ssram_select(cs_pin);

    // Output read sequence command.
    uint8_t command[] = { CMD_WRITE, dest_addr >> 16, dest_addr >> 8, dest_addr };
    spi_write_blocking(SPI_SSRAM, command, sizeof(command));

    if (g_rx_dma_channel >= 0) {
        // Receive to empty the SPI peripheral's RX FIFO and assert an interrupt on completion.
        hw_clear_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
        dma_channel_transfer_to_buffer_now(g_rx_dma_channel, &g_dummy, size);

        hw_set_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
        dma_channel_transfer_from_buffer_now(g_tx_dma_channel, src, size);
    } else {
        spi_write_blocking(SPI_SSRAM, src, size);
        ice_ssram_deselect();
    }
}

void ice_ssram_read(int cs_pin, void* dest, uint32_t src_addr, uint32_t size) {
    // Wait for previous transactions from this library to terminate
    ice_ssram_wait();

    ice_ssram_select(cs_pin);

    // Output write sequence command. This also ignores data received before and during the command bits
    // and drains the receive FIFO so can start the DMA transfer immediately after.
    uint8_t command[] = { CMD_READ, src_addr >> 16, src_addr >> 8, src_addr };
    spi_write_blocking(SPI_SSRAM, command, sizeof(command));

    if (g_rx_dma_channel >= 0) {
        // Must start RX channel first. Suppose TX channel started first and a long-running interrupt handler ran
        // before starting the RX channel. In that time, the RX FIFO could overflow. With RX starting first, the
        // RX FIFO won't start to fill until TX also starts, since TX drives SCLK.
        hw_set_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
        dma_channel_transfer_to_buffer_now(g_rx_dma_channel, dest, size);

        hw_clear_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
        dma_channel_transfer_from_buffer_now(g_tx_dma_channel, &g_dummy, size);
    } else {
        spi_read_blocking(SPI_SSRAM, 0, dest, size);
        ice_ssram_deselect();
    }
}
