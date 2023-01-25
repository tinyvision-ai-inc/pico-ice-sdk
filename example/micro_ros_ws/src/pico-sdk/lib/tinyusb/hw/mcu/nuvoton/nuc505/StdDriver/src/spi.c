/**************************************************************************//**
 * @file     spi.c
 * @version  V1.0
 * $Revision: 7 $
 * $Date: 15/12/01 8:34p $
 * @brief    NUC505 series SPI driver source file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC505Series.h"
/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SPI_Driver SPI Driver
  @{
*/


/** @addtogroup NUC505_SPI_EXPORTED_FUNCTIONS SPI Exported Functions
  @{
*/

/**
  * @brief  This function make SPI module be ready to transfer.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32MasterSlave Decides the SPI module is operating in master mode or in slave mode. Valid values are listed below.
  *                                     - \ref SPI_MASTER
  *                                     - \ref SPI_SLAVE
  * @param[in]  u32SPIMode Decides the transfer timing. Valid values are listed below.
  *                                     - \ref SPI_MODE_0
  *                                     - \ref SPI_MODE_1
  *                                     - \ref SPI_MODE_2
  *                                     - \ref SPI_MODE_3
  * @param[in]  u32DataWidth Decides the data width of a SPI transaction.
  * @param[in]  u32BusClock The expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI peripheral clock.
  * @details By default, the SPI transfer sequence is MSB first, the slave selection signal is active low and the automatic
  *          slave selection function is disabled.
  *          In Slave mode, the u32BusClock shall be NULL and the SPI clock divider setting will be 0.
  *          The actual clock rate may be different from the target SPI clock rate.
  *          For example, if the SPI source clock rate is 12MHz and the target SPI bus clock rate is 7MHz, the
  *          actual SPI clock rate will be 6MHz.
  * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  * @note   SPI engine clock should less or equal than APB clock.
  */
uint32_t SPI_Open(SPI_T *spi,
                  uint32_t u32MasterSlave,
                  uint32_t u32SPIMode,
                  uint32_t u32DataWidth,
                  uint32_t u32BusClock)
{
    uint32_t u32Pclk, u32Div;

    if(u32DataWidth == 32)
        u32DataWidth = 0;

    spi->CTL = u32MasterSlave | (u32DataWidth << SPI_CTL_DWIDTH_Pos) | (u32SPIMode) | SPI_CTL_SPIEN_Msk;

    if ( spi == SPI0 )
    {
        if(CLK->CLKDIV2 & CLK_CLKDIV2_SPI0SEL_Msk)
            u32Pclk = CLK_GetPLLClockFreq();
        else
            u32Pclk = __HXT;
    }
    else
    {
        if(CLK->CLKDIV2 & CLK_CLKDIV2_SPI1SEL_Msk)
            u32Pclk = CLK_GetPLLClockFreq();
        else
            u32Pclk = __HXT;
    }

    if ( u32BusClock > CLK_GetPCLKFreq()  )
        u32BusClock = CLK_GetPCLKFreq();

    u32Div = 0xff;

    if(u32BusClock !=0 )
    {
        u32Div = (u32Pclk / u32BusClock) - 1;
        if(u32Div > 0xFF)
            u32Div = 0xFF;
        spi->CLKDIV = (spi->CLKDIV & ~0xff) | u32Div;
    }
    else
    {
        u32BusClock = CLK_GetPCLKFreq();
        u32Div = (u32Pclk / u32BusClock) - 1;
        if(u32Div > 0xFF)
            u32Div = 0xFF;
        spi->CLKDIV = (spi->CLKDIV & ~0xff) | u32Div;
    }

    return ( u32Pclk / (u32Div+1) );
}

/**
  * @brief  Disable SPI controller.
  * @param[in]  spi The base address of SPI module.
  * @return None
  * @details This function will reset SPI controller and disable SPI peripheral clock.
  */
void SPI_Close(SPI_T *spi)
{
    /* Reset SPI */
    if((uint32_t)spi == SPI0_BASE)
    {
        SYS->IPRST1 |= SYS_IPRST1_SPI0RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_SPI0RST_Msk;
    }
    else
    {
        SYS->IPRST1 |= SYS_IPRST1_SPI1RST_Msk;
        SYS->IPRST1 &= ~SYS_IPRST1_SPI1RST_Msk;
    }
}

/**
  * @brief  Clear Rx FIFO buffer.
  * @param[in]  spi The base address of SPI module.
  * @return None
  * @details This function will clear SPI Rx FIFO buffer. The RXEMPTY (SPI_STATUS[8]) will be set to 1.
  */
