/**************************************************************************//**
 * @file     clk.c
 * @version  V1.00
 * $Revision: 12 $
 * $Date: 14/07/01 1:13p $
 * @brief    NUC505 CLK driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "NUC505Series.h"

#include "clk.h"

typedef struct tagConstraint
{
    unsigned int u32NMin;
    unsigned int u32NMax;
    unsigned int u32FpdfMin;
} S_Constrait;
static S_Constrait pll_pfd_constraint[]=
{
    { 1, 1, 50.0, },
    { 2, 2, 35.0, },
    { 3, 3, 30.0, },
    { 4, 4, 25.0, },
    { 5, 5, 23.0, },
    { 6, 6, 21.0, },
    { 7, 7, 20.0, },
    { 8, 8, 19.0, },
    { 9, 9, 18.0, },
    { 10, 10, 17.0, },
    { 11, 11, 16.0, },
    { 12, 12, 16,/*15.5*/ },
    { 13, 13, 15.0, },
    { 14, 14, 15,/*14.5*/ },
    { 15, 15, 14.0, },
    { 16, 16, 14,/*13.5*/ },
    { 17, 17, 13.0, },
    { 18, 18, 13,/*12.5*/ },
    { 19, 19, 12.0, },

    { 20, 20, 12,/*11.5*/ },
    { 21, 21, 12,/*11.5,*/ },
    { 22, 22, 11.0, },
    { 23, 23, 11.0, },
    { 24, 24, 11,/*10.5*/ },
    { 25, 25, 11,/*10.5*/ },
    { 26, 26, 10.0, },
    { 27, 27, 10.0, },
    { 28, 28, 10,/*9.5*/ },
    { 29, 29, 10,/*9.5*/ },
    { 20, 32, 9.0, },
    { 33, 36, 9,/*8.5*/ },
    { 37, 40, 8.0, },
    { 41, 48, 8,/*7.5*/ },
    { 49, 56, 7.0, },
    { 57, 64, 7,/*6.5*/ },
    { 65, 80, 6.0, },
    { 81, 96, 6,/*5.5*/ },
    { 97, 128, 5.0 },
};
static int pllfreq_pdf_check(unsigned int N, unsigned int M, unsigned int Fin)
{
    uint32_t i, sel = 0;
    uint32_t Fpdf = (Fin/1000)/M;
    for(i=0; i<sizeof(pll_pfd_constraint)/sizeof(pll_pfd_constraint[0]); i=i+1)
    {
        if((N>=pll_pfd_constraint[i].u32NMin) && (N<=pll_pfd_constraint[i].u32NMax) )
        {
            sel = i;
            break;
        }
    }
    if(i>=sizeof(pll_pfd_constraint)/sizeof(pll_pfd_constraint[0]))
        return -1;

    if((Fpdf >= pll_pfd_constraint[sel].u32FpdfMin) && (Fpdf <= 80 ) )
        return 1;
    else
        return -1;
}

