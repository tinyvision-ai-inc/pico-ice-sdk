/**************************************************************************//**
 * @file     SYS.h
 * @version  V1.0
 * $Revision  1 $
 * $Date: 14/07/01 1:13p $
 * @brief    NUC505 SYS Header File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SYS_Driver SYS Driver
  @{
*/

/** @addtogroup NUC505_SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Reset Status Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
//SYS->RSTSTS
#define  SYS_RSTSTS_RST           (0x1UL<<SYS_RSTSTS_PINRF_Pos)         /*!<System reset by pulling down external reset pin. \hideinitializer */
#define  SYS_RSTSTS_LVR           (0x1UL<<SYS_RSTSTS_LVRF_Pos)          /*!<System reset by low voltage. \hideinitializer */
#define  SYS_RSTSTS_WDT           (0x1UL<<SYS_RSTSTS_WDTRF_Pos)         /*!<System reset by watchdog timer. \hideinitializer */
#define  SYS_RSTSTS_CPU           (0x1UL<<SYS_RSTSTS_CPURF_Pos)         /*!<System reset by reset CPU. \hideinitializer */
#define  SYS_RSTSTS_POR           (0x1UL<<SYS_RSTSTS_PORF_Pos)          /*!<System reset by power on reset. \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
/* How to use below #define?
Example 1: If user want to reset UART0
            Programmer can issue following API to achieve it.

            SYS_ResetModule(UART0_RST);

        Remember that programmer need to reset module one by one. The parameter is mutually exclusive and only one selected.
*/
#define CHIP_RST  ((0x0<<24)|SYS_IPRST0_CHIPRST_Pos)    /*!<Reset CHIP  \hideinitializer */
#define CPU_RST   ((0x0<<24)|SYS_IPRST0_CPURST_Pos)     /*!<Reset CPU  \hideinitializer */
#define UART0_RST ((0xC<<24)|SYS_IPRST1_UART0RST_Pos)   /*!<Reset UART0 \hideinitializer */
#define UART1_RST ((0xC<<24)|SYS_IPRST1_UART1RST_Pos)   /*!<Reset UART1 \hideinitializer */
#define TMR0_RST  ((0xC<<24)|SYS_IPRST1_TMR0RST_Pos)    /*!<Reset TMR0  \hideinitializer */
#define TMR1_RST  ((0xC<<24)|SYS_IPRST1_TMR1RST_Pos)    /*!<Reset TMR1 \hideinitializer */
#define WDTF_RST  ((0xC<<24)|SYS_IPRST1_WDTFRST_Pos)    /*!<Reset WDT Full \hideinitializer */
#define TMR2_RST  ((0xC<<24)|SYS_IPRST1_TMR2RST_Pos)    /*!<Reset TMR2 \hideinitializer */
#define UART2_RST ((0xC<<24)|SYS_IPRST1_UART2RST_Pos)   /*!<Reset UART1 \hideinitializer */
#define PWM_RST   ((0xC<<24)|SYS_IPRST1_PWMRST_Pos)     /*!<Reset PWM \hideinitializer */
#define I2C0_RST  ((0xC<<24)|SYS_IPRST1_I2C0RST_Pos)    /*!<Reset I2C0 \hideinitializer */
#define I2C1_RST  ((0xC<<24)|SYS_IPRST1_I2C1RST_Pos)    /*!<Reset I2C1 \hideinitializer */
#define SPIM_RST  ((0xC<<24)|SYS_IPRST1_SPIMRST_Pos)    /*!<Reset SPI0 \hideinitializer */
#define USBD_RST  ((0xC<<24)|SYS_IPRST1_USBDRST_Pos)    /*!<Reset USBD \hideinitializer */
#define WDTP_RST  ((0xC<<24)|SYS_IPRST1_WDTPRST_Pos)    /*!<Reset WDT Partial \hideinitializer */
#define MTP_RST   ((0xC<<24)|SYS_IPRST1_MTPRST_Pos)     /*!<Reset MTP \hideinitializer */
#define I2S_RST   ((0xC<<24)|SYS_IPRST1_I2SRST_Pos)     /*!<Reset MTP \hideinitializer */
#define USBH_RST  ((0xC<<24)|SYS_IPRST1_USBHRST_Pos)    /*!<Reset USBH \hideinitializer */
#define SDH_RST   ((0xC<<24)|SYS_IPRST1_SDHRST_Pos)     /*!<Reset SDH \hideinitializer */
#define SRAM_RST  ((0xC<<24)|SYS_IPRST1_SRAMRST_Pos)    /*!<Reset SRAM \hideinitializer */
#define GPIO_RST  ((0xC<<24)|SYS_IPRST1_GPIORST_Pos)    /*!<Reset GPIO \hideinitializer */
#define ADC_RST   ((0xC<<24)|SYS_IPRST1_ADCRST_Pos)     /*!<Reset ADC \hideinitializer  */
#define SPI0_RST  ((0xC<<24)|SYS_IPRST1_SPI0RST_Pos)    /*!<Reset SPI0 \hideinitializer  */
#define SPI1_RST  ((0xC<<24)|SYS_IPRST1_SPI1RST_Pos)    /*!<Reset SPI1 \hideinitializer  */

