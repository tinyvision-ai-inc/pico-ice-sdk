/**************************************************************************//**
 * @file     SYS.h
 * @version  V3.00
 * @brief    NUC121 series SYS driver header file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
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

#define GPIO_RST    ((0x4<<24)|SYS_IPRST1_GPIORST_Pos)      /*!< GPIO reset is one of the SYS_ResetModule parameter */
#define TMR0_RST    ((0x4<<24)|SYS_IPRST1_TMR0RST_Pos)      /*!< TMR0 reset is one of the SYS_ResetModule parameter */
#define TMR1_RST    ((0x4<<24)|SYS_IPRST1_TMR1RST_Pos)      /*!< TMR1 reset is one of the SYS_ResetModule parameter */
#define TMR2_RST    ((0x4<<24)|SYS_IPRST1_TMR2RST_Pos)      /*!< TMR2 reset is one of the SYS_ResetModule parameter */
#define TMR3_RST    ((0x4<<24)|SYS_IPRST1_TMR3RST_Pos)      /*!< TMR3 reset is one of the SYS_ResetModule parameter */
#define I2C0_RST    ((0x4<<24)|SYS_IPRST1_I2C0RST_Pos)      /*!< I2C0 reset is one of the SYS_ResetModule parameter */
#define I2C1_RST    ((0x4<<24)|SYS_IPRST1_I2C1RST_Pos)      /*!< I2C1 reset is one of the SYS_ResetModule parameter */
#define SPI0_RST    ((0x4<<24)|SYS_IPRST1_SPI0RST_Pos)      /*!< SPI0 reset is one of the SYS_ResetModule parameter */
#define UART0_RST   ((0x4<<24)|SYS_IPRST1_UART0RST_Pos)     /*!< UART0 reset is one of the SYS_ResetModule parameter */
#define BPWM0_RST   ((0x4<<24)|SYS_IPRST1_BPWM0RST_Pos)     /*!< BPWM0 reset is one of the SYS_ResetModule parameter */
#define BPWM1_RST   ((0x4<<24)|SYS_IPRST1_BPWM1RST_Pos)     /*!< BPWM1 reset is one of the SYS_ResetModule parameter */
#define PWM0_RST    ((0x4<<24)|SYS_IPRST1_PWM0RST_Pos)      /*!< PWM0 reset is one of the SYS_ResetModule parameter */
#define PWM1_RST    ((0x4<<24)|SYS_IPRST1_PWM1RST_Pos)      /*!< PWM1 reset is one of the SYS_ResetModule parameter */
#define USBD_RST    ((0x4<<24)|SYS_IPRST1_USBDRST_Pos)      /*!< USBD reset is one of the SYS_ResetModule parameter */
#define ADC_RST     ((0x4<<24)|SYS_IPRST1_ADCRST_Pos)       /*!< ADC reset is one of the SYS_ResetModule parameter */

#define USCI0_RST   ((0x8<<24)|SYS_IPRST2_USCI0RST_Pos)     /*!< USCI0 reset is one of the SYS_ResetModule parameter */


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
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/

/* How to use below #define?

Example: If user want to set PB.1 as UART0_TXD and PB.0 as UART0_RXD in initial function,
         user can issue following command to achieve it.

         SYS->GPB_MFPL = (SYS->GPB_MFPL & (~SYS_GPB_MFPL_PB1MFP_Msk)) | SYS_GP0_MFPL_PB1MFP_UART0_TXD;
         SYS->GPB_MFPL = (SYS->GPB_MFPL & (~SYS_GPB_MFPL_PB0MFP_Msk)) | SYS_GP0_MFPL_PB0MFP_UART0_RXD;
*/

//PA.10 MFP
#define SYS_GPA_MFPH_PA10MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for GPIO          */
#define SYS_GPA_MFPH_PA10MFP_I2C1_SDA        (0x1UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for I2C1_SDA      */
#define SYS_GPA_MFPH_PA10MFP_BPWM0_CH4       (0x4UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for BPWM0_CH4     */
#define SYS_GPA_MFPH_PA10MFP_PWM0_BRAKE0     (0x5UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for PWM0_BRAKE0   */
#define SYS_GPA_MFPH_PA10MFP_USCI0_DAT1      (0x6UL<<SYS_GPA_MFPH_PA10MFP_Pos)   /*!< GPA_MFPH PA10 setting for USCI0_DAT1    */

//PA.11 MFP
#define SYS_GPA_MFPH_PA11MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for GPIO          */
#define SYS_GPA_MFPH_PA11MFP_I2C1_SCL        (0x1UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for I2C1_SCL      */
#define SYS_GPA_MFPH_PA11MFP_BPWM0_CH5       (0x4UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for BPWM0_CH5     */
#define SYS_GPA_MFPH_PA11MFP_TM0             (0x5UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for TM0           */
#define SYS_GPA_MFPH_PA11MFP_USCI0_CLK       (0x6UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for USCI0_CLK     */
#define SYS_GPA_MFPH_PA11MFP_USCI0_DAT0      (0x7UL<<SYS_GPA_MFPH_PA11MFP_Pos)   /*!< GPA_MFPH PA11 setting for USCI0_DAT0    */

//PA.12 MFP
#define SYS_GPA_MFPH_PA12MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for GPIO          */
#define SYS_GPA_MFPH_PA12MFP_PWM0_CH0        (0x1UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for PWM0_CH0      */
#define SYS_GPA_MFPH_PA12MFP_I2C1_SCL        (0x2UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for I2C1_SCL      */
#define SYS_GPA_MFPH_PA12MFP_UART0_RXD       (0x3UL<<SYS_GPA_MFPH_PA12MFP_Pos)   /*!< GPA_MFPH PA12 setting for UART0_RXD     */

//PA.13 MFP
#define SYS_GPA_MFPH_PA13MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for GPIO          */
#define SYS_GPA_MFPH_PA13MFP_PWM0_CH1        (0x1UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for PWM0_CH1      */
#define SYS_GPA_MFPH_PA13MFP_I2C1_SDA        (0x2UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for I2C1_SDA      */
#define SYS_GPA_MFPH_PA13MFP_UART0_TXD       (0x3UL<<SYS_GPA_MFPH_PA13MFP_Pos)   /*!< GPA_MFPH PA13 setting for UART0_TXD     */

//PA.14 MFP
#define SYS_GPA_MFPH_PA14MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for GPIO          */
#define SYS_GPA_MFPH_PA14MFP_PWM0_CH2        (0x1UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for PWM0_CH2      */
#define SYS_GPA_MFPH_PA14MFP_UART0_nCTS      (0x3UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for UART0_nCTS    */
#define SYS_GPA_MFPH_PA14MFP_PWM0_BRAKE0     (0x4UL<<SYS_GPA_MFPH_PA14MFP_Pos)   /*!< GPA_MFPH PA14 setting for PWM0_BRAKE0   */

