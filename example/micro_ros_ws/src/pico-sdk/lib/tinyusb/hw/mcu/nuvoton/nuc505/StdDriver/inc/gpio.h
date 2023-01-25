/**************************************************************************//**
 * @file     gpio.h
 * @version  V1.00
 * $Revision: 11 $
 * $Date: 14/05/29 1:13p $
 * @brief    NUC505 GPIO driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup NUC505_GPIO_EXPORTED_CONSTANTS GPIO Exported Constants
  @{
*/
#define GPIO_PIN_MAX    16   /*!< Specify Maximum Pins of Each GPIO Port */

/*---------------------------------------------------------------------------------------------------------*/
/*  MODE Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_MODE_INPUT              0x0UL           /*!< Input Mode */
#define GPIO_MODE_OUTPUT             0x1UL           /*!< Output Mode */

/*---------------------------------------------------------------------------------------------------------*/
/*  PULL Mode Constant Definitions                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_PULL_DISABLE              0x0UL           /*!< Input Pull Up/Down Disable */
#define GPIO_PULL_UP_EN              0x1UL           /*!< Input Pull Up Enable */
#define GPIO_PULL_DOWN_EN             0x2UL           /*!< Input Pull Down Enable */

/*---------------------------------------------------------------------------------------------------------*/
/*  GPIO Interrupt Type Constant Definitions                                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INT_RISING             0x00010000UL    /*!< Interrupt enable by Input Rising Edge */
#define GPIO_INT_FALLING            0x00000001UL    /*!< Interrupt enable by Input Falling Edge */
#define GPIO_INT_BOTH_EDGE          0x00010001UL    /*!< Interrupt enable by both Rising Edge and Falling Edge */

/*---------------------------------------------------------------------------------------------------------*/
/*  DBCTL Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_DBCTL_EINT0_DBEN_MASK        0x00000001UL /*!< Enable EINT0 debounce sampling */
#define GPIO_DBCTL_EINT1_DBEN_MASK        0x00000002UL /*!< Enable EINT1 debounce sampling */
#define GPIO_DBCTL_EINT2_DBEN_MASK        0x00000004UL /*!< Enable EINT2 debounce sampling */
#define GPIO_DBCTL_EINT3_DBEN_MASK        0x00000008UL /*!< Enable EINT3 debounce sampling */

#define GPIO_DBCTL_DBCLKSEL_1        0x00000000UL /*!< DBCTL setting for sampling cycle = 1 clocks */
#define GPIO_DBCTL_DBCLKSEL_2        0x00000001UL /*!< DBCTL setting for sampling cycle = 2 clocks */
#define GPIO_DBCTL_DBCLKSEL_4        0x00000002UL /*!< DBCTL setting for sampling cycle = 4 clocks */
#define GPIO_DBCTL_DBCLKSEL_8        0x00000003UL /*!< DBCTL setting for sampling cycle = 8 clocks */
#define GPIO_DBCTL_DBCLKSEL_16       0x00000004UL /*!< DBCTL setting for sampling cycle = 16 clocks */
#define GPIO_DBCTL_DBCLKSEL_32       0x00000005UL /*!< DBCTL setting for sampling cycle = 32 clocks */
#define GPIO_DBCTL_DBCLKSEL_64       0x00000006UL /*!< DBCTL setting for sampling cycle = 64 clocks */
#define GPIO_DBCTL_DBCLKSEL_128      0x00000007UL /*!< DBCTL setting for sampling cycle = 128 clocks */
#define GPIO_DBCTL_DBCLKSEL_256      0x00000008UL /*!< DBCTL setting for sampling cycle = 256 clocks */
#define GPIO_DBCTL_DBCLKSEL_512      0x00000009UL /*!< DBCTL setting for sampling cycle = 512 clocks */
#define GPIO_DBCTL_DBCLKSEL_1024     0x0000000AUL /*!< DBCTL setting for sampling cycle = 1024 clocks */
#define GPIO_DBCTL_DBCLKSEL_2048     0x0000000BUL /*!< DBCTL setting for sampling cycle = 2048 clocks */
#define GPIO_DBCTL_DBCLKSEL_4096     0x0000000CUL /*!< DBCTL setting for sampling cycle = 4096 clocks */
#define GPIO_DBCTL_DBCLKSEL_8192     0x0000000DUL /*!< DBCTL setting for sampling cycle = 8192 clocks */
#define GPIO_DBCTL_DBCLKSEL_16384    0x0000000EUL /*!< DBCTL setting for sampling cycle = 16384 clocks */
#define GPIO_DBCTL_DBCLKSEL_32768    0x0000000FUL /*!< DBCTL setting for sampling cycle = 32768 clocks */

