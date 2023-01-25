/**************************************************************************//**
 * @file     CLK.h
 * @version  V1.0
 * $Revision  1 $
 * $Date: 14/07/01 1:13p $
 * @brief    NUC505 CLK Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __CLK_H__
#define __CLK_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_CLK_Driver CLK Driver
  @{
*/


/** @addtogroup NUC505_CLK_EXPORTED_CONSTANTS CLK Exported Constants
@{
*/
#define FREQ_96MHZ              96000000
#define FREQ_64MHZ              64000000
#define FREQ_24MHZ              24000000
#define FREQ_12MHZ              12000000
#define FREQ_6MHZ               6000000
#define FREQ_1MHZ               1000000

#define CLK_APLL_49142000           0xD542          /*!< APLL Operation Frequency for 8k, 12k, 16k, 24k, 32k, 48k and 96k sampling rate. In fact, the output clock is 49142857  \hideinitializer */
#define CLK_APLL_45142000           0xD382          /*!< APLL Operation Frequency for 11025, 22050 and 44100 sampling rate sampling rate. In fact, the output clock is 45142857  \hideinitializer*/
#define CLK_APLL_49142857           0xD542          /*!< APLL Operation Frequency for 8k, 12k, 16k, 24k, 32k, 48k and 96k sampling rate  \hideinitializer */
#define CLK_APLL_45142857           0xD382          /*!< APLL Operation Frequency for 11025, 22050 and 44100 sampling rate sampling rate  \hideinitializer*/
#define CLK_APLL_49152031           0x424D542       /*!< APLL Operation Frequency for 8k, 12k, 16k, 24k, 32k, 48k and 96k sampling rate  \hideinitializer */
#define CLK_APLL_45158425           0x704D382       /*!< APLL Operation Frequency for 11025, 22050 and 44100 sampling rate sampling rate  \hideinitializer*/



#define MINIMUM_PLL                         48000000
#define CLK_AHBCLK_PCLKCKEN_Pos     31
/*---------------------------------------------------------------------------------------------------------*/
/*  PLLCTL constant definitions. PLL = FIN * NF / NR / NO                                                  */
/*---------------------------------------------------------------------------------------------------------*/

#if (__HXT == 12000000)