/*---------------------------------------------------------------------------------------------------------*/
/*  BOOTSET constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_BOOT_ICE_ESPI        (0x6)                                    /*!<Boot from ICE with external SPI flash. \hideinitializer */
#define  SYS_BOOT_ICE_SPI             (0x7)                                    /*!<Boot from ICP with SPI flash. \hideinitializer */
#define  SYS_BOOT_ICP                   (0xB)                                  /*!<Boot from ICP. \hideinitializer */
#define  SYS_BOOT_ESPI                (0xD)                                    /*!<Boot from external SPI flash. \hideinitializer */
#define  SYS_BOOT_USB                   (0xE)                                  /*!<Boot from USB. \hideinitializer */
#define  SYS_BOOT_SPI                   (0xF)                                  /*!<Boot from SPI flash. \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  LVD constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_LVD_FLAG                   (0x1UL<<SYS_LVDCTL_LVDIF_Pos)      /*!<Low voltage detection flag. Write 1 to clear the bit \hideinitializer */
#define  SYS_LVD_2_6V                 (0x0UL<<SYS_LVDCTL_LVDSEL_Pos)     /*!<Threshold voltage of LVD is selected 2.6V \hideinitializer */
#define  SYS_LVD_2_8V                 (0x1UL<<SYS_LVDCTL_LVDSEL_Pos)     /*!<Threshold voltage of LVD is selected 2.8V \hideinitializer */
#define  SYS_LVD_ENABLE               (0x1UL<<SYS_LVDCTL_LVDEN_Pos)        /*!<Enable LVD function \hideinitializer */
#define  SYS_LVD_DISABLE                (0x0UL<<SYS_LVDCTL_LVDEN_Pos)      /*!<Disable LVD function \hideinitializer */
#define  SYS_LVR_ENABLE               (0x1UL<<SYS_LVDCTL_LVDEN_Pos)        /*!<Enable LVR function \hideinitializer */
#define  SYS_LVR_DISABLE                (0x0UL<<SYS_LVDCTL_LVDEN_Pos)      /*!<Disable LVR function \hideinitializer */
#define  SYS_POR_DISABLE                (0x1UL<<SYS_LVDCTL_PORENB_Pos)     /*!<Disable power on reset function \hideinitializer */
#define  SYS_POR_ENABLE               (0x0UL<<SYS_LVDCTL_PORENB_Pos)       /*!<Enable power on reset function \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Wake-up constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_WAKEUP_I2C0              (SYS_WAKEUP_I2C0WE_Msk)      /*!<Wakeup source from I2C0 \hideinitializer */
#define  SYS_WAKEUP_I2C1                (SYS_WAKEUP_I2C1WE_Msk)        /*!<Wakeup source from I2C1 \hideinitializer */
#define  SYS_WAKEUP_GPIO                (SYS_WAKEUP_GPIOWE_Msk)        /*!<Wakeup source from GPIO \hideinitializer */
#define  SYS_WAKEUP_RTC                 (SYS_WAKEUP_RTCWE_Msk)       /*!<Wakeup source from RTC \hideinitializer */
#define  SYS_WAKEUP_WDT                 (SYS_WAKEUP_WDTWE_Msk)       /*!<Wakeup source from WDT \hideinitializer */
#define  SYS_WAKEUP_TMR0                (SYS_WAKEUP_TMR0WE_Msk)        /*!<Wakeup source from TMR0 \hideinitializer */
#define  SYS_WAKEUP_TMR1                    (SYS_WAKEUP_TMR1WE_Msk)        /*!<Wakeup source from TMR1 \hideinitializer */
#define  SYS_WAKEUP_TMR2                (SYS_WAKEUP_TMR2WE_Msk)        /*!<Wakeup source from TMR2 \hideinitializer */
#define  SYS_WAKEUP_TMR3                (SYS_WAKEUP_TMR3WE_Msk)        /*!<Wakeup source from TMR3 \hideinitializer */
#define  SYS_WAKEUP_UART0               (SYS_WAKEUP_UART0WE_Msk)     /*!<Wakeup source from UART0 \hideinitializer */
#define  SYS_WAKEUP_UART1           (SYS_WAKEUP_UART1WE_Msk)     /*!<Wakeup source from UART1 \hideinitializer */
#define  SYS_WAKEUP_UART2               (SYS_WAKEUP_UART2WE_Msk)     /*!<Wakeup source from UART2 \hideinitializer */
#define  SYS_WAKEUP_USBD            (SYS_WAKEUP_USBDWE_Msk)        /*!<Wakeup source from USBD \hideinitializer */
#define  SYS_WAKEUP_USBH                (SYS_WAKEUP_USBHWE_Msk)        /*!<Wakeup source from USBH \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  NMI channels constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_NMI_RTC                (SYS_NMICTL_RTCIEN_Msk)         /*!<NMI source from RTC \hideinitializer */
#define  SYS_NMI_WDT                    (SYS_NMICTL_WDTIEN_Msk)         /*!<NMI source from WDT \hideinitializer */
#define  SYS_NMI_POR                    (SYS_NMICTL_PORIEN_Msk)         /*!<NMI source from POR \hideinitializer */
#define  SYS_NMI_EINT0              (SYS_NMICTL_EINT0IEN_Msk)       /*!<NMI source from EINT0 \hideinitializer */
#define  SYS_NMI_EINT1              (SYS_NMICTL_EINT1IEN_Msk)       /*!<NMI source from EINT1 \hideinitializer */
#define  SYS_NMI_EINT2              (SYS_NMICTL_EINT2IEN_Msk)       /*!<NMI source from EINT2 \hideinitializer */
#define  SYS_NMI_EINT3                  (SYS_NMICTL_EINT3IEN_Msk)       /*!<NMI source from EINT3 \hideinitializer */
#define  SYS_NMI_LVD                    (SYS_NMICTL_LVDIEN_Msk)         /*!<NMI source from LVD \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  AHB priority constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_AHB_PRI_FIXED      (0x0UL<<SYS_AHBCTL_PRISEL_Pos)     /*!<AHB bus arbitration Fixed Priority mode \hideinitializer */
#define  SYS_AHB_PRI_ROTATE       (0x1UL<<SYS_AHBCTL_PRISEL_Pos)       /*!<AHB bus arbitration Round-Robin priority mode \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Ports constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_PORT_A         (0)                                             /*!<GPA port \hideinitializer */
#define  SYS_PORT_B         (1)                                               /*!<GPB port \hideinitializer */
#define  SYS_PORT_C         (2)                                             /*!<GPC port  \hideinitializer */
#define  SYS_PORT_D         (3)                                             /*!<GPD port  \hideinitializer */
/*---------------------------------------------------------------------------------------------------------*/
/*  Pins driving strength constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_PIN_0          (0)                                             /*!<Port pin0 \hideinitializer */
#define  SYS_PIN_1          (1)                                                 /*!<Port pin1 \hideinitializer */
#define  SYS_PIN_2          (2)                                             /*!<Port pin2 \hideinitializer */
#define  SYS_PIN_3          (3)                                             /*!<Port pin3 \hideinitializer */
#define  SYS_PIN_4          (4)                                             /*!<Port pin4 \hideinitializer */
#define  SYS_PIN_5          (5)                                                 /*!<Port pin5 \hideinitializer */
#define  SYS_PIN_6          (6)                                             /*!<Port pin6 \hideinitializer */
#define  SYS_PIN_7          (7)                                             /*!<Port pin7 \hideinitializer */
#define  SYS_PIN_8          (8)                                             /*!<Port pin8 \hideinitializer */
#define  SYS_PIN_9          (9)                                                 /*!<Port pin9 \hideinitializer */
#define  SYS_PIN_10         (10)                                            /*!<Port pin10 \hideinitializer */
#define  SYS_PIN_11         (11)                                            /*!<Port pin11 \hideinitializer */
#define  SYS_PIN_12         (12)                                            /*!<Port pin12 \hideinitializer */
#define  SYS_PIN_13             (13)                                                /*!<Port pin13 \hideinitializer */
#define  SYS_PIN_14         (14)                                            /*!<Port pin14 \hideinitializer */
#define  SYS_PIN_15         (15)                                            /*!<Port pin15 \hideinitializer */
/*---------------------------------------------------------------------------------------------------------*/
/*  Analog and Digital shared pins driving strength constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_DRIVING_STRENGTH_2MA           (0)                     /*!<GPA[7:0]/GPD[4:2] pin's driving strength 2mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_6P5MA     (1)                         /*!<GPA[7:0]/GPD[4:2] pin's driving strength 6.5mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_8P7MA     (2)                     /*!<GPA[7:0]/GPD[4:2] pin's driving strength 8.7mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_13MA      (3)                     /*!<GPA[7:0]/GPD[4:2] pin's driving strength 13mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_15P2MA        (4)                         /*!<GPA[7:0]/GPD[4:2] pin's driving strength 15.2mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_19P5MA        (5)                         /*!<GPA[7:0]/GPD[4:2] pin's driving strength 19.5mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_21P7MA        (6)                     /*!<GPA[7:0]/GPD[4:2] pin's driving strength 21.7mA \hideinitializer */
#define  SYS_DRIVING_STRENGTH_26P1MA        (7)                         /*!<GPA[7:0]/GPD[4:2] pin's driving strength 26.1mA \hideinitializer */



