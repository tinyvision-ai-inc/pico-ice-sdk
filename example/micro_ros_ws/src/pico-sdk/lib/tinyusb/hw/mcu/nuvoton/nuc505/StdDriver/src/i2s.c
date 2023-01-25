/**************************************************************************//**
 * @file     i2s.c
 * @version  V1.1
 * $Revision: 7 $
 * $Date: 15/12/01 3:41p $
 * @brief    NUC505 series I2S driver source file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC505Series.h"
/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_I2S_Driver I2S Driver
  @{
*/


/** @addtogroup NUC505_I2S_EXPORTED_FUNCTIONS I2S Exported Functions
  @{
*/

/**
  * @brief  This function is used to get I2S source clock frequency.
  * @param[in]  i2s The base address of I2S module.
  * @return I2S source clock frequency (Hz).
  * @details Return the source clock frequency according to the setting of I2SSEL (CLKDIV2[24:25]).
  */
static uint32_t I2S_GetSourceClockFreq(I2S_T *i2s)
{
    uint32_t u32Freq=0, u32ClkSrcSel=0;

    // get I2S selection clock source
    if((uint32_t)i2s == I2S_BASE)
    {
        u32ClkSrcSel = CLK->CLKDIV2 & CLK_CLKDIV2_I2SSEL_Msk;
        u32Freq = (CLK->CLKDIV2 & CLK_CLKDIV2_I2SDIV_Msk)+1;
    }

    switch (u32ClkSrcSel)
    {
    case CLK_I2S_SRC_EXT:
        u32Freq = __HXT / u32Freq;
        break;

    case CLK_I2S_SRC_PLL:
        u32Freq = CLK_GetPLLClockFreq() / u32Freq;
        break;

    case CLK_I2S_SRC_APLL:
        u32Freq = CLK_GetAPLLClockFreq() / u32Freq;
        break;

    default:
        u32Freq = __HXT / u32Freq;
        break;
    }

    return u32Freq;
}

/**
  * @brief  This function configures some parameters of I2S interface for general purpose use.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32MasterSlave I2S operation mode. Valid values are listed below.
  *                                     - \ref I2S_MODE_MASTER
  *                                     - \ref I2S_MODE_SLAVE
  * @param[in] u32SampleRate Sample rate
  * @param[in] u32WordWidth Data length. Valid values are listed below.
  *                                     - \ref I2S_DATABIT_8
  *                                     - \ref I2S_DATABIT_16
  *                                     - \ref I2S_DATABIT_24
  *                                     - \ref I2S_DATABIT_32
  * @param[in] u32Channels Audio format. Valid values are listed below.
  *                                     - \ref I2S_MONO
  *                                     - \ref I2S_STEREO
  * @param[in] u32DataFormat Data format. Valid values are listed below.
  *                                     - \ref I2S_FORMAT_I2S
  *                                     - \ref I2S_FORMAT_MSB
  *                                     - \ref I2S_FORMAT_PCMA
  *                                     - \ref I2S_FORMAT_PCMB
    * @param[in] u32AudioInterface Audio interface. Valid values are listed below.
  *                                     - \ref I2S_DISABLE_INTERNAL_CODEC
  *                                     - \ref I2S_ENABLE_INTERNAL_CODEC
  * @return Real sample rate of master mode or peripheral clock rate of slave mode.
  * @details This function will reset I2S controller and configure I2S controller according to the input parameters.
  *          Set Tx and Rx FIFO threshold to middle value. Both the Tx and Rx functions will be enabled.
  *          The actual sample rate may be different from the target sample rate. The real sample rate will be returned for reference.
    *          The audio interface can be internal CODEC \ref I2S_ENABLE_INTERNAL_CODEC or external CODEC \ref I2S_DISABLE_INTERNAL_CODEC.
  */
uint32_t I2S_Open(I2S_T *i2s, uint32_t u32MasterSlave, uint32_t u32SampleRate, uint32_t u32WordWidth, uint32_t u32Channels, uint32_t u32DataFormat, uint32_t u32AudioInterface)
{
    uint16_t u16Divider;
    uint32_t u32BitRate, u32SrcClk;

    if((uint32_t)i2s == I2S_BASE)
    {
        SYS->IPRST1 |= SYS_IPRST1_I2SRST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_I2SRST_Msk;
    }

    if ( u32AudioInterface == 1 )
    {
        i2s->CTL = BIT22 | u32MasterSlave | u32WordWidth | u32Channels | u32DataFormat | I2S_CTL_CODECRST_Msk | I2S_FIFO_TX_LEVEL_WORD_8 | I2S_FIFO_RX_LEVEL_WORD_9;
        i2s->CTL &= ~I2S_CTL_CODECSEL_Msk;
        u32WordWidth = I2S_DATABIT_32;
    }
    else if ( u32AudioInterface == 0 )
    {
        i2s->CTL = BIT22 | u32MasterSlave | u32WordWidth | u32Channels | u32DataFormat | I2S_CTL_CODECSEL_Msk | I2S_FIFO_TX_LEVEL_WORD_8 | I2S_FIFO_RX_LEVEL_WORD_9;
        i2s->CTL &= ~I2S_CTL_CODECRST_Msk;
    }
    else
    {
        i2s->CTL = BIT22 | u32MasterSlave | u32WordWidth | u32Channels | u32DataFormat | I2S_CTL_CODECRST_Msk | I2S_CTL_CODECSEL_Msk | I2S_FIFO_TX_LEVEL_WORD_8 | I2S_FIFO_RX_LEVEL_WORD_9;
        u32WordWidth = I2S_DATABIT_32;
    }

    u32SrcClk = I2S_GetSourceClockFreq(i2s);

    u32BitRate = u32SampleRate * (((u32WordWidth>>4) & 0x3) + 1) * 16;
    u16Divider = (((((u32SrcClk*10)/u32BitRate) + 5) / 10) >> 1) - 1;
    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_BCLKDIV_Msk) | (u16Divider << 8);

    //calculate real sample rate
    u32BitRate = u32SrcClk / (2*(u16Divider+1));
    u32SampleRate = u32BitRate / ((((u32WordWidth>>4) & 0x3) + 1) * 16);

    i2s->CTL |= I2S_CTL_I2SEN_Msk;

    return u32SampleRate;
}

