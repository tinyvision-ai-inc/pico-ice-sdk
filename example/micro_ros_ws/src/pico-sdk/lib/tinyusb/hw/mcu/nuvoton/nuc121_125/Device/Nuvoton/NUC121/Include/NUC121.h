/**************************************************************************//**
 * @file     NUC121.h
 * @version  V3.00
 * @brief    NUC121/NUC125 Series Peripheral Access Layer Header File
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/**
  \mainpage NuMicro NUC121/NUC125 Series CMSIS BSP Driver Reference
  *
  * <b>Introduction</b>
  *
  * This user manual describes the usage of NUC121/NUC125 Series MCU device driver
  *
  * <b>Disclaimer</b>
  *
  * The Software is furnished "AS IS", without warranty as to performance or results, and
  * the entire risk as to performance or results is assumed by YOU. Nuvoton disclaims all
  * warranties, express, implied or otherwise, with regard to the Software, its use, or
  * operation, including without limitation any and all warranties of merchantability, fitness
  * for a particular purpose, and non-infringement of intellectual property rights.
  *
  * <b>Important Notice</b>
  *
  * Nuvoton Products are neither intended nor warranted for usage in systems or equipment,
  * any malfunction or failure of which may cause loss of human life, bodily injury or severe
  * property damage. Such applications are deemed, "Insecure Usage".
  *
  * Insecure usage includes, but is not limited to: equipment for surgical implementation,
  * atomic energy control instruments, airplane or spaceship instruments, the control or
  * operation of dynamic, brake or safety systems designed for vehicular use, traffic signal
  * instruments, all types of safety devices, and other applications intended to support or
  * sustain life.
  *
  * All Insecure Usage shall be made at customer's risk, and in the event that third parties
  * lay claims to Nuvoton as a result of customer's Insecure Usage, customer shall indemnify
  * the damages and liabilities thus incurred by Nuvoton.
  *
  * Please note that all data and specifications are subject to change without notice. All the
  * trademarks of products and companies mentioned in this datasheet belong to their respective
  * owners.
  *
  * <b>Copyright Notice</b>
  *
  * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
  */

#ifndef __NUC121_H__
#define __NUC121_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

/** @addtogroup MCU_CMSIS Device Definitions for CMSIS
  Interrupt Number Definition and Configurations for CMSIS
  @{
*/

/**
 * @details  Interrupt Number Definition. The maximum of 32 Specific Interrupts are possible.
 */

typedef enum IRQn
{
    /******  Cortex-M0 Processor Exceptions Numbers ***********************************************/
    NonMaskableInt_IRQn       = -14,    /*!< 2 Non Maskable Interrupt                             */
    HardFault_IRQn            = -13,    /*!< 3 Cortex-M0 Hard Fault Interrupt                     */
    SVCall_IRQn               = -5,     /*!< 11 Cortex-M0 SV Call Interrupt                       */
    PendSV_IRQn               = -2,     /*!< 14 Cortex-M0 Pend SV Interrupt                       */
    SysTick_IRQn              = -1,     /*!< 15 Cortex-M0 System Tick Interrupt                   */

    /******  ARMIKMCU Swift specific Interrupt Numbers ********************************************/
    BOD_IRQn                  = 0,      /*!< Brown-Out Low Voltage Detected Interrupt             */
    WDT_IRQn                  = 1,      /*!< Watch Dog Timer Interrupt                            */
    EINT024_IRQn              = 2,      /*!< EINT0, EINT2 and EINT4 Interrupt                     */
    EINT135_IRQn              = 3,      /*!< EINT1, EINT3 and EINT5 Interrupt                     */
    GPAB_IRQn                 = 4,      /*!< GPIO_P0P1 Interrupt                                  */
    GPCDEF_IRQn               = 5,      /*!< GPIO_P2P3P4P5 Interrupt                              */
    PWM0_IRQn                 = 6,      /*!< PWM0 Interrupt                                       */
    PWM1_IRQn                 = 7,      /*!< PWM1 Interrupt                                       */
    TMR0_IRQn                 = 8,      /*!< TIMER0 Interrupt                                     */
    TMR1_IRQn                 = 9,      /*!< TIMER1 Interrupt                                     */
    TMR2_IRQn                 = 10,     /*!< TIMER2 Interrupt                                     */
    TMR3_IRQn                 = 11,     /*!< TIMER3 Interrupt                                     */
    UART0_IRQn                = 12,     /*!< UART0 Interrupt                                      */
    //RESERVE0                  = 13,
    SPI0_IRQn                 = 14,     /*!< SPI0 Interrupt                                       */
    //RESERVE1                  = 15,
    //RESERVE2                  = 16,
    //RESERVE3                  = 17,
    I2C0_IRQn                 = 18,     /*!< I2C0 Interrupt                                       */
    I2C1_IRQn                 = 19,     /*!< I2C1 Interrupt                                       */
    BPWM0_IRQn                = 20,     /*!< BPWM0 Interrupt                                      */
    BPWM1_IRQn                = 21,     /*!< BPWM1 Interrupt                                      */
    USCI_IRQn                 = 22,     /*!< USCI0, USCI1 and USCI2 interrupt                     */
    USBD_IRQn                 = 23,     /*!< USB Device Interrupt                                 */
    //RESERVE6                  = 24,
    PWM_BRAKE_IRQn            = 25,     /*!< PWM Brake Interrupt                                  */
    PDMA_IRQn                 = 26,     /*!< PDMA Interrupt                                       */
    //RESERVE7                  = 27,
    PWRWU_IRQn                = 28,     /*!< Power Down Wake Up Interrupt                         */
    ADC_IRQn                  = 29,     /*!< ADC Interrupt                                        */
    CLKDIRC_IRQn              = 30,     /*!< Clock fail detect and IRC TRIM Interrupt             */
    //RESERVE8                  = 31,
} IRQn_Type;