/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
/* How to use below #define?
Example 1: If user want to set PA.0 as ADC_CH0 in initial function,
           user can issue following command to achieve it.

           SYS->GPA_MFPL  = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA0MFP_Msk) ) | SYS_GPA_MFPL_PA0MFP_ADC_CH0;

*/
//GPA_MFPL_PA0MFP
#define SYS_GPA_MFPL_PA0MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for GPIO \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_ADC_CH0     (0x1UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for ADC_CH0 \hideinitializer */

//GPA_MFPL_PA1MFP
#define SYS_GPA_MFPL_PA1MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for GPIO \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_ADC_CH1     (0x1UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for ADC_CH1 \hideinitializer */

//GPA_MFPL_PA2MFP
#define SYS_GPA_MFPL_PA2MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_ADC_CH2     (0x1UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for ADC_CH2    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_I2S_MCLK    (0x2UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for I2S_MCLK   \hideinitializer */

//GPA_MFPL_PA3MFP
#define SYS_GPA_MFPL_PA3MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_ADC_CH3     (0x1UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for ADC_CH3      \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_I2S_DIN     (0x2UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for I2S_DIN       \hideinitializer */

//GPA_MFPL_PA4MFP
#define SYS_GPA_MFPL_PA4MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA4MFP_Pos)           /*!< GPA_MFPL PA4 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_ADC_CH4     (0x1UL<<SYS_GPA_MFPL_PA4MFP_Pos)           /*!< GPA_MFPL PA4 setting for ADC_CH4     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_I2S_DOUT    (0x2UL<<SYS_GPA_MFPL_PA4MFP_Pos)           /*!< GPA_MFPL PA4 setting for I2S_DOUT    \hideinitializer */

