/**************************************************************************//**
 * @file     PWM.c
 * @version  V1.00
 * $Revision: 20 $
 * $Date: 14/05/29 1:13p $
 * @brief    NUC505 PWM driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC505Series.h"

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_PWM_Driver PWM Driver
  @{
*/


/** @addtogroup NUC505_PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

/**
 * @brief This function config PWM generator and get the nearest frequency in edge aligned auto-reload mode
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Frequency Target generator frequency
 * @param[in] u32DutyCycle Target generator duty cycle percentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return Nearest frequency clock in nano second
 * @note Since every two channels, (0 & 1), (2 & 3) shares a prescaler. Call this API to configure PWM frequency may affect
 *       existing frequency of other channel.
 */
uint32_t PWM_ConfigOutputChannel (PWM_T *pwm,
                                  uint32_t u32ChannelNum,
                                  uint32_t u32Frequency,
                                  uint32_t u32DutyCycle)
{
    uint32_t i;
    uint32_t u32PWM_CLock;
    uint8_t  u8Divider = 1, u8Prescale = 0xFF;
    uint16_t u16CNR = 0xFFFF;

    if ((CLK->CLKDIV5 & CLK_CLKDIV5_PWMSEL_Msk) == 0)
        u32PWM_CLock = __HXT /(((CLK->CLKDIV5 & CLK_CLKDIV5_PWMDIV_Msk) >> CLK_CLKDIV5_PWMDIV_Pos) + 1);
    else
        u32PWM_CLock = SystemCoreClock /(((CLK->CLKDIV5 & CLK_CLKDIV5_PWMDIV_Msk) >> CLK_CLKDIV5_PWMDIV_Pos) + 1);

    for(; u8Divider < 17; u8Divider <<= 1)    // clk divider could only be 1, 2, 4, 8, 16
    {
        i = (u32PWM_CLock / u32Frequency) / u8Divider;
        // If target value is larger than CNR * prescale, need to use a larger divider
        if(i > (0x10000 * 0x100))
            continue;

        // CNR = 0xFFFF + 1, get a prescaler that CNR value is below 0xFFFF
        u8Prescale = (i + 0xFFFF)/ 0x10000;

        // u8Prescale must at least be 2, otherwise the output stop
        if(u8Prescale < 3)
            u8Prescale = 2;

        i /= u8Prescale;

        if(i <= 0x10000)
        {
            if(i == 1)
                u16CNR = 1;     // Too fast, and PWM cannot generate expected frequency...
            else
                u16CNR = i;
            break;
        }

    }
    // Store return value here 'cos we're gonna change u8Divider & u8Prescale & u16CNR to the real value to fill into register
    i = u32PWM_CLock / (u8Prescale * u8Divider * u16CNR);

    u8Prescale -= 1;
    u16CNR -= 1;
    // convert to real register value
    if(u8Divider == 1)
        u8Divider = 4;
    else if (u8Divider == 2)
        u8Divider = 0;
    else if (u8Divider == 4)
        u8Divider = 1;
    else if (u8Divider == 8)
        u8Divider = 2;
    else // 16
        u8Divider = 3;

    // every two channels share a prescaler
    pwm->CLKPSC = (pwm->CLKPSC & ~(PWM_CLKPSC_CLKPSC01_Msk << ((u32ChannelNum >> 1) * 8))) | (u8Prescale << ((u32ChannelNum >> 1) * 8));
    pwm->CLKDIV = (pwm->CLKDIV & ~(PWM_CLKDIV_CLKDIV0_Msk << (4 * u32ChannelNum))) | (u8Divider << (4 * u32ChannelNum));
    pwm->CTL |= 1 << (PWM_CTL_CNTMODE0_Pos + 8 * u32ChannelNum);
    if(u32DutyCycle == 0)
        *(__IO uint32_t *) (&pwm->CMPDAT0 + 3 * u32ChannelNum) = 0;
    else
        *(__IO uint32_t *) (&pwm->CMPDAT0 + 3 * u32ChannelNum) = u32DutyCycle * (u16CNR + 1) / 100 - 1;

    *(__IO uint32_t *) (&pwm->PERIOD0 + 3 * u32ChannelNum) = u16CNR;

    return(i);
}

