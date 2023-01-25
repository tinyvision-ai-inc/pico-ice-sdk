/**************************************************************************//**
 * @file        spim.c
 * @version     V1.00
 * $Revision:   1$
 * $Date:       14/07/10 5:00p$
 * @brief       NUC505 series SPIM driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC505Series.h"

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SPIM_Driver SPIM Driver
  @{
*/

/** @addtogroup NUC505_SPIM_EXPORTED_FUNCTIONS SPIM Exported Functions
  @{
*/

/**
  * @brief                      This function makes SPIM module be ready to transfer.
  * @param[in]  spim            Base address of SPIM module.
  * @param[in]  u32SPIMode      Ignored. Fill with 0.
  * @param[in]  u32BusClock     Expected frequency of SPI bus clock in Hz.
  * @return                     Actual frequency of SPI peripheral clock.
  * @note   SPI interface defaults to \ref SPIM_CTL1_IFSEL_INTERN. Call \ref SPIM_SetIF to change.
  * @note   If u32BusClock = 0, divider setting will be set to the maximum value.
  * @note   If u32BusClock >= SPI peripheral clock source, divider setting will be set to 0.
  * @note   If u32BusClock != 0, actual frequency will be the nearest to and not greater than u32BusClock.
  * @note   This function doesn't change system clock setting.
  */
uint32_t SPIM_Open(SPIM_T *spim, uint32_t u32SPIMode, uint32_t u32BusClock)
{
    (void)u32SPIMode;

#if 0   // User program will take care.
    CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk;     // Enable IP clock.
#endif

    SYS->IPRST1 |= SYS_IPRST1_SPIMRST_Msk;      // Reset IP.
    SYS->IPRST1 &= ~SYS_IPRST1_SPIMRST_Msk;

    SPIM_SetIF(spim, SPIM_CTL1_IFSEL_INTERN);

    return SPIM_SetBusClock(spim, u32BusClock);
}

/**
  * @brief                      Disable SPIM module.
  * @param[in]  spim            Base address of SPIM module.
  * @return                     None.
  * @details                    This function will reset SPIM module.
  */
void SPIM_Close(SPIM_T *spim)
{
    (void)spim;

#if 0   // User program will take care.
    if ((spim->CTL1 & SPIM_CTL1_IFSEL_Msk) == SPIM_CTL1_IFSEL_GPIO)
    {
        // Configure multi-function pins for GPIO.
        SYS->GPA_MFPH = SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA8MFP_Msk | (0 << SYS_GPA_MFPH_PA8MFP_Pos);    // GPIOA[8]
        SYS->GPA_MFPH = SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA9MFP_Msk | (0 << SYS_GPA_MFPH_PA9MFP_Pos);    // GPIOA[9]
        SYS->GPA_MFPH = SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA10MFP_Msk | (0 << SYS_GPA_MFPH_PA10MFP_Pos);  // GPIOA[10]
        SYS->GPA_MFPH = SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA11MFP_Msk | (0 << SYS_GPA_MFPH_PA11MFP_Pos);  // GPIOA[11]
        SYS->GPA_MFPH = SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA12MFP_Msk | (0 << SYS_GPA_MFPH_PA12MFP_Pos);  // GPIOA[12]
        SYS->GPA_MFPH = SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA13MFP_Msk | (0 << SYS_GPA_MFPH_PA13MFP_Pos);  // GPIOA[13]
    }
#endif

    SYS->IPRST1 |= SYS_IPRST1_SPIMRST_Msk;       // Reset IP.
    SYS->IPRST1 &= ~SYS_IPRST1_SPIMRST_Msk;

#if 0   // User program will take care.
    CLK->AHBCLK &= ~CLK_AHBCLK_SPIMCKEN_Msk;    // Disable IP clock.
#endif
}

/**
  * @brief                  Set SPI bus clock.
  * @param[in]  spim        Base address of SPIM module.
  * @param[in]  u32BusClock Expected frequency of SPI bus clock in Hz.
  * @return                 Actual frequency of SPI bus clock.
  * @note                   If u32BusClock = 0, divider will be set to the maximum value.
  * @note                   If u32BusClock >= SPI peripheral clock source, divider will be set to 0.
  * @note                   If u32BusClock != 0, actual frequency will be the nearest to and not greater than u32BusClock.
  * @note                   This function doesn't change system clock setting.
  */
uint32_t SPIM_SetBusClock(SPIM_T *spim, uint32_t u32BusClock)
{
    uint32_t u32Divider;

    if (u32BusClock)
    {
        u32Divider = SystemCoreClock / (u32BusClock * 2);
        if (u32Divider)
        {
            if (u32BusClock < (SystemCoreClock / (u32Divider * 2)))   // Not divisible.
            {
                u32Divider ++;
            }
        }
        else
        {
            if (u32BusClock < SystemCoreClock)    // SystemCoreClock x (1/2) < u32BusClock < SystemCoreClock
            {
                u32Divider ++;
            }
        }
    }
    else
    {
        u32Divider = 65535;
    }

    spim->CTL1 = (spim->CTL1 & (~SPIM_CTL1_DIVIDER_Msk)) | (u32Divider << SPIM_CTL1_DIVIDER_Pos);

    return SPIM_GetBusClock(spim);
}

