/******************************************************************************
 * @file     i2s.h
 * @version  V1.1
 * $Revision: 12 $
 * $Date: 15/12/01 3:41p $
 * @brief    NUC505 series I2S driver header file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __I2S_H__
#define __I2S_H__

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

/** @addtogroup NUC505_I2S_Driver I2S Driver
  @{
*/

/** @addtogroup NUC505_I2S_EXPORTED_CONSTANTS I2S Exported Constants
  @{
*/

/* I2S Data Width */
#define I2S_DATABIT_8           (0 << I2S_CTL_WDWIDTH_Pos)      /*!< I2S data width is 8-bit */
#define I2S_DATABIT_16          (1 << I2S_CTL_WDWIDTH_Pos)      /*!< I2S data width is 16-bit */
#define I2S_DATABIT_24          (2 << I2S_CTL_WDWIDTH_Pos)      /*!< I2S data width is 24-bit */
#define I2S_DATABIT_32          (3 << I2S_CTL_WDWIDTH_Pos)      /*!< I2S data width is 32-bit */

/* I2S Audio Format */
#define I2S_MONO                I2S_CTL_MONO_Msk                /*!< Monaural channel */
#define I2S_STEREO              0                                  /*!< Stereo channel */

/* I2S Data Format */
#define I2S_FORMAT_MSB          I2S_CTL_FORMAT_Msk                 /*!< MSB data format */
#define I2S_FORMAT_I2S          0                                  /*!< I2S data format */
#define I2S_FORMAT_PCMB         I2S_CTL_FORMAT_Msk                 /*!< PCMB data format */
#define I2S_FORMAT_PCMA         0                                  /*!< PCMA data format */

/* I2S Interface */
#define I2S_PCM                 I2S_CTL_PCMEN_Msk                  /*!< PCM interface is selected */
#define I2S_I2S                 0                                  /*!< I2S interface is selected */

/* I2S Operation mode */
#define I2S_MODE_SLAVE          I2S_CTL_SLAVE_Msk               /*!< As slave mode */
#define I2S_MODE_MASTER         0                                  /*!< As master mode */

/* I2S TX FIFO Threshold */
#define I2S_FIFO_TX_LEVEL_WORD_0    0                              /*!< TX threshold is 0 word */
#define I2S_FIFO_TX_LEVEL_WORD_1    (1 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 1 word */
#define I2S_FIFO_TX_LEVEL_WORD_2    (2 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 2 words */
#define I2S_FIFO_TX_LEVEL_WORD_3    (3 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 3 words */
#define I2S_FIFO_TX_LEVEL_WORD_4    (4 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 4 words */
#define I2S_FIFO_TX_LEVEL_WORD_5    (5 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 5 words */
#define I2S_FIFO_TX_LEVEL_WORD_6    (6 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 6 words */
#define I2S_FIFO_TX_LEVEL_WORD_7    (7 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 7 words */
#define I2S_FIFO_TX_LEVEL_WORD_8    (8 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 8 words */
#define I2S_FIFO_TX_LEVEL_WORD_9    (9 << I2S_CTL_TXTH_Pos)    /*!< TX threshold is 9 words */
#define I2S_FIFO_TX_LEVEL_WORD_10   (10<< I2S_CTL_TXTH_Pos)    /*!< TX threshold is 10 words */
#define I2S_FIFO_TX_LEVEL_WORD_11   (11<< I2S_CTL_TXTH_Pos)    /*!< TX threshold is 11 words */
#define I2S_FIFO_TX_LEVEL_WORD_12   (12<< I2S_CTL_TXTH_Pos)    /*!< TX threshold is 12 words */
#define I2S_FIFO_TX_LEVEL_WORD_13   (13<< I2S_CTL_TXTH_Pos)    /*!< TX threshold is 13 words */
#define I2S_FIFO_TX_LEVEL_WORD_14   (14<< I2S_CTL_TXTH_Pos)    /*!< TX threshold is 14 words */
#define I2S_FIFO_TX_LEVEL_WORD_15   (15<< I2S_CTL_TXTH_Pos)    /*!< TX threshold is 15 words */

