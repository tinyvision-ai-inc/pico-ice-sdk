/**************************************************************************//**
 * @file     sd.h
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 14/06/30 2:23p $
 * @brief    NUC505 SD driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#ifndef __SD_H__
#define __SD_H__

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SD_Driver SD Driver
  @{
*/


/** @addtogroup NUC505_SD_EXPORTED_CONSTANTS SD Exported Constants
  @{
*/

#define SD_CARD         0
#define SD_ERR_ID       0xFFFF0100

#define SD_TIMEOUT      (SD_ERR_ID|0x01)
#define SD_NO_MEMORY    (SD_ERR_ID|0x02)

//-- function return value
#define Successful      0
#define Fail            1

//--- define type of SD card or MMC
#define SD_TYPE_UNKNOWN         0
#define SD_TYPE_SD_HIGH         1
#define SD_TYPE_SD_LOW          2
#define SD_TYPE_MMC             3   // MMC access mode: Byte mode for capacity <= 2GB
#define SD_TYPE_MMC_SECTOR_MODE 4   // MMC access mode: Sector mode for capacity > 2GB


/* SD error */
#define SD_NO_SD_CARD       (SD_ERR_ID|0x10)
#define SD_ERR_DEVICE       (SD_ERR_ID|0x11)
#define SD_INIT_TIMEOUT     (SD_ERR_ID|0x12)
#define SD_SELECT_ERROR     (SD_ERR_ID|0x13)
#define SD_WRITE_PROTECT    (SD_ERR_ID|0x14)
#define SD_INIT_ERROR       (SD_ERR_ID|0x15)
#define SD_CRC7_ERROR       (SD_ERR_ID|0x16)
#define SD_CRC16_ERROR      (SD_ERR_ID|0x17)
#define SD_CRC_ERROR        (SD_ERR_ID|0x18)
#define SD_CMD8_ERROR       (SD_ERR_ID|0x19)

#define MMC_FREQ    20000
#define EMMC_FREQ   26000
#define SD_FREQ     24000
#define SDHC_FREQ   24000

#define STOR_STRING_LEN 32

#define SD_PORT0    (1 << 0)  /*!< Card select SD0 \hideinitializer */
#define SD_PORT1    (1 << 2)  /*!< Card select SD1 \hideinitializer */

#define CardDetect_From_GPIO    (1 << 8)   /*!< Card detection pin is GPIO \hideinitializer */
#define CardDetect_From_DAT3    (1 << 9)   /*!< Card detection pin is DAT3 \hideinitializer */

/*@}*/ /* end of group NUC505_SD_EXPORTED_CONSTANTS */

/** @addtogroup NUC505_SD_EXPORTED_TYPEDEF SD Exported Type Defines
  @{
*/
typedef struct SD_info_t
{
    uint32_t    CardType;       /*!< SD_TYPE_SD_HIGH for SDHC, SD_TYPE_SD_LOW for SD, or SD_TYPE_MMC for MMC */
    uint32_t    RCA;            /*!< relative card address */
    uint8_t     IsCardInsert;   /*!< card insert state */
} SD_INFO_T;

/* we allocate one of these for every device that we remember */
typedef struct disk_data_t
{
    struct disk_data_t  *next;    /*!< next device */

    /* information about the device -- always good */
    unsigned int  totalSectorN;   /*!< total sector number */
    unsigned int  diskSize;       /*!< disk size in Kbytes */
    int           sectorSize;     /*!< sector size in bytes */
    char          vendor[STOR_STRING_LEN];  /*!< SD card vendor */
    char          product[STOR_STRING_LEN]; /*!< SD card product id */
    char          serial[STOR_STRING_LEN];  /*!< SD card serial number */
} DISK_DATA_T;

extern DISK_DATA_T SD_DiskInfo0;

/*@}*/ /* end of group NUC505_SD_EXPORTED_TYPEDEF */


/** @addtogroup NUC505_SD_EXPORTED_FUNCTIONS SD Exported Functions
  @{
*/


/**
 *  @brief    Enable specified interrupt.
 *
 *  @param    [in] u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTEN_BLKDIEN_Msk / \ref SDH_INTEN_CRCIEN_Msk  / \ref SDH_INTEN_CDIEN0_Msk /
 *                           \ref SDH_INTEN_RTOIEN_Msk  / \ref SDH_INTEN_DITOIEN_Msk / \ref SDH_INTEN_CDSRC0_Msk
 *
 *  @return   None.
 * \hideinitializer
 */
#define SD_ENABLE_INT(u32IntMask)   (SD->INTEN |= (u32IntMask))