/**
  * @brief              Get the actual frequency of SPI bus clock.
  * @param[in]  spim    Base address of SPIM module.
  * @return             Actual SPI bus clock frequency in Hz.
  */
uint32_t SPIM_GetBusClock(SPIM_T *spim)
{
    uint32_t u32Divider = ((spim->CTL1 & SPIM_CTL1_DIVIDER_Msk) >> SPIM_CTL1_DIVIDER_Pos);

    return u32Divider ? SystemCoreClock / (u32Divider * 2) : SystemCoreClock;
}

/**
  * @brief              Enable interrupt function.
  * @param[in]  spim    Base address of SPIM module.
  * @param[in]  u32Mask Combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt enable bit.
  *                     This parameter decides which interrupts will be enabled.
  *                     Valid values include:
  *                     - \ref SPIM_INT_MASK
  * @return             None.
  * @details            Enable SPIM related interrupts specified by u32Mask parameter.
  */
void SPIM_EnableInt(SPIM_T *spim, uint32_t u32Mask)
{
    // Enable the only one interrupt.
    if ((u32Mask & SPIM_INT_MASK) == SPIM_INT_MASK)
    {
        spim->CTL0 |= SPIM_CTL0_IEN_Msk;
    }
}

/**
  * @brief              Disable interrupt function.
  * @param[in]  spim    Base address of SPIM module.
  * @param[in]  u32Mask Combination of all related interrupt enable bits.
  *                     Each bit corresponds to a interrupt enable bit.
  *                     This parameter decides which interrupts will be enabled.
  *                     Valid values include:
  *                     - \ref SPIM_INT_MASK
  * @return             None.
  * @details            Disable SPIM related interrupts specified by u32Mask parameter.
  */
void SPIM_DisableInt(SPIM_T *spim, uint32_t u32Mask)
{
    // Disable the only one interrupt.
    if ((u32Mask & SPIM_INT_MASK) == SPIM_INT_MASK)
    {
        spim->CTL0 &= ~SPIM_CTL0_IEN_Msk;
    }
}

/**
  * @brief              Get interrupt flag.
  * @param[in]  spim    Base address of SPIM module.
  * @param[in]  u32Mask Combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be read.
  *                     Valid values include:
  *                     - \ref SPIM_INT_MASK
  * @return             Interrupt flags of selected sources.
  * @details            Get SPIM related interrupt flags specified by u32Mask parameter.
  */
uint32_t SPIM_GetIntFlag(SPIM_T *spim, uint32_t u32Mask)
{
    uint32_t u32IntFlag = 0;

    // Check the only one interrupt flag.
    if ((u32Mask & SPIM_INT_MASK) && (spim->CTL0 & SPIM_CTL0_IF_Msk))
    {
        u32IntFlag |= SPIM_INT_MASK;
    }

    return u32IntFlag;
}

/**
  * @brief                      This function specifies slave peripheral.
  * @param[in]  spim            Base address of SPIM module.
  * @param[in]  u32IFSel        Slave peripheral. Valid values include:
  *                             - \ref SPIM_CTL1_IFSEL_INTERN
  *                             - \ref SPIM_CTL1_IFSEL_EXTERN
  * @return                     None.
  */
void SPIM_SetIF(SPIM_T *spim, uint32_t u32IFSel)
{
    static uint32_t s_u32IFSelIntern = (uint32_t) -1;

    if (u32IFSel == SPIM_CTL1_IFSEL_MCP || u32IFSel == SPIM_CTL1_IFSEL_MCP64 || u32IFSel == SPIM_CTL1_IFSEL_INTERN)
    {
        if (s_u32IFSelIntern == (uint32_t) -1)
        {
            uint32_t u32JedecID;

            /* There are two interfaces for internal SPI Flash. Read JEDEC ID for check. */
            s_u32IFSelIntern = SPIM_CTL1_IFSEL_MCP;
            spim->CTL1 = (spim->CTL1 & ~SPIM_CTL1_IFSEL_Msk) | s_u32IFSelIntern;         // Set Slave Peripheral to MCP.

            /* Read JEDEC ID. */
            SPIM_SET_SS_LOW(SPIM);                                          // SS activated.
            SPIM_ENABLE_IO_MODE(SPIM, SPIM_CTL0_BITMODE_STAN, 1);           // I/O mode, 1-bit, output.
            SPIM_SET_DATA_WIDTH(SPIM, 8);
            SPIM_SET_BURST_NUM(SPIM, 1);
            SPIM_WRITE_TX0(SPIM, 0x9f);
            SPIM_TRIGGER(SPIM);
            while (SPIM_IS_BUSY(SPIM));                                     // Wait for ready.
            SPIM_SET_QDIODIR(SPIM, 0);                                      // Change I/O direction to input.
            SPIM_SET_DATA_WIDTH(SPIM, 24);
            SPIM_SET_BURST_NUM(SPIM, 1);
            SPIM_TRIGGER(SPIM);
            while (SPIM_IS_BUSY(SPIM));                                     // Wait for ready.
            u32JedecID = SPIM_READ_RX0(SPIM);
            u32JedecID &= 0x00FFFFFF;
            SPIM_SET_SS_HIGH(SPIM);                                         // SS deactivated.

            if (u32JedecID == 0x00000000 || u32JedecID == 0x00FFFFFF)
            {
                s_u32IFSelIntern = SPIM_CTL1_IFSEL_MCP64;
                spim->CTL1 = (spim->CTL1 & ~SPIM_CTL1_IFSEL_Msk) | s_u32IFSelIntern;   // Set Slave Peripheral MCP64.
            }
        }
        else
        {
            spim->CTL1 = (spim->CTL1 & ~SPIM_CTL1_IFSEL_Msk) | s_u32IFSelIntern;   // Set Slave Peripheral MCP/MCP64.
        }
    }

    if (u32IFSel == SPIM_CTL1_IFSEL_GPIO/* || u32IFSel == SPIM_CTL1_IFSEL_EXTERN*/)
    {
        spim->CTL1 = (spim->CTL1 & ~SPIM_CTL1_IFSEL_Msk) | SPIM_CTL1_IFSEL_GPIO;        // Set Slave Peripheral to GPIO.
    }
}

