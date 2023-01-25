/******************************************************************************
 * @file     spi.h
 * @version  V1.0
 * $Revision: 11 $
 * $Date: 15/12/01 8:41p $
 * @brief    NUC505 series SPI driver header file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __SPI_H__
#define __SPI_H__

/*---------------------------------------------------------------------------------------------------------*/
/* Include related headers                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
#include "NUC505Series.h"

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SPI_Driver SPI Driver
  @{
*/

/** @addtogroup NUC505_SPI_EXPORTED_CONSTANTS SPI Exported Constants
  @{
*/

#define SPI_MODE_0        (SPI_CTL_TXNEG_Msk)                             /*!< CLKPOL=0; RXNEG=0; TXNEG=1 */
#define SPI_MODE_1        (SPI_CTL_RXNEG_Msk)                             /*!< CLKPOL=0; RXNEG=1; TXNEG=0 */
#define SPI_MODE_2        (SPI_CTL_CLKPOL_Msk | SPI_CTL_RXNEG_Msk)        /*!< CLKPOL=1; RXNEG=1; TXNEG=0 */
#define SPI_MODE_3        (SPI_CTL_CLKPOL_Msk | SPI_CTL_TXNEG_Msk)        /*!< CLKPOL=1; RXNEG=0; TXNEG=1 */

#define SPI_SLAVE         (SPI_CTL_SLAVE_Msk)                             /*!< Set as slave */
#define SPI_MASTER        (0x0)                                           /*!< Set as master */

#define SPI_SS                (SPI_SSCTL_SS_Msk)                          /*!< Set SS */
#define SPI_SS_ACTIVE_HIGH    (SPI_SSCTL_SSACTPOL_Msk)                    /*!< SS active high */
#define SPI_SS_ACTIVE_LOW     (0x0)                                       /*!< SS active low */

/* SPI Interrupt Mask */
#define SPI_UNIT_INT_MASK                (0x001)                          /*!< Unit transfer interrupt mask */
#define SPI_SSACT_INT_MASK               (0x002)                          /*!< Slave selection signal active interrupt mask */
#define SPI_SSINACT_INT_MASK             (0x004)                          /*!< Slave selection signal inactive interrupt mask */
#define SPI_SLVUR_INT_MASK               (0x008)                          /*!< Slave under run interrupt mask */
#define SPI_SLVBE_INT_MASK               (0x010)                          /*!< Slave bit count error interrupt mask */
#define SPI_SLVTO_INT_MASK               (0x020)                          /*!< Slave time-out interrupt mask */
#define SPI_TXUF_INT_MASK                (0x040)                          /*!< Slave TX underflow interrupt mask */
#define SPI_FIFO_TXTH_INT_MASK           (0x080)                          /*!< FIFO TX threshold interrupt mask */
#define SPI_FIFO_RXTH_INT_MASK           (0x100)                          /*!< FIFO RX threshold interrupt mask */
#define SPI_FIFO_RXOV_INT_MASK           (0x200)                          /*!< FIFO RX overrun interrupt mask */
#define SPI_FIFO_RXTO_INT_MASK           (0x400)                          /*!< FIFO RX time-out interrupt mask */

/* SPI Status Mask */
#define SPI_BUSY_MASK                    (0x01)                           /*!< Busy status mask */
#define SPI_RX_EMPTY_MASK                (0x02)                           /*!< RX empty status mask */
#define SPI_RX_FULL_MASK                 (0x04)                           /*!< RX full status mask */
#define SPI_TX_EMPTY_MASK                (0x08)                           /*!< TX empty status mask */
#define SPI_TX_FULL_MASK                 (0x10)                           /*!< TX full status mask */
#define SPI_TXRX_RESET_MASK              (0x20)                           /*!< TX or RX reset status mask */
#define SPI_SPIEN_STS_MASK               (0x40)                           /*!< SPIEN status mask */
#define SPI_SSLINE_STS_MASK              (0x80)                           /*!< SPIn_SS line status mask */


/*@}*/ /* end of group NUC505_SPI_EXPORTED_CONSTANTS */