/**
 *  @brief    Disable specified interrupt.
 *
 *  @param    [in] u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTEN_BLKDIEN_Msk / \ref SDH_INTEN_CRCIEN_Msk  / \ref SDH_INTEN_CDIEN0_Msk  /
 *                           \ref SDH_INTEN_RTOIEN_Msk  / \ref SDH_INTEN_DITOIEN_Msk / \ref SDH_INTEN_CDSRC0_Msk
 *
 *  @return   None.
 * \hideinitializer
 */
#define SD_DISABLE_INT(u32IntMask)  (SD->INTEN &= ~(u32IntMask))

/**
 *  @brief    Get specified interrupt flag/status.
 *
 *  @param    [in] u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTSTS_BLKDIF_Msk / \ref SDH_INTSTS_CRCIF_Msk   / \ref SDH_INTSTS_CRC7_Msk /
 *                           \ref SDH_INTSTS_CRC16_Msk  / \ref SDH_INTSTS_CRCSTS_Msk  / \ref SDH_INTSTS_DAT0STS_Msk /
 *                           \ref SDH_INTSTS_CDIF0_Msk  / \ref SDH_INTSTS_RTOIF_Msk   / \ref SDH_INTSTS_DITOIF_Msk /
 *                           \ref SDH_INTSTS_CDSTS0_Msk / \ref SDH_INTSTS_DAT1STS_Msk /
 *
 *  @retval 0: The specified interrupt is not happened.
 *  @retval 1: The specified interrupt is happened.
 * \hideinitializer
 */
#define SD_GET_INT_FLAG(u32IntMask) ((SD->INTSTS & (u32IntMask))?1:0)


/**
 *  @brief    Clear specified interrupt flag/status.
 *
 *  @param    [in] u32IntMask    Interrupt type mask:
 *                           \ref SDH_INTSTS_BLKDIF_Msk / \ref SDH_INTSTS_CRCIF_Msk  / \ref SDH_INTSTS_CDIF0_Msk  /
 *                           \ref SDH_INTSTS_RTOIF_Msk  / \ref SDH_INTSTS_DITOIF_Msk /
 *
 *  @return   None.
 * \hideinitializer
 */
#define SD_CLR_INT_FLAG(u32IntMask) (SD->INTSTS = u32IntMask)


/**
 *  @brief    Check SD Card inserted or removed.
 *
 *  @param    [in] u32CardNum    Select SD0 or SD1. (\ref SD_PORT0 / \ref SD_PORT1) \n
 *                          NUC505 only support SD0.
 *
 *  @retval   0: Card removed.
 *  @retval   1: Card inserted.
 * \hideinitializer
 */
//#define SD_IS_CARD_PRESENT(u32CardNum) ((u32CardNum & (SD_PORT0))?(SD0.IsCardInsert):(SD1.IsCardInsert))
#define SD_IS_CARD_PRESENT(u32CardNum) ((u32CardNum & (SD_PORT0))?(SD0.IsCardInsert):(SD0.IsCardInsert))

/**
 *  @brief    Get SD Card capacity.
 *
 *  @param    [in] u32CardNum    Select SD0 or SD1. (\ref SD_PORT0 / \ref SD_PORT1) \n
 *                          NUC505 only support SD0.
 *
 *  @return   SD Card capacity. (unit: KByte)
 * \hideinitializer
 */
//#define SD_GET_CARD_CAPACITY(u32CardNum)  ((u32CardNum & (SD_PORT0))?(SD_DiskInfo0.diskSize):(SD_DiskInfo1.diskSize))
#define SD_GET_CARD_CAPACITY(u32CardNum)  ((u32CardNum & (SD_PORT0))?(SD_DiskInfo0.diskSize):(SD_DiskInfo0.diskSize))

/**
 *  @brief    Get SD Card total sector number.
 *
 *  @param    [in] u32CardNum    Select SD0 or SD1. (\ref SD_PORT0 / \ref SD_PORT1) \n
 *                          NUC505 only support SD0.
 *
 *  @return   SD Card total sector number.
 * \hideinitializer
 */
#define SD_GET_CARD_SECTOR_NUM(u32CardNum)  ((u32CardNum & (SD_PORT0))?(SD_DiskInfo0.totalSectorN):(SD_DiskInfo0.totalSectorN))

void SD_Open(uint32_t u32CardDetSrc);
void SD_Close(uint32_t u32CardNum);
void SD_Probe(uint32_t u32CardNum);
uint32_t SD_Read(uint32_t u32CardNum, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount);
uint32_t SD_Write(uint32_t u32CardNum, uint8_t *pu8BufAddr, uint32_t u32StartSec, uint32_t u32SecCount);



/*@}*/ /* end of group NUC505_ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_ADC_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#endif  //end of __SD_H__
/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
