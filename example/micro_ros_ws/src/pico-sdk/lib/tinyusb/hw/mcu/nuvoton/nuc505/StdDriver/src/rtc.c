/**************************************************************************//**
 * @file     rtc.c
 * @version  V1.00
 * $Revision: 13 $
 * $Date: 14/06/25 1:13p $
 * @brief    NUC505 RTC driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/


#include <stdio.h>
#include "NUC505Series.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Includes of local headers                                                                               */
/*---------------------------------------------------------------------------------------------------------*/



/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_RTC_Driver RTC Driver
  @{
*/
/// @cond HIDDEN_SYMBOLS

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define RTC_GLOBALS

/*---------------------------------------------------------------------------------------------------------*/
/* Global file scope (static) variables                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
static volatile uint32_t g_u32Reg, g_u32Reg1,g_u32hiYear,g_u32loYear,g_u32hiMonth,g_u32loMonth,g_u32hiDay,g_u32loDay;
static volatile uint32_t g_u32hiHour,g_u32loHour,g_u32hiMin,g_u32loMin,g_u32hiSec,g_u32loSec;

/// @endcond HIDDEN_SYMBOLS



/** @addtogroup NUC505_RTC_EXPORTED_FUNCTIONS RTC Exported Functions
  @{
*/


/**
 *  @brief      Synchronize RTC Register Write Status
 *              Software needs to call it after writing each RTC register.  \n
 *
 *  @return     None
 *
 */
void RTC_SyncReg(void)
{
    uint32_t u32i = 0, u32Wait = 0;

    u32Wait = RTC->SYNC & RTC_SYNC_SYNC_Msk;

    while(u32Wait!=RTC_SYNC_SYNC_Msk)
    {
        u32Wait = RTC->SYNC & RTC_SYNC_SYNC_Msk;
        u32i++;
        if(u32i > 500000)
            break;
    }
}



/**
 *  @brief      Set Frequency Compensation Data (It takes 1~2 seconds)
 *
 *  @return     None
 *
 */
void RTC_32KCalibration(void)
{
    uint32_t u32RegInt = 0,u32RegFra = 0,u32Count = 0;
    uint32_t u32Clock;
    float fTmp;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    u32Clock = CLK_GetPCLKFreq();        /* APB Clock */
    RTC->FREQADJ |= RTC_FREQADJ_ADJTRG_Msk;
    RTC_SyncReg();
    while(RTC->FREQADJ & RTC_FREQADJ_ADJTRG_Msk);

    u32Count = RTC->CALCNT;

    if(u32Count > 0)
    {
        fTmp = ((float) u32Clock / u32Count) * 32768;

        u32RegInt = (uint32_t) fTmp - 1;

        u32RegFra = (uint32_t)((fTmp - (u32RegInt + 1)) * 60) - 1;
    }

    RTC->FREQADJ = ((RTC->FREQADJ & ~(RTC_FREQADJ_INTEGER_Msk |RTC_FREQADJ_FRACTION_Msk)) | (((u32RegInt & 0xFFFF) << 8) | (u32RegFra & 0x3F)));
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      This function is used to: \n
 *              1. Write initial key to let RTC start count.  \n
 *              2. Input parameter indicates start time.      \n
 *              Null pointer for using default starting time. \n
 *
 *  @param[in]  sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *  @return     None
 *
 */
void RTC_Open (S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Reg;

    volatile int32_t i32delay = 1000;

    CLK->APBCLK  |= CLK_APBCLK_RTCCKEN_Msk;

    if((RTC->INIT & RTC_INIT_ACTIVE_Msk)!= RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;

        while((RTC->INIT & RTC_INIT_ACTIVE_Msk) != RTC_INIT_ACTIVE_Msk)
        {
            /* Waiting for RTC settings stable */
            while(i32delay--)
            {
                if((RTC->INIT & RTC_INIT_ACTIVE_Msk) == RTC_INIT_ACTIVE_Msk)
                    break;
            }
            i32delay = 1000;
            RTC->INIT = RTC_INIT_KEY;
        }
        i32delay = 1000;
        RTC_SyncReg();
    }

    if(sPt == NULL)
        return;


    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk))
    {
        while(i32delay--)
        {
            if(RTC->RWEN & RTC_RWEN_RWENF_Msk)
                break;
        }
        i32delay = 10000;
        RTC->INIT = RTC_INIT_KEY;
        RTC_SyncReg();
        RTC->RWEN = RTC_WRITE_KEY;
    }
    i32delay = 1000;
    RTC_SyncReg();

    RTC->POWCTL = RTC->POWCTL | RTC_POWCTL_POWEN_Msk;
    RTC_SyncReg();

    /*-----------------------------------------------------------------------------------------------------*/
    /* Second, set RTC 24/12 hour setting                                                                  */
    /*-----------------------------------------------------------------------------------------------------*/
    if (sPt->u32TimeScale == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();

        /*-------------------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 up to 32                                              */
        /*-------------------------------------------------------------------------------------------------*/
        if (sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    }
    else                                                                               /* RTC_CLOCK_24 */
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
    }

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC Calender Loading                                                                            */
    /*-----------------------------------------------------------------------------------------------------*/
    u32Reg     = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((sPt->u32Month  / 10) << 12);
    u32Reg    |= ((sPt->u32Month  % 10) << 8);
    u32Reg    |= ((sPt->u32Day    / 10) << 4);
    u32Reg    |= (sPt->u32Day     % 10);
    g_u32Reg = u32Reg;

    RTC->CAL = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    /*-----------------------------------------------------------------------------------------------------*/
    /* Set RTC Time Loading                                                                                */
    /*-----------------------------------------------------------------------------------------------------*/
    u32Reg     = ((sPt->u32Hour / 10) << 20);
    u32Reg    |= ((sPt->u32Hour % 10) << 16);
    u32Reg    |= ((sPt->u32Minute / 10) << 12);
    u32Reg    |= ((sPt->u32Minute % 10) << 8);
    u32Reg    |= ((sPt->u32Second / 10) << 4);
    u32Reg    |= (sPt->u32Second % 10);
    g_u32Reg = u32Reg;

    RTC->TIME = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    RTC->WEEKDAY = sPt->u32DayOfWeek;
    RTC_SyncReg();

    /* Waiting for RTC settings stable */
    while(i32delay--);

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      Read current date/time from RTC setting
 *
 *  @param[out]  sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *  @return     None                                                \n
 *
 */
void RTC_GetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Tmp;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    sPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;    /* 12/24-hour */
    sPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk;/* Day of week */

    g_u32hiYear  = (RTC->CAL & RTC_CAL_TENYEAR_Msk) >> RTC_CAL_TENYEAR_Pos;
    g_u32loYear  = (RTC->CAL & RTC_CAL_YEAR_Msk)    >> RTC_CAL_YEAR_Pos;
    g_u32hiMonth = (RTC->CAL & RTC_CAL_TENMON_Msk)  >> RTC_CAL_TENMON_Pos;
    g_u32loMonth = (RTC->CAL & RTC_CAL_MON_Msk)     >> RTC_CAL_MON_Pos;
    g_u32hiDay   = (RTC->CAL & RTC_CAL_TENDAY_Msk)  >> RTC_CAL_TENDAY_Pos;
    g_u32loDay   = (RTC->CAL & RTC_CAL_DAY_Msk);

    g_u32hiHour =  (RTC->TIME & RTC_TIME_TENHR_Msk)  >> RTC_TIME_TENHR_Pos;
    g_u32loHour =  (RTC->TIME & RTC_TIME_HR_Msk)     >> RTC_TIME_HR_Pos;
    g_u32hiMin  =  (RTC->TIME & RTC_TIME_TENMIN_Msk) >> RTC_TIME_TENMIN_Pos;
    g_u32loMin  =  (RTC->TIME & RTC_TIME_MIN_Msk)    >> RTC_TIME_MIN_Pos;
    g_u32hiSec  =  (RTC->TIME & RTC_TIME_TENSEC_Msk) >> RTC_TIME_TENSEC_Pos;
    g_u32loSec  =  (RTC->TIME & RTC_TIME_SEC_Msk);

    u32Tmp  = (g_u32hiYear * 10);              /* Compute to 20XX year */
    u32Tmp += g_u32loYear;
    sPt->u32Year = u32Tmp + RTC_YEAR2000;

    u32Tmp = (g_u32hiMonth * 10);              /* Compute 0~12 month */
    sPt->u32Month = u32Tmp + g_u32loMonth;

    u32Tmp = (g_u32hiDay * 10);                /* Compute 0~31 day */
    sPt->u32Day   =  u32Tmp  + g_u32loDay;

    if (sPt->u32TimeScale == RTC_CLOCK_12)   /* Compute12/24 hour */
    {
        u32Tmp = (g_u32hiHour * 10);
        u32Tmp+= g_u32loHour;
        sPt->u32Hour = u32Tmp;               /* AM: 1~12. PM: 21~32. */

        if (sPt->u32Hour >= 21)
        {
            sPt->u32AmPm = RTC_PM;
            sPt->u32Hour -= 20;
        }
        else
        {
            sPt->u32AmPm = RTC_AM;
        }

        u32Tmp = (g_u32hiMin  * 10);
        u32Tmp+= g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp = (g_u32hiSec  * 10);
        u32Tmp+= g_u32loSec;
        sPt->u32Second = u32Tmp;

    }
    else
    {
        /* RTC_CLOCK_24 */
        u32Tmp  = (g_u32hiHour * 10);
        u32Tmp += g_u32loHour;
        sPt->u32Hour = u32Tmp;

        u32Tmp  = (g_u32hiMin * 10);
        u32Tmp +=  g_u32loMin;
        sPt->u32Minute = u32Tmp;

        u32Tmp  = (g_u32hiSec * 10);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }
    RTC->RWEN = 0;
    RTC_SyncReg();
}