//GPA_MFPL_PA5MFP
#define SYS_GPA_MFPL_PA5MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA5MFP_Pos)           /*!< GPA_MFPL PA5 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_ADC_CH5     (0x1UL<<SYS_GPA_MFPL_PA5MFP_Pos)           /*!< GPA_MFPL PA5 setting for ADC_CH5     \hideinitializer */

//GPA_MFPL_PA6MFP
#define SYS_GPA_MFPL_PA6MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_ADC_CH6     (0x1UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for ADC_CH6     \hideinitializer */

//GPA_MFPL_PA7MFP
#define SYS_GPA_MFPL_PA7MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_ADC_CH7     (0x1UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for ADC_CH7    \hideinitializer */

//GPA_MFPH_PA8MFP
#define SYS_GPA_MFPH_PA8MFP_GPIO        (0x0UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_SPIM_SS     (0x1UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for SPIM_SS   \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_I2S_LRCLK   (0x2UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for I2S_LRCLK     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_UART1_TXD   (0x3UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for UART1_TXD    \hideinitializer */

//GPA_MFPH_PA9MFP
#define SYS_GPA_MFPH_PA9MFP_GPIO        (0x0UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for GPIO      \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_SPIM_CLK   (0x1UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for SPIM_CLK \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_I2S_BCLK    (0x2UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for I2S_BCLK  \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_UART1_RXD   (0x3UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for UART1_RXD \hideinitializer */

//GPA_MFPH_PA10MFP
#define SYS_GPA_MFPH_PA10MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_SPIM_MOSI  (0x1UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for SPIM_MOSI  \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_I2C1_SCL   (0x2UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for I2C1_SCL   \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_SD_CLK     (0x4UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for SD_CLK  \hideinitializer */

//GPA_MFPH_PA11MFP
#define SYS_GPA_MFPH_PA11MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_SPIM_MISO  (0x1UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for SPIM_MISO  \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_I2C1_SDA   (0x2UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for I2C1_SDA   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_SD_CMD     (0x4UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for SD_CMD   \hideinitializer */