/** @addtogroup NUC505_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief      Clear the unit transfer interrupt flag.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Write 1 to UNITIF bit of SPI_STATUS register to clear the unit transfer interrupt flag.
  */
#define SPI_CLR_UNIT_TRANS_INT_FLAG(spi)   ((spi)->STATUS |= SPI_STATUS_UNITIF_Msk)

/**
  * @brief      Disable Slave 3-wire mode.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Clear SLV3WIRE bit of SPI_SSCTL register to disable Slave 3-wire mode.
  */
#define SPI_DISABLE_3WIRE_MODE(spi)   ((spi)->SSCTL &= ~SPI_SSCTL_SLV3WIRE_Msk)

/**
  * @brief      Enable Slave 3-wire mode.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Set SLV3WIRE bit of SPI_SSCTL register to enable Slave 3-wire mode.
  */
#define SPI_ENABLE_3WIRE_MODE(spi)   ((spi)->SSCTL |= SPI_SSCTL_SLV3WIRE_Msk)

/**
  * @brief      Get the count of available data in Rx FIFO.
  * @param[in]  spi The base address of SPI module.
  * @return     The count of available data in Rx FIFO.
  * @details    Read RXCNT (SPI_STATUS[27:24]) to get the count of available data in Rx FIFO.
  */
#define SPI_GET_RX_FIFO_COUNT(spi)   (((spi)->STATUS & SPI_STATUS_RXCNT_Msk) >> SPI_STATUS_RXCNT_Pos)

/**
  * @brief      Get the Rx FIFO empty flag.
  * @param[in]  spi The base address of SPI module.
  * @retval     0 Rx FIFO is not empty.
  * @retval     1 Rx FIFO is empty.
  * @details    Read RXEMPTY bit of SPI_STATUS register to get the Rx FIFO empty flag.
  */
#define SPI_GET_RX_FIFO_EMPTY_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_RXEMPTY_Msk)>>SPI_STATUS_RXEMPTY_Pos)

/**
  * @brief      Get the Tx FIFO empty flag.
  * @param[in]  spi The base address of SPI module.
  * @retval     0 Tx FIFO is not empty.
  * @retval     1 Tx FIFO is empty.
  * @details    Read TXEMPTY bit of SPI_STATUS register to get the Tx FIFO empty flag.
  */
#define SPI_GET_TX_FIFO_EMPTY_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_TXEMPTY_Msk)>>SPI_STATUS_TXEMPTY_Pos)

/**
  * @brief      Get the Tx FIFO full flag.
  * @param[in]  spi The base address of SPI module.
  * @retval     0 Tx FIFO is not full.
  * @retval     1 Tx FIFO is full.
  * @details    Read TXFULL bit of SPI_STATUS register to get the Tx FIFO full flag.
  */
#define SPI_GET_TX_FIFO_FULL_FLAG(spi)   (((spi)->STATUS & SPI_STATUS_TXFULL_Msk)>>SPI_STATUS_TXFULL_Pos)

/**
  * @brief      Get the datum read from Rx register.
  * @param[in]  spi The base address of SPI module.
  * @return     Data in Rx register.
  * @details    Read SPI_RX register to get the received datum.
  */
#define SPI_READ_RX(spi)   ((spi)->RX)

/**
  * @brief      Write datum to Tx register.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32TxData The datum which user attempt to transfer through SPI bus.
  * @return     None.
  * @details    Write u32TxData to SPI_TX register.
  */
#define SPI_WRITE_TX(spi, u32TxData)   ((spi)->TX = (u32TxData))

/**
  * @brief      Set SPIn_SS pin to high state.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set SPIn_SS pin to high state.
  */
#define SPI_SET_SS_HIGH(spi)   ((spi)->SSCTL = ((spi)->SSCTL & (~SPI_SSCTL_AUTOSS_Msk)) | (SPI_SSCTL_SSACTPOL_Msk | SPI_SSCTL_SS_Msk))

/**
  * @brief      Set SPIn_SS pin to low state.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Disable automatic slave selection function and set SPIn_SS pin to low state.
  */