/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT           0       /*!< armikcmu does not provide a MPU present or not       */
#define __NVIC_PRIO_BITS        2       /*!< armikcmu Supports 2 Bits for the Priority Levels     */
#define __Vendor_SysTickConfig  0       /*!< Set to 1 if different SysTick Config is used         */

/*@}*/ /* end of group MCU_CMSIS */


#include "core_cm0.h"                   /*!< Cortex-M0 processor and core peripherals             */
#include "system_NUC121.h"              /*!< NUC121 System                                        */

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
 * Initialize the system clock
 *
 * @param  None
 * @return None
 *
 * @brief  Setup the microcontroller system
 *         Initialize the PLL and update the SystemFrequency variable
 */
extern void SystemInit(void);


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/** @addtogroup REGISTER Control Register
  @{
*/

#include "adc_reg.h"
#include "bpwm_reg.h"
#include "clk_reg.h"
#include "fmc_reg.h"
#include "gpio_reg.h"
#include "i2c_reg.h"
#include "int_reg.h"
#include "pdma_reg.h"
#include "pwm_reg.h"
#include "spi_reg.h"
#include "sys_reg.h"
#include "timer_reg.h"
#include "uart_reg.h"
#include "ui2c_reg.h"
#include "uspi_reg.h"
#include "uuart_reg.h"
#include "usbd_reg.h"
#include "wdt_reg.h"
#include "wwdt_reg.h"

/**@}*/ /* end of REGISTER group */


/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/** @addtogroup PERIPHERAL_BASE Peripheral Memory Base
  Memory Mapped Structure for Series Peripheral
  @{
 */
/* Peripheral and SRAM base address */
#define FLASH_BASE          ((uint32_t)0x00000000)
#define SRAM_BASE           ((uint32_t)0x20000000)
#define AHB_BASE            ((uint32_t)0x50000000)
#define APB1_BASE           ((uint32_t)0x40000000)
#define APB2_BASE           ((uint32_t)0x40100000)

/* Peripheral memory map */
/* AHB */
#define SYS_BASE            (AHB_BASE       + 0x00000)                  /*!< System Global Controller Base Address            */
#define CLK_BASE            (AHB_BASE       + 0x00200)                  /*!< System Clock Controller Base Address             */
#define INT_BASE            (AHB_BASE       + 0x00300)                  /*!< Interrupt Source Controller Base Address         */
#define GPIO_BASE           (AHB_BASE       + 0x04000)                  /*!< GPIO Base Address                                */
#define PDMA_BASE           (AHB_BASE       + 0x08000)                  /*!< PDMA Base Address                                */
#define FMC_BASE            (AHB_BASE       + 0x0C000)                  /*!< Flash Memory Controller Base Address             */

#define PA_BASE             (GPIO_BASE               )                  /*!< GPIO PA Base Address                             */
#define PB_BASE             (GPIO_BASE      + 0x00040)                  /*!< GPIO PB Base Address                             */
#define PC_BASE             (GPIO_BASE      + 0x00080)                  /*!< GPIO PC Base Address                             */
#define PD_BASE             (GPIO_BASE      + 0x000C0)                  /*!< GPIO PD Base Address                             */
#define PE_BASE             (GPIO_BASE      + 0x00100)                  /*!< GPIO PE Base Address                             */
#define PF_BASE             (GPIO_BASE      + 0x00140)                  /*!< GPIO PF Base Address                             */
#define GPIO_DBCTL_BASE     (GPIO_BASE      + 0x00180)                  /*!< GPIO De-bounce Cycle Control Base Address        */
#define GPIO_PIN_DATA_BASE  (GPIO_BASE      + 0x00200)                  /*!< GPIO Pin Data Input/Output Control Base Address  */