static uint32_t PLL_calculate(uint32_t u32Target)
{
    uint32_t u32M, u32N, u32P;
    uint32_t u32Fpll_clko;
    uint32_t u32Fvco;
    uint32_t u32Register, u32Fin=__HXT/1000;

    do
    {
#if 0 /* Much jitter */
        for(u32M =1 ; u32M<=64; u32M=u32M+1)
        {
            for(u32N=1 ; u32N<=128; u32N=u32N+1)
            {
                for(u32P =1 ; u32P<=8; u32P=u32P+1)
                {
#else /* Less jitter */
        for(u32P =8 ; u32P>=1; u32P=u32P-1)
        {
            for(u32N=1 ; u32N<=128; u32N=u32N+1)
            {
                for(u32M =1 ; u32M<=64; u32M=u32M+1)
                {
#endif
                    u32Fvco = u32Fin/u32M*u32N;
                    if((u32Fvco<300000))
                        continue;
                    if((u32Fvco>1000000))
                        continue;
                    if(pllfreq_pdf_check(u32N, u32M, u32Fin)<0)
                        continue;
                    u32Fpll_clko = (u32Fin/u32M)*u32N/u32P;
                    if( (u32Fpll_clko==u32Target) )
                    {
                        u32Register = ((u32P-1)<<13) | ((u32M-1)<<7) | ((u32N-1));
                        return u32Register;
                    }
                }
            }
        }
    }
    while(0);
    return 0;
}

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_CLK_Driver CLK Driver
  @{
*/


/** @addtogroup NUC505_CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/


/**
  * @brief                      Enter to Power-down mode
  * @return     None
  * @details                            This function let system enter to Power-down mode.
  */
void CLK_PowerDown(void)
{
    //SCB->SCR = SCB_SCR_SLEEPDEEP_Msk;
    //CLK->PWRCTL |= (CLK_PWRCTL_PDEN_Msk | CLK_PWRCTL_PDWKDLY_Msk );
    SCB->SCR |= 0x14;
    CLK->PWRCTL |= (CLK_PWRCTL_PDWKIF_Msk | CLK_PWRCTL_PDWKIEN_Msk | CLK_PWRCTL_PDWTCPU_Msk );
    //CLK->PWRCTL |= (CLK_PWRCTL_PDWKIF_Msk | CLK_PWRCTL_PDWTCPU_Msk );
    CLK->PWRCTL = CLK->PWRCTL & (~CLK_PWRCTL_HXTEN_Msk);                    /* Power down */
    __WFI();
}

/**
  * @brief                      Enter to Idle mode.
  * @return     None
  * @details                    This function let system enter to Idle mode.
  */
void CLK_Idle(void)
{
    /* Set the processor uses sleep as its low power mode */
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    /* Chip enter idle mode after CPU run WFI instruction */
    __WFI();
}


/**
  * @brief                      This function get PCLK frequency.
  * @return     PCLK frequency.
  * @details                    The frequency unit is Hz.
  */
uint32_t CLK_GetPCLKFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock/(((CLK->CLKDIV0 & CLK_CLKDIV0_PCLKDIV_Msk) >> CLK_CLKDIV0_PCLKDIV_Pos)+1);
}

/**
  * @brief                      The function is used to get external high speed crystal clock frequency.
  * @return                     External crystal frequency.
  * @details                    The frequency unit is Hz.
  */
uint32_t CLK_GetHXTFreq(void)
{
    if(CLK->PWRCTL & CLK_PWRCTL_HXTEN_Msk )
        return __HXT;
    else
        return 0;
}

/**
  * @brief                      The function is used to get HCLK frequency.
  * @return     HCLK frequency.
  * @details                    The frequency unit is Hz.
  */
uint32_t CLK_GetHCLKFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}

/**
  * @brief                      The function is used to get CPU frequency.
  * @return     CPU frequency.
  * @details                    The frequency unit is Hz.
  */
uint32_t CLK_GetCPUFreq(void)
{
    SystemCoreClockUpdate();
    return SystemCoreClock;
}

/**
  * @brief                      The function is used to set HCLK frequency.
  * @param[in]  u32Hclk         Specified HCLK frequency.
  * @return     HCLK frequency.
  * @details                    The frequency's unit is Hz. The range of u32Hclk is 1 MHz ~ 100 MHz.
  */
uint32_t CLK_SetCoreClock(uint32_t u32Hclk)
{
    uint32_t u32Register, u32DlyTime;
    uint32_t u32TarFreq = u32Hclk;

    u32Register = CLK->CLKDIV0 & ~(CLK_CLKDIV0_HCLKSEL_Msk | CLK_CLKDIV0_HCLKDIV_Msk);
    if(u32Hclk<=100000000) /*HCLK less than or equal to 100MHz*/
    {
        if(u32TarFreq<(MINIMUM_PLL/16))
        {
            if( (__HXT%u32TarFreq) == 0 )
                CLK->CLKDIV0 = u32Register | ((__HXT/u32TarFreq-1)&CLK_CLKDIV0_HCLKDIV_Msk);
            else
                CLK->CLKDIV0 = u32Register | ((__HXT/u32TarFreq)&CLK_CLKDIV0_HCLKDIV_Msk);
        }
        else
        {
            uint32_t div0;

            while(u32TarFreq<MINIMUM_PLL)
                u32TarFreq = u32TarFreq*2;
            div0 =  u32Register  | (u32TarFreq/u32Hclk-1);
            do
            {
                u32Register = PLL_calculate(u32TarFreq/1000);
                if(u32Register==0)
                    u32TarFreq = u32TarFreq-1000000;
            }
            while(u32Register==0);

            CLK->CLKDIV0 &= ~CLK_CLKDIV0_HCLKSEL_Msk;
            CLK->PLLCTL = u32Register;
            CLK->CLKDIV0 = div0;
            u32DlyTime = CLK_GetHXTFreq()/2000;     /* 500us/(1/(12MHz)) = 6000 */
            while(u32DlyTime>0)
            {
                u32DlyTime = u32DlyTime-1;
            }
            CLK->CLKDIV0 |= CLK_CLKDIV0_HCLKSEL_Msk;
        }

        /* Update System Core Clock */
        SystemCoreClockUpdate();
    }
    return SystemCoreClock;
}

/**
  * @brief                      This function specified HCLK clock source and HCLK clock divider.
  * @param[in]  u32ClkSrc         HCLK clock source. Including :
  *                             - \ref CLK_HCLK_SRC_EXT
  *                             - \ref CLK_HCLK_SRC_PLL
  * @param[in]  u32ClkDiv       HCLK clock divider. Including :
  *                             - \ref CLK_CLKDIV0_HCLK(x)
  * @return     None.
  */
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_HCLKDIV_Msk) | u32ClkDiv;
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_HCLKSEL_Msk) | u32ClkSrc;
    SystemCoreClockUpdate();
}


