/**************************************************************************//**
 * @file        spim.h
 * @version     V1.00
 * $Revision:   1$
 * $Date:       14/07/10 5:00p$
 * @brief       NUC505 series SPIM driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __SPIM_H__
#define __SPIM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SPIM_Driver SPIM Driver
  @{
*/

/** @addtogroup NUC505_SPIM_EXPORTED_CONSTANTS SPIM Exported Constants
  @{
*/

#define SPIM_CTL0_BITMODE_STAN      (0UL << SPIM_CTL0_BITMODE_Pos)              /*!< Standard mode (SPI Interface including DO, DI, HOLD, WP). \hideinitializer */
#define SPIM_CTL0_BITMODE_DUAL      (1UL << SPIM_CTL0_BITMODE_Pos)              /*!< Dual mode (SPI Interface including D0, D1, HOLD, WP). \hideinitializer */
#define SPIM_CTL0_BITMODE_QUAD      (2UL << SPIM_CTL0_BITMODE_Pos)              /*!< Quad mode (SPI Interface including D0, D1, D2, D3). \hideinitializer */
#define SPIM_CTL0_OPMODE_IO         (0UL << SPIM_CTL0_OPMODE_Pos)               /*!< I/O Mode. \hideinitializer */
#define SPIM_CTL0_OPMODE_DMAWRITE   (1UL << SPIM_CTL0_OPMODE_Pos)               /*!< DMA Write mode. \hideinitializer */
#define SPIM_CTL0_OPMODE_DMAREAD    (2UL << SPIM_CTL0_OPMODE_Pos)               /*!< DMA Read mode. \hideinitializer */
#define SPIM_CTL0_OPMODE_DMM        (3UL << SPIM_CTL0_OPMODE_Pos)               /*!< Direct Memory Mapping mode. \hideinitializer */
#define SPIM_CTL0_CMDCODE_PAGE_PROG                 (0x02UL << SPIM_CTL0_CMDCODE_Pos)   /*!< Page Program command (in \ref SPIM_CTL0_OPMODE_DMAWRITE mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_QUAD_PAGE_PROG_TYPE1      (0x32UL << SPIM_CTL0_CMDCODE_Pos)   /*!< Quad Page Program (type 1) command (in \ref SPIM_CTL0_OPMODE_DMAWRITE mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_QUAD_PAGE_PROG_TYPE2      (0x38UL << SPIM_CTL0_CMDCODE_Pos)   /*!< Quad Page Program (type 2) command (in \ref SPIM_CTL0_OPMODE_DMAWRITE mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_QUAD_PAGE_PROG_TYPE3      (0x40UL << SPIM_CTL0_CMDCODE_Pos)   /*!< Quad Page Program (type 3) command (in \ref SPIM_CTL0_OPMODE_DMAWRITE mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_READ_DATA                 (0x03UL << SPIM_CTL0_CMDCODE_Pos)   /*!< Read Data command (in \ref SPIM_CTL0_OPMODE_DMAREAD/\ref SPIM_CTL0_OPMODE_DMM mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_FAST_READ                 (0x0BUL << SPIM_CTL0_CMDCODE_Pos)   /*!< Fast Read command (in \ref SPIM_CTL0_OPMODE_DMAREAD/\ref SPIM_CTL0_OPMODE_DMM mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_FAST_READ_DUAL_OUT        (0x3BUL << SPIM_CTL0_CMDCODE_Pos)   /*!< Fast Read Dual Output command (in \ref SPIM_CTL0_OPMODE_DMAREAD/\ref SPIM_CTL0_OPMODE_DMM mode). \hideinitializer */
#define SPIM_CTL0_CMDCODE_FAST_READ_QUAD_IO         (0xEBUL << SPIM_CTL0_CMDCODE_Pos)   /*!< Fast Read Quad I/O command (in \ref SPIM_CTL0_OPMODE_DMAREAD/\ref SPIM_CTL0_OPMODE_DMM mode). \hideinitializer */