/* I2S RX FIFO Threshold */
#define I2S_FIFO_RX_LEVEL_WORD_1    0                              /*!< RX threshold is 1 word */
#define I2S_FIFO_RX_LEVEL_WORD_2    (1 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 2 words */
#define I2S_FIFO_RX_LEVEL_WORD_3    (2 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 3 words */
#define I2S_FIFO_RX_LEVEL_WORD_4    (3 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 4 words */
#define I2S_FIFO_RX_LEVEL_WORD_5    (4 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 5 words */
#define I2S_FIFO_RX_LEVEL_WORD_6    (5 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 6 words */
#define I2S_FIFO_RX_LEVEL_WORD_7    (6 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 7 words */
#define I2S_FIFO_RX_LEVEL_WORD_8    (7 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 8 words */
#define I2S_FIFO_RX_LEVEL_WORD_9    (8 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 9 words */
#define I2S_FIFO_RX_LEVEL_WORD_10   (9 << I2S_CTL_RXTH_Pos)    /*!< RX threshold is 10 words */
#define I2S_FIFO_RX_LEVEL_WORD_11   (10<< I2S_CTL_RXTH_Pos)    /*!< RX threshold is 11 words */
#define I2S_FIFO_RX_LEVEL_WORD_12   (11<< I2S_CTL_RXTH_Pos)    /*!< RX threshold is 12 words */
#define I2S_FIFO_RX_LEVEL_WORD_13   (12<< I2S_CTL_RXTH_Pos)    /*!< RX threshold is 13 words */
#define I2S_FIFO_RX_LEVEL_WORD_14   (13<< I2S_CTL_RXTH_Pos)    /*!< RX threshold is 14 words */
#define I2S_FIFO_RX_LEVEL_WORD_15   (14<< I2S_CTL_RXTH_Pos)    /*!< RX threshold is 15 words */
#define I2S_FIFO_RX_LEVEL_WORD_16   (15<< I2S_CTL_RXTH_Pos)    /*!< RX threshold is 16 words */

#define I2S_FIFO_RXUD_INT_MASK         (0x1ul << I2S_IEN_RXUDIEN_Pos)                    /*!< I2S IEN: RXUDIEN Mask                  */
#define I2S_FIFO_RXOV_INT_MASK         (0x1ul << I2S_IEN_RXOVIEN_Pos)                    /*!< I2S IEN: RXOVIEN Mask                  */
#define I2S_FIFO_RXTH_INT_MASK         (0x1ul << I2S_IEN_RXTHIEN_Pos)                    /*!< I2S IEN: RXTHIEN Mask                  */
#define I2S_RDMAE_INT_MASK             (0x1ul << I2S_IEN_RDMAEIEN_Pos)                   /*!< I2S IEN: RDMAEIEN Mask                 */
#define I2S_RDMAT_INT_MASK             (0x1ul << I2S_IEN_RDMATIEN_Pos)                   /*!< I2S IEN: RDMATIEN Mask                 */
#define I2S_TDMAE_INT_MASK             (0x1ul << I2S_IEN_TDMAEIEN_Pos)                   /*!< I2S IEN: TDMAEIEN Mask                 */
#define I2S_TDMAT_INT_MASK             (0x1ul << I2S_IEN_TDMATIEN_Pos)                   /*!< I2S IEN: TDMATIEN Mask                 */
#define I2S_FIFO_TXUD_INT_MASK         (0x1ul << I2S_IEN_TXUDIEN_Pos)                    /*!< I2S IEN: TXUDIEN Mask                  */
#define I2S_FIFO_TXOV_INT_MASK         (0x1ul << I2S_IEN_TXOVIEN_Pos)                    /*!< I2S IEN: TXOVIEN Mask                  */
#define I2S_FIFO_TXTH_INT_MASK         (0x1ul << I2S_IEN_TXTHIEN_Pos)                    /*!< I2S IEN: TXTHIEN Mask                  */
#define I2S_RZC_INT_MASK               (0x1ul << I2S_IEN_RZCIEN_Pos)                     /*!< I2S IEN: RZCIEN Mask                   */
#define I2S_LZC_INT_MASK               (0x1ul << I2S_IEN_LZCIEN_Pos)                     /*!< I2S IEN: LZCIEN Mask                   */

/* I2S Record Channel */
#define I2S_MONO_RIGHT          0                                  /*!< Record mono right channel */
#define I2S_MONO_LEFT           I2S_CTL_RXLCH_Msk               /*!< Record mono left channel */

/* I2S Channel */
#define I2S_RIGHT               0                                  /*!< Select right channel */
#define I2S_LEFT                1                                  /*!< Select left channel */

/* I2S Internal CODEC Select */
#define I2S_DISABLE_INTERNAL_CODEC      0           /*!< CODECRST=0, CODECSEL=1 */
#define I2S_ENABLE_INTERNAL_CODEC       1           /*!< CODECRST=1, CODECSEL=0 */

/*@}*/ /* end of group NUC505_I2S_EXPORTED_CONSTANTS */