/* APB1 */
#define WDT_BASE            (APB1_BASE      + 0x04000)                  /*!< Watch Dog Timer Base Address                     */
#define WWDT_BASE           (APB1_BASE      + 0x04100)                  /*!< Window Watch Dog Timer Base Address              */
#define TIMER0_BASE         (APB1_BASE      + 0x10000)                  /*!< Timer0 Base Address                              */
#define TIMER1_BASE         (APB1_BASE      + 0x10020)                  /*!< Timer1 Base Address                              */
#define I2C0_BASE           (APB1_BASE      + 0x20000)                  /*!< I2C0 Base Address                                */
#define SPI0_BASE           (APB1_BASE      + 0x30000)                  /*!< SPI0 Base Address                                */
#define BPWM0_BASE          (APB1_BASE      + 0x40000)                  /*!< BPWM0 Base Address                               */
#define PWM0_BASE           (APB1_BASE      + 0x44000)                  /*!< PWM0 Base Address                                */
#define UART0_BASE          (APB1_BASE      + 0x50000)                  /*!< UART0 Base Address                               */
#define USBD_BASE           (APB1_BASE      + 0x60000)                  /*!< USB Device Base Address                          */
#define USCI0_BASE          (APB1_BASE      + 0x70000)
#define ADC_BASE            (APB1_BASE      + 0xE0000)                  /*!< ADC Base Address                                 */

/* APB2 */
#define TIMER2_BASE         (APB2_BASE      + 0x10000)                  /*!< Timer2 Base Address                              */
#define TIMER3_BASE         (APB2_BASE      + 0x10020)                  /*!< Timer3 Base Address                              */
#define I2C1_BASE           (APB2_BASE      + 0x20000)                  /*!< I2C1 Base Address                                */
#define BPWM1_BASE          (APB2_BASE      + 0x40000)                  /*!< BPWM1 Base Address                               */
#define PWM1_BASE           (APB2_BASE      + 0x44000)                  /*!< PWM1 Base Address                                */

/**@}*/ /* end of group PERIPHERAL_BASE */


/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

/** @addtogroup PMODULE Peripheral Pointer
  The Declaration of Peripheral Pointer
  @{
 */
#define ADC                 ((ADC_T *) ADC_BASE)                        /*!< ADC Configuration Struct                         */

#define BPWM0               ((BPWM_T *) BPWM0_BASE)                     /*!< BPWM0 Configuration Struct                       */
#define BPWM1               ((BPWM_T *) BPWM1_BASE)                     /*!< BPWM1 Configuration Struct                       */

#define CLK                 ((CLK_T *) CLK_BASE)                        /*!< System Clock Controller Configuration Struct     */

#define FMC                 ((FMC_T *) FMC_BASE)                        /*!< Flash Memory Controller */

#define GPIO                ((GPIO_DBCTL_T *) GPIO_DBCTL_BASE)          /*!< Interrupt De-bounce Cycle Control Configuration Struct */
#define PA                  ((GPIO_T *) PA_BASE)                        /*!< GPIO PORTA Configuration Struct                        */
#define PB                  ((GPIO_T *) PB_BASE)                        /*!< GPIO PORTB Configuration Struct                        */
#define PC                  ((GPIO_T *) PC_BASE)                        /*!< GPIO PORTC Configuration Struct                        */
#define PD                  ((GPIO_T *) PD_BASE)                        /*!< GPIO PORTD Configuration Struct                        */
#define PE                  ((GPIO_T *) PE_BASE)                        /*!< GPIO PORTE Configuration Struct                        */
#define PF                  ((GPIO_T *) PF_BASE)                        /*!< GPIO PORTF Configuration Struct                        */

#define I2C0                ((I2C_T *) I2C0_BASE)                       /*!< I2C0 Configuration Struct                        */
#define I2C1                ((I2C_T *) I2C1_BASE)                       /*!< I2C1 Configuration Struct                        */

#define INT                 ((INT_T *) INT_BASE)                        /*!< Interrupt Source Controller Configuration Struct */

#define PDMA                ((PDMA_T *) PDMA_BASE)                      /*!< PDMA Configuration Struct                        */

#define PWM0                ((PWM_T *)  PWM0_BASE)                      /*!< PWM0 Configuration Struct                        */
#define PWM1                ((PWM_T *)  PWM1_BASE)                      /*!< PWM1 Configuration Struct                        */