void SPI_ClearRxFIFO(SPI_T *spi)
{
    spi->FIFOCTL |= SPI_FIFOCTL_RXFBCLR_Msk;
}

/**
  * @brief  Clear Tx FIFO buffer.
  * @param[in]  spi The base address of SPI module.
  * @return None
  * @details This function will clear SPI Tx FIFO buffer. The TXEMPTY (SPI_STATUS[16]) will be set to 1.
  * @note The Tx shift register will not be cleared.
  */
void SPI_ClearTxFIFO(SPI_T *spi)
{
    spi->FIFOCTL |= SPI_FIFOCTL_TXFBCLR_Msk;
}

/**
  * @brief  Disable the automatic slave selection function.
  * @param[in]  spi The base address of SPI module.
  * @return None
  * @details This function will disable the automatic slave selection function and set slave selection signal to inactive state.
  */
void SPI_DisableAutoSS(SPI_T *spi)
{
    spi->SSCTL &= ~(SPI_SSCTL_AUTOSS_Msk | SPI_SSCTL_SS_Msk);
}

/**
  * @brief  Enable the automatic slave selection function.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32SSPinMask Specifies slave selection pins. Valid value is:
  *                        - \ref SPI_SS
  * @param[in]  u32ActiveLevel Specifies the active level of slave selection signal. Valid values are:
  *                        - \ref SPI_SS_ACTIVE_HIGH
  *                        - \ref SPI_SS_ACTIVE_LOW
  * @return None
  * @details This function will enable the automatic slave selection function. Only available in Master mode.
  *          The slave selection pin and the active level will be set in this function.
  */
void SPI_EnableAutoSS(SPI_T *spi, uint32_t u32SSPinMask, uint32_t u32ActiveLevel)
{
    spi->SSCTL = (spi->SSCTL & (~(SPI_SSCTL_AUTOSS_Msk | SPI_SSCTL_SSACTPOL_Msk | SPI_SSCTL_SS_Msk))) | (u32SSPinMask | u32ActiveLevel | SPI_SSCTL_AUTOSS_Msk);
}

/**
  * @brief  Set the SPI bus clock.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32BusClock The expected frequency of SPI bus clock in Hz.
  * @return Actual frequency of SPI bus clock.
  * @details This function is only available in Master mode. The actual clock rate may be different from the target SPI bus clock rate.
  *          For example, if the SPI source clock rate is 12MHz and the target SPI bus clock rate is 7MHz, the actual SPI bus clock
  *          rate will be 6MHz.
  * @note   If u32BusClock = 0, DIVIDER setting will be set to the maximum value.
  * @note   SPI engine clock should less or equal than APB clock.
  */
uint32_t SPI_SetBusClock(SPI_T *spi, uint32_t u32BusClock)
{
    uint32_t u32Pclk, u32Div;

    if ( spi == SPI0 )
    {
        if(CLK->CLKDIV2 & CLK_CLKDIV2_SPI0SEL_Msk)
            u32Pclk = CLK_GetPLLClockFreq();
        else
            u32Pclk = __HXT;
    }
    else
    {
        if(CLK->CLKDIV2 & CLK_CLKDIV2_SPI1SEL_Msk)
            u32Pclk = CLK_GetPLLClockFreq();
        else
            u32Pclk = __HXT;
    }

    if ( u32BusClock > CLK_GetPCLKFreq()  )
        u32BusClock = CLK_GetPCLKFreq();

    u32Div = 0xff;

    if(u32BusClock !=0 )
    {
        u32Div = (u32Pclk / u32BusClock) - 1;
        if(u32Div > 0xFF)
            u32Div = 0xFF;
        spi->CLKDIV = (spi->CLKDIV & ~0xff) | u32Div;
    }
    else
    {
        u32BusClock = CLK_GetPCLKFreq();
        u32Div = (u32Pclk / u32BusClock) - 1;
        if(u32Div > 0xFF)
            u32Div = 0xFF;
        spi->CLKDIV = (spi->CLKDIV & ~0xff) | u32Div;
    }

    return ( u32Pclk / (u32Div+1) );
}

/**
  * @brief  Configure FIFO threshold setting.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32TxThreshold Decides the Tx FIFO threshold. For SPI0/SPI1, it could be 0 ~ 7.
  * @param[in]  u32RxThreshold Decides the Rx FIFO threshold. For SPI0/SPI1, it could be 0 ~ 7.
  * @return None
  * @details Set Tx FIFO threshold and Rx FIFO threshold configurations.
  */
