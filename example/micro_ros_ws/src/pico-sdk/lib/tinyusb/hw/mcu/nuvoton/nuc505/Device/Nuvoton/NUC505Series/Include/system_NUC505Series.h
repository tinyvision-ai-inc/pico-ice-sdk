/**************************************************************************//**
 * @file     system_NUC505Series.h
 * @version  V1.00
 * $Revision: 3 $
 * $Date: 13/11/10 9:32a $
 * @brief    NUC505 series system clock definition file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SYSTEM_NUC505SERIES_H__
#define __SYSTEM_NUC505SERIES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __HXT         (12000000UL)  /*!< High Speed External Crystal Clock Frequency 12MHz */
#define __LXT         (32768UL)     /*!< Low Speed External Crystal Clock Frequency 32.768kHz */
#define __HIRC        (22118400UL)  /*!< High Speed Internal 22MHz RC Oscillator Frequency */
#define __LIRC        (10000UL)     /*!< Low Speed Internal 10kHz RC Oscillator Frequency */
#define __HSI         (__HIRC)      /* Factory Default is internal 12MHz */


extern uint32_t SystemCoreClock;     /*!< System Clock Frequency (Core Clock)  */
extern uint32_t CyclesPerUs;         /*!< Cycles per micro second              */
extern uint32_t PllClock;            /*!< PLL Output Clock Frequency           */


/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from CPU registers.
 */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_NUC505SERIES_H__ */
/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