#endif /* */
/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV0_HCLK(x)     (((x)-1) << CLK_CLKDIV0_HCLKDIV_Pos)    /*!< CLKDIV Setting for HCLK clock divider. It could be 1~16  \hideinitializer */
#define CLK_CLKDIV0_PCLK(x)     (((x)-1) << CLK_CLKDIV0_PCLKDIV_Pos)    /*!< CLKDIV Setting for PCLK clock divider. It could be 1~16   \hideinitializer */
#define CLK_CLKDIV0_USBD(x)     (((x)-1) << CLK_CLKDIV0_USBDDIV_Pos)    /*!< CLKDIV Setting for USBD clock divider. It could be 1~32  \hideinitializer */
#define CLK_CLKDIV0_USBH(x)     (((x)-1) << CLK_CLKDIV0_USBHDIV_Pos)    /*!< CLKDIV Setting for USBH clock divider. It could be 1~16  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV1_ADC(x)      (((x)-1) << CLK_CLKDIV1_ADCDIV_Pos)     /*!< CLKDIV Setting for ADC clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV1_STICK(x)    (((x)-1) << CLK_CLKDIV1_STICKDIV_Pos)   /*!< CLKDIV Setting for STICK clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV1_SDH(x)      (((x)-1) << CLK_CLKDIV1_SDHDIV_Pos)     /*!< CLKDIV Setting for SDH clock divider. It could be 1~2048  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV2_I2S(x)      (((x)-1) << CLK_CLKDIV2_I2SDIV_Pos)     /*!< CLKDIV Setting for SC4 clock divider. It could be 1~256  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV3_UART0(x)    (((x)-1) << CLK_CLKDIV3_UART0DIV_Pos)   /*!< CLKDIV Setting for UART0 clock divider. It could be 1~16  \hideinitializer */
#define CLK_CLKDIV3_UART1(x)    (((x)-1) << CLK_CLKDIV3_UART1DIV_Pos)   /*!< CLKDIV Setting for UART1 clock divider. It could be 1~16  \hideinitializer */
#define CLK_CLKDIV3_UART2(x)    (((x)-1) << CLK_CLKDIV3_UART2DIV_Pos)   /*!< CLKDIV Setting for UART2 clock divider. It could be 1~16  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV4 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV4_TMR0(x)     (((x)-1) << CLK_CLKDIV4_TMR0DIV_Pos)    /*!< CLKDIV Setting for TMR0 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV4_TMR1(x)     (((x)-1) << CLK_CLKDIV4_TMR1DIV_Pos)    /*!< CLKDIV Setting for TMR1 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV4_TMR2(x)     (((x)-1) << CLK_CLKDIV4_TMR2DIV_Pos)    /*!< CLKDIV Setting for TMR2 clock divider. It could be 1~256  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV5 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_CLKDIV5_TMR3(x)     (((x)-1) << CLK_CLKDIV5_TMR3DIV_Pos)    /*!< CLKDIV Setting for TMR3 clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV5_WDT(x)        (((x)-1) << CLK_CLKDIV5_WDTDIV_Pos)     /*!< CLKDIV Setting for WDT clock divider. It could be 1~256  \hideinitializer */
#define CLK_CLKDIV5_PWM(x)        (((x)-1) << CLK_CLKDIV5_PWMDIV_Pos)     /*!< CLKDIV Setting for PWM clock divider. It could be 1~256  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV0 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_HCLK_SRC_EXT        (0x00UL<<CLK_CLKDIV0_HCLKSEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_HCLK_SRC_PLL        (0x01UL<<CLK_CLKDIV0_HCLKSEL_Pos)             /*!< Setting clock source as PLL  \hideinitializer */
#define CLK_USBD_SRC_EXT        (0x00UL<<CLK_CLKDIV0_USBDSEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_USBD_SRC_PLL        (0x01UL<<CLK_CLKDIV0_USBDSEL_Pos)             /*!< Setting clock source as PLL  \hideinitializer */
#define CLK_USBH_SRC_PLL        (0x01UL<<CLK_CLKDIV0_USBHSEL_Pos)             /*!< Setting clock source as PLL  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV1 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_SDH_SRC_EXT     (0x00UL<<CLK_CLKDIV1_SDHSEL_Pos)              /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_SDH_SRC_PLL     (0x01UL<<CLK_CLKDIV1_SDHSEL_Pos)              /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_STICK_SRC_EXT       (0x00UL<<SysTick_CTRL_CLKSOURCE_Pos)        /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_STICK_SRC_HCLK      (0x01UL<<SysTick_CTRL_CLKSOURCE_Pos)        /*!< Setting clock source as HCLK  \hideinitializer */
#define CLK_ADC_SRC_EXT         (0x00UL<<CLK_CLKDIV1_ADCSEL_Pos)              /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_ADC_SRC_PLL         (0x01UL<<CLK_CLKDIV1_ADCSEL_Pos)              /*!< Setting clock source as PLL   \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV2 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_SPI0_SRC_EXT        (0x00UL<<CLK_CLKDIV2_SPI0SEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_SPI0_SRC_PLL        (0x01UL<<CLK_CLKDIV2_SPI0SEL_Pos)             /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_SPI1_SRC_EXT        (0x00UL<<CLK_CLKDIV2_SPI1SEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_SPI1_SRC_PLL        (0x01UL<<CLK_CLKDIV2_SPI1SEL_Pos)             /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_I2S_SRC_EXT         (0x00UL<<CLK_CLKDIV2_I2SSEL_Pos)              /*!< Setting clock source as EXT      \hideinitializer */
#define CLK_I2S_SRC_PLL         (0x01UL<<CLK_CLKDIV2_I2SSEL_Pos)              /*!< Setting clock source as PLL      \hideinitializer */
#define CLK_I2S_SRC_APLL        (0x03UL<<CLK_CLKDIV2_I2SSEL_Pos)              /*!< Setting clock source as APLL     \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV3 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_UART0_SRC_EXT       (0x00UL<<CLK_CLKDIV3_UART0SEL_Pos)            /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_UART0_SRC_PLL       (0x01UL<<CLK_CLKDIV3_UART0SEL_Pos)            /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_UART1_SRC_EXT       (0x00UL<<CLK_CLKDIV3_UART1SEL_Pos)            /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_UART1_SRC_PLL       (0x01UL<<CLK_CLKDIV3_UART1SEL_Pos)            /*!< Setting clock source as PLL   \hideinitializer */
#define CLK_UART2_SRC_EXT       (0x00UL<<CLK_CLKDIV3_UART2SEL_Pos)            /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_UART2_SRC_PLL       (0x01UL<<CLK_CLKDIV3_UART2SEL_Pos)            /*!< Setting clock source as PLL   \hideinitializer */
/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV4 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_TMR0_SRC_RTC        (0x00UL<<CLK_CLKDIV4_TMR0SEL_Pos)             /*!< Setting clock source as RTC   \hideinitializer */
#define CLK_TMR0_SRC_EXT        (0x01UL<<CLK_CLKDIV4_TMR0SEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_TMR1_SRC_RTC        (0x00UL<<CLK_CLKDIV4_TMR1SEL_Pos)             /*!< Setting clock source as RTC   \hideinitializer */
#define CLK_TMR1_SRC_EXT        (0x01UL<<CLK_CLKDIV4_TMR1SEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_TMR2_SRC_RTC        (0x00UL<<CLK_CLKDIV4_TMR2SEL_Pos)             /*!< Setting clock source as RTC   \hideinitializer */
#define CLK_TMR2_SRC_EXT        (0x01UL<<CLK_CLKDIV4_TMR2SEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  CLKDIV5 constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define CLK_TMR3_SRC_RTC        (0x00UL<<CLK_CLKDIV5_TMR3SEL_Pos)             /*!< Setting clock source as RTC   \hideinitializer */
#define CLK_TMR3_SRC_EXT        (0x01UL<<CLK_CLKDIV5_TMR3SEL_Pos)             /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_WDT_SRC_RTC         (0x00UL<<CLK_CLKDIV5_WDTSEL_Pos)              /*!< Setting clock source as RTC   \hideinitializer */
#define CLK_WDT_SRC_EXT         (0x01UL<<CLK_CLKDIV5_WDTSEL_Pos)              /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_PWM_SRC_EXT         (0x00UL<<CLK_CLKDIV5_PWMSEL_Pos)              /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_PWM_SRC_PLL         (0x01UL<<CLK_CLKDIV5_PWMSEL_Pos)              /*!< Setting clock source as PLL   \hideinitializer */