/**
  * @brief                      This function get PLL frequency. The frequency unit is Hz.
  * @return     PLL frequency.
  */
uint32_t CLK_GetPLLClockFreq(void)
{
    uint32_t u32Freq =0, u32PLLSrc;
    uint32_t u32PllReg, u32M,u32N,u32P;

    u32PLLSrc = __HXT;
    u32PllReg = CLK->PLLCTL;
    if((u32PllReg & CLK_PLLCTL_PD_Msk))
        return 0;
    u32M = ((u32PllReg&CLK_PLLCTL_INDIV_Msk)>>CLK_PLLCTL_INDIV_Pos)+1;
    u32N = ((u32PllReg&CLK_PLLCTL_FBDIV_Msk)>>CLK_PLLCTL_FBDIV_Pos)+1;
    u32P = ((u32PllReg&CLK_PLLCTL_OUTDIV_Msk)>>CLK_PLLCTL_OUTDIV_Pos)+1;
    u32Freq = (u32PLLSrc/u32M)*u32N/u32P;

    return u32Freq;
}

/**
  * @brief                      This function get APLL frequency. The frequency unit is Hz.
    * @param[in]  None
  * @return     APLL frequency.
    * @details
  */
uint32_t CLK_GetAPLLClockFreq(void)
{
    uint32_t u32Freq =0, u32PLLSrc;
    uint32_t u32PllReg, u32M,u32N,u32P;
    uint32_t u32Step, u32Frac;

    u32PLLSrc = __HXT;
    u32PllReg = CLK->APLLCTL;
    if((u32PllReg & CLK_APLLCTL_PD_Msk))
        return 0;
    u32M = ((u32PllReg&CLK_APLLCTL_INDIV_Msk)>>CLK_APLLCTL_INDIV_Pos)+1;
    u32N = ((u32PllReg&CLK_APLLCTL_FBDIV_Msk)>>CLK_APLLCTL_FBDIV_Pos)+1;
    u32P = ((u32PllReg&CLK_APLLCTL_OUTDIV_Msk)>>CLK_APLLCTL_OUTDIV_Pos)+1;
    u32Freq = (u32PLLSrc*u32N)/u32M/u32P;
    if(u32PllReg & CLK_APLLCTL_MODE_Pos)
    {
        u32Step = __HXT/u32M/4096/u32P;
        u32Frac = u32PllReg >> CLK_APLLCTL_FRAC_Pos;
        u32Freq = u32Freq + u32Step * u32Frac;
    }
    return u32Freq;
}
/**
  * @brief                      This function set selected module clock source and module clock divider
  * @param[in]  u32ModuleIdx      Module index.
  * @param[in]  u32ClkSrc         Module clock source.
  * @param[in]  u32ClkDiv         Module clock divider.
  * @return         None
  * @details        Valid parameter combinations listed in following table:
  *
  * |Module index          |Clock source                          |Divider                       |
  * | :------------------- | :-------------------------------     | :-------------------------   |
  * |\ref SRAM01_MODULE    | HCLK                                 | x                            |
  * |\ref SRAM23_MODULE    | HCLK                                 | x                            |
  * |\ref ROM_MODULE       | HCLK                                 | x                            |
  * |\ref SPIM_MODULE      | HCLK                                 | x                            |
  * |\ref SDH_MODULE       |\ref CLK_SDH_SRC_EXT                  |\ref CLK_CLKDIV1_SDH(x)       |
  * |\ref SDH_MODULE       |\ref CLK_SDH_SRC_PLL                  |\ref CLK_CLKDIV1_SDH(x)       |
  * |\ref USBD_MODULE      |\ref CLK_USBD_SRC_EXT                 |\ref CLK_CLKDIV0_USBD(x)      |
    * |\ref PCLK_MODULE      | x                                    |\ref CLK_CLKDIV0_PCLK(x)      |
  * |\ref USBD_MODULE      |\ref CLK_USBD_SRC_PLL                 |\ref CLK_CLKDIV0_USBD(x)      |
  * |\ref USBH_MODULE      |\ref CLK_USBH_SRC_PLL                 |\ref CLK_CLKDIV0_USBH(x)      |
  * |\ref TMR0_MODULE      |\ref CLK_TMR0_SRC_RTC                 |\ref CLK_CLKDIV4_TMR0(x)      |
  * |\ref TMR0_MODULE      |\ref CLK_TMR0_SRC_EXT                 |\ref CLK_CLKDIV4_TMR0(x)      |
  * |\ref TMR1_MODULE      |\ref CLK_TMR1_SRC_RTC                 |\ref CLK_CLKDIV4_TMR1(x)      |
  * |\ref TMR1_MODULE      |\ref CLK_TMR1_SRC_EXT                 |\ref CLK_CLKDIV4_TMR1(x)      |
  * |\ref TMR2_MODULE      |\ref CLK_TMR2_SRC_RTC                 |\ref CLK_CLKDIV4_TMR2(x)      |
  * |\ref TMR2_MODULE      |\ref CLK_TMR2_SRC_EXT                 |\ref CLK_CLKDIV4_TMR2(x)      |
  * |\ref WDT_MODULE       |\ref CLK_WDT_SRC_RTC                  |\ref CLK_CLKDIV5_WDT(x)       |
  * |\ref WDT_MODULE       |\ref CLK_WDT_SRC_EXT                    |\ref CLK_CLKDIV5_WDT(x)       |
  * |\ref I2C0_MODULE      | PCLK                                 | x                            |
  * |\ref I2C1_MODULE      | PCLK                                 | x                            |
  * |\ref RTC_MODULE       | x                                    | x                            |
    * |\ref PWM_MODULE       |\ref CLK_PWM_SRC_EXT                  |\ref CLK_CLKDIV5_PWM(x)       |
    * |\ref PWM_MODULE       |\ref CLK_PWM_SRC_PLL                  |\ref CLK_CLKDIV5_PWM(x)       |
    * |\ref SPI0_MODULE      |\ref CLK_SPI0_SRC_EXT                     | x                            |
    * |\ref SPI0_MODULE      |\ref CLK_SPI0_SRC_PLL                     | x                            |
    * |\ref SPI1_MODULE      |\ref CLK_SPI1_SRC_EXT                     | x                            |
    * |\ref SPI1_MODULE      |\ref CLK_SPI1_SRC_EXT                     | x                            |
  * |\ref UART0_MODULE     |\ref CLK_UART0_SRC_EXT                |\ref CLK_CLKDIV3_UART0(x)     |
  * |\ref UART0_MODULE     |\ref CLK_UART0_SRC_PLL                |\ref CLK_CLKDIV3_UART0(x)     |
  * |\ref UART1_MODULE     |\ref CLK_UART1_SRC_EXT                |\ref CLK_CLKDIV3_UART1(x)     |
  * |\ref UART1_MODULE     |\ref CLK_UART1_SRC_PLL                |\ref CLK_CLKDIV3_UART1(x)     |
  * |\ref UART2_MODULE     |\ref CLK_UART2_SRC_EXT                |\ref CLK_CLKDIV3_UART2(x)     |
  * |\ref UART2_MODULE     |\ref CLK_UART2_SRC_PLL                |\ref CLK_CLKDIV3_UART2(x)     |
  * |\ref I2S_MODULE       |\ref CLK_I2S_SRC_EXT                  |\ref CLK_CLKDIV2_I2S(x)       |
  * |\ref I2S_MODULE       |\ref CLK_I2S_SRC_PLL                  |\ref CLK_CLKDIV2_I2S(x)       |
  * |\ref I2S_MODULE       |\ref CLK_I2S_SRC_APLL                 |\ref CLK_CLKDIV2_I2S(x)       |
  * |\ref ADC_MODULE       |\ref CLK_ADC_SRC_EXT                  |\ref CLK_CLKDIV1_ADC(x)       |
  * |\ref ADC_MODULE       |\ref CLK_ADC_SRC_PLL                  |\ref CLK_CLKDIV1_ADC(x)       |
  *
  */