/*---------------------------------------------------------------------------------------------------------*/
/*  INTSRCGP Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INTSRCGP_EINT0        0x00000000UL /*!< Selection input pins to EINT0 interrupt source */
#define GPIO_INTSRCGP_EINT1        0x00000001UL /*!< Selection input pins to EINT1 interrupt source */
#define GPIO_INTSRCGP_EINT2        0x00000002UL /*!< Selection input pins to EINT2 interrupt source */
#define GPIO_INTSRCGP_EINT3        0x00000003UL /*!< Selection input pins to EINT3 interrupt source */

/*---------------------------------------------------------------------------------------------------------*/
/*  INTCTL Constant Definitions                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define GPIO_INTCTL_LEVEL_SENSITIVE        0x00000100UL /*!< Selection interrupt request source control to level*/

#define GPIO_INTCTL_EINT0_INTLHEN_MASK        0x00000001UL /*!< Enable active EINT0 interrupt to latch the input values */
#define GPIO_INTCTL_EINT1_INTLHEN_MASK        0x00000002UL /*!< Enable active EINT1 interrupt to latch the input values */
#define GPIO_INTCTL_EINT2_INTLHEN_MASK        0x00000004UL /*!< Enable active EINT2 interrupt to latch the input values */
#define GPIO_INTCTL_EINT3_INTLHEN_MASK        0x00000008UL /*!< Enable active EINT3 interrupt to latch the input values */

#define GPIO_INTCTL_EINT0_WKEN_MASK        0x00000010UL /*!< Enable EINT0 wake up the chip from power down mode */
#define GPIO_INTCTL_EINT1_WKEN_MASK        0x00000020UL /*!< Enable EINT1 wake up the chip from power down mode */
#define GPIO_INTCTL_EINT2_WKEN_MASK        0x00000040UL /*!< Enable EINT2 wake up the chip from power down mode */
#define GPIO_INTCTL_EINT3_WKEN_MASK        0x00000080UL /*!< Enable EINT3 wake up the chip from power down mode */

/** Define GPIO Pin Data Input/Output. It could be used to control each I/O pin by pin address mapping.
 *  Example 1:
 *
 *      PA0_DOUT = 1;
 *
 *  It is used to set PA0 to high;
 *
 *  Example 2:
 *
 *      if (PA0_PIN)
 *          PA0_DOUT = 0;
 *
 *  If PA0 pin status is high, then set PA0 data output to low.
 */
#define MEM_ADDR(address)  *((volatile unsigned long *) (address))
#define BITBAND(address,bitnum) ((address & 0xF0000000)+0x02000000+((address & 0xFFFFF)<<5)+(bitnum<<2))

