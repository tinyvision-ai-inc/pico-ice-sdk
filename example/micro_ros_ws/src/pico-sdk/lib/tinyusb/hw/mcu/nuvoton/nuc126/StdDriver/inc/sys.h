/**************************************************************************//**
 * @file     SYS.h
 * @version  V3
 * $Revision: 18 $
 * $Date: 17/04/28 5:38p $
 * @brief    NUC126 series System Manager (SYS) driver header file
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SYS_H__
#define __SYS_H__


#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SYS_Driver SYS Driver
  @{
*/

/** @addtogroup SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_RST    ((0x0<<24)|SYS_IPRST0_PDMARST_Pos)      /*!< PDMA reset is one of the SYS_ResetModule parameter */
#define EBI_RST     ((0x0<<24)|SYS_IPRST0_EBIRST_Pos)       /*!< EBI reset is one of the SYS_ResetModule parameter */
#define HDIV_RST    ((0x0<<24)|SYS_IPRST0_HDIVRST_Pos)      /*!< HDIV reset is one of the SYS_ResetModule parameter */
#define CRC_RST     ((0x0<<24)|SYS_IPRST0_CRCRST_Pos)       /*!< CRC reset is one of the SYS_ResetModule parameter */

#define GPIO_RST    ((0x4<<24)|SYS_IPRST1_GPIORST_Pos)      /*!< GPIO reset is one of the SYS_ResetModule parameter */
#define TMR0_RST    ((0x4<<24)|SYS_IPRST1_TMR0RST_Pos)      /*!< TMR0 reset is one of the SYS_ResetModule parameter */
#define TMR1_RST    ((0x4<<24)|SYS_IPRST1_TMR1RST_Pos)      /*!< TMR1 reset is one of the SYS_ResetModule parameter */
#define TMR2_RST    ((0x4<<24)|SYS_IPRST1_TMR2RST_Pos)      /*!< TMR2 reset is one of the SYS_ResetModule parameter */
#define TMR3_RST    ((0x4<<24)|SYS_IPRST1_TMR3RST_Pos)      /*!< TMR3 reset is one of the SYS_ResetModule parameter */
#define I2C0_RST    ((0x4<<24)|SYS_IPRST1_I2C0RST_Pos)      /*!< I2C0 reset is one of the SYS_ResetModule parameter */
#define I2C1_RST    ((0x4<<24)|SYS_IPRST1_I2C1RST_Pos)      /*!< I2C1 reset is one of the SYS_ResetModule parameter */
#define SPI0_RST    ((0x4<<24)|SYS_IPRST1_SPI0RST_Pos)      /*!< SPI0 reset is one of the SYS_ResetModule parameter */
#define SPI1_RST    ((0x4<<24)|SYS_IPRST1_SPI1RST_Pos)      /*!< SPI1 reset is one of the SYS_ResetModule parameter */
#define UART0_RST   ((0x4<<24)|SYS_IPRST1_UART0RST_Pos)     /*!< UART0 reset is one of the SYS_ResetModule parameter */
#define UART1_RST   ((0x4<<24)|SYS_IPRST1_UART1RST_Pos)     /*!< UART1 reset is one of the SYS_ResetModule parameter */
#define UART2_RST   ((0x4<<24)|SYS_IPRST1_UART2RST_Pos)     /*!< UART2 reset is one of the SYS_ResetModule parameter */
#define PWM0_RST    ((0x4<<24)|SYS_IPRST1_PWM0RST_Pos)      /*!< PWM0 reset is one of the SYS_ResetModule parameter */
#define PWM1_RST    ((0x4<<24)|SYS_IPRST1_PWM1RST_Pos)      /*!< PWM1 reset is one of the SYS_ResetModule parameter */
#define ACMP01_RST  ((0x4<<24)|SYS_IPRST1_ACMP01RST_Pos)    /*!< ACMP01 reset is one of the SYS_ResetModule parameter */
#define USBD_RST    ((0x4<<24)|SYS_IPRST1_USBDRST_Pos)      /*!< USBD reset is one of the SYS_ResetModule parameter */
#define ADC_RST     ((0x4<<24)|SYS_IPRST1_ADCRST_Pos)       /*!< ADC reset is one of the SYS_ResetModule parameter */

#define SC0_RST     ((0x8<<24)|SYS_IPRST2_SC0RST_Pos)       /*!< SC0 reset is one of the SYS_ResetModule parameter */
#define SC1_RST     ((0x8<<24)|SYS_IPRST2_SC1RST_Pos)       /*!< SC1 reset is one of the SYS_ResetModule parameter */
#define USCI0_RST   ((0x8<<24)|SYS_IPRST2_USCI0RST_Pos)     /*!< USCI0 reset is one of the SYS_ResetModule parameter */
#define USCI1_RST   ((0x8<<24)|SYS_IPRST2_USCI1RST_Pos)     /*!< USCI1 reset is one of the SYS_ResetModule parameter */
#define USCI2_RST   ((0x8<<24)|SYS_IPRST2_USCI2RST_Pos)     /*!< USCI2 reset is one of the SYS_ResetModule parameter */


/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector Threshold Voltage Selection constant definitions.                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_BODCTL_BOD_RST_EN           (1UL<<SYS_BODCTL_BODRSTEN_Pos)    /*!< Brown-out Reset Enable */
#define SYS_BODCTL_BOD_INTERRUPT_EN     (0UL<<SYS_BODCTL_BODRSTEN_Pos)    /*!< Brown-out Interrupt Enable */
#define SYS_BODCTL_BODVL_4_5V           (3UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 4.5V */
#define SYS_BODCTL_BODVL_3_7V           (2UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 3.7V */
#define SYS_BODCTL_BODVL_2_7V           (1UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.7V */
#define SYS_BODCTL_BODVL_2_2V           (0UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.2V */


/*---------------------------------------------------------------------------------------------------------*/
/*  VREFCTL constant definitions. (Write-Protection Register)                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_VREFCTL_VREF_PIN        (0x0UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = Vref pin */
#define SYS_VREFCTL_VREF_2_56V      (0x3UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 2.56V */
#define SYS_VREFCTL_VREF_2_048V     (0x7UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 2.048V */
#define SYS_VREFCTL_VREF_3_072V     (0xBUL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 3.072V */
#define SYS_VREFCTL_VREF_4_096V     (0xFUL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 4.096V */
#define SYS_VREFCTL_VREF_AVDD       (0x10UL<<SYS_VREFCTL_VREFCTL_Pos)   /*!< Vref = AVDD */


/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/

/* How to use below #define?

Example: If user want to set PA.2 as UART0_TXD and PA.3 as UART0_RXD in initial function,
         user can issue following command to achieve it.

         SYS->GPA_MFPL = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA2MFP_Msk)) | SYS_GPA_MFPL_PA2MFP_UART0_TXD;
         SYS->GPA_MFPL = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA3MFP_Msk)) | SYS_GPA_MFPL_PA3MFP_UART0_RXD;
*/

//PA.0 MFP
#define SYS_GPA_MFPL_PA0MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for GPIO           */
#define SYS_GPA_MFPL_PA0MFP_UART1_nCTS      (0x1UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for UART1_nCTS     */
#define SYS_GPA_MFPL_PA0MFP_UART1_TXD       (0x3UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for UART1_TXD      */
#define SYS_GPA_MFPL_PA0MFP_USCI1_CTL0      (0x4UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for USCI1_CTL0     */
#define SYS_GPA_MFPL_PA0MFP_SC0_CLK         (0x5UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for SC0_CLK        */
#define SYS_GPA_MFPL_PA0MFP_PWM1_CH5        (0x6UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for PWM1_CH5       */
#define SYS_GPA_MFPL_PA0MFP_EBI_AD0         (0x7UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for EBI_AD0        */
#define SYS_GPA_MFPL_PA0MFP_INT0            (0x8UL<<SYS_GPA_MFPL_PA0MFP_Pos)    /*!< GPA_MFPL PA0 setting for INT0           */

//PA.1 MFP
#define SYS_GPA_MFPL_PA1MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for GPIO           */
#define SYS_GPA_MFPL_PA1MFP_UART1_nRTS      (0x1UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for UART1_nRTS     */
#define SYS_GPA_MFPL_PA1MFP_UART1_RXD       (0x3UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for UART1_RXD      */
#define SYS_GPA_MFPL_PA1MFP_USCI1_CTL1      (0x4UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for USCI1_CTL1     */
#define SYS_GPA_MFPL_PA1MFP_SC0_DAT         (0x5UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for SC0_DAT        */
#define SYS_GPA_MFPL_PA1MFP_PWM1_CH4        (0x6UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for PWM1_CH4       */
#define SYS_GPA_MFPL_PA1MFP_EBI_AD1         (0x7UL<<SYS_GPA_MFPL_PA1MFP_Pos)    /*!< GPA_MFPL PA1 setting for EBI_AD1        */

//PA.2 MFP
#define SYS_GPA_MFPL_PA2MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for GPIO           */
#define SYS_GPA_MFPL_PA2MFP_UART0_TXD       (0x2UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for UART0_TXD      */
#define SYS_GPA_MFPL_PA2MFP_UART0_nCTS      (0x3UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for UART0_nCTS     */
#define SYS_GPA_MFPL_PA2MFP_I2C0_SDA        (0x4UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for I2C0_SDA       */
#define SYS_GPA_MFPL_PA2MFP_SC0_RST         (0x5UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for SC0_RST        */
#define SYS_GPA_MFPL_PA2MFP_PWM1_CH3        (0x6UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for PWM1_CH3       */
#define SYS_GPA_MFPL_PA2MFP_EBI_AD2         (0x7UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for EBI_AD2        */
#define SYS_GPA_MFPL_PA2MFP_USCI1_CTL0      (0x8UL<<SYS_GPA_MFPL_PA2MFP_Pos)    /*!< GPA_MFPL PA2 setting for USCI1_CTL0     */

//PA.3 MFP
#define SYS_GPA_MFPL_PA3MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for GPIO           */
#define SYS_GPA_MFPL_PA3MFP_UART0_RXD       (0x2UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for UART0_RXD      */
#define SYS_GPA_MFPL_PA3MFP_UART0_nRTS      (0x3UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for UART0_nRTS     */
#define SYS_GPA_MFPL_PA3MFP_I2C0_SCL        (0x4UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for I2C0_SCL       */
#define SYS_GPA_MFPL_PA3MFP_SC0_PWR         (0x5UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for SC0_PWR        */
#define SYS_GPA_MFPL_PA3MFP_PWM1_CH2        (0x6UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for PWM1_CH2       */
#define SYS_GPA_MFPL_PA3MFP_EBI_AD3         (0x7UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for EBI_AD3        */
#define SYS_GPA_MFPL_PA3MFP_USCI1_CLK       (0x8UL<<SYS_GPA_MFPL_PA3MFP_Pos)    /*!< GPA_MFPL PA3 setting for USCI1_CLK      */

//PA.4 MFP
#define SYS_GPA_MFPL_PA4MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA4MFP_Pos)    /*!< GPA_MFPL PA4 setting for GPIO           */
#define SYS_GPA_MFPL_PA4MFP_SPI1_SS         (0x2UL<<SYS_GPA_MFPL_PA4MFP_Pos)    /*!< GPA_MFPL PA4 setting for SPI1_SS        */
#define SYS_GPA_MFPL_PA4MFP_TM3_EXT         (0x3UL<<SYS_GPA_MFPL_PA4MFP_Pos)    /*!< GPA_MFPL PA4 setting for TM3_EXT        */
#define SYS_GPA_MFPL_PA4MFP_EBI_AD4         (0x7UL<<SYS_GPA_MFPL_PA4MFP_Pos)    /*!< GPA_MFPL PA4 setting for EBI_AD4        */

//PA.5 MFP
#define SYS_GPA_MFPL_PA5MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA5MFP_Pos)    /*!< GPA_MFPL PA5 setting for GPIO           */
#define SYS_GPA_MFPL_PA5MFP_SPI1_MOSI       (0x2UL<<SYS_GPA_MFPL_PA5MFP_Pos)    /*!< GPA_MFPL PA5 setting for SPI1_MOSI      */
#define SYS_GPA_MFPL_PA5MFP_TM2_EXT         (0x3UL<<SYS_GPA_MFPL_PA5MFP_Pos)    /*!< GPA_MFPL PA5 setting for TM2_EXT        */
#define SYS_GPA_MFPL_PA5MFP_TM_BRAKE3       (0x6UL<<SYS_GPA_MFPL_PA5MFP_Pos)    /*!< GPA_MFPL PA5 setting for TM_BRAKE3      */
#define SYS_GPA_MFPL_PA5MFP_EBI_AD5         (0x7UL<<SYS_GPA_MFPL_PA5MFP_Pos)    /*!< GPA_MFPL PA5 setting for EBI_AD5        */

//PA.6 MFP
#define SYS_GPA_MFPL_PA6MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA6MFP_Pos)    /*!< GPA_MFPL PA6 setting for GPIO           */
#define SYS_GPA_MFPL_PA6MFP_SPI1_MISO       (0x2UL<<SYS_GPA_MFPL_PA6MFP_Pos)    /*!< GPA_MFPL PA6 setting for SPI1_MISO      */
#define SYS_GPA_MFPL_PA6MFP_TM1_EXT         (0x3UL<<SYS_GPA_MFPL_PA6MFP_Pos)    /*!< GPA_MFPL PA6 setting for TM1_EXT        */
#define SYS_GPA_MFPL_PA6MFP_TM_BRAKE2       (0x6UL<<SYS_GPA_MFPL_PA6MFP_Pos)    /*!< GPA_MFPL PA6 setting for TM_BRAKE2      */
#define SYS_GPA_MFPL_PA6MFP_EBI_AD6         (0x7UL<<SYS_GPA_MFPL_PA6MFP_Pos)    /*!< GPA_MFPL PA6 setting for EBI_AD6        */

//PA.7 MFP
#define SYS_GPA_MFPL_PA7MFP_GPIO            (0x0UL<<SYS_GPA_MFPL_PA7MFP_Pos)    /*!< GPA_MFPL PA7 setting for GPIO           */
#define SYS_GPA_MFPL_PA7MFP_SPI1_CLK        (0x2UL<<SYS_GPA_MFPL_PA7MFP_Pos)    /*!< GPA_MFPL PA7 setting for SPI1_CLK       */
#define SYS_GPA_MFPL_PA7MFP_TM0_EXT         (0x3UL<<SYS_GPA_MFPL_PA7MFP_Pos)    /*!< GPA_MFPL PA7 setting for TM0_EXT        */
#define SYS_GPA_MFPL_PA7MFP_TM_BRAKE1       (0x6UL<<SYS_GPA_MFPL_PA7MFP_Pos)    /*!< GPA_MFPL PA7 setting for TM_BRAKE1      */
#define SYS_GPA_MFPL_PA7MFP_EBI_AD7         (0x7UL<<SYS_GPA_MFPL_PA7MFP_Pos)    /*!< GPA_MFPL PA7 setting for EBI_AD7        */

//PA.8 MFP
#define SYS_GPA_MFPH_PA8MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for GPIO           */
#define SYS_GPA_MFPH_PA8MFP_CLKO            (0x1UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for CLKO           */
#define SYS_GPA_MFPH_PA8MFP_I2C1_SCL        (0x2UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for I2C1_SCL       */
#define SYS_GPA_MFPH_PA8MFP_UART1_TXD       (0x3UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for UART1_TXD      */
#define SYS_GPA_MFPH_PA8MFP_SC0_PWR         (0x4UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for SC0_PWR        */
#define SYS_GPA_MFPH_PA8MFP_SC1_RST         (0x5UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for SC1_RST        */
#define SYS_GPA_MFPH_PA8MFP_TM_BRAKE0       (0x6UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for TM_BRAKE0      */
#define SYS_GPA_MFPH_PA8MFP_PWM0_BRAKE0     (0x7UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for PWM0_BRAKE0    */
#define SYS_GPA_MFPH_PA8MFP_TM1             (0x8UL<<SYS_GPA_MFPH_PA8MFP_Pos)    /*!< GPA_MFPH PA8 setting for TM1            */

//PA.9 MFP
#define SYS_GPA_MFPH_PA9MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for GPIO           */
#define SYS_GPA_MFPH_PA9MFP_SPI1_I2SMCLK    (0x1UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for SPI1_I2SMCLK   */
#define SYS_GPA_MFPH_PA9MFP_I2C1_SDA        (0x2UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for I2C1_SDA       */
#define SYS_GPA_MFPH_PA9MFP_UART1_RXD       (0x3UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for UART1_RXD      */
#define SYS_GPA_MFPH_PA9MFP_SC0_RST         (0x4UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for SC0_RST        */
#define SYS_GPA_MFPH_PA9MFP_SC1_PWR         (0x5UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for SC1_PWR        */
#define SYS_GPA_MFPH_PA9MFP_TM_BRAKE1       (0x6UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for TM_BRAKE1      */
#define SYS_GPA_MFPH_PA9MFP_PWM1_BRAKE1     (0x7UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for PWM1_BRAKE1    */
#define SYS_GPA_MFPH_PA9MFP_TM2             (0x8UL<<SYS_GPA_MFPH_PA9MFP_Pos)    /*!< GPA_MFPH PA9 setting for TM2            */

//PA.10 MFP
#define SYS_GPA_MFPH_PA10MFP_GPIO           (0x0UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for GPIO          */
#define SYS_GPA_MFPH_PA10MFP_UART1_nCTS     (0x3UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for UART1_nCTS    */
#define SYS_GPA_MFPH_PA10MFP_SC1_DAT        (0x5UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for SC1_DAT       */

//PA.11 MFP
#define SYS_GPA_MFPH_PA11MFP_GPIO           (0x0UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for GPIO          */
#define SYS_GPA_MFPH_PA11MFP_UART1_nRTS     (0x3UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for UART1_nRTS    */
#define SYS_GPA_MFPH_PA11MFP_SC1_CLK        (0x5UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for SC1_CLK       */

//PA.12 MFP
#define SYS_GPA_MFPH_PA12MFP_GPIO           (0x0UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for GPIO          */
#define SYS_GPA_MFPH_PA12MFP_SPI1_I2SMCLK   (0x2UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for SPI1_I2SMCLK  */
#define SYS_GPA_MFPH_PA12MFP_UART2_RXD      (0x3UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for UART2_RXD     */
#define SYS_GPA_MFPH_PA12MFP_UART1_RXD      (0x4UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for UART1_RXD     */
#define SYS_GPA_MFPH_PA12MFP_TM_BRAKE2      (0x6UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for TM_BRAKE2     */

//PA.13 MFP
#define SYS_GPA_MFPH_PA13MFP_GPIO           (0x0UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for GPIO          */
#define SYS_GPA_MFPH_PA13MFP_UART2_TXD      (0x3UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for UART2_TXD     */
#define SYS_GPA_MFPH_PA13MFP_UART1_TXD      (0x4UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for UART1_TXD     */
#define SYS_GPA_MFPH_PA13MFP_TM_BRAKE3      (0x6UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA12 setting for TM_BRAKE3     */

//PA.14 MFP
#define SYS_GPA_MFPH_PA14MFP_GPIO           (0x0UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for GPIO          */
#define SYS_GPA_MFPH_PA14MFP_UART2_nCTS     (0x3UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for UART2_nCTS    */
#define SYS_GPA_MFPH_PA14MFP_USCI1_CTL1     (0x4UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for USCI1_CTL1    */
#define SYS_GPA_MFPH_PA14MFP_TM2            (0x6UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for TM2           */

//PA.15 MFP
#define SYS_GPA_MFPH_PA15MFP_GPIO           (0x0UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for GPIO          */
#define SYS_GPA_MFPH_PA15MFP_UART2_nRTS     (0x3UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for UART2_nRTS    */
#define SYS_GPA_MFPH_PA15MFP_USCI1_CLK      (0x4UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for USCI1_CLK     */
#define SYS_GPA_MFPH_PA15MFP_TM3            (0x6UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for TM3   */

//PB.0 MFP
#define SYS_GPB_MFPL_PB0MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for GPIO           */
#define SYS_GPB_MFPL_PB0MFP_ADC0_CH0        (0x1UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for ADC0_CH0       */
#define SYS_GPB_MFPL_PB0MFP_VDET_P0         (0x2UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for VDET_P0        */
#define SYS_GPB_MFPL_PB0MFP_UART2_RXD       (0x3UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for UART2_RXD      */
#define SYS_GPB_MFPL_PB0MFP_TM2             (0x4UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for TM2            */
#define SYS_GPB_MFPL_PB0MFP_USCI1_DAT0      (0x6UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for USCI1_DAT0     */
#define SYS_GPB_MFPL_PB0MFP_EBI_nWRL        (0x7UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for EBI_nWRL       */
#define SYS_GPB_MFPL_PB0MFP_INT1            (0x8UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for INT1           */
#define SYS_GPB_MFPL_PB0MFP_TM1_EXT         (0xAUL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for TM1_EXT        */

//PB.1 MFP
#define SYS_GPB_MFPL_PB1MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for GPIO           */
#define SYS_GPB_MFPL_PB1MFP_ADC0_CH1        (0x1UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for ADC0_CH1       */
#define SYS_GPB_MFPL_PB1MFP_VDET_P1         (0x2UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for VDET_P1        */
#define SYS_GPB_MFPL_PB1MFP_UART2_TXD       (0x3UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for UART2_TXD      */
#define SYS_GPB_MFPL_PB1MFP_TM3             (0x4UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for TM3            */
#define SYS_GPB_MFPL_PB1MFP_SC0_RST         (0x5UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for SC0_RST        */
#define SYS_GPB_MFPL_PB1MFP_PWM0_SYNC_OUT   (0x6UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for PWM0_SYNC_OUT  */
#define SYS_GPB_MFPL_PB1MFP_EBI_nWRH        (0x7UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for EBI_nWRH       */
#define SYS_GPB_MFPL_PB1MFP_USCI1_DAT1      (0x8UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for USCI1_DAT1     */

//PB.2 MFP
#define SYS_GPB_MFPL_PB2MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for GPIO           */
#define SYS_GPB_MFPL_PB2MFP_ADC0_CH2        (0x1UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for ADC0_CH2       */
#define SYS_GPB_MFPL_PB2MFP_SPI0_CLK        (0x2UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for SPI0_CLK       */
#define SYS_GPB_MFPL_PB2MFP_SPI1_CLK        (0x3UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for SPI1_CLK       */
#define SYS_GPB_MFPL_PB2MFP_UART1_RXD       (0x4UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for UART1_RXD      */
#define SYS_GPB_MFPL_PB2MFP_SC0_nCD         (0x5UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for SC0_nCD        */
#define SYS_GPB_MFPL_PB2MFP_TM_BRAKE0       (0x6UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for TM_BRAKE0      */
#define SYS_GPB_MFPL_PB2MFP_EBI_nCS0        (0x7UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for EBI_nCS0       */
#define SYS_GPB_MFPL_PB2MFP_USCI0_DAT0      (0x8UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for USCI0_DAT0     */
#define SYS_GPB_MFPL_PB2MFP_TM2_EXT         (0xAUL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for TM2_EXT        */

//PB.3 MFP
#define SYS_GPB_MFPL_PB3MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for GPIO           */
#define SYS_GPB_MFPL_PB3MFP_ADC0_CH3        (0x1UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for ADC0_CH3       */
#define SYS_GPB_MFPL_PB3MFP_SPI0_MISO       (0x2UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for SPI0_MISO      */
#define SYS_GPB_MFPL_PB3MFP_SPI1_MISO       (0x3UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for SPI1_MISO      */
#define SYS_GPB_MFPL_PB3MFP_UART1_TXD       (0x4UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for UART1_TXD      */
#define SYS_GPB_MFPL_PB3MFP_TM_BRAKE1       (0x6UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for TM_BRAKE1      */
#define SYS_GPB_MFPL_PB3MFP_EBI_ALE         (0x7UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for EBI_ALE        */
#define SYS_GPB_MFPL_PB3MFP_USCI0_DAT1      (0x8UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for USCI0_DAT1     */
#define SYS_GPB_MFPL_PB3MFP_TM0_EXT        (0xAUL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for TM0_EXT         */

//PB.4 MFP
#define SYS_GPB_MFPL_PB4MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for GPIO           */
#define SYS_GPB_MFPL_PB4MFP_ADC0_CH4        (0x1UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for ADC0_CH4       */
#define SYS_GPB_MFPL_PB4MFP_SPI0_SS         (0x2UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for SPI0_SS        */
#define SYS_GPB_MFPL_PB4MFP_SPI1_SS         (0x3UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for SPI1_SS        */
#define SYS_GPB_MFPL_PB4MFP_UART1_nCTS      (0x4UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for UART1_nCTS     */
#define SYS_GPB_MFPL_PB4MFP_ACMP0_N         (0x5UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for ACMP0_N        */
#define SYS_GPB_MFPL_PB4MFP_SC1_nCD         (0x6UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for SC1_nCD        */
#define SYS_GPB_MFPL_PB4MFP_EBI_AD7         (0x7UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for EBI_AD7        */
#define SYS_GPB_MFPL_PB4MFP_USCI0_CTL1      (0x8UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for USCI0_CTL1     */
#define SYS_GPB_MFPL_PB4MFP_UART2_RXD       (0x9UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for UART2_RXD      */
#define SYS_GPB_MFPL_PB4MFP_TM1_EXT         (0xAUL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for TM1_EXT        */

//PB.5 MFP
#define SYS_GPB_MFPL_PB5MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for GPIO           */
#define SYS_GPB_MFPL_PB5MFP_ADC0_CH13       (0x1UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for ADC0_CH13      */
#define SYS_GPB_MFPL_PB5MFP_SPI0_MOSI       (0x2UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for SPI0_MOSI      */
#define SYS_GPB_MFPL_PB5MFP_SPI1_MOSI       (0x3UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for SPI1_MOSI      */
#define SYS_GPB_MFPL_PB5MFP_ACMP0_P2        (0x5UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for ACMP0_P2       */
#define SYS_GPB_MFPL_PB5MFP_SC1_RST         (0x6UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for SC1_RST        */
#define SYS_GPB_MFPL_PB5MFP_EBI_AD6         (0x7UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for EBI_AD6        */
#define SYS_GPB_MFPL_PB5MFP_UART2_RXD       (0x9UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for UART2_RXD      */

//PB.6 MFP
#define SYS_GPB_MFPL_PB6MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for GPIO           */
#define SYS_GPB_MFPL_PB6MFP_ADC0_CH14       (0x1UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for ADC0_CH14      */
#define SYS_GPB_MFPL_PB6MFP_SPI0_MISO       (0x2UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for SPI0_MISO      */
#define SYS_GPB_MFPL_PB6MFP_SPI1_MISO       (0x3UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for SPI1_MISO      */
#define SYS_GPB_MFPL_PB6MFP_ACMP0_P1        (0x5UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for ACMP0_P1       */
#define SYS_GPB_MFPL_PB6MFP_SC1_PWR         (0x6UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for SC1_PWR        */
#define SYS_GPB_MFPL_PB6MFP_EBI_AD5         (0x7UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for EBI_AD5        */

//PB.7 MFP
#define SYS_GPB_MFPL_PB7MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for GPIO           */
#define SYS_GPB_MFPL_PB7MFP_ADC0_CH15       (0x1UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for ADC0_CH15      */
#define SYS_GPB_MFPL_PB7MFP_SPI0_CLK        (0x2UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for SPI0_CLK       */
#define SYS_GPB_MFPL_PB7MFP_SPI1_CLK        (0x3UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for SPI1_CLK       */
#define SYS_GPB_MFPL_PB7MFP_USCI2_CTL1      (0x4UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for USCI2_CTL1     */
#define SYS_GPB_MFPL_PB7MFP_ACMP0_P0        (0x5UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for ACMP0_P0       */
#define SYS_GPB_MFPL_PB7MFP_SC1_DAT         (0x6UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for SC1_DAT        */
#define SYS_GPB_MFPL_PB7MFP_EBI_AD4         (0x7UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for EBI_AD4        */