/**
  * @brief  Disable I2S function.
  * @param[in]  i2s The base address of I2S module.
  * @return None
  * @details Disable I2S function and I2S peripheral clock.
  */
void I2S_Close(I2S_T *i2s)
{
    i2s->CTL &= ~I2S_CTL_I2SEN_Msk;

    if((uint32_t)i2s == I2S_BASE)
        NVIC_DisableIRQ(I2S_IRQn);
}

/**
  * @brief Enable interrupt function.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Mask The combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt source. Valid values are listed below.
  *            - \ref I2S_FIFO_RXUD_INT_MASK
  *            - \ref I2S_FIFO_RXOV_INT_MASK
  *            - \ref I2S_FIFO_RXTH_INT_MASK
  *            - \ref I2S_RDMAE_INT_MASK
  *            - \ref I2S_RDMAT_INT_MASK
  *            - \ref I2S_TDMAE_INT_MASK
  *            - \ref I2S_TDMAT_INT_MASK
  *            - \ref I2S_FIFO_TXUD_INT_MASK
  *            - \ref I2S_FIFO_TXOV_INT_MASK
  *            - \ref I2S_FIFO_TXTH_INT_MASK
  *            - \ref I2S_RZC_INT_MASK
  *            - \ref I2S_LZC_INT_MASK
  * @return None
  * @details This function enables the interrupt according to the u32Mask parameter.
  */
void I2S_EnableInt(I2S_T *i2s, uint32_t u32Mask)
{
    i2s->IEN |= u32Mask;
}

/**
  * @brief Disable interrupt function.
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32Mask The combination of all related interrupt enable bits.
  *            Each bit corresponds to a interrupt source. Valid values are listed below.
  *            - \ref I2S_FIFO_RXUD_INT_MASK
  *            - \ref I2S_FIFO_RXOV_INT_MASK
  *            - \ref I2S_FIFO_RXTH_INT_MASK
  *            - \ref I2S_RDMAE_INT_MASK
  *            - \ref I2S_RDMAT_INT_MASK
  *            - \ref I2S_TDMAE_INT_MASK
  *            - \ref I2S_TDMAT_INT_MASK
  *            - \ref I2S_FIFO_TXUD_INT_MASK
  *            - \ref I2S_FIFO_TXOV_INT_MASK
  *            - \ref I2S_FIFO_TXTH_INT_MASK
  *            - \ref I2S_RZC_INT_MASK
  *            - \ref I2S_LZC_INT_MASK
  * @return None
  * @details This function disables the interrupt according to the u32Mask parameter.
  */
void I2S_DisableInt(I2S_T *i2s, uint32_t u32Mask)
{
    i2s->IEN &= ~u32Mask;
}

/**
  * @brief  Enable master clock (MCLK).
  * @param[in] i2s The base address of I2S module.
  * @param[in] u32BusClock The target MCLK clock rate.
  * @return Actual MCLK clock rate
  * @details Set the master clock rate according to u32BusClock parameter and enable master clock output.
  *          The actual master clock rate may be different from the target master clock rate. The real master clock rate will be returned for reference.
  */
uint32_t I2S_EnableMCLK(I2S_T *i2s, uint32_t u32BusClock)
{
    uint8_t u8Divider;
    uint32_t u32SrcClk, u32Reg;

    u32SrcClk = I2S_GetSourceClockFreq(i2s);
    if (u32BusClock == u32SrcClk)
        u8Divider = 0;
    else
        u8Divider = ((((u32SrcClk*10)/u32BusClock) + 5) / 10) >> 1;

    i2s->CLKDIV = (i2s->CLKDIV & ~I2S_CLKDIV_MCLKDIV_Msk) | u8Divider;

    i2s->CTL |= I2S_CTL_MCLKEN_Msk;

    u32Reg = i2s->CLKDIV & I2S_CLKDIV_MCLKDIV_Msk;

    if (u32Reg == 0)
        return u32SrcClk;
    else
        return ((u32SrcClk >> 1) / u32Reg);
}

/**
  * @brief  Disable master clock (MCLK).
  * @param[in] i2s The base address of I2S module.
  * @return None
  * @details Clear MCLKEN bit of I2S_CTL register to disable master clock output.
  */
void I2S_DisableMCLK(I2S_T *i2s)
{
    i2s->CTL &= ~I2S_CTL_MCLKEN_Msk;
}

/**
  * @brief  Configure FIFO threshold setting.
  * @param[in]  i2s The pointer of the specified I2S module.
  * @param[in]  u32TxThreshold Decides the TX FIFO threshold. It could be 0 ~ 15.
  * @param[in]  u32RxThreshold Decides the RX FIFO threshold. It could be 0 ~ 15.
  * @return None
  * @details Set TX FIFO threshold and RX FIFO threshold configurations.
  */
void I2S_SetFIFO(I2S_T *i2s, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    i2s->CTL = ((i2s->CTL & ~(I2S_CTL_TXTH_Msk | I2S_CTL_RXTH_Msk)) |
                (u32TxThreshold << I2S_CTL_TXTH_Pos) |
                (u32RxThreshold << I2S_CTL_RXTH_Pos));
}
/*@}*/ /* end of group NUC505_I2S_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_I2S_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