/** @addtogroup NUC505_I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/* inline functions                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/**
  * @brief  Enable zero cross detection function.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32ChMask The mask for left or right channel. Valid values are:
  *                    - \ref I2S_RIGHT
  *                    - \ref I2S_LEFT
  * @return None
  * @details This function will set RZCEN or LZCEN bit of I2S_CTL register to enable zero cross detection function.
  */
static __INLINE void I2S_ENABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == I2S_RIGHT)
        i2s->CTL |= I2S_CTL_RZCEN_Msk;
    else
        i2s->CTL |= I2S_CTL_LZCEN_Msk;
}

/**
  * @brief  Disable zero cross detection function.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32ChMask The mask for left or right channel. Valid values are:
  *                    - \ref I2S_RIGHT
  *                    - \ref I2S_LEFT
  * @return None
  * @details This function will clear RZCEN or LZCEN bit of I2S_CTL register to disable zero cross detection function.
  */
static __INLINE void I2S_DISABLE_TX_ZCD(I2S_T *i2s, uint32_t u32ChMask)
{
    if(u32ChMask == I2S_RIGHT)
        i2s->CTL &= ~I2S_CTL_RZCEN_Msk;
    else
        i2s->CTL &= ~I2S_CTL_LZCEN_Msk;
}

/**
  * @brief  Enable I2S Tx DMA function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will set TXDMAEN bit of I2S_CTL register to transmit data with DMA.
  */
#define I2S_ENABLE_TXDMA(i2s)  ( (i2s)->CTL |= I2S_CTL_TXDMAEN_Msk )

/**
  * @brief  Disable I2S Tx DMA function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear TXDMAEN bit of I2S_CTL register to disable Tx DMA function.
  */
#define I2S_DISABLE_TXDMA(i2s) ( (i2s)->CTL &= ~I2S_CTL_TXDMAEN_Msk )

/**
  * @brief  Enable I2S Rx DMA function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will set RXDMAEN bit of I2S_CTL register to receive data with DMA.
  */
#define I2S_ENABLE_RXDMA(i2s) ( (i2s)->CTL |= I2S_CTL_RXDMAEN_Msk )

/**
  * @brief  Disable I2S Rx DMA function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear RXDMAEN bit of I2S_CTL register to disable Rx DMA function.
  */
#define I2S_DISABLE_RXDMA(i2s) ( (i2s)->CTL &= ~I2S_CTL_RXDMAEN_Msk )

/**
  * @brief  Enable I2S Tx function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will set TXEN bit of I2S_CTL register to enable I2S Tx function.
  */
#define I2S_ENABLE_TX(i2s) ( (i2s)->CTL |= I2S_CTL_TXEN_Msk )

/**
  * @brief  Disable I2S Tx function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear TXEN bit of I2S_CTL register to disable I2S Tx function.
  */
#define I2S_DISABLE_TX(i2s) ( (i2s)->CTL &= ~I2S_CTL_TXEN_Msk )

/**
  * @brief  Enable I2S Rx function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will set RXEN bit of I2S_CTL register to enable I2S Rx function.
  */
#define I2S_ENABLE_RX(i2s) ( (i2s)->CTL |= I2S_CTL_RXEN_Msk )

/**
  * @brief  Disable I2S Rx function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear RXEN bit of I2S_CTL register to disable I2S Rx function.
  */
#define I2S_DISABLE_RX(i2s) ( (i2s)->CTL &= ~I2S_CTL_RXEN_Msk )

/**
  * @brief  Enable Tx Mute function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will set MUTE bit of I2S_CTL register to enable I2S Tx mute function.
  */
#define I2S_ENABLE_TX_MUTE(i2s)  ( (i2s)->CTL |= I2S_CTL_MUTE_Msk )

/**
  * @brief  Disable Tx Mute function.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear MUTE bit of I2S_CTL register to disable I2S Tx mute function.
  */
#define I2S_DISABLE_TX_MUTE(i2s) ( (i2s)->CTL &= ~I2S_CTL_MUTE_Msk )

/**
  * @brief  Clear Tx FIFO.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear Tx FIFO. The internal Tx FIFO pointer will be reset to FIFO start point.
  */
#define I2S_CLR_TX_FIFO(i2s) ( (i2s)->CTL |= I2S_CTL_TXCLR_Msk )

/**
  * @brief  Clear Rx FIFO.
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details This macro will clear Rx FIFO. The internal Rx FIFO pointer will be reset to FIFO start point.
  */
#define I2S_CLR_RX_FIFO(i2s) ( (i2s)->CTL |= I2S_CTL_RXCLR_Msk )