//PB.8 MFP
#define SYS_GPB_MFPH_PB8MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for GPIO           */
#define SYS_GPB_MFPH_PB8MFP_ADC0_CH5        (0x1UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for ADC0_CH5       */
#define SYS_GPB_MFPH_PB8MFP_UART1_nRTS      (0x4UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for UART1_nRTS     */
#define SYS_GPB_MFPH_PB8MFP_TM_BRAKE2       (0x5UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for TM_BRAKE2      */
#define SYS_GPB_MFPH_PB8MFP_PWM0_CH2        (0x6UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for PWM0_CH2       */
#define SYS_GPB_MFPH_PB8MFP_USCI0_CTL0      (0x8UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for USCI0_CTL0     */

//PB.9 MFP
#define SYS_GPB_MFPH_PB9MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for GPIO           */
#define SYS_GPB_MFPH_PB9MFP_ADC0_CH6        (0x1UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for ADC0_CH6       */
#define SYS_GPB_MFPH_PB9MFP_USCI0_CLK       (0x8UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for USCI0_CLK      */

//PB.10 MFP
#define SYS_GPB_MFPH_PB10MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB10MFP_Pos)   /*!< GPB_MFPH PB10 setting for GPIO          */
#define SYS_GPB_MFPH_PB10MFP_ADC0_CH7       (0x1UL<<SYS_GPB_MFPH_PB10MFP_Pos)   /*!< GPB_MFPH PB10 setting for ADC0_CH7      */

//PB.11 MFP
#define SYS_GPB_MFPH_PB11MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB11MFP_Pos)   /*!< GPB_MFPH PB11 setting for GPIO          */
#define SYS_GPB_MFPH_PB11MFP_ADC0_CH8       (0x1UL<<SYS_GPB_MFPH_PB11MFP_Pos)   /*!< GPB_MFPH PB11 setting for ADC0_CH8      */

//PB.12 MFP
#define SYS_GPB_MFPH_PB12MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB12MFP_Pos)   /*!< GPB_MFPH PB12 setting for GPIO          */
#define SYS_GPB_MFPH_PB12MFP_PWM1_CH1       (0x6UL<<SYS_GPB_MFPH_PB12MFP_Pos)   /*!< GPB_MFPH PB12 setting for PWM1_CH1      */

//PB.13MFP
#define SYS_GPB_MFPH_PB13MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB13MFP_Pos)   /*!< GPB_MFPH PB13 setting for GPIO          */
#define SYS_GPB_MFPH_PB13MFP_ADC0_CH10      (0x1UL<<SYS_GPB_MFPH_PB13MFP_Pos)   /*!< GPB_MFPH PB13 setting for ADC0_CH10     */

//PB.14 MFP
#define SYS_GPB_MFPH_PB14MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for GPIO          */
#define SYS_GPB_MFPH_PB14MFP_ADC0_CH11      (0x1UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for ADC0_CH11     */

//PB.15 MFP
#define SYS_GPB_MFPH_PB15MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for GPIO          */
#define SYS_GPB_MFPH_PB15MFP_ADC0_CH12      (0x1UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for ADC0_CH12     */
#define SYS_GPB_MFPH_PB15MFP_ACMP0_P3       (0x5UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for ACMP0_P3      */
#define SYS_GPB_MFPH_PB15MFP_EBI_nCS1       (0x7UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for EBI_nCS1      */

//PC.0 MFP
#define SYS_GPC_MFPL_PC0MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for GPIO           */
#define SYS_GPC_MFPL_PC0MFP_SC0_DAT         (0x1UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for SC0_DAT        */
#define SYS_GPC_MFPL_PC0MFP_SPI0_CLK        (0x2UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for SPI0_CLK       */
#define SYS_GPC_MFPL_PC0MFP_UART2_nCTS      (0x3UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for UART2_nCTS     */
#define SYS_GPC_MFPL_PC0MFP_USCI0_DAT0      (0x4UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for USCI0_DAT0     */
#define SYS_GPC_MFPL_PC0MFP_ACMP0_WLAT      (0x5UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for ACMP0_WLAT     */
#define SYS_GPC_MFPL_PC0MFP_PWM0_CH0        (0x6UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for PWM0_CH0       */
#define SYS_GPC_MFPL_PC0MFP_EBI_AD8         (0x7UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for EBI_AD8        */
#define SYS_GPC_MFPL_PC0MFP_INT2            (0x8UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for INT2           */

//PC.1 MFP
#define SYS_GPC_MFPL_PC1MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for GPIO           */
#define SYS_GPC_MFPL_PC1MFP_CLKO            (0x1UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for CLKO           */
#define SYS_GPC_MFPL_PC1MFP_SC0_CLK         (0x2UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for SC0_CLK        */
#define SYS_GPC_MFPL_PC1MFP_UART2_nRTS      (0x3UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for UART2_nRTS     */
#define SYS_GPC_MFPL_PC1MFP_USCI0_DAT1      (0x4UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for USCI0_DAT1     */
#define SYS_GPC_MFPL_PC1MFP_ACMP1_WLAT      (0x5UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for ACMP1_WLAT     */
#define SYS_GPC_MFPL_PC1MFP_PWM0_CH1        (0x6UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for PWM0_CH1       */
#define SYS_GPC_MFPL_PC1MFP_EBI_AD9         (0x7UL<<SYS_GPC_MFPL_PC1MFP_Pos)    /*!< GPC_MFPL PC1 setting for EBI_AD9        */

//PC.2 MFP
#define SYS_GPC_MFPL_PC2MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for GPIO           */
#define SYS_GPC_MFPL_PC2MFP_SC0_RST         (0x1UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for SC0_RST        */
#define SYS_GPC_MFPL_PC2MFP_SPI0_SS         (0x2UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for SPI0_SS        */
#define SYS_GPC_MFPL_PC2MFP_UART2_TXD       (0x3UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for UART2_TXD      */
#define SYS_GPC_MFPL_PC2MFP_USCI0_CTL1      (0x4UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for USCI0_CTL1     */
#define SYS_GPC_MFPL_PC2MFP_ACMP1_O         (0x5UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for ACMP1_O        */
#define SYS_GPC_MFPL_PC2MFP_PWM0_CH2        (0x6UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for PWM0_CH2       */
#define SYS_GPC_MFPL_PC2MFP_EBI_AD10        (0x7UL<<SYS_GPC_MFPL_PC2MFP_Pos)    /*!< GPC_MFPL PC2 setting for EBI_AD10       */

//PC.3 MFP
#define SYS_GPC_MFPL_PC3MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for GPIO           */
#define SYS_GPC_MFPL_PC3MFP_SC0_PWR         (0x1UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for SC0_PWR        */
#define SYS_GPC_MFPL_PC3MFP_SPI0_MOSI       (0x2UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for SPI0_MOSI      */
#define SYS_GPC_MFPL_PC3MFP_UART2_RXD       (0x3UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for UART2_RXD      */
#define SYS_GPC_MFPL_PC3MFP_USCI0_CTL0      (0x5UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for USCI0_CTL0     */
#define SYS_GPC_MFPL_PC3MFP_PWM0_CH3        (0x6UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for PWM0_CH3       */
#define SYS_GPC_MFPL_PC3MFP_EBI_AD11        (0x7UL<<SYS_GPC_MFPL_PC3MFP_Pos)    /*!< GPC_MFPL PC3 setting for EBI_AD11       */

//PC.4 MFP
#define SYS_GPC_MFPL_PC4MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for GPIO           */
#define SYS_GPC_MFPL_PC4MFP_SC0_nCD         (0x1UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for SC0_nCD        */
#define SYS_GPC_MFPL_PC4MFP_SPI0_MISO       (0x2UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for SPI0_MISO      */
#define SYS_GPC_MFPL_PC4MFP_I2C1_SCL        (0x3UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for I2C1_SCL       */
#define SYS_GPC_MFPL_PC4MFP_USCI0_CLK       (0x5UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for USCI0_CLK      */
#define SYS_GPC_MFPL_PC4MFP_PWM0_CH4        (0x6UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for PWM0_CH4       */
#define SYS_GPC_MFPL_PC4MFP_EBI_AD12        (0x7UL<<SYS_GPC_MFPL_PC4MFP_Pos)    /*!< GPC_MFPL PC4 setting for EBI_AD12       */

//PC.5 MFP
#define SYS_GPC_MFPL_PC5MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC5MFP_Pos)    /*!< GPC_MFPL PC5 setting for GPIO           */
#define SYS_GPC_MFPL_PC5MFP_SPI0_I2SMCLK    (0x2UL<<SYS_GPC_MFPL_PC5MFP_Pos)    /*!< GPC_MFPL PC5 setting for SPI0_I2SMCLK   */
#define SYS_GPC_MFPL_PC5MFP_I2C1_SDA        (0x3UL<<SYS_GPC_MFPL_PC5MFP_Pos)    /*!< GPC_MFPL PC5 setting for I2C1_SDA       */
#define SYS_GPC_MFPL_PC5MFP_USCI0_DAT0      (0x4UL<<SYS_GPC_MFPL_PC5MFP_Pos)    /*!< GPC_MFPL PC5 setting for USCI0_DAT0     */
#define SYS_GPC_MFPL_PC5MFP_PWM0_CH5        (0x6UL<<SYS_GPC_MFPL_PC5MFP_Pos)    /*!< GPC_MFPL PC5 setting for PWM0_CH5       */
#define SYS_GPC_MFPL_PC5MFP_EBI_AD13        (0x7UL<<SYS_GPC_MFPL_PC5MFP_Pos)    /*!< GPC_MFPL PC5 setting for EBI_AD13       */

//PC.6 MFP
#define SYS_GPC_MFPL_PC6MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC6MFP_Pos)    /*!< GPC_MFPL PC6 setting for GPIO           */
#define SYS_GPC_MFPL_PC6MFP_USCI0_DAT1      (0x4UL<<SYS_GPC_MFPL_PC6MFP_Pos)    /*!< GPC_MFPL PC6 setting for USCI0_DAT1     */
#define SYS_GPC_MFPL_PC6MFP_ACMP1_O         (0x5UL<<SYS_GPC_MFPL_PC6MFP_Pos)    /*!< GPC_MFPL PC6 setting for ACMP1_O        */
#define SYS_GPC_MFPL_PC6MFP_PWM1_CH0        (0x6UL<<SYS_GPC_MFPL_PC6MFP_Pos)    /*!< GPC_MFPL PC6 setting for PWM1_CH0       */
#define SYS_GPC_MFPL_PC6MFP_EBI_AD14        (0x7UL<<SYS_GPC_MFPL_PC6MFP_Pos)    /*!< GPC_MFPL PC6 setting for EBI_AD14       */

//PC.7 MFP
#define SYS_GPC_MFPL_PC7MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC7MFP_Pos)    /*!< GPC_MFPL PC7 setting for GPIO           */
#define SYS_GPC_MFPL_PC7MFP_USCI0_CTL1      (0x4UL<<SYS_GPC_MFPL_PC7MFP_Pos)    /*!< GPC_MFPL PC7 setting for USCI0_CTL1     */
#define SYS_GPC_MFPL_PC7MFP_PWM1_CH1        (0x6UL<<SYS_GPC_MFPL_PC7MFP_Pos)    /*!< GPC_MFPL PC7 setting for PWM1_CH1       */
#define SYS_GPC_MFPL_PC7MFP_EBI_AD15        (0x7UL<<SYS_GPC_MFPL_PC7MFP_Pos)    /*!< GPC_MFPL PC7 setting for EBI_AD15       */

//PC.8 MFP
#define SYS_GPC_MFPH_PC8MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC8MFP_Pos)    /*!< GPC_MFPH PC8 setting for GPIO           */
#define SYS_GPC_MFPH_PC8MFP_ADC0_CH16       (0x1UL<<SYS_GPC_MFPH_PC8MFP_Pos)    /*!< GPC_MFPH PC8 setting for ADC0_CH16      */
#define SYS_GPC_MFPH_PC8MFP_UART0_nRTS      (0x3UL<<SYS_GPC_MFPH_PC8MFP_Pos)    /*!< GPC_MFPH PC8 setting for UART0_nRTS     */

//PC.9 MFP
#define SYS_GPC_MFPH_PC9MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC9MFP_Pos)    /*!< GPC_MFPH PC9 setting for GPIO           */
#define SYS_GPC_MFPH_PC9MFP_SPI0_I2SMCLK    (0x2UL<<SYS_GPC_MFPH_PC9MFP_Pos)    /*!< GPC_MFPH PC9 setting for SPI0_I2SMCLK   */
#define SYS_GPC_MFPH_PC9MFP_I2C1_SCL        (0x3UL<<SYS_GPC_MFPH_PC9MFP_Pos)    /*!< GPC_MFPH PC9 setting for I2C1_SCL       */
#define SYS_GPC_MFPH_PC9MFP_USCI2_CTL1      (0x4UL<<SYS_GPC_MFPH_PC9MFP_Pos)    /*!< GPC_MFPH PC9 setting for USCI2_CTL1     */
#define SYS_GPC_MFPH_PC9MFP_PWM1_CH0        (0x6UL<<SYS_GPC_MFPH_PC9MFP_Pos)    /*!< GPC_MFPH PC9 setting for PWM1_CH0       */

//PC.10 MFP
#define SYS_GPC_MFPH_PC10MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for GPIO          */
#define SYS_GPC_MFPH_PC10MFP_SPI0_MOSI      (0x2UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for SPI0_MOSI     */
#define SYS_GPC_MFPH_PC10MFP_I2C1_SDA       (0x3UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for I2C1_SDA      */
#define SYS_GPC_MFPH_PC10MFP_USCI2_DAT1     (0x4UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for USCI2_DAT1    */
#define SYS_GPC_MFPH_PC10MFP_PWM1_CH1       (0x6UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for PWM1_CH1      */

//PC.11 MFP
#define SYS_GPC_MFPH_PC11MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for GPIO          */
#define SYS_GPC_MFPH_PC11MFP_SPI0_MISO      (0x2UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for SPI0_MISO     */
#define SYS_GPC_MFPH_PC11MFP_USCI2_CLK      (0x4UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for USCI2_CLK     */
#define SYS_GPC_MFPH_PC11MFP_PWM1_CH2       (0x6UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for PWM1_CH2      */

//PC.12 MFP
#define SYS_GPC_MFPH_PC12MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for GPIO          */
#define SYS_GPC_MFPH_PC12MFP_SPI0_CLK       (0x2UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for SPI0_CLK      */
#define SYS_GPC_MFPH_PC12MFP_USCI2_CTL0     (0x4UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for USCI2_CTL0    */
#define SYS_GPC_MFPH_PC12MFP_PWM1_CH3       (0x6UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for PWM1_CH3      */

//PC.13 MFP
#define SYS_GPC_MFPH_PC13MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for GPIO          */
#define SYS_GPC_MFPH_PC13MFP_SPI0_SS        (0x2UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for SPI0_SS       */
#define SYS_GPC_MFPH_PC13MFP_USCI2_DAT0     (0x4UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for USCI2_DAT0    */
#define SYS_GPC_MFPH_PC13MFP_PWM1_CH4       (0x6UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for PWM1_CH4      */

//PC.14 MFP
#define SYS_GPC_MFPH_PC14MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC14MFP_Pos)   /*!< GPC_MFPH PC14 setting for GPIO          */
#define SYS_GPC_MFPH_PC14MFP_PWM1_CH5       (0x6UL<<SYS_GPC_MFPH_PC14MFP_Pos)   /*!< GPC_MFPH PC14 setting for PWM1_CH5      */

//PC.15 MFP
#define SYS_GPC_MFPH_PC15MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC15MFP_Pos)   /*!< GPC_MFPH PC15 setting for GPIO          */
#define SYS_GPC_MFPH_PC15MFP_PWM1_CH0       (0x6UL<<SYS_GPC_MFPH_PC15MFP_Pos)   /*!< GPC_MFPH PC15 setting for PWM1_CH0      */

//PD.0 MFP
#define SYS_GPD_MFPL_PD0MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for GPIO           */
#define SYS_GPD_MFPL_PD0MFP_SPI0_I2SMCLK    (0x1UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for SPI0_I2SMCLK   */
#define SYS_GPD_MFPL_PD0MFP_SPI1_I2SMCLK    (0x2UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for SPI1_I2SMCLK   */
#define SYS_GPD_MFPL_PD0MFP_UART0_RXD       (0x3UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for UART0_RXD      */
#define SYS_GPD_MFPL_PD0MFP_USCI2_CTL0      (0x4UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for USCI2_CTL0     */
#define SYS_GPD_MFPL_PD0MFP_ACMP1_N         (0x5UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for ACMP1_N        */
#define SYS_GPD_MFPL_PD0MFP_SC1_CLK         (0x6UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for SC1_CLK        */
#define SYS_GPD_MFPL_PD0MFP_INT3            (0x8UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for INT3           */

//PD.1 MFP
#define SYS_GPD_MFPL_PD1MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for GPIO           */
#define SYS_GPD_MFPL_PD1MFP_ADC0_CH19       (0x1UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for ADC0_CH19      */
#define SYS_GPD_MFPL_PD1MFP_PWM0_SYNC_IN    (0x2UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for PWM0_SYNC_IN   */
#define SYS_GPD_MFPL_PD1MFP_UART0_TXD       (0x3UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for UART0_TXD      */
#define SYS_GPD_MFPL_PD1MFP_USCI2_CLK       (0x4UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for USCI2_CLK      */
#define SYS_GPD_MFPL_PD1MFP_ACMP1_P2        (0x5UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for ACMP1_P2       */
#define SYS_GPD_MFPL_PD1MFP_TM0             (0x6UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for TM0            */
#define SYS_GPD_MFPL_PD1MFP_EBI_nRD         (0x7UL<<SYS_GPD_MFPL_PD1MFP_Pos)    /*!< GPD_MFPL PD1 setting for EBI_nRD        */

//PD.2 MFP
#define SYS_GPD_MFPL_PD2MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for GPIO           */
#define SYS_GPD_MFPL_PD2MFP_ADC0_ST         (0x1UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for ADC0_ST        */
#define SYS_GPD_MFPL_PD2MFP_TM0_EXT         (0x3UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for TM0_EXT        */
#define SYS_GPD_MFPL_PD2MFP_USCI2_DAT0      (0x4UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for USCI2_DAT0     */
#define SYS_GPD_MFPL_PD2MFP_ACMP1_P1        (0x5UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for ACMP1_P1       */
#define SYS_GPD_MFPL_PD2MFP_PWM0_BRAKE0     (0x6UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for PWM0_BRAKE0    */
#define SYS_GPD_MFPL_PD2MFP_EBI_nWR         (0x7UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for EBI_nWR        */
#define SYS_GPD_MFPL_PD2MFP_INT0            (0x8UL<<SYS_GPD_MFPL_PD2MFP_Pos)    /*!< GPD_MFPL PD2 setting for INT0           */

//PD.3 MFP
#define SYS_GPD_MFPL_PD3MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for GPIO           */
#define SYS_GPD_MFPL_PD3MFP_TM2             (0x1UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for TM2            */
#define SYS_GPD_MFPL_PD3MFP_SPI0_I2SMCLK    (0x2UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for SPI0_I2SMCLK   */
#define SYS_GPD_MFPL_PD3MFP_TM1_EXT         (0x3UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for TM1_EXT        */
#define SYS_GPD_MFPL_PD3MFP_USCI2_DAT1      (0x4UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for USCI2_DAT1     */
#define SYS_GPD_MFPL_PD3MFP_ACMP1_P0        (0x5UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for ACMP1_P0       */
#define SYS_GPD_MFPL_PD3MFP_PWM0_BRAKE1     (0x6UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for PWM0_BRAKE1    */
#define SYS_GPD_MFPL_PD3MFP_EBI_MCLK        (0x7UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for EBI_MCLK       */
#define SYS_GPD_MFPL_PD3MFP_INT1            (0x8UL<<SYS_GPD_MFPL_PD3MFP_Pos)    /*!< GPD_MFPL PD3 setting for INT1           */

//PD.4 MFP
#define SYS_GPD_MFPL_PD4MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD4MFP_Pos)    /*!< GPD_MFPL PD4 setting for GPIO           */
#define SYS_GPD_MFPL_PD4MFP_SPI1_CLK        (0x2UL<<SYS_GPD_MFPL_PD4MFP_Pos)    /*!< GPD_MFPL PD4 setting for SPI1_CLK       */
#define SYS_GPD_MFPL_PD4MFP_I2C0_SDA        (0x3UL<<SYS_GPD_MFPL_PD4MFP_Pos)    /*!< GPD_MFPL PD4 setting for I2C0_SDA       */
#define SYS_GPD_MFPL_PD4MFP_UART2_nRTS      (0x4UL<<SYS_GPD_MFPL_PD4MFP_Pos)    /*!< GPD_MFPL PD4 setting for UART2_nRTS     */
#define SYS_GPD_MFPL_PD4MFP_PWM0_BRAKE0     (0x5UL<<SYS_GPD_MFPL_PD4MFP_Pos)    /*!< GPD_MFPL PD4 setting for PWM0_BRAKE0    */
#define SYS_GPD_MFPL_PD4MFP_TM0             (0x6UL<<SYS_GPD_MFPL_PD4MFP_Pos)    /*!< GPD_MFPL PD4 setting for TM0            */

//PD.5 MFP
#define SYS_GPD_MFPL_PD5MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for GPIO           */
#define SYS_GPD_MFPL_PD5MFP_CLKO            (0x1UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for CLKO           */
#define SYS_GPD_MFPL_PD5MFP_SPI1_MISO       (0x2UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for SPI1_MISO      */
#define SYS_GPD_MFPL_PD5MFP_I2C0_SCL        (0x3UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for I2C0_SCL       */
#define SYS_GPD_MFPL_PD5MFP_UART2_nCTS      (0x4UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for UART2_nCTS     */
#define SYS_GPD_MFPL_PD5MFP_PWM0_BRAKE1     (0x5UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for PWM0_BRAKE1    */
#define SYS_GPD_MFPL_PD5MFP_TM1             (0x6UL<<SYS_GPD_MFPL_PD5MFP_Pos)    /*!< GPD_MFPL PD5 setting for TM1            */

//PD.6 MFP
#define SYS_GPD_MFPL_PD6MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for GPIO           */
#define SYS_GPD_MFPL_PD6MFP_CLKO            (0x1UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for CLKO           */
#define SYS_GPD_MFPL_PD6MFP_SPI1_SS         (0x2UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for SPI1_SS        */
#define SYS_GPD_MFPL_PD6MFP_UART0_RXD       (0x3UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for UART0_RXD      */
#define SYS_GPD_MFPL_PD6MFP_UART2_TXD       (0x4UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for UART2_TXD      */
#define SYS_GPD_MFPL_PD6MFP_ACMP0_O         (0x5UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for ACMP0_O        */
#define SYS_GPD_MFPL_PD6MFP_PWM0_CH5        (0x6UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for PWM0_CH5       */
#define SYS_GPD_MFPL_PD6MFP_EBI_nWR         (0x7UL<<SYS_GPD_MFPL_PD6MFP_Pos)    /*!< GPD_MFPL PD6 setting for EBI_nWR        */

//PD.7 MFP
#define SYS_GPD_MFPL_PD7MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for GPIO           */
#define SYS_GPD_MFPL_PD7MFP_USCI1_CTL1      (0x1UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for USCI1_CTL1     */
#define SYS_GPD_MFPL_PD7MFP_SPI0_I2SMCLK    (0x2UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for SPI0_I2SMCLK   */
#define SYS_GPD_MFPL_PD7MFP_PWM0_SYNC_IN    (0x3UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for PWM0_SYNC_IN   */
#define SYS_GPD_MFPL_PD7MFP_TM1             (0x4UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for TM1            */
#define SYS_GPD_MFPL_PD7MFP_ACMP0_O         (0x5UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for ACMP0_O        */
#define SYS_GPD_MFPL_PD7MFP_PWM0_CH5        (0x6UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for PWM0_CH5       */
#define SYS_GPD_MFPL_PD7MFP_EBI_nRD         (0x7UL<<SYS_GPD_MFPL_PD7MFP_Pos)    /*!< GPD_MFPL PD7 setting for EBI_nRD        */

//PD.8 MFP
#define SYS_GPD_MFPH_PD8MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD8MFP_Pos)    /*!< GPD_MFPH PD8 setting for GPIO           */
#define SYS_GPD_MFPH_PD8MFP_ADC0_CH17       (0x1UL<<SYS_GPD_MFPH_PD8MFP_Pos)    /*!< GPD_MFPH PD8 setting for ADC0_CH17      */
#define SYS_GPD_MFPH_PD8MFP_UART0_nCTS      (0x3UL<<SYS_GPD_MFPH_PD8MFP_Pos)    /*!< GPD_MFPH PD8 setting for UART0_nCTS     */
#define SYS_GPD_MFPH_PD8MFP_USCI2_CTL1      (0x4UL<<SYS_GPD_MFPH_PD8MFP_Pos)    /*!< GPD_MFPH PD8 setting for USCI2_CTL1     */
#define SYS_GPD_MFPH_PD8MFP_TM2             (0x6UL<<SYS_GPD_MFPH_PD8MFP_Pos)    /*!< GPD_MFPH PD8 setting for TM2            */
#define SYS_GPD_MFPH_PD8MFP_EBI_nCS0        (0x7UL<<SYS_GPD_MFPH_PD8MFP_Pos)    /*!< GPD_MFPH PD8 setting for EBI_nCS0       */

//PD.9 MFP
#define SYS_GPD_MFPH_PD9MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for GPIO           */
#define SYS_GPD_MFPH_PD9MFP_ADC0_CH18       (0x1UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for ADC0_CH18      */
#define SYS_GPD_MFPH_PD9MFP_UART0_RXD       (0x3UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for UART0_RXD      */
#define SYS_GPD_MFPH_PD9MFP_USCI2_CTL0      (0x4UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for USCI2_CTL0     */
#define SYS_GPD_MFPH_PD9MFP_ACMP1_P3        (0x5UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for ACMP1_P3       */
#define SYS_GPD_MFPH_PD9MFP_TM3             (0x6UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for TM3            */
#define SYS_GPD_MFPH_PD9MFP_EBI_ALE         (0x7UL<<SYS_GPD_MFPH_PD9MFP_Pos)    /*!< GPD_MFPH PD9 setting for EBI_ALE        */

//PD.10 MFP
#define SYS_GPD_MFPH_PD10MFP_GPIO           (0x0UL<<SYS_GPD_MFPH_PD10MFP_Pos)   /*!< GPD_MFPH PD10 setting for GPIO          */
#define SYS_GPD_MFPH_PD10MFP_TM2            (0x4UL<<SYS_GPD_MFPH_PD10MFP_Pos)   /*!< GPD_MFPH PD10 setting for TM2           */
#define SYS_GPD_MFPH_PD10MFP_USCI2_DAT0     (0x5UL<<SYS_GPD_MFPH_PD10MFP_Pos)   /*!< GPD_MFPH PD10 setting for USCI2_DAT0    */

//PD.11 MFP
#define SYS_GPD_MFPH_PD11MFP_GPIO           (0x0UL<<SYS_GPD_MFPH_PD11MFP_Pos)   /*!< GPD_MFPH PD11 setting for GPIO          */
#define SYS_GPD_MFPH_PD11MFP_TM3            (0x4UL<<SYS_GPD_MFPH_PD11MFP_Pos)   /*!< GPD_MFPH PD11 setting for TM3           */
#define SYS_GPD_MFPH_PD11MFP_USCI2_DAT1     (0x5UL<<SYS_GPD_MFPH_PD11MFP_Pos)   /*!< GPD_MFPH PD11 setting for USCI2_DAT1    */