void SPI_SetFIFO(SPI_T *spi, uint32_t u32TxThreshold, uint32_t u32RxThreshold)
{
    spi->FIFOCTL = ((spi->FIFOCTL & ~(SPI_FIFOCTL_TXTH_Msk | SPI_FIFOCTL_RXTH_Msk)) |
                    (u32TxThreshold << SPI_FIFOCTL_TXTH_Pos) |
                    (u32RxThreshold << SPI_FIFOCTL_RXTH_Pos));
}

/**
  * @brief  Get the actual frequency of SPI bus clock. Only available in Master mode.
  * @param[in]  spi The base address of SPI module.
  * @return Actual SPI bus clock frequency in Hz.
  * @details This function will calculate the actual SPI bus clock rate according to the SPInSEL and DIVIDER settings. Only available in Master mode.
  */
uint32_t SPI_GetBusClock(SPI_T *spi)
{
    uint32_t u32Pclk;
    uint32_t u32Div;

    if ( spi == SPI0 )
    {
        if(CLK->CLKDIV2 & CLK_CLKDIV2_SPI0SEL_Msk)
            u32Pclk = CLK_GetPLLClockFreq();
        else
            u32Pclk = __HXT;
    }
    else
    {
        if(CLK->CLKDIV2 & CLK_CLKDIV2_SPI1SEL_Msk)
            u32Pclk = CLK_GetPLLClockFreq();
        else
            u32Pclk = __HXT;
    }

//  if ( u32Pclk > CLK_GetPCLKFreq()  )
//          u32Pclk = CLK_GetPCLKFreq();

    u32Div = spi->CLKDIV & 0xff;
    return (u32Pclk / (u32Div + 1));
}

/**
  * @brief  Enable interrupt function.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32Mask The combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt enable bit.
  *                     This parameter decides which interrupts will be enabled. Valid values are:
  *                        - \ref SPI_UNIT_INT_MASK
  *                        - \ref SPI_SSACT_INT_MASK
  *                        - \ref SPI_SSINACT_INT_MASK
  *                        - \ref SPI_SLVUR_INT_MASK
  *                        - \ref SPI_SLVBE_INT_MASK
  *                        - \ref SPI_SLVTO_INT_MASK
  *                        - \ref SPI_TXUF_INT_MASK
  *                        - \ref SPI_FIFO_TXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXOV_INT_MASK
  *                        - \ref SPI_FIFO_RXTO_INT_MASK
  * @return None
  * @details Enable SPI related interrupts specified by u32Mask parameter.
  */