//GPA_MFPH_PA12MFP
#define SYS_GPA_MFPH_PA12MFP_GPIO               (0x0UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_SPIM_D2          (0x1UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for SPIM_D2   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_TM0_CNT_OUT    (0x2UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for TM0_CNT_OUT   \hideinitializer */

//GPA_MFPH_PA13MFP
#define SYS_GPA_MFPH_PA13MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_SPIM_D3    (0x1UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for SPIM_D3   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_TM0_EXT    (0x2UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for TM0_EXT   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_SD_nCD     (0x4UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for SD_nCD  \hideinitializer */

//GPA_MFPH_PA14MFP
#define SYS_GPA_MFPH_PA14MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_I2C0_SCL   (0x2UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for I2C0_SCL   \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_SD_DAT0    (0x4UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for SD_DAT0  \hideinitializer */

//GPA_MFPH_PA15MFP
#define SYS_GPA_MFPH_PA15MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_I2C0_SDA   (0x2UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for I2C0_SDA   \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_SD_DAT1    (0x4UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for SD_DAT1   \hideinitializer */

//GPB_MFPL_PB0MFP
#define SYS_GPB_MFPL_PB0MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_I2C0_SCL       (0x2UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for I2C0_SCL    \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_UART0_TXD      (0x3UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for UART0_TXD     \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_SD_DAT2        (0x4UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for SD_DAT2     \hideinitializer */

//GPB_MFPL_PB1MFP
#define SYS_GPB_MFPL_PB1MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_I2C0_SDA        (0x2UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for I2C0_SDA    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_UART0_RXD           (0x3UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for UART0_RXD     \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_SD_DAT3         (0x4UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for SD_DAT3     \hideinitializer */

//GPB_MFPL_PB2MFP
#define SYS_GPB_MFPL_PB2MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_SPI0_SS        (0x1UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for SPI0_SS    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_CLOCK_VIEW     (0x2UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for CLOCK_VIEW     \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_SD_CMD         (0x4UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for SD_CMD     \hideinitializer */

//GPB_MFPL_PB3MFP
#define SYS_GPB_MFPL_PB3MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_SPI0_CLK       (0x1UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for SPI0_CLK    \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_SD_CLK         (0x4UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for SD_CLK     \hideinitializer */

//GPB_MFPL_PB4MFP
#define SYS_GPB_MFPL_PB4MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_SPI0_MOSI        (0x1UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for SPI0_MOSI    \hideinitializer */

//GPB_MFPL_PB5MFP
#define SYS_GPB_MFPL_PB5MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_SPI0_MISO            (0x1UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for SPI0_MISO    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_SD_nCD           (0x4UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for SD_nCD     \hideinitializer */

//GPB_MFPL_PB6MFP
#define SYS_GPB_MFPL_PB6MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_UART1_TXD      (0x3UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for UART1_TXD      \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_SD_DAT0         (0x4UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for SD_DAT0       \hideinitializer */

//GPB_MFPL_PB7MFP
#define SYS_GPB_MFPL_PB7MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_UART1_RXD       (0x3UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for UART1_RXD     \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_SD_DAT1         (0x4UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for SD_DAT1    \hideinitializer */

//GPB_MFPH_PB8MFP
#define SYS_GPB_MFPH_PB8MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_USBH_PWEN       (0x1UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for USBH_PWEN     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_TM1_CNT_OUT     (0x2UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for TM1_CNT_OUT    \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_UART1_nCTS          (0x3UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for UART1_nCTS     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_SD_DAT2         (0x4UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for SD_DAT2    \hideinitializer */

//GPB_MFPH_PB9MFP
#define SYS_GPB_MFPH_PB9MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for GPIO    \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_USBH_OVD        (0x1UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for USBH_OVD    \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_TM1_EXT         (0x2UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for TM1_EXT     \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_UART1_nRTS      (0x3UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for UART1_nRTS      \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_SD_DAT3         (0x4UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for SD_DAT3     \hideinitializer */

//GPB_MFPH_PB10MFP
#define SYS_GPB_MFPH_PB10MFP_GPIO               (0x0UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_SPI1_SS            (0x1UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for SPI1_SS  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_I2C1_SCL       (0x2UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for I2C1_SCL   \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_UART2_TXD      (0x3UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for UART2_TXD  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_PWM_CH0          (0x4UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for PWM_CH0   \hideinitializer */

//GPB_MFPH_PB11MFP
#define SYS_GPB_MFPH_PB11MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_SPI1_CLK           (0x1UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for SPI1_CLK   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_I2C1_SDA       (0x2UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for I2C1_SDA  \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_UART2_RXD      (0x3UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for UART2_RXD   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_PWM_CH1        (0x4UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for PWM_CH1   \hideinitializer */