//PD.12 MFP
#define SYS_GPD_MFPH_PD12MFP_GPIO           (0x0UL<<SYS_GPD_MFPH_PD12MFP_Pos)   /*!< GPD_MFPH PD12 setting for GPIO          */
#define SYS_GPD_MFPH_PD12MFP_USCI1_CTL0     (0x1UL<<SYS_GPD_MFPH_PD12MFP_Pos)   /*!< GPD_MFPH PD12 setting for USCI1_CTL0    */
#define SYS_GPD_MFPH_PD12MFP_SPI1_SS        (0x2UL<<SYS_GPD_MFPH_PD12MFP_Pos)   /*!< GPD_MFPH PD12 setting for SPI1_SS       */
#define SYS_GPD_MFPH_PD12MFP_UART0_TXD      (0x3UL<<SYS_GPD_MFPH_PD12MFP_Pos)   /*!< GPD_MFPH PD12 setting for UART0_TXD     */
#define SYS_GPD_MFPH_PD12MFP_PWM1_CH0       (0x6UL<<SYS_GPD_MFPH_PD12MFP_Pos)   /*!< GPD_MFPH PD12 setting for PWM1_CH0      */
#define SYS_GPD_MFPH_PD12MFP_EBI_ADR16      (0x7UL<<SYS_GPD_MFPH_PD12MFP_Pos)   /*!< GPD_MFPH PD12 setting for EBI_ADR16     */

//PD.13 MFP
#define SYS_GPD_MFPH_PD13MFP_GPIO           (0x0UL<<SYS_GPD_MFPH_PD13MFP_Pos)   /*!< GPD_MFPH PD13 setting for GPIO          */
#define SYS_GPD_MFPH_PD13MFP_USCI1_DAT1     (0x1UL<<SYS_GPD_MFPH_PD13MFP_Pos)   /*!< GPD_MFPH PD13 setting for USCI1_DAT1    */
#define SYS_GPD_MFPH_PD13MFP_SPI1_MOSI      (0x2UL<<SYS_GPD_MFPH_PD13MFP_Pos)   /*!< GPD_MFPH PD13 setting for SPI1_MOSI     */
#define SYS_GPD_MFPH_PD13MFP_UART0_RXD      (0x3UL<<SYS_GPD_MFPH_PD13MFP_Pos)   /*!< GPD_MFPH PD13 setting for UART0_RXD     */
#define SYS_GPD_MFPH_PD13MFP_PWM1_CH1       (0x6UL<<SYS_GPD_MFPH_PD13MFP_Pos)   /*!< GPD_MFPH PD13 setting for PWM1_CH1      */
#define SYS_GPD_MFPH_PD13MFP_EBI_ADR17      (0x7UL<<SYS_GPD_MFPH_PD13MFP_Pos)   /*!< GPD_MFPH PD13 setting for EBI_ADR17     */

//PD.14 MFP
#define SYS_GPD_MFPH_PD14MFP_GPIO           (0x0UL<<SYS_GPD_MFPH_PD14MFP_Pos)   /*!< GPD_MFPH PD14 setting for GPIO          */
#define SYS_GPD_MFPH_PD14MFP_USCI1_DAT0     (0x1UL<<SYS_GPD_MFPH_PD14MFP_Pos)   /*!< GPD_MFPH PD14 setting for USCI1_DAT0    */
#define SYS_GPD_MFPH_PD14MFP_SPI1_MISO      (0x2UL<<SYS_GPD_MFPH_PD14MFP_Pos)   /*!< GPD_MFPH PD14 setting for SPI1_MISO     */
#define SYS_GPD_MFPH_PD14MFP_UART0_nCTS     (0x3UL<<SYS_GPD_MFPH_PD14MFP_Pos)   /*!< GPD_MFPH PD14 setting for UART0_nCTS    */
#define SYS_GPD_MFPH_PD14MFP_PWM1_CH2       (0x6UL<<SYS_GPD_MFPH_PD14MFP_Pos)   /*!< GPD_MFPH PD14 setting for PWM1_CH2      */
#define SYS_GPD_MFPH_PD14MFP_EBI_ADR18      (0x7UL<<SYS_GPD_MFPH_PD14MFP_Pos)   /*!< GPD_MFPH PD14 setting for EBI_ADR18     */

//PD.15 MFP
#define SYS_GPD_MFPH_PD15MFP_GPIO           (0x0UL<<SYS_GPD_MFPH_PD15MFP_Pos)   /*!< GPD_MFPH PD15 setting for GPIO          */
#define SYS_GPD_MFPH_PD15MFP_USCI1_CLK      (0x1UL<<SYS_GPD_MFPH_PD15MFP_Pos)   /*!< GPD_MFPH PD15 setting for USCI1_CLK     */
#define SYS_GPD_MFPH_PD15MFP_SPI1_CLK       (0x2UL<<SYS_GPD_MFPH_PD15MFP_Pos)   /*!< GPD_MFPH PD15 setting for SPI1_CLK      */
#define SYS_GPD_MFPH_PD15MFP_UART0_nRTS     (0x3UL<<SYS_GPD_MFPH_PD15MFP_Pos)   /*!< GPD_MFPH PD15 setting for UART0_nRTS    */
#define SYS_GPD_MFPH_PD15MFP_PWM1_CH3       (0x6UL<<SYS_GPD_MFPH_PD15MFP_Pos)   /*!< GPD_MFPH PD15 setting for PWM1_CH3      */
#define SYS_GPD_MFPH_PD15MFP_EBI_ADR19      (0x7UL<<SYS_GPD_MFPH_PD15MFP_Pos)   /*!< GPD_MFPH PD15 setting for EBI_ADR19     */

//PE.0 MFP
#define SYS_GPE_MFPL_PE0MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for GPIO           */
#define SYS_GPE_MFPL_PE0MFP_SPI0_CLK        (0x2UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for SPI0_CLK       */
#define SYS_GPE_MFPL_PE0MFP_I2C1_SDA        (0x3UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for I2C1_SDA       */
#define SYS_GPE_MFPL_PE0MFP_TM2_EXT         (0x4UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for TM2_EXT        */
#define SYS_GPE_MFPL_PE0MFP_SC0_nCD         (0x5UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for SC0_nCD        */
#define SYS_GPE_MFPL_PE0MFP_PWM0_CH0        (0x6UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for PWM0_CH0       */
#define SYS_GPE_MFPL_PE0MFP_EBI_nCS1        (0x7UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for EBI_nCS1       */
#define SYS_GPE_MFPL_PE0MFP_INT4            (0x8UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for INT4           */

//PE.1 MFP
#define SYS_GPE_MFPL_PE1MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE1MFP_Pos)    /*!< GPE_MFPL PE1 setting for GPIO           */
#define SYS_GPE_MFPL_PE1MFP_TM3_EXT         (0x3UL<<SYS_GPE_MFPL_PE1MFP_Pos)    /*!< GPE_MFPL PE1 setting for TM3_EXT        */
#define SYS_GPE_MFPL_PE1MFP_SC0_nCD         (0x5UL<<SYS_GPE_MFPL_PE1MFP_Pos)    /*!< GPE_MFPL PE1 setting for SC0_nCD        */
#define SYS_GPE_MFPL_PE1MFP_PWM0_CH1        (0x6UL<<SYS_GPE_MFPL_PE1MFP_Pos)    /*!< GPE_MFPL PE1 setting for PWM0_CH1       */

//PE.2 MFP
#define SYS_GPE_MFPL_PE2MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE2MFP_Pos)    /*!< GPE_MFPL PE2 setting for GPIO           */
#define SYS_GPE_MFPL_PE2MFP_ADC0_CH9        (0x1UL<<SYS_GPE_MFPL_PE2MFP_Pos)    /*!< GPE_MFPL PE2 setting for ADC0_CH9       */
#define SYS_GPE_MFPL_PE2MFP_UART1_nRTS      (0x4UL<<SYS_GPE_MFPL_PE2MFP_Pos)    /*!< GPE_MFPL PE2 setting for UART1_nRTS     */
#define SYS_GPE_MFPL_PE2MFP_TM_BRAKE3       (0x5UL<<SYS_GPE_MFPL_PE2MFP_Pos)    /*!< GPE_MFPL PE2 setting for TM_BRAKE3      */
#define SYS_GPE_MFPL_PE2MFP_PWM0_CH2        (0x6UL<<SYS_GPE_MFPL_PE2MFP_Pos)    /*!< GPE_MFPL PE2 setting for PWM0_CH2       */
#define SYS_GPE_MFPL_PE2MFP_USCI0_CTL0      (0x8UL<<SYS_GPE_MFPL_PE2MFP_Pos)    /*!< GPE_MFPL PE2 setting for USCI0_CTL0     */

//PE.3 MFP
#define SYS_GPE_MFPL_PE3MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE3MFP_Pos)    /*!< GPE_MFPL PE3 setting for GPIO           */
#define SYS_GPE_MFPL_PE3MFP_SPI1_MOSI       (0x2UL<<SYS_GPE_MFPL_PE3MFP_Pos)    /*!< GPE_MFPL PE3 setting for SPI1_MOSI      */
#define SYS_GPE_MFPL_PE3MFP_UART2_RXD       (0x4UL<<SYS_GPE_MFPL_PE3MFP_Pos)    /*!< GPE_MFPL PE3 setting for UART2_RXD      */
#define SYS_GPE_MFPL_PE3MFP_PWM0_CH3        (0x6UL<<SYS_GPE_MFPL_PE3MFP_Pos)    /*!< GPE_MFPL PE3 setting for PWM0_CH3       */

//PE.4 MFP
#define SYS_GPE_MFPL_PE4MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for GPIO           */
#define SYS_GPE_MFPL_PE4MFP_I2C0_SCL        (0x2UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for I2C0_SCL       */
#define SYS_GPE_MFPL_PE4MFP_I2C1_SCL        (0x3UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for I2C1_SCL       */
#define SYS_GPE_MFPL_PE4MFP_USCI0_CTL0      (0x4UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for USCI0_CTL0     */
#define SYS_GPE_MFPL_PE4MFP_SC0_PWR         (0x5UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for SC0_PWR        */
#define SYS_GPE_MFPL_PE4MFP_PWM1_BRAKE0     (0x6UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for PWM1_BRAKE0    */
#define SYS_GPE_MFPL_PE4MFP_EBI_nCS0        (0x7UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for EBI_nCS0       */
#define SYS_GPE_MFPL_PE4MFP_INT0            (0x8UL<<SYS_GPE_MFPL_PE4MFP_Pos)    /*!< GPE_MFPL PE4 setting for INT0           */

//PE.5 MFP
#define SYS_GPE_MFPL_PE5MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for GPIO           */
#define SYS_GPE_MFPL_PE5MFP_I2C0_SDA        (0x2UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for I2C0_SDA       */
#define SYS_GPE_MFPL_PE5MFP_I2C1_SDA        (0x3UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for I2C1_SDA       */
#define SYS_GPE_MFPL_PE5MFP_USCI0_CLK       (0x4UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for USCI0_CLK      */
#define SYS_GPE_MFPL_PE5MFP_SC0_RST         (0x5UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for SC0_RST        */
#define SYS_GPE_MFPL_PE5MFP_PWM1_BRAKE1     (0x6UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for PWM1_BRAKE1    */
#define SYS_GPE_MFPL_PE5MFP_EBI_ALE         (0x7UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for EBI_ALE        */
#define SYS_GPE_MFPL_PE5MFP_INT1            (0x8UL<<SYS_GPE_MFPL_PE5MFP_Pos)    /*!< GPE_MFPL PE5 setting for INT1           */

//PE.6 MFP
#define SYS_GPE_MFPL_PE6MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE6MFP_Pos)    /*!< GPE_MFPL PE6 setting for GPIO           */
#define SYS_GPE_MFPL_PE6MFP_ICE_CLK         (0x1UL<<SYS_GPE_MFPL_PE6MFP_Pos)    /*!< GPE_MFPL PE6 setting for ICE_CLK        */
#define SYS_GPE_MFPL_PE6MFP_I2C0_SCL        (0x2UL<<SYS_GPE_MFPL_PE6MFP_Pos)    /*!< GPE_MFPL PE6 setting for I2C0_SCL       */
#define SYS_GPE_MFPL_PE6MFP_UART0_RXD       (0x3UL<<SYS_GPE_MFPL_PE6MFP_Pos)    /*!< GPE_MFPL PE6 setting for UART0_RXD      */

//PE.7 MFP
#define SYS_GPE_MFPL_PE7MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE7MFP_Pos)    /*!< GPE_MFPL PE7 setting for GPIO           */
#define SYS_GPE_MFPL_PE7MFP_ICE_DAT         (0x1UL<<SYS_GPE_MFPL_PE7MFP_Pos)    /*!< GPE_MFPL PE7 setting for ICE_DAT        */
#define SYS_GPE_MFPL_PE7MFP_I2C0_SDA        (0x2UL<<SYS_GPE_MFPL_PE7MFP_Pos)    /*!< GPE_MFPL PE7 setting for I2C0_SDA       */
#define SYS_GPE_MFPL_PE7MFP_UART0_TXD       (0x3UL<<SYS_GPE_MFPL_PE7MFP_Pos)    /*!< GPE_MFPL PE7 setting for UART0_TXD      */

//PE.8 MFP
#define SYS_GPE_MFPH_PE8MFP_GPIO            (0x0UL<<SYS_GPE_MFPH_PE8MFP_Pos)    /*!< GPE_MFPH PE8 setting for GPIO           */
#define SYS_GPE_MFPH_PE8MFP_UART1_TXD       (0x1UL<<SYS_GPE_MFPH_PE8MFP_Pos)    /*!< GPE_MFPH PE8 setting for UART1_TXD      */
#define SYS_GPE_MFPH_PE8MFP_TM0             (0x3UL<<SYS_GPE_MFPH_PE8MFP_Pos)    /*!< GPE_MFPH PE8 setting for TM0            */
#define SYS_GPE_MFPH_PE8MFP_I2C1_SCL        (0x4UL<<SYS_GPE_MFPH_PE8MFP_Pos)    /*!< GPE_MFPH PE8 setting for I2C1_SCL       */
#define SYS_GPE_MFPH_PE8MFP_SC0_PWR         (0x5UL<<SYS_GPE_MFPH_PE8MFP_Pos)    /*!< GPE_MFPH PE8 setting for SC0_PWR        */

//PE.9 MFP
#define SYS_GPE_MFPH_PE9MFP_GPIO            (0x0UL<<SYS_GPE_MFPH_PE9MFP_Pos)    /*!< GPE_MFPH PE9 setting for GPIO           */
#define SYS_GPE_MFPH_PE9MFP_UART1_RXD       (0x1UL<<SYS_GPE_MFPH_PE9MFP_Pos)    /*!< GPE_MFPH PE9 setting for UART1_RXD      */
#define SYS_GPE_MFPH_PE9MFP_TM1             (0x3UL<<SYS_GPE_MFPH_PE9MFP_Pos)    /*!< GPE_MFPH PE9 setting for TM1            */
#define SYS_GPE_MFPH_PE9MFP_I2C1_SDA        (0x4UL<<SYS_GPE_MFPH_PE9MFP_Pos)    /*!< GPE_MFPH PE9 setting for I2C1_SDA       */
#define SYS_GPE_MFPH_PE9MFP_SC0_RST         (0x5UL<<SYS_GPE_MFPH_PE9MFP_Pos)    /*!< GPE_MFPH PE9 setting for SC0_RST        */

//PE.10 MFP
#define SYS_GPE_MFPH_PE10MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for GPIO          */
#define SYS_GPE_MFPH_PE10MFP_SPI1_MISO      (0x1UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for SPI1_MISO     */
#define SYS_GPE_MFPH_PE10MFP_SPI0_MISO      (0x2UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for SPI0_MISO     */
#define SYS_GPE_MFPH_PE10MFP_UART1_nCTS     (0x3UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for UART1_nCTS    */
#define SYS_GPE_MFPH_PE10MFP_SC0_DAT        (0x5UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for SC0_DAT       */
#define SYS_GPE_MFPH_PE10MFP_SPI1_CLK       (0x6UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for SPI1_CLK      */
#define SYS_GPE_MFPH_PE10MFP_EBI_AD7        (0x7UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for EBI_AD7       */
#define SYS_GPE_MFPH_PE10MFP_TM0_EXT        (0x8UL<<SYS_GPE_MFPH_PE10MFP_Pos)   /*!< GPE_MFPH PE10 setting for TM0_EXT       */

//PE.11 MFP
#define SYS_GPE_MFPH_PE11MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for GPIO          */
#define SYS_GPE_MFPH_PE11MFP_SPI1_MOSI      (0x1UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for SPI1_MOSI     */
#define SYS_GPE_MFPH_PE11MFP_SPI0_MOSI      (0x2UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for SPI0_MOSI     */
#define SYS_GPE_MFPH_PE11MFP_UART1_nRTS     (0x3UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for UART1_nRTS    */
#define SYS_GPE_MFPH_PE11MFP_SC0_CLK        (0x5UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for SC0_CLK       */
#define SYS_GPE_MFPH_PE11MFP_SPI1_MISO      (0x6UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for SPI1_MISO     */
#define SYS_GPE_MFPH_PE11MFP_EBI_AD6        (0x7UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for EBI_AD6       */
#define SYS_GPE_MFPH_PE11MFP_TM1_EXT        (0x8UL<<SYS_GPE_MFPH_PE11MFP_Pos)   /*!< GPE_MFPH PE11 setting for TM1_EXT       */

//PE.12 MFP
#define SYS_GPE_MFPH_PE12MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for GPIO          */
#define SYS_GPE_MFPH_PE12MFP_SPI1_SS        (0x1UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for SPI1_SS       */
#define SYS_GPE_MFPH_PE12MFP_SPI0_SS        (0x2UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for SPI0_SS       */
#define SYS_GPE_MFPH_PE12MFP_UART1_TXD      (0x3UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for UART1_TXD     */
#define SYS_GPE_MFPH_PE12MFP_I2C0_SCL       (0x4UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for I2C0_SCL      */
#define SYS_GPE_MFPH_PE12MFP_SPI1_MOSI      (0x6UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for SPI1_MOSI     */
#define SYS_GPE_MFPH_PE12MFP_EBI_AD5        (0x7UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for EBI_AD5       */
#define SYS_GPE_MFPH_PE12MFP_TM2_EXT        (0x8UL<<SYS_GPE_MFPH_PE12MFP_Pos)   /*!< GPE_MFPH PE12 setting for TM2_EXT       */

//PE.13 MFP
#define SYS_GPE_MFPH_PE13MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for GPIO          */
#define SYS_GPE_MFPH_PE13MFP_SPI1_CLK       (0x1UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for SPI1_CLK      */
#define SYS_GPE_MFPH_PE13MFP_SPI0_CLK       (0x2UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for SPI0_CLK      */
#define SYS_GPE_MFPH_PE13MFP_UART1_RXD      (0x3UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for UART1_RXD     */
#define SYS_GPE_MFPH_PE13MFP_I2C0_SDA       (0x4UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for I2C0_SDA      */
#define SYS_GPE_MFPH_PE13MFP_SPI1_SS        (0x6UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for SPI1_SS       */
#define SYS_GPE_MFPH_PE13MFP_EBI_AD4        (0x7UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for EBI_AD4       */
#define SYS_GPE_MFPH_PE13MFP_TM3_EXT        (0x8UL<<SYS_GPE_MFPH_PE13MFP_Pos)   /*!< GPE_MFPH PE13 setting for TM3_EXT       */

//PF.0 MFP
#define SYS_GPF_MFPL_PF0MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for GPIO           */
#define SYS_GPF_MFPL_PF0MFP_X32_OUT         (0x1UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for X32_OUT        */
#define SYS_GPF_MFPL_PF0MFP_USCI2_CTL1      (0x5UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for USCI2_CTL1     */
#define SYS_GPF_MFPL_PF0MFP_INT5            (0x8UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for INT5           */

//PF.1 MFP
#define SYS_GPF_MFPL_PF1MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF1MFP_Pos)    /*!< GPF_MFPL PF1 setting for GPIO           */
#define SYS_GPF_MFPL_PF1MFP_X32_IN          (0x1UL<<SYS_GPF_MFPL_PF1MFP_Pos)    /*!< GPF_MFPL PF1 setting for X32_IN         */
#define SYS_GPF_MFPL_PF1MFP_USCI2_CTL0      (0x5UL<<SYS_GPF_MFPL_PF1MFP_Pos)    /*!< GPF_MFPL PF1 setting for USCI2_CTL0     */
#define SYS_GPF_MFPL_PF1MFP_PWM1_BRAKE0     (0x6UL<<SYS_GPF_MFPL_PF1MFP_Pos)    /*!< GPF_MFPL PF1 setting for PWM1_BRAKE0    */

//PF.2 MFP
#define SYS_GPF_MFPL_PF2MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF2MFP_Pos)    /*!< GPF_MFPL PF2 setting for GPIO           */
#define SYS_GPF_MFPL_PF2MFP_USCI2_CLK       (0x5UL<<SYS_GPF_MFPL_PF2MFP_Pos)    /*!< GPF_MFPL PF2 setting for USCI2_CLK      */
#define SYS_GPF_MFPL_PF2MFP_PWM1_BRAKE1     (0x6UL<<SYS_GPF_MFPL_PF2MFP_Pos)    /*!< GPF_MFPL PF2 setting for PWM1_BRAKE1    */

//PF.3 MFP
#define SYS_GPF_MFPL_PF3MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF3MFP_Pos)    /*!< GPF_MFPL PF3 setting for GPIO           */
#define SYS_GPF_MFPL_PF3MFP_XT1_OUT         (0x1UL<<SYS_GPF_MFPL_PF3MFP_Pos)    /*!< GPF_MFPL PF3 setting for XT1_OUT        */
#define SYS_GPF_MFPL_PF3MFP_I2C1_SCL        (0x3UL<<SYS_GPF_MFPL_PF3MFP_Pos)    /*!< GPF_MFPL PF3 setting for I2C1_SCL       */

//PF.4 MFP
#define SYS_GPF_MFPL_PF4MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF4MFP_Pos)    /*!< GPF_MFPL PF4 setting for GPIO           */
#define SYS_GPF_MFPL_PF4MFP_XT1_IN          (0x1UL<<SYS_GPF_MFPL_PF4MFP_Pos)    /*!< GPF_MFPL PF4 setting for XT1_IN         */
#define SYS_GPF_MFPL_PF4MFP_I2C1_SDA        (0x3UL<<SYS_GPF_MFPL_PF4MFP_Pos)    /*!< GPF_MFPL PF4 setting for I2C1_SDA       */

//PF.5 MFP
#define SYS_GPF_MFPL_PF5MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF5MFP_Pos)    /*!< GPF_MFPL PF5 setting for GPIO           */
#define SYS_GPF_MFPL_PF5MFP_TM3_EXT         (0x3UL<<SYS_GPF_MFPL_PF5MFP_Pos)    /*!< GPF_MFPL PF5 setting for TM3_EXT        */
#define SYS_GPF_MFPL_PF5MFP_SC1_nCD         (0x5UL<<SYS_GPF_MFPL_PF5MFP_Pos)    /*!< GPF_MFPL PF5 setting for SC1_nCD        */
#define SYS_GPF_MFPL_PF5MFP_TM_BRAKE0       (0x6UL<<SYS_GPF_MFPL_PF5MFP_Pos)    /*!< GPF_MFPL PF5 setting for TM_BRAKE0      */

//PF.6 MFP
#define SYS_GPF_MFPL_PF6MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF6MFP_Pos)    /*!< GPF_MFPL PF6 setting for GPIO           */

//PF.7 MFP
#define SYS_GPF_MFPL_PF7MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF7MFP_Pos)    /*!< GPF_MFPL PF7 setting for GPIO           */