/**
 * @brief This function config PWM capture and get the nearest unit time
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32UnitTimeNsec Unit time of counter
 * @param[in] u32CaptureEdge Condition to latch the counter
 * @return Nearest unit time in nano second
 * @note Since every two channels, (0 & 1), (2 & 3) shares a prescaler. Call this API to configure PWM frequency may affect
 *       existing frequency of other channel.
 */
uint32_t PWM_ConfigCaptureChannel (PWM_T *pwm,
                                   uint32_t u32ChannelNum,
                                   uint32_t u32UnitTimeNsec,
                                   uint32_t u32CaptureEdge)
{
    uint32_t i;
    uint32_t u32PWM_CLock;
    uint8_t  u8Divider = 1, u8Prescale = 0xFF;
    uint16_t u16CNR = 0xFFFF;

    (void)u32CaptureEdge;

    if ((CLK->CLKDIV5 & CLK_CLKDIV5_PWMSEL_Msk) == 0)
        u32PWM_CLock = __HXT /(((CLK->CLKDIV5 & CLK_CLKDIV5_PWMDIV_Msk) >> CLK_CLKDIV5_PWMDIV_Pos) + 1);
    else
        u32PWM_CLock = SystemCoreClock /(((CLK->CLKDIV5 & CLK_CLKDIV5_PWMDIV_Msk) >> CLK_CLKDIV5_PWMDIV_Pos) + 1);

    for(; u8Divider < 17; u8Divider <<= 1)    // clk divider could only be 1, 2, 4, 8, 16
    {
        i = ((u32PWM_CLock / u8Divider) * u32UnitTimeNsec) / 1000000000;

        // If target value is larger than 0xFF, need to use a larger divider
        if(i > (0xFF))
            continue;

        u8Prescale = i;

        // u8Prescale must at least be 2, otherwise the output stop
        if(u8Prescale < 3)
            u8Prescale = 2;

        break;
    }

    // Store return value here 'cos we're gonna change u8Divider & u8Prescale & u16CNR to the real value to fill into register
    i = (u8Prescale * u8Divider) * 1000000000/ u32PWM_CLock;

    u8Prescale -= 1;
    u16CNR -= 1;
    // convert to real register value
    if(u8Divider == 1)
        u8Divider = 4;
    else if (u8Divider == 2)
        u8Divider = 0;
    else if (u8Divider == 4)
        u8Divider = 1;
    else if (u8Divider == 8)
        u8Divider = 2;
    else // 16
        u8Divider = 3;

    // every two channels share a prescaler
    pwm->CLKPSC = (pwm->CLKPSC & ~(PWM_CLKPSC_CLKPSC01_Msk << ((u32ChannelNum >> 1) * 8))) | (u8Prescale << ((u32ChannelNum >> 1) * 8));
    pwm->CLKDIV = (pwm->CLKDIV & ~(PWM_CLKDIV_CLKDIV0_Msk << (4 * u32ChannelNum))) | (u8Divider << (4 * u32ChannelNum));
    pwm->CTL |= 1 << (PWM_CTL_CNTMODE0_Pos + 8 * u32ChannelNum);
    *(__IO uint32_t *) (&pwm->PERIOD0 + 3 * u32ChannelNum) = u16CNR;

    return(i);
}

/**
 * @brief This function start PWM module
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 */
void PWM_Start (PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            pwm->CTL |= (1 << (8*i));
        }
    }
}

/**
 * @brief This function stop PWM module
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 */
void PWM_Stop (PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            *(__IO uint32_t *) (&pwm->PERIOD0 + 3 * i) = 0;
        }
    }

}

