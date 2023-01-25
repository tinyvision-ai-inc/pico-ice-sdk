/**************************************************************************//**
 * @file     uart.c
 * @version  V3.00
 * @brief    NUC121 series UART driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup UART_Driver UART Driver
  @{
*/


/** @addtogroup UART_EXPORTED_FUNCTIONS UART Exported Functions
  @{
*/

/**
 *    @brief        Clear UART specified interrupt flag
 *
 *    @param[in]    psUART              The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                      - \ref UART_INTSTS_LININT_Msk    : LIN bus interrupt
 *                                      - \ref UART_INTSTS_WKINT_Msk     : Wake-up interrupt
 *                                      - \ref UART_INTSTS_BUFERRINT_Msk : Buffer Error interrupt
 *                                      - \ref UART_INTSTS_MODEMINT_Msk  : Modem Status interrupt
 *                                      - \ref UART_INTSTS_RLSINT_Msk    : Receive Line Status interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to clear UART specified interrupt flag.
 */
void UART_ClearIntFlag(UART_T *psUART, uint32_t u32InterruptFlag)
{

    if (u32InterruptFlag & UART_INTSTS_RLSINT_Msk)      /* Clear Receive Line Status Interrupt */
        psUART->FIFOSTS = UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_ADDRDETF_Msk;

    if (u32InterruptFlag & UART_INTSTS_MODEMINT_Msk)    /* Clear Modem Status Interrupt */
        psUART->MODEMSTS |= UART_MODEMSTS_CTSDETF_Msk;

    if (u32InterruptFlag & UART_INTSTS_BUFERRINT_Msk)   /* Clear Buffer Error Interrupt */
        psUART->FIFOSTS = UART_FIFOSTS_RXOVIF_Msk | UART_FIFOSTS_TXOVIF_Msk;

    if (u32InterruptFlag & UART_INTSTS_WKINT_Msk)       /* Clear Wake-up Interrupt */
        psUART->WKSTS = psUART->WKSTS;

    if (u32InterruptFlag & UART_INTSTS_LININT_Msk)      /* Clear LIN Bus Interrupt */
    {
        psUART->INTSTS = UART_INTSTS_LINIF_Msk;
        psUART->LINSTS = psUART->LINSTS;
    }

}


/**
 *  @brief      Disable UART interrupt
 *
 *  @param[in]  psUART The pointer of the specified UART module.
 *
 *  @return     None
 *
 *  @details    The function is used to disable UART interrupt.
 */
void UART_Close(UART_T *psUART)
{
    psUART->INTEN = 0;
}


/**
 *  @brief      Disable UART auto flow control function
 *
 *  @param[in]  psUART The pointer of the specified UART module.
 *
 *  @return     None
 *
 *  @details    The function is used to disable UART auto flow control.
 */
void UART_DisableFlowCtrl(UART_T *psUART)
{
    psUART->INTEN &= ~(UART_INTEN_ATORTSEN_Msk | UART_INTEN_ATOCTSEN_Msk);
}


/**
 *    @brief        Disable UART specified interrupt
 *
 *    @param[in]    psUART              The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module.
 *                                      - \ref UART_INTEN_TXENDIEN_Msk   : Transmitter Empty interrupt
 *                                      - \ref UART_INTEN_ABRIEN_Msk     : Auto-baud Rate Interrupt
 *                                      - \ref UART_INTEN_LINIEN_Msk     : Lin Bus interrupt
 *                                      - \ref UART_INTEN_WKIEN_Msk      : Wake-up interrupt
 *                                      - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                                      - \ref UART_INTEN_RXTOIEN_Msk    : Rx Time-out interrupt
 *                                      - \ref UART_INTEN_MODEMIEN_Msk   : Modem Status interrupt
 *                                      - \ref UART_INTEN_RLSIEN_Msk     : Receive Line Status interrupt
 *                                      - \ref UART_INTEN_THREIEN_Msk    : Tx Empty interrupt
 *                                      - \ref UART_INTEN_RDAIEN_Msk     : Rx Ready interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to disable UART specified interrupt and disable NVIC UART IRQ.
 */
void UART_DisableInt(UART_T  *psUART, uint32_t u32InterruptFlag)
{
    /* Disable UART specified interrupt */
    UART_DISABLE_INT(psUART, u32InterruptFlag);

    /* Disable NVIC UART IRQ */
    NVIC_DisableIRQ(UART0_IRQn);

}

/**
 *    @brief        Enable UART auto flow control function
 *
 *    @param[in]    psUART    The pointer of the specified UART module.
 *
 *    @return       None
 *
 *    @details      The function is used to Enable UART auto flow control.
 */