//PA.15 MFP
#define SYS_GPA_MFPH_PA15MFP_GPIO            (0x0UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for GPIO          */
#define SYS_GPA_MFPH_PA15MFP_PWM0_CH3        (0x1UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for PWM0_CH3      */
#define SYS_GPA_MFPH_PA15MFP_SPI_I2SMCLK     (0x2UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for SPI_I2SMCLK   */
#define SYS_GPA_MFPH_PA15MFP_CLKO            (0x3UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for CLKO          */
#define SYS_GPA_MFPH_PA15MFP_PWM1_BRAKE1     (0x4UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for PWM1_BRAKE1   */
#define SYS_GPA_MFPH_PA15MFP_UART0_nRTS      (0x5UL<<SYS_GPA_MFPH_PA15MFP_Pos)   /*!< GPA_MFPH PA15 setting for UART0_nRTS    */

//PB.0 MFP
#define SYS_GPB_MFPL_PB0MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for GPIO           */
#define SYS_GPB_MFPL_PB0MFP_UART0_RXD        (0x1UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for UART0_RXD      */
#define SYS_GPB_MFPL_PB0MFP_PWM1_CH0         (0x4UL<<SYS_GPB_MFPL_PB0MFP_Pos)    /*!< GPB_MFPL PB0 setting for PWM1_CH0       */

//PB.1 MFP
#define SYS_GPB_MFPL_PB1MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for GPIO          */
#define SYS_GPB_MFPL_PB1MFP_UART0_TXD        (0x1UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for UART0_TXD     */
#define SYS_GPB_MFPL_PB1MFP_PWM1_CH1         (0x4UL<<SYS_GPB_MFPL_PB1MFP_Pos)    /*!< GPB_MFPL PB1 setting for PWM1_CH1      */

//PB.2 MFP
#define SYS_GPB_MFPL_PB2MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for GPIO          */
#define SYS_GPB_MFPL_PB2MFP_UART0_nRTS       (0x1UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for UART0_nRTS    */
#define SYS_GPB_MFPL_PB2MFP_TM2_EXT          (0x2UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for TM2_EXT       */
#define SYS_GPB_MFPL_PB2MFP_PWM1_CH2         (0x4UL<<SYS_GPB_MFPL_PB2MFP_Pos)    /*!< GPB_MFPL PB2 setting for PWM1_CH2      */

//PB.3 MFP
#define SYS_GPB_MFPL_PB3MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for GPIO          */
#define SYS_GPB_MFPL_PB3MFP_UART0_nCTS       (0x1UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for UART0_nCTS    */
#define SYS_GPB_MFPL_PB3MFP_TM3_EXT          (0x2UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for TM3_EXT       */
#define SYS_GPB_MFPL_PB3MFP_PWM1_CH3         (0x4UL<<SYS_GPB_MFPL_PB3MFP_Pos)    /*!< GPB_MFPL PB3 setting for PWM1_CH3      */

//PB.4 MFP
#define SYS_GPB_MFPL_PB4MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for GPIO          */
#define SYS_GPB_MFPL_PB4MFP_BPWM0_CH3        (0x4UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for BPWM0_CH3     */
#define SYS_GPB_MFPL_PB4MFP_TM2_EXT          (0x5UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for TM2_EXT       */
#define SYS_GPB_MFPL_PB4MFP_USCI0_CTL0       (0x6UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for USCI0_CTL0    */
#define SYS_GPB_MFPL_PB4MFP_USCI0_DAT0       (0x7UL<<SYS_GPB_MFPL_PB4MFP_Pos)    /*!< GPB_MFPL PB4 setting for USCI0_DAT0    */

//PB.5 MFP
#define SYS_GPB_MFPL_PB5MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for GPIO          */
#define SYS_GPB_MFPL_PB5MFP_BPWM0_CH2        (0x4UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for BPWM0_CH2     */
#define SYS_GPB_MFPL_PB5MFP_TM3              (0x5UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for TM3           */
#define SYS_GPB_MFPL_PB5MFP_USCI0_CLK        (0x6UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for USCI0_CLK     */
#define SYS_GPB_MFPL_PB5MFP_USCI0_DAT1       (0x7UL<<SYS_GPB_MFPL_PB5MFP_Pos)    /*!< GPB_MFPL PB5 setting for USCI0_DAT1    */

//PB.6 MFP
#define SYS_GPB_MFPL_PB6MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for GPIO          */
#define SYS_GPB_MFPL_PB6MFP_BPWM0_CH1        (0x4UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for BPWM0_CH1     */
#define SYS_GPB_MFPL_PB6MFP_USCI0_DAT0       (0x6UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for USCI0_DAT0    */
#define SYS_GPB_MFPL_PB6MFP_USCI0_CTL1       (0x7UL<<SYS_GPB_MFPL_PB6MFP_Pos)    /*!< GPB_MFPL PB6 setting for USCI0_CTL1    */

//PB.7 MFP
#define SYS_GPB_MFPL_PB7MFP_GPIO             (0x0UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for GPIO          */
#define SYS_GPB_MFPL_PB7MFP_BPWM0_CH0        (0x4UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for BPWM0_CH0     */
#define SYS_GPB_MFPL_PB7MFP_USCI0_DAT1       (0x6UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for USCI0_DAT1    */
#define SYS_GPB_MFPL_PB7MFP_USCI0_CTL0       (0x7UL<<SYS_GPB_MFPL_PB7MFP_Pos)    /*!< GPB_MFPL PB7 setting for USCI0_CTL0    */

//PB.8 MFP
#define SYS_GPB_MFPH_PB8MFP_GPIO             (0x0UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for GPIO           */
#define SYS_GPB_MFPH_PB8MFP_TM0              (0x1UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for TM0            */
#define SYS_GPB_MFPH_PB8MFP_ADC_CH8          (0x3UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for ADC_CH8        */
#define SYS_GPB_MFPH_PB8MFP_BPWM1_CH1        (0x4UL<<SYS_GPB_MFPH_PB8MFP_Pos)    /*!< GPB_MFPH PB8 setting for BPWM1_CH1      */