void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv)
{
    uint32_t u32tmp=0,u32sel=0,u32div=0;

    if(MODULE_CLKDIV_Msk(u32ModuleIdx)!=MODULE_NoMsk)
    {
        uint32_t u32DivOffset = MODULE_CLKDIV(u32ModuleIdx);
        if(u32DivOffset<4)
            u32div =(uint32_t)&CLK->CLKDIV0+(u32DivOffset)*4;       /* Get register address */
        else
            u32div =(uint32_t)&CLK->CLKDIV4+((u32DivOffset-4)*4);   /* Get register address */
        u32tmp = *(volatile uint32_t *)(u32div);                              /* Get register content value */

        u32tmp = ( u32tmp & ~(MODULE_CLKDIV_Msk(u32ModuleIdx)<<MODULE_CLKDIV_Pos(u32ModuleIdx)) ) | ((u32ClkDiv<<MODULE_CLKDIV_Pos(u32ModuleIdx) | (u32ClkSrc)));
        *(volatile uint32_t *)(u32div) = u32tmp;
    }

    if(MODULE_CLKSEL_Msk(u32ModuleIdx)!=MODULE_NoMsk)
    {
        uint32_t i32SelOffset = MODULE_CLKSEL(u32ModuleIdx);
        if(i32SelOffset<4)
            u32sel = (uint32_t)&CLK->CLKDIV0+(i32SelOffset*4);
        else
            u32sel = (uint32_t)&CLK->CLKDIV4+((i32SelOffset-4)*4);
        u32tmp = *(volatile uint32_t *)(u32sel);
        u32tmp = ( u32tmp & ~(MODULE_CLKSEL_Msk(u32ModuleIdx)<<MODULE_CLKSEL_Pos(u32ModuleIdx)) ) | u32ClkSrc;
        *(volatile uint32_t *)(u32sel) = u32tmp;
    }
}