/**
  * @brief  This function sets the recording source channel when mono mode is used.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Ch left or right channel. Valid values are:
  *                - \ref I2S_MONO_LEFT
  *                - \ref I2S_MONO_RIGHT
  * @return None
  * @details This function selects the recording source channel of monaural mode.
  */
static __INLINE void I2S_SET_MONO_RX_CHANNEL(I2S_T *i2s, uint32_t u32Ch)
{
    u32Ch == I2S_MONO_LEFT ?
    (i2s->CTL |= I2S_CTL_RXLCH_Msk) :
    (i2s->CTL &= ~I2S_CTL_RXLCH_Msk);
}

/**
  * @brief  Write data to I2S Tx FIFO.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Data The value written to Tx FIFO.
  * @return None
  * @details This macro will write a value to Tx FIFO.
  */
#define I2S_WRITE_TX_FIFO(i2s, u32Data)  ( (i2s)->TX = (u32Data) )

/**
  * @brief  Read Rx FIFO.
  * @param[in] i2s The base address of I2S module.
  * @return The value read from Rx FIFO.
  * @details This function will return a value read from Rx FIFO.
  */
#define I2S_READ_RX_FIFO(i2s) ( (i2s)->RX )

/**
  * @brief  Get the interrupt flag.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Mask The mask value for all interrupt flags.
  * @return The interrupt flags specified by the u32mask parameter.
  * @details This macro will return the combination interrupt flags of I2S_STATUS register. The flags are specified by the u32mask parameter.
  */
#define I2S_GET_INT_FLAG(i2s, u32Mask) ( (i2s)->STATUS & (u32Mask) )

/**
  * @brief  Clear the interrupt flag.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Mask The mask value for all interrupt flags.
  * @return None
  * @details This macro will clear the interrupt flags specified by the u32mask parameter.
  * @note Except TXBUSY, TXEMPTY, TXFULL, TXTHIF, RXEMPTY, RXFULL, RXTHIF, RIGHT, TXIF, RXIF, and I2SIF interrupt flags, the other interrupt flags LZCIF, RZCIF, TXOVIF, TXUDIF, RXOVIF, RXUDIF, TDMATIF, TDMAEIF, RDMATIF, and RDMAEIF can be cleared by writing 1 to itself.
  */
#define I2S_CLR_INT_FLAG(i2s, u32Mask) ( (i2s)->STATUS = (u32Mask) )

/**
  * @brief  Get transmit FIFO level
  * @param[in] i2s The base address of I2S module.
  * @return Tx FIFO level
  * @details This macro will return the number of available words in Tx FIFO.
  */
#define I2S_GET_TX_FIFO_LEVEL(i2s) ( ((i2s)->STATUS & I2S_STATUS_TXCNT_Msk) >> I2S_STATUS_TXCNT_Pos  )

/**
  * @brief  Get receive FIFO level
  * @param[in] i2s The base address of I2S module.
  * @return Rx FIFO level
  * @details This macro will return the number of available words in Rx FIFO.
  */
#define I2S_GET_RX_FIFO_LEVEL(i2s) ( ((i2s)->STATUS & I2S_STATUS_RXCNT_Msk) >> I2S_STATUS_RXCNT_Pos )

/**
  * @brief  Set transmit FIFO threshold level.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Word The value set to Tx threshold level. Valid values are:
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_0
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_1
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_2
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_3
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_4
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_5
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_6
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_7
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_8
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_9
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_10
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_11
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_12
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_13
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_14
  *                - \ref I2S_FIFO_TX_LEVEL_WORD_15
  * @return None
  * @details This macro will write a value to TXTH.
  */
static __INLINE void I2S_SET_TX_TH_LEVEL(I2S_T *i2s, uint32_t u32Word)
{
    i2s->CTL &= ~I2S_CTL_TXTH_Msk;
    i2s->CTL |= u32Word;
}

/**
  * @brief  Set receive FIFO threshold level.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Word The value set to Rx threshold level. Valid values are:
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_1
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_2
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_3
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_4
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_5
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_6
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_7
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_8
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_9
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_10
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_11
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_12
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_13
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_14
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_15
  *                - \ref I2S_FIFO_RX_LEVEL_WORD_16
  * @return None
  * @details This macro will write a value to RXTH.
  */
static __INLINE void I2S_SET_RX_TH_LEVEL(I2S_T *i2s, uint32_t u32Word)
{
    i2s->CTL &= ~I2S_CTL_RXTH_Msk;
    i2s->CTL |= u32Word;
}

/**
  * @brief  Set start address to I2S Tx DMA.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The value set to TXSTADDR.
  * @return None
  * @details This macro will write a value to TXSTADDR.
  */
#define I2S_SET_TXDMA_STADDR(i2s, u32Address)  ( (i2s)->TXSTADDR = (u32Address) )