#define SPI_SET_SS_LOW(spi)   ((spi)->SSCTL = ((spi)->SSCTL & (~(SPI_SSCTL_AUTOSS_Msk | SPI_SSCTL_SSACTPOL_Msk))) | SPI_SSCTL_SS_Msk)

/**
  * @brief      Enable Byte Reorder function.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Enable byte reorder function. The suspend interval depends on the setting of SUSPITV (SPI_CTL[7:4]).
  */
#define SPI_ENABLE_BYTE_REORDER(spi)   ((spi)->CTL |=  SPI_CTL_REORDER_Msk)

/**
  * @brief      Disable Byte Reorder function.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Clear REORDER bit field of SPI_CTL register to disable byte reorder function.
  */
#define SPI_DISABLE_BYTE_REORDER(spi)   ((spi)->CTL &= ~SPI_CTL_REORDER_Msk)

/**
  * @brief      Set the length of suspend interval.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32SuspCycle Decides the length of suspend interval.
  * @return     None.
  * @details    Set the length of suspend interval according to u32SuspCycle.
  *             The length of suspend interval is ((u32SuspCycle + 0.5) * the length of one SPI bus clock cycle).
  */
#define SPI_SET_SUSPEND_CYCLE(spi, u32SuspCycle)   ((spi)->CTL = ((spi)->CTL & ~SPI_CTL_SUSPITV_Msk) | ((u32SuspCycle) << SPI_CTL_SUSPITV_Pos))

/**
  * @brief      Set the SPI transfer sequence with LSB first.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Set LSB bit of SPI_CTL register to set the SPI transfer sequence with LSB first.
  */
#define SPI_SET_LSB_FIRST(spi)   ((spi)->CTL |= SPI_CTL_LSB_Msk)

/**
  * @brief      Set the SPI transfer sequence with MSB first.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Clear LSB bit of SPI_CTL register to set the SPI transfer sequence with MSB first.
  */
#define SPI_SET_MSB_FIRST(spi)   ((spi)->CTL &= ~SPI_CTL_LSB_Msk)

/**
  * @brief      Set the data width of a SPI transaction.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32Width The bit width of one transaction.
  * @return     None.
  * @details    The data width can be 8 ~ 32 bits.
  */
#define SPI_SET_DATA_WIDTH(spi, u32Width)   ((spi)->CTL = ((spi)->CTL & ~SPI_CTL_DWIDTH_Msk) | (((u32Width)&0x1F) << SPI_CTL_DWIDTH_Pos))

/**
  * @brief      Get the SPI busy state.
  * @param[in]  spi The base address of SPI module.
  * @retval     0 SPI controller is not busy.
  * @retval     1 SPI controller is busy.
  * @details    This macro will return the busy state of SPI controller.
  */
#define SPI_IS_BUSY(spi)   ( ((spi)->STATUS & SPI_STATUS_BUSY_Msk)>>SPI_STATUS_BUSY_Pos )

/**
  * @brief      Enable SPI controller.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Set SPIEN (SPI_CTL[0]) to enable SPI controller.
  */
#define SPI_ENABLE(spi)   ((spi)->CTL |= SPI_CTL_SPIEN_Msk)

/**
  * @brief      Disable SPI controller.
  * @param[in]  spi The base address of SPI module.
  * @return     None.
  * @details    Clear SPIEN (SPI_CTL[0]) to disable SPI controller.
  */
#define SPI_DISABLE(spi)   ((spi)->CTL &= ~SPI_CTL_SPIEN_Msk)



/* Function prototype declaration */
uint32_t SPI_Open(SPI_T *spi, uint32_t u32MasterSlave, uint32_t u32SPIMode, uint32_t u32DataWidth, uint32_t u32BusClock);
void SPI_Close(SPI_T *spi);
void SPI_ClearRxFIFO(SPI_T *spi);
void SPI_ClearTxFIFO(SPI_T *spi);
void SPI_DisableAutoSS(SPI_T *spi);
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel);
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock);
void SPI_SetFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold);
uint32_t SPI_GetBusClock(SPI_T *spi);
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask);
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask);
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask);
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask);


/*@}*/ /* end of group NUC505_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_SPI_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__SPI_H__

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