void UART_EnableFlowCtrl(UART_T *psUART)
{
    /* Set RTS pin output is low level active */
    psUART->MODEM |= UART_MODEM_RTSACTLV_Msk;

    /* Set CTS pin input is low level active */
    psUART->MODEMSTS |= UART_MODEMSTS_CTSACTLV_Msk;

    /* Set RTS and CTS auto flow control enable */
    psUART->INTEN |= UART_INTEN_ATORTSEN_Msk | UART_INTEN_ATOCTSEN_Msk;
}


/**
 *    @brief        Enable UART specified interrupt
 *
 *    @param[in]    psUART              The pointer of the specified UART module.
 *    @param[in]    u32InterruptFlag    The specified interrupt of UART module:
 *                                      - \ref UART_INTEN_TXENDIEN_Msk   : Transmitter Empty interrupt
 *                                      - \ref UART_INTEN_ABRIEN_Msk     : Auto-baud Rate Interrupt
 *                                      - \ref UART_INTEN_LINIEN_Msk     : Lin Bus interrupt
 *                                      - \ref UART_INTEN_WKIEN_Msk      : Wake-up interrupt
 *                                      - \ref UART_INTEN_BUFERRIEN_Msk  : Buffer Error interrupt
 *                                      - \ref UART_INTEN_RXTOIEN_Msk    : Rx Time-out interrupt
 *                                      - \ref UART_INTEN_MODEMIEN_Msk   : Modem Status interrupt
 *                                      - \ref UART_INTEN_RLSIEN_Msk     : Receive Line Status interrupt
 *                                      - \ref UART_INTEN_THREIEN_Msk    : Tx Empty interrupt
 *                                      - \ref UART_INTEN_RDAIEN_Msk     : Rx Ready interrupt
 *
 *    @return       None
 *
 *    @details      The function is used to enable UART specified interrupt and enable NVIC UART IRQ.
 */
void UART_EnableInt(UART_T  *psUART, uint32_t u32InterruptFlag)
{

    /* Enable UART specified interrupt */
    UART_ENABLE_INT(psUART, u32InterruptFlag);

    /* Enable NVIC UART IRQ */
    NVIC_EnableIRQ(UART0_IRQn);

}


/**
 *    @brief        Open and set UART function
 *
 *    @param[in]    psUART          The pointer of the specified UART module.
 *    @param[in]    u32Baudrate     The baudrate of UART module.
 *
 *    @return       None
 *
 *    @details      This function use to enable UART function and set baud-rate.
 */