/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define ACMP0_N_PB4              SYS_GPB_MFPL_PB4MFP_ACMP0_N          /*!< GPB_MFPL PB4 setting for ACMP0_N        */
#define ACMP0_O_PD6              SYS_GPD_MFPL_PD6MFP_ACMP0_O          /*!< GPD_MFPL PD6 setting for ACMP0_O        */
#define ACMP0_O_PD7              SYS_GPD_MFPL_PD7MFP_ACMP0_O          /*!< GPD_MFPL PD7 setting for ACMP0_O        */
#define ACMP0_P0_PB7             SYS_GPB_MFPL_PB7MFP_ACMP0_P0         /*!< GPB_MFPL PB7 setting for ACMP0_P0       */
#define ACMP0_P1_PB6             SYS_GPB_MFPL_PB6MFP_ACMP0_P1         /*!< GPB_MFPL PB6 setting for ACMP0_P1       */
#define ACMP0_P2_PB5             SYS_GPB_MFPL_PB5MFP_ACMP0_P2         /*!< GPB_MFPL PB5 setting for ACMP0_P2       */
#define ACMP0_P3_PB15            SYS_GPB_MFPH_PB15MFP_ACMP0_P3        /*!< GPB_MFPH PB15 setting for ACMP0_P3      */
#define ACMP0_WLAT_PC0           SYS_GPC_MFPL_PC0MFP_ACMP0_WLAT       /*!< GPC_MFPL PC0 setting for ACMP0_WLAT     */
#define ACMP1_N_PD0              SYS_GPD_MFPL_PD0MFP_ACMP1_N          /*!< GPD_MFPL PD0 setting for ACMP1_N        */
#define ACMP1_O_PC6              SYS_GPC_MFPL_PC6MFP_ACMP1_O          /*!< GPC_MFPL PC6 setting for ACMP1_O        */
#define ACMP1_O_PC2              SYS_GPC_MFPL_PC2MFP_ACMP1_O          /*!< GPC_MFPL PC2 setting for ACMP1_O        */
#define ACMP1_P0_PD3             SYS_GPD_MFPL_PD3MFP_ACMP1_P0         /*!< GPD_MFPL PD3 setting for ACMP1_P0       */
#define ACMP1_P1_PD2             SYS_GPD_MFPL_PD2MFP_ACMP1_P1         /*!< GPD_MFPL PD2 setting for ACMP1_P1       */
#define ACMP1_P2_PD1             SYS_GPD_MFPL_PD1MFP_ACMP1_P2         /*!< GPD_MFPL PD1 setting for ACMP1_P2       */
#define ACMP1_P3_PD9             SYS_GPD_MFPH_PD9MFP_ACMP1_P3         /*!< GPD_MFPH PD9 setting for ACMP1_P3       */
#define ACMP1_WLAT_PC1           SYS_GPC_MFPL_PC1MFP_ACMP1_WLAT       /*!< GPC_MFPL PC1 setting for ACMP1_WLAT     */
#define ADC0_CH0_PB0             SYS_GPB_MFPL_PB0MFP_ADC0_CH0         /*!< GPB_MFPL PB0 setting for ADC0_CH0       */
#define ADC0_CH1_PB1             SYS_GPB_MFPL_PB1MFP_ADC0_CH1         /*!< GPB_MFPL PB1 setting for ADC0_CH1       */
#define ADC0_CH10_PB13           SYS_GPB_MFPH_PB13MFP_ADC0_CH10       /*!< GPB_MFPH PB13 setting for ADC0_CH10     */
#define ADC0_CH11_PB14           SYS_GPB_MFPH_PB14MFP_ADC0_CH11       /*!< GPB_MFPH PB14 setting for ADC0_CH11     */
#define ADC0_CH12_PB15           SYS_GPB_MFPH_PB15MFP_ADC0_CH12       /*!< GPB_MFPH PB15 setting for ADC0_CH12     */
#define ADC0_CH13_PB5            SYS_GPB_MFPL_PB5MFP_ADC0_CH13        /*!< GPB_MFPL PB5 setting for ADC0_CH13      */
#define ADC0_CH14_PB6            SYS_GPB_MFPL_PB6MFP_ADC0_CH14        /*!< GPB_MFPL PB6 setting for ADC0_CH14      */
#define ADC0_CH15_PB7            SYS_GPB_MFPL_PB7MFP_ADC0_CH15        /*!< GPB_MFPL PB7 setting for ADC0_CH15      */
#define ADC0_CH16_PC8            SYS_GPC_MFPH_PC8MFP_ADC0_CH16        /*!< GPC_MFPH PC8 setting for ADC0_CH16      */
#define ADC0_CH17_PD8            SYS_GPD_MFPH_PD8MFP_ADC0_CH17        /*!< GPD_MFPH PD8 setting for ADC0_CH17      */
#define ADC0_CH18_PD9            SYS_GPD_MFPH_PD9MFP_ADC0_CH18        /*!< GPD_MFPH PD9 setting for ADC0_CH18      */
#define ADC0_CH19_PD1            SYS_GPD_MFPL_PD1MFP_ADC0_CH19        /*!< GPD_MFPL PD1 setting for ADC0_CH19      */
#define ADC0_CH2_PB2             SYS_GPB_MFPL_PB2MFP_ADC0_CH2         /*!< GPB_MFPL PB2 setting for ADC0_CH2       */
#define ADC0_CH3_PB3             SYS_GPB_MFPL_PB3MFP_ADC0_CH3         /*!< GPB_MFPL PB3 setting for ADC0_CH3       */
#define ADC0_CH4_PB4             SYS_GPB_MFPL_PB4MFP_ADC0_CH4         /*!< GPB_MFPL PB4 setting for ADC0_CH4       */
#define ADC0_CH5_PB8             SYS_GPB_MFPH_PB8MFP_ADC0_CH5         /*!< GPB_MFPH PB8 setting for ADC0_CH5       */
#define ADC0_CH6_PB9             SYS_GPB_MFPH_PB9MFP_ADC0_CH6         /*!< GPB_MFPH PB9 setting for ADC0_CH6       */
#define ADC0_CH7_PB10            SYS_GPB_MFPH_PB10MFP_ADC0_CH7        /*!< GPB_MFPH PB10 setting for ADC0_CH7      */
#define ADC0_CH8_PB11            SYS_GPB_MFPH_PB11MFP_ADC0_CH8        /*!< GPB_MFPH PB11 setting for ADC0_CH8      */
#define ADC0_CH9_PE2             SYS_GPE_MFPL_PE2MFP_ADC0_CH9         /*!< GPE_MFPL PE2 setting for ADC0_CH9       */
#define ADC0_ST_PD2              SYS_GPD_MFPL_PD2MFP_ADC0_ST          /*!< GPD_MFPL PD2 setting for ADC0_ST        */
#define CLKO_PD5                 SYS_GPD_MFPL_PD5MFP_CLKO             /*!< GPD_MFPL PD5 setting for CLKO           */
#define CLKO_PD6                 SYS_GPD_MFPL_PD6MFP_CLKO             /*!< GPD_MFPL PD6 setting for CLKO           */
#define CLKO_PA8                 SYS_GPA_MFPH_PA8MFP_CLKO             /*!< GPA_MFPH PA8 setting for CLKO           */
#define CLKO_PC1                 SYS_GPC_MFPL_PC1MFP_CLKO             /*!< GPC_MFPL PC1 setting for CLKO           */
#define EBI_AD0_PA0              SYS_GPA_MFPL_PA0MFP_EBI_AD0          /*!< GPA_MFPL PA0 setting for EBI_AD0        */
#define EBI_AD1_PA1              SYS_GPA_MFPL_PA1MFP_EBI_AD1          /*!< GPA_MFPL PA1 setting for EBI_AD1        */
#define EBI_AD10_PC2             SYS_GPC_MFPL_PC2MFP_EBI_AD10         /*!< GPC_MFPL PC2 setting for EBI_AD10       */
#define EBI_AD11_PC3             SYS_GPC_MFPL_PC3MFP_EBI_AD11         /*!< GPC_MFPL PC3 setting for EBI_AD11       */
#define EBI_AD12_PC4             SYS_GPC_MFPL_PC4MFP_EBI_AD12         /*!< GPC_MFPL PC4 setting for EBI_AD12       */
#define EBI_AD13_PC5             SYS_GPC_MFPL_PC5MFP_EBI_AD13         /*!< GPC_MFPL PC5 setting for EBI_AD13       */
#define EBI_AD14_PC6             SYS_GPC_MFPL_PC6MFP_EBI_AD14         /*!< GPC_MFPL PC6 setting for EBI_AD14       */
#define EBI_AD15_PC7             SYS_GPC_MFPL_PC7MFP_EBI_AD15         /*!< GPC_MFPL PC7 setting for EBI_AD15       */
#define EBI_AD2_PA2              SYS_GPA_MFPL_PA2MFP_EBI_AD2          /*!< GPA_MFPL PA2 setting for EBI_AD2        */
#define EBI_AD3_PA3              SYS_GPA_MFPL_PA3MFP_EBI_AD3          /*!< GPA_MFPL PA3 setting for EBI_AD3        */
#define EBI_AD4_PA4              SYS_GPA_MFPL_PA4MFP_EBI_AD4          /*!< GPA_MFPL PA4 setting for EBI_AD4        */
#define EBI_AD4_PB7              SYS_GPB_MFPL_PB7MFP_EBI_AD4          /*!< GPB_MFPL PB7 setting for EBI_AD4        */
#define EBI_AD4_PE13             SYS_GPE_MFPH_PE13MFP_EBI_AD4         /*!< GPE_MFPH PE13 setting for EBI_AD4       */
#define EBI_AD5_PA5              SYS_GPA_MFPL_PA5MFP_EBI_AD5          /*!< GPA_MFPL PA5 setting for EBI_AD5        */
#define EBI_AD5_PE12             SYS_GPE_MFPH_PE12MFP_EBI_AD5         /*!< GPE_MFPH PE12 setting for EBI_AD5       */
#define EBI_AD5_PB6              SYS_GPB_MFPL_PB6MFP_EBI_AD5          /*!< GPB_MFPL PB6 setting for EBI_AD5        */
#define EBI_AD6_PE11             SYS_GPE_MFPH_PE11MFP_EBI_AD6         /*!< GPE_MFPH PE11 setting for EBI_AD6       */
#define EBI_AD6_PA6              SYS_GPA_MFPL_PA6MFP_EBI_AD6          /*!< GPA_MFPL PA6 setting for EBI_AD6        */
#define EBI_AD6_PB5              SYS_GPB_MFPL_PB5MFP_EBI_AD6          /*!< GPB_MFPL PB5 setting for EBI_AD6        */
#define EBI_AD7_PB4              SYS_GPB_MFPL_PB4MFP_EBI_AD7          /*!< GPB_MFPL PB4 setting for EBI_AD7        */
#define EBI_AD7_PA7              SYS_GPA_MFPL_PA7MFP_EBI_AD7          /*!< GPA_MFPL PA7 setting for EBI_AD7        */
#define EBI_AD7_PE10             SYS_GPE_MFPH_PE10MFP_EBI_AD7         /*!< GPE_MFPH PE10 setting for EBI_AD7       */
#define EBI_AD8_PC0              SYS_GPC_MFPL_PC0MFP_EBI_AD8          /*!< GPC_MFPL PC0 setting for EBI_AD8        */
#define EBI_AD9_PC1              SYS_GPC_MFPL_PC1MFP_EBI_AD9          /*!< GPC_MFPL PC1 setting for EBI_AD9        */
#define EBI_ADR16_PD12           SYS_GPD_MFPH_PD12MFP_EBI_ADR16       /*!< GPD_MFPH PD12 setting for EBI_ADR16     */
#define EBI_ADR17_PD13           SYS_GPD_MFPH_PD13MFP_EBI_ADR17       /*!< GPD_MFPH PD13 setting for EBI_ADR17     */
#define EBI_ADR18_PD14           SYS_GPD_MFPH_PD14MFP_EBI_ADR18       /*!< GPD_MFPH PD14 setting for EBI_ADR18     */
#define EBI_ADR19_PD15           SYS_GPD_MFPH_PD15MFP_EBI_ADR19       /*!< GPD_MFPH PD15 setting for EBI_ADR19     */
#define EBI_ALE_PB3              SYS_GPB_MFPL_PB3MFP_EBI_ALE          /*!< GPB_MFPL PB3 setting for EBI_ALE        */
#define EBI_ALE_PE5              SYS_GPE_MFPL_PE5MFP_EBI_ALE          /*!< GPE_MFPL PE5 setting for EBI_ALE        */
#define EBI_ALE_PD9              SYS_GPD_MFPH_PD9MFP_EBI_ALE          /*!< GPD_MFPH PD9 setting for EBI_ALE        */
#define EBI_MCLK_PD3             SYS_GPD_MFPL_PD3MFP_EBI_MCLK         /*!< GPD_MFPL PD3 setting for EBI_MCLK       */
#define EBI_nCS0_PE4             SYS_GPE_MFPL_PE4MFP_EBI_nCS0         /*!< GPE_MFPL PE4 setting for EBI_nCS0       */
#define EBI_nCS0_PB2             SYS_GPB_MFPL_PB2MFP_EBI_nCS0         /*!< GPB_MFPL PB2 setting for EBI_nCS0       */
#define EBI_nCS0_PD8             SYS_GPD_MFPH_PD8MFP_EBI_nCS0         /*!< GPD_MFPH PD8 setting for EBI_nCS0       */
#define EBI_nCS1_PE0             SYS_GPE_MFPL_PE0MFP_EBI_nCS1         /*!< GPE_MFPL PE0 setting for EBI_nCS1       */
#define EBI_nCS1_PB15            SYS_GPB_MFPH_PB15MFP_EBI_nCS1        /*!< GPB_MFPH PB15 setting for EBI_nCS1      */
#define EBI_nRD_PD7              SYS_GPD_MFPL_PD7MFP_EBI_nRD          /*!< GPD_MFPL PD7 setting for EBI_nRD        */
#define EBI_nRD_PD1              SYS_GPD_MFPL_PD1MFP_EBI_nRD          /*!< GPD_MFPL PD1 setting for EBI_nRD        */
#define EBI_nWR_PD6              SYS_GPD_MFPL_PD6MFP_EBI_nWR          /*!< GPD_MFPL PD6 setting for EBI_nWR        */
#define EBI_nWR_PD2              SYS_GPD_MFPL_PD2MFP_EBI_nWR          /*!< GPD_MFPL PD2 setting for EBI_nWR        */
#define EBI_nWRH_PB1             SYS_GPB_MFPL_PB1MFP_EBI_nWRH         /*!< GPB_MFPL PB1 setting for EBI_nWRH       */
#define EBI_nWRL_PB0             SYS_GPB_MFPL_PB0MFP_EBI_nWRL         /*!< GPB_MFPL PB0 setting for EBI_nWRL       */
#define I2C0_SCL_PE4             SYS_GPE_MFPL_PE4MFP_I2C0_SCL         /*!< GPE_MFPL PE4 setting for I2C0_SCL       */
#define I2C0_SCL_PA3             SYS_GPA_MFPL_PA3MFP_I2C0_SCL         /*!< GPA_MFPL PA3 setting for I2C0_SCL       */
#define I2C0_SCL_PE12            SYS_GPE_MFPH_PE12MFP_I2C0_SCL        /*!< GPE_MFPH PE12 setting for I2C0_SCL      */
#define I2C0_SCL_PD5             SYS_GPD_MFPL_PD5MFP_I2C0_SCL         /*!< GPD_MFPL PD5 setting for I2C0_SCL       */
#define I2C0_SCL_PE6             SYS_GPE_MFPL_PE6MFP_I2C0_SCL         /*!< GPE_MFPL PE6 setting for I2C0_SCL       */
#define I2C0_SDA_PA2             SYS_GPA_MFPL_PA2MFP_I2C0_SDA         /*!< GPA_MFPL PA2 setting for I2C0_SDA       */
#define I2C0_SDA_PD4             SYS_GPD_MFPL_PD4MFP_I2C0_SDA         /*!< GPD_MFPL PD4 setting for I2C0_SDA       */
#define I2C0_SDA_PE7             SYS_GPE_MFPL_PE7MFP_I2C0_SDA         /*!< GPE_MFPL PE7 setting for I2C0_SDA       */
#define I2C0_SDA_PE13            SYS_GPE_MFPH_PE13MFP_I2C0_SDA        /*!< GPE_MFPH PE13 setting for I2C0_SDA      */
#define I2C0_SDA_PE5             SYS_GPE_MFPL_PE5MFP_I2C0_SDA         /*!< GPE_MFPL PE5 setting for I2C0_SDA       */
#define I2C1_SCL_PC4             SYS_GPC_MFPL_PC4MFP_I2C1_SCL         /*!< GPC_MFPL PC4 setting for I2C1_SCL       */
#define I2C1_SCL_PE4             SYS_GPE_MFPL_PE4MFP_I2C1_SCL         /*!< GPE_MFPL PE4 setting for I2C1_SCL       */
#define I2C1_SCL_PC9             SYS_GPC_MFPH_PC9MFP_I2C1_SCL         /*!< GPC_MFPH PC9 setting for I2C1_SCL       */
#define I2C1_SCL_PE8             SYS_GPE_MFPH_PE8MFP_I2C1_SCL         /*!< GPE_MFPH PE8 setting for I2C1_SCL       */
#define I2C1_SCL_PA8             SYS_GPA_MFPH_PA8MFP_I2C1_SCL         /*!< GPA_MFPH PA8 setting for I2C1_SCL       */
#define I2C1_SCL_PF3             SYS_GPF_MFPL_PF3MFP_I2C1_SCL         /*!< GPF_MFPL PF3 setting for I2C1_SCL       */
#define I2C1_SDA_PC5             SYS_GPC_MFPL_PC5MFP_I2C1_SDA         /*!< GPC_MFPL PC5 setting for I2C1_SDA       */
#define I2C1_SDA_PE0             SYS_GPE_MFPL_PE0MFP_I2C1_SDA         /*!< GPE_MFPL PE0 setting for I2C1_SDA       */
#define I2C1_SDA_PC10            SYS_GPC_MFPH_PC10MFP_I2C1_SDA        /*!< GPC_MFPH PC10 setting for I2C1_SDA      */
#define I2C1_SDA_PA9             SYS_GPA_MFPH_PA9MFP_I2C1_SDA         /*!< GPA_MFPH PA9 setting for I2C1_SDA       */
#define I2C1_SDA_PE9             SYS_GPE_MFPH_PE9MFP_I2C1_SDA         /*!< GPE_MFPH PE9 setting for I2C1_SDA       */
#define I2C1_SDA_PE5             SYS_GPE_MFPL_PE5MFP_I2C1_SDA         /*!< GPE_MFPL PE5 setting for I2C1_SDA       */
#define I2C1_SDA_PF4             SYS_GPF_MFPL_PF4MFP_I2C1_SDA         /*!< GPF_MFPL PF4 setting for I2C1_SDA       */
#define ICE_CLK_PE6              SYS_GPE_MFPL_PE6MFP_ICE_CLK          /*!< GPE_MFPL PE6 setting for ICE_CLK        */
#define ICE_DAT_PE7              SYS_GPE_MFPL_PE7MFP_ICE_DAT          /*!< GPE_MFPL PE7 setting for ICE_DAT        */
#define INT0_PE4                 SYS_GPE_MFPL_PE4MFP_INT0             /*!< GPE_MFPL PE4 setting for INT0           */
#define INT0_PD2                 SYS_GPD_MFPL_PD2MFP_INT0             /*!< GPD_MFPL PD2 setting for INT0           */
#define INT0_PA0                 SYS_GPA_MFPL_PA0MFP_INT0             /*!< GPA_MFPL PA0 setting for INT0           */
#define INT1_PE5                 SYS_GPE_MFPL_PE5MFP_INT1             /*!< GPE_MFPL PE5 setting for INT1           */
#define INT1_PD3                 SYS_GPD_MFPL_PD3MFP_INT1             /*!< GPD_MFPL PD3 setting for INT1           */
#define INT1_PB0                 SYS_GPB_MFPL_PB0MFP_INT1             /*!< GPB_MFPL PB0 setting for INT1           */
#define INT2_PC0                 SYS_GPC_MFPL_PC0MFP_INT2             /*!< GPC_MFPL PC0 setting for INT2           */
#define INT3_PD0                 SYS_GPD_MFPL_PD0MFP_INT3             /*!< GPD_MFPL PD0 setting for INT3           */
#define INT4_PE0                 SYS_GPE_MFPL_PE0MFP_INT4             /*!< GPE_MFPL PE0 setting for INT4           */
#define INT5_PF0                 SYS_GPF_MFPL_PF0MFP_INT5             /*!< GPF_MFPL PF0 setting for INT5           */
#define PWM0_BRAKE0_PD2          SYS_GPD_MFPL_PD2MFP_PWM0_BRAKE0      /*!< GPD_MFPL PD2 setting for PWM0_BRAKE0    */
#define PWM0_BRAKE0_PD4          SYS_GPD_MFPL_PD4MFP_PWM0_BRAKE0      /*!< GPD_MFPL PD4 setting for PWM0_BRAKE0    */
#define PWM0_BRAKE0_PA8          SYS_GPA_MFPH_PA8MFP_PWM0_BRAKE0      /*!< GPA_MFPH PA8 setting for PWM0_BRAKE0    */
#define PWM0_BRAKE1_PD5          SYS_GPD_MFPL_PD5MFP_PWM0_BRAKE1      /*!< GPD_MFPL PD5 setting for PWM0_BRAKE1    */
#define PWM0_BRAKE1_PD3          SYS_GPD_MFPL_PD3MFP_PWM0_BRAKE1      /*!< GPD_MFPL PD3 setting for PWM0_BRAKE1    */
#define PWM0_CH0_PC0             SYS_GPC_MFPL_PC0MFP_PWM0_CH0         /*!< GPC_MFPL PC0 setting for PWM0_CH0       */
#define PWM0_CH0_PE0             SYS_GPE_MFPL_PE0MFP_PWM0_CH0         /*!< GPE_MFPL PE0 setting for PWM0_CH0       */
#define PWM0_CH1_PC1             SYS_GPC_MFPL_PC1MFP_PWM0_CH1         /*!< GPC_MFPL PC1 setting for PWM0_CH1       */
#define PWM0_CH1_PE1             SYS_GPE_MFPL_PE1MFP_PWM0_CH1         /*!< GPE_MFPL PE1 setting for PWM0_CH1       */
#define PWM0_CH2_PE2             SYS_GPE_MFPL_PE2MFP_PWM0_CH2         /*!< GPE_MFPL PE2 setting for PWM0_CH2       */
#define PWM0_CH2_PC2             SYS_GPC_MFPL_PC2MFP_PWM0_CH2         /*!< GPC_MFPL PC2 setting for PWM0_CH2       */
#define PWM0_CH2_PB8             SYS_GPB_MFPH_PB8MFP_PWM0_CH2         /*!< GPB_MFPH PB8 setting for PWM0_CH2       */
#define PWM0_CH3_PE3             SYS_GPE_MFPL_PE3MFP_PWM0_CH3         /*!< GPE_MFPL PE3 setting for PWM0_CH3       */
#define PWM0_CH3_PC3             SYS_GPC_MFPL_PC3MFP_PWM0_CH3         /*!< GPC_MFPL PC3 setting for PWM0_CH3       */
#define PWM0_CH4_PC4             SYS_GPC_MFPL_PC4MFP_PWM0_CH4         /*!< GPC_MFPL PC4 setting for PWM0_CH4       */
#define PWM0_CH5_PD7             SYS_GPD_MFPL_PD7MFP_PWM0_CH5         /*!< GPD_MFPL PD7 setting for PWM0_CH5       */
#define PWM0_CH5_PC5             SYS_GPC_MFPL_PC5MFP_PWM0_CH5         /*!< GPC_MFPL PC5 setting for PWM0_CH5       */
#define PWM0_CH5_PD6             SYS_GPD_MFPL_PD6MFP_PWM0_CH5         /*!< GPD_MFPL PD6 setting for PWM0_CH5       */
#define PWM0_SYNC_IN_PD7         SYS_GPD_MFPL_PD7MFP_PWM0_SYNC_IN     /*!< GPD_MFPL PD7 setting for PWM0_SYNC_IN   */
#define PWM0_SYNC_IN_PD1         SYS_GPD_MFPL_PD1MFP_PWM0_SYNC_IN     /*!< GPD_MFPL PD1 setting for PWM0_SYNC_IN   */
#define PWM0_SYNC_OUT_PB1        SYS_GPB_MFPL_PB1MFP_PWM0_SYNC_OUT    /*!< GPB_MFPL PB1 setting for PWM0_SYNC_OUT  */
#define PWM1_BRAKE0_PE4          SYS_GPE_MFPL_PE4MFP_PWM1_BRAKE0      /*!< GPE_MFPL PE4 setting for PWM1_BRAKE0    */
#define PWM1_BRAKE0_PF1          SYS_GPF_MFPL_PF1MFP_PWM1_BRAKE0      /*!< GPF_MFPL PF1 setting for PWM1_BRAKE0    */
#define PWM1_BRAKE1_PF2          SYS_GPF_MFPL_PF2MFP_PWM1_BRAKE1      /*!< GPF_MFPL PF2 setting for PWM1_BRAKE1    */
#define PWM1_BRAKE1_PA9          SYS_GPA_MFPH_PA9MFP_PWM1_BRAKE1      /*!< GPA_MFPH PA9 setting for PWM1_BRAKE1    */
#define PWM1_BRAKE1_PE5          SYS_GPE_MFPL_PE5MFP_PWM1_BRAKE1      /*!< GPE_MFPL PE5 setting for PWM1_BRAKE1    */
#define PWM1_CH0_PD12            SYS_GPD_MFPH_PD12MFP_PWM1_CH0        /*!< GPD_MFPH PD12 setting for PWM1_CH0      */
#define PWM1_CH0_PC9             SYS_GPC_MFPH_PC9MFP_PWM1_CH0         /*!< GPC_MFPH PC9 setting for PWM1_CH0       */
#define PWM1_CH0_PC6             SYS_GPC_MFPL_PC6MFP_PWM1_CH0         /*!< GPC_MFPL PC6 setting for PWM1_CH0       */
#define PWM1_CH0_PC15            SYS_GPC_MFPH_PC15MFP_PWM1_CH0        /*!< GPC_MFPH PC15 setting for PWM1_CH0      */
#define PWM1_CH1_PC10            SYS_GPC_MFPH_PC10MFP_PWM1_CH1        /*!< GPC_MFPH PC10 setting for PWM1_CH1      */
#define PWM1_CH1_PD13            SYS_GPD_MFPH_PD13MFP_PWM1_CH1        /*!< GPD_MFPH PD13 setting for PWM1_CH1      */
#define PWM1_CH1_PC7             SYS_GPC_MFPL_PC7MFP_PWM1_CH1         /*!< GPC_MFPL PC7 setting for PWM1_CH1       */
#define PWM1_CH1_PB12            SYS_GPB_MFPH_PB12MFP_PWM1_CH1        /*!< GPB_MFPH PB12 setting for PWM1_CH1      */
#define PWM1_CH2_PC11            SYS_GPC_MFPH_PC11MFP_PWM1_CH2        /*!< GPC_MFPH PC11 setting for PWM1_CH2      */
#define PWM1_CH2_PD14            SYS_GPD_MFPH_PD14MFP_PWM1_CH2        /*!< GPD_MFPH PD14 setting for PWM1_CH2      */
#define PWM1_CH2_PA3             SYS_GPA_MFPL_PA3MFP_PWM1_CH2         /*!< GPA_MFPL PA3 setting for PWM1_CH2       */
#define PWM1_CH3_PA2             SYS_GPA_MFPL_PA2MFP_PWM1_CH3         /*!< GPA_MFPL PA2 setting for PWM1_CH3       */
#define PWM1_CH3_PC12            SYS_GPC_MFPH_PC12MFP_PWM1_CH3        /*!< GPC_MFPH PC12 setting for PWM1_CH3      */
#define PWM1_CH3_PD15            SYS_GPD_MFPH_PD15MFP_PWM1_CH3        /*!< GPD_MFPH PD15 setting for PWM1_CH3      */
#define PWM1_CH4_PC13            SYS_GPC_MFPH_PC13MFP_PWM1_CH4        /*!< GPC_MFPH PC13 setting for PWM1_CH4      */
#define PWM1_CH4_PA1             SYS_GPA_MFPL_PA1MFP_PWM1_CH4         /*!< GPA_MFPL PA1 setting for PWM1_CH4       */
#define PWM1_CH5_PC14            SYS_GPC_MFPH_PC14MFP_PWM1_CH5        /*!< GPC_MFPH PC14 setting for PWM1_CH5      */
#define PWM1_CH5_PA0             SYS_GPA_MFPL_PA0MFP_PWM1_CH5         /*!< GPA_MFPL PA0 setting for PWM1_CH5       */
#define SC0_CLK_PA0              SYS_GPA_MFPL_PA0MFP_SC0_CLK          /*!< GPA_MFPL PA0 setting for SC0_CLK        */
#define SC0_CLK_PE11             SYS_GPE_MFPH_PE11MFP_SC0_CLK         /*!< GPE_MFPH PE11 setting for SC0_CLK       */
#define SC0_CLK_PC1              SYS_GPC_MFPL_PC1MFP_SC0_CLK          /*!< GPC_MFPL PC1 setting for SC0_CLK        */
#define SC0_DAT_PA1              SYS_GPA_MFPL_PA1MFP_SC0_DAT          /*!< GPA_MFPL PA1 setting for SC0_DAT        */
#define SC0_DAT_PC0              SYS_GPC_MFPL_PC0MFP_SC0_DAT          /*!< GPC_MFPL PC0 setting for SC0_DAT        */
#define SC0_DAT_PE10             SYS_GPE_MFPH_PE10MFP_SC0_DAT         /*!< GPE_MFPH PE10 setting for SC0_DAT       */
#define SC0_PWR_PE8              SYS_GPE_MFPH_PE8MFP_SC0_PWR          /*!< GPE_MFPH PE8 setting for SC0_PWR        */
#define SC0_PWR_PA8              SYS_GPA_MFPH_PA8MFP_SC0_PWR          /*!< GPA_MFPH PA8 setting for SC0_PWR        */
#define SC0_PWR_PA3              SYS_GPA_MFPL_PA3MFP_SC0_PWR          /*!< GPA_MFPL PA3 setting for SC0_PWR        */
#define SC0_PWR_PE4              SYS_GPE_MFPL_PE4MFP_SC0_PWR          /*!< GPE_MFPL PE4 setting for SC0_PWR        */
#define SC0_PWR_PC3              SYS_GPC_MFPL_PC3MFP_SC0_PWR          /*!< GPC_MFPL PC3 setting for SC0_PWR        */
#define SC0_RST_PA2              SYS_GPA_MFPL_PA2MFP_SC0_RST          /*!< GPA_MFPL PA2 setting for SC0_RST        */
#define SC0_RST_PB1              SYS_GPB_MFPL_PB1MFP_SC0_RST          /*!< GPB_MFPL PB1 setting for SC0_RST        */
#define SC0_RST_PC2              SYS_GPC_MFPL_PC2MFP_SC0_RST          /*!< GPC_MFPL PC2 setting for SC0_RST        */
#define SC0_RST_PE5              SYS_GPE_MFPL_PE5MFP_SC0_RST          /*!< GPE_MFPL PE5 setting for SC0_RST        */
#define SC0_RST_PE9              SYS_GPE_MFPH_PE9MFP_SC0_RST          /*!< GPE_MFPH PE9 setting for SC0_RST        */
#define SC0_RST_PA9              SYS_GPA_MFPH_PA9MFP_SC0_RST          /*!< GPA_MFPH PA9 setting for SC0_RST        */
#define SC0_nCD_PB2              SYS_GPB_MFPL_PB2MFP_SC0_nCD          /*!< GPB_MFPL PB2 setting for SC0_nCD        */
#define SC0_nCD_PE0              SYS_GPE_MFPL_PE0MFP_SC0_nCD          /*!< GPE_MFPL PE0 setting for SC0_nCD        */
#define SC0_nCD_PE1              SYS_GPE_MFPL_PE1MFP_SC0_nCD          /*!< GPE_MFPL PE1 setting for SC0_nCD        */
#define SC0_nCD_PC4              SYS_GPC_MFPL_PC4MFP_SC0_nCD          /*!< GPC_MFPL PC4 setting for SC0_nCD        */
#define SC1_CLK_PD0              SYS_GPD_MFPL_PD0MFP_SC1_CLK          /*!< GPD_MFPL PD0 setting for SC1_CLK        */
#define SC1_CLK_PA11             SYS_GPA_MFPH_PA11MFP_SC1_CLK         /*!< GPA_MFPH PA11 setting for SC1_CLK       */
#define SC1_DAT_PA10             SYS_GPA_MFPH_PA10MFP_SC1_DAT         /*!< GPA_MFPH PA10 setting for SC1_DAT       */
#define SC1_DAT_PB7              SYS_GPB_MFPL_PB7MFP_SC1_DAT          /*!< GPB_MFPL PB7 setting for SC1_DAT        */
#define SC1_PWR_PA9              SYS_GPA_MFPH_PA9MFP_SC1_PWR          /*!< GPA_MFPH PA9 setting for SC1_PWR        */
#define SC1_PWR_PB6              SYS_GPB_MFPL_PB6MFP_SC1_PWR          /*!< GPB_MFPL PB6 setting for SC1_PWR        */
#define SC1_RST_PA8              SYS_GPA_MFPH_PA8MFP_SC1_RST          /*!< GPA_MFPH PA8 setting for SC1_RST        */
#define SC1_RST_PB5              SYS_GPB_MFPL_PB5MFP_SC1_RST          /*!< GPB_MFPL PB5 setting for SC1_RST        */
#define SC1_nCD_PB4              SYS_GPB_MFPL_PB4MFP_SC1_nCD          /*!< GPB_MFPL PB4 setting for SC1_nCD        */
#define SC1_nCD_PF5              SYS_GPF_MFPL_PF5MFP_SC1_nCD          /*!< GPF_MFPL PF5 setting for SC1_nCD        */
#define SPI0_CLK_PC0             SYS_GPC_MFPL_PC0MFP_SPI0_CLK         /*!< GPC_MFPL PC0 setting for SPI0_CLK       */
#define SPI0_CLK_PE0             SYS_GPE_MFPL_PE0MFP_SPI0_CLK         /*!< GPE_MFPL PE0 setting for SPI0_CLK       */
#define SPI0_CLK_PB7             SYS_GPB_MFPL_PB7MFP_SPI0_CLK         /*!< GPB_MFPL PB7 setting for SPI0_CLK       */
#define SPI0_CLK_PE13            SYS_GPE_MFPH_PE13MFP_SPI0_CLK        /*!< GPE_MFPH PE13 setting for SPI0_CLK      */
#define SPI0_CLK_PC12            SYS_GPC_MFPH_PC12MFP_SPI0_CLK        /*!< GPC_MFPH PC12 setting for SPI0_CLK      */
#define SPI0_CLK_PB2             SYS_GPB_MFPL_PB2MFP_SPI0_CLK         /*!< GPB_MFPL PB2 setting for SPI0_CLK       */
#define SPI0_I2SMCLK_PC5         SYS_GPC_MFPL_PC5MFP_SPI0_I2SMCLK     /*!< GPC_MFPL PC5 setting for SPI0_I2SMCLK   */
#define SPI0_I2SMCLK_PD7         SYS_GPD_MFPL_PD7MFP_SPI0_I2SMCLK     /*!< GPD_MFPL PD7 setting for SPI0_I2SMCLK   */
#define SPI0_I2SMCLK_PC9         SYS_GPC_MFPH_PC9MFP_SPI0_I2SMCLK     /*!< GPC_MFPH PC9 setting for SPI0_I2SMCLK   */
#define SPI0_I2SMCLK_PD0         SYS_GPD_MFPL_PD0MFP_SPI0_I2SMCLK     /*!< GPD_MFPL PD0 setting for SPI0_I2SMCLK   */
#define SPI0_I2SMCLK_PD3         SYS_GPD_MFPL_PD3MFP_SPI0_I2SMCLK     /*!< GPD_MFPL PD3 setting for SPI0_I2SMCLK   */
#define SPI0_MISO_PC4            SYS_GPC_MFPL_PC4MFP_SPI0_MISO        /*!< GPC_MFPL PC4 setting for SPI0_MISO      */
#define SPI0_MISO_PC11           SYS_GPC_MFPH_PC11MFP_SPI0_MISO       /*!< GPC_MFPH PC11 setting for SPI0_MISO     */
#define SPI0_MISO_PB3            SYS_GPB_MFPL_PB3MFP_SPI0_MISO        /*!< GPB_MFPL PB3 setting for SPI0_MISO      */
#define SPI0_MISO_PB6            SYS_GPB_MFPL_PB6MFP_SPI0_MISO        /*!< GPB_MFPL PB6 setting for SPI0_MISO      */
#define SPI0_MISO_PE10           SYS_GPE_MFPH_PE10MFP_SPI0_MISO       /*!< GPE_MFPH PE10 setting for SPI0_MISO     */
#define SPI0_MOSI_PC10           SYS_GPC_MFPH_PC10MFP_SPI0_MOSI       /*!< GPC_MFPH PC10 setting for SPI0_MOSI     */
#define SPI0_MOSI_PB5            SYS_GPB_MFPL_PB5MFP_SPI0_MOSI        /*!< GPB_MFPL PB5 setting for SPI0_MOSI      */
#define SPI0_MOSI_PE11           SYS_GPE_MFPH_PE11MFP_SPI0_MOSI       /*!< GPE_MFPH PE11 setting for SPI0_MOSI     */
#define SPI0_MOSI_PC3            SYS_GPC_MFPL_PC3MFP_SPI0_MOSI        /*!< GPC_MFPL PC3 setting for SPI0_MOSI      */
#define SPI0_SS_PE12             SYS_GPE_MFPH_PE12MFP_SPI0_SS         /*!< GPE_MFPH PE12 setting for SPI0_SS       */
#define SPI0_SS_PC2              SYS_GPC_MFPL_PC2MFP_SPI0_SS          /*!< GPC_MFPL PC2 setting for SPI0_SS        */
#define SPI0_SS_PC13             SYS_GPC_MFPH_PC13MFP_SPI0_SS         /*!< GPC_MFPH PC13 setting for SPI0_SS       */
#define SPI0_SS_PB4              SYS_GPB_MFPL_PB4MFP_SPI0_SS          /*!< GPB_MFPL PB4 setting for SPI0_SS        */
#define SPI1_CLK_PA7             SYS_GPA_MFPL_PA7MFP_SPI1_CLK         /*!< GPA_MFPL PA7 setting for SPI1_CLK       */
#define SPI1_CLK_PD15            SYS_GPD_MFPH_PD15MFP_SPI1_CLK        /*!< GPD_MFPH PD15 setting for SPI1_CLK      */
#define SPI1_CLK_PE10            SYS_GPE_MFPH_PE10MFP_SPI1_CLK        /*!< GPE_MFPH PE10 setting for SPI1_CLK      */
#define SPI1_CLK_PB2             SYS_GPB_MFPL_PB2MFP_SPI1_CLK         /*!< GPB_MFPL PB2 setting for SPI1_CLK       */
#define SPI1_CLK_PE13            SYS_GPE_MFPH_PE13MFP_SPI1_CLK        /*!< GPE_MFPH PE13 setting for SPI1_CLK      */
#define SPI1_CLK_PB7             SYS_GPB_MFPL_PB7MFP_SPI1_CLK         /*!< GPB_MFPL PB7 setting for SPI1_CLK       */
#define SPI1_CLK_PD4             SYS_GPD_MFPL_PD4MFP_SPI1_CLK         /*!< GPD_MFPL PD4 setting for SPI1_CLK       */
#define SPI1_I2SMCLK_PA9         SYS_GPA_MFPH_PA9MFP_SPI1_I2SMCLK     /*!< GPA_MFPH PA9 setting for SPI1_I2SMCLK   */
#define SPI1_I2SMCLK_PD0         SYS_GPD_MFPL_PD0MFP_SPI1_I2SMCLK     /*!< GPD_MFPL PD0 setting for SPI1_I2SMCLK   */
#define SPI1_I2SMCLK_PA12        SYS_GPA_MFPH_PA12MFP_SPI1_I2SMCLK    /*!< GPA_MFPH PA12 setting for SPI1_I2SMCLK  */
#define SPI1_MISO_PB3            SYS_GPB_MFPL_PB3MFP_SPI1_MISO        /*!< GPB_MFPL PB3 setting for SPI1_MISO      */
#define SPI1_MISO_PA6            SYS_GPA_MFPL_PA6MFP_SPI1_MISO        /*!< GPA_MFPL PA6 setting for SPI1_MISO      */
#define SPI1_MISO_PD5            SYS_GPD_MFPL_PD5MFP_SPI1_MISO        /*!< GPD_MFPL PD5 setting for SPI1_MISO      */
#define SPI1_MISO_PD14           SYS_GPD_MFPH_PD14MFP_SPI1_MISO       /*!< GPD_MFPH PD14 setting for SPI1_MISO     */
#define SPI1_MISO_PB6            SYS_GPB_MFPL_PB6MFP_SPI1_MISO        /*!< GPB_MFPL PB6 setting for SPI1_MISO      */
#define SPI1_MISO_PE10           SYS_GPE_MFPH_PE10MFP_SPI1_MISO       /*!< GPE_MFPH PE10 setting for SPI1_MISO     */
#define SPI1_MISO_PE11           SYS_GPE_MFPH_PE11MFP_SPI1_MISO       /*!< GPE_MFPH PE11 setting for SPI1_MISO     */
#define SPI1_MOSI_PE12           SYS_GPE_MFPH_PE12MFP_SPI1_MOSI       /*!< GPE_MFPH PE12 setting for SPI1_MOSI     */
#define SPI1_MOSI_PE3            SYS_GPE_MFPL_PE3MFP_SPI1_MOSI        /*!< GPE_MFPL PE3 setting for SPI1_MOSI      */
#define SPI1_MOSI_PB5            SYS_GPB_MFPL_PB5MFP_SPI1_MOSI        /*!< GPB_MFPL PB5 setting for SPI1_MOSI      */
#define SPI1_MOSI_PA5            SYS_GPA_MFPL_PA5MFP_SPI1_MOSI        /*!< GPA_MFPL PA5 setting for SPI1_MOSI      */
#define SPI1_MOSI_PE11           SYS_GPE_MFPH_PE11MFP_SPI1_MOSI       /*!< GPE_MFPH PE11 setting for SPI1_MOSI     */
#define SPI1_MOSI_PD13           SYS_GPD_MFPH_PD13MFP_SPI1_MOSI       /*!< GPD_MFPH PD13 setting for SPI1_MOSI     */
#define SPI1_SS_PB4              SYS_GPB_MFPL_PB4MFP_SPI1_SS          /*!< GPB_MFPL PB4 setting for SPI1_SS        */
#define SPI1_SS_PE12             SYS_GPE_MFPH_PE12MFP_SPI1_SS         /*!< GPE_MFPH PE12 setting for SPI1_SS       */
#define SPI1_SS_PD6              SYS_GPD_MFPL_PD6MFP_SPI1_SS          /*!< GPD_MFPL PD6 setting for SPI1_SS        */
#define SPI1_SS_PA4              SYS_GPA_MFPL_PA4MFP_SPI1_SS          /*!< GPA_MFPL PA4 setting for SPI1_SS        */
#define SPI1_SS_PE13             SYS_GPE_MFPH_PE13MFP_SPI1_SS         /*!< GPE_MFPH PE13 setting for SPI1_SS       */
#define SPI1_SS_PD12             SYS_GPD_MFPH_PD12MFP_SPI1_SS         /*!< GPD_MFPH PD12 setting for SPI1_SS       */
#define TM0_PD4                  SYS_GPD_MFPL_PD4MFP_TM0              /*!< GPD_MFPL PD4 setting for TM0            */
#define TM0_PD1                  SYS_GPD_MFPL_PD1MFP_TM0              /*!< GPD_MFPL PD1 setting for TM0            */
#define TM0_PE8                  SYS_GPE_MFPH_PE8MFP_TM0              /*!< GPE_MFPH PE8 setting for TM0            */
#define TM0_EXT_PD2              SYS_GPD_MFPL_PD2MFP_TM0_EXT          /*!< GPD_MFPL PD2 setting for TM0_EXT        */
#define TM0_EXT_PB3              SYS_GPB_MFPL_PB3MFP_TM0_EXT          /*!< GPB_MFPL PB3 setting for TM0_EXT        */
#define TM0_EXT_PE10             SYS_GPE_MFPH_PE10MFP_TM0_EXT         /*!< GPE_MFPH PE10 setting for TM0_EXT       */
#define TM0_EXT_PA7              SYS_GPA_MFPL_PA7MFP_TM0_EXT          /*!< GPA_MFPL PA7 setting for TM0_EXT        */
#define TM1_PA8                  SYS_GPA_MFPH_PA8MFP_TM1              /*!< GPA_MFPH PA8 setting for TM1            */
#define TM1_PD7                  SYS_GPD_MFPL_PD7MFP_TM1              /*!< GPD_MFPL PD7 setting for TM1            */
#define TM1_PE9                  SYS_GPE_MFPH_PE9MFP_TM1              /*!< GPE_MFPH PE9 setting for TM1            */
#define TM1_PD5                  SYS_GPD_MFPL_PD5MFP_TM1              /*!< GPD_MFPL PD5 setting for TM1            */
#define TM1_EXT_PD3              SYS_GPD_MFPL_PD3MFP_TM1_EXT          /*!< GPD_MFPL PD3 setting for TM1_EXT        */
#define TM1_EXT_PB4              SYS_GPB_MFPL_PB4MFP_TM1_EXT          /*!< GPB_MFPL PB4 setting for TM1_EXT        */
#define TM1_EXT_PA6              SYS_GPA_MFPL_PA6MFP_TM1_EXT          /*!< GPA_MFPL PA6 setting for TM1_EXT         */
#define TM1_EXT_PE11             SYS_GPE_MFPH_PE11MFP_TM1_EXT         /*!< GPE_MFPH PE11 setting for TM1_EXT       */
#define TM1_EXT_PB0              SYS_GPB_MFPL_PB0MFP_TM1_EXT          /*!< GPB_MFPL PB0 setting for TM1_EXT        */
#define TM2_PA9                  SYS_GPA_MFPH_PA9MFP_TM2              /*!< GPA_MFPH PA9 setting for TM2            */
#define TM2_PB0                  SYS_GPB_MFPL_PB0MFP_TM2              /*!< GPB_MFPL PB0 setting for TM2            */
#define TM2_PA14                 SYS_GPA_MFPH_PA14MFP_TM2             /*!< GPA_MFPH PA14 setting for TM2   */
#define TM2_PD10                 SYS_GPD_MFPH_PD10MFP_TM2             /*!< GPD_MFPH PD10 setting for TM2           */
#define TM2_PD8                  SYS_GPD_MFPH_PD8MFP_TM2              /*!< GPD_MFPH PD8 setting for TM2            */
#define TM2_PD3                  SYS_GPD_MFPL_PD3MFP_TM2              /*!< GPD_MFPL PD3 setting for TM2            */
#define TM2_EXT_PE12             SYS_GPE_MFPH_PE12MFP_TM2_EXT         /*!< GPE_MFPH PE12 setting for TM2_EXT       */
#define TM2_EXT_PB2              SYS_GPB_MFPL_PB2MFP_TM2_EXT          /*!< GPB_MFPL PB2 setting for TM2_EXT        */
#define TM2_EXT_PE0              SYS_GPE_MFPL_PE0MFP_TM2_EXT          /*!< GPE_MFPL PE0 setting for TM2_EXT        */
#define TM2_EXT_PA5              SYS_GPA_MFPL_PA5MFP_TM2_EXT          /*!< GPA_MFPL PA5 setting for TM2_EXT        */
#define TM3_PD9                  SYS_GPD_MFPH_PD9MFP_TM3              /*!< GPD_MFPH PD9 setting for TM3            */
#define TM3_PB1                  SYS_GPB_MFPL_PB1MFP_TM3              /*!< GPB_MFPL PB1 setting for TM3            */
#define TM3_PA15                 SYS_GPA_MFPH_PA15MFP_TM3             /*!< GPA_MFPH PA15 setting for TM3   */
#define TM3_PD11                 SYS_GPD_MFPH_PD11MFP_TM3             /*!< GPD_MFPH PD11 setting for TM3           */
#define TM3_EXT_PE1              SYS_GPE_MFPL_PE1MFP_TM3_EXT          /*!< GPE_MFPL PE1 setting for TM3_EXT        */
#define TM3_EXT_PA4              SYS_GPA_MFPL_PA4MFP_TM3_EXT          /*!< GPA_MFPL PA4 setting for TM3_EXT        */
#define TM3_EXT_PF5              SYS_GPF_MFPL_PF5MFP_TM3_EXT          /*!< GPF_MFPL PF5 setting for TM3_EXT        */
#define TM3_EXT_PE13             SYS_GPE_MFPH_PE13MFP_TM3_EXT         /*!< GPE_MFPH PE13 setting for TM3_EXT       */
#define TM_BRAKE0_PB2            SYS_GPB_MFPL_PB2MFP_TM_BRAKE0        /*!< GPB_MFPL PB2 setting for TM_BRAKE0      */
#define TM_BRAKE0_PA8            SYS_GPA_MFPH_PA8MFP_TM_BRAKE0        /*!< GPA_MFPH PA8 setting for TM_BRAKE0      */
#define TM_BRAKE0_PF5            SYS_GPF_MFPL_PF5MFP_TM_BRAKE0        /*!< GPF_MFPL PF5 setting for TM_BRAKE0      */
#define TM_BRAKE1_PA9            SYS_GPA_MFPH_PA9MFP_TM_BRAKE1        /*!< GPA_MFPH PA9 setting for TM_BRAKE1      */
#define TM_BRAKE1_PA7            SYS_GPA_MFPL_PA7MFP_TM_BRAKE1        /*!< GPA_MFPL PA7 setting for TM_BRAKE1      */
#define TM_BRAKE1_PB3            SYS_GPB_MFPL_PB3MFP_TM_BRAKE1        /*!< GPB_MFPL PB3 setting for TM_BRAKE1      */
#define TM_BRAKE2_PB8            SYS_GPB_MFPH_PB8MFP_TM_BRAKE2        /*!< GPB_MFPH PB8 setting for TM_BRAKE2      */
#define TM_BRAKE2_PA12           SYS_GPA_MFPH_PA12MFP_TM_BRAKE2       /*!< GPA_MFPH PA12 setting for TM_BRAKE2     */
#define TM_BRAKE2_PA6            SYS_GPA_MFPL_PA6MFP_TM_BRAKE2        /*!< GPA_MFPL PA6 setting for TM_BRAKE2      */
#define TM_BRAKE3_PA5            SYS_GPA_MFPL_PA5MFP_TM_BRAKE3        /*!< GPA_MFPL PA5 setting for TM_BRAKE3      */
#define TM_BRAKE3_PA13           SYS_GPA_MFPH_PA13MFP_TM_BRAKE3       /*!< GPA_MFPH PA12 setting for TM_BRAKE3     */
#define TM_BRAKE3_PE2            SYS_GPE_MFPL_PE2MFP_TM_BRAKE3        /*!< GPE_MFPL PE2 setting for TM_BRAKE3      */
#define UART0_RXD_PA3            SYS_GPA_MFPL_PA3MFP_UART0_RXD        /*!< GPA_MFPL PA3 setting for UART0_RXD      */
#define UART0_RXD_PE6            SYS_GPE_MFPL_PE6MFP_UART0_RXD        /*!< GPE_MFPL PE6 setting for UART0_RXD      */
#define UART0_RXD_PD9            SYS_GPD_MFPH_PD9MFP_UART0_RXD        /*!< GPD_MFPH PD9 setting for UART0_RXD      */
#define UART0_RXD_PD0            SYS_GPD_MFPL_PD0MFP_UART0_RXD        /*!< GPD_MFPL PD0 setting for UART0_RXD      */
#define UART0_RXD_PD13           SYS_GPD_MFPH_PD13MFP_UART0_RXD       /*!< GPD_MFPH PD13 setting for UART0_RXD     */
#define UART0_RXD_PD6            SYS_GPD_MFPL_PD6MFP_UART0_RXD        /*!< GPD_MFPL PD6 setting for UART0_RXD      */
#define UART0_TXD_PD1            SYS_GPD_MFPL_PD1MFP_UART0_TXD        /*!< GPD_MFPL PD1 setting for UART0_TXD      */
#define UART0_TXD_PE7            SYS_GPE_MFPL_PE7MFP_UART0_TXD        /*!< GPE_MFPL PE7 setting for UART0_TXD      */
#define UART0_TXD_PD12           SYS_GPD_MFPH_PD12MFP_UART0_TXD       /*!< GPD_MFPH PD12 setting for UART0_TXD     */
#define UART0_TXD_PA2            SYS_GPA_MFPL_PA2MFP_UART0_TXD        /*!< GPA_MFPL PA2 setting for UART0_TXD      */
#define UART0_nCTS_PD8           SYS_GPD_MFPH_PD8MFP_UART0_nCTS       /*!< GPD_MFPH PD8 setting for UART0_nCTS     */
#define UART0_nCTS_PD14          SYS_GPD_MFPH_PD14MFP_UART0_nCTS      /*!< GPD_MFPH PD14 setting for UART0_nCTS    */
#define UART0_nCTS_PA2           SYS_GPA_MFPL_PA2MFP_UART0_nCTS       /*!< GPA_MFPL PA2 setting for UART0_nCTS     */
#define UART0_nRTS_PC8           SYS_GPC_MFPH_PC8MFP_UART0_nRTS       /*!< GPC_MFPH PC8 setting for UART0_nRTS     */
#define UART0_nRTS_PD15          SYS_GPD_MFPH_PD15MFP_UART0_nRTS      /*!< GPD_MFPH PD15 setting for UART0_nRTS    */
#define UART0_nRTS_PA3           SYS_GPA_MFPL_PA3MFP_UART0_nRTS       /*!< GPA_MFPL PA3 setting for UART0_nRTS     */
#define UART1_RXD_PA1            SYS_GPA_MFPL_PA1MFP_UART1_RXD        /*!< GPA_MFPL PA1 setting for UART1_RXD      */
#define UART1_RXD_PE9            SYS_GPE_MFPH_PE9MFP_UART1_RXD        /*!< GPE_MFPH PE9 setting for UART1_RXD      */
#define UART1_RXD_PA9            SYS_GPA_MFPH_PA9MFP_UART1_RXD        /*!< GPA_MFPH PA9 setting for UART1_RXD      */
#define UART1_RXD_PB2            SYS_GPB_MFPL_PB2MFP_UART1_RXD        /*!< GPB_MFPL PB2 setting for UART1_RXD      */
#define UART1_RXD_PA12           SYS_GPA_MFPH_PA12MFP_UART1_RXD       /*!< GPA_MFPH PA12 setting for UART1_RXD     */
#define UART1_RXD_PE13           SYS_GPE_MFPH_PE13MFP_UART1_RXD       /*!< GPE_MFPH PE13 setting for UART1_RXD     */
#define UART1_TXD_PA13           SYS_GPA_MFPH_PA13MFP_UART1_TXD       /*!< GPA_MFPH PA13 setting for UART1_TXD     */
#define UART1_TXD_PB3            SYS_GPB_MFPL_PB3MFP_UART1_TXD        /*!< GPB_MFPL PB3 setting for UART1_TXD      */
#define UART1_TXD_PE8            SYS_GPE_MFPH_PE8MFP_UART1_TXD        /*!< GPE_MFPH PE8 setting for UART1_TXD      */
#define UART1_TXD_PA0            SYS_GPA_MFPL_PA0MFP_UART1_TXD        /*!< GPA_MFPL PA0 setting for UART1_TXD      */
#define UART1_TXD_PE12           SYS_GPE_MFPH_PE12MFP_UART1_TXD       /*!< GPE_MFPH PE12 setting for UART1_TXD     */
#define UART1_TXD_PA8            SYS_GPA_MFPH_PA8MFP_UART1_TXD        /*!< GPA_MFPH PA8 setting for UART1_TXD      */
#define UART1_nCTS_PB4           SYS_GPB_MFPL_PB4MFP_UART1_nCTS       /*!< GPB_MFPL PB4 setting for UART1_nCTS     */
#define UART1_nCTS_PA10          SYS_GPA_MFPH_PA10MFP_UART1_nCTS      /*!< GPA_MFPH PA10 setting for UART1_nCTS    */
#define UART1_nCTS_PA0           SYS_GPA_MFPL_PA0MFP_UART1_nCTS       /*!< GPA_MFPL PA0 setting for UART1_nCTS     */
#define UART1_nCTS_PE10          SYS_GPE_MFPH_PE10MFP_UART1_nCTS      /*!< GPE_MFPH PE10 setting for UART1_nCTS    */
#define UART1_nRTS_PA11          SYS_GPA_MFPH_PA11MFP_UART1_nRTS      /*!< GPA_MFPH PA11 setting for UART1_nRTS    */
#define UART1_nRTS_PB8           SYS_GPB_MFPH_PB8MFP_UART1_nRTS       /*!< GPB_MFPH PB8 setting for UART1_nRTS     */
#define UART1_nRTS_PA1           SYS_GPA_MFPL_PA1MFP_UART1_nRTS       /*!< GPA_MFPL PA1 setting for UART1_nRTS     */
#define UART1_nRTS_PE11          SYS_GPE_MFPH_PE11MFP_UART1_nRTS      /*!< GPE_MFPH PE11 setting for UART1_nRTS    */
#define UART1_nRTS_PE2           SYS_GPE_MFPL_PE2MFP_UART1_nRTS       /*!< GPE_MFPL PE2 setting for UART1_nRTS     */
#define UART2_RXD_PB0            SYS_GPB_MFPL_PB0MFP_UART2_RXD        /*!< GPB_MFPL PB0 setting for UART2_RXD      */
#define UART2_RXD_PC3            SYS_GPC_MFPL_PC3MFP_UART2_RXD        /*!< GPC_MFPL PC3 setting for UART2_RXD      */
#define UART2_RXD_PE3            SYS_GPE_MFPL_PE3MFP_UART2_RXD        /*!< GPE_MFPL PE3 setting for UART2_RXD      */
#define UART2_RXD_PB5            SYS_GPB_MFPL_PB5MFP_UART2_RXD        /*!< GPB_MFPL PB5 setting for UART2_RXD      */
#define UART2_RXD_PA12           SYS_GPA_MFPH_PA12MFP_UART2_RXD       /*!< GPA_MFPH PA12 setting for UART2_RXD     */
#define UART2_RXD_PB4            SYS_GPB_MFPL_PB4MFP_UART2_RXD        /*!< GPB_MFPL PB4 setting for UART2_RXD      */
#define UART2_TXD_PD6            SYS_GPD_MFPL_PD6MFP_UART2_TXD        /*!< GPD_MFPL PD6 setting for UART2_TXD      */
#define UART2_TXD_PB1            SYS_GPB_MFPL_PB1MFP_UART2_TXD        /*!< GPB_MFPL PB1 setting for UART2_TXD      */
#define UART2_TXD_PA13           SYS_GPA_MFPH_PA13MFP_UART2_TXD       /*!< GPA_MFPH PA13 setting for UART2_TXD     */
#define UART2_TXD_PC2            SYS_GPC_MFPL_PC2MFP_UART2_TXD        /*!< GPC_MFPL PC2 setting for UART2_TXD      */
#define UART2_nCTS_PC0           SYS_GPC_MFPL_PC0MFP_UART2_nCTS       /*!< GPC_MFPL PC0 setting for UART2_nCTS     */
#define UART2_nCTS_PD5           SYS_GPD_MFPL_PD5MFP_UART2_nCTS       /*!< GPD_MFPL PD5 setting for UART2_nCTS     */
#define UART2_nCTS_PA14          SYS_GPA_MFPH_PA14MFP_UART2_nCTS      /*!< GPA_MFPH PA14 setting for UART2_nCTS    */
#define UART2_nRTS_PA15          SYS_GPA_MFPH_PA15MFP_UART2_nRTS      /*!< GPA_MFPH PA15 setting for UART2_nRTS    */
#define UART2_nRTS_PD4           SYS_GPD_MFPL_PD4MFP_UART2_nRTS       /*!< GPD_MFPL PD4 setting for UART2_nRTS     */
#define UART2_nRTS_PC1           SYS_GPC_MFPL_PC1MFP_UART2_nRTS       /*!< GPC_MFPL PC1 setting for UART2_nRTS     */
#define USCI0_CLK_PB9            SYS_GPB_MFPH_PB9MFP_USCI0_CLK        /*!< GPB_MFPH PB9 setting for USCI0_CLK      */
#define USCI0_CLK_PC4            SYS_GPC_MFPL_PC4MFP_USCI0_CLK        /*!< GPC_MFPL PC4 setting for USCI0_CLK      */
#define USCI0_CLK_PE5            SYS_GPE_MFPL_PE5MFP_USCI0_CLK        /*!< GPE_MFPL PE5 setting for USCI0_CLK      */
#define USCI0_CTL0_PC3           SYS_GPC_MFPL_PC3MFP_USCI0_CTL0       /*!< GPC_MFPL PC3 setting for USCI0_CTL0     */
#define USCI0_CTL0_PB8           SYS_GPB_MFPH_PB8MFP_USCI0_CTL0       /*!< GPB_MFPH PB8 setting for USCI0_CTL0     */
#define USCI0_CTL0_PE4           SYS_GPE_MFPL_PE4MFP_USCI0_CTL0       /*!< GPE_MFPL PE4 setting for USCI0_CTL0     */
#define USCI0_CTL0_PE2           SYS_GPE_MFPL_PE2MFP_USCI0_CTL0       /*!< GPE_MFPL PE2 setting for USCI0_CTL0     */
#define USCI0_CTL1_PC7           SYS_GPC_MFPL_PC7MFP_USCI0_CTL1       /*!< GPC_MFPL PC7 setting for USCI0_CTL1     */
#define USCI0_CTL1_PB4           SYS_GPB_MFPL_PB4MFP_USCI0_CTL1       /*!< GPB_MFPL PB4 setting for USCI0_CTL1     */
#define USCI0_CTL1_PC2           SYS_GPC_MFPL_PC2MFP_USCI0_CTL1       /*!< GPC_MFPL PC2 setting for USCI0_CTL1     */
#define USCI0_DAT0_PC5           SYS_GPC_MFPL_PC5MFP_USCI0_DAT0       /*!< GPC_MFPL PC5 setting for USCI0_DAT0     */
#define USCI0_DAT0_PC0           SYS_GPC_MFPL_PC0MFP_USCI0_DAT0       /*!< GPC_MFPL PC0 setting for USCI0_DAT0     */
#define USCI0_DAT0_PB2           SYS_GPB_MFPL_PB2MFP_USCI0_DAT0       /*!< GPB_MFPL PB2 setting for USCI0_DAT0     */
#define USCI0_DAT1_PC1           SYS_GPC_MFPL_PC1MFP_USCI0_DAT1       /*!< GPC_MFPL PC1 setting for USCI0_DAT1     */
#define USCI0_DAT1_PB3           SYS_GPB_MFPL_PB3MFP_USCI0_DAT1       /*!< GPB_MFPL PB3 setting for USCI0_DAT1     */
#define USCI0_DAT1_PC6           SYS_GPC_MFPL_PC6MFP_USCI0_DAT1       /*!< GPC_MFPL PC6 setting for USCI0_DAT1     */
#define USCI1_CLK_PD15           SYS_GPD_MFPH_PD15MFP_USCI1_CLK       /*!< GPD_MFPH PD15 setting for USCI1_CLK     */
#define USCI1_CLK_PA3            SYS_GPA_MFPL_PA3MFP_USCI1_CLK        /*!< GPA_MFPL PA3 setting for USCI1_CLK      */
#define USCI1_CLK_PA15           SYS_GPA_MFPH_PA15MFP_USCI1_CLK       /*!< GPA_MFPH PA15 setting for USCI1_CLK     */
#define USCI1_CTL0_PA2           SYS_GPA_MFPL_PA2MFP_USCI1_CTL0       /*!< GPA_MFPL PA2 setting for USCI1_CTL0     */
#define USCI1_CTL0_PA0           SYS_GPA_MFPL_PA0MFP_USCI1_CTL0       /*!< GPA_MFPL PA0 setting for USCI1_CTL0     */
#define USCI1_CTL0_PD12          SYS_GPD_MFPH_PD12MFP_USCI1_CTL0      /*!< GPD_MFPH PD12 setting for USCI1_CTL0    */
#define USCI1_CTL1_PA1           SYS_GPA_MFPL_PA1MFP_USCI1_CTL1       /*!< GPA_MFPL PA1 setting for USCI1_CTL1     */
#define USCI1_CTL1_PA14          SYS_GPA_MFPH_PA14MFP_USCI1_CTL1      /*!< GPA_MFPH PA14 setting for USCI1_CTL1    */
#define USCI1_CTL1_PD7           SYS_GPD_MFPL_PD7MFP_USCI1_CTL1       /*!< GPD_MFPL PD7 setting for USCI1_CTL1     */
#define USCI1_DAT0_PD14          SYS_GPD_MFPH_PD14MFP_USCI1_DAT0      /*!< GPD_MFPH PD14 setting for USCI1_DAT0    */
#define USCI1_DAT0_PB0           SYS_GPB_MFPL_PB0MFP_USCI1_DAT0       /*!< GPB_MFPL PB0 setting for USCI1_DAT0     */
#define USCI1_DAT1_PB1           SYS_GPB_MFPL_PB1MFP_USCI1_DAT1       /*!< GPB_MFPL PB1 setting for USCI1_DAT1     */
#define USCI1_DAT1_PD13          SYS_GPD_MFPH_PD13MFP_USCI1_DAT1      /*!< GPD_MFPH PD13 setting for USCI1_DAT1    */
#define USCI2_CLK_PC11           SYS_GPC_MFPH_PC11MFP_USCI2_CLK       /*!< GPC_MFPH PC11 setting for USCI2_CLK     */
#define USCI2_CLK_PD1            SYS_GPD_MFPL_PD1MFP_USCI2_CLK        /*!< GPD_MFPL PD1 setting for USCI2_CLK      */
#define USCI2_CLK_PF2            SYS_GPF_MFPL_PF2MFP_USCI2_CLK        /*!< GPF_MFPL PF2 setting for USCI2_CLK      */
#define USCI2_CTL0_PD0           SYS_GPD_MFPL_PD0MFP_USCI2_CTL0       /*!< GPD_MFPL PD0 setting for USCI2_CTL0     */
#define USCI2_CTL0_PD9           SYS_GPD_MFPH_PD9MFP_USCI2_CTL0       /*!< GPD_MFPH PD9 setting for USCI2_CTL0     */
#define USCI2_CTL0_PC12          SYS_GPC_MFPH_PC12MFP_USCI2_CTL0      /*!< GPC_MFPH PC12 setting for USCI2_CTL0    */
#define USCI2_CTL0_PF1           SYS_GPF_MFPL_PF1MFP_USCI2_CTL0       /*!< GPF_MFPL PF1 setting for USCI2_CTL0     */
#define USCI2_CTL1_PC9           SYS_GPC_MFPH_PC9MFP_USCI2_CTL1       /*!< GPC_MFPH PC9 setting for USCI2_CTL1     */
#define USCI2_CTL1_PF0           SYS_GPF_MFPL_PF0MFP_USCI2_CTL1       /*!< GPF_MFPL PF0 setting for USCI2_CTL1     */
#define USCI2_CTL1_PD8           SYS_GPD_MFPH_PD8MFP_USCI2_CTL1       /*!< GPD_MFPH PD8 setting for USCI2_CTL1     */
#define USCI2_CTL1_PB7           SYS_GPB_MFPL_PB7MFP_USCI2_CTL1       /*!< GPB_MFPL PB7 setting for USCI2_CTL1     */
#define USCI2_DAT0_PD2           SYS_GPD_MFPL_PD2MFP_USCI2_DAT0       /*!< GPD_MFPL PD2 setting for USCI2_DAT0     */
#define USCI2_DAT0_PD10          SYS_GPD_MFPH_PD10MFP_USCI2_DAT0      /*!< GPD_MFPH PD10 setting for USCI2_DAT0    */
#define USCI2_DAT0_PC13          SYS_GPC_MFPH_PC13MFP_USCI2_DAT0      /*!< GPC_MFPH PC13 setting for USCI2_DAT0    */
#define USCI2_DAT1_PD3           SYS_GPD_MFPL_PD3MFP_USCI2_DAT1       /*!< GPD_MFPL PD3 setting for USCI2_DAT1     */
#define USCI2_DAT1_PC10          SYS_GPC_MFPH_PC10MFP_USCI2_DAT1      /*!< GPC_MFPH PC10 setting for USCI2_DAT1    */
#define USCI2_DAT1_PD11          SYS_GPD_MFPH_PD11MFP_USCI2_DAT1      /*!< GPD_MFPH PD11 setting for USCI2_DAT1    */
#define VDET_P0_PB0              SYS_GPB_MFPL_PB0MFP_VDET_P0          /*!< GPB_MFPL PB0 setting for VDET_P0        */
#define VDET_P1_PB1              SYS_GPB_MFPL_PB1MFP_VDET_P1          /*!< GPB_MFPL PB1 setting for VDET_P1        */
#define X32_IN_PF1               SYS_GPF_MFPL_PF1MFP_X32_IN           /*!< GPF_MFPL PF1 setting for X32_IN         */
#define X32_OUT_PF0              SYS_GPF_MFPL_PF0MFP_X32_OUT          /*!< GPF_MFPL PF0 setting for X32_OUT        */
#define XT1_IN_PF4               SYS_GPF_MFPL_PF4MFP_XT1_IN           /*!< GPF_MFPL PF4 setting for XT1_IN         */
#define XT1_OUT_PF3              SYS_GPF_MFPL_PF3MFP_XT1_OUT          /*!< GPF_MFPL PF3 setting for XT1_OUT        */