//PB.9 MFP
#define SYS_GPB_MFPH_PB9MFP_GPIO             (0x0UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for GPIO           */
#define SYS_GPB_MFPH_PB9MFP_TM1              (0x1UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for TM1            */
#define SYS_GPB_MFPH_PB9MFP_SPI0_I2SMCLK     (0x3UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for SPI0_I2SMCLK   */
#define SYS_GPB_MFPH_PB9MFP_PWM0_CH4         (0x4UL<<SYS_GPB_MFPH_PB9MFP_Pos)    /*!< GPB_MFPH PB9 setting for PWM0_CH4       */

//PB.10 MFP
#define SYS_GPB_MFPH_PB10MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB10MFP_Pos)   /*!< GPB_MFPH PB10 setting for GPIO          */
#define SYS_GPB_MFPH_PB10MFP_TM2             (0x1UL<<SYS_GPB_MFPH_PB10MFP_Pos)   /*!< GPB_MFPH PB10 setting for TM2           */
#define SYS_GPB_MFPH_PB10MFP_SPI0_I2SMCLK    (0x3UL<<SYS_GPB_MFPH_PB10MFP_Pos)   /*!< GPB_MFPH PB10 setting for SPI0_I2SMCLK  */
#define SYS_GPB_MFPH_PB10MFP_PWM0_CH5        (0x4UL<<SYS_GPB_MFPH_PB10MFP_Pos)   /*!< GPB_MFPH PB10 setting for PWM0_CH5      */

//PB.12 MFP
#define SYS_GPB_MFPH_PB12MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB12MFP_Pos)   /*!< GPB_MFPH PB12 setting for GPIO          */
#define SYS_GPB_MFPH_PB12MFP_CLKO            (0x2UL<<SYS_GPB_MFPH_PB12MFP_Pos)   /*!< GPB_MFPH PB12 setting for CLKO          */
#define SYS_GPB_MFPH_PB12MFP_ADC_CH11        (0x3UL<<SYS_GPB_MFPH_PB12MFP_Pos)   /*!< GPB_MFPH PB12 setting for ADC_CH11      */
#define SYS_GPB_MFPH_PB12MFP_USCI0_CTL0      (0x6UL<<SYS_GPB_MFPH_PB12MFP_Pos)   /*!< GPB_MFPH PB12 setting for USCI0_CTL0    */

//PB.13 MFP
#define SYS_GPB_MFPH_PB13MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB13MFP_Pos)   /*!< GPB_MFPH PB13 setting for GPIO          */
#define SYS_GPB_MFPH_PB13MFP_ADC_CH10        (0x3UL<<SYS_GPB_MFPH_PB13MFP_Pos)   /*!< GPB_MFPH PB13 setting for ADC_CH10      */
#define SYS_GPB_MFPH_PB13MFP_USCI0_CTL1      (0x6UL<<SYS_GPB_MFPH_PB13MFP_Pos)   /*!< GPB_MFPH PB13 setting for USCI0_CTL1    */

//PB.14 MFP
#define SYS_GPB_MFPH_PB14MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for GPIO          */
#define SYS_GPB_MFPH_PB14MFP_INT0            (0x1UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for INT0          */
#define SYS_GPB_MFPH_PB14MFP_UART0_nRTS      (0x2UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for UART0_nRTS    */
#define SYS_GPB_MFPH_PB14MFP_ADC_CH9         (0x3UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for ADC_CH9       */
#define SYS_GPB_MFPH_PB14MFP_BPWM1_CH0       (0x4UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for BPWM1_CH0     */
#define SYS_GPB_MFPH_PB14MFP_SPI0_SS         (0x7UL<<SYS_GPB_MFPH_PB14MFP_Pos)   /*!< GPB_MFPH PB14 setting for SPI0_SS       */

//PB.15 MFP
#define SYS_GPB_MFPH_PB15MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for GPIO          */
#define SYS_GPB_MFPH_PB15MFP_INT1            (0x1UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for INT1          */
#define SYS_GPB_MFPH_PB15MFP_TM0_EXT         (0x2UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for TM0_EXT       */
#define SYS_GPB_MFPH_PB15MFP_BPWM1_CH5       (0x4UL<<SYS_GPB_MFPH_PB15MFP_Pos)   /*!< GPB_MFPH PB15 setting for BPWM1_CH5     */

//PC.0 MFP
#define SYS_GPC_MFPL_PC0MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for GPIO            */
#define SYS_GPC_MFPL_PC0MFP_SPI0_SS          (0x1UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for SPI0_SS         */
#define SYS_GPC_MFPL_PC0MFP_PWM1_CH0         (0x4UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for PWM1_CH0        */
#define SYS_GPC_MFPL_PC0MFP_TM2              (0x5UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for TM2             */
#define SYS_GPC_MFPL_PC0MFP_UART0_RXD        (0x6UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for UART0_RXD       */
#define SYS_GPC_MFPL_PC0MFP_USCI0_CLK        (0x7UL<<SYS_GPC_MFPL_PC0MFP_Pos)    /*!< GPC_MFPL PC0 setting for USCI0_CLK       */

//PC.1 MFP
#define SYS_GPC_MFPL_PC1MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC1MFP_Pos)   /*!< GPC_MFPL PC1 setting for GPIO           */
#define SYS_GPC_MFPL_PC1MFP_SPI0_CLK         (0x1UL<<SYS_GPC_MFPL_PC1MFP_Pos)   /*!< GPC_MFPL PC1 setting for SPI0_CLK       */
#define SYS_GPC_MFPL_PC1MFP_PWM1_CH1         (0x4UL<<SYS_GPC_MFPL_PC1MFP_Pos)   /*!< GPC_MFPL PC1 setting for PWM1_CH1       */
#define SYS_GPC_MFPL_PC1MFP_UART0_TXD        (0x6UL<<SYS_GPC_MFPL_PC1MFP_Pos)   /*!< GPC_MFPL PC1 setting for UART0_TXD      */
#define SYS_GPC_MFPL_PC1MFP_USCI0_CTL0       (0x7UL<<SYS_GPC_MFPL_PC1MFP_Pos)   /*!< GPC_MFPL PC1 setting for USCI0_CTL0     */

