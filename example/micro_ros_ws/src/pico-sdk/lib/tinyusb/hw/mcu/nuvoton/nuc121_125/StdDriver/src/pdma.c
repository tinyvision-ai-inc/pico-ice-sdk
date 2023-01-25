/**************************************************************************//**
 * @file     pdma.c
 * @version  V3.00
 * @brief    NUC121 series PDMA driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"


static uint8_t u32ChSelect[PDMA_CH_MAX];

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup PDMA_Driver PDMA Driver
  @{
*/


/** @addtogroup PDMA_EXPORTED_FUNCTIONS PDMA Exported Functions
  @{
*/

/**
 * @brief       PDMA Open
 *
 * @param[in]   u32Mask     Channel enable bits.
 *                - \ref PDMA_CHCTL_CHEN0_Msk
 *                - \ref PDMA_CHCTL_CHEN1_Msk
 *                - \ref PDMA_CHCTL_CHEN2_Msk
 *                - \ref PDMA_CHCTL_CHEN3_Msk
 *                - \ref PDMA_CHCTL_CHEN4_Msk
 * @return      None
 *
 * @details     This function enable the PDMA channels.
 */
void PDMA_Open(uint32_t u32Mask)
{
    int volatile i;

    for (i = 0; i < PDMA_CH_MAX; i++)
    {
        if ((1 << i) & u32Mask)
        {
            PDMA->DSCT[i].CTL = 0;
            u32ChSelect[i] = PDMA_MEM;
        }
    }

    PDMA->CHCTL |= u32Mask;
}

/**
 * @brief       PDMA Close
 *
 * @param       None
 *
 * @return      None
 *
 * @details     This function disable all PDMA channels.
 */
void PDMA_Close(void)
{
    PDMA->CHCTL = 0;
}

/**
 * @brief       Set PDMA Transfer Count
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Width        Data width. Valid values are
 *                - \ref PDMA_WIDTH_8
 *                - \ref PDMA_WIDTH_16
 *                - \ref PDMA_WIDTH_32
 * @param[in]   u32TransCount   Transfer count
 *
 * @return      None
 *
 * @details     This function set the selected channel data width and transfer count.
 */
void PDMA_SetTransferCnt(uint32_t u32Ch, uint32_t u32Width, uint32_t u32TransCount)
{
    PDMA->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_TXCNT_Msk | PDMA_DSCT_CTL_TXWIDTH_Msk);
    PDMA->DSCT[u32Ch].CTL |= (u32Width | ((u32TransCount - 1) << PDMA_DSCT_CTL_TXCNT_Pos));
}

/**
 * @brief       Set PDMA Transfer Address
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32SrcAddr      Source address
 * @param[in]   u32SrcCtrl      Source control attribute. Valid values are
 *                - \ref PDMA_SAR_INC
 *                - \ref PDMA_SAR_FIX
 * @param[in]   u32DstAddr      destination address
 * @param[in]   u32DstCtrl      destination control attribute. Valid values are
 *                - \ref PDMA_DAR_INC
 *                - \ref PDMA_DAR_FIX
 *
 * @return      None
 *
 * @details     This function set the selected channel source/destination address and attribute.
 */
void PDMA_SetTransferAddr(uint32_t u32Ch, uint32_t u32SrcAddr, uint32_t u32SrcCtrl, uint32_t u32DstAddr, uint32_t u32DstCtrl)
{
    PDMA->DSCT[u32Ch].SA = u32SrcAddr;
    PDMA->DSCT[u32Ch].DA = u32DstAddr;
    PDMA->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_SAINC_Msk | PDMA_DSCT_CTL_DAINC_Msk);
    PDMA->DSCT[u32Ch].CTL |= (u32SrcCtrl | u32DstCtrl);
}