/**
  * @brief  Set threshold address to I2S Tx DMA.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The value set to TXTHADDR.
  * @return None
  * @details This macro will write a value to TXTHADDR.
  */
#define I2S_SET_TXDMA_THADDR(i2s, u32Address)  ( (i2s)->TXTHADDR = (u32Address) )

/**
  * @brief  Set end address to I2S Tx DMA.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The value set to TXEADDR.
  * @return None
  * @details This macro will write a value to TXEADDR.
  */
#define I2S_SET_TXDMA_EADDR(i2s, u32Address)  ( (i2s)->TXEADDR = (u32Address) )

/**
  * @brief  Get current address to I2S Tx DMA.
  * @param[in] i2s The base address of I2S module.
  * @return Tx DMA current address
  * @details This macro will return the address of TXCADDR.
  */
#define I2S_GET_TXDMA_CADDR(i2s) ( (i2s)->TXCADDR )

/**
  * @brief  Set start address to I2S Rx DMA.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The value set to RXSTADDR.
  * @return None
  * @details This macro will write a value to RXSTADDR.
  */
#define I2S_SET_RXDMA_STADDR(i2s, u32Address)  ( (i2s)->RXSTADDR = (u32Address) )

/**
  * @brief  Set threshold address to I2S Rx DMA.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The value set to RXTHADDR.
  * @return None
  * @details This macro will write a value to RXTHADDR.
  */
#define I2S_SET_RXDMA_THADDR(i2s, u32Address)  ( (i2s)->RXTHADDR = (u32Address) )

/**
  * @brief  Set end address to I2S Rx DMA.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The value set to RXEADDR.
  * @return None
  * @details This macro will write a value to RXEADDR.
  */
#define I2S_SET_RXDMA_EADDR(i2s, u32Address)  ( (i2s)->RXEADDR = (u32Address) )

/**
  * @brief  Get current address to I2S Rx DMA.
  * @param[in] i2s The base address of I2S module.
  * @return Rx DMA current address
  * @details This macro will return the address of RXCADDR.
  */
#define I2S_GET_RXDMA_CADDR(i2s) ( (i2s)->RXCADDR )