/**
 * @brief This function stop PWM generation immediately by clear channel enable bit
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Bit 0 is channel 0, bit 1 is channel 1...
 * @return None
 */
void PWM_ForceStop (PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;
    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            pwm->CTL &= ~(1 << (8*i));
        }
    }
}

/**
 * @brief This function enables PWM capture of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 */
void PWM_EnableCapture (PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;

    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            if(i & 0x02)
                pwm->CAPCTL23 |= (1 << (PWM_CAPCTL23_CAPEN2_Pos + ((i & 0x01) << 4)));
            else
                pwm->CAPCTL01 |= (1 << (PWM_CAPCTL01_CAPEN0_Pos + ((i & 0x01) << 4)));
        }
    }

    pwm->CAPINEN |= u32ChannelMask;

    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            pwm->CTL |= (1 << (PWM_CTL_CNTMODE0_Pos + (8*i)));
        }
    }
}

/**
 * @brief This function disables PWM capture of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 */
void PWM_DisableCapture (PWM_T *pwm, uint32_t u32ChannelMask)
{
    uint32_t i;

    for(i = 0; i < PWM_CHANNEL_NUM; i ++)
    {
        if(u32ChannelMask & (1 << i))
        {
            if(i & 0x02)
                pwm->CAPCTL23 &= ~(1 << (PWM_CAPCTL23_CAPEN2_Pos + ((i & 0x01) << 4)));
            else
                pwm->CAPCTL01 &= ~(1 << (PWM_CAPCTL01_CAPEN0_Pos + ((i & 0x01) << 4)));
        }
    }

    pwm->CAPINEN &= ~u32ChannelMask;
}

/**
 * @brief This function enables PWM output generation of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel.
 *                           Set bit 0 to 1 enables channel 0 output, set bit 1 to 1 enables channel 1 output...
 * @return None
 */
void PWM_EnableOutput (PWM_T *pwm, uint32_t u32ChannelMask)
{
    pwm->POEN |= u32ChannelMask;
}

/**
 * @brief This function disables PWM output generation of selected channels
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Set bit 0 to 1 disables channel 0 output, set bit 1 to 1 disables channel 1 output...
 * @return None
 */
void PWM_DisableOutput (PWM_T *pwm, uint32_t u32ChannelMask)
{
    pwm->POEN &= ~u32ChannelMask;
}

/**
 * @brief This function enable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Duration Dead Zone length in PWM clock count, valid values are between 0~0xFF, but 0 means there is no
 *                        dead zone.
 * @return None
 */
void PWM_EnableDeadZone (PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // set duration
    pwm->CLKPSC = (pwm->CLKPSC & ~(PWM_CLKPSC_DZCNT01_Msk << (8 * u32ChannelNum))) | (u32Duration << (PWM_CLKPSC_DZCNT01_Pos + 8 * u32ChannelNum));
    // enable dead zone
    pwm->CTL |= (PWM_CTL_DTEN01_Msk << u32ChannelNum);
}

/**
 * @brief This function disable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 */
void PWM_DisableDeadZone (PWM_T *pwm, uint32_t u32ChannelNum)
{
    // every two channels shares the same setting
    u32ChannelNum >>= 1;
    // enable dead zone
    pwm->CTL &= ~(PWM_CTL_DTEN01_Msk << u32ChannelNum);
}

/**
 * @brief This function enable capture interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Edge Capture interrupt type. It could be either
 *              - \ref PWM_FALLING_LATCH_INT_ENABLE
 *              - \ref PWM_RISING_LATCH_INT_ENABLE
 *              - \ref PWM_RISING_FALLING_LATCH_INT_ENABLE
 * @return None
 */
void PWM_EnableCaptureInt (PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    // enable capture interrupt
    if(u32ChannelNum < 2)
        pwm->CAPCTL01 = (pwm->CAPCTL01 & ~(0x06 << (16 * u32ChannelNum))) | (u32Edge << (16 * u32ChannelNum));
    else
        pwm->CAPCTL23 = (pwm->CAPCTL23 & ~(0x06 << (16 * (u32ChannelNum - 2)))) | (u32Edge << (16 * (u32ChannelNum - 2)));

}