void SPI_EnableInt(SPI_T *spi, uint32_t u32Mask)
{
    /* Enable unit transfer interrupt flag */
    if((u32Mask & SPI_UNIT_INT_MASK) == SPI_UNIT_INT_MASK)
        spi->CTL |= SPI_CTL_UNITIEN_Msk;

    /* Enable slave selection signal active interrupt flag */
    if((u32Mask & SPI_SSACT_INT_MASK) == SPI_SSACT_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SSACTIEN_Msk;

    /* Enable slave selection signal inactive interrupt flag */
    if((u32Mask & SPI_SSINACT_INT_MASK) == SPI_SSINACT_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SSINAIEN_Msk;

    /* Enable slave Tx under run interrupt flag */
    if((u32Mask & SPI_SLVUR_INT_MASK) == SPI_SLVUR_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SLVURIEN_Msk;

    /* Enable slave bit count error interrupt flag */
    if((u32Mask & SPI_SLVBE_INT_MASK) == SPI_SLVBE_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SLVBEIEN_Msk;

    /* Enable slave time-out interrupt flag */
    if((u32Mask & SPI_SLVTO_INT_MASK) == SPI_SLVTO_INT_MASK)
        spi->SSCTL |= SPI_SSCTL_SLVTOIEN_Msk;

    /* Enable slave Tx underflow interrupt flag */
    if((u32Mask & SPI_TXUF_INT_MASK) == SPI_TXUF_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_TXUFIEN_Msk;

    /* Enable Tx threshold interrupt flag */
    if((u32Mask & SPI_FIFO_TXTH_INT_MASK) == SPI_FIFO_TXTH_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_TXTHIEN_Msk;

    /* Enable Rx threshold interrupt flag */
    if((u32Mask & SPI_FIFO_RXTH_INT_MASK) == SPI_FIFO_RXTH_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_RXTHIEN_Msk;

    /* Enable Rx overrun interrupt flag */
    if((u32Mask & SPI_FIFO_RXOV_INT_MASK) == SPI_FIFO_RXOV_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_RXOVIEN_Msk;

    /* Enable Rx time-out interrupt flag */
    if((u32Mask & SPI_FIFO_RXTO_INT_MASK) == SPI_FIFO_RXTO_INT_MASK)
        spi->FIFOCTL |= SPI_FIFOCTL_RXTOIEN_Msk;
}

/**
  * @brief  Disable interrupt function.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32Mask The combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt bit.
  *                     This parameter decides which interrupts will be disabled. Valid values are:
  *                        - \ref SPI_UNIT_INT_MASK
  *                        - \ref SPI_SSACT_INT_MASK
  *                        - \ref SPI_SSINACT_INT_MASK
  *                        - \ref SPI_SLVUR_INT_MASK
  *                        - \ref SPI_SLVBE_INT_MASK
  *                        - \ref SPI_SLVTO_INT_MASK
  *                        - \ref SPI_TXUF_INT_MASK
  *                        - \ref SPI_FIFO_TXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXOV_INT_MASK
  *                        - \ref SPI_FIFO_RXTO_INT_MASK
  * @return None
  * @details Disable SPI related interrupts specified by u32Mask parameter.
  */
void SPI_DisableInt(SPI_T *spi, uint32_t u32Mask)
{
    /* Disable unit transfer interrupt flag */
    if((u32Mask & SPI_UNIT_INT_MASK) == SPI_UNIT_INT_MASK)
        spi->CTL &= ~SPI_CTL_UNITIEN_Msk;

    /* Disable slave selection signal active interrupt flag */
    if((u32Mask & SPI_SSACT_INT_MASK) == SPI_SSACT_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SSACTIEN_Msk;

    /* Disable slave selection signal inactive interrupt flag */
    if((u32Mask & SPI_SSINACT_INT_MASK) == SPI_SSINACT_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SSINAIEN_Msk;

    /* Disable slave Tx under run interrupt flag */
    if((u32Mask & SPI_SLVUR_INT_MASK) == SPI_SLVUR_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SLVURIEN_Msk;

    /* Disable slave bit count error interrupt flag */
    if((u32Mask & SPI_SLVBE_INT_MASK) == SPI_SLVBE_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SLVBEIEN_Msk;

    /* Disable slave time-out interrupt flag */
    if((u32Mask & SPI_SLVTO_INT_MASK) == SPI_SLVTO_INT_MASK)
        spi->SSCTL &= ~SPI_SSCTL_SLVTOIEN_Msk;

    /* Disable slave Tx underflow interrupt flag */
    if((u32Mask & SPI_TXUF_INT_MASK) == SPI_TXUF_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_TXUFIEN_Msk;

    /* Disable Tx threshold interrupt flag */
    if((u32Mask & SPI_FIFO_TXTH_INT_MASK) == SPI_FIFO_TXTH_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_TXTHIEN_Msk;

    /* Disable Rx threshold interrupt flag */
    if((u32Mask & SPI_FIFO_RXTH_INT_MASK) == SPI_FIFO_RXTH_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_RXTHIEN_Msk;

    /* Disable Rx overrun interrupt flag */
    if((u32Mask & SPI_FIFO_RXOV_INT_MASK) == SPI_FIFO_RXOV_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_RXOVIEN_Msk;

    /* Disable Rx time-out interrupt flag */
    if((u32Mask & SPI_FIFO_RXTO_INT_MASK) == SPI_FIFO_RXTO_INT_MASK)
        spi->FIFOCTL &= ~SPI_FIFOCTL_RXTOIEN_Msk;
}

/**
  * @brief  Get interrupt flag.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32Mask The combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be read. Valid values are:
  *                        - \ref SPI_UNIT_INT_MASK
  *                        - \ref SPI_SSACT_INT_MASK
  *                        - \ref SPI_SSINACT_INT_MASK
  *                        - \ref SPI_SLVUR_INT_MASK
  *                        - \ref SPI_SLVBE_INT_MASK
  *                        - \ref SPI_SLVTO_INT_MASK
  *                        - \ref SPI_TXUF_INT_MASK
  *                        - \ref SPI_FIFO_TXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXOV_INT_MASK
  *                        - \ref SPI_FIFO_RXTO_INT_MASK
  * @return Interrupt flags of selected sources.
  * @details Get SPI related interrupt flags specified by u32Mask parameter.
  */
uint32_t SPI_GetIntFlag(SPI_T *spi, uint32_t u32Mask)
{
    uint32_t u32IntFlag = 0;

    /* Check unit transfer interrupt flag */
    if((u32Mask & SPI_UNIT_INT_MASK) && (spi->STATUS & SPI_STATUS_UNITIF_Msk))
        u32IntFlag |= SPI_UNIT_INT_MASK;

    /* Check slave selection signal active interrupt flag */
    if((u32Mask & SPI_SSACT_INT_MASK) && (spi->STATUS & SPI_STATUS_SSACTIF_Msk))
        u32IntFlag |= SPI_SSACT_INT_MASK;

    /* Check slave selection signal inactive interrupt flag */
    if((u32Mask & SPI_SSINACT_INT_MASK) && (spi->STATUS & SPI_STATUS_SSINAIF_Msk))
        u32IntFlag |= SPI_SSINACT_INT_MASK;

    /* Check slave Tx under run interrupt flag */
    if((u32Mask & SPI_SLVUR_INT_MASK) && (spi->STATUS & SPI_STATUS_SLVURIF_Msk))
        u32IntFlag |= SPI_SLVUR_INT_MASK;

    /* Check slave bit count error interrupt flag */
    if((u32Mask & SPI_SLVBE_INT_MASK) && (spi->STATUS & SPI_STATUS_SLVBEIF_Msk))
        u32IntFlag |= SPI_SLVBE_INT_MASK;

    /* Check slave time-out interrupt flag */
    if((u32Mask & SPI_SLVTO_INT_MASK) && (spi->STATUS & SPI_STATUS_SLVTOIF_Msk))
        u32IntFlag |= SPI_SLVTO_INT_MASK;

    /* Check slave Tx underflow interrupt flag */
    if((u32Mask & SPI_TXUF_INT_MASK) && (spi->STATUS & SPI_STATUS_TXUFIF_Msk))
        u32IntFlag |= SPI_TXUF_INT_MASK;

    /* Check Tx threshold interrupt flag */
    if((u32Mask & SPI_FIFO_TXTH_INT_MASK) && (spi->STATUS & SPI_STATUS_TXTHIF_Msk))
        u32IntFlag |= SPI_FIFO_TXTH_INT_MASK;

    /* Check Rx threshold interrupt flag */
    if((u32Mask & SPI_FIFO_RXTH_INT_MASK) && (spi->STATUS & SPI_STATUS_RXTHIF_Msk))
        u32IntFlag |= SPI_FIFO_RXTH_INT_MASK;

    /* Check Rx overrun interrupt flag */
    if((u32Mask & SPI_FIFO_RXOV_INT_MASK) && (spi->STATUS & SPI_STATUS_RXOVIF_Msk))
        u32IntFlag |= SPI_FIFO_RXOV_INT_MASK;

    /* Check Rx time-out interrupt flag */
    if((u32Mask & SPI_FIFO_RXTO_INT_MASK) && (spi->STATUS & SPI_STATUS_RXTOIF_Msk))
        u32IntFlag |= SPI_FIFO_RXTO_INT_MASK;

    return u32IntFlag;
}

/**
  * @brief  Clear interrupt flag.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32Mask The combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be cleared. Valid values are:
  *                        - \ref SPI_UNIT_INT_MASK
  *                        - \ref SPI_SSACT_INT_MASK
  *                        - \ref SPI_SSINACT_INT_MASK
  *                        - \ref SPI_SLVUR_INT_MASK
  *                        - \ref SPI_SLVBE_INT_MASK
  *                        - \ref SPI_SLVTO_INT_MASK
  *                        - \ref SPI_TXUF_INT_MASK
  *                        - \ref SPI_FIFO_TXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXTH_INT_MASK
  *                        - \ref SPI_FIFO_RXOV_INT_MASK
  *                        - \ref SPI_FIFO_RXTO_INT_MASK
  * @return None
  * @details Clear SPI related interrupt flags specified by u32Mask parameter.
  */
void SPI_ClearIntFlag(SPI_T *spi, uint32_t u32Mask)
{
    if(u32Mask & SPI_UNIT_INT_MASK)
        spi->STATUS = SPI_STATUS_UNITIF_Msk; /* Clear unit transfer interrupt flag */

    if(u32Mask & SPI_SSACT_INT_MASK)
        spi->STATUS = SPI_STATUS_SSACTIF_Msk; /* Clear slave selection signal active interrupt flag */

    if(u32Mask & SPI_SSINACT_INT_MASK)
        spi->STATUS = SPI_STATUS_SSINAIF_Msk; /* Clear slave selection signal inactive interrupt flag */

    if(u32Mask & SPI_SLVUR_INT_MASK)
        spi->STATUS = SPI_STATUS_SLVURIF_Msk; /* Clear slave Tx under run interrupt flag */

    if(u32Mask & SPI_SLVBE_INT_MASK)
        spi->STATUS = SPI_STATUS_SLVBEIF_Msk; /* Clear slave bit count error interrupt flag */

    if(u32Mask & SPI_SLVTO_INT_MASK)
        spi->STATUS = SPI_STATUS_SLVTOIF_Msk; /* Clear slave time-out interrupt flag */

    if(u32Mask & SPI_TXUF_INT_MASK)
        spi->STATUS = SPI_STATUS_TXUFIF_Msk; /* Clear slave Tx underflow interrupt flag */

    if(u32Mask & SPI_FIFO_RXOV_INT_MASK)
        spi->STATUS = SPI_STATUS_RXOVIF_Msk; /* Clear Rx overrun interrupt flag */

    if(u32Mask & SPI_FIFO_RXTO_INT_MASK)
        spi->STATUS = SPI_STATUS_RXTOIF_Msk; /* Clear Rx time-out interrupt flag */
}

/**
  * @brief  Get SPI status.
  * @param[in]  spi The base address of SPI module.
  * @param[in]  u32Mask The combination of all related sources.
  *                     Each bit corresponds to a source.
  *                     This parameter decides which flags will be read. Valid values are:
  *                        - \ref SPI_BUSY_MASK
  *                        - \ref SPI_RX_EMPTY_MASK
  *                        - \ref SPI_RX_FULL_MASK
  *                        - \ref SPI_TX_EMPTY_MASK
  *                        - \ref SPI_TX_FULL_MASK
  *                        - \ref SPI_TXRX_RESET_MASK
  *                        - \ref SPI_SPIEN_STS_MASK
  *                        - \ref SPI_SSLINE_STS_MASK
  * @return Flags of selected sources.
  * @details Get SPI related status specified by u32Mask parameter.
  */
uint32_t SPI_GetStatus(SPI_T *spi, uint32_t u32Mask)
{
    uint32_t u32Flag = 0;

    /* Check busy status */
    if((u32Mask & SPI_BUSY_MASK) && (spi->STATUS & SPI_STATUS_BUSY_Msk))
        u32Flag |= SPI_BUSY_MASK;

    /* Check Rx empty flag */
    if((u32Mask & SPI_RX_EMPTY_MASK) && (spi->STATUS & SPI_STATUS_RXEMPTY_Msk))
        u32Flag |= SPI_RX_EMPTY_MASK;

    /* Check Rx full flag */
    if((u32Mask & SPI_RX_FULL_MASK) && (spi->STATUS & SPI_STATUS_RXFULL_Msk))
        u32Flag |= SPI_RX_FULL_MASK;

    /* Check Tx empty flag */
    if((u32Mask & SPI_TX_EMPTY_MASK) && (spi->STATUS & SPI_STATUS_TXEMPTY_Msk))
        u32Flag |= SPI_TX_EMPTY_MASK;

    /* Check Tx full flag */
    if((u32Mask & SPI_TX_FULL_MASK) && (spi->STATUS & SPI_STATUS_TXFULL_Msk))
        u32Flag |= SPI_TX_FULL_MASK;

    /* Check Tx/Rx reset flag */
    if((u32Mask & SPI_TXRX_RESET_MASK) && (spi->STATUS & SPI_STATUS_TXRXRST_Msk))
        u32Flag |= SPI_TXRX_RESET_MASK;

    /* Check SPIEN flag */
    if((u32Mask & SPI_SPIEN_STS_MASK) && (spi->STATUS & SPI_STATUS_SPIENSTS_Msk))
        u32Flag |= SPI_SPIEN_STS_MASK;

    /* Check SPIn_SS line status */
    if((u32Mask & SPI_SSLINE_STS_MASK) && (spi->STATUS & SPI_STATUS_SSLINE_Msk))
        u32Flag |= SPI_SSLINE_STS_MASK;

    return u32Flag;
}

/*@}*/ /* end of group NUC505_SPI_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_SPI_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/