/**
 *  @brief      Read alarm date/time from RTC setting
 *
 *  @param[out]  sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *  @return     None                                              \n
 *
 */
void RTC_GetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Tmp;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    sPt->u32TimeScale = RTC->CLKFMT & RTC_CLKFMT_24HEN_Msk;              /* 12/24-hour */
    sPt->u32DayOfWeek = RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk;          /* Day of week */

    if(RTC->CALM & RTC_CALM_MSKYEAR_Msk)
        sPt->u32Year = RTC_ALARM_MASK;
    else
    {
        g_u32hiYear  = (RTC->CALM & RTC_CALM_TENYEAR_Msk) >> RTC_CALM_TENYEAR_Pos;
        g_u32loYear  = (RTC->CALM & RTC_CALM_YEAR_Msk)    >> RTC_CALM_YEAR_Pos;
        u32Tmp  = (g_u32hiYear * 10);                                    /* Compute to 20XX year */
        u32Tmp += g_u32loYear;
        sPt->u32Year = u32Tmp + RTC_YEAR2000;
    }

    if(RTC->CALM & RTC_CALM_MSKMON_Msk)
        sPt->u32Month = RTC_ALARM_MASK;
    else
    {
        g_u32hiMonth = (RTC->CALM & RTC_CALM_TENMON_Msk)  >> RTC_CALM_TENMON_Pos;
        g_u32loMonth = (RTC->CALM & RTC_CALM_MON_Msk)     >> RTC_CALM_MON_Pos;
        u32Tmp = (g_u32hiMonth * 10);                                    /* Compute 0~12 month */
        sPt->u32Month = u32Tmp + g_u32loMonth;

    }
    if(RTC->CALM & RTC_CALM_MSKMON_Msk)
        sPt->u32Day = RTC_ALARM_MASK;
    else
    {
        g_u32hiDay   = (RTC->CALM & RTC_CALM_TENDAY_Msk)  >> RTC_CALM_TENDAY_Pos;
        g_u32loDay   = (RTC->CALM & RTC_CALM_DAY_Msk);
        u32Tmp = (g_u32hiDay * 10);                                        /* Compute 0~31 day */
        sPt->u32Day = u32Tmp + g_u32loDay;
    }

    if(RTC->TALM & RTC_TALM_MSKHR_Msk)
        sPt->u32Hour  = RTC_ALARM_MASK;
    else
    {
        g_u32hiHour   =  (RTC->TALM & RTC_TALM_TENHR_Msk)  >> RTC_TALM_TENHR_Pos;
        g_u32loHour   =  (RTC->TALM & RTC_TALM_HR_Msk)     >> RTC_TALM_HR_Pos;

        if (sPt->u32TimeScale == RTC_CLOCK_12)                             /* Compute12/24 hour */
        {
            u32Tmp  = (g_u32hiHour * 10);
            u32Tmp += g_u32loHour;
            sPt->u32Hour = u32Tmp;                                        /* AM: 1~12. PM: 21~32. */

            if (sPt->u32Hour >= 21)
            {
                sPt->u32AmPm  = RTC_PM;
                sPt->u32Hour -= 20;
            }
            else
            {
                sPt->u32AmPm = RTC_AM;
            }
        }
        else
        {
            /* RTC_CLOCK_24 */
            u32Tmp  = (g_u32hiHour * 10);
            u32Tmp +=  g_u32loHour;
            sPt->u32Hour = u32Tmp;
        }

    }
    if(RTC->TALM & RTC_TALM_MSKMIN_Msk)
        sPt->u32Minute = RTC_ALARM_MASK;
    else
    {
        g_u32hiMin    =  (RTC->TALM & RTC_TALM_TENMIN_Msk) >> RTC_TALM_TENMIN_Pos;
        g_u32loMin    =  (RTC->TALM & RTC_TALM_MIN_Msk)    >> RTC_TALM_MIN_Pos;

        u32Tmp  = (g_u32hiMin * 10);
        u32Tmp += g_u32loMin;
        sPt->u32Minute = u32Tmp;
    }
    if(RTC->TALM & RTC_TALM_MSKSEC_Msk)
        sPt->u32Second = RTC_ALARM_MASK;
    else
    {
        g_u32hiSec    =  (RTC->TALM & RTC_TALM_TENSEC_Msk) >> RTC_TALM_TENSEC_Pos;
        g_u32loSec    =  (RTC->TALM & RTC_TALM_SEC_Msk);

        u32Tmp  = (g_u32hiSec * 10);
        u32Tmp += g_u32loSec;
        sPt->u32Second = u32Tmp;
    }


    RTC->RWEN = 0;
    RTC_SyncReg();
}



