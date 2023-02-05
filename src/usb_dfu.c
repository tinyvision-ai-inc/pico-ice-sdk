#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "hardware/watchdog.h"

#include "ice_fpga.h"
#include "ice_flash.h"
#include "ice_bitstream.h"

#include "tusb.h"

static bool dfu_download_pending;

/*
 * Invoked right before tud_dfu_download_cb() (state=DFU_DNBUSY) or tud_dfu_manifest_cb() (state=DFU_MANIFEST)
 * Application return timeout in milliseconds (bwPollTimeout) for the next download/manifest operation.
 * During this period, USB host won't try to communicate with us.
 */
uint32_t tud_dfu_get_timeout_cb(uint8_t alt, uint8_t state)
{
	return 0; /* Request we are polled in 1ms */
}

/*
 * Invoked when received DFU_DNLOAD (wLength>0) following by DFU_GETSTATUS (state=DFU_DNBUSY) requests
 * This callback could be returned before flashing op is complete (async).
 * Once finished flashing, application must call tud_dfu_finish_flashing()
 */
void tud_dfu_download_cb(uint8_t alt, uint16_t block_num, const uint8_t *data, uint16_t length)
{
    if (!dfu_download_pending) {
        dfu_download_pending = true;
        if (alt == 1) {
            ice_flash_init();
        } else {
            ice_bitstream_open();
        }
    }

    uint32_t dest_addr = block_num * CFG_TUD_DFU_XFER_BUFSIZE;

    for (uint32_t offset = 0; offset < length; offset += ICE_FLASH_PAGE_SIZE) {
        if (alt == 1) {
            if ((dest_addr + offset) % ICE_FLASH_SECTOR_SIZE == 0) {
                ice_flash_erase_sector(dest_addr + offset);
            }

            ice_flash_program_page(dest_addr + offset, data + offset);
        } else {
            ice_bitstream_write(data, length);
        }
    }

    tud_dfu_finish_flashing(DFU_STATUS_OK);
}

/*
 * Invoked when download process is complete, received DFU_DNLOAD (wLength=0) following by DFU_GETSTATUS (state=Manifest)
 * Application can do checksum, or actual flashing if buffered entire image previously.
 * Once finished flashing, application must call tud_dfu_finish_flashing()
 */
void tud_dfu_manifest_cb(uint8_t alt)
{
    assert(dfu_download_pending);
    dfu_download_pending = false;

    bool fpga_done;
    if (alt == 1) {
        ice_flash_deinit();
        fpga_done = ice_reset();
    } else {
        fpga_done = ice_bitstream_close();
    }

    tud_dfu_finish_flashing(fpga_done ? DFU_STATUS_OK : DFU_STATUS_ERR_FIRMWARE);
}

/*
 * Called if -R option passed to dfu-util.
 */
void tud_dfu_detach_cb(void)
{
    watchdog_reboot(0, 0, 0);
}