//#define CLK_I2C0_SRC_     (Clock source and divider in IP internal)
//#define CLK_I2C1_SRC_     (Clock source and divider in IP internal)
//#define CLK_RTC_SRC_      (Clock source and divider in IP internal)
#define CLK_SYSTICK_SRC_EXT     (0x00UL<<SysTick_CTRL_CLKSOURCE_Pos)      /*!< Setting clock source as EXT   \hideinitializer */
#define CLK_SYSTICK_SRC_PLL     (0x01UL<<SysTick_CTRL_CLKSOURCE_Pos)      /*!< Setting clock source as PLL   \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  MODULE constant definitions.                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define MODULE_AHPBCLK(x)                  ((x >>30) & 0x3)                     /*!< Calculate AHBCLK/APBCLK offset address on MODULE index  \hideinitializer */
#define MODULE_CLKSEL(x)                   ((x >>27) & 0x7)                     /*!< Calculate CLKSEL offset address on MODULE index  \hideinitializer */
#define MODULE_CLKSEL_Msk(x)               ((1<<((x >>22) & 0x1F))-1)   /*!< Calculate CLKSEL mask offset on MODULE index  \hideinitializer */
#define MODULE_CLKSEL_Pos(x)               ((x >>17) & 0x1f)                  /*!< Calculate CLKSEL position offset on MODULE index  \hideinitializer */
#define MODULE_CLKDIV(x)                   ((x >>14) & 0x7)                     /*!< Calculate CLKDIV position offset on MODULE index  \hideinitializer */
#define MODULE_CLKDIV_Msk(x)               ((1<<((x >>10) & 0xF))-1)    /*!< Calculate CLKDIV mask offset on MODULE index  \hideinitializer */
#define MODULE_CLKDIV_Pos(x)               ((x >>5 ) & 0x1f)                  /*!< Calculate CLKDIV mask bit position offset on MODULE index  \hideinitializer */
#define MODULE_IP_EN_Pos(x)                ((x >>0 ) & 0x1f)                    /*!< Calculate clock enable bit position on MODULE index  \hideinitializer */
#define MODULE_NoMsk                       0x0                                  /*!< Not mask on MODULE index  \hideinitializer */