/**
  * @brief                      This function enable module clock
  * @param[in]  u32ModuleIdx        Module index. Including :
  *                             - \ref SRAM01_MODULE
  *                             - \ref SRAM23_MODULE
  *                             - \ref ROM_MODULE
  *                             - \ref SPIM_MODULE
  *                             - \ref SDH_MODULE
  *                             - \ref PCLK_MODULE
  *                             - \ref USBD_MODULE
  *                             - \ref USBH_MODULE
  *                             - \ref TMR0_MODULE
  *                             - \ref TMR1_MODULE
  *                             - \ref TMR2_MODULE
  *                             - \ref TMR3_MODULE
  *                             - \ref WDT_MODULE
  *                             - \ref I2C0_MODULE
  *                             - \ref I2C1_MODULE
  *                             - \ref RTC_MODULE
  *                             - \ref PWM_MODULE
  *                             - \ref SPI0_MODULE
  *                             - \ref SPI1_MODULE
  *                             - \ref UART0_MODULE
  *                             - \ref UART1_MODULE
  *                             - \ref UART2_MODULE
  *                             - \ref I2S_MODULE
  *                             - \ref ADC_MODULE
  * @return     None
  */
void CLK_EnableModuleClock(uint32_t u32ModuleIdx)
{
    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK+(MODULE_AHPBCLK(u32ModuleIdx)*4))  |= 1<<MODULE_IP_EN_Pos(u32ModuleIdx);
}

/**
  * @brief                      This function disable module clock
  * @param[in]  u32ModuleIdx    Module index. Including :
  *                             - \ref SRAM01_MODULE
  *                             - \ref SRAM23_MODULE
  *                             - \ref ROM_MODULE
  *                             - \ref SPIM_MODULE
  *                             - \ref SDH_MODULE
  *                             - \ref PCLK_MODULE
  *                             - \ref USBD_MODULE
  *                             - \ref USBH_MODULE
  *                             - \ref TMR0_MODULE
  *                             - \ref TMR1_MODULE
  *                             - \ref TMR2_MODULE
  *                             - \ref TMR3_MODULE
  *                             - \ref WDT_MODULE
  *                             - \ref I2C0_MODULE
  *                             - \ref I2C1_MODULE
  *                             - \ref RTC_MODULE
  *                             - \ref PWM_MODULE
  *                             - \ref SPI0_MODULE
  *                             - \ref SPI1_MODULE
  *                             - \ref UART0_MODULE
  *                             - \ref UART1_MODULE
  *                             - \ref UART2_MODULE
  *                             - \ref I2S_MODULE
  *                             - \ref ADC_MODULE
  * @return     None
  */