#define ACMP0_N_PB4_Msk          SYS_GPB_MFPL_PB4MFP_Msk              /*<! ACMP0_N         PB4      MFP Mask */
#define ACMP0_O_PD6_Msk          SYS_GPD_MFPL_PD6MFP_Msk              /*<! ACMP0_O         PD6      MFP Mask */
#define ACMP0_O_PD7_Msk          SYS_GPD_MFPL_PD7MFP_Msk              /*<! ACMP0_O         PD7      MFP Mask */
#define ACMP0_P0_PB7_Msk         SYS_GPB_MFPL_PB7MFP_Msk              /*<! ACMP0_P0        PB7      MFP Mask */
#define ACMP0_P1_PB6_Msk         SYS_GPB_MFPL_PB6MFP_Msk              /*<! ACMP0_P1        PB6      MFP Mask */
#define ACMP0_P2_PB5_Msk         SYS_GPB_MFPL_PB5MFP_Msk              /*<! ACMP0_P2        PB5      MFP Mask */
#define ACMP0_P3_PB15_Msk        SYS_GPB_MFPH_PB15MFP_Msk             /*<! ACMP0_P3        PB15     MFP Mask */
#define ACMP0_WLAT_PC0_Msk       SYS_GPC_MFPL_PC0MFP_Msk              /*<! ACMP0_WLAT      PC0      MFP Mask */
#define ACMP1_N_PD0_Msk          SYS_GPD_MFPL_PD0MFP_Msk              /*<! ACMP1_N         PD0      MFP Mask */
#define ACMP1_O_PC6_Msk          SYS_GPC_MFPL_PC6MFP_Msk              /*<! ACMP1_O         PC6      MFP Mask */
#define ACMP1_O_PC2_Msk          SYS_GPC_MFPL_PC2MFP_Msk              /*<! ACMP1_O         PC2      MFP Mask */
#define ACMP1_P0_PD3_Msk         SYS_GPD_MFPL_PD3MFP_Msk              /*<! ACMP1_P0        PD3      MFP Mask */
#define ACMP1_P1_PD2_Msk         SYS_GPD_MFPL_PD2MFP_Msk              /*<! ACMP1_P1        PD2      MFP Mask */
#define ACMP1_P2_PD1_Msk         SYS_GPD_MFPL_PD1MFP_Msk              /*<! ACMP1_P2        PD1      MFP Mask */
#define ACMP1_P3_PD9_Msk         SYS_GPD_MFPH_PD9MFP_Msk              /*<! ACMP1_P3        PD9      MFP Mask */
#define ACMP1_WLAT_PC1_Msk       SYS_GPC_MFPL_PC1MFP_Msk              /*<! ACMP1_WLAT      PC1      MFP Mask */
#define ADC0_CH0_PB0_Msk         SYS_GPB_MFPL_PB0MFP_Msk              /*<! ADC0_CH0        PB0      MFP Mask */
#define ADC0_CH1_PB1_Msk         SYS_GPB_MFPL_PB1MFP_Msk              /*<! ADC0_CH1        PB1      MFP Mask */
#define ADC0_CH10_PB13_Msk       SYS_GPB_MFPH_PB13MFP_Msk             /*<! ADC0_CH10       PB13     MFP Mask */
#define ADC0_CH11_PB14_Msk       SYS_GPB_MFPH_PB14MFP_Msk             /*<! ADC0_CH11       PB14     MFP Mask */
#define ADC0_CH12_PB15_Msk       SYS_GPB_MFPH_PB15MFP_Msk             /*<! ADC0_CH12       PB15     MFP Mask */
#define ADC0_CH13_PB5_Msk        SYS_GPB_MFPL_PB5MFP_Msk              /*<! ADC0_CH13       PB5      MFP Mask */
#define ADC0_CH14_PB6_Msk        SYS_GPB_MFPL_PB6MFP_Msk              /*<! ADC0_CH14       PB6      MFP Mask */
#define ADC0_CH15_PB7_Msk        SYS_GPB_MFPL_PB7MFP_Msk              /*<! ADC0_CH15       PB7      MFP Mask */
#define ADC0_CH16_PC8_Msk        SYS_GPC_MFPH_PC8MFP_Msk              /*<! ADC0_CH16       PC8      MFP Mask */
#define ADC0_CH17_PD8_Msk        SYS_GPD_MFPH_PD8MFP_Msk              /*<! ADC0_CH17       PD8      MFP Mask */
#define ADC0_CH18_PD9_Msk        SYS_GPD_MFPH_PD9MFP_Msk              /*<! ADC0_CH18       PD9      MFP Mask */
#define ADC0_CH19_PD1_Msk        SYS_GPD_MFPL_PD1MFP_Msk              /*<! ADC0_CH19       PD1      MFP Mask */
#define ADC0_CH2_PB2_Msk         SYS_GPB_MFPL_PB2MFP_Msk              /*<! ADC0_CH2        PB2      MFP Mask */
#define ADC0_CH3_PB3_Msk         SYS_GPB_MFPL_PB3MFP_Msk              /*<! ADC0_CH3        PB3      MFP Mask */
#define ADC0_CH4_PB4_Msk         SYS_GPB_MFPL_PB4MFP_Msk              /*<! ADC0_CH4        PB4      MFP Mask */
#define ADC0_CH5_PB8_Msk         SYS_GPB_MFPH_PB8MFP_Msk              /*<! ADC0_CH5        PB8      MFP Mask */
#define ADC0_CH6_PB9_Msk         SYS_GPB_MFPH_PB9MFP_Msk              /*<! ADC0_CH6        PB9      MFP Mask */
#define ADC0_CH7_PB10_Msk        SYS_GPB_MFPH_PB10MFP_Msk             /*<! ADC0_CH7        PB10     MFP Mask */
#define ADC0_CH8_PB11_Msk        SYS_GPB_MFPH_PB11MFP_Msk             /*<! ADC0_CH8        PB11     MFP Mask */
#define ADC0_CH9_PE2_Msk         SYS_GPE_MFPL_PE2MFP_Msk              /*<! ADC0_CH9        PE2      MFP Mask */
#define ADC0_ST_PD2_Msk          SYS_GPD_MFPL_PD2MFP_Msk              /*<! ADC0_ST         PD2      MFP Mask */
#define CLKO_PD5_Msk             SYS_GPD_MFPL_PD5MFP_Msk              /*<! CLKO            PD5      MFP Mask */
#define CLKO_PD6_Msk             SYS_GPD_MFPL_PD6MFP_Msk              /*<! CLKO            PD6      MFP Mask */
#define CLKO_PA8_Msk             SYS_GPA_MFPH_PA8MFP_Msk              /*<! CLKO            PA8      MFP Mask */
#define CLKO_PC1_Msk             SYS_GPC_MFPL_PC1MFP_Msk              /*<! CLKO            PC1      MFP Mask */
#define EBI_AD0_PA0_Msk          SYS_GPA_MFPL_PA0MFP_Msk              /*<! EBI_AD0         PA0      MFP Mask */
#define EBI_AD1_PA1_Msk          SYS_GPA_MFPL_PA1MFP_Msk              /*<! EBI_AD1         PA1      MFP Mask */
#define EBI_AD10_PC2_Msk         SYS_GPC_MFPL_PC2MFP_Msk              /*<! EBI_AD10        PC2      MFP Mask */
#define EBI_AD11_PC3_Msk         SYS_GPC_MFPL_PC3MFP_Msk              /*<! EBI_AD11        PC3      MFP Mask */
#define EBI_AD12_PC4_Msk         SYS_GPC_MFPL_PC4MFP_Msk              /*<! EBI_AD12        PC4      MFP Mask */
#define EBI_AD13_PC5_Msk         SYS_GPC_MFPL_PC5MFP_Msk              /*<! EBI_AD13        PC5      MFP Mask */
#define EBI_AD14_PC6_Msk         SYS_GPC_MFPL_PC6MFP_Msk              /*<! EBI_AD14        PC6      MFP Mask */
#define EBI_AD15_PC7_Msk         SYS_GPC_MFPL_PC7MFP_Msk              /*<! EBI_AD15        PC7      MFP Mask */
#define EBI_AD2_PA2_Msk          SYS_GPA_MFPL_PA2MFP_Msk              /*<! EBI_AD2         PA2      MFP Mask */
#define EBI_AD3_PA3_Msk          SYS_GPA_MFPL_PA3MFP_Msk              /*<! EBI_AD3         PA3      MFP Mask */
#define EBI_AD4_PA4_Msk          SYS_GPA_MFPL_PA4MFP_Msk              /*<! EBI_AD4         PA4      MFP Mask */
#define EBI_AD4_PB7_Msk          SYS_GPB_MFPL_PB7MFP_Msk              /*<! EBI_AD4         PB7      MFP Mask */
#define EBI_AD4_PE13_Msk         SYS_GPE_MFPH_PE13MFP_Msk             /*<! EBI_AD4         PE13     MFP Mask */
#define EBI_AD5_PA5_Msk          SYS_GPA_MFPL_PA5MFP_Msk              /*<! EBI_AD5         PA5      MFP Mask */
#define EBI_AD5_PE12_Msk         SYS_GPE_MFPH_PE12MFP_Msk             /*<! EBI_AD5         PE12     MFP Mask */
#define EBI_AD5_PB6_Msk          SYS_GPB_MFPL_PB6MFP_Msk              /*<! EBI_AD5         PB6      MFP Mask */
#define EBI_AD6_PE11_Msk         SYS_GPE_MFPH_PE11MFP_Msk             /*<! EBI_AD6         PE11     MFP Mask */
#define EBI_AD6_PA6_Msk          SYS_GPA_MFPL_PA6MFP_Msk              /*<! EBI_AD6         PA6      MFP Mask */
#define EBI_AD6_PB5_Msk          SYS_GPB_MFPL_PB5MFP_Msk              /*<! EBI_AD6         PB5      MFP Mask */
#define EBI_AD7_PB4_Msk          SYS_GPB_MFPL_PB4MFP_Msk              /*<! EBI_AD7         PB4      MFP Mask */
#define EBI_AD7_PA7_Msk          SYS_GPA_MFPL_PA7MFP_Msk              /*<! EBI_AD7         PA7      MFP Mask */
#define EBI_AD7_PE10_Msk         SYS_GPE_MFPH_PE10MFP_Msk             /*<! EBI_AD7         PE10     MFP Mask */
#define EBI_AD8_PC0_Msk          SYS_GPC_MFPL_PC0MFP_Msk              /*<! EBI_AD8         PC0      MFP Mask */
#define EBI_AD9_PC1_Msk          SYS_GPC_MFPL_PC1MFP_Msk              /*<! EBI_AD9         PC1      MFP Mask */
#define EBI_ADR16_PD12_Msk       SYS_GPD_MFPH_PD12MFP_Msk             /*<! EBI_ADR16       PD12     MFP Mask */
#define EBI_ADR17_PD13_Msk       SYS_GPD_MFPH_PD13MFP_Msk             /*<! EBI_ADR17       PD13     MFP Mask */
#define EBI_ADR18_PD14_Msk       SYS_GPD_MFPH_PD14MFP_Msk             /*<! EBI_ADR18       PD14     MFP Mask */
#define EBI_ADR19_PD15_Msk       SYS_GPD_MFPH_PD15MFP_Msk             /*<! EBI_ADR19       PD15     MFP Mask */
#define EBI_ALE_PB3_Msk          SYS_GPB_MFPL_PB3MFP_Msk              /*<! EBI_ALE         PB3      MFP Mask */
#define EBI_ALE_PE5_Msk          SYS_GPE_MFPL_PE5MFP_Msk              /*<! EBI_ALE         PE5      MFP Mask */
#define EBI_ALE_PD9_Msk          SYS_GPD_MFPH_PD9MFP_Msk              /*<! EBI_ALE         PD9      MFP Mask */
#define EBI_MCLK_PD3_Msk         SYS_GPD_MFPL_PD3MFP_Msk              /*<! EBI_MCLK        PD3      MFP Mask */
#define EBI_nCS0_PE4_Msk         SYS_GPE_MFPL_PE4MFP_Msk              /*<! EBI_nCS0        PE4      MFP Mask */
#define EBI_nCS0_PB2_Msk         SYS_GPB_MFPL_PB2MFP_Msk              /*<! EBI_nCS0        PB2      MFP Mask */
#define EBI_nCS0_PD8_Msk         SYS_GPD_MFPH_PD8MFP_Msk              /*<! EBI_nCS0        PD8      MFP Mask */
#define EBI_nCS1_PE0_Msk         SYS_GPE_MFPL_PE0MFP_Msk              /*<! EBI_nCS1        PE0      MFP Mask */
#define EBI_nCS1_PB15_Msk        SYS_GPB_MFPH_PB15MFP_Msk             /*<! EBI_nCS1        PB15     MFP Mask */
#define EBI_nRD_PD7_Msk          SYS_GPD_MFPL_PD7MFP_Msk              /*<! EBI_nRD         PD7      MFP Mask */
#define EBI_nRD_PD1_Msk          SYS_GPD_MFPL_PD1MFP_Msk              /*<! EBI_nRD         PD1      MFP Mask */
#define EBI_nWR_PD6_Msk          SYS_GPD_MFPL_PD6MFP_Msk              /*<! EBI_nWR         PD6      MFP Mask */
#define EBI_nWR_PD2_Msk          SYS_GPD_MFPL_PD2MFP_Msk              /*<! EBI_nWR         PD2      MFP Mask */
#define EBI_nWRH_PB1_Msk         SYS_GPB_MFPL_PB1MFP_Msk              /*<! EBI_nWRH        PB1      MFP Mask */
#define EBI_nWRL_PB0_Msk         SYS_GPB_MFPL_PB0MFP_Msk              /*<! EBI_nWRL        PB0      MFP Mask */
#define I2C0_SCL_PE4_Msk         SYS_GPE_MFPL_PE4MFP_Msk              /*<! I2C0_SCL        PE4      MFP Mask */
#define I2C0_SCL_PA3_Msk         SYS_GPA_MFPL_PA3MFP_Msk              /*<! I2C0_SCL        PA3      MFP Mask */
#define I2C0_SCL_PE12_Msk        SYS_GPE_MFPH_PE12MFP_Msk             /*<! I2C0_SCL        PE12     MFP Mask */
#define I2C0_SCL_PD5_Msk         SYS_GPD_MFPL_PD5MFP_Msk              /*<! I2C0_SCL        PD5      MFP Mask */
#define I2C0_SCL_PE6_Msk         SYS_GPE_MFPL_PE6MFP_Msk              /*<! I2C0_SCL        PE6      MFP Mask */
#define I2C0_SDA_PA2_Msk         SYS_GPA_MFPL_PA2MFP_Msk              /*<! I2C0_SDA        PA2      MFP Mask */
#define I2C0_SDA_PD4_Msk         SYS_GPD_MFPL_PD4MFP_Msk              /*<! I2C0_SDA        PD4      MFP Mask */
#define I2C0_SDA_PE7_Msk         SYS_GPE_MFPL_PE7MFP_Msk              /*<! I2C0_SDA        PE7      MFP Mask */
#define I2C0_SDA_PE13_Msk        SYS_GPE_MFPH_PE13MFP_Msk             /*<! I2C0_SDA        PE13     MFP Mask */
#define I2C0_SDA_PE5_Msk         SYS_GPE_MFPL_PE5MFP_Msk              /*<! I2C0_SDA        PE5      MFP Mask */
#define I2C1_SCL_PC4_Msk         SYS_GPC_MFPL_PC4MFP_Msk              /*<! I2C1_SCL        PC4      MFP Mask */
#define I2C1_SCL_PE4_Msk         SYS_GPE_MFPL_PE4MFP_Msk              /*<! I2C1_SCL        PE4      MFP Mask */
#define I2C1_SCL_PC9_Msk         SYS_GPC_MFPH_PC9MFP_Msk              /*<! I2C1_SCL        PC9      MFP Mask */
#define I2C1_SCL_PE8_Msk         SYS_GPE_MFPH_PE8MFP_Msk              /*<! I2C1_SCL        PE8      MFP Mask */
#define I2C1_SCL_PA8_Msk         SYS_GPA_MFPH_PA8MFP_Msk              /*<! I2C1_SCL        PA8      MFP Mask */
#define I2C1_SCL_PF3_Msk         SYS_GPF_MFPL_PF3MFP_Msk              /*<! I2C1_SCL        PF3      MFP Mask */
#define I2C1_SDA_PC5_Msk         SYS_GPC_MFPL_PC5MFP_Msk              /*<! I2C1_SDA        PC5      MFP Mask */
#define I2C1_SDA_PE0_Msk         SYS_GPE_MFPL_PE0MFP_Msk              /*<! I2C1_SDA        PE0      MFP Mask */
#define I2C1_SDA_PC10_Msk        SYS_GPC_MFPH_PC10MFP_Msk             /*<! I2C1_SDA        PC10     MFP Mask */
#define I2C1_SDA_PA9_Msk         SYS_GPA_MFPH_PA9MFP_Msk              /*<! I2C1_SDA        PA9      MFP Mask */
#define I2C1_SDA_PE9_Msk         SYS_GPE_MFPH_PE9MFP_Msk              /*<! I2C1_SDA        PE9      MFP Mask */
#define I2C1_SDA_PE5_Msk         SYS_GPE_MFPL_PE5MFP_Msk              /*<! I2C1_SDA        PE5      MFP Mask */
#define I2C1_SDA_PF4_Msk         SYS_GPF_MFPL_PF4MFP_Msk              /*<! I2C1_SDA        PF4      MFP Mask */
#define ICE_CLK_PE6_Msk          SYS_GPE_MFPL_PE6MFP_Msk              /*<! ICE_CLK         PE6      MFP Mask */
#define ICE_DAT_PE7_Msk          SYS_GPE_MFPL_PE7MFP_Msk              /*<! ICE_DAT         PE7      MFP Mask */
#define INT0_PE4_Msk             SYS_GPE_MFPL_PE4MFP_Msk              /*<! INT0            PE4      MFP Mask */
#define INT0_PD2_Msk             SYS_GPD_MFPL_PD2MFP_Msk              /*<! INT0            PD2      MFP Mask */
#define INT0_PA0_Msk             SYS_GPA_MFPL_PA0MFP_Msk              /*<! INT0            PA0      MFP Mask */
#define INT1_PE5_Msk             SYS_GPE_MFPL_PE5MFP_Msk              /*<! INT1            PE5      MFP Mask */
#define INT1_PD3_Msk             SYS_GPD_MFPL_PD3MFP_Msk              /*<! INT1            PD3      MFP Mask */
#define INT1_PB0_Msk             SYS_GPB_MFPL_PB0MFP_Msk              /*<! INT1            PB0      MFP Mask */
#define INT2_PC0_Msk             SYS_GPC_MFPL_PC0MFP_Msk              /*<! INT2            PC0      MFP Mask */
#define INT3_PD0_Msk             SYS_GPD_MFPL_PD0MFP_Msk              /*<! INT3            PD0      MFP Mask */
#define INT4_PE0_Msk             SYS_GPE_MFPL_PE0MFP_Msk              /*<! INT4            PE0      MFP Mask */
#define INT5_PF0_Msk             SYS_GPF_MFPL_PF0MFP_Msk              /*<! INT5            PF0      MFP Mask */
#define PWM0_BRAKE0_PD2_Msk      SYS_GPD_MFPL_PD2MFP_Msk              /*<! PWM0_BRAKE0     PD2      MFP Mask */
#define PWM0_BRAKE0_PD4_Msk      SYS_GPD_MFPL_PD4MFP_Msk              /*<! PWM0_BRAKE0     PD4      MFP Mask */
#define PWM0_BRAKE0_PA8_Msk      SYS_GPA_MFPH_PA8MFP_Msk              /*<! PWM0_BRAKE0     PA8      MFP Mask */
#define PWM0_BRAKE1_PD5_Msk      SYS_GPD_MFPL_PD5MFP_Msk              /*<! PWM0_BRAKE1     PD5      MFP Mask */
#define PWM0_BRAKE1_PD3_Msk      SYS_GPD_MFPL_PD3MFP_Msk              /*<! PWM0_BRAKE1     PD3      MFP Mask */
#define PWM0_CH0_PC0_Msk         SYS_GPC_MFPL_PC0MFP_Msk              /*<! PWM0_CH0        PC0      MFP Mask */
#define PWM0_CH0_PE0_Msk         SYS_GPE_MFPL_PE0MFP_Msk              /*<! PWM0_CH0        PE0      MFP Mask */
#define PWM0_CH1_PC1_Msk         SYS_GPC_MFPL_PC1MFP_Msk              /*<! PWM0_CH1        PC1      MFP Mask */
#define PWM0_CH1_PE1_Msk         SYS_GPE_MFPL_PE1MFP_Msk              /*<! PWM0_CH1        PE1      MFP Mask */
#define PWM0_CH2_PE2_Msk         SYS_GPE_MFPL_PE2MFP_Msk              /*<! PWM0_CH2        PE2      MFP Mask */
#define PWM0_CH2_PC2_Msk         SYS_GPC_MFPL_PC2MFP_Msk              /*<! PWM0_CH2        PC2      MFP Mask */
#define PWM0_CH2_PB8_Msk         SYS_GPB_MFPH_PB8MFP_Msk              /*<! PWM0_CH2        PB8      MFP Mask */
#define PWM0_CH3_PE3_Msk         SYS_GPE_MFPL_PE3MFP_Msk              /*<! PWM0_CH3        PE3      MFP Mask */
#define PWM0_CH3_PC3_Msk         SYS_GPC_MFPL_PC3MFP_Msk              /*<! PWM0_CH3        PC3      MFP Mask */
#define PWM0_CH4_PC4_Msk         SYS_GPC_MFPL_PC4MFP_Msk              /*<! PWM0_CH4        PC4      MFP Mask */
#define PWM0_CH5_PD7_Msk         SYS_GPD_MFPL_PD7MFP_Msk              /*<! PWM0_CH5        PD7      MFP Mask */
#define PWM0_CH5_PC5_Msk         SYS_GPC_MFPL_PC5MFP_Msk              /*<! PWM0_CH5        PC5      MFP Mask */
#define PWM0_CH5_PD6_Msk         SYS_GPD_MFPL_PD6MFP_Msk              /*<! PWM0_CH5        PD6      MFP Mask */
#define PWM0_SYNC_IN_PD7_Msk     SYS_GPD_MFPL_PD7MFP_Msk              /*<! PWM0_SYNC_IN    PD7      MFP Mask */
#define PWM0_SYNC_IN_PD1_Msk     SYS_GPD_MFPL_PD1MFP_Msk              /*<! PWM0_SYNC_IN    PD1      MFP Mask */
#define PWM0_SYNC_OUT_PB1_Msk    SYS_GPB_MFPL_PB1MFP_Msk              /*<! PWM0_SYNC_OUT   PB1      MFP Mask */
#define PWM1_BRAKE0_PE4_Msk      SYS_GPE_MFPL_PE4MFP_Msk              /*<! PWM1_BRAKE0     PE4      MFP Mask */
#define PWM1_BRAKE0_PF1_Msk      SYS_GPF_MFPL_PF1MFP_Msk              /*<! PWM1_BRAKE0     PF1      MFP Mask */
#define PWM1_BRAKE1_PF2_Msk      SYS_GPF_MFPL_PF2MFP_Msk              /*<! PWM1_BRAKE1     PF2      MFP Mask */
#define PWM1_BRAKE1_PA9_Msk      SYS_GPA_MFPH_PA9MFP_Msk              /*<! PWM1_BRAKE1     PA9      MFP Mask */
#define PWM1_BRAKE1_PE5_Msk      SYS_GPE_MFPL_PE5MFP_Msk              /*<! PWM1_BRAKE1     PE5      MFP Mask */
#define PWM1_CH0_PD12_Msk        SYS_GPD_MFPH_PD12MFP_Msk             /*<! PWM1_CH0        PD12     MFP Mask */
#define PWM1_CH0_PC9_Msk         SYS_GPC_MFPH_PC9MFP_Msk              /*<! PWM1_CH0        PC9      MFP Mask */
#define PWM1_CH0_PC6_Msk         SYS_GPC_MFPL_PC6MFP_Msk              /*<! PWM1_CH0        PC6      MFP Mask */
#define PWM1_CH0_PC15_Msk        SYS_GPC_MFPH_PC15MFP_Msk             /*<! PWM1_CH0        PC15     MFP Mask */
#define PWM1_CH1_PC10_Msk        SYS_GPC_MFPH_PC10MFP_Msk             /*<! PWM1_CH1        PC10     MFP Mask */
#define PWM1_CH1_PD13_Msk        SYS_GPD_MFPH_PD13MFP_Msk             /*<! PWM1_CH1        PD13     MFP Mask */
#define PWM1_CH1_PC7_Msk         SYS_GPC_MFPL_PC7MFP_Msk              /*<! PWM1_CH1        PC7      MFP Mask */
#define PWM1_CH1_PB12_Msk        SYS_GPB_MFPH_PB12MFP_Msk             /*<! PWM1_CH1        PB12     MFP Mask */
#define PWM1_CH2_PC11_Msk        SYS_GPC_MFPH_PC11MFP_Msk             /*<! PWM1_CH2        PC11     MFP Mask */
#define PWM1_CH2_PD14_Msk        SYS_GPD_MFPH_PD14MFP_Msk             /*<! PWM1_CH2        PD14     MFP Mask */
#define PWM1_CH2_PA3_Msk         SYS_GPA_MFPL_PA3MFP_Msk              /*<! PWM1_CH2        PA3      MFP Mask */
#define PWM1_CH3_PA2_Msk         SYS_GPA_MFPL_PA2MFP_Msk              /*<! PWM1_CH3        PA2      MFP Mask */
#define PWM1_CH3_PC12_Msk        SYS_GPC_MFPH_PC12MFP_Msk             /*<! PWM1_CH3        PC12     MFP Mask */
#define PWM1_CH3_PD15_Msk        SYS_GPD_MFPH_PD15MFP_Msk             /*<! PWM1_CH3        PD15     MFP Mask */
#define PWM1_CH4_PC13_Msk        SYS_GPC_MFPH_PC13MFP_Msk             /*<! PWM1_CH4        PC13     MFP Mask */
#define PWM1_CH4_PA1_Msk         SYS_GPA_MFPL_PA1MFP_Msk              /*<! PWM1_CH4        PA1      MFP Mask */
#define PWM1_CH5_PC14_Msk        SYS_GPC_MFPH_PC14MFP_Msk             /*<! PWM1_CH5        PC14     MFP Mask */
#define PWM1_CH5_PA0_Msk         SYS_GPA_MFPL_PA0MFP_Msk              /*<! PWM1_CH5        PA0      MFP Mask */
#define SC0_CLK_PA0_Msk          SYS_GPA_MFPL_PA0MFP_Msk              /*<! SC0_CLK         PA0      MFP Mask */
#define SC0_CLK_PE11_Msk         SYS_GPE_MFPH_PE11MFP_Msk             /*<! SC0_CLK         PE11     MFP Mask */
#define SC0_CLK_PC1_Msk          SYS_GPC_MFPL_PC1MFP_Msk              /*<! SC0_CLK         PC1      MFP Mask */
#define SC0_DAT_PA1_Msk          SYS_GPA_MFPL_PA1MFP_Msk              /*<! SC0_DAT         PA1      MFP Mask */
#define SC0_DAT_PC0_Msk          SYS_GPC_MFPL_PC0MFP_Msk              /*<! SC0_DAT         PC0      MFP Mask */
#define SC0_DAT_PE10_Msk         SYS_GPE_MFPH_PE10MFP_Msk             /*<! SC0_DAT         PE10     MFP Mask */
#define SC0_PWR_PE8_Msk          SYS_GPE_MFPH_PE8MFP_Msk              /*<! SC0_PWR         PE8      MFP Mask */
#define SC0_PWR_PA8_Msk          SYS_GPA_MFPH_PA8MFP_Msk              /*<! SC0_PWR         PA8      MFP Mask */
#define SC0_PWR_PA3_Msk          SYS_GPA_MFPL_PA3MFP_Msk              /*<! SC0_PWR         PA3      MFP Mask */
#define SC0_PWR_PE4_Msk          SYS_GPE_MFPL_PE4MFP_Msk              /*<! SC0_PWR         PE4      MFP Mask */
#define SC0_PWR_PC3_Msk          SYS_GPC_MFPL_PC3MFP_Msk              /*<! SC0_PWR         PC3      MFP Mask */
#define SC0_RST_PA2_Msk          SYS_GPA_MFPL_PA2MFP_Msk              /*<! SC0_RST         PA2      MFP Mask */
#define SC0_RST_PB1_Msk          SYS_GPB_MFPL_PB1MFP_Msk              /*<! SC0_RST         PB1      MFP Mask */
#define SC0_RST_PC2_Msk          SYS_GPC_MFPL_PC2MFP_Msk              /*<! SC0_RST         PC2      MFP Mask */
#define SC0_RST_PE5_Msk          SYS_GPE_MFPL_PE5MFP_Msk              /*<! SC0_RST         PE5      MFP Mask */
#define SC0_RST_PE9_Msk          SYS_GPE_MFPH_PE9MFP_Msk              /*<! SC0_RST         PE9      MFP Mask */
#define SC0_RST_PA9_Msk          SYS_GPA_MFPH_PA9MFP_Msk              /*<! SC0_RST         PA9      MFP Mask */
#define SC0_nCD_PB2_Msk          SYS_GPB_MFPL_PB2MFP_Msk              /*<! SC0_nCD         PB2      MFP Mask */
#define SC0_nCD_PE0_Msk          SYS_GPE_MFPL_PE0MFP_Msk              /*<! SC0_nCD         PE0      MFP Mask */
#define SC0_nCD_PE1_Msk          SYS_GPE_MFPL_PE1MFP_Msk              /*<! SC0_nCD         PE1      MFP Mask */
#define SC0_nCD_PC4_Msk          SYS_GPC_MFPL_PC4MFP_Msk              /*<! SC0_nCD         PC4      MFP Mask */
#define SC1_CLK_PD0_Msk          SYS_GPD_MFPL_PD0MFP_Msk              /*<! SC1_CLK         PD0      MFP Mask */
#define SC1_CLK_PA11_Msk         SYS_GPA_MFPH_PA11MFP_Msk             /*<! SC1_CLK         PA11     MFP Mask */
#define SC1_DAT_PA10_Msk         SYS_GPA_MFPH_PA10MFP_Msk             /*<! SC1_DAT         PA10     MFP Mask */
#define SC1_DAT_PB7_Msk          SYS_GPB_MFPL_PB7MFP_Msk              /*<! SC1_DAT         PB7      MFP Mask */
#define SC1_PWR_PA9_Msk          SYS_GPA_MFPH_PA9MFP_Msk              /*<! SC1_PWR         PA9      MFP Mask */
#define SC1_PWR_PB6_Msk          SYS_GPB_MFPL_PB6MFP_Msk              /*<! SC1_PWR         PB6      MFP Mask */
#define SC1_RST_PA8_Msk          SYS_GPA_MFPH_PA8MFP_Msk              /*<! SC1_RST         PA8      MFP Mask */
#define SC1_RST_PB5_Msk          SYS_GPB_MFPL_PB5MFP_Msk              /*<! SC1_RST         PB5      MFP Mask */
#define SC1_nCD_PB4_Msk          SYS_GPB_MFPL_PB4MFP_Msk              /*<! SC1_nCD         PB4      MFP Mask */
#define SC1_nCD_PF5_Msk          SYS_GPF_MFPL_PF5MFP_Msk              /*<! SC1_nCD         PF5      MFP Mask */
#define SPI0_CLK_PC0_Msk         SYS_GPC_MFPL_PC0MFP_Msk              /*<! SPI0_CLK        PC0      MFP Mask */
#define SPI0_CLK_PE0_Msk         SYS_GPE_MFPL_PE0MFP_Msk              /*<! SPI0_CLK        PE0      MFP Mask */
#define SPI0_CLK_PB7_Msk         SYS_GPB_MFPL_PB7MFP_Msk              /*<! SPI0_CLK        PB7      MFP Mask */
#define SPI0_CLK_PE13_Msk        SYS_GPE_MFPH_PE13MFP_Msk             /*<! SPI0_CLK        PE13     MFP Mask */
#define SPI0_CLK_PC12_Msk        SYS_GPC_MFPH_PC12MFP_Msk             /*<! SPI0_CLK        PC12     MFP Mask */
#define SPI0_CLK_PB2_Msk         SYS_GPB_MFPL_PB2MFP_Msk              /*<! SPI0_CLK        PB2      MFP Mask */
#define SPI0_I2SMCLK_PC5_Msk     SYS_GPC_MFPL_PC5MFP_Msk              /*<! SPI0_I2SMCLK    PC5      MFP Mask */
#define SPI0_I2SMCLK_PD7_Msk     SYS_GPD_MFPL_PD7MFP_Msk              /*<! SPI0_I2SMCLK    PD7      MFP Mask */
#define SPI0_I2SMCLK_PC9_Msk     SYS_GPC_MFPH_PC9MFP_Msk              /*<! SPI0_I2SMCLK    PC9      MFP Mask */
#define SPI0_I2SMCLK_PD0_Msk     SYS_GPD_MFPL_PD0MFP_Msk              /*<! SPI0_I2SMCLK    PD0      MFP Mask */
#define SPI0_I2SMCLK_PD3_Msk     SYS_GPD_MFPL_PD3MFP_Msk              /*<! SPI0_I2SMCLK    PD3      MFP Mask */
#define SPI0_MISO_PC4_Msk        SYS_GPC_MFPL_PC4MFP_Msk              /*<! SPI0_MISO       PC4      MFP Mask */
#define SPI0_MISO_PC11_Msk       SYS_GPC_MFPH_PC11MFP_Msk             /*<! SPI0_MISO       PC11     MFP Mask */
#define SPI0_MISO_PB3_Msk        SYS_GPB_MFPL_PB3MFP_Msk              /*<! SPI0_MISO       PB3      MFP Mask */
#define SPI0_MISO_PB6_Msk        SYS_GPB_MFPL_PB6MFP_Msk              /*<! SPI0_MISO       PB6      MFP Mask */
#define SPI0_MISO_PE10_Msk       SYS_GPE_MFPH_PE10MFP_Msk             /*<! SPI0_MISO       PE10     MFP Mask */
#define SPI0_MOSI_PC10_Msk       SYS_GPC_MFPH_PC10MFP_Msk             /*<! SPI0_MOSI       PC10     MFP Mask */
#define SPI0_MOSI_PB5_Msk        SYS_GPB_MFPL_PB5MFP_Msk              /*<! SPI0_MOSI       PB5      MFP Mask */
#define SPI0_MOSI_PE11_Msk       SYS_GPE_MFPH_PE11MFP_Msk             /*<! SPI0_MOSI       PE11     MFP Mask */
#define SPI0_MOSI_PC3_Msk        SYS_GPC_MFPL_PC3MFP_Msk              /*<! SPI0_MOSI       PC3      MFP Mask */
#define SPI0_SS_PE12_Msk         SYS_GPE_MFPH_PE12MFP_Msk             /*<! SPI0_SS         PE12     MFP Mask */
#define SPI0_SS_PC2_Msk          SYS_GPC_MFPL_PC2MFP_Msk              /*<! SPI0_SS         PC2      MFP Mask */
#define SPI0_SS_PC13_Msk         SYS_GPC_MFPH_PC13MFP_Msk             /*<! SPI0_SS         PC13     MFP Mask */
#define SPI0_SS_PB4_Msk          SYS_GPB_MFPL_PB4MFP_Msk              /*<! SPI0_SS         PB4      MFP Mask */
#define SPI1_CLK_PA7_Msk         SYS_GPA_MFPL_PA7MFP_Msk              /*<! SPI1_CLK        PA7      MFP Mask */
#define SPI1_CLK_PD15_Msk        SYS_GPD_MFPH_PD15MFP_Msk             /*<! SPI1_CLK        PD15     MFP Mask */
#define SPI1_CLK_PE10_Msk        SYS_GPE_MFPH_PE10MFP_Msk             /*<! SPI1_CLK        PE10     MFP Mask */
#define SPI1_CLK_PB2_Msk         SYS_GPB_MFPL_PB2MFP_Msk              /*<! SPI1_CLK        PB2      MFP Mask */
#define SPI1_CLK_PE13_Msk        SYS_GPE_MFPH_PE13MFP_Msk             /*<! SPI1_CLK        PE13     MFP Mask */
#define SPI1_CLK_PB7_Msk         SYS_GPB_MFPL_PB7MFP_Msk              /*<! SPI1_CLK        PB7      MFP Mask */
#define SPI1_CLK_PD4_Msk         SYS_GPD_MFPL_PD4MFP_Msk              /*<! SPI1_CLK        PD4      MFP Mask */
#define SPI1_I2SMCLK_PA9_Msk     SYS_GPA_MFPH_PA9MFP_Msk              /*<! SPI1_I2SMCLK    PA9      MFP Mask */
#define SPI1_I2SMCLK_PD0_Msk     SYS_GPD_MFPL_PD0MFP_Msk              /*<! SPI1_I2SMCLK    PD0      MFP Mask */
#define SPI1_I2SMCLK_PA12_Msk    SYS_GPA_MFPH_PA12MFP_Msk             /*<! SPI1_I2SMCLK    PA12     MFP Mask */
#define SPI1_MISO_PB3_Msk        SYS_GPB_MFPL_PB3MFP_Msk              /*<! SPI1_MISO       PB3      MFP Mask */
#define SPI1_MISO_PA6_Msk        SYS_GPA_MFPL_PA6MFP_Msk              /*<! SPI1_MISO       PA6      MFP Mask */
#define SPI1_MISO_PD5_Msk        SYS_GPD_MFPL_PD5MFP_Msk              /*<! SPI1_MISO       PD5      MFP Mask */
#define SPI1_MISO_PD14_Msk       SYS_GPD_MFPH_PD14MFP_Msk             /*<! SPI1_MISO       PD14     MFP Mask */
#define SPI1_MISO_PB6_Msk        SYS_GPB_MFPL_PB6MFP_Msk              /*<! SPI1_MISO       PB6      MFP Mask */
#define SPI1_MISO_PE10_Msk       SYS_GPE_MFPH_PE10MFP_Msk             /*<! SPI1_MISO       PE10     MFP Mask */
#define SPI1_MISO_PE11_Msk       SYS_GPE_MFPH_PE11MFP_Msk             /*<! SPI1_MISO       PE11     MFP Mask */
#define SPI1_MOSI_PE12_Msk       SYS_GPE_MFPH_PE12MFP_Msk             /*<! SPI1_MOSI       PE12     MFP Mask */
#define SPI1_MOSI_PE3_Msk        SYS_GPE_MFPL_PE3MFP_Msk              /*<! SPI1_MOSI       PE3      MFP Mask */
#define SPI1_MOSI_PB5_Msk        SYS_GPB_MFPL_PB5MFP_Msk              /*<! SPI1_MOSI       PB5      MFP Mask */
#define SPI1_MOSI_PA5_Msk        SYS_GPA_MFPL_PA5MFP_Msk              /*<! SPI1_MOSI       PA5      MFP Mask */
#define SPI1_MOSI_PE11_Msk       SYS_GPE_MFPH_PE11MFP_Msk             /*<! SPI1_MOSI       PE11     MFP Mask */
#define SPI1_MOSI_PD13_Msk       SYS_GPD_MFPH_PD13MFP_Msk             /*<! SPI1_MOSI       PD13     MFP Mask */
#define SPI1_SS_PB4_Msk          SYS_GPB_MFPL_PB4MFP_Msk              /*<! SPI1_SS         PB4      MFP Mask */
#define SPI1_SS_PE12_Msk         SYS_GPE_MFPH_PE12MFP_Msk             /*<! SPI1_SS         PE12     MFP Mask */
#define SPI1_SS_PD6_Msk          SYS_GPD_MFPL_PD6MFP_Msk              /*<! SPI1_SS         PD6      MFP Mask */
#define SPI1_SS_PA4_Msk          SYS_GPA_MFPL_PA4MFP_Msk              /*<! SPI1_SS         PA4      MFP Mask */
#define SPI1_SS_PE13_Msk         SYS_GPE_MFPH_PE13MFP_Msk             /*<! SPI1_SS         PE13     MFP Mask */
#define SPI1_SS_PD12_Msk         SYS_GPD_MFPH_PD12MFP_Msk             /*<! SPI1_SS         PD12     MFP Mask */
#define TM0_PD4_Msk              SYS_GPD_MFPL_PD4MFP_Msk              /*<! TM0             PD4      MFP Mask */
#define TM0_PD1_Msk              SYS_GPD_MFPL_PD1MFP_Msk              /*<! TM0             PD1      MFP Mask */
#define TM0_PE8_Msk              SYS_GPE_MFPH_PE8MFP_Msk              /*<! TM0             PE8      MFP Mask */
#define TM0_EXT_PD2_Msk          SYS_GPD_MFPL_PD2MFP_Msk              /*<! TM0_EXT         PD2      MFP Mask */
#define TM0_EXT_PB3_Msk          SYS_GPB_MFPL_PB3MFP_Msk              /*<! TM0_EXT         PB3      MFP Mask */
#define TM0_EXT_PE10_Msk         SYS_GPE_MFPH_PE10MFP_Msk             /*<! TM0_EXT         PE10     MFP Mask */
#define TM0_EXT_PA7_Msk          SYS_GPA_MFPL_PA7MFP_Msk              /*<! TM0_EXT         PA7      MFP Mask */
#define TM1_PA8_Msk              SYS_GPA_MFPH_PA8MFP_Msk              /*<! TM1             PA8      MFP Mask */
#define TM1_PD7_Msk              SYS_GPD_MFPL_PD7MFP_Msk              /*<! TM1             PD7      MFP Mask */
#define TM1_PE9_Msk              SYS_GPE_MFPH_PE9MFP_Msk              /*<! TM1             PE9      MFP Mask */
#define TM1_PD5_Msk              SYS_GPD_MFPL_PD5MFP_Msk              /*<! TM1             PD5      MFP Mask */
#define TM1_EXT_PD3_Msk          SYS_GPD_MFPL_PD3MFP_Msk              /*<! TM1_EXT         PD3      MFP Mask */
#define TM1_EXT_PB4_Msk          SYS_GPB_MFPL_PB4MFP_Msk              /*<! TM1_EXT         PB4      MFP Mask */
#define TM1_EXT_PA6_Msk          SYS_GPA_MFPL_PA6MFP_Msk              /*<! TM1_EXT         PA6      MFP Mask */
#define TM1_EXT_PE11_Msk         SYS_GPE_MFPH_PE11MFP_Msk             /*<! TM1_EXT         PE11     MFP Mask */
#define TM1_EXT_PB0_Msk          SYS_GPB_MFPL_PB0MFP_Msk              /*<! TM1_EXT         PB0      MFP Mask */
#define TM2_PA9_Msk              SYS_GPA_MFPH_PA9MFP_Msk              /*<! TM2             PA9      MFP Mask */
#define TM2_PB0_Msk              SYS_GPB_MFPL_PB0MFP_Msk              /*<! TM2             PB0      MFP Mask */
#define TM2_PA14_Msk             SYS_GPA_MFPH_PA14MFP_Msk             /*<! TM2             PA14     MFP Mask */
#define TM2_PD10_Msk             SYS_GPD_MFPH_PD10MFP_Msk             /*<! TM2             PD10     MFP Mask */
#define TM2_PD8_Msk              SYS_GPD_MFPH_PD8MFP_Msk              /*<! TM2             PD8      MFP Mask */
#define TM2_PD3_Msk              SYS_GPD_MFPL_PD3MFP_Msk              /*<! TM2             PD3      MFP Mask */
#define TM2_EXT_PE12_Msk         SYS_GPE_MFPH_PE12MFP_Msk             /*<! TM2_EXT         PE12     MFP Mask */
#define TM2_EXT_PB2_Msk          SYS_GPB_MFPL_PB2MFP_Msk              /*<! TM2_EXT         PB2      MFP Mask */
#define TM2_EXT_PE0_Msk          SYS_GPE_MFPL_PE0MFP_Msk              /*<! TM2_EXT         PE0      MFP Mask */
#define TM2_EXT_PA5_Msk          SYS_GPA_MFPL_PA5MFP_Msk              /*<! TM2_EXT         PA5      MFP Mask */
#define TM3_PD9_Msk              SYS_GPD_MFPH_PD9MFP_Msk              /*<! TM3             PD9      MFP Mask */
#define TM3_PB1_Msk              SYS_GPB_MFPL_PB1MFP_Msk              /*<! TM3             PB1      MFP Mask */
#define TM3_PA15_Msk             SYS_GPA_MFPH_PA15MFP_Msk             /*<! TM3             PA15     MFP Mask */
#define TM3_PD11_Msk             SYS_GPD_MFPH_PD11MFP_Msk             /*<! TM3             PD11     MFP Mask */
#define TM3_EXT_PE1_Msk          SYS_GPE_MFPL_PE1MFP_Msk              /*<! TM3_EXT         PE1      MFP Mask */
#define TM3_EXT_PA4_Msk          SYS_GPA_MFPL_PA4MFP_Msk              /*<! TM3_EXT         PA4      MFP Mask */
#define TM3_EXT_PF5_Msk          SYS_GPF_MFPL_PF5MFP_Msk              /*<! TM3_EXT         PF5      MFP Mask */
#define TM3_EXT_PE13_Msk         SYS_GPE_MFPH_PE13MFP_Msk             /*<! TM3_EXT         PE13     MFP Mask */
#define TM_BRAKE0_PB2_Msk        SYS_GPB_MFPL_PB2MFP_Msk              /*<! TM_BRAKE0       PB2      MFP Mask */
#define TM_BRAKE0_PA8_Msk        SYS_GPA_MFPH_PA8MFP_Msk              /*<! TM_BRAKE0       PA8      MFP Mask */
#define TM_BRAKE0_PF5_Msk        SYS_GPF_MFPL_PF5MFP_Msk              /*<! TM_BRAKE0       PF5      MFP Mask */
#define TM_BRAKE1_PA9_Msk        SYS_GPA_MFPH_PA9MFP_Msk              /*<! TM_BRAKE1       PA9      MFP Mask */
#define TM_BRAKE1_PA7_Msk        SYS_GPA_MFPL_PA7MFP_Msk              /*<! TM_BRAKE1       PA7      MFP Mask */
#define TM_BRAKE1_PB3_Msk        SYS_GPB_MFPL_PB3MFP_Msk              /*<! TM_BRAKE1       PB3      MFP Mask */
#define TM_BRAKE2_PB8_Msk        SYS_GPB_MFPH_PB8MFP_Msk              /*<! TM_BRAKE2       PB8      MFP Mask */
#define TM_BRAKE2_PA12_Msk       SYS_GPA_MFPH_PA12MFP_Msk             /*<! TM_BRAKE2       PA12     MFP Mask */
#define TM_BRAKE2_PA6_Msk        SYS_GPA_MFPL_PA6MFP_Msk              /*<! TM_BRAKE2       PA6      MFP Mask */
#define TM_BRAKE3_PA5_Msk        SYS_GPA_MFPL_PA5MFP_Msk              /*<! TM_BRAKE3       PA5      MFP Mask */
#define TM_BRAKE3_PA13_Msk       SYS_GPA_MFPH_PA13MFP_Msk             /*<! TM_BRAKE3       PA13     MFP Mask */
#define TM_BRAKE3_PE2_Msk        SYS_GPE_MFPL_PE2MFP_Msk              /*<! TM_BRAKE3       PE2      MFP Mask */
#define UART0_RXD_PA3_Msk        SYS_GPA_MFPL_PA3MFP_Msk              /*<! UART0_RXD       PA3      MFP Mask */
#define UART0_RXD_PE6_Msk        SYS_GPE_MFPL_PE6MFP_Msk              /*<! UART0_RXD       PE6      MFP Mask */
#define UART0_RXD_PD9_Msk        SYS_GPD_MFPH_PD9MFP_Msk              /*<! UART0_RXD       PD9      MFP Mask */
#define UART0_RXD_PD0_Msk        SYS_GPD_MFPL_PD0MFP_Msk              /*<! UART0_RXD       PD0      MFP Mask */
#define UART0_RXD_PD13_Msk       SYS_GPD_MFPH_PD13MFP_Msk             /*<! UART0_RXD       PD13     MFP Mask */
#define UART0_RXD_PD6_Msk        SYS_GPD_MFPL_PD6MFP_Msk              /*<! UART0_RXD       PD6      MFP Mask */
#define UART0_TXD_PD1_Msk        SYS_GPD_MFPL_PD1MFP_Msk              /*<! UART0_TXD       PD1      MFP Mask */
#define UART0_TXD_PE7_Msk        SYS_GPE_MFPL_PE7MFP_Msk              /*<! UART0_TXD       PE7      MFP Mask */
#define UART0_TXD_PD12_Msk       SYS_GPD_MFPH_PD12MFP_Msk             /*<! UART0_TXD       PD12     MFP Mask */
#define UART0_TXD_PA2_Msk        SYS_GPA_MFPL_PA2MFP_Msk              /*<! UART0_TXD       PA2      MFP Mask */
#define UART0_nCTS_PD8_Msk       SYS_GPD_MFPH_PD8MFP_Msk              /*<! UART0_nCTS      PD8      MFP Mask */
#define UART0_nCTS_PD14_Msk      SYS_GPD_MFPH_PD14MFP_Msk             /*<! UART0_nCTS      PD14     MFP Mask */
#define UART0_nCTS_PA2_Msk       SYS_GPA_MFPL_PA2MFP_Msk              /*<! UART0_nCTS      PA2      MFP Mask */
#define UART0_nRTS_PC8_Msk       SYS_GPC_MFPH_PC8MFP_Msk              /*<! UART0_nRTS      PC8      MFP Mask */
#define UART0_nRTS_PD15_Msk      SYS_GPD_MFPH_PD15MFP_Msk             /*<! UART0_nRTS      PD15     MFP Mask */
#define UART0_nRTS_PA3_Msk       SYS_GPA_MFPL_PA3MFP_Msk              /*<! UART0_nRTS      PA3      MFP Mask */
#define UART1_RXD_PA1_Msk        SYS_GPA_MFPL_PA1MFP_Msk              /*<! UART1_RXD       PA1      MFP Mask */
#define UART1_RXD_PE9_Msk        SYS_GPE_MFPH_PE9MFP_Msk              /*<! UART1_RXD       PE9      MFP Mask */
#define UART1_RXD_PA9_Msk        SYS_GPA_MFPH_PA9MFP_Msk              /*<! UART1_RXD       PA9      MFP Mask */
#define UART1_RXD_PB2_Msk        SYS_GPB_MFPL_PB2MFP_Msk              /*<! UART1_RXD       PB2      MFP Mask */
#define UART1_RXD_PA12_Msk       SYS_GPA_MFPH_PA12MFP_Msk             /*<! UART1_RXD       PA12     MFP Mask */
#define UART1_RXD_PE13_Msk       SYS_GPE_MFPH_PE13MFP_Msk             /*<! UART1_RXD       PE13     MFP Mask */
#define UART1_TXD_PA13_Msk       SYS_GPA_MFPH_PA13MFP_Msk             /*<! UART1_TXD       PA13     MFP Mask */
#define UART1_TXD_PB3_Msk        SYS_GPB_MFPL_PB3MFP_Msk              /*<! UART1_TXD       PB3      MFP Mask */
#define UART1_TXD_PE8_Msk        SYS_GPE_MFPH_PE8MFP_Msk              /*<! UART1_TXD       PE8      MFP Mask */
#define UART1_TXD_PA0_Msk        SYS_GPA_MFPL_PA0MFP_Msk              /*<! UART1_TXD       PA0      MFP Mask */
#define UART1_TXD_PE12_Msk       SYS_GPE_MFPH_PE12MFP_Msk             /*<! UART1_TXD       PE12     MFP Mask */
#define UART1_TXD_PA8_Msk        SYS_GPA_MFPH_PA8MFP_Msk              /*<! UART1_TXD       PA8      MFP Mask */
#define UART1_nCTS_PB4_Msk       SYS_GPB_MFPL_PB4MFP_Msk              /*<! UART1_nCTS      PB4      MFP Mask */
#define UART1_nCTS_PA10_Msk      SYS_GPA_MFPH_PA10MFP_Msk             /*<! UART1_nCTS      PA10     MFP Mask */
#define UART1_nCTS_PA0_Msk       SYS_GPA_MFPL_PA0MFP_Msk              /*<! UART1_nCTS      PA0      MFP Mask */
#define UART1_nCTS_PE10_Msk      SYS_GPE_MFPH_PE10MFP_Msk             /*<! UART1_nCTS      PE10     MFP Mask */
#define UART1_nRTS_PA11_Msk      SYS_GPA_MFPH_PA11MFP_Msk             /*<! UART1_nRTS      PA11     MFP Mask */
#define UART1_nRTS_PB8_Msk       SYS_GPB_MFPH_PB8MFP_Msk              /*<! UART1_nRTS      PB8      MFP Mask */
#define UART1_nRTS_PA1_Msk       SYS_GPA_MFPL_PA1MFP_Msk              /*<! UART1_nRTS      PA1      MFP Mask */
#define UART1_nRTS_PE11_Msk      SYS_GPE_MFPH_PE11MFP_Msk             /*<! UART1_nRTS      PE11     MFP Mask */
#define UART1_nRTS_PE2_Msk       SYS_GPE_MFPL_PE2MFP_Msk              /*<! UART1_nRTS      PE2      MFP Mask */
#define UART2_RXD_PB0_Msk        SYS_GPB_MFPL_PB0MFP_Msk              /*<! UART2_RXD       PB0      MFP Mask */
#define UART2_RXD_PC3_Msk        SYS_GPC_MFPL_PC3MFP_Msk              /*<! UART2_RXD       PC3      MFP Mask */
#define UART2_RXD_PE3_Msk        SYS_GPE_MFPL_PE3MFP_Msk              /*<! UART2_RXD       PE3      MFP Mask */
#define UART2_RXD_PB5_Msk        SYS_GPB_MFPL_PB5MFP_Msk              /*<! UART2_RXD       PB5      MFP Mask */
#define UART2_RXD_PA12_Msk       SYS_GPA_MFPH_PA12MFP_Msk             /*<! UART2_RXD       PA12     MFP Mask */
#define UART2_RXD_PB4_Msk        SYS_GPB_MFPL_PB4MFP_Msk              /*<! UART2_RXD       PB4      MFP Mask */
#define UART2_TXD_PD6_Msk        SYS_GPD_MFPL_PD6MFP_Msk              /*<! UART2_TXD       PD6      MFP Mask */
#define UART2_TXD_PB1_Msk        SYS_GPB_MFPL_PB1MFP_Msk              /*<! UART2_TXD       PB1      MFP Mask */
#define UART2_TXD_PA13_Msk       SYS_GPA_MFPH_PA13MFP_Msk             /*<! UART2_TXD       PA13     MFP Mask */
#define UART2_TXD_PC2_Msk        SYS_GPC_MFPL_PC2MFP_Msk              /*<! UART2_TXD       PC2      MFP Mask */
#define UART2_nCTS_PC0_Msk       SYS_GPC_MFPL_PC0MFP_Msk              /*<! UART2_nCTS      PC0      MFP Mask */
#define UART2_nCTS_PD5_Msk       SYS_GPD_MFPL_PD5MFP_Msk              /*<! UART2_nCTS      PD5      MFP Mask */
#define UART2_nCTS_PA14_Msk      SYS_GPA_MFPH_PA14MFP_Msk             /*<! UART2_nCTS      PA14     MFP Mask */
#define UART2_nRTS_PA15_Msk      SYS_GPA_MFPH_PA15MFP_Msk             /*<! UART2_nRTS      PA15     MFP Mask */
#define UART2_nRTS_PD4_Msk       SYS_GPD_MFPL_PD4MFP_Msk              /*<! UART2_nRTS      PD4      MFP Mask */
#define UART2_nRTS_PC1_Msk       SYS_GPC_MFPL_PC1MFP_Msk              /*<! UART2_nRTS      PC1      MFP Mask */
#define USCI0_CLK_PB9_Msk        SYS_GPB_MFPH_PB9MFP_Msk              /*<! USCI0_CLK       PB9      MFP Mask */
#define USCI0_CLK_PC4_Msk        SYS_GPC_MFPL_PC4MFP_Msk              /*<! USCI0_CLK       PC4      MFP Mask */
#define USCI0_CLK_PE5_Msk        SYS_GPE_MFPL_PE5MFP_Msk              /*<! USCI0_CLK       PE5      MFP Mask */
#define USCI0_CTL0_PC3_Msk       SYS_GPC_MFPL_PC3MFP_Msk              /*<! USCI0_CTL0      PC3      MFP Mask */
#define USCI0_CTL0_PB8_Msk       SYS_GPB_MFPH_PB8MFP_Msk              /*<! USCI0_CTL0      PB8      MFP Mask */
#define USCI0_CTL0_PE4_Msk       SYS_GPE_MFPL_PE4MFP_Msk              /*<! USCI0_CTL0      PE4      MFP Mask */
#define USCI0_CTL0_PE2_Msk       SYS_GPE_MFPL_PE2MFP_Msk              /*<! USCI0_CTL0      PE2      MFP Mask */
#define USCI0_CTL1_PC7_Msk       SYS_GPC_MFPL_PC7MFP_Msk              /*<! USCI0_CTL1      PC7      MFP Mask */
#define USCI0_CTL1_PB4_Msk       SYS_GPB_MFPL_PB4MFP_Msk              /*<! USCI0_CTL1      PB4      MFP Mask */
#define USCI0_CTL1_PC2_Msk       SYS_GPC_MFPL_PC2MFP_Msk              /*<! USCI0_CTL1      PC2      MFP Mask */
#define USCI0_DAT0_PC5_Msk       SYS_GPC_MFPL_PC5MFP_Msk              /*<! USCI0_DAT0      PC5      MFP Mask */
#define USCI0_DAT0_PC0_Msk       SYS_GPC_MFPL_PC0MFP_Msk              /*<! USCI0_DAT0      PC0      MFP Mask */
#define USCI0_DAT0_PB2_Msk       SYS_GPB_MFPL_PB2MFP_Msk              /*<! USCI0_DAT0      PB2      MFP Mask */
#define USCI0_DAT1_PC1_Msk       SYS_GPC_MFPL_PC1MFP_Msk              /*<! USCI0_DAT1      PC1      MFP Mask */
#define USCI0_DAT1_PB3_Msk       SYS_GPB_MFPL_PB3MFP_Msk              /*<! USCI0_DAT1      PB3      MFP Mask */
#define USCI0_DAT1_PC6_Msk       SYS_GPC_MFPL_PC6MFP_Msk              /*<! USCI0_DAT1      PC6      MFP Mask */
#define USCI1_CLK_PD15_Msk       SYS_GPD_MFPH_PD15MFP_Msk             /*<! USCI1_CLK       PD15     MFP Mask */
#define USCI1_CLK_PA3_Msk        SYS_GPA_MFPL_PA3MFP_Msk              /*<! USCI1_CLK       PA3      MFP Mask */
#define USCI1_CLK_PA15_Msk       SYS_GPA_MFPH_PA15MFP_Msk             /*<! USCI1_CLK       PA15     MFP Mask */
#define USCI1_CTL0_PA2_Msk       SYS_GPA_MFPL_PA2MFP_Msk              /*<! USCI1_CTL0      PA2      MFP Mask */
#define USCI1_CTL0_PA0_Msk       SYS_GPA_MFPL_PA0MFP_Msk              /*<! USCI1_CTL0      PA0      MFP Mask */
#define USCI1_CTL0_PD12_Msk      SYS_GPD_MFPH_PD12MFP_Msk             /*<! USCI1_CTL0      PD12     MFP Mask */
#define USCI1_CTL1_PA1_Msk       SYS_GPA_MFPL_PA1MFP_Msk              /*<! USCI1_CTL1      PA1      MFP Mask */
#define USCI1_CTL1_PA14_Msk      SYS_GPA_MFPH_PA14MFP_Msk             /*<! USCI1_CTL1      PA14     MFP Mask */
#define USCI1_CTL1_PD7_Msk       SYS_GPD_MFPL_PD7MFP_Msk              /*<! USCI1_CTL1      PD7      MFP Mask */
#define USCI1_DAT0_PD14_Msk      SYS_GPD_MFPH_PD14MFP_Msk             /*<! USCI1_DAT0      PD14     MFP Mask */
#define USCI1_DAT0_PB0_Msk       SYS_GPB_MFPL_PB0MFP_Msk              /*<! USCI1_DAT0      PB0      MFP Mask */
#define USCI1_DAT1_PB1_Msk       SYS_GPB_MFPL_PB1MFP_Msk              /*<! USCI1_DAT1      PB1      MFP Mask */
#define USCI1_DAT1_PD13_Msk      SYS_GPD_MFPH_PD13MFP_Msk             /*<! USCI1_DAT1      PD13     MFP Mask */
#define USCI2_CLK_PC11_Msk       SYS_GPC_MFPH_PC11MFP_Msk             /*<! USCI2_CLK       PC11     MFP Mask */
#define USCI2_CLK_PD1_Msk        SYS_GPD_MFPL_PD1MFP_Msk              /*<! USCI2_CLK       PD1      MFP Mask */
#define USCI2_CLK_PF2_Msk        SYS_GPF_MFPL_PF2MFP_Msk              /*<! USCI2_CLK       PF2      MFP Mask */
#define USCI2_CTL0_PD0_Msk       SYS_GPD_MFPL_PD0MFP_Msk              /*<! USCI2_CTL0      PD0      MFP Mask */
#define USCI2_CTL0_PD9_Msk       SYS_GPD_MFPH_PD9MFP_Msk              /*<! USCI2_CTL0      PD9      MFP Mask */
#define USCI2_CTL0_PC12_Msk      SYS_GPC_MFPH_PC12MFP_Msk             /*<! USCI2_CTL0      PC12     MFP Mask */
#define USCI2_CTL0_PF1_Msk       SYS_GPF_MFPL_PF1MFP_Msk              /*<! USCI2_CTL0      PF1      MFP Mask */
#define USCI2_CTL1_PC9_Msk       SYS_GPC_MFPH_PC9MFP_Msk              /*<! USCI2_CTL1      PC9      MFP Mask */
#define USCI2_CTL1_PF0_Msk       SYS_GPF_MFPL_PF0MFP_Msk              /*<! USCI2_CTL1      PF0      MFP Mask */
#define USCI2_CTL1_PD8_Msk       SYS_GPD_MFPH_PD8MFP_Msk              /*<! USCI2_CTL1      PD8      MFP Mask */
#define USCI2_CTL1_PB7_Msk       SYS_GPB_MFPL_PB7MFP_Msk              /*<! USCI2_CTL1      PB7      MFP Mask */
#define USCI2_DAT0_PD2_Msk       SYS_GPD_MFPL_PD2MFP_Msk              /*<! USCI2_DAT0      PD2      MFP Mask */
#define USCI2_DAT0_PD10_Msk      SYS_GPD_MFPH_PD10MFP_Msk             /*<! USCI2_DAT0      PD10     MFP Mask */
#define USCI2_DAT0_PC13_Msk      SYS_GPC_MFPH_PC13MFP_Msk             /*<! USCI2_DAT0      PC13     MFP Mask */
#define USCI2_DAT1_PD3_Msk       SYS_GPD_MFPL_PD3MFP_Msk              /*<! USCI2_DAT1      PD3      MFP Mask */
#define USCI2_DAT1_PC10_Msk      SYS_GPC_MFPH_PC10MFP_Msk             /*<! USCI2_DAT1      PC10     MFP Mask */
#define USCI2_DAT1_PD11_Msk      SYS_GPD_MFPH_PD11MFP_Msk             /*<! USCI2_DAT1      PD11     MFP Mask */
#define VDET_P0_PB0_Msk          SYS_GPB_MFPL_PB0MFP_Msk              /*<! VDET_P0         PB0      MFP Mask */
#define VDET_P1_PB1_Msk          SYS_GPB_MFPL_PB1MFP_Msk              /*<! VDET_P1         PB1      MFP Mask */
#define X32_IN_PF1_Msk           SYS_GPF_MFPL_PF1MFP_Msk              /*<! X32_IN          PF1      MFP Mask */
#define X32_OUT_PF0_Msk          SYS_GPF_MFPL_PF0MFP_Msk              /*<! X32_OUT         PF0      MFP Mask */
#define XT1_IN_PF4_Msk           SYS_GPF_MFPL_PF4MFP_Msk              /*<! XT1_IN          PF4      MFP Mask */
#define XT1_OUT_PF3_Msk          SYS_GPF_MFPL_PF3MFP_Msk              /*<! XT1_OUT         PF3      MFP Mask */