/*--------------------------------------------------------------------------------------------------------------------------------------*/
/*   AHBCLK/APBCLK(2) | CLKSEL_OFFSET(3) | CLKSEL_Msk bit no(5) |    CLKSEL Bit Pos(5) | CLKDIV_OFFSET(3) | CLKDIV_Msk bit no(4)    | CLKDIV Bit Pos(5) |  IP_EN_Pos(5) */
/*  [31:30]                             [29:27]                     [26:22]                                 [21:17]                             [16:14]                         [13:10]                                         [9:5]                   [4:0]                 */
/*  CKEN OFFSET                             0: Meaning no clock select.                                     0: Meaning no clock divider                                                                 */
/*--------------------------------------------------------------------------------------------------------------------------------------*/
#define SRAM01_MODULE      ((0UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(00<<17)      |( 0<<14)|( MODULE_NoMsk<<10)   |( 0<<5)|CLK_AHBCLK_SRAM01CKEN_Pos)     /*!< SRAM01 Module  \hideinitializer */
#define SRAM23_MODULE      ((0UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(00<<17)      |( 0<<14)|( MODULE_NoMsk<<10)   |( 0<<5)|CLK_AHBCLK_SRAM23CKEN_Pos)   /*!< SRAM23 Module  \hideinitializer */
#define ROM_MODULE         ((0UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(00<<17)      |( 0<<14)|( MODULE_NoMsk<<10)   |( 0<<5)|CLK_AHBCLK_ROMCKEN_Pos)      /*!< ROM Module  \hideinitializer */
#define SPIM_MODULE        ((0UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(00<<17)      |( 0<<14)|( MODULE_NoMsk<<10)   |( 0<<5)|CLK_AHBCLK_SPIMCKEN_Pos)     /*!< SPIM Module  \hideinitializer */
#define SDH_MODULE         ((0UL<<30)|(01<<27)|(01<<22)                  |(30<<17)      |( 1<<14)|( 11<<10)                     |(16<<5)|CLK_AHBCLK_SDHCKEN_Pos)      /*!< SDH Module  \hideinitializer */

#define PCLK_MODULE        ((0UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(00<<17)      |( 0<<14)|(  4<<10)                     |(8<<5)|CLK_AHBCLK_PCLKCKEN_Pos)      /*!< USBD Module  \hideinitializer */
#define USBD_MODULE        ((0UL<<30)|(00<<27)|(01<<22)                  |(23<<17)      |( 0<<14)|(  5<<10)                     |(16<<5)|CLK_AHBCLK_USBDCKEN_Pos)     /*!< USBD Module  \hideinitializer */
#define USBH_MODULE        ((0UL<<30)|(00<<27)|(01<<22)                  |(30<<17)      |( 0<<14)|(  4<<10)                 |(24<<5)|CLK_AHBCLK_USBHCKEN_Pos)     /*!< USBH Module  \hideinitializer */