//GPB_MFPH_PB12MFP
#define SYS_GPB_MFPH_PB12MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_SPI1_MOSI      (0x1UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for SPI1_MOSI   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_USBH1_DP               (0x2UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for USBH1_DP  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_UART2_nCTS     (0x3UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for UART2_nCTS   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_PWM_CH2        (0x4UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for PWM_CH3     \hideinitializer */

//GPB_MFPH_PB13MFP
#define SYS_GPB_MFPH_PB13MFP_GPIO               (0x0UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_SPI1_MISO      (0x1UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for SPI1_MISO    \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_USBH1_DM       (0x2UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for USBH1_DM   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_UART2_nRTS     (0x3UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for UART2_nRTS   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_PWM_CH3        (0x4UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for PWM_CH3    \hideinitializer */

//GPB_MFPH_PB14MFP
#define SYS_GPB_MFPH_PB14MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_USBH1_DP       (0x1UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for USBH1_DP   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_I2C1_SCL       (0x2UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for I2C1_SCL    \hideinitializer */

//GPB_MFPH_PB15MFP
#define SYS_GPB_MFPH_PB15MFP_GPIO           (0x0UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_USBH1_DM       (0x1UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for USBH1_DM  \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_I2C1_SDA       (0x2UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for I2C1_SDA  \hideinitializer */

//GPC_MFPL_PC0MFP
#define SYS_GPC_MFPL_PC0MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_SD_CMD          (0x1UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for SD_CMD    \hideinitializer */

//GPC_MFPL_PC1MFP
#define SYS_GPC_MFPL_PC1MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_SD_CLK          (0x1UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for SD_CLK     \hideinitializer */

//GPC_MFPL_PC2MFP
#define SYS_GPC_MFPL_PC2MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_SD_nCD          (0x1UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for SD_nCD    \hideinitializer */

//GPC_MFPL_PC3MFP
#define SYS_GPC_MFPL_PC3MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for GPIO     \hideinitializer */

//GPC_MFPL_PC4MFP
#define SYS_GPC_MFPL_PC4MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_SD_DAT0           (0x1UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for SD_DAT0    \hideinitializer */

//GPC_MFPL_PC5MFP
#define SYS_GPC_MFPL_PC5MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_SD_DAT1         (0x1UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for SD_DAT1    \hideinitializer */

//GPC_MFPL_PC6MFP
#define SYS_GPC_MFPL_PC6MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_SD_DAT2         (0x1UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for SD_DAT2    \hideinitializer */

//GPC_MFPL_PC7MFP
#define SYS_GPC_MFPL_PC7MFP_GPIO            (0x0UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_SD_DAT3         (0x1UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for SD_DAT3    \hideinitializer */

//GPC_MFPL_PC8MFP
#define SYS_GPC_MFPH_PC8MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC8MFP_Pos)           /*!< GPC_MFPH PC8 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_I2S_MCLK        (0x1UL<<SYS_GPC_MFPH_PC8MFP_Pos)           /*!< GPC_MFPH PC8 setting for I2S_MCLK    \hideinitializer */

//GPC_MFPH_PC9MFP
#define SYS_GPC_MFPH_PC9MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_I2S_DIN         (0x1UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for I2S_DIN    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_TM2_CNT_OUT     (0x2UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for TM2_CNT_OUT    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_PWM_CH0         (0x3UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for PWM_CH0    \hideinitializer */


//GPC_MFPH_PC10MFP
#define SYS_GPC_MFPH_PC10MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_I2S_DOUT       (0x1UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for I2S_DOUT   \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_TM2_EXT        (0x2UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for TM2_EXT  \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_PWM_CH1          (0x3UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for PWM_CH1      \hideinitializer */

//GPC_MFPH_PC11MFP
#define SYS_GPC_MFPH_PC11MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for GPIO \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_I2S_LRCLK      (0x1UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for I2S_LRCLK \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_TM3_CNT_OUT    (0x2UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for TM3_CNT_OUT \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_PWM_CH2        (0x3UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for PWM_CH2 \hideinitializer */

//GPC_MFPH_PC12MFP
#define SYS_GPC_MFPH_PC12MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_I2S_BCLK       (0x1UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for I2S_BCLK   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_TM3_EXT        (0x2UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for TM3_EXT    \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_PWM_CH3        (0x3UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for PWM_CH3  \hideinitializer */

//GPC_MFPH_PC13MFP
#define SYS_GPC_MFPH_PC13MFP_GPIO           (0x0UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_USBH2_DP       (0x1UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for USBH2_DP   \hideinitializer */