void UART_Open(UART_T *psUART, uint32_t u32Baudrate)
{
    uint8_t u8UartClkSrcSel, u8UartClkDivNum;
    uint32_t au32ClkTbl[4] = {__HXT, 0, __LXT, __HIRC_DIV2};
    uint32_t u32BaudDiv = 0;

    /* Get UART clock source selection */
    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

    /* Get UART clock divider number */
    u8UartClkDivNum = (CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos;

    /* Select UART function */
    psUART->FUNCSEL = UART_FUNCSEL_UART;

    /* Set UART line configuration */
    psUART->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;

    /* Set UART Rx and RTS trigger level */
    psUART->FIFO &= ~(UART_FIFO_RFITL_Msk | UART_FIFO_RTSTRGLV_Msk);

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if (u8UartClkSrcSel == 1)
        au32ClkTbl[u8UartClkSrcSel] = CLK_GetPLLClockFreq();

    /* Set UART baud rate */
    if (u32Baudrate != 0)
    {
        u32BaudDiv = UART_BAUD_MODE2_DIVIDER((au32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32Baudrate);

        if (u32BaudDiv > 0xFFFF)
            psUART->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER((au32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32Baudrate));
        else
            psUART->BAUD = (UART_BAUD_MODE2 | u32BaudDiv);
    }
}


/**
 *    @brief        Read UART data
 *
 *    @param[in]    psUART          The pointer of the specified UART module.
 *    @param[in]    pu8RxBuf        The buffer to receive the data of receive FIFO.
 *    @param[in]    u32ReadBytes    The the read bytes number of data.
 *
 *    @return       u32Count Receive byte count
 *
 *    @details      The function is used to read Rx data from RX FIFO and the data will be stored in pu8RxBuf.
 */
uint32_t UART_Read(UART_T *psUART, uint8_t *pu8RxBuf, uint32_t u32ReadBytes)
{
    uint32_t  u32Count, u32Delayno;

    for (u32Count = 0; u32Count < u32ReadBytes; u32Count++)
    {
        u32Delayno = 0;

        while (psUART->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)   /* Check RX empty => failed */
        {
            u32Delayno++;

            if (u32Delayno >= 0x40000000)
                return FALSE;
        }

        pu8RxBuf[u32Count] = psUART->DAT;    /* Get Data from UART RX  */
    }

    return u32Count;

}


/**
 *    @brief        Set UART line configuration
 *
 *    @param[in]    psUART          The pointer of the specified UART module.
 *    @param[in]    u32Baudrate     The register value of baudrate of UART module.
 *                                  If u32Baudrate = 0, UART baudrate will not change.
 *    @param[in]    u32DataWidth    The data length of UART module.
 *                                  - \ref UART_WORD_LEN_5
 *                                  - \ref UART_WORD_LEN_6
 *                                  - \ref UART_WORD_LEN_7
 *                                  - \ref UART_WORD_LEN_8
 *    @param[in]    u32Parity       The parity setting (none/odd/even/mark/space) of UART module.
 *                                  - \ref UART_PARITY_NONE
 *                                  - \ref UART_PARITY_ODD
 *                                  - \ref UART_PARITY_EVEN
 *                                  - \ref UART_PARITY_MARK
 *                                  - \ref UART_PARITY_SPACE
 *    @param[in]    u32StopBits     The stop bit length (1/1.5/2 bit) of UART module.
 *                                  - \ref UART_STOP_BIT_1
 *                                  - \ref UART_STOP_BIT_1_5
 *                                  - \ref UART_STOP_BIT_2
 *
 *    @return       None
 *
 *    @details      This function use to config UART line setting.
 */
void UART_SetLine_Config(UART_T *psUART, uint32_t u32Baudrate, uint32_t u32DataWidth, uint32_t u32Parity, uint32_t  u32StopBits)
{
    uint8_t u8UartClkSrcSel, u8UartClkDivNum;
    uint32_t au32ClkTbl[4] = {__HXT, 0, __LXT, __HIRC_DIV2};
    uint32_t u32Baud_Div = 0;

    /* Get UART clock source selection */
    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

    /* Get UART clock divider number */
    u8UartClkDivNum = (CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos;

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if (u8UartClkSrcSel == 1)
        au32ClkTbl[u8UartClkSrcSel] = CLK_GetPLLClockFreq();

    /* Set UART baud rate */
    if (u32Baudrate != 0)
    {
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER((au32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32Baudrate);

        if (u32Baud_Div > 0xFFFF)
            psUART->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER((au32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32Baudrate));
        else
            psUART->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);
    }

    /* Set UART line configuration */
    psUART->LINE = u32DataWidth | u32Parity | u32StopBits;
}


/**
 *    @brief        Set Rx timeout count
 *
 *    @param[in]    psUART  The pointer of the specified UART module.
 *    @param[in]    u32TOC  Rx timeout counter.
 *
 *    @return       None
 *
 *    @details      This function use to set Rx timeout count.
 */
void UART_SetTimeoutCnt(UART_T *psUART, uint32_t u32TOC)
{
    /* Set time-out interrupt comparator */
    psUART->TOUT = (psUART->TOUT & ~UART_TOUT_TOIC_Msk) | (u32TOC);

    /* Set time-out counter enable */
    psUART->INTEN |= UART_INTEN_TOCNTEN_Msk;
}


/**
 *    @brief        Select and configure IrDA function
 *
 *    @param[in]    psUART          The pointer of the specified UART module.
 *    @param[in]    u32Buadrate     The baudrate of UART module.
 *    @param[in]    u32Direction    The direction of UART module in IrDA mode:
 *                                  - \ref UART_IRDA_TXEN
 *                                  - \ref UART_IRDA_RXEN
 *
 *    @return       None
  *
 *    @details      The function is used to configure IrDA relative settings. It consists of TX or RX mode and baudrate.
 */
void UART_SelectIrDAMode(UART_T *psUART, uint32_t u32Buadrate, uint32_t u32Direction)
{
    uint8_t u8UartClkSrcSel, u8UartClkDivNum;
    uint32_t au32ClkTbl[4] = {__HXT, 0, __LXT, __HIRC_DIV2};
    uint32_t u32Baud_Div;

    /* Select IrDA function mode */
    psUART->FUNCSEL = UART_FUNCSEL_IrDA;

    /* Get UART clock source selection */
    u8UartClkSrcSel = (CLK->CLKSEL1 & CLK_CLKSEL1_UARTSEL_Msk) >> CLK_CLKSEL1_UARTSEL_Pos;

    /* Get UART clock divider number */
    u8UartClkDivNum = (CLK->CLKDIV0 & CLK_CLKDIV0_UARTDIV_Msk) >> CLK_CLKDIV0_UARTDIV_Pos;

    /* Get PLL clock frequency if UART clock source selection is PLL */
    if (u8UartClkSrcSel == 1)
        au32ClkTbl[u8UartClkSrcSel] = CLK_GetPLLClockFreq();

    /* Set UART IrDA baud rate in mode 0 */
    if (u32Buadrate != 0)
    {
        u32Baud_Div = UART_BAUD_MODE0_DIVIDER((au32ClkTbl[u8UartClkSrcSel]) / (u8UartClkDivNum + 1), u32Buadrate);

        if (u32Baud_Div < 0xFFFF)
            psUART->BAUD = (UART_BAUD_MODE0 | u32Baud_Div);
    }

    /* Configure IrDA relative settings */
    if (u32Direction == UART_IRDA_RXEN)
    {
        psUART->IRDA |= UART_IRDA_RXINV_Msk;     //Rx signal is inverse
        psUART->IRDA &= ~UART_IRDA_TXEN_Msk;
    }
    else
    {
        psUART->IRDA &= ~UART_IRDA_TXINV_Msk;    //Tx signal is not inverse
        psUART->IRDA |= UART_IRDA_TXEN_Msk;
    }

}


/**
 *    @brief        Select and configure RS485 function
 *
 *    @param[in]    psUART      The pointer of the specified UART module.
 *    @param[in]    u32Mode     The operation mode(NMM/AUD/AAD).
 *                              - \ref UART_ALTCTL_RS485NMM_Msk
 *                              - \ref UART_ALTCTL_RS485AUD_Msk
 *                              - \ref UART_ALTCTL_RS485AAD_Msk
 *    @param[in]    u32Addr     The RS485 address.
 *
 *    @return       None
 *
 *    @details      The function is used to set RS485 relative setting.
 */
void UART_SelectRS485Mode(UART_T *psUART, uint32_t u32Mode, uint32_t u32Addr)
{
    /* Select UART RS485 function mode */
    psUART->FUNCSEL = UART_FUNCSEL_RS485;

    /* Set RS585 configuration */
    psUART->ALTCTL &= ~(UART_ALTCTL_RS485NMM_Msk | UART_ALTCTL_RS485AUD_Msk | UART_ALTCTL_RS485AAD_Msk | UART_ALTCTL_ADDRMV_Msk);
    psUART->ALTCTL |= (u32Mode | (u32Addr << UART_ALTCTL_ADDRMV_Pos));
}


/**
 *    @brief        Select and configure LIN function
 *
 *    @param[in]    psUART          The pointer of the specified UART module.
 *    @param[in]    u32Mode         The LIN direction :
 *                                  - \ref UART_ALTCTL_LINTXEN_Msk
 *                                  - \ref UART_ALTCTL_LINRXEN_Msk
 *    @param[in]    u32BreakLength  The breakfield length.
 *
 *    @return       None
 *
 *    @details      The function is used to set LIN relative setting.
 */
void UART_SelectLINMode(UART_T *psUART, uint32_t u32Mode, uint32_t u32BreakLength)
{
    /* Select LIN function mode */
    psUART->FUNCSEL = UART_FUNCSEL_LIN;

    /* Select LIN function setting : Tx enable, Rx enable and break field length */
    psUART->ALTCTL &= ~(UART_ALTCTL_LINTXEN_Msk | UART_ALTCTL_LINRXEN_Msk | UART_ALTCTL_BRKFL_Msk);
    psUART->ALTCTL |= (u32Mode | (u32BreakLength << UART_ALTCTL_BRKFL_Pos));
}


/**
 *    @brief        Write UART data
 *
 *    @param[in]    psUART          The pointer of the specified UART module.
 *    @param[in]    pu8TxBuf        The buffer to send the data to UART transmission FIFO.
 *    @param[out]   u32WriteBytes   The byte number of data.
 *
 *    @return       u32Count transfer byte count
 *
 *    @details      The function is to write data into TX buffer to transmit data by UART.
 */
uint32_t UART_Write(UART_T *psUART, uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    uint32_t  u32Count, u32Delayno;

    for (u32Count = 0; u32Count != u32WriteBytes; u32Count++)
    {
        u32Delayno = 0;

        while (psUART->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)  /* Check Tx Full */
        {
            u32Delayno++;

            if (u32Delayno >= 0x40000000)
                return FALSE;
        }

        psUART->DAT = pu8TxBuf[u32Count];    /* Send UART Data from buffer */
    }

    return u32Count;

}


/*@}*/ /* end of group UART_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group UART_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/