/**
 * @brief This function disable capture interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Edge Capture interrupt type. It could be either
 *              - \ref PWM_FALLING_LATCH_INT_ENABLE
 *              - \ref PWM_RISING_LATCH_INT_ENABLE
 *              - \ref PWM_RISING_FALLING_LATCH_INT_ENABLE
 * @return None
 */
void PWM_DisableCaptureInt (PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    // disable capture interrupt
    if(u32ChannelNum < 2)
        pwm->CAPCTL01 &= ~(u32Edge << (16 * u32ChannelNum));
    else
        pwm->CAPCTL23 &= ~(u32Edge << (16 * (u32ChannelNum - 2)));
}

/**
 * @brief This function clear capture interrupt flag of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Edge Capture interrupt type. It could be either
 *              - \ref PWM_RISING_LATCH_INT_FLAG
 *              - \ref PWM_FALLING_LATCH_INT_FLAG
 *              - \ref PWM_RISING_FALLING_LATCH_INT_FLAG
 * @return None
 */
void PWM_ClearCaptureIntFlag (PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge)
{
    // disable capture interrupt flag
    if(u32ChannelNum < 2)
        pwm->CAPCTL01 |= (((u32Edge << 6) | PWM_CAPCTL01_CAPIF0_Msk) << (16 * u32ChannelNum));
    else
        pwm->CAPCTL23 |= (((u32Edge << 6) | PWM_CAPCTL23_CAPIF2_Pos) << (16 * (u32ChannelNum - 2)));
}

/**
 * @brief This function get capture interrupt flag of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return Capture interrupt flag of specified channel
 * @retval 0 Capture interrupt did not occurred
 * @retval 1 Rising edge latch interrupt occurred
 * @retval 2 Falling edge latch interrupt occurred
 * @retval 3 Rising and falling edge latch interrupt occurred
 */
uint32_t PWM_GetCaptureIntFlag (PWM_T *pwm, uint32_t u32ChannelNum)
{
    if(u32ChannelNum < 2)
        return (((pwm->CAPCTL01 >> (16 * u32ChannelNum)) >> 6) & PWM_RISING_FALLING_LATCH_INT_FLAG);
    else
        return (((pwm->CAPCTL23 >> (16 * (u32ChannelNum - 2))) >> 6) & PWM_RISING_FALLING_LATCH_INT_FLAG);
}

/**
 * @brief This function enable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32IntPeriodType Period interrupt type, unused
 * @return None
 * @note All channels share the same period interrupt type setting.
 */
void PWM_EnablePeriodInt (PWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType)
{
    (void)u32IntPeriodType;
    pwm->INTEN |= ((1 << PWM_INTEN_PIEN_Pos) << u32ChannelNum);
}

/**
 * @brief This function disable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 */
void PWM_DisablePeriodInt (PWM_T *pwm, uint32_t u32ChannelNum)
{
    pwm->INTEN &= ~((1 << PWM_INTEN_PIEN_Pos) << u32ChannelNum);
}

/**
 * @brief This function clear period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 */
void PWM_ClearPeriodIntFlag (PWM_T *pwm, uint32_t u32ChannelNum)
{
    // write 1 clear
    pwm->INTSTS = ((1 << PWM_INTSTS_PIF_Pos) << u32ChannelNum);
}

/**
 * @brief This function get period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return Period interrupt flag of specified channel
 * @retval 0 Period interrupt did not occurred
 * @retval 1 Period interrupt occurred
 */
uint32_t PWM_GetPeriodIntFlag (PWM_T *pwm, uint32_t u32ChannelNum)
{
    return(pwm->INTSTS & ((1 << PWM_INTSTS_PIF_Pos) << u32ChannelNum) ? 1 : 0);
}



/*@}*/ /* end of group NUC505_PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_PWM_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