/**
 *  @brief      This function is used to update date/time to RTC.
 *
 *  @param[in]  sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *  @return     None
 *
 *
 */
void RTC_SetDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    if (sPt->u32TimeScale == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
        /*-----------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 up to 32                                      */
        /*-----------------------------------------------------------------------------------------*/
        if (sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    }
    else                                                                  /* RTC_CLOCK_24 */
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
    }

    RTC->WEEKDAY = sPt->u32DayOfWeek & RTC_WEEKDAY_WEEKDAY_Msk;
    RTC_SyncReg();
    u32Reg     = ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((sPt->u32Month  / 10) << 12);
    u32Reg    |= ((sPt->u32Month  % 10) << 8);
    u32Reg    |= ((sPt->u32Day    / 10) << 4);
    u32Reg    |=  (sPt->u32Day    % 10);
    g_u32Reg = u32Reg;

    RTC->CAL = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    u32Reg     = ((sPt->u32Hour   / 10) << 20);
    u32Reg    |= ((sPt->u32Hour   % 10) << 16);
    u32Reg    |= ((sPt->u32Minute / 10) << 12);
    u32Reg    |= ((sPt->u32Minute % 10) << 8);
    u32Reg    |= ((sPt->u32Second / 10) << 4);
    u32Reg    |=  (sPt->u32Second % 10);
    g_u32Reg = u32Reg;

    RTC->TIME = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      This function is used to set alarm date/time to RTC.
 *
 *  @param[in]  sPt \n
 *                     Specify the time property and current time. It includes:                          \n
 *                     u32Year: Year value.                                                               \n
 *                     u32Month: Month value.                                                             \n
 *                     u32Day: Day value.                                                                 \n
 *                     u32DayOfWeek: Day of week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                  \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                  \ref RTC_SATURDAY]                                       \n
 *                     u32Hour: Hour value.                                                               \n
 *                     u32Minute: Minute value.                                                           \n
 *                     u32Second: Second value.                                                           \n
 *                     u32TimeScale: [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]                                  \n
 *                     u8AmPm: [ \ref RTC_AM / \ref RTC_PM]                                                    \n
 *
 *
 *  @return     None
 *
 *  @note        If the parameter is 0xFF, RTC alarm mask for the field will be enabled and it also return 0xFF when user reads back the values.                                                \n
 */