#define TMR0_MODULE        ((1UL<<30)|(04<<27)|(01<<22)                  |(24<<17)      |( 4<<14)|(  8<<10)                 |( 0<<5)|CLK_APBCLK_TMR0CKEN_Pos)     /*!< TMR0 Module  \hideinitializer */
#define TMR1_MODULE        ((1UL<<30)|(04<<27)|(01<<22)                  |(25<<17)      |( 4<<14)|(  8<<10)                 |( 8<<5)|CLK_APBCLK_TMR1CKEN_Pos)     /*!< TMR1 Module  \hideinitializer */
#define TMR2_MODULE        ((1UL<<30)|(04<<27)|(01<<22)                  |(26<<17)      |( 4<<14)|(  8<<10)                 |(16<<5)|CLK_APBCLK_TMR2CKEN_Pos)     /*!< TMR2 Module  \hideinitializer */
#define TMR3_MODULE        ((1UL<<30)|(05<<27)|(01<<22)                  |(24<<17)      |( 5<<14)|(  8<<10)                 |( 0<<5)|CLK_APBCLK_TMR3CKEN_Pos)     /*!< TMR3 Module  \hideinitializer */
#define WDT_MODULE         ((1UL<<30)|(05<<27)|(01<<22)                  |(25<<17)      |( 5<<14)|(  8<<10)                 |( 8<<5)|CLK_APBCLK_WDTCKEN_Pos)      /*!< WDT Module  \hideinitializer */

#define I2C0_MODULE        ((1UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(0<<17)           |( 0<<14)|(  MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK_I2C0CKEN_Pos)     /*!< I2C0 Module  \hideinitializer */
#define I2C1_MODULE        ((1UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(0<<17)           |( 0<<14)|(  MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK_I2C1CKEN_Pos)     /*!< I2C1 Module  \hideinitializer */
#define RTC_MODULE         ((1UL<<30)|(00<<27)|(MODULE_NoMsk<<22)|(0<<17)           |( 0<<14)|(  MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK_RTCCKEN_Pos)      /*!< RTC Module  \hideinitializer */
#define PWM_MODULE         ((1UL<<30)|(05<<27)|(01<<22)                  |(26<<17)      |( 5<<14)|(  8<<10)                     |( 16<<5)|CLK_APBCLK_PWMCKEN_Pos)     /*!< PWM Module  \hideinitializer */

#define SPI0_MODULE        ((1UL<<30)|(02<<27)|(01<<22)                  |(28<<17)      |( 0<<14)|(  MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK_SPI0CKEN_Pos)     /*!< SPI0 Module  \hideinitializer */
#define SPI1_MODULE        ((1UL<<30)|(02<<27)|(01<<22)                  |(29<<17)      |( 0<<14)|(  MODULE_NoMsk<<10)|( 0<<5)|CLK_APBCLK_SPI1CKEN_Pos)     /*!< SPI1 Module  \hideinitializer */


#define UART0_MODULE       ((1UL<<30)|(03<<27)|(01<<22)                  |(04<<17)      |( 3<<14)|(  4<<10)                 |( 0<<5)|CLK_APBCLK_UART0CKEN_Pos)    /*!< UART0 Module  \hideinitializer */
#define UART1_MODULE       ((1UL<<30)|(03<<27)|(01<<22)                  |(12<<17)      |( 3<<14)|(  4<<10)                 |( 8<<5)|CLK_APBCLK_UART1CKEN_Pos)    /*!< UART1 Module  \hideinitializer */
#define UART2_MODULE       ((1UL<<30)|(03<<27)|(01<<22)                  |(20<<17)      |( 3<<14)|(  4<<10)                 |(16<<5)|CLK_APBCLK_UART2CKEN_Pos)    /*!< UART2 Module  \hideinitializer */

#define I2S_MODULE           ((1UL<<30)|(02<<27)|(02<<22)                    |(24<<17)      |( 2<<14)|(  8<<10)                 |( 0<<5)|CLK_APBCLK_I2SCKEN_Pos)      /*!< I2S Module  \hideinitializer */
#define ADC_MODULE           ((1UL<<30)|(01<<27)|(01<<22)                    |(28<<17)      |( 1<<14)|(  8<<10)                 |( 0<<5)|CLK_APBCLK_ADCCKEN_Pos)      /*!< ADC Module  \hideinitializer */
/*@}*/ /* end of group NUC505_CLK_EXPORTED_CONSTANTS */