/**
  * @brief  This function sets the internal CODEC register.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The internal CODEC register address.
  * @param[in] u32Value The internal CODEC register value.
  * @return None
  * @details This function sets internal CODEC register, through internal I2C protocol.
  *
  * CODEC ADC Control Register (CODEC_ADCCTL)
  * ===================================================================================================
  * (Address: 00H; Default: 10H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7]     |ADCEN         |0         |CODEC ADC Enable Control
  * |        |              |          |0 = Digital ADC function Disabled.
  * |        |              |          |1 = Digital ADC function Enabled.
  * |[6]     |HPFEN         |0         |High Pass Filter Enable Control
  * |        |              |          |0 = High Pass Filter Disabled.
  * |        |              |          |1 = High Pass Filter Enabled.
  * |[5]     |Reserved      |0         |Reserved.
  * |[4]     |STEREO        |1         |CODEC ADC Output Channel Mode
  * |        |              |          |0 = Left mono mode (Right channel outputs the same signal as left channel).
  * |        |              |          |1 = Stereo mode.
  * |[3:0]   |Reserved      |0000      |Reserved.
  *
  * CODEC DAC Control Register (CODEC_DACCTL)
  * ===================================================================================================
  * (Address: 01H; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7]     |DACEN         |0         |CODEC DAC Enable Control
  * |        |              |          |0 = Digital DAC function Disabled.
  * |        |              |          |1 = Digital DAC function Enabled.
  * |[6]     |Reserved      |0         |Reserved.
  * |[5:4]   |DAC_MODE      |00        |CODEC DAC Output Stereo Or Mono Signal Control
  * |        |              |          |00 = Output stereo signal mode.
  * |        |              |          |01 = Output left mono signal mode. (Right channel signal is the same as left channel).
  * |        |              |          |10 = Output right mono signal mode. (Left channel signal is the same as right channel).
  * |        |              |          |11 = Output (left signal + right signal)/2 mono mode.
  * |[3]     |DAC_DMUTEL    |0         |Left Channel Digital Mute Enable Control
  * |        |              |          |0 = Channel Digital Output Mute Disabled.
  * |        |              |          |1 = Channel Digital Output Mute Enabled.
  * |[2]     |DAC_DMUTER    |0         |Right Channel Digital Mute Enable Control
  * |        |              |          |0 = Channel Digital Output Mute Disabled.
  * |        |              |          |1 = Channel Digital Output Mute Enabled.
  * |[1:0]   |Reserved      |00        |Reserved.
  *
  * CODEC Control Register (CODEC_CTL)
  * ===================================================================================================
  * (Address: 02H; Default: 80H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7]     |SRESET        |1         |CODEC Soft Reset Control Bit
  * |        |              |          |0 = Reset AD/DA filter and I2S parts, except I2C block.
  * |        |              |          |1 = Normal operation.
  * |[6]     |SLAVE         |0         |I2S Interface Mode Selection
  * |        |              |          |0 = I2S interface is in Master mode.
  * |        |              |          |1 = I2S interface is in Slave mode.
  * |[5:0]   |Reserved      |000000    |Reserved
  *
  * CODEC DAC Left Channel Volume Control Register (CODEC_DACLVCTL)
  * ===================================================================================================
  * (Address: 03H; Default: 80H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:0]   |DACVOLL       |1000_0000 |DAC Left Channel Volume Control Register
  * |        |              |          |The value can be programmed from 0x00 to 0x80, and the step is 1/128 * (Voltage Full Scale).
  * |        |              |          |Note: Default setting is 0x80 (Max Volume).
  *
  * CODEC DAC Right Channel Volume Control Register (CODEC_DACRVCTL)
  * ===================================================================================================
  * (Address: 04H; Default: 80H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:0]   |DACVOLR       |1000_0000 |DAC Right Channel Volume Control Register
  * |        |              |          |The value can be programmed from 0x00 to 0x80, and the step is 1/128 * (Voltage Full Scale).
  * |        |              |          |Note: Default setting is 0x80 (Max Volume).
  *
  * CODEC DAC Left Channel Analog Volume Control Register (CODEC_DACLVACTL)
  * ===================================================================================================
  * (Address: 08H; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:5]   |Reserved      |000       |Reserved.
  * |[4:0]   |AVOLL         |0_0000    |DAC Left Channel Analog Volume Control Register
  * |        |              |          |The value can be programmed from 0x00 to 0x1F, and the step is -2dB.
  * |        |              |          |0x00 = 0 dB.
  * |        |              |          |0x01 = -2 dB.
  * |        |              |          |0x02 = -4 dB.
  * |        |              |          |...
  * |        |              |          |0x1E = -60 dB.
  * |        |              |          |0x1F = Analog Mute.
  *
  * CODEC DAC Right Channel Analog Volume Control Register (CODEC_DACRVACTL)
  * ===================================================================================================
  * (Address: 09H; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:5]   |Reserved      |000       |Reserved.
  * |[4:0]   |AVOLR         |0_0000    |DAC Right Channel Analog Volume Control Register
  * |        |              |          |The value can be programmed from 0x00 to 0x1F, and the step is -2dB.
  * |        |              |          |0x00 = 0 dB.
  * |        |              |          |0x01 = -2 dB.
  * |        |              |          |0x02 = -4 dB.
  * |        |              |          |...
  * |        |              |          |0x1E = -60 dB.
  * |        |              |          |0x1F = Analog Mute.
  *
  * CODEC DAC Output Channel Analog Mix Control Register (CODEC_DACMIXCTL)
  * ===================================================================================================
  * (Address: 0AH; Default: 09H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:6]   |Reserved      |00        |Reserved.
  * |[5:3]   |MIXSELL       |001       |DAC Output Left Channel Analog Mix Control
  * |        |              |          |000 = No signal selected.
  * |        |              |          |001 = Left DAC line-out signal selected.
  * |        |              |          |010 = Left analog input signal selected.
  * |        |              |          |100 = ADC MIC signal selected.
  * |        |              |          |011 = Left DAC line-out and left analog input signal mixer.
  * |        |              |          |110 = Left analog input and ADC MIC signal mixer.
  * |        |              |          |101 = Left DAC line-out and ADC MIC signal mixer.
  * |        |              |          |111 = Left DAC line-out, analog input, and ADC MIC signal mixer.
  * |        |              |          |Note: Left analog input signal can be set from LLineIn or MIC.
  * |[2:0]   |MIXSELR       |001       |DAC Output Right Channel Analog Mix Control
  * |        |              |          |000 = No signal selected.
  * |        |              |          |001 = Right DAC line-out signal selected.
  * |        |              |          |010 = Right analog input signal selected.
  * |        |              |          |100 = ADC MIC signal selected.
  * |        |              |          |011 = Right DAC line-out and right analog input signal mixer.
  * |        |              |          |110 = Right analog input and ADC MIC signal mixer.
  * |        |              |          |101 = Right DAC line-out and ADC MIC signal mixer.
  * |        |              |          |111 = Right DAC line-out, right analog input, and ADC MIC signal mixer.
  * |        |              |          |Note: Right analog input signal can be set from RLineIn or MIC.
  *
  * CODEC DAC Power Down Control Register of Analog Blocks (CODEC_DACPDCTL)
  * ===================================================================================================
  * (Address: 0BH; Default: FFH; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:6]   |Reserved      |11        |Reserved.
  * |[5]     |HPROI         |1         |Headphone Output Resistance Control Register
  * |        |              |          |0 = The impedance of headphone out is 1K Ohm.
  * |        |              |          |1 = The impedance of headphone out is 40K Ohm.
  * |        |              |          |Note: The bit is useful when headphone analog block is power-down.
  * |[4]     |PDCHG         |1         |VMID Pre-Charge Capacitance Control
  * |        |              |          |0 = VMID Pre-Charge capacitance Disabled.
  * |        |              |          |1 = VMID Pre-Charge capacitance Enabled.
  * |[3]     |PWDNL         |1         |DAC Left Channel Analog Block Power Control
  * |        |              |          |0 = Channel power Enabled.
  * |        |              |          |1 = Channel power Disabled.
  * |[2]     |PWDNR         |1         |DAC Right Channel Analog Block Power Control
  * |        |              |          |0 = Channel power Enabled.
  * |        |              |          |1 = Channel power Disabled.
  * |[1]     |PDPAL         |1         |DAC Left Headphone Out Analog Block Power Control
  * |        |              |          |0 = Headphone analog block power Enabled.
  * |        |              |          |1 = Headphone analog block power Disabled.
  * |[0]     |PDPAR         |1         |DAC Right Headphone Out Analog Block Power Control
  * |        |              |          |0 = Headphone analog block power Enabled.
  * |        |              |          |1 = Headphone analog block power Disabled.
  *
  * CODEC Power Control Register (CODEC_PWRCTL)
  * ===================================================================================================
  * (Address: 0DH; Default: 3AH; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:4]   |Reserved      |0011      |Reserved.
  * |[3]     |PDBIAS        |1         |CODEC Reference (MIC_BIAS) Power Control
  * |        |              |          |0 = Reference power Enabled.
  * |        |              |          |1 = Reference power Disabled.
  * |[2:0]   |RESADJ[2:0]   |010       |Current Biasing Resistor Selection
  * |        |              |          |000 = Smallest biasing resistor.
  * |        |              |          |001 = Biggest biasing resistor.
  * |        |              |          |010 = Medium big biasing resistor.
  * |        |              |          |100 = Medium small biasing resistor.
  * |        |              |          |Other = Reserved.
  *
  * CODEC ADC Input Control Register (CODEC_ADCINCTL)
  * ===================================================================================================
  * (Address: 0EH; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:3]   |Reserved      |0_0000    |Reserved.
  * |[2]     |MIC_SEL       |0         |Input Microphone Source Selection
  * |        |              |          |0 = Input signal is from MIC0.
  * |        |              |          |1 = Input signal is from MIC1.
  * |[1:0]   |ADCINSEL      |00        |Analog Input Signal Source Selection
  * |        |              |          |00 = Analog input signal is from line input.
  * |        |              |          |10 = Analog input signal is from microphone input.
  * |        |              |          |Other = Reserved.
  *
  * CODEC ADC Power Down Control Register (CODEC_ADCPDCTL)
  * ===================================================================================================
  * (Address: 0FH; Default: FFH; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:6]   |Reserved      |11        |Reserved.
  * |[5]     |PDMIC         |1         |Bias Current Of Microphone Power Control And Right Line-In Channel Selection
  * |        |              |          |0 = MIC-BIAS pin is for mic-bias function, and bias current power Enabled.
  * |        |              |          |1 = MIC-BIAS pin is for right line-in function, and bias current power Disabled.
  * |[4]     |PDSTO         |1         |Sidetone Analog Gain Block Power Control
  * |        |              |          |0 = Gain block power Enabled.
  * |        |              |          |1 = Gain block power Disabled.
  * |[3]     |PDPGAL        |1         |Left Channel Analog Gain Block Power Control Register
  * |        |              |          |0 = Gain block power Enabled.
  * |        |              |          |1 = Gain block power Disabled.
  * |[2]     |PDPGAR        |1         |Right Channel Analog Gain Block Power Control Register
  * |        |              |          |0 = Gain block power Enabled.
  * |        |              |          |1 = Gain block power Disabled.
  * |[1]     |PDL           |1         |Left Channel Sigma-Delta Module Power Control
  * |        |              |          |0 = Sigma-Delta Module power Enabled.
  * |        |              |          |1 = Sigma-Delta Module power Disabled.
  * |[0]     |PDR           |1         |Right Channel Sigma-Delta Module Power Control
  * |        |              |          |0 = Sigma-Delta Module power Enabled.
  * |        |              |          |1 = Sigma-Delta Module power Disabled.
  *
  * CODEC ADC Left Channel Gain Control Register (CODEC_ADCLVCTL)
  * ===================================================================================================
  * (Address: 10H; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:5]   |Reserved      |000       |Reserved.
  * |[4]     |PREVOL        |0         |Microphone Input Signal Pre-Gain Boost Control Register
  * |        |              |          |0 = Pre-Gain is 0 dB.
  * |        |              |          |1 = Pre-Gain is 20 dB.
  * |[3:0]   |ADC_VOLL      |0000      |ADC Left Channel Gain Control
  * |        |              |          |The value can be programmed from 0x0 to 0xF, and the step is 1.6dB.
  * |        |              |          |0x0 = 0 dB.
  * |        |              |          |0x1 = 1.6 dB.
  * |        |              |          |0x2 = 3.2 dB.
  * |        |              |          |...
  * |        |              |          |0xE = 22.4 dB.
  * |        |              |          |0xF = Volume Mute.
  *
  * CODEC ADC Right Channel Gain Control Register (CODEC_ADCRVCTL)
  * ===================================================================================================
  * (Address: 11H; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:4]   |Reserved      |0000      |Reserved.
  * |[3:0]   |ADC_VOLR      |0000      |ADC Right Channel Gain Control
  * |        |              |          |The value can be programmed from 0x0 to 0xF, and the step is 1.6dB.
  * |        |              |          |0x0 = 0 dB.
  * |        |              |          |0x1 = 1.6 dB.
  * |        |              |          |0x2 = 3.2 dB.
  * |        |              |          |...
  * |        |              |          |0xE = 22.4 dB.
  * |        |              |          |0xF = Volume Mute.
  *
  * CODEC ADC Sidetone Volume Control Register (CODEC_STOCTL)
  * ===================================================================================================
  * (Address: 12H; Default: 00H; Access: R/W)
  * ---------------------------------------------------------------------------------------------------
  * |Bits    |Label         |Default   |Description
  * | :----: | :----:       | :----:   | :---- |
  * |[7:4]   |Reserved      |0000      |Reserved.
  * |[3:0]   |STO_VOL       |0000      |ADC Sidetone Volume Control
  * |        |              |          |The value can be programmed from 0x0 to 0xF, and the step is -1.6dB.
  * |        |              |          |0x0 = 0 dB.
  * |        |              |          |0x1 = -1.6 dB.
  * |        |              |          |0x2 = -3.2 dB.
  * |        |              |          |...
  * |        |              |          |0xE = -22.4 dB.
  * |        |              |          |0xF = Volume Mute.
  *
  */