void RTC_SetAlarmDateAndTime(S_RTC_TIME_DATA_T *sPt)
{
    uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    if (sPt->u32TimeScale == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
        /*-----------------------------------------------------------------------------------------*/
        /* important, range of 12-hour PM mode is 21 up to 32                                      */
        /*-----------------------------------------------------------------------------------------*/
        if (sPt->u32AmPm == RTC_PM)
            sPt->u32Hour += 20;
    }
    else                                                                  /* RTC_CLOCK_24 */
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
    }
    u32Reg = 0;

    if(sPt->u32DayOfWeek == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKWEEKDAY_Msk;
    else
        u32Reg = (sPt->u32DayOfWeek << RTC_CALM_WEEKDAY_Pos) & RTC_CALM_WEEKDAY_Msk;

    if(sPt->u32Year == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKYEAR_Msk;
    else
    {
        u32Reg    |= ((sPt->u32Year - RTC_YEAR2000) / 10) << 20;
        u32Reg    |= (((sPt->u32Year - RTC_YEAR2000) % 10) << 16);
    }
    if(sPt->u32Month == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKMON_Msk;
    else
    {
        u32Reg    |= ((sPt->u32Month  / 10) << 12);
        u32Reg    |= ((sPt->u32Month  % 10) << 8);
    }
    if(sPt->u32Day == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKDAY_Msk;
    else
    {
        u32Reg    |= ((sPt->u32Day     / 10) << 4);
        u32Reg    |=  (sPt->u32Day    % 10);
    }
    g_u32Reg   = u32Reg;

    RTC->CALM = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    u32Reg = 0;
    if(sPt->u32Hour == RTC_ALARM_MASK)
        u32Reg |= RTC_TALM_MSKHR_Msk;
    else
    {
        u32Reg    |= ((sPt->u32Hour   / 10) << 20);
        u32Reg    |= ((sPt->u32Hour   % 10) << 16);
    }
    if(sPt->u32Minute == RTC_ALARM_MASK)
        u32Reg |= RTC_TALM_MSKMIN_Msk;
    else
    {
        u32Reg    |= ((sPt->u32Minute / 10) << 12);
        u32Reg    |= ((sPt->u32Minute % 10) << 8);
    }
    if(sPt->u32Second == RTC_ALARM_MASK)
        u32Reg |= RTC_TALM_MSKSEC_Msk;
    else
    {
        u32Reg    |= ((sPt->u32Second / 10) << 4);
        u32Reg    |=  (sPt->u32Second % 10);
    }
    g_u32Reg = u32Reg;

    RTC->TALM = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    u32Reg = RTC->POWCTL | RTC_POWCTL_ALMIEN_Msk;
    RTC->POWCTL =  u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}


/**
 *  @brief      This function is used to update date to RTC
 *
 *  @param[in]  u32Year       The Year Calendar Digit of Alarm Setting                           \n
 *  @param[in]  u32Month      The Month Calendar Digit of Alarm Setting                           \n
 *  @param[in]  u32Day        The Day Calendar Digit of Alarm Setting                             \n
 *  @param[in]  u32DayOfWeek  The Day of Week. [ \ref RTC_SUNDAY / \ref RTC_MONDAY / \ref RTC_TUESDAY /
 *                                                 \ref RTC_WEDNESDAY / \ref RTC_THURSDAY / \ref RTC_FRIDAY /
 *                                                 \ref RTC_SATURDAY]                                          \n
 *
 *  @return     None
 *
 */
void RTC_SetDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day, uint32_t u32DayOfWeek)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->WEEKDAY = u32DayOfWeek & RTC_WEEKDAY_WEEKDAY_Msk;
    RTC_SyncReg();

    u32Reg     = ((u32Year - RTC_YEAR2000) / 10) << 20;
    u32Reg    |= (((u32Year - RTC_YEAR2000) % 10) << 16);
    u32Reg    |= ((u32Month  / 10) << 12);
    u32Reg    |= ((u32Month  % 10) << 8);
    u32Reg    |= ((u32Day    / 10) << 4);
    u32Reg    |=  (u32Day    % 10);
    g_u32Reg   = u32Reg;

    RTC->CAL = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      This function is used to update time to RTC.                                     \n
 *                                                                                               \n
 *  @param[in]    u32Hour     The Hour Time Digit of Alarm Setting.
 *  @param[in]    u32Minute   The Month Calendar Digit of Alarm Setting
 *  @param[in]    u32Second   The Day Calendar Digit of Alarm Setting
 *  @param[in]    u32TimeMode The 24-Hour / 12-Hour Time Scale Selection. [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]
 *  @param[in]    u32AmPm     12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [ \ref RTC_AM / \ref RTC_PM]
 *
 *  @return     None
 *
 */
void RTC_SetTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    if (u32TimeMode == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();

        if (u32AmPm == RTC_PM)    /* important, range of 12-hour PM mode is 21 up to 32 */
            u32Hour += 20;
    }
    else if(u32TimeMode == RTC_CLOCK_24)
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
    }

    u32Reg     = ((u32Hour   / 10) << 20);
    u32Reg    |= ((u32Hour   % 10) << 16);
    u32Reg    |= ((u32Minute / 10) << 12);
    u32Reg    |= ((u32Minute % 10) << 8);
    u32Reg    |= ((u32Second / 10) << 4);
    u32Reg    |=  (u32Second % 10);

    g_u32Reg = u32Reg;

    RTC->TIME = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      This function is used to set alarm date to RTC
 *
 *  @param[in]      u32Year    The Year Calendar Digit of Alarm Setting
 *  @param[in]      u32Month   The Month Calendar Digit of Alarm Setting
 *  @param[in]      u32Day     The Day Calendar Digit of Alarm Setting
 *
 *  @return      None
 *
 *  @ note       If the parameter is 0xFF, RTC alarm mask for the field will be enabled and it also return 0xFF when user reads back the values.\n
 *               For example: RTC_SetAlarmDate(0xFF, 0xFF, 2); The alarm occurs monthly 2nd.
 */

void RTC_SetAlarmDate(uint32_t u32Year, uint32_t u32Month, uint32_t u32Day)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    u32Reg = RTC_CALM_MSKWEEKDAY_Msk; /* Always enable Weekday Mask*/

    if(u32Year == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKYEAR_Msk;
    else
    {
        u32Reg    |= ((u32Year - RTC_YEAR2000) / 10) << 20;
        u32Reg    |= (((u32Year - RTC_YEAR2000) % 10) << 16);
    }
    if(u32Month == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKMON_Msk;
    else
    {
        u32Reg    |= ((u32Month  / 10) << 12);
        u32Reg    |= ((u32Month  % 10) << 8);
    }
    if(u32Day == RTC_ALARM_MASK)
        u32Reg |= RTC_CALM_MSKDAY_Msk;
    else
    {
        u32Reg    |= ((u32Day / 10) << 4);
        u32Reg    |=  (u32Day % 10);
    }
    g_u32Reg   = u32Reg;

    RTC->CALM = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    u32Reg = RTC->POWCTL | RTC_POWCTL_ALMIEN_Msk;
    RTC->POWCTL =  u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      This function is used to set alarm date to RTC
 *
 *  @param[in]     u32Hour     The Hour Time Digit of Alarm Setting.
 *  @param[in]     u32Minute   The Minute Time Digit of Alarm Setting
 *  @param[in]     u32Second   The Second Time Digit of Alarm Setting
 *  @param[in]     u32TimeMode The 24-Hour / 12-Hour Time Scale Selection. [ \ref RTC_CLOCK_12 / \ref RTC_CLOCK_24]
 *  @param[in]     u32AmPm     12-hour time scale with AM and PM indication. Only Time Scale select 12-hour used. [ \ref RTC_AM / \ref RTC_PM]
 *
 *  @return        None
 *
 *  @note       If the parameter is 0xFF, RTC alarm mask for the field will be enabled and it also return 0xFF when user reads back the values.
 *              For example: The alarm occurs when 20xx/xx/02 00:00:10.
 *                 RTC_SetAlarmDate(0xFF, 0xFF, 2); \n
 *                 RTC_ SetAlarmTime (0xFF, 0xFF, 10);
 */
void RTC_SetAlarmTime(uint32_t u32Hour, uint32_t u32Minute, uint32_t u32Second, uint32_t u32TimeMode, uint32_t u32AmPm)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    if (u32TimeMode == RTC_CLOCK_12)
    {
        RTC->CLKFMT &= ~RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();

        if (u32AmPm == RTC_PM)    /* important, range of 12-hour PM mode is 21 up to 32 */
            u32Hour += 20;
    }
    else if(u32TimeMode == RTC_CLOCK_24)
    {
        RTC->CLKFMT |= RTC_CLKFMT_24HEN_Msk;
        RTC_SyncReg();
    }

    u32Reg = 0;
    if(u32Hour == RTC_ALARM_MASK)
        u32Reg |= RTC_TALM_MSKHR_Msk;
    else
    {
        u32Reg    |= ((u32Hour / 10) << 20);
        u32Reg    |= ((u32Hour % 10) << 16);
    }
    if(u32Minute == RTC_ALARM_MASK)
        u32Reg |= RTC_TALM_MSKMIN_Msk;
    else
    {
        u32Reg    |= ((u32Minute / 10) << 12);
        u32Reg    |= ((u32Minute % 10) << 8);
    }
    if(u32Second == RTC_ALARM_MASK)
        u32Reg |= RTC_TALM_MSKSEC_Msk;
    else
    {
        u32Reg    |= ((u32Second / 10) << 4);
        u32Reg    |=  (u32Second % 10);
    }
    g_u32Reg = u32Reg;

    RTC->TALM = (uint32_t)g_u32Reg;
    RTC_SyncReg();

    u32Reg = RTC->POWCTL | RTC_POWCTL_ALMIEN_Msk;
    RTC->POWCTL =  u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      This function is used to get day of week
 *
 *  @return     Day of Week
 *
 */
uint32_t RTC_GetDayOfWeek(void)
{
    return (RTC->WEEKDAY & RTC_WEEKDAY_WEEKDAY_Msk);
}



/**
 *  @brief      The function is used to set time tick period for periodic time tick Interrupt.
 *
 *  @param[in]  u32TickSelection
 *                       It is used to set the RTC time tick period for Periodic Time Tick Interrupt request.
 *                       It consists of: \n
 *                       - \ref RTC_TICK_1_SEC : Time tick is 1 second        \n
 *                       - \ref RTC_TICK_1_2_SEC : Time tick is 1/2 second    \n
 *                       - \ref RTC_TICK_1_4_SEC : Time tick is 1/4 second    \n
 *                       - \ref RTC_TICK_1_8_SEC : Time tick is 1/8 second    \n
 *                       - \ref RTC_TICK_1_16_SEC : Time tick is 1/16 second  \n
 *                       - \ref RTC_TICK_1_32_SEC : Time tick is 1/32 second  \n
 *                       - \ref RTC_TICK_1_64_SEC : Time tick is 1/64 second  \n
 *                       - \ref RTC_TICK_1_128_SEC : Time tick is 1/128 second
 *
 *  @return     None
 *
 */
void RTC_SetTickPeriod(uint32_t u32TickSelection)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->TICK = (RTC->TICK & ~RTC_TICK_TICKSEL_Msk) | u32TickSelection;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}


/**
 *  @brief      The function is used to enable specified interrupt.
 *
 *  @param[in]  u32IntFlagMask      The structure of interrupt source. It consists of:      \n
 *                                    - \ref RTC_INTEN_ALMIEN_Msk    \n
 *                                     - \ref RTC_INTEN_RALMIEN_Msk  \n
 *                                    - \ref RTC_INTEN_TICKIEN_Msk  \n
 *                                    - \ref RTC_INTEN_PKEYIEN_Msk  \n
 *
 *  @return     None
 *
 */
void RTC_EnableInt(uint32_t u32IntFlagMask)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->INTEN |= u32IntFlagMask;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief      The function is used to disable specified interrupt.
 *
 *  @param[in]  u32IntFlagMask      The structure of interrupt source. It consists of:     \n
 *                                    - \ref RTC_INTEN_ALMIEN_Msk    \n
 *                                    - \ref RTC_INTEN_TICKIEN_Msk  \n
 *                                    - \ref RTC_INTEN_PKEYIEN_Msk  \n
 *
 *  @return    None
 *
 */
void RTC_DisableInt(uint32_t u32IntFlagMask)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    if(u32IntFlagMask & RTC_INTEN_TICKIEN_Msk)
    {
        RTC->INTEN  &= ~RTC_INTEN_TICKIEN_Msk;
        RTC_SyncReg();

        RTC->INTSTS |= RTC_INTSTS_TICKIF_Msk;
        RTC_SyncReg();
    }

    if(u32IntFlagMask & RTC_INTEN_ALMIEN_Msk)
    {
        RTC->INTEN &= ~RTC_INTEN_ALMIEN_Msk;
        RTC_SyncReg();

        RTC->INTSTS |= RTC_INTSTS_ALMIF_Msk;
        RTC_SyncReg();
    }

    if(u32IntFlagMask & RTC_INTEN_PKEYIEN_Msk)
    {
        RTC->INTEN &= ~RTC_INTEN_PKEYIEN_Msk;
        RTC_SyncReg();

        RTC->INTSTS |= RTC_INTSTS_POWKEYIF_Msk;
        RTC_SyncReg();
    }


    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief    Disable RTC clock.
 *
 *  @return   None
 *
 */
void RTC_Close (void)
{
    CLK->APBCLK  &= ~CLK_APBCLK_RTCCKEN_Msk;
}

/**
 *  @brief      This function is used to set relative alarm time to RTC
 *
 *  @param[in]  u32Second   The Second Time Digit of relative Alarm Setting
 *
 *  @return     None
 *
 */
void RTC_SetRelAlarmTime(uint32_t u32Second)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->POWCTL =  (RTC->POWCTL & ~(RTC_POWCTL_RALMTIME_Msk | RTC_POWCTL_RALMIEN_Msk));
    RTC_SyncReg();

    u32Reg = (RTC->POWCTL & ~RTC_POWCTL_RALMTIME_Msk)| ((u32Second & 0xFFF) <<RTC_POWCTL_RALMTIME_Pos);
    RTC->POWCTL = u32Reg;
    RTC_SyncReg();

    u32Reg = RTC->POWCTL | RTC_POWCTL_RALMIEN_Msk;
    RTC->POWCTL =  u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}


/**
 *  @brief      This function is used to set Power Key active mode and active time
 *
 *  @details    For Level Trigger mode, Power key will be active after Power Key is pressed specified seconds.  \n
 *              But for Edge Trigger mode, it needs to released Power Key to let Power Key active.\n
 *              For example: In Edge Trigger mode, Power Key will not be active if Power Key is always pressed by something else.\n
 *                           Power Key will be active only when Power Key is released (after the specified seconds).
 *
 *  @param[in]  u32Mode      Power Key Active mode\n
 *                                - \ref RTC_TRIGGER_EDGE    \n
 *                                - \ref RTC_TRIGGER_LEVEL  \n
 *  @param[in]  u32Second   Power Key will be active after (u32Second + 1 ) * 0.25 seconds.  \n
 *
 *  @return     None
 *
 */
void RTC_SetPowerOnMode(uint32_t u32Mode, uint32_t u32Second)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->POWCTL =  (RTC->POWCTL & ~RTC_POWCTL_EDGE_TRIG_Msk) | u32Mode;
    RTC_SyncReg();

    u32Reg = (RTC->FREQADJ & ~RTC_FREQADJ_PKEYTIME_Msk)| ((u32Second & 0xF) <<RTC_FREQADJ_PKEYTIME_Pos);
    RTC->FREQADJ = u32Reg;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}