//PC.2 MFP
#define SYS_GPC_MFPL_PC2MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC2MFP_Pos)   /*!< GPC_MFPL PC2 setting for GPIO           */
#define SYS_GPC_MFPL_PC2MFP_SPI0_MISO        (0x1UL<<SYS_GPC_MFPL_PC2MFP_Pos)   /*!< GPC_MFPL PC2 setting for SPI0_MISO      */
#define SYS_GPC_MFPL_PC2MFP_I2C1_SCL         (0x3UL<<SYS_GPC_MFPL_PC2MFP_Pos)   /*!< GPC_MFPL PC2 setting for I2C1_SCL       */
#define SYS_GPC_MFPL_PC2MFP_PWM1_CH2         (0x4UL<<SYS_GPC_MFPL_PC2MFP_Pos)   /*!< GPC_MFPL PC2 setting for PWM1_CH2       */
#define SYS_GPC_MFPL_PC2MFP_UART0_nCTS       (0x6UL<<SYS_GPC_MFPL_PC2MFP_Pos)   /*!< GPC_MFPL PC2 setting for UART0_nCTS     */
#define SYS_GPC_MFPL_PC2MFP_USCI0_DAT1       (0x7UL<<SYS_GPC_MFPL_PC2MFP_Pos)   /*!< GPC_MFPL PC2 setting for USCI0_DAT1     */

//PC.3 MFP
#define SYS_GPC_MFPL_PC3MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC3MFP_Pos)   /*!< GPC_MFPL PC3 setting for GPIO           */
#define SYS_GPC_MFPL_PC3MFP_SPI0_MOSI        (0x1UL<<SYS_GPC_MFPL_PC3MFP_Pos)   /*!< GPC_MFPL PC3 setting for SPI0_MOSI      */
#define SYS_GPC_MFPL_PC3MFP_I2C1_SDA         (0x3UL<<SYS_GPC_MFPL_PC3MFP_Pos)   /*!< GPC_MFPL PC3 setting for I2C1_SDA       */
#define SYS_GPC_MFPL_PC3MFP_PWM1_CH3         (0x4UL<<SYS_GPC_MFPL_PC3MFP_Pos)   /*!< GPC_MFPL PC3 setting for PWM1_CH3       */
#define SYS_GPC_MFPL_PC3MFP_UART0_nRTS       (0x6UL<<SYS_GPC_MFPL_PC3MFP_Pos)   /*!< GPC_MFPL PC3 setting for UART0_nRTS     */
#define SYS_GPC_MFPL_PC3MFP_USCI0_DAT0       (0x7UL<<SYS_GPC_MFPL_PC3MFP_Pos)   /*!< GPC_MFPL PC3 setting for USCI0_DAT0     */

//PC.4 MFP
#define SYS_GPC_MFPL_PC4MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC4MFP_Pos)   /*!< GPC_MFPL PC4 setting for GPIO           */
#define SYS_GPC_MFPL_PC4MFP_UART0_RXD        (0x2UL<<SYS_GPC_MFPL_PC4MFP_Pos)   /*!< GPC_MFPL PC4 setting for UART0_RXD      */
#define SYS_GPC_MFPL_PC4MFP_SPI0_I2SMCLK     (0x3UL<<SYS_GPC_MFPL_PC4MFP_Pos)   /*!< GPC_MFPL PC4 setting for SPI0_I2SMCLK   */
#define SYS_GPC_MFPL_PC4MFP_PWM1_CH4         (0x4UL<<SYS_GPC_MFPL_PC4MFP_Pos)   /*!< GPC_MFPL PC4 setting for PWM1_CH4       */
#define SYS_GPC_MFPL_PC4MFP_USCI0_DAT1       (0x7UL<<SYS_GPC_MFPL_PC4MFP_Pos)   /*!< GPC_MFPL PC4 setting for USCI0_DAT1     */

//PC.5 MFP
#define SYS_GPC_MFPL_PC5MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC5MFP_Pos)   /*!< GPC_MFPL PC5 setting for GPIO           */
#define SYS_GPC_MFPL_PC5MFP_UART0_TXD        (0x2UL<<SYS_GPC_MFPL_PC5MFP_Pos)   /*!< GPC_MFPL PC5 setting for UART0_TXD      */
#define SYS_GPC_MFPL_PC5MFP_PWM1_CH5         (0x4UL<<SYS_GPC_MFPL_PC5MFP_Pos)   /*!< GPC_MFPL PC5 setting for PWM1_CH5       */
#define SYS_GPC_MFPL_PC5MFP_USCI0_DAT0       (0x7UL<<SYS_GPC_MFPL_PC5MFP_Pos)   /*!< GPC_MFPL PC5 setting for USCI0_DAT0     */

//PC.8 MFP
#define SYS_GPC_MFPH_PC8MFP_GPIO             (0x0UL<<SYS_GPC_MFPH_PC8MFP_Pos)   /*!< GPC_MFPH PC8 setting for GPIO           */
#define SYS_GPC_MFPH_PC8MFP_STADC            (0x2UL<<SYS_GPC_MFPH_PC8MFP_Pos)   /*!< GPC_MFPH PC8 setting for STADC          */
#define SYS_GPC_MFPH_PC8MFP_SPI0_SS          (0x3UL<<SYS_GPC_MFPH_PC8MFP_Pos)   /*!< GPC_MFPH PC8 setting for SPI0_SS        */
#define SYS_GPC_MFPH_PC8MFP_PWM0_CH4         (0x4UL<<SYS_GPC_MFPH_PC8MFP_Pos)   /*!< GPC_MFPH PC8 setting for PWM0_CH4       */
#define SYS_GPC_MFPH_PC8MFP_PWM1_BRAKE0      (0x5UL<<SYS_GPC_MFPH_PC8MFP_Pos)   /*!< GPC_MFPH PC8 setting for PWM1_BRAKE0    */
#define SYS_GPC_MFPH_PC8MFP_USCI0_CTL0       (0x7UL<<SYS_GPC_MFPH_PC8MFP_Pos)   /*!< GPC_MFPH PC8 setting for USCI0_CTL0     */

//PC.9 MFP
#define SYS_GPC_MFPH_PC9MFP_GPIO             (0x0UL<<SYS_GPC_MFPH_PC9MFP_Pos)   /*!< GPC_MFPH PC9 setting for GPIO           */
#define SYS_GPC_MFPH_PC9MFP_SPI0_CLK         (0x3UL<<SYS_GPC_MFPH_PC9MFP_Pos)   /*!< GPC_MFPH PC9 setting for SPI0_CLK       */
#define SYS_GPC_MFPH_PC9MFP_PWM0_CH5         (0x4UL<<SYS_GPC_MFPH_PC9MFP_Pos)   /*!< GPC_MFPH PC9 setting for PWM0_CH5       */
#define SYS_GPC_MFPH_PC9MFP_PWM0_BRAKE1      (0x5UL<<SYS_GPC_MFPH_PC9MFP_Pos)   /*!< GPC_MFPH PC9 setting for PWM0_BRAKE1    */
#define SYS_GPC_MFPH_PC9MFP_USCI0_CLK        (0x7UL<<SYS_GPC_MFPH_PC9MFP_Pos)   /*!< GPC_MFPH PC9 setting for USCI0_CLK      */