/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */

/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/


/**
  * @brief      Clear Brown-out detector interrupt flag
  * @param      None
  * @return     None
  * @details    This macro clear Brown-out detector interrupt flag.
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCTL |= SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Set Brown-out detector function to normal mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to normal mode.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_CLEAR_BOD_LPM()             (SYS->BODCTL &= ~SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_BOD()               (SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Enable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_BOD()                (SYS->BODCTL |= SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Get Brown-out detector interrupt flag
  * @param      None
  * @retval     0   Brown-out detect interrupt flag is not set.
  * @retval     >=1 Brown-out detect interrupt flag is set.
  * @details    This macro get Brown-out detector interrupt flag.
  */
#define SYS_GET_BOD_INT_FLAG()          (SYS->BODCTL & SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Get Brown-out detector status
  * @param      None
  * @retval     0   System voltage is higher than BOD threshold voltage setting or BOD function is disabled.
  * @retval     >=1 System voltage is lower than BOD threshold voltage setting.
  * @details    This macro get Brown-out detector output status.
  *             If the BOD function is disabled, this function always return 0.
  */
#define SYS_GET_BOD_OUTPUT()            (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk)

/**
  * @brief      Enable Brown-out detector interrupt function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector interrupt function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCTL &= ~SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Enable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detect reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCTL |= SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Set Brown-out detector function low power mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to low power mode.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_SET_BOD_LPM()               (SYS->BODCTL |= SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Set Brown-out detector voltage level
  * @param[in]  u32Level is Brown-out voltage level. Including :
  *             - \ref SYS_BODCTL_BODVL_4_5V
  *             - \ref SYS_BODCTL_BODVL_3_7V
  *             - \ref SYS_BODCTL_BODVL_2_7V
  *             - \ref SYS_BODCTL_BODVL_2_2V
  * @return     None
  * @details    This macro set Brown-out detector voltage level.
  *             The write-protection function should be disabled before using this macro.
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCTL = (SYS->BODCTL & ~SYS_BODCTL_BODVL_Msk) | (u32Level))

/**
  * @brief      Get reset source is from Brown-out detector reset
  * @param      None
  * @retval     0   Previous reset source is not from Brown-out detector reset
  * @retval     >=1 Previous reset source is from Brown-out detector reset
  * @details    This macro get previous reset source is from Brown-out detect reset or not.
  */