static __INLINE void I2S_SET_INTERNAL_CODEC(I2S_T *i2s, uint32_t u32Address, uint32_t u32Value)
{
    (i2s)->CODECCTL = (0x7F << I2S_CODECCTL_I2CCKDIV_Pos) | (0x40 << I2S_CODECCTL_DEVID_Pos) | I2S_CODECCTL_RW_Msk | (u32Address << I2S_CODECCTL_ADDR_Pos) | u32Value;
    while(((i2s)->CODECCTL & I2S_CODECCTL_BUSY_Msk));
}

/**
  * @brief  This function gets the internal CODEC register.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Address The internal CODEC register address.
  * @return the 8-bit address and 8-bit value of internal CODEC register.
  * @details This function gets internal CODEC register, through internal I2C protocol.
  */
static __INLINE uint32_t I2S_GET_INTERNAL_CODEC(I2S_T *i2s, uint32_t u32Address)
{
    (i2s)->CODECCTL &= ~I2S_CODECCTL_RW_Msk;
    (i2s)->CODECCTL = (0x7F << I2S_CODECCTL_I2CCKDIV_Pos) | (0x40 << I2S_CODECCTL_DEVID_Pos) | (u32Address << I2S_CODECCTL_ADDR_Pos);
    while(((i2s)->CODECCTL & I2S_CODECCTL_BUSY_Msk));
    return (i2s)->CODECCTL & 0x0000FFFF;
}



uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat, uint32_t u32AudioInterface);
void I2S_Close(I2S_T *i2s);
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask);
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask);
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock);
void I2S_DisableMCLK(I2S_T *i2s);
void I2S_SetFIFO(I2S_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold);

/*@}*/ /* end of group NUC505_I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_I2S_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__I2S_H__

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