/**
 * @brief       Set PDMA Transfer Mode
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Peripheral   The selected peripheral. Valid values are
 *                - \ref PDMA_MEM
 *                - \ref PDMA_UART0_TX
 *                - \ref PDMA_UART0_RX
 *                - \ref PDMA_USCI0_TX
 *                - \ref PDMA_USCI0_RX
 *                - \ref PDMA_SPI0_TX
 *                - \ref PDMA_SPI0_RX
 *                - \ref PDMA_ADC_RX
 *                - \ref PDMA_PWM0_P0_RX
 *                - \ref PDMA_PWM0_P1_RX
 *                - \ref PDMA_PWM0_P2_RX
 *                - \ref PDMA_PWM1_P0_RX
 *                - \ref PDMA_PWM1_P1_RX
 *                - \ref PDMA_PWM1_P2_RX
 *                - \ref PDMA_I2C0_TX
 *                - \ref PDMA_I2C0_RX
 *                - \ref PDMA_I2C1_TX
 *                - \ref PDMA_I2C1_RX
 *                - \ref PDMA_TMR0
 *                - \ref PDMA_TMR1
 *                - \ref PDMA_TMR2
 *                - \ref PDMA_TMR3
 * @param[in]   u32ScatterEn    Scatter-gather mode enable
 * @param[in]   u32DescAddr     Scatter-gather descriptor address
 *
 * @return      None
 *
 * @details     This function set the selected channel transfer mode. Include peripheral setting.
 */
void PDMA_SetTransferMode(uint32_t u32Ch, uint32_t u32Peripheral, uint32_t u32ScatterEn, uint32_t u32DescAddr)
{
    u32ChSelect[u32Ch] = u32Peripheral;

    switch (u32Ch)
    {
    case 0:
        PDMA->REQSEL0_3 = (PDMA->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC0_Msk) | u32Peripheral;
        break;

    case 1:
        PDMA->REQSEL0_3 = (PDMA->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC1_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC1_Pos);
        break;

    case 2:
        PDMA->REQSEL0_3 = (PDMA->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC2_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC2_Pos);
        break;

    case 3:
        PDMA->REQSEL0_3 = (PDMA->REQSEL0_3 & ~PDMA_REQSEL0_3_REQSRC3_Msk) | (u32Peripheral << PDMA_REQSEL0_3_REQSRC3_Pos);
        break;

    case 4:
        PDMA->REQSEL4 = (PDMA->REQSEL4 & ~PDMA_REQSEL4_REQSRC4_Msk) | u32Peripheral;

    default:
        ;
    }

    if (u32ScatterEn)
    {
        PDMA->DSCT[u32Ch].CTL = (PDMA->DSCT[u32Ch].CTL & ~PDMA_DSCT_CTL_OPMODE_Msk) | PDMA_OP_SCATTER;
        PDMA->DSCT[u32Ch].FIRST = u32DescAddr - (PDMA->SCATBA);
    }
    else
        PDMA->DSCT[u32Ch].CTL = (PDMA->DSCT[u32Ch].CTL & ~PDMA_DSCT_CTL_OPMODE_Msk) | PDMA_OP_BASIC;
}

/**
 * @brief       Set PDMA Burst Type and Size
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32BurstType    Burst mode or single mode. Valid values are
 *                - \ref PDMA_REQ_SINGLE
 *                - \ref PDMA_REQ_BURST
 * @param[in]   u32BurstSize    Set the size of burst mode. Valid values are
 *                - \ref PDMA_BURST_128
 *                - \ref PDMA_BURST_64
 *                - \ref PDMA_BURST_32
 *                - \ref PDMA_BURST_16
 *                - \ref PDMA_BURST_8
 *                - \ref PDMA_BURST_4
 *                - \ref PDMA_BURST_2
 *                - \ref PDMA_BURST_1
 *
 * @return      None
 *
 * @details     This function set the selected channel burst type and size.
 */
void PDMA_SetBurstType(uint32_t u32Ch, uint32_t u32BurstType, uint32_t u32BurstSize)
{
    PDMA->DSCT[u32Ch].CTL &= ~(PDMA_DSCT_CTL_TXTYPE_Msk | PDMA_DSCT_CTL_BURSIZE_Msk);
    PDMA->DSCT[u32Ch].CTL |= (u32BurstType | u32BurstSize);
}

/**
 * @brief       Enable timeout function
 *
 * @param[in]   u32Mask         Channel enable bits.
 *                - \ref PDMA_TOUTEN_TOUTEN0_Msk
 *                - \ref PDMA_TOUTEN_TOUTEN1_Msk
 * @return      None
 *
 * @details     This function enable timeout function of the selected channel(s).
 * @note        This function is only supported in channel 0 and channel 1.
 */
void PDMA_EnableTimeout(uint32_t u32Mask)
{
    PDMA->TOUTEN |= u32Mask;
}