#define GPIOA_DOUT             (GPIOA_BASE + 0x08)
#define GPIOB_DOUT             (GPIOB_BASE + 0x08)
#define GPIOC_DOUT             (GPIOC_BASE + 0x08)
#define GPIOD_DOUT             (GPIOD_BASE + 0x08)
#define GPIOA_PIN             (GPIOA_BASE + 0x0C)
#define GPIOB_PIN             (GPIOB_BASE + 0x0C)
#define GPIOC_PIN             (GPIOC_BASE + 0x0C)
#define GPIOD_PIN             (GPIOD_BASE + 0x0C)
#define PA0_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 0))  /*!< Specify PA0 Pin Data Output */
#define PA1_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 1))  /*!< Specify PA1 Pin Data Output */
#define PA2_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 2))  /*!< Specify PA2 Pin Data Output */
#define PA3_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 3))  /*!< Specify PA3 Pin Data Output */
#define PA4_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 4))  /*!< Specify PA4 Pin Data Output */
#define PA5_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 5))  /*!< Specify PA5 Pin Data Output */
#define PA6_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 6))  /*!< Specify PA6 Pin Data Output */
#define PA7_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 7))  /*!< Specify PA7 Pin Data Output */
#define PA8_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 8))  /*!< Specify PA8 Pin Data Output */
#define PA9_DOUT             MEM_ADDR(BITBAND(GPIOA_DOUT, 9))  /*!< Specify PA9 Pin Data Output */
#define PA10_DOUT            MEM_ADDR(BITBAND(GPIOA_DOUT, 10)) /*!< Specify PA10 Pin Data Output */
#define PA11_DOUT            MEM_ADDR(BITBAND(GPIOA_DOUT, 11)) /*!< Specify PA11 Pin Data Output */
#define PA12_DOUT            MEM_ADDR(BITBAND(GPIOA_DOUT, 12)) /*!< Specify PA12 Pin Data Output */
#define PA13_DOUT            MEM_ADDR(BITBAND(GPIOA_DOUT, 13)) /*!< Specify PA13 Pin Data Output */
#define PA14_DOUT            MEM_ADDR(BITBAND(GPIOA_DOUT, 14)) /*!< Specify PA14 Pin Data Output */
#define PA15_DOUT            MEM_ADDR(BITBAND(GPIOA_DOUT, 15)) /*!< Specify PA15 Pin Data Output */

#define PB0_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 0))  /*!< Specify PB0 Pin Data Output */
#define PB1_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 1))  /*!< Specify PB1 Pin Data Output */
#define PB2_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 2))  /*!< Specify PB2 Pin Data Output */
#define PB3_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 3))  /*!< Specify PB3 Pin Data Output */
#define PB4_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 4))  /*!< Specify PB4 Pin Data Output */
#define PB5_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 5))  /*!< Specify PB5 Pin Data Output */
#define PB6_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 6))  /*!< Specify PB6 Pin Data Output */
#define PB7_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 7))  /*!< Specify PB7 Pin Data Output */
#define PB8_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 8))  /*!< Specify PB8 Pin Data Output */
#define PB9_DOUT             MEM_ADDR(BITBAND(GPIOB_DOUT, 9))  /*!< Specify PB9 Pin Data Output */
#define PB10_DOUT            MEM_ADDR(BITBAND(GPIOB_DOUT, 10)) /*!< Specify PB10 Pin Data Output */
#define PB11_DOUT            MEM_ADDR(BITBAND(GPIOB_DOUT, 11)) /*!< Specify PB11 Pin Data Output */
#define PB12_DOUT            MEM_ADDR(BITBAND(GPIOB_DOUT, 12)) /*!< Specify PB12 Pin Data Output */
#define PB13_DOUT            MEM_ADDR(BITBAND(GPIOB_DOUT, 13)) /*!< Specify PB13 Pin Data Output */
#define PB14_DOUT            MEM_ADDR(BITBAND(GPIOB_DOUT, 14)) /*!< Specify PB14 Pin Data Output */
#define PB15_DOUT            MEM_ADDR(BITBAND(GPIOB_DOUT, 15)) /*!< Specify PB15 Pin Data Output */