#define SPIM_CTL1_IFSEL_GPIO        (0UL << SPIM_CTL1_IFSEL_Pos)                /*!< SPI Interface from GPIO. \hideinitializer */
#define SPIM_CTL1_IFSEL_MCP         (1UL << SPIM_CTL1_IFSEL_Pos)                /*!< SPI Interface from MCP. \hideinitializer */
#define SPIM_CTL1_IFSEL_MCP64       (2UL << SPIM_CTL1_IFSEL_Pos)                /*!< SPI Interface from MCP64. \hideinitializer */
#define SPIM_CTL1_IFSEL_INTERN      SPIM_CTL1_IFSEL_MCP                         /*!< SPI Interface from internal(MCP/MCP64). \hideinitializer */
#define SPIM_CTL1_IFSEL_EXTERN      SPIM_CTL1_IFSEL_GPIO                        /*!< SPI Interface from external(GPIO). \hideinitializer */

/* SPIM Interrupt Mask */
#define SPIM_INT_MASK                   (0x001)                                 /*!< Interrupt mask. \hideinitializer */


/*@}*/ /* end of group NUC505_SPIM_EXPORTED_CONSTANTS */

/** @addtogroup NUC505_SPIM_EXPORTED_FUNCTIONS SPIM Exported Functions
  @{
*/

/**
  * @brief                  Enable I/O mode.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32BitMode  Bit mode. Valid values include:
  *                         - \ref SPIM_CTL0_BITMODE_STAN
  *                         - \ref SPIM_CTL0_BITMODE_DUAL
  *                         - \ref SPIM_CTL0_BITMODE_QUAD
  * @param[in]  u32QDIODir  I/O direction for Quad/Dual mode. Valid values can be 0 (for input) or 1 (for output).
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_ENABLE_IO_MODE(spim, u32BitMode, u32QDIODir) \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~(SPIM_CTL0_BITMODE_Msk))) | (u32BitMode);   \
        (spim)->CTL0 = ((spim)->CTL0 & (~(SPIM_CTL0_QDIODIR_Msk))) | ((u32QDIODir) << SPIM_CTL0_QDIODIR_Pos);   \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_OPMODE_Msk)) | SPIM_CTL0_OPMODE_IO;    \
    } while (0)

/**
  * @brief                  Set bit mode for I/O mode.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32BitMode  Bit mode. Valid values include:
  *                         - \ref SPIM_CTL0_BITMODE_STAN
  *                         - \ref SPIM_CTL0_BITMODE_DUAL
  *                         - \ref SPIM_CTL0_BITMODE_QUAD
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_SET_BIT_MODE(spim, u32BitMode)  \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~(SPIM_CTL0_BITMODE_Msk))) | (u32BitMode);    \
    } while (0)

/**
  * @brief                  Set direction for Quad/Dual I/O mode.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32Dir      Direction. Valid values can be 0 (for input) and 1 (for output).
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_SET_QDIODIR(spim, u32Dir)  \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~(SPIM_CTL0_QDIODIR_Msk))) | (((u32Dir) ? 1 : 0) << SPIM_CTL0_QDIODIR_Pos);    \
    } while (0)


/**
  * @brief                  Enable DMA mode.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  isWrite     0 for DMA Read mode; 1 for DMA Write mode.
  * @param[in]  u32CmdCode  Command code.
  * - Valid values for DMA Write mode include:
  *     - \ref SPIM_CTL0_CMDCODE_PAGE_PROG
  *     - \ref SPIM_CTL0_CMDCODE_QUAD_PAGE_PROG_TYPE1
  *     - \ref SPIM_CTL0_CMDCODE_QUAD_PAGE_PROG_TYPE2
  *     - \ref SPIM_CTL0_CMDCODE_QUAD_PAGE_PROG_TYPE3
  * - Valid values for DMA Read mode include:
  *     - \ref SPIM_CTL0_CMDCODE_READ_DATA
  *     - \ref SPIM_CTL0_CMDCODE_FAST_READ
  *     - \ref SPIM_CTL0_CMDCODE_FAST_READ_DUAL_OUT
  *     - \ref SPIM_CTL0_CMDCODE_FAST_READ_QUAD_IO
  * @param[in]  is4ByteAddr 4-byte address or not.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_ENABLE_DMA_MODE(spim, isWrite, u32CmdCode, is4ByteAddr) \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_CMDCODE_Msk)) | (u32CmdCode);  \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_B4ADDREN_Msk)) | ((is4ByteAddr) << SPIM_CTL0_B4ADDREN_Pos);    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_OPMODE_Msk)) | ((isWrite) ? SPIM_CTL0_OPMODE_DMAWRITE : SPIM_CTL0_OPMODE_DMAREAD);    \
    } while (0)

/**
  * @brief                  Enable Direct Memory Mapping (DMM) mode.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32ReadCmdCode  Read command code. Valid values include:
  *                         - \ref SPIM_CTL0_CMDCODE_READ_DATA
  *                         - \ref SPIM_CTL0_CMDCODE_FAST_READ
  *                         - \ref SPIM_CTL0_CMDCODE_FAST_READ_DUAL_OUT
  *                         - \ref SPIM_CTL0_CMDCODE_FAST_READ_QUAD_IO
  * @param[in]  is4ByteAddr 4-byte address or not.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_ENABLE_DMM_MODE(spim, u32ReadCmdCode, is4ByteAddr) \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_CMDCODE_Msk)) | (u32ReadCmdCode);  \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_B4ADDREN_Msk)) | ((is4ByteAddr) << SPIM_CTL0_B4ADDREN_Pos);    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_OPMODE_Msk)) | (SPIM_CTL0_OPMODE_DMM);    \
    } while (0)

/**
  * @brief                      Set the length of suspend interval.
  * @param[in]  spim            Base address of SPIM module.
  * @param[in]  u32SuspCycle    Decides the length of suspend interval which ranges between 0 and 15.
  * @return                     None.
  * \hideinitializer
  */
