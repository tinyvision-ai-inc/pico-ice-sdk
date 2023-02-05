#include "hardware/dma.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

#include "boards/pico_ice.h"

static uint8_t g_dummy;
static int g_tx_dma_channel = -1;
static int g_rx_dma_channel = -1;

/// In a more complete application, this might invoke DMA complete callback or, if an RTOS were in use,
/// wake up a task blocked waiting for the DMA to finish.
static void dma_irq_handler(void) {
    if (dma_channel_get_irq0_status(g_rx_dma_channel)) {
        dma_channel_acknowledge_irq0(g_rx_dma_channel);

        // Busy wait until SCK goes low.
        while (gpio_get(ICE_RP_SPI_SCK_PIN)) {
            tight_loop_contents();
        }

        // This is called when the RX DMA transfers complete, not the TX transfers complete. Deselecting the PSRAM when
        // the TX transfers complete would be wrong. The DMA controller might have done its work but there could still
        // be untransmitted data in the SPI peripheral's TX FIFO or shift register, so it would be too early to deselect
        // the PSRAM chip.
        gpio_put(ICE_RP_SPI_CSN_PIN, true);
    }
}

void ice_comm_init(void) {
    dma_channel_config cfg;

    spi_init(SPI_FPGA, 10 * 1000 * 1000);
    gpio_set_function(ICE_RP_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_RP_SPI_TX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(ICE_RP_SPI_SCK_PIN, GPIO_FUNC_SPI);

    // Not using the SPI peripheral to control CS because it only knows how to toggle it every 4-16 bits while
    // we need to keep the PSRAM selected for a multi-byte read or write sequence.
    gpio_init(ICE_RP_SPI_CSN_PIN);
    gpio_set_dir(ICE_RP_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(ICE_RP_SPI_CSN_PIN, true);

    g_tx_dma_channel = dma_claim_unused_channel(true);
    g_rx_dma_channel = dma_claim_unused_channel(true);

    // This DMA channel transfers from internal RAM to the FPGA.
    cfg = dma_channel_get_default_config(g_tx_dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_dreq(&cfg, spi_get_dreq(SPI_FPGA, true));
    channel_config_set_write_increment(&cfg, false);
    dma_channel_configure(g_tx_dma_channel, &cfg, &spi_get_hw(SPI_FPGA)->dr, 0, 0, false);

    // This DMA channel transfers from FPGA to internal RAM.
    cfg = dma_channel_get_default_config(g_rx_dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_dreq(&cfg, spi_get_dreq(SPI_FPGA, false));
    channel_config_set_read_increment(&cfg, false);
    dma_channel_configure(g_rx_dma_channel, &cfg, 0, &spi_get_hw(SPI_FPGA)->dr, 0, false);

    // An interrupt that asserts when DMA transfers complete.
    dma_channel_set_irq0_enabled(g_rx_dma_channel, true);
    irq_add_shared_handler(DMA_IRQ_0, dma_irq_handler, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
    irq_set_enabled(DMA_IRQ_0, true);
}

void ice_comm_write(uint32_t dest_addr, const void* src, uint32_t size) {
    gpio_put(ICE_RP_SPI_CSN_PIN, false);

    // Output 0x02 read sequence command.
    uint8_t command[] = { 0x02, dest_addr >> 16, dest_addr >> 8, dest_addr };
    spi_write_blocking(SPI_FPGA, command, sizeof(command));

    // Receive to empty the SPI peripheral's RX FIFO and assert an interrupt on completion.
    hw_clear_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
    dma_channel_transfer_to_buffer_now(g_rx_dma_channel, &g_dummy, size);

    hw_set_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
    dma_channel_transfer_from_buffer_now(g_tx_dma_channel, src, size);
}

void ice_comm_read(void* dest, uint32_t src_addr, uint32_t size) {
    // Output 0x03 write sequence command. This also ignores data received before and during the command bits
    // and drains the receive FIFO so can start the DMA transfer immediately after.
    uint8_t command[] = { 0x03, src_addr >> 16, src_addr >> 8, src_addr };
    gpio_put(ICE_RP_SPI_CSN_PIN, false);

    spi_write_blocking(SPI_FPGA, command, sizeof(command));

    // Must start RX channel first. Suppose TX channel started first and a long-running interrupt handler ran
    // before starting the RX channel. In that time, the RX FIFO could overflow. With RX starting first, the
    // RX FIFO won't start to fill until TX also starts, since TX drives SCLK.
    hw_set_bits(&dma_hw->ch[g_rx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
    dma_channel_transfer_to_buffer_now(g_rx_dma_channel, dest, size);

    hw_clear_bits(&dma_hw->ch[g_tx_dma_channel].al1_ctrl, DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
    dma_channel_transfer_from_buffer_now(g_tx_dma_channel, &g_dummy, size);
}