//PC.10 MFP
#define SYS_GPC_MFPH_PC10MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for GPIO          */
#define SYS_GPC_MFPH_PC10MFP_SPI0_MISO       (0x3UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for SPI0_MISO     */
#define SYS_GPC_MFPH_PC10MFP_PWM0_CH0        (0x4UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for PWM0_CH0      */
#define SYS_GPC_MFPH_PC10MFP_USCI0_DAT1      (0x7UL<<SYS_GPC_MFPH_PC10MFP_Pos)   /*!< GPC_MFPH PC10 setting for USCI0_DAT1    */

//PC.11 MFP
#define SYS_GPC_MFPH_PC11MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for GPIO          */
#define SYS_GPC_MFPH_PC11MFP_SPI0_MOSI       (0x3UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for SPI0_MOSI     */
#define SYS_GPC_MFPH_PC11MFP_PWM0_CH1        (0x4UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for PWM0_CH1      */
#define SYS_GPC_MFPH_PC11MFP_TM1             (0x5UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for TM1           */
#define SYS_GPC_MFPH_PC11MFP_I2C0_SDA        (0x6UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for I2C0_SDA      */
#define SYS_GPC_MFPH_PC11MFP_USCI0_DAT0      (0x7UL<<SYS_GPC_MFPH_PC11MFP_Pos)   /*!< GPC_MFPH PC11 setting for USCI0_DAT0    */

//PC.12 MFP
#define SYS_GPC_MFPH_PC12MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for GPIO          */
#define SYS_GPC_MFPH_PC12MFP_PWM0_CH2        (0x2UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for PWM0_CH2      */
#define SYS_GPC_MFPH_PC12MFP_SPI0_I2SMCLK    (0x3UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for SPI0_I2SMCLK  */
#define SYS_GPC_MFPH_PC12MFP_CLKO            (0x4UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for CLKO          */
#define SYS_GPC_MFPH_PC12MFP_INT0            (0x5UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for INT0          */
#define SYS_GPC_MFPH_PC12MFP_I2C0_SCL        (0x6UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for I2C0_SCL      */
#define SYS_GPC_MFPH_PC12MFP_USCI0_CTL1      (0x7UL<<SYS_GPC_MFPH_PC12MFP_Pos)   /*!< GPC_MFPH PC12 setting for USCI0_CTL1    */

//PC.13 MFP
#define SYS_GPC_MFPH_PC13MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for GPIO          */
#define SYS_GPC_MFPH_PC13MFP_PWM0_CH3        (0x2UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for PWM0_CH3      */
#define SYS_GPC_MFPH_PC13MFP_CLKO            (0x3UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for CLKO          */
#define SYS_GPC_MFPH_PC13MFP_INT0            (0x5UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for INT0          */
#define SYS_GPC_MFPH_PC13MFP_I2C0_SDA        (0x6UL<<SYS_GPC_MFPH_PC13MFP_Pos)   /*!< GPC_MFPH PC13 setting for I2C0_SDA      */

//PD.0 MFP
#define SYS_GPD_MFPL_PD0MFP_GPIO              (0x0UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for GPIO            */
#define SYS_GPD_MFPL_PD0MFP_ADC_CH0           (0x3UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for ADC_CH0         */
#define SYS_GPD_MFPL_PD0MFP_UART0_nRTS        (0x5UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for UART0_nRTS      */
#define SYS_GPD_MFPL_PD0MFP_USCI0_CTL0        (0x6UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for USCI0_CTL0      */
#define SYS_GPD_MFPL_PD0MFP_SPI0_SS           (0x7UL<<SYS_GPD_MFPL_PD0MFP_Pos)    /*!< GPD_MFPL PD0 setting for SPI0_SS         */

//PD.1 MFP
#define SYS_GPD_MFPL_PD1MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD1MFP_Pos)   /*!< GPD_MFPL PD1 setting for GPIO           */
#define SYS_GPD_MFPL_PD1MFP_ADC_CH1          (0x3UL<<SYS_GPD_MFPL_PD1MFP_Pos)   /*!< GPD_MFPL PD1 setting for ADC_CH1        */
#define SYS_GPD_MFPL_PD1MFP_TM0_EXT          (0x4UL<<SYS_GPD_MFPL_PD1MFP_Pos)   /*!< GPD_MFPL PD1 setting for TM0_EXT        */
#define SYS_GPD_MFPL_PD1MFP_UART0_RXD        (0x5UL<<SYS_GPD_MFPL_PD1MFP_Pos)   /*!< GPD_MFPL PD1 setting for UART0_RXD      */
#define SYS_GPD_MFPL_PD1MFP_USCI0_CLK        (0x6UL<<SYS_GPD_MFPL_PD1MFP_Pos)   /*!< GPD_MFPL PD1 setting for USCI0_CLK      */
#define SYS_GPD_MFPL_PD1MFP_SPI0_CLK         (0x7UL<<SYS_GPD_MFPL_PD1MFP_Pos)   /*!< GPD_MFPL PD1 setting for SPI0_CLK       */

//PD.2 MFP
#define SYS_GPD_MFPL_PD2MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD2MFP_Pos)   /*!< GPD_MFPL PD2 setting for GPIO           */
#define SYS_GPD_MFPL_PD2MFP_ADC_CH2          (0x3UL<<SYS_GPD_MFPL_PD2MFP_Pos)   /*!< GPD_MFPL PD2 setting for ADC_CH2        */
#define SYS_GPD_MFPL_PD2MFP_TM3              (0x4UL<<SYS_GPD_MFPL_PD2MFP_Pos)   /*!< GPD_MFPL PD2 setting for TM3            */
#define SYS_GPD_MFPL_PD2MFP_UART0_TXD        (0x5UL<<SYS_GPD_MFPL_PD2MFP_Pos)   /*!< GPD_MFPL PD2 setting for UART0_TXD      */
#define SYS_GPD_MFPL_PD2MFP_USCI0_DAT1       (0x6UL<<SYS_GPD_MFPL_PD2MFP_Pos)   /*!< GPD_MFPL PD2 setting for USCI0_DAT1     */
#define SYS_GPD_MFPL_PD2MFP_SPI0_MISO        (0x7UL<<SYS_GPD_MFPL_PD2MFP_Pos)   /*!< GPD_MFPL PD2 setting for SPI0_MISO      */

