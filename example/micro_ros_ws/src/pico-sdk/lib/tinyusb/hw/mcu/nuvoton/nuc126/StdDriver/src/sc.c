/**************************************************************************//**
 * @file     sc.c
 * @version  V3.00
 * $Revision: 7 $
 * $Date: 16/10/25 4:25p $
 * @brief    NUC126 series Smart Card(SC) driver source file
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC126.h"

/* Below are variables used locally by SC driver and does not want to parse by doxygen unless HIDDEN_SYMBOLS is defined */
/// @cond HIDDEN_SYMBOLS
static uint32_t u32CardStateIgnore[SC_INTERFACE_NUM] = {0, 0};

/// @endcond HIDDEN_SYMBOLS

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SC_Driver SC Driver
  @{
*/

/** @addtogroup SC_EXPORTED_FUNCTIONS SC Exported Functions
  @{
*/

/**
  * @brief      Check Smartcard Slot Status
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @retval     TRUE    Card insert
  * @retval     FALSE   Card remove
  *
  * @details    This function is used to check if specified smartcard slot is presented.
  */
uint32_t SC_IsCardInserted(SC_T *sc)
{
    /* Put conditions into two variable to remove IAR compilation warning */
    uint32_t cond1 = ((sc->STATUS & SC_STATUS_CDPINSTS_Msk) >> SC_STATUS_CDPINSTS_Pos);
    uint32_t cond2 = ((sc->CTL & SC_CTL_CDLV_Msk) >> SC_CTL_CDLV_Pos);

    if(sc == SC0 && u32CardStateIgnore[0] == 1)
        return TRUE;
    else if(sc == SC1 && u32CardStateIgnore[1] == 1)
        return TRUE;
    else if(cond1 != cond2)
        return FALSE;
    else
        return TRUE;
}

/**
  * @brief      Reset the Tx/Rx FIFO
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    This function reset both transmit and receive FIFO of specified smartcard module.
  */
void SC_ClearFIFO(SC_T *sc)
{
    sc->ALTCTL |= (SC_ALTCTL_TXRST_Msk | SC_ALTCTL_RXRST_Msk);
}

/**
  * @brief      Disable specified Smartcard
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    SC will force all transition to IDLE state.
  */
void SC_Close(SC_T *sc)
{
    sc->INTEN = 0;
    while(sc->PINCTL & SC_PINCTL_SYNC_Msk);
    sc->PINCTL = 0;
    sc->ALTCTL = 0;
    while(sc->CTL & SC_CTL_SYNC_Msk);
    sc->CTL = 0;
}

/**
  * @brief      Initialized Smartcard
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32CD   Card detect polarity, select the SC_CD pin state which indicates card insert. Could be:
  *                         -\ref SC_PIN_STATE_HIGH
  *                         -\ref SC_PIN_STATE_LOW
  *                         -\ref SC_PIN_STATE_IGNORE, no card detect pin, always assumes card present.
  * @param[in]  u32PWR  Power on polarity, select the SC_PWR pin state which could set smartcard VCC to high level. Could be:
  *                         -\ref SC_PIN_STATE_HIGH
  *                         -\ref SC_PIN_STATE_LOW
  *
  * @return     None
  *
  * @details    Initialization process configures smartcard and enables engine clock.
  */
void SC_Open(SC_T *sc, uint32_t u32CD, uint32_t u32PWR)
{
    uint32_t u32Reg = 0, u32Intf;

    if(sc == SC0)
        u32Intf = 0;
    else if(sc == SC1)
        u32Intf = 1;
    else
        return ;

    if(u32CD != SC_PIN_STATE_IGNORE)
    {
        u32Reg = u32CD ? 0 : SC_CTL_CDLV_Msk;
        u32CardStateIgnore[u32Intf] = 0;
    }
    else
    {
        u32CardStateIgnore[u32Intf] = 1;
    }
    while(sc->PINCTL & SC_PINCTL_SYNC_Msk);
    sc->PINCTL = u32PWR ? 0 : SC_PINCTL_PWRINV_Msk;

    while(sc->CTL & SC_CTL_SYNC_Msk);
    sc->CTL = SC_CTL_SCEN_Msk | u32Reg;
}

/**
  * @brief      Reset specified Smartcard
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    Reset the Tx/Rx FIFO, clock and initial default parameter.
  */
void SC_ResetReader(SC_T *sc)
{
    uint32_t u32Intf;

    if(sc == SC0)
        u32Intf = 0;
    else if(sc == SC1)
        u32Intf = 1;
    else
        return ;

    /* Reset FIFO, enable auto de-activation while card removal */
    sc->ALTCTL |= (SC_ALTCTL_TXRST_Msk | SC_ALTCTL_RXRST_Msk | SC_ALTCTL_ADACEN_Msk);
    /* Set Rx trigger level to 1 character, longest card detect debounce period, disable error retry (EMV ATR does not use error retry) */
    while(sc->CTL & SC_CTL_SYNC_Msk);
    sc->CTL &= ~(SC_CTL_RXTRGLV_Msk | SC_CTL_CDDBSEL_Msk | SC_CTL_TXRTY_Msk | SC_CTL_RXRTY_Msk);
    /* Enable auto convention, and all three smartcard internal timers */
    sc->CTL |= SC_CTL_AUTOCEN_Msk | SC_CTL_TMRSEL_Msk;
    /* Disable Rx time-out */
    sc->RXTOUT = 0;
    /* 372 clocks per ETU by default */
    sc->ETUCTL = 371;

    /* Enable necessary interrupt for smartcard operation */
    if(u32CardStateIgnore[u32Intf])   // Do not enable card detect interrupt if card present state ignore
    {
        sc->INTEN = (SC_INTEN_RDAIEN_Msk |
                     SC_INTEN_TERRIEN_Msk |
                     SC_INTEN_TMR0IEN_Msk |
                     SC_INTEN_TMR1IEN_Msk |
                     SC_INTEN_TMR2IEN_Msk |
                     SC_INTEN_BGTIEN_Msk |
                     SC_INTEN_ACERRIEN_Msk);
    }
    else
    {
        sc->INTEN = (SC_INTEN_RDAIEN_Msk |
                     SC_INTEN_TERRIEN_Msk |
                     SC_INTEN_TMR0IEN_Msk |
                     SC_INTEN_TMR1IEN_Msk |
                     SC_INTEN_TMR2IEN_Msk |
                     SC_INTEN_BGTIEN_Msk |
                     SC_INTEN_ACERRIEN_Msk |
                     SC_INTEN_CDIEN_Msk);
    }

    return;
}

/**
  * @brief      Set Block Guard Time
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32BGT  Block guard time using ETU as unit, valid range are between 1 ~ 32.
  *
  * @return     None
  *
  * @details    This function is used to configure block guard time (BGT) of specified smartcard module.
  */
void SC_SetBlockGuardTime(SC_T *sc, uint32_t u32BGT)
{
    sc->CTL = (sc->CTL & ~SC_CTL_BGT_Msk) | ((u32BGT - 1) << SC_CTL_BGT_Pos);
}

/**
  * @brief      Set Character Guard Time
  *
  * @param[in]  sc      The pointer of smartcard module.
  * @param[in]  u32CGT  Character guard time using ETU as unit, valid range are between 11 ~ 267.
  *
  * @return     None
  *
  * @details    This function is used to configure character guard time (CGT) of specified smartcard module.
  * @note       Before using this API, user should set the correct stop bit length first.
  */
void SC_SetCharGuardTime(SC_T *sc, uint32_t u32CGT)
{
    /* CGT is "START bit" + "8-bits" + "Parity bit" + "STOP bit(s)" + "EGT counts" */
    u32CGT -= (sc->CTL & SC_CTL_NSB_Msk) ? 11 : 12;
    sc->EGT = u32CGT;
}

/**
  * @brief      Stop all Timer Counting
  *
  * @param[in]  sc      The pointer of smartcard module.
  *
  * @return     None
  *
  * @details    This function stop all smartcard timer of specified smartcard module.
  * @note       This function stop the timers within smartcard module, \b not timer module.
  */
void SC_StopAllTimer(SC_T *sc)
{
    sc->ALTCTL &= ~(SC_ALTCTL_CNTEN0_Msk | SC_ALTCTL_CNTEN1_Msk | SC_ALTCTL_CNTEN2_Msk);
}

/**
  * @brief      Configure and Start specified Timer
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32TimerCh  Specify time channel to start. Valid values are 0, 1, 2.
  * @param[in]  u32Mode     Timer operating mode, valid values are:
  *                             - \ref SC_TMR_MODE_0
  *                             - \ref SC_TMR_MODE_1
  *                             - \ref SC_TMR_MODE_2
  *                             - \ref SC_TMR_MODE_3
  *                             - \ref SC_TMR_MODE_4
  *                             - \ref SC_TMR_MODE_5
  *                             - \ref SC_TMR_MODE_6
  *                             - \ref SC_TMR_MODE_7
  *                             - \ref SC_TMR_MODE_8
  *                             - \ref SC_TMR_MODE_F
  * @param[in]  u32ETUCount Timer timeout duration, ETU based. For timer 0, valid  range are between 1 ~ 0x1000000 ETUs.
  *                         For timer 1 and timer 2, valid range are between 1 ~ 0x100 ETUs.
  *
  * @return     None
  *
  * @details    Enable Timer starting, counter will count when condition match.
  * @note       This function start the timer within smartcard module, \b not timer module.
  * @note       Depend on the timer operating mode, timer may not start counting immediately.
  */
void SC_StartTimer(SC_T *sc, uint32_t u32TimerCh, uint32_t u32Mode, uint32_t u32ETUCount)
{
    uint32_t reg = u32Mode | (SC_TMRCTL0_CNT_Msk & (u32ETUCount - 1));

    if(u32TimerCh == 0)         // timer 0
    {
        sc->TMRCTL0 = reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN0_Msk;
    }
    else if(u32TimerCh == 1)    // timer 1
    {
        sc->TMRCTL1 = reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN1_Msk;
    }
    else                        // timer 2
    {
        sc->TMRCTL2 = reg;
        sc->ALTCTL |= SC_ALTCTL_CNTEN2_Msk;
    }
}

/**
  * @brief      Stop specified Timer Counting
  *
  * @param[in]  sc          The pointer of smartcard module.
  * @param[in]  u32TimerCh  Specify timer channel to stop. Valid values are 0, 1, 2.
  *
  * @return     None
  *
  * @details    This function stop a smartcard timer of specified smartcard module.
  * @note       This function stop the timer within smartcard module, \b not timer module.
  */
void SC_StopTimer(SC_T *sc, uint32_t u32TimerCh)
{
    if(u32TimerCh == 0)         // timer 0
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN0_Msk;
    else if(u32TimerCh == 1)    // timer 1
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN1_Msk;
    else                        // timer 2
        sc->ALTCTL &= ~SC_ALTCTL_CNTEN2_Msk;
}

/**
  * @brief      Gets Smartcard Clock Frequency
  *
  * @param[in]  sc          The pointer of smartcard module.
  *
  * @return     Smartcard frequency in kHZ.
  */
uint32_t SC_GetInterfaceClock(SC_T *sc)
{
    uint32_t u32ClkSrc, u32Num, u32Clk;

    if(sc == SC0)
        u32Num = 0;
    else if(sc == SC1)
        u32Num = 1;
    else
        u32Num = 2;

    u32ClkSrc = (CLK->CLKSEL3 >> (2 * u32Num)) & CLK_CLKSEL3_SC0SEL_Msk;

    // Get smartcard module clock
    if(u32ClkSrc == 0)
        u32Clk = __HXT;
    else if(u32ClkSrc == 1)
        u32Clk = CLK_GetPLLClockFreq();
    else if(u32ClkSrc == 2)
    {
        SystemCoreClockUpdate();
        if(CLK->CLKSEL0 & CLK_CLKSEL0_PCLK1SEL_Msk)
            u32Clk = SystemCoreClock >> 1;
        else
            u32Clk = SystemCoreClock;
    }
    else
        u32Clk = __HIRC;


    u32Clk /= (((CLK->CLKDIV1 >> (8 * u32Num)) & CLK_CLKDIV1_SC0DIV_Msk) + 1) * 1000;
    return u32Clk;
}

/*@}*/ /* end of group SC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