/**
 *  @brief      This function is used to get power key status
 *
 *  @return     Status of Power key
 *
 */
uint32_t RTC_GetPowerKeyStatus(void)
{
    __IO uint32_t u32Reg;
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    u32Reg = (RTC->POWCTL & RTC_POWCTL_POWKEY_Msk) >> RTC_POWCTL_POWKEY_Pos ;

    RTC->RWEN = 0;
    RTC_SyncReg();

    return u32Reg;
}

/**
 *  @brief      This function is used to set RTC power off
 *
 *  @return     None
 *
 */
void RTC_SetPowerOff(void)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->POWCTL = ((RTC->POWCTL & ~RTC_POWCTL_POWEN_Msk) | RTC_POWCTL_SWPOWOFF_Msk);
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();

    //Disable CPU

    while(1);
}

/**
 *  @brief      This function is used to enable Hardware Power off function and set the trigger time
 *
 *  @details    The function is called software code is out of control and triggered automatically by hardware when software code is out of control.  \n
 *              Push down on RTC "Power Key" and hold it down a specified seconds, NUC505 power off will be power off immediately.
 *
 *  @param[in]  u32Second   Holding Power key (u32Second + 3) seconds to power off
 *
 *  @return     None
 *
 */
void RTC_EnableHardwarePowerOff(uint32_t u32Second)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->POWCTL = ((RTC->POWCTL & ~RTC_POWCTL_POWOFFT_Msk) | RTC_POWCTL_POWOFFEN_Msk | ( (u32Second & 0xF) << RTC_POWCTL_POWOFFT_Pos) );
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/**
 *  @brief    This function is used to disable Hardware Power off function
 *
 *  @return   None
 *
 */
void RTC_DisableHardwarePowerOff(void)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();

    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->POWCTL = RTC->POWCTL & ~RTC_POWCTL_POWOFFEN_Msk;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();

}

/**
 *  @brief      The function is used to set RTC clock source.
 *
 *  @param[in]    u32ClockSource
 *                       It is used to select RTC clock source.
 *                       It consists of: \n
 *                       - \ref RTC_CLKSRC_EXTERNAL  \n
 *                       - \ref RTC_CLKSRC_INTERNAL  \n
 *
 *  @return     None
 *
 */
void RTC_SetClockSource(uint32_t u32ClockSource)
{
    RTC->INIT = RTC_INIT_KEY;
    RTC_SyncReg();
    RTC->RWEN = RTC_WRITE_KEY;
    while(!(RTC->RWEN & RTC_RWEN_RWENF_Msk));
    RTC_SyncReg();

    RTC->CLKSRC = (RTC->CLKSRC & ~RTC_CLKSRC_CKSRC_Msk) | u32ClockSource;
    RTC_SyncReg();

    RTC->RWEN = 0;
    RTC_SyncReg();
}

/*@}*/ /* end of group NUC505_RTC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_RTC_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