#define SPIM_SET_SUSPEND_CYCLE(spim, u32SuspCycle) \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_SUSPITV_Msk)) | ((u32SuspCycle) << SPIM_CTL0_SUSPITV_Pos);    \
    } while (0)

/**
  * @brief                      Set the number of successive transmit/receive transactions in one transfer.
  * @param[in]  spim            Base address of SPIM module.
  * @param[in]  u32BurstNum     Decides the transmit/receive number in one transfer which ranges between 1 and 4.
  * @return                     None.
  * \hideinitializer
  */
#define SPIM_SET_BURST_NUM(spim, u32BurstNum) \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_BURSTNUM_Msk)) | (((u32BurstNum) - 1) << SPIM_CTL0_BURSTNUM_Pos);  \
    } while (0)

/**
  * @brief                  Set the data width of a transmit/receive transaction.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32Width    Data width which ranges between 1 and 32.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_SET_DATA_WIDTH(spim, u32Width)   \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_DWIDTH_Msk)) | (((u32Width) - 1) << SPIM_CTL0_DWIDTH_Pos);  \
    } while (0)

/**
  * @brief              Disable cipher.
  * @note               Cipher can only be disabled and cannot be enabled.
  * @param[in]  spim    Base address of SPIM module.
  * @return             None.
  * \hideinitializer
  */
#define SPIM_DISABLE_CIPHER(spim) \
    do {    \
        (spim)->CTL0 = ((spim)->CTL0 & (~SPIM_CTL0_CIPHOFF_Msk)) | ((! (0)) << SPIM_CTL0_CIPHOFF_Pos); \
    } while (0)

/**
  * @brief              Set slave select pin to high state.
  * @param[in]  spim    Base address of SPIM module.
  * @return             None.
  * \hideinitializer
  */
#define SPIM_SET_SS_HIGH(spim) \
    do {    \
        ((spim)->CTL1 = ((spim)->CTL1 & (~SPIM_CTL1_SSACTPOL_Msk)) | ((0) << SPIM_CTL1_SSACTPOL_Pos));   \
        ((spim)->CTL1 = ((spim)->CTL1 & (~SPIM_CTL1_SS_Msk)) | ((! (0)) << SPIM_CTL1_SS_Pos)); \
    } while (0)

/**
  * @brief              Set slave select pin to low state.
  * @param[in]  spim    Base address of SPIM module.
  * @return             None.
  * \hideinitializer
  */
#define SPIM_SET_SS_LOW(spim) \
    do {    \
        ((spim)->CTL1 = ((spim)->CTL1 & (~SPIM_CTL1_SSACTPOL_Msk)) | ((0) << SPIM_CTL1_SSACTPOL_Pos));   \
        ((spim)->CTL1 = ((spim)->CTL1 & (~SPIM_CTL1_SS_Msk)) | ((! (1)) << SPIM_CTL1_SS_Pos)); \
    } while (0)