#define PC0_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 0))  /*!< Specify PC0 Pin Data Output */
#define PC1_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 1))  /*!< Specify PC1 Pin Data Output */
#define PC2_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 2))  /*!< Specify PC2 Pin Data Output */
#define PC3_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 3))  /*!< Specify PC3 Pin Data Output */
#define PC4_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 4))  /*!< Specify PC4 Pin Data Output */
#define PC5_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 5))  /*!< Specify PC5 Pin Data Output */
#define PC6_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 6))  /*!< Specify PC6 Pin Data Output */
#define PC7_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 7))  /*!< Specify PC7 Pin Data Output */
#define PC8_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 8))  /*!< Specify PC8 Pin Data Output */
#define PC9_DOUT             MEM_ADDR(BITBAND(GPIOC_DOUT, 9))  /*!< Specify PC9 Pin Data Output */
#define PC10_DOUT            MEM_ADDR(BITBAND(GPIOC_DOUT, 10)) /*!< Specify PC10 Pin Data Output */
#define PC11_DOUT            MEM_ADDR(BITBAND(GPIOC_DOUT, 11)) /*!< Specify PC11 Pin Data Output */
#define PC12_DOUT            MEM_ADDR(BITBAND(GPIOC_DOUT, 12)) /*!< Specify PC12 Pin Data Output */
#define PC13_DOUT            MEM_ADDR(BITBAND(GPIOC_DOUT, 13)) /*!< Specify PC13 Pin Data Output */
#define PC14_DOUT            MEM_ADDR(BITBAND(GPIOC_DOUT, 14)) /*!< Specify PC14 Pin Data Output */

#define PD0_DOUT             MEM_ADDR(BITBAND(GPIOD_DOUT, 0))  /*!< Specify PD0 Pin Data Output */
#define PD1_DOUT             MEM_ADDR(BITBAND(GPIOD_DOUT, 1))  /*!< Specify PD1 Pin Data Output */
#define PD2_DOUT             MEM_ADDR(BITBAND(GPIOD_DOUT, 2))  /*!< Specify PD2 Pin Data Output */
#define PD3_DOUT             MEM_ADDR(BITBAND(GPIOD_DOUT, 3))  /*!< Specify PD3 Pin Data Output */
#define PD4_DOUT             MEM_ADDR(BITBAND(GPIOD_DOUT, 4))  /*!< Specify PD4 Pin Data Output */

#define PA0_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 0))  /*!< Specify PA0 Pin Data Input */
#define PA1_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 1))  /*!< Specify PA1 Pin Data Input */
#define PA2_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 2))  /*!< Specify PA2 Pin Data Input */
#define PA3_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 3))  /*!< Specify PA3 Pin Data Input */
#define PA4_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 4))  /*!< Specify PA4 Pin Data Input */
#define PA5_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 5))  /*!< Specify PA5 Pin Data Input */
#define PA6_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 6))  /*!< Specify PA6 Pin Data Input */
#define PA7_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 7))  /*!< Specify PA7 Pin Data Input */
#define PA8_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 8))  /*!< Specify PA8 Pin Data Input */
#define PA9_PIN             MEM_ADDR(BITBAND(GPIOA_PIN, 9))  /*!< Specify PA9 Pin Data Input */
#define PA10_PIN            MEM_ADDR(BITBAND(GPIOA_PIN, 10)) /*!< Specify PA10 Pin Data Input */
#define PA11_PIN            MEM_ADDR(BITBAND(GPIOA_PIN, 11)) /*!< Specify PA11 Pin Data Input */
#define PA12_PIN            MEM_ADDR(BITBAND(GPIOA_PIN, 12)) /*!< Specify PA12 Pin Data Input */
#define PA13_PIN            MEM_ADDR(BITBAND(GPIOA_PIN, 13)) /*!< Specify PA13 Pin Data Input */
#define PA14_PIN            MEM_ADDR(BITBAND(GPIOA_PIN, 14)) /*!< Specify PA14 Pin Data Input */
#define PA15_PIN            MEM_ADDR(BITBAND(GPIOA_PIN, 15)) /*!< Specify PA15 Pin Data Input */