/** @addtogroup NUC505_CLK_EXPORTED_FUNCTIONS CLK Exported Functions
  @{
*/


#define CLK_SET_APLL(x)                                         (CLK->APLLCTL = x)                                                                                                  /*!< This macro sets APLL control register \hideinitializer */
#define CLK_APLL_ENABLE_POWERDOWN()                 (CLK->APLLCTL |= CLK_APLLCTL_PD_Msk)                                                                /*!< This macro sets APLL power down                \hideinitializer */
#define CLK_PLL_ENABLE_POWERDOWN()                  (CLK->PLLCTL |= CLK_PLLCTL_PD_Msk)                                                              /*!< This macro sets PLL power down                 \hideinitializer */
#define CLK_APLL_DISABLE_POWERDOWN()                (CLK->APLLCTL &= ~CLK_APLLCTL_PD_Msk)                                                               /*!< This macro sets APLL in operation state            \hideinitializer */
#define CLK_PLL_DISABLE_POWERDOWN()                 (CLK->PLLCTL &= ~CLK_PLLCTL_PD_Msk)                                                             /*!< This macro sets PLL in operation state             \hideinitializer */

#define CLK_SET_AHBCLK(x)                                           (CLK->AHBCLK = x)                                                                                               /*!< This macro enables/disables AHB IPs clock                  \hideinitializer */
#define CLK_SET_APBCLK(x)                                           (CLK->APBCLK = x)                                                                                               /*!< This macro enables/disables APB IPs clock                      \hideinitializer */
#define CLK_GET_AHBCLK(x)                                           (CLK->AHBCLK)                                                                                                       /*!< This macro gets AHB IPs clock                  \hideinitializer */
#define CLK_GET_APBCLK(x)                                           (CLK->APBCLK)                                                                                                       /*!< This macro gets APB IPs clock                  \hideinitializer */

#define CLK_SET_WAKEUP_PRESCALAR(x)                     (CLK->PWRCTL  = (CLK->PWRCTL &~CLK_PWRCTL_PDWKPSC_Msk) | (x<<8))        /*!< This macro sets pre-scalar for chip waiting for clock stable as power down wake up         \hideinitializer */
#define CLK_ENABLE_WAKEUP_PRESCALAR()                   (CLK->PWRCTL  |= CLK_PWRCTL_HXTCTL_Msk)                                                         /*!< This macro enable pre-scalar for clock stable \hideinitializer */
#define CLK_DISABLE_WAKEUP_PRESCALAR()              (CLK->PWRCTL  &= ~CLK_PWRCTL_HXTCTL_Msk)                                                      /*!< This macro disable pre-scalar for clock stable \hideinitializer */


void CLK_PowerDown(void);
void CLK_Idle(void);
uint32_t CLK_GetHXTFreq(void);
uint32_t CLK_GetHCLKFreq(void);
uint32_t CLK_GetPCLKFreq(void);
uint32_t CLK_GetCPUFreq(void);
uint32_t CLK_GetPLLClockFreq(void);
uint32_t CLK_GetAPLLClockFreq(void);
uint32_t CLK_SetCoreClock(uint32_t u32Hclk);
void CLK_SetHCLK(uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetModuleClock(uint32_t u32ModuleIdx, uint32_t u32ClkSrc, uint32_t u32ClkDiv);
void CLK_SetSysTickClockSrc(uint32_t u32ClkSrc);

void CLK_EnableModuleClock(uint32_t u32ModuleIdx);
void CLK_DisableModuleClock(uint32_t u32ModuleIdx);
uint32_t CLK_EnablePLL(uint32_t u32PllClkSrc, uint32_t u32PllFreq);
void CLK_DisablePLL(void);
void CLK_SysTickDelay(uint32_t us);
void CLK_EnableSysTick(uint32_t u32ClkSrc, uint32_t u32Count);
void CLK_DisableSysTick(void);
/*@}*/ /* end of group NUC505_CLK_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_CLK_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__CLK_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