/**
  * @brief              Check if SPIM module is busy.
  * @param[in]  spim    Base address of SPIM module.
  * @retval 0           Not busy.
  * @retval 1           Busy.
  * \hideinitializer
  */
#define SPIM_IS_BUSY(spim) \
    (!!((spim)->CTL1 & SPIM_CTL1_SPIMEN_Msk))

/**
  * @brief              Trigger SPI transfer.
  * @param[in]  spim    Base address of SPIM module.
  * @return             None.
  * \hideinitializer
  */
#define SPIM_TRIGGER(spim)  \
    do {    \
        (spim)->CTL1 = ((spim)->CTL1 & (~SPIM_CTL1_SPIMEN_Msk)) | SPIM_CTL1_SPIMEN_Msk;   \
    } while (0)

/**
  * @brief                  Write datum to TX0 register.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32TxData   Data which user attempts to transfer through SPI bus.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_WRITE_TX0(spim, u32TxData)   \
    do {    \
        (spim)->TX0 = (u32TxData);  \
    } while (0)

/**
  * @brief                  Write datum to TX1 register.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32TxData   Data which user attempts to transfer through SPI bus.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_WRITE_TX1(spim, u32TxData)   \
    do {    \
        (spim)->TX1 = (u32TxData);  \
    } while (0)

/**
  * @brief                  Write datum to TX2 register.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32TxData   Data which user attempts to transfer through SPI bus.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_WRITE_TX2(spim, u32TxData)   \
    do {    \
        (spim)->TX2 = (u32TxData);  \
    } while (0)

/**
  * @brief                  Write datum to TX3 register.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32TxData   Data which user attempts to transfer through SPI bus.
  * @return                 None.
  * \hideinitializer
  */
#define SPIM_WRITE_TX3(spim, u32TxData)   \
    do {    \
        (spim)->TX3 = (u32TxData);  \
    } while (0)

/**
  * @brief                  Get the datum read from RX0 register.
  * @param[in]  spim        Base address of SPIM module.
  * @return                 Datum read from RX0 register.
  * \hideinitializer
  */
#define SPIM_READ_RX0(spim)     (spim)->RX0

/**
  * @brief                  Get the datum read from RX1 register.
  * @param[in]  spim        Base address of SPIM module.
  * @return                 Datum read from RX1 register.
  * \hideinitializer
  */
#define SPIM_READ_RX1(spim)     (spim)->RX1

/**
  * @brief                  Get the datum read from RX2 register.
  * @param[in]  spim        Base address of SPIM module.
  * @return                 Datum read from RX2 register.
  * \hideinitializer
  */
#define SPIM_READ_RX2(spim)     (spim)->RX2

/**
  * @brief                  Get the datum read from RX3 register.
  * @param[in]  spim        Base address of SPIM module.
  * @return                 Datum read from RX3 register.
  * \hideinitializer
  */
#define SPIM_READ_RX3(spim)     (spim)->RX3

uint32_t SPIM_Open(SPIM_T *spim, uint32_t u32SPIMode, uint32_t u32BusClock);
void SPIM_Close(SPIM_T *spim);
uint32_t SPIM_SetBusClock(SPIM_T *spim, uint32_t u32BusClock);
uint32_t SPIM_GetBusClock(SPIM_T *spim);
void SPIM_EnableInt(SPIM_T *spim, uint32_t u32Mask);
void SPIM_DisableInt(SPIM_T *spim, uint32_t u32Mask);
uint32_t SPIM_GetIntFlag(SPIM_T *spim, uint32_t u32Mask);
void SPIM_ClearIntFlag(SPIM_T *spim, uint32_t u32Mask);
void SPIM_SetIF(SPIM_T *spim, uint32_t u32IFSel);

void SPIM_DMAWritePage(SPIM_T *spim, uint32_t u32FlashAddr, uint32_t u32Len, uint8_t *pu8TxBuf);
void SPIM_DMAReadFlash(SPIM_T *spim, uint32_t u32FlashAddr, uint32_t u32Len, uint8_t *pu8RxBuf);

/*@}*/ /* end of group NUC505_SPIM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_SPIM_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__SPIM_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