#define SPI0                ((SPI_T *) SPI0_BASE)                       /*!< SPI0 Configuration Struct                        */

#define SYS                 ((SYS_T *) SYS_BASE)                        /*!< System Global Controller Configuration Struct    */

#define TIMER0              ((TIMER_T *) TIMER0_BASE)                   /*!< TIMER0 Configuration Struct                      */
#define TIMER1              ((TIMER_T *) TIMER1_BASE)                   /*!< TIMER1 Configuration Struct                      */
#define TIMER2              ((TIMER_T *) TIMER2_BASE)                   /*!< TIMER2 Configuration Struct                      */
#define TIMER3              ((TIMER_T *) TIMER3_BASE)                   /*!< TIMER3 Configuration Struct                      */

#define UART0               ((UART_T *) UART0_BASE)                     /*!< UART0 Configuration Struct                       */

#define UI2C0               ((UI2C_T *) USCI0_BASE)                     /*!< UI2C0 Configuration Struct                       */
#define USPI0               ((USPI_T *) USCI0_BASE)                     /*!< USPI0 Configuration Struct                       */
#define UUART0              ((UUART_T *) USCI0_BASE)                    /*!< UUART0 Configuration Struct                      */

#define USBD                ((USBD_T *) USBD_BASE)                      /*!< USB Device Configuration Struct                  */

#define WDT                 ((WDT_T *) WDT_BASE)                        /*!< Watch Dog Timer Configuration Struct             */

#define WWDT                ((WWDT_T *) WWDT_BASE)                      /*!< Window Watch Dog Timer Configuration Struct      */

/**@}*/ /* end of group PMODULE */
/**@}*/ /* end of group REGISTER */


//=============================================================================
typedef volatile unsigned char  vu8;
typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;

#define M8(adr)  (*((vu8  *) (adr)))
#define M16(adr) (*((vu16 *) (adr)))
#define M32(adr) (*((vu32 *) (adr)))

#define outpw(port,value)   (*((volatile unsigned int *)(port))=(value))
#define inpw(port)          ((*((volatile unsigned int *)(port))))
#define outpb(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inpb(port)          ((*((volatile unsigned char *)(port))))
#define outps(port,value)   (*((volatile unsigned short *)(port))=(value))
#define inps(port)          ((*((volatile unsigned short *)(port))))

#define outp32(port,value)  (*((volatile unsigned int *)(port))=(value))
#define inp32(port)         ((*((volatile unsigned int *)(port))))
#define outp8(port,value)   (*((volatile unsigned char *)(port))=(value))
#define inp8(port)          ((*((volatile unsigned char *)(port))))
#define outp16(port,value)  (*((volatile unsigned short *)(port))=(value))
#define inp16(port)         ((*((volatile unsigned short *)(port))))

#define E_SUCCESS   0
#ifndef NULL
    #define NULL    0
#endif

#define TRUE        1
#define FALSE       0

#define ENABLE      1
#define DISABLE     0

/* Bit Mask Definitions */
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

/* Byte Mask Definitions */
#define BYTE0_Msk               (0x000000FF)
#define BYTE1_Msk               (0x0000FF00)
#define BYTE2_Msk               (0x00FF0000)
#define BYTE3_Msk               (0xFF000000)

#define _GET_BYTE0(u32Param)    (((u32Param) & BYTE0_Msk)      )  /*!< Extract Byte 0 (Bit  0~ 7) from parameter u32Param */
#define _GET_BYTE1(u32Param)    (((u32Param) & BYTE1_Msk) >>  8)  /*!< Extract Byte 1 (Bit  8~15) from parameter u32Param */
#define _GET_BYTE2(u32Param)    (((u32Param) & BYTE2_Msk) >> 16)  /*!< Extract Byte 2 (Bit 16~23) from parameter u32Param */
#define _GET_BYTE3(u32Param)    (((u32Param) & BYTE3_Msk) >> 24)  /*!< Extract Byte 3 (Bit 24~31) from parameter u32Param */


/******************************************************************************/
/*                         Peripheral header files                            */
/******************************************************************************/
#include "adc.h"
#include "bpwm.h"
#include "clk.h"
#include "fmc.h"
#include "gpio.h"
#include "i2c.h"
#include "pdma.h"
#include "pwm.h"
#include "spi_i2s.h"
#include "sys.h"
#include "timer.h"
#include "uart.h"
#include "usbd.h"
#include "usci_i2c.h"
#include "usci_spi.h"
#include "usci_uart.h"
#include "wdt.h"
#include "wwdt.h"

#endif /*__NUC121_H__*/