//PD.3 MFP
#define SYS_GPD_MFPL_PD3MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD3MFP_Pos)   /*!< GPD_MFPL PD3 setting for GPIO           */
#define SYS_GPD_MFPL_PD3MFP_ADC_CH3          (0x3UL<<SYS_GPD_MFPL_PD3MFP_Pos)   /*!< GPD_MFPL PD3 setting for ADC_CH3        */
#define SYS_GPD_MFPL_PD3MFP_TM1_EXT          (0x4UL<<SYS_GPD_MFPL_PD3MFP_Pos)   /*!< GPD_MFPL PD3 setting for TM1_EXT        */
#define SYS_GPD_MFPL_PD3MFP_UART0_nCTS       (0x5UL<<SYS_GPD_MFPL_PD3MFP_Pos)   /*!< GPD_MFPL PD3 setting for UART0_nCTS     */
#define SYS_GPD_MFPL_PD3MFP_USCI0_DAT0       (0x6UL<<SYS_GPD_MFPL_PD3MFP_Pos)   /*!< GPD_MFPL PD3 setting for USCI0_DAT0     */
#define SYS_GPD_MFPL_PD3MFP_SPI0_MOSI        (0x7UL<<SYS_GPD_MFPL_PD3MFP_Pos)   /*!< GPD_MFPL PD3 setting for SPI0_MOSI      */

//PD.4 MFP
#define SYS_GPD_MFPL_PD4MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD4MFP_Pos)   /*!< GPD_MFPL PD4 setting for GPIO           */
#define SYS_GPD_MFPL_PD4MFP_ADC_CH4          (0x2UL<<SYS_GPD_MFPL_PD4MFP_Pos)   /*!< GPD_MFPL PD4 setting for ADC_CH4        */
#define SYS_GPD_MFPL_PD4MFP_BPWM1_CH5        (0x4UL<<SYS_GPD_MFPL_PD4MFP_Pos)   /*!< GPD_MFPL PD4 setting for BPWM1_CH5      */
#define SYS_GPD_MFPL_PD4MFP_UART0_nRTS       (0x5UL<<SYS_GPD_MFPL_PD4MFP_Pos)   /*!< GPD_MFPL PD4 setting for UART0_nRTS     */
#define SYS_GPD_MFPL_PD4MFP_USCI0_CTL0       (0x6UL<<SYS_GPD_MFPL_PD4MFP_Pos)   /*!< GPD_MFPL PD4 setting for USCI0_CTL0     */
#define SYS_GPD_MFPL_PD4MFP_SPI0_SS          (0x7UL<<SYS_GPD_MFPL_PD4MFP_Pos)   /*!< GPD_MFPL PD4 setting for SPI0_SS        */

//PD.5 MFP
#define SYS_GPD_MFPL_PD5MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD5MFP_Pos)   /*!< GPD_MFPL PD5 setting for GPIO           */
#define SYS_GPD_MFPL_PD5MFP_ADC_CH5          (0x2UL<<SYS_GPD_MFPL_PD5MFP_Pos)   /*!< GPD_MFPL PD5 setting for ADC_CH5        */
#define SYS_GPD_MFPL_PD5MFP_BPWM1_CH4        (0x4UL<<SYS_GPD_MFPL_PD5MFP_Pos)   /*!< GPD_MFPL PD5 setting for BPWM1_CH4      */

//PD.8 MFP
#define SYS_GPD_MFPH_PD8MFP_GPIO             (0x0UL<<SYS_GPD_MFPH_PD8MFP_Pos)   /*!< GPD_MFPH PD8 setting for GPIO           */
#define SYS_GPD_MFPH_PD8MFP_USCI0_DAT0       (0x6UL<<SYS_GPD_MFPH_PD8MFP_Pos)   /*!< GPD_MFPH PD8 setting for USCI0_DAT0     */

//PD.9 MFP
#define SYS_GPD_MFPH_PD9MFP_GPIO             (0x0UL<<SYS_GPD_MFPH_PD9MFP_Pos)   /*!< GPD_MFPH PD9 setting for GPIO           */
#define SYS_GPD_MFPH_PD9MFP_PWM0_BRAKE1      (0x5UL<<SYS_GPD_MFPH_PD9MFP_Pos)   /*!< GPD_MFPH PD9 setting for PWM0_BRAKE1    */

//PD.10 MFP
#define SYS_GPD_MFPH_PD10MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD10MFP_Pos)   /*!< GPD_MFPH PD10 setting for GPIO          */
#define SYS_GPD_MFPH_PD10MFP_CLKO            (0x1UL<<SYS_GPD_MFPH_PD10MFP_Pos)   /*!< GPD_MFPH PD10 setting for CLKO          */
#define SYS_GPD_MFPH_PD10MFP_BPWM0_CH5       (0x4UL<<SYS_GPD_MFPH_PD10MFP_Pos)   /*!< GPD_MFPH PD10 setting for BPWM0_CH5     */

//PD.11 MFP
#define SYS_GPD_MFPH_PD11MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD11MFP_Pos)   /*!< GPD_MFPH PD11 setting for GPIO          */
#define SYS_GPD_MFPH_PD11MFP_INT1            (0x1UL<<SYS_GPD_MFPH_PD11MFP_Pos)   /*!< GPD_MFPH PD11 setting for INT1          */
#define SYS_GPD_MFPH_PD11MFP_BPWM0_CH4       (0x4UL<<SYS_GPD_MFPH_PD11MFP_Pos)   /*!< GPD_MFPH PD11 setting for BPWM0_CH4     */

//PE.0 MFP
#define SYS_GPE_MFPL_PE0MFP_GPIO              (0x0UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for GPIO            */
#define SYS_GPE_MFPL_PE0MFP_INT0              (0x1UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for INT0            */
#define SYS_GPE_MFPL_PE0MFP_CLKO              (0x3UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for CLKO            */
#define SYS_GPE_MFPL_PE0MFP_PWM0_CH3          (0x4UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for PWM0_CH3        */
#define SYS_GPE_MFPL_PE0MFP_TM1_EXT           (0x5UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for TM1_EXT         */
#define SYS_GPE_MFPL_PE0MFP_USCI0_DAT0        (0x7UL<<SYS_GPE_MFPL_PE0MFP_Pos)    /*!< GPE_MFPL PE0 setting for USCI0_DAT0      */