//GPC_MFPH_PC14MFP
#define SYS_GPC_MFPH_PC14MFP_GPIO               (0x0UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_USBH2_DM           (0x1UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for USBH2_DM   \hideinitializer */

//GPD_MFPL_PD0MFP
#define SYS_GPD_MFPL_PD0MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_I2C0_SCL        (0x2UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for I2C0_SCL     \hideinitializer */

//GPD_MFPL_PD1MFP
#define SYS_GPD_MFPL_PD1MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_I2C0_SDA        (0x2UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for I2C0_SDA     \hideinitializer */

//GPD_MFPL_PD2MFP
#define SYS_GPD_MFPL_PD2MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD2MFP_Pos)            /*!< GPD_MFPL PD2 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_MIC1_P          (0x1UL<<SYS_GPD_MFPL_PD2MFP_Pos)            /*!< GPD_MFPL PD2 setting for MIC1_P    \hideinitializer */

//GPD_MFPL_PD3MFP
#define SYS_GPD_MFPL_PD3MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD3MFP_Pos)            /*!< GPD_MFPL PD3 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_MIC1_N          (0x1UL<<SYS_GPD_MFPL_PD3MFP_Pos)            /*!< GPD_MFPL PD3 setting for MIC1_N   \hideinitializer */

//GPD_MFPL_PD4MFP
#define SYS_GPD_MFPL_PD4MFP_GPIO            (0x0UL<<SYS_GPD_MFPL_PD4MFP_Pos)            /*!< GPD_MFPL PD4 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_RLINEIN               (0x1UL<<SYS_GPD_MFPL_PD4MFP_Pos)              /*!< GPD_MFPL PD4 setting for Line In     \hideinitializer */

/*@}*/ /* end of group NUC505_SYS_EXPORTED_CONSTANTS */

/** @addtogroup NUC505_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

#define SYS_IS_CPU_RST()                    (SYS->RSTSTS & SYS_RSTSTS_CPURF_Msk)            /*!< This macro gets previous reset source is from CPU-Reset \hideinitializer */
#define SYS_IS_LVR_RST()                    (SYS->RSTSTS & SYS_RSTSTS_LVRF_Msk)             /*!< This macro gets previous reset source is from Low-Voltage-Reset \hideinitializer */
#define SYS_IS_POR_RST()                    (SYS->RSTSTS & SYS_RSTSTS_PORF_Msk)             /*!< This macro gets previous reset source is from Power-on Reset \hideinitializer */
#define SYS_IS_RSTPIN_RST()                 (SYS->RSTSTS & SYS_RSTSTS_PINRF_Msk)            /*!< This macro gets previous reset source is from reset pin reset \hideinitializer */
#define SYS_IS_WDT_RST()                    (SYS->RSTSTS & SYS_RSTSTS_WDTRF_Msk)            /*!< This macro gets previous reset source is from window watch dog  reset \hideinitializer */
#define SYS_CLEAR_RST_SOURCE(u32RstSts)     (SYS->RSTSTS = u32RstSts)                         /*!< This macro clears reset source. \hideinitializer */
#define SYS_DISABLE_LVR()                   (SYS->LVDCTL &= ~SYS_LVDCTL_LVREN_Msk)          /*!< This macro disables Low-Voltage Reset function \hideinitializer */
#define SYS_ENABLE_LVR()                    (SYS->LVDCTL |= SYS_LVDCTL_LVREN_Msk)           /*!< This macro enables Low-Voltage Reset function \hideinitializer */
#define SYS_DISABLE_POR()                   (SYS->LVDCTL |= SYS_LVDCTL_PORENB_Msk)          /*!< This macro disables Power-on Reset function \hideinitializer */
#define SYS_ENABLE_POR()                    (SYS->LVDCTL &= ~SYS_LVDCTL_PORENB_Msk)         /*!< This macro enables Power-on Reset function \hideinitializer */

#define SYS_ENABLE_WAKEUP(u32WakeUp)                    (SYS->WAKEUP = (SYS->WAKEUP&0x03FFF) | u32WakeUp)               /*!< This macro enables wake-up function by specified IP \hideinitializer */
#define SYS_DISABLE_WAKEUP(u32WakeUp)                   (SYS->WAKEUP = (SYS->WAKEUP&0x03FFF) & ~u32WakeUp)          /*!< This macro disables wake-up function by specified IP \hideinitializer */
#define SYS_GET_WAKEUP_SOURCE()                             ((SYS->WAKEUP & 0x3FFF0000)>>16)                                                /*!< This macro gets wake-up flag \hideinitializer */
#define SYS_CLEAR_WAKEUP_SOURCE(u32WakeUp)      (SYS->WAKEUP = (SYS->WAKEUP&0x03FFF) | (u32WakeUp<<16)) /*!< This macro clears wake-up flag by specified IP \hideinitializer */