/**
  * @brief              Clear interrupt flag.
  * @param[in]  spim    Base address of SPIM module.
  * @param[in]  u32Mask Combination of all related interrupt sources.
  *                     Each bit corresponds to a interrupt source.
  *                     This parameter decides which interrupt flags will be cleared.
  *                     Valid values include:
  *                     - \ref SPIM_INT_MASK
  * @return             None.
  * @details            Clear SPIM related interrupt flags specified by u32Mask parameter.
  */
void SPIM_ClearIntFlag(SPIM_T *spim, uint32_t u32Mask)
{
    // Clear the only one interrupt flag.
    if (u32Mask & SPIM_INT_MASK)
    {
        spim->CTL0 |= SPIM_CTL0_IF_Msk;
    }
}

/**
  * @brief                      Write data to SPI Flash by DMA Write mode.
  * @param[in]  spim            Base address of SPIM module.
  * @param[in]  u32FlashAddr    Start Flash address to write. Must be word-aligned.
  * @param[in]  u32Len          Number of bytes to write. Must be word-aligned.
  * @param[in]  pu8TxBuf        Transmit buffer. Must be word-aligned.
  * @note                       This function doesn't handle cross-page range and just sends one Page Program command which requires address range be in a single page.
  * @note                       Non-blocking function call. Call \ref SPIM_IS_BUSY to check finish or not.
  * @return                     None.
  */
void SPIM_DMAWritePage(SPIM_T *spim, uint32_t u32FlashAddr, uint32_t u32Len, uint8_t *pu8TxBuf)
{
    /* Dependent on SPI flash chips, CS# Deselect Time (tSHSL) requires to be 10ns, 30ns, 50ns, or even 100ns.
     * Based on the formula below, choose a safe setting.
     * Deselect time interval of DMA write mode = (DWDELSEL + 1) * AHB clock cycle time */
    spim->RXCLKDLY = (spim->RXCLKDLY & ~SPIM_RXCLKDLY_DWDELSEL_Msk) | (0xF << SPIM_RXCLKDLY_DWDELSEL_Pos);

    spim->SRAMADDR = (uint32_t) pu8TxBuf;               // SRAM address.
    spim->DMATBCNT = u32Len;                            // Transfer length.
    spim->FADDR = u32FlashAddr;                         // Flash address.
    SPIM_TRIGGER(spim);                                 // Go.

    /* User must call SPIM_IS_BUSY to check finish or not. */
}

/**
  * @brief                      Read data from SPI Flash by DMA Read mode.
  * @param[in]  spim            Base address SPIM module.
  * @param[in]  u32FlashAddr    Start Flash address to read. Must be word-aligned.
  * @param[in]  u32Len          Number of bytes to read. Must be word-aligned.
  * @param[out] pu8RxBuf        Receive buffer. Must be word-aligned.
  * @note                       Non-blocking function call. Call \ref SPIM_IS_BUSY to check finish or not.
  * @return     None.
  */
void SPIM_DMAReadFlash(SPIM_T *spim, uint32_t u32FlashAddr, uint32_t u32Len, uint8_t *pu8RxBuf)
{
    spim->SRAMADDR = (uint32_t) pu8RxBuf;               // SRAM address.
    spim->DMATBCNT = u32Len;                            // Transfer length.
    spim->FADDR = u32FlashAddr;                         // Flash address.
    SPIM_TRIGGER(spim);                                 // Go.

    /* User must call SPIM_IS_BUSY to check finish or not. */
}

/*@}*/ /* end of group NUC505_SPIM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_SPIM_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