//PE.1 MFP
#define SYS_GPE_MFPL_PE1MFP_GPIO             (0x0UL<<SYS_GPE_MFPL_PE1MFP_Pos)   /*!< GPE_MFPL PE1 setting for GPIO           */
#define SYS_GPE_MFPL_PE1MFP_STADC            (0x2UL<<SYS_GPE_MFPL_PE1MFP_Pos)   /*!< GPE_MFPL PE1 setting for STADC          */
#define SYS_GPE_MFPL_PE1MFP_CLKO             (0x3UL<<SYS_GPE_MFPL_PE1MFP_Pos)   /*!< GPE_MFPL PE1 setting for CLKO           */
#define SYS_GPE_MFPL_PE1MFP_TM3              (0x5UL<<SYS_GPE_MFPL_PE1MFP_Pos)   /*!< GPE_MFPL PE1 setting for TM3            */
#define SYS_GPE_MFPL_PE1MFP_USCI0_DAT1       (0x7UL<<SYS_GPE_MFPL_PE1MFP_Pos)   /*!< GPE_MFPL PE1 setting for USCI0_DAT1     */

//PE.2 MFP
#define SYS_GPE_MFPL_PE2MFP_GPIO             (0x0UL<<SYS_GPE_MFPL_PE2MFP_Pos)   /*!< GPE_MFPL PE2 setting for GPIO           */
#define SYS_GPE_MFPL_PE2MFP_INT1             (0x1UL<<SYS_GPE_MFPL_PE2MFP_Pos)   /*!< GPE_MFPL PE2 setting for INT1           */
#define SYS_GPE_MFPL_PE2MFP_TM0_EXT          (0x5UL<<SYS_GPE_MFPL_PE2MFP_Pos)   /*!< GPE_MFPL PE2 setting for TM0_EXT        */
#define SYS_GPE_MFPL_PE2MFP_I2C0_SCL         (0x6UL<<SYS_GPE_MFPL_PE2MFP_Pos)   /*!< GPE_MFPL PE2 setting for I2C0_SCL       */
#define SYS_GPE_MFPL_PE2MFP_USCI0_CTL1       (0x7UL<<SYS_GPE_MFPL_PE2MFP_Pos)   /*!< GPE_MFPL PE2 setting for USCI0_CTL1     */

//PF.0 MFP
#define SYS_GPF_MFPL_PF0MFP_GPIO              (0x0UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for GPIO            */
#define SYS_GPF_MFPL_PF0MFP_XT_OUT            (0x1UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for XT_OUT          */
#define SYS_GPF_MFPL_PF0MFP_XT1_OUT           (0x1UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for XT1_OUT         */
#define SYS_GPF_MFPL_PF0MFP_X32_OUT           (0x1UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for X32_OUT         */
#define SYS_GPF_MFPL_PF0MFP_BPWM1_CH3         (0x4UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for BPWM1_CH3       */
#define SYS_GPF_MFPL_PF0MFP_TM3               (0x5UL<<SYS_GPF_MFPL_PF0MFP_Pos)    /*!< GPF_MFPL PF0 setting for TM3             */

//PF.1 MFP
#define SYS_GPF_MFPL_PF1MFP_GPIO             (0x0UL<<SYS_GPF_MFPL_PF1MFP_Pos)   /*!< GPF_MFPL PF1 setting for GPIO           */
#define SYS_GPF_MFPL_PF1MFP_XT_IN            (0x1UL<<SYS_GPF_MFPL_PF1MFP_Pos)   /*!< GPF_MFPL PF1 setting for XT_IN          */
#define SYS_GPF_MFPL_PF1MFP_XT1_IN           (0x1UL<<SYS_GPF_MFPL_PF1MFP_Pos)   /*!< GPF_MFPL PF1 setting for XT1_IN         */
#define SYS_GPF_MFPL_PF1MFP_X32_IN           (0x1UL<<SYS_GPF_MFPL_PF1MFP_Pos)   /*!< GPF_MFPL PF1 setting for X32_IN         */
#define SYS_GPF_MFPL_PF1MFP_BPWM1_CH2        (0x4UL<<SYS_GPF_MFPL_PF1MFP_Pos)   /*!< GPF_MFPL PF1 setting for BPWM1_CH2      */
#define SYS_GPF_MFPL_PF1MFP_TM1_EXT          (0x5UL<<SYS_GPF_MFPL_PF1MFP_Pos)   /*!< GPF_MFPL PF1 setting for TM1_EXT        */

//PF.2 MFP
#define SYS_GPF_MFPL_PF2MFP_GPIO             (0x0UL<<SYS_GPF_MFPL_PF2MFP_Pos)   /*!< GPF_MFPL PF2 setting for GPIO           */
#define SYS_GPF_MFPL_PF2MFP_ICE_DAT          (0x1UL<<SYS_GPF_MFPL_PF2MFP_Pos)   /*!< GPF_MFPL PF2 setting for ICE_DAT        */
#define SYS_GPF_MFPL_PF2MFP_I2C0_SDA         (0x2UL<<SYS_GPF_MFPL_PF2MFP_Pos)   /*!< GPF_MFPL PF2 setting for I2C0_SDA       */
#define SYS_GPF_MFPL_PF2MFP_ADC_CH6          (0x3UL<<SYS_GPF_MFPL_PF2MFP_Pos)   /*!< GPF_MFPL PF2 setting for ADC_CH6        */
#define SYS_GPF_MFPL_PF2MFP_BPWM1_CH3        (0x4UL<<SYS_GPF_MFPL_PF2MFP_Pos)   /*!< GPF_MFPL PF2 setting for BPWM1_CH3      */

//PF.3 MFP
#define SYS_GPF_MFPL_PF3MFP_GPIO             (0x0UL<<SYS_GPF_MFPL_PF3MFP_Pos)   /*!< GPF_MFPL PF3 setting for GPIO           */
#define SYS_GPF_MFPL_PF3MFP_ICE_CLK          (0x1UL<<SYS_GPF_MFPL_PF3MFP_Pos)   /*!< GPF_MFPL PF3 setting for ICE_CLK        */
#define SYS_GPF_MFPL_PF3MFP_I2C0_SCL         (0x2UL<<SYS_GPF_MFPL_PF3MFP_Pos)   /*!< GPF_MFPL PF3 setting for I2C0_SCL       */
#define SYS_GPF_MFPL_PF3MFP_ADC_CH7          (0x3UL<<SYS_GPF_MFPL_PF3MFP_Pos)   /*!< GPF_MFPL PF3 setting for ADC_CH7        */
#define SYS_GPF_MFPL_PF3MFP_BPWM1_CH2        (0x4UL<<SYS_GPF_MFPL_PF3MFP_Pos)   /*!< GPF_MFPL PF3 setting for BPWM1_CH2      */