/**
 * @brief       Disable timeout function
 *
 * @param[in]   u32Mask         Channel enable bits.
 *                - \ref PDMA_TOUTEN_TOUTEN0_Msk
 *                - \ref PDMA_TOUTEN_TOUTEN1_Msk
 * @return      None
 *
 * @details     This function disable timeout function of the selected channel(s).
 * @note        This function is only supported in channel 0 and channel 1.
 */
void PDMA_DisableTimeout(uint32_t u32Mask)
{
    PDMA->TOUTEN &= ~u32Mask;
}

/**
 * @brief       Set PDMA Timeout Count
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32OnOff        Enable/disable timeout function
 * @param[in]   u32TimeOutCnt   Timeout count
 * @return      None
 *
 * @details     This function set the timeout count.
 * @note        This function is only supported in channel 0 and channel 1.
 */
void PDMA_SetTimeOut(uint32_t u32Ch, uint32_t u32OnOff, uint32_t u32TimeOutCnt)
{
    switch (u32Ch)
    {
    case 0:
        PDMA->TOC0_1 = (PDMA->TOC0_1 & ~PDMA_TOC0_1_TOC0_Msk) | u32TimeOutCnt;
        break;

    case 1:
        PDMA->TOC0_1 = (PDMA->TOC0_1 & ~PDMA_TOC0_1_TOC1_Msk) | (u32TimeOutCnt << PDMA_TOC0_1_TOC1_Pos);
        break;

    default:
        ;
    }

    if (u32OnOff)
        PDMA->TOUTEN |= (1 << u32Ch);
    else
        PDMA->TOUTEN &= ~(1 << u32Ch);
}

/**
 * @brief       Trigger PDMA
 *
 * @param[in]   u32Ch           The selected channel
 *
 * @return      None
 *
 * @details     This function trigger the selected channel.
 */
void PDMA_Trigger(uint32_t u32Ch)
{
    if (u32ChSelect[u32Ch] == PDMA_MEM)
        PDMA->SWREQ = (1 << u32Ch);
}

/**
 * @brief       Enable Interrupt
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type. Valid values are
 *                - \ref PDMA_INT_TRANS_DONE
 *                - \ref PDMA_INT_TEMPTY
 *                - \ref PDMA_INT_TIMEOUT
 *
 * @return      None
 *
 * @details     This function enable the selected channel interrupt.
 * @note        PDMA_INT_TIMEOUT is only supported in channel 0 and channel 1.
 */
void PDMA_EnableInt(uint32_t u32Ch, uint32_t u32Mask)
{
    switch (u32Mask)
    {
    case PDMA_INT_TRANS_DONE:
        PDMA->INTEN |= (1 << u32Ch);
        break;

    case PDMA_INT_TEMPTY:
        PDMA->DSCT[u32Ch].CTL &= ~PDMA_DSCT_CTL_TBINTDIS_Msk;
        break;

    case PDMA_INT_TIMEOUT:
        PDMA->TOUTIEN |= (1 << u32Ch);
        break;

    default:
        ;
    }
}

/**
 * @brief       Disable Interrupt
 *
 * @param[in]   u32Ch           The selected channel
 * @param[in]   u32Mask         The Interrupt Type. Valid values are
 *                - \ref PDMA_INT_TRANS_DONE
 *                - \ref PDMA_INT_TEMPTY
 *                - \ref PDMA_INT_TIMEOUT
 *
 * @return      None
 *
 * @details     This function disable the selected channel interrupt.
 * @note        PDMA_INT_TIMEOUT is only supported in channel 0 and channel 1.
 * @note        The transfer done interrupt is disabled when table empty interrupt is disabled(PDMA_INT_TEMPTY).
 */
void PDMA_DisableInt(uint32_t u32Ch, uint32_t u32Mask)
{
    switch (u32Mask)
    {
    case PDMA_INT_TRANS_DONE:
        PDMA->INTEN &= ~(1 << u32Ch);
        break;

    case PDMA_INT_TEMPTY:
        PDMA->DSCT[u32Ch].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;
        break;

    case PDMA_INT_TIMEOUT:
        PDMA->TOUTIEN &= ~(1 << u32Ch);
        break;

    default:
        ;
    }
}

/*@}*/ /* end of group PDMA_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group PDMA_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