#define PB0_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 0))  /*!< Specify PB0 Pin Data Input */
#define PB1_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 1))  /*!< Specify PB1 Pin Data Input */
#define PB2_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 2))  /*!< Specify PB2 Pin Data Input */
#define PB3_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 3))  /*!< Specify PB3 Pin Data Input */
#define PB4_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 4))  /*!< Specify PB4 Pin Data Input */
#define PB5_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 5))  /*!< Specify PB5 Pin Data Input */
#define PB6_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 6))  /*!< Specify PB6 Pin Data Input */
#define PB7_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 7))  /*!< Specify PB7 Pin Data Input */
#define PB8_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 8))  /*!< Specify PB8 Pin Data Input */
#define PB9_PIN             MEM_ADDR(BITBAND(GPIOB_PIN, 9))  /*!< Specify PB9 Pin Data Input */
#define PB10_PIN            MEM_ADDR(BITBAND(GPIOB_PIN, 10)) /*!< Specify PB10 Pin Data Input */
#define PB11_PIN            MEM_ADDR(BITBAND(GPIOB_PIN, 11)) /*!< Specify PB11 Pin Data Input */
#define PB12_PIN            MEM_ADDR(BITBAND(GPIOB_PIN, 12)) /*!< Specify PB12 Pin Data Input */
#define PB13_PIN            MEM_ADDR(BITBAND(GPIOB_PIN, 13)) /*!< Specify PB13 Pin Data Input */
#define PB14_PIN            MEM_ADDR(BITBAND(GPIOB_PIN, 14)) /*!< Specify PB14 Pin Data Input */
#define PB15_PIN            MEM_ADDR(BITBAND(GPIOB_PIN, 15)) /*!< Specify PB15 Pin Data Input */

#define PC0_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 0))  /*!< Specify PC0 Pin Data Input */
#define PC1_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 1))  /*!< Specify PC1 Pin Data Input */
#define PC2_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 2))  /*!< Specify PC2 Pin Data Input */
#define PC3_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 3))  /*!< Specify PC3 Pin Data Input */
#define PC4_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 4))  /*!< Specify PC4 Pin Data Input */
#define PC5_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 5))  /*!< Specify PC5 Pin Data Input */
#define PC6_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 6))  /*!< Specify PC6 Pin Data Input */
#define PC7_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 7))  /*!< Specify PC7 Pin Data Input */
#define PC8_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 8))  /*!< Specify PC8 Pin Data Input */
#define PC9_PIN             MEM_ADDR(BITBAND(GPIOC_PIN, 9))  /*!< Specify PC9 Pin Data Input */
#define PC10_PIN            MEM_ADDR(BITBAND(GPIOC_PIN, 10)) /*!< Specify PC10 Pin Data Input */
#define PC11_PIN            MEM_ADDR(BITBAND(GPIOC_PIN, 11)) /*!< Specify PC11 Pin Data Input */
#define PC12_PIN            MEM_ADDR(BITBAND(GPIOC_PIN, 12)) /*!< Specify PC12 Pin Data Input */
#define PC13_PIN            MEM_ADDR(BITBAND(GPIOC_PIN, 13)) /*!< Specify PC13 Pin Data Input */
#define PC14_PIN            MEM_ADDR(BITBAND(GPIOC_PIN, 14)) /*!< Specify PC14 Pin Data Input */

#define PD0_PIN             MEM_ADDR(BITBAND(GPIOD_PIN, 0))  /*!< Specify PD0 Pin Data Input */
#define PD1_PIN             MEM_ADDR(BITBAND(GPIOD_PIN, 1))  /*!< Specify PD1 Pin Data Input */
#define PD2_PIN             MEM_ADDR(BITBAND(GPIOD_PIN, 2))  /*!< Specify PD2 Pin Data Input */
#define PD3_PIN             MEM_ADDR(BITBAND(GPIOD_PIN, 3))  /*!< Specify PD3 Pin Data Input */
#define PD4_PIN             MEM_ADDR(BITBAND(GPIOD_PIN, 4))  /*!< Specify PD4 Pin Data Input */

/*@}*/ /* end of group NUC505_GPIO_EXPORTED_CONSTANTS */