//PF.4 MFP
#define SYS_GPF_MFPL_PF4MFP_GPIO             (0x0UL<<SYS_GPF_MFPL_PF4MFP_Pos)   /*!< GPF_MFPL PF4 setting for GPIO           */
#define SYS_GPF_MFPL_PF4MFP_ICE_DAT          (0x1UL<<SYS_GPF_MFPL_PF4MFP_Pos)   /*!< GPF_MFPL PF4 setting for ICE_DAT        */
#define SYS_GPF_MFPL_PF4MFP_I2C0_SDA         (0x2UL<<SYS_GPF_MFPL_PF4MFP_Pos)   /*!< GPF_MFPL PF4 setting for I2C0_SDA       */
#define SYS_GPF_MFPL_PF4MFP_UART0_TXD        (0x3UL<<SYS_GPF_MFPL_PF4MFP_Pos)   /*!< GPF_MFPL PF4 setting for UART0_TXD      */
#define SYS_GPF_MFPL_PF4MFP_PWM0_CH3         (0x4UL<<SYS_GPF_MFPL_PF4MFP_Pos)   /*!< GPF_MFPL PF4 setting for PWM0_CH3       */

//PF.5 MFP
#define SYS_GPF_MFPL_PF5MFP_GPIO             (0x0UL<<SYS_GPF_MFPL_PF5MFP_Pos)   /*!< GPF_MFPL PF5 setting for GPIO           */
#define SYS_GPF_MFPL_PF5MFP_ICE_CLK          (0x1UL<<SYS_GPF_MFPL_PF5MFP_Pos)   /*!< GPF_MFPL PF5 setting for ICE_CLK        */
#define SYS_GPF_MFPL_PF5MFP_I2C0_SCL         (0x2UL<<SYS_GPF_MFPL_PF5MFP_Pos)   /*!< GPF_MFPL PF5 setting for I2C0_SCL       */
#define SYS_GPF_MFPL_PF5MFP_UART0_RXD        (0x3UL<<SYS_GPF_MFPL_PF5MFP_Pos)   /*!< GPF_MFPL PF5 setting for UART0_RXD      */


/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */

/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/


/**
  * @brief      Clear Brown-out detector interrupt flag
  * @param      None
  * @return     None
  * @details    This macro clear Brown-out detector interrupt flag.
  * \hideinitializer
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCTL |= SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Set Brown-out detector function to normal mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to normal mode.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_CLEAR_BOD_LPM()             (SYS->BODCTL &= ~SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_BOD()               (SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Enable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_BOD()                (SYS->BODCTL |= SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Get Brown-out detector interrupt flag
  * @param      None
  * @retval     0   Brown-out detect interrupt flag is not set.
  * @retval     >=1 Brown-out detect interrupt flag is set.
  * @details    This macro get Brown-out detector interrupt flag.
  * \hideinitializer
  */
#define SYS_GET_BOD_INT_FLAG()          (SYS->BODCTL & SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Get Brown-out detector status
  * @param      None
  * @retval     0   System voltage is higher than BOD threshold voltage setting or BOD function is disabled.
  * @retval     >=1 System voltage is lower than BOD threshold voltage setting.
  * @details    This macro get Brown-out detector output status.
  *             If the BOD function is disabled, this function always return 0.
  * \hideinitializer
  */
#define SYS_GET_BOD_OUTPUT()            (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk)

/**
  * @brief      Enable Brown-out detector interrupt function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector interrupt function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCTL &= ~SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Enable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detect reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCTL |= SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Set Brown-out detector function low power mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to low power mode.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
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
  * \hideinitializer
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCTL = (SYS->BODCTL & ~SYS_BODCTL_BODVL_Msk) | (u32Level))

/**
  * @brief      Get reset source is from Brown-out detector reset
  * @param      None
  * @retval     0   Previous reset source is not from Brown-out detector reset
  * @retval     >=1 Previous reset source is from Brown-out detector reset
  * @details    This macro get previous reset source is from Brown-out detect reset or not.
  * \hideinitializer
  */
#define SYS_IS_BOD_RST()                (SYS->RSTSTS & SYS_RSTSTS_BODRF_Msk)

/**
  * @brief      Get reset source is from CPU reset
  * @param      None
  * @retval     0   Previous reset source is not from CPU reset
  * @retval     >=1 Previous reset source is from CPU reset
  * @details    This macro get previous reset source is from CPU reset.
  * \hideinitializer
  */
#define SYS_IS_CPU_RST()                (SYS->RSTSTS & SYS_RSTSTS_CPURF_Msk)

/**
  * @brief      Get reset source is from LVR Reset
  * @param      None
  * @retval     0   Previous reset source is not from Low-Voltage-Reset
  * @retval     >=1 Previous reset source is from Low-Voltage-Reset
  * @details    This macro get previous reset source is from Low-Voltage-Reset.
  * \hideinitializer
  */
#define SYS_IS_LVR_RST()                (SYS->RSTSTS & SYS_RSTSTS_LVRF_Msk)

/**
  * @brief      Get reset source is from Power-on Reset
  * @param      None
  * @retval     0   Previous reset source is not from Power-on Reset
  * @retval     >=1 Previous reset source is from Power-on Reset
  * @details    This macro get previous reset source is from Power-on Reset.
  * \hideinitializer
  */
#define SYS_IS_POR_RST()                (SYS->RSTSTS & SYS_RSTSTS_PORF_Msk)

/**
  * @brief      Get reset source is from reset pin reset
  * @param      None
  * @retval     0   Previous reset source is not from reset pin reset
  * @retval     >=1 Previous reset source is from reset pin reset
  * @details    This macro get previous reset source is from reset pin reset.
  * \hideinitializer
  */
#define SYS_IS_RSTPIN_RST()             (SYS->RSTSTS & SYS_RSTSTS_PINRF_Msk)

/**
  * @brief      Get reset source is from system reset
  * @param      None
  * @retval     0   Previous reset source is not from system reset
  * @retval     >=1 Previous reset source is from system reset
  * @details    This macro get previous reset source is from system reset.
  * \hideinitializer
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSTS & SYS_RSTSTS_MCURF_Msk)

/**
  * @brief      Get reset source is from window watch dog reset
  * @param      None
  * @retval     0   Previous reset source is not from window watch dog reset
  * @retval     >=1 Previous reset source is from window watch dog reset
  * @details    This macro get previous reset source is from window watch dog reset.
  * \hideinitializer
  */
#define SYS_IS_WDT_RST()                (SYS->RSTSTS & SYS_RSTSTS_WDTRF_Msk)

/**
  * @brief      Disable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_LVR()               (SYS->BODCTL &= ~SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Enable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_LVR()                (SYS->BODCTL |= SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Disable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_POR()               (SYS->PORCTL = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
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
  * @return     None
  * @details    This macro clear reset source flag.
  * \hideinitializer
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
    while (SYS->REGLCTL == 0);
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