#define SYS_IS_BOD_RST()                (SYS->RSTSTS & SYS_RSTSTS_BODRF_Msk)

/**
  * @brief      Get reset source is from CPU reset
  * @param      None
  * @retval     0   Previous reset source is not from CPU reset
  * @retval     >=1 Previous reset source is from CPU reset
  * @details    This macro get previous reset source is from CPU reset.
  */
#define SYS_IS_CPU_RST()                (SYS->RSTSTS & SYS_RSTSTS_CPURF_Msk)

/**
  * @brief      Get reset source is from LVR Reset
  * @param      None
  * @retval     0   Previous reset source is not from Low-Voltage-Reset
  * @retval     >=1 Previous reset source is from Low-Voltage-Reset
  * @details    This macro get previous reset source is from Low-Voltage-Reset.
  */
#define SYS_IS_LVR_RST()                (SYS->RSTSTS & SYS_RSTSTS_LVRF_Msk)

/**
  * @brief      Get reset source is from Power-on Reset
  * @param      None
  * @retval     0   Previous reset source is not from Power-on Reset
  * @retval     >=1 Previous reset source is from Power-on Reset
  * @details    This macro get previous reset source is from Power-on Reset.
  */
#define SYS_IS_POR_RST()                (SYS->RSTSTS & SYS_RSTSTS_PORF_Msk)