/** @addtogroup NUC505_GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Calculate GPIO port offset
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 *
 * @return      The specified GPIO port offset
 *
 * @details     Calculate GPIO port offset.
 * \hideinitializer
 */
#define GPIO_GET_OFFSET(gpio)                  ((gpio & 0xFF) /0x10)

/**
 * @brief       Clear GPIO Pin Interrupt Flag
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @return      None
 *
 * @details     Clear the interrupt status of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_CLR_INT_FLAG(gpio, u32PinMask)     GPIO_ClrIntFlag(gpio, u32PinMask)


/**
 * @brief       Disable Pin De-bounce Function
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32EINTMask  The specified EINT. It could be \n
 *                             - \ref   GPIO_DBCTL_EINT0_DBEN_MASK
 *                             - \ref   GPIO_DBCTL_EINT1_DBEN_MASK
 *                             - \ref   GPIO_DBCTL_EINT2_DBEN_MASK
 *                             - \ref   GPIO_DBCTL_EINT3_DBEN_MASK
 *
 * @return      None
 *
 * @details     Disable the interrupt de-bounce function of specified EINT.
 * \hideinitializer
 */
#define GPIO_DISABLE_DEBOUNCE(gpio, u32EINTMask)   (GPIO->DBCTL &= ~u32EINTMask)

/**
 * @brief       Enable Pin De-bounce Function
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32EINTMask  The specified EINT. It could be \n
 *                             - \ref   GPIO_DBCTL_EINT0_DBEN_MASK
 *                             - \ref   GPIO_DBCTL_EINT1_DBEN_MASK
 *                             - \ref   GPIO_DBCTL_EINT2_DBEN_MASK
 *                             - \ref   GPIO_DBCTL_EINT3_DBEN_MASK
 *
 * @return      None
 *
 * @details     Enable the interrupt de-bounce function of specified EINT.
 * \hideinitializer
 */
#define GPIO_ENABLE_DEBOUNCE(gpio, u32EINTMask)    (GPIO->DBCTL |= u32EINTMask)

/**
 * @brief       Get GPIO Pin Interrupt Flag
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 *
 * @retval      0           No interrupt at specified GPIO pin
 * @retval      1           The specified GPIO pin generate an interrupt
 *
 * @details     Get the interrupt status of specified GPIO pin.
 * \hideinitializer
 */
#define GPIO_GET_INT_FLAG(gpio, u32PinMask)   (((*(__IO uint32_t *) (&GPIO->INTSTSA_B + (GPIO_GET_OFFSET((uint32_t)gpio) >> 1))) >> (16 * (GPIO_GET_OFFSET((uint32_t)gpio) % 2)))  & u32PinMask)

/**
 * @brief       Set De-bounce Sampling Cycle Time
 *
 * @param[in]   u32ClkSrc   Unused.
 * @param[in]   u32ClkSel   The de-bounce sampling cycle selection. It could be \n
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_1
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_2
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_4
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_8
 *                             - \ref  GPIO_DBCTL_DBCLKSEL_16
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_32
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_64
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_128
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_256
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_512
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_1024
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_2048
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_4096
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_8192
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_16384
 *                             - \ref   GPIO_DBCTL_DBCLKSEL_32768
 *
 * @return      None
 *
 * @details     Set the interrupt de-bounce sampling cycle time based on the debounce counter clock source. \n
 *              Example: The De-debounce counter clock source is APB clock 10 MHz and sampling cycle selection is 14. \n
 *              Then the target de-bounce sampling cycle time is (2^14)*(1/(10*1000000)) s = 1.6 ms,
 *              and system will sampling interrupt input once per 1.6 ms.
 * \hideinitializer
 */
#define GPIO_SET_DEBOUNCE_TIME(u32ClkSrc, u32ClkSel)  (GPIO->DBCTL = (GPIO->DBCTL & ~GPIO_DBCTL_DBCLKSEL_Msk) | (u32ClkSel << GPIO_DBCTL_DBCLKSEL_Pos ))