void CLK_DisableModuleClock(uint32_t u32ModuleIdx)
{
    *(volatile uint32_t *)((uint32_t)&CLK->AHBCLK+(MODULE_AHPBCLK(u32ModuleIdx)*4))  &= ~(1<<MODULE_IP_EN_Pos(u32ModuleIdx));
}

/**
  * @brief                      This function set PLL frequency
  * @param[in]  u32PllClkSrc    PLL clock source. useless in NUC505 Series :
  * @param[in]  u32PllFreq      PLL frequency
  * @return         PLL frequency
  */
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq)
{
    uint32_t u32HclkDiv, u32Register;
    uint32_t u32CurrPll = CLK_GetPLLClockFreq();
    (void)u32PllClkSrc;
    u32HclkDiv = (CLK->CLKDIV0&CLK_CLKDIV0_HCLKDIV_Msk)+1;
    if( (u32PllFreq/u32HclkDiv)>100000000)
        return u32CurrPll;

    u32Register = PLL_calculate(u32PllFreq/1000);
    if(u32Register==0)
        return u32CurrPll;
    CLK->PLLCTL = u32Register;
    return CLK_GetPLLClockFreq();
}

/**
  * @brief                      This function disable PLL
  * @return     None
  */
void CLK_DisablePLL(void)
{
    CLK->PLLCTL |= CLK_PLLCTL_PD_Msk;
}

/**
  * @brief                      This function execute delay function.
  * @param[in]  us              Delay time. The Max value is 2^24 / CPU Clock(MHz). Ex:
  *                             50MHz => 335544us, 48MHz => 349525us, 28MHz => 699050us ...
  * @return     None
  * @details    Use the SysTick to generate the delay time and the UNIT is in us.
  *             The SysTick clock source is from HCLK, i.e the same as system core clock.
  */
void CLK_SysTickDelay(uint32_t us)
{
    SysTick->LOAD = us * CyclesPerUs;
    SysTick->VAL  =  (0x00);
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    /* Waiting for down-count to zero */
    if(us!=0)
        while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0);
}

/**
  * @brief                      This function set SysTick clock source
  * @param[in]  u32ClkSrc       SysTick clock source. Including :
  *                             - \ref CLK_SYSTICK_SRC_EXT
  *                             - \ref CLK_SYSTICK_SRC_PLL
  * @return         None
  */
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc)
{
    //CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_STCLKSEL_Msk) | u32ClkSrc ;
    SysTick->CTRL = (SysTick->CTRL & ~SysTick_CTRL_CLKSOURCE_Msk) | u32ClkSrc;
}

/**
  * @brief      Enable System Tick counter
  * @param[in]  u32ClkSrc   System Tick clock source. Including:
  *                         - \ref CLK_STICK_SRC_EXT
  *                         - \ref CLK_STICK_SRC_HCLK
  * @param[in]  u32Count    System Tick reload value. It could be 0~0xFFFFFF.
  * @return     None
  * @details    This function set System Tick clock source, reload value, enable System Tick counter and interrupt.
  *             The register write-protection function should be disabled before using this function.
  */
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count)
{
    /* Set System Tick counter disabled */
    SysTick->CTRL = 0;

    /* Set System Tick clock source */
    if( u32ClkSrc == CLK_STICK_SRC_HCLK )
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    else
        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;

    /* Set System Tick reload value */
    SysTick->LOAD = u32Count;

    /* Clear System Tick current value and counter flag */
    SysTick->VAL = 0;

    /* Set System Tick interrupt enabled and counter enabled */
    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief      Disable System Tick counter
  * @param      None
  * @return     None
  * @details    This function disable System Tick counter.
  */
void CLK_DisableSysTick(void)
{
    /* Set System Tick counter disabled */
    SysTick->CTRL = 0;
}

/*@}*/ /* end of group NUC505_CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_CLK_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