#define SYS_ENABLE_NMI(u32Channel)                      (SYS->NMICTL = (SYS->NMICTL&0x0FF) | u32Channel)                /*!< This macro enables NMI interrupt channel by specified channel \hideinitializer */
#define SYS_DISABLE_NMI(u32Channel)                     (SYS->NMICTL = (SYS->NMICTL&0x0FF) & ~u32Channel)               /*!< This macro disables NMI interrupt channel by specified channel \hideinitializer */
#define SYS_GET_NMI_SOURCE(u32Channel)          ((SYS->NMICTL&0x000FF0000) & (u32Channel<<16))                  /*!< This macro gets NMI interrupt status by specified channel \hideinitializer */
#define SYS_CLEAR_NMI_SOURCE(u32Channel)            (SYS->NMICTL = (SYS->NMICTL&0x0FF) | (u32Channel<<16))  /*!< This macro clears NMI interrupt status by specified channel \hideinitializer */

#define SYS_ENABLE_CPU_AHB_HIGH_PRI()                   (SYS->AHBCTL = SYS->AHBCTL | SYS_AHBCTL_CPUHPRI_Msk)        /*!< This macro raise CPU priority to the highest priority as interrupt occurrence \hideinitializer */
#define SYS_DISABLE_CPU_AHB_HIGH_PRI()              (SYS->AHBCTL = SYS->AHBCTL & ~SYS_AHBCTL_CPUHPRI_Msk)       /*!< This macro set CPU priority to the lowest priority \hideinitializer */
#define SYS_CLEAR_CPU_HIGH_PRI_STATUS()             (SYS->AHBCTL = SYS->AHBCTL | SYS_AHBCTL_PRISTS_Msk)
/*!< This macro clear the highest priority status of CPU as the priority of CPU has been raised to the highest priority \hideinitializer */
#define SYS_AHB_ARBITRATION_MODE(u32PriSelect)  (SYS->AHBCTL = SYS->AHBCTL | (u32PriSelect & SYS_AHBCTL_PRISEL_Msk))
/*!< This macro set AHB priority strategy  \hideinitializer */

#define SYS_GET_REMAP_ADDR()                                        (SYS->RVMPADDR)                                                     /*!< This macro gets physical address that remap to 0 \hideinitializer */
#define SYS_GET_REMAP_LEN()                                         (SYS->RVMPLEN>>24)                                              /*!< This macro gets the length that remap to 0 \hideinitializer */

#define SYS_SET_RST_DEBOUNCE(u32RstDebounce)        (SYS->RSTDBCNT = u32RstDebounce)                    /*!< This macro gets physical address that remap to 0 \hideinitializer */
#define SYS_ENABLE_RST_DEBOUNCE()                               (SYS->RSTDBEN = SYS_RSTDBEN_RSTDBEN_Msk)    /*!< This macro gets physical address that remap to 0 \hideinitializer */
#define SYS_DISABLE_RST_DEBOUNCE()                          (SYS->RSTDBEN = 0)                                              /*!< This macro gets physical address that remap to 0 \hideinitializer */
#define SYS_SET_EMBEDDED_SPIFLASH_PULL(x)               (SYS->EPADPUEN = x)                                             /*!< This macro sets embedded SPI Flash pull up control \hideinitializer */


void SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_ReadPDID(void);
void SYS_ResetChip(void);
void SYS_ResetCPU(void);
void SYS_ResetModule(uint32_t u32ModuleIndex);
uint32_t SYS_GetResetSrc(void);
void SYS_ClearResetSrc(uint32_t u32Src);
void SYS_EnableLVD(uint32_t u32Enable, uint32_t u32Level);
void SYS_DisableLVD(void);
void SYS_BootSrc(uint32_t u32BootSrc);
void SYS_SharedPinDrivingStrangth(uint32_t u32Port, uint32_t u32Pin, uint32_t u32DrivingLevel);
void SYS_SetSharedPinType(uint32_t u32Port, uint32_t u32Pin, uint32_t u32InputType, uint32_t u32BufferType);
void SYS_SetDigitalPinInputType(uint32_t u32Port, uint32_t u32Pin, uint32_t u32BufferType);
void SYS_RemapPhysicalAddress(uint32_t u32Address, uint32_t u32Len);


/*@}*/ /* end of group NUC505_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_SYS_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__SYS_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