/**
 * @brief       Get GPIO Port IN Data
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 *
 * @return      The specified port data
 *
 * @details     Get the PIN register of specified GPIO port.
 * \hideinitializer
 */
#define GPIO_GET_IN_DATA(gpio)   ((gpio)->PIN)

/**
 * @brief       Set GPIO Port OUT Data
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32Data     GPIO port data.
 *
 * @return      None
 *
 * @details     Set the Data into specified GPIO port.
 * \hideinitializer
 */
#define GPIO_SET_OUT_DATA(gpio, u32Data)   ((gpio)->DOUT = (u32Data))

/**
 * @brief       Disable GPIO Wake Up Function
 *
 * @param[in]   u32WkMask  The EINT of wake up source. It could be \n
 *                             - \ref   GPIO_INTCTL_EINT0_WKEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT1_WKEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT2_WKEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT3_WKEN_MASK
 *
 * @return      None
 *
 * @details     Disable the wake up function of EINT.
 * \hideinitializer
 */
#define GPIO_DISABLE_WAKE_UP(u32WkMask)   (GPIO->INTCTL &= ~u32WkMask)

/**
 * @brief       Enable GPIO Wake Up Function
 *
 * @param[in]   u32WkMask  The EINT of wake up source. It could be \n
 *                             - \ref   GPIO_INTCTL_EINT0_WKEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT1_WKEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT2_WKEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT3_WKEN_MASK
 *
 * @return      None
 *
 * @details     Enable the wake up function of EINT.
 * \hideinitializer
 */
#define GPIO_ENABLE_WAKE_UP(u32WkMask)    (GPIO->INTCTL |= u32WkMask)

/**
 * @brief       Disable GPIO Interrupt Latch Function
 *
 * @param[in]   u32LatchMask  The EINT of interrupt latch source. It could be \n
 *                             - \ref   GPIO_INTCTL_EINT0_INTLHEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT1_INTLHEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT2_INTLHEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT3_INTLHEN_MASK
 *
 * @return      None
 *
 * @details     Disable the interrupt latch function of EINT.
 * \hideinitializer
 */
#define GPIO_DISABLE_INT_LATCH(u32LatchMask)   (GPIO->INTCTL &= ~u32LatchMask)

/**
 * @brief       Enable GPIO Interrupt Latch Function
 *
 * @param[in]   u32LatchMask  The EINT of interrupt latch source. It could be \n
 *                             - \ref   GPIO_INTCTL_EINT0_INTLHEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT1_INTLHEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT2_INTLHEN_MASK
 *                             - \ref   GPIO_INTCTL_EINT3_INTLHEN_MASK
 *
 * @return      None
 *
 * @details     Enable the interrupt latch function of EINT.
 * \hideinitializer
 */
#define GPIO_ENABLE_INT_LATCH(u32LatchMask)    (GPIO->INTCTL |= u32LatchMask)

/**
 * @brief       Get GPIO Port Latch Data
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 *
 * @return      The specified port latch data
 *
 * @details     Get the interrupt latch data of specified GPIO port.
 * \hideinitializer
 */
#define GPIO_GET_LATCH_DATA(gpio)   *(__IO uint32_t *) (&PA->LATCHDAT + GPIO_GET_OFFSET((uint32_t)gpio))

void GPIO_SetMode(void *gpio, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_EnableInt(void *gpio, uint32_t u32Pin, uint32_t u32IntAttribs);
void GPIO_DisableInt(void *gpio, uint32_t u32Pin);
void GPIO_SetIntGroup(void *gpio, uint32_t u32Pin, uint32_t u32IntGroup);
void GPIO_SetPullMode(void *gpio, uint32_t u32PinMask, uint32_t u32Mode);
void GPIO_ClrIntFlag(void *gpio, uint32_t u32PinMask);

/*@}*/ /* end of group NUC505_GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_GPIO_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__GPIO_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