/**
  * @brief      Get reset source is from reset pin reset
  * @param      None
  * @retval     0   Previous reset source is not from reset pin reset
  * @retval     >=1 Previous reset source is from reset pin reset
  * @details    This macro get previous reset source is from reset pin reset.
  */
#define SYS_IS_RSTPIN_RST()             (SYS->RSTSTS & SYS_RSTSTS_PINRF_Msk)

/**
  * @brief      Get reset source is from system reset
  * @param      None
  * @retval     0   Previous reset source is not from system reset
  * @retval     >=1 Previous reset source is from system reset
  * @details    This macro get previous reset source is from system reset.
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSTS & SYS_RSTSTS_MCURF_Msk)

/**
  * @brief      Get reset source is from window watch dog reset
  * @param      None
  * @retval     0   Previous reset source is not from window watch dog reset
  * @retval     >=1 Previous reset source is from window watch dog reset
  * @details    This macro get previous reset source is from window watch dog reset.
  */
#define SYS_IS_WDT_RST()                (SYS->RSTSTS & SYS_RSTSTS_WDTRF_Msk)

/**
  * @brief      Disable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_LVR()               (SYS->BODCTL &= ~SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Enable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_LVR()                (SYS->BODCTL |= SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Disable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_POR()               (SYS->PORCTL = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_POR()                (SYS->PORCTL = 0)

/**
  * @brief      Clear reset source flag
  * @param[in]  u32RstSrc is reset source. Including :
  *             - \ref SYS_RSTSTS_PORF_Msk
  *             - \ref SYS_RSTSTS_PINRF_Msk
  *             - \ref SYS_RSTSTS_WDTRF_Msk
  *             - \ref SYS_RSTSTS_LVRF_Msk
  *             - \ref SYS_RSTSTS_BODRF_Msk
  *             - \ref SYS_RSTSTS_MCURF_Msk
  *             - \ref SYS_RSTSTS_CPURF_Msk
  *             - \ref SYS_RSTSTS_CPULKRF_Msk
  * @return     None
  * @details    This macro clear reset source flag.
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) ((SYS->RSTSTS) = (u32RstSrc) )




/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  */
__STATIC_INLINE void SYS_UnlockReg(void)
{
    do
    {
        SYS->REGLCTL = 0x59;
        SYS->REGLCTL = 0x16;
        SYS->REGLCTL = 0x88;
    }
    while(SYS->REGLCTL == 0);
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function is used to enable register write-protection function.
  *             To lock the protected register to forbid write access.
  */
__STATIC_INLINE void SYS_LockReg(void)
{
    SYS->REGLCTL = 0;
}


void SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetBODStatus(void);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_IsRegLocked(void);
uint32_t SYS_ReadPDID(void);
void SYS_ResetChip(void);
void SYS_ResetCPU(void);
void SYS_ResetModule(uint32_t u32ModuleIndex);
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel);
void SYS_DisableBOD(void);


/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */


#ifdef __cplusplus
}
#endif

#endif //__SYS_H__

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
