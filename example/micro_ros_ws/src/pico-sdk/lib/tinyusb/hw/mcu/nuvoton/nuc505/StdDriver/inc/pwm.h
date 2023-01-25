/**************************************************************************//**
 * @file     pwm.h
 * @version  V1.00
 * $Revision: 18 $
 * $Date: 14/05/29 1:13p $
 * @brief    NUC505 PWM driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PWM_H__
#define __PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_PWM_Driver PWM Driver
  @{
*/

/** @addtogroup NUC505_PWM_EXPORTED_CONSTANTS PWM Exported Constants
  @{
*/
#define PWM_CHANNEL_NUM                     (4)      /*!< PWM channel number \hideinitializer */
#define PWM_CH0                             (0UL)    /*!< PWM channel 0  \hideinitializer */
#define PWM_CH1                             (1UL)    /*!< PWM channel 1  \hideinitializer */
#define PWM_CH2                             (2UL)    /*!< PWM channel 2  \hideinitializer */
#define PWM_CH3                             (3UL)    /*!< PWM channel 3  \hideinitializer */
#define PWM_CH_0_MASK                       (1UL)    /*!< PWM channel 0 mask \hideinitializer */
#define PWM_CH_1_MASK                       (2UL)    /*!< PWM channel 1 mask \hideinitializer */
#define PWM_CH_2_MASK                       (4UL)    /*!< PWM channel 2 mask \hideinitializer */
#define PWM_CH_3_MASK                       (8UL)    /*!< PWM channel 3 mask \hideinitializer */
#define PWM_CLK_DIV_1                       (4UL)    /*!< PWM clock divide by 1 \hideinitializer */
#define PWM_CLK_DIV_2                       (0UL)    /*!< PWM clock divide by 2 \hideinitializer */
#define PWM_CLK_DIV_4                       (1UL)    /*!< PWM clock divide by 4 \hideinitializer */
#define PWM_CLK_DIV_8                       (2UL)    /*!< PWM clock divide by 8 \hideinitializer */
#define PWM_CLK_DIV_16                      (3UL)    /*!< PWM clock divide by 16 \hideinitializer */
#define PWM_RISING_LATCH_INT_ENABLE         (0x02UL)       /*!< PWM rising latch interrupt enable \hideinitializer */
#define PWM_FALLING_LATCH_INT_ENABLE        (0x04UL)     /*!< PWM falling latch interrupt enable \hideinitializer */
#define PWM_RISING_FALLING_LATCH_INT_ENABLE (0x06UL)     /*!< PWM rising latch interrupt enable \hideinitializer */
#define PWM_RISING_LATCH_INT_FLAG           (0x01UL)          /*!< PWM rising latch condition happened \hideinitializer */
#define PWM_FALLING_LATCH_INT_FLAG          (0x02UL)         /*!< PWM falling latch condition happened \hideinitializer */
#define PWM_RISING_FALLING_LATCH_INT_FLAG   (0x03UL)  /*!< PWM rising latch condition happened \hideinitializer */

/*@}*/ /* end of group NUC505_PWM_EXPORTED_CONSTANTS */


/** @addtogroup NUC505_PWM_EXPORTED_FUNCTIONS PWM Exported Functions
  @{
*/

/**
 * @brief This macro enable output inverter of specified channel(s)
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelMask Combination of enabled channels. Each bit corresponds to a channel
 *                           Bit 0 represents channel 0, bit 1 represents channel 1...
 * @return None
 * \hideinitializer
 */
#define PWM_ENABLE_OUTPUT_INVERTER(pwm, u32ChannelMask) \
{\
    uint32_t i; \
    pwm->CTL &= ~(PWM_CTL_PINV0_Msk | PWM_CTL_PINV1_Msk | PWM_CTL_PINV2_Msk | PWM_CTL_PINV3_Msk);   \
    for(i = 0; i < PWM_CHANNEL_NUM; i ++) { \
        if((u32ChannelMask) & (1 << i)) { \
            pwm->CTL |= (1UL << (8*i + 2)); \
        }   \
    }   \
}

/**
 * @brief This macro get captured rising data
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * \hideinitializer
 */
#define PWM_GET_CAPTURE_RISING_DATA(pwm, u32ChannelNum) (*(__IO uint32_t *) (&pwm->RCAPDAT0 + 2 * u32ChannelNum))

/**
 * @brief This macro get captured falling data
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @return None
 * \hideinitializer
 */
#define PWM_GET_CAPTURE_FALLING_DATA(pwm, u32ChannelNum) (*(__IO uint32_t *) (&pwm->FCAPDAT0 + 2 * u32ChannelNum))

/**
 * @brief This macro set the prescaler of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Prescaler Clock prescaler of specified channel. Valid values are between 1 ~ 0xFF
 * @return None
 * @note Every even channel N, and channel (N + 1) share a prescaler. So if channel 0 prescaler changed,
 *       channel 1 will also be affected.
 * \hideinitializer
 */
#define PWM_SET_PRESCALER(pwm, u32ChannelNum, u32Prescaler) \
    (pwm->CLKPSC = (pwm->CLKPSC & ~(PWM_CLKPSC_CLKPSC01_Msk << (((u32ChannelNum) >> 1) * 8))) | ((u32Prescaler) << (((u32ChannelNum) >> 1) * 8)))

/**
 * @brief This macro set the divider of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32Divider Clock divider of specified channel. Valid values are
 *              - \ref PWM_CLK_DIV_1
 *              - \ref PWM_CLK_DIV_2
 *              - \ref PWM_CLK_DIV_4
 *              - \ref PWM_CLK_DIV_8
 *              - \ref PWM_CLK_DIV_16
 * @return None
 * \hideinitializer
 */
#define PWM_SET_DIVIDER(pwm, u32ChannelNum, u32Divider) \
    (pwm->CLKDIV = (pwm->CLKDIV & ~(PWM_CLKDIV_CLKDIV0_Msk << ((u32ChannelNum) * 4))) | ((u32Divider) << ((u32ChannelNum) * 4)))

/**
 * @brief This macro set the duty of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32CMR Duty of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next PWM period
 * \hideinitializer
 */
#define PWM_SET_CMR(pwm, u32ChannelNum, u32CMR) (*(__IO uint32_t *)(&pwm->CMPDAT0 + 3 * u32ChannelNum) = (u32CMR))

/**
 * @brief This macro set the period of the selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~3
 * @param[in] u32CNR Period of specified channel. Valid values are between 0~0xFFFF
 * @return None
 * @note This new setting will take effect on next PWM period
 * @note PWM counter will stop if period length set to 0
 * \hideinitializer
 */
#define PWM_SET_CNR(pwm, u32ChannelNum, u32CNR)  (*(__IO uint32_t *)(&pwm->PERIOD0 + 3 * u32ChannelNum) = (u32CNR))

uint32_t PWM_ConfigOutputChannel(PWM_T *pwm,
                                 uint32_t u32ChannelNum,
                                 uint32_t u32Frequency,
                                 uint32_t u32DutyCycle);
uint32_t PWM_ConfigCaptureChannel (PWM_T *pwm,
                                   uint32_t u32ChannelNum,
                                   uint32_t u32UnitTimeNsec,
                                   uint32_t u32CaptureEdge);
void PWM_Start(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_Stop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_ForceStop(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableCapture(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_DisableOutput(PWM_T *pwm, uint32_t u32ChannelMask);
void PWM_EnableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Duration);
void PWM_DisableDeadZone(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void PWM_DisableCaptureInt(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
void PWM_ClearCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum, uint32_t u32Edge);
uint32_t PWM_GetCaptureIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_EnablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum,  uint32_t u32IntPeriodType);
void PWM_DisablePeriodInt(PWM_T *pwm, uint32_t u32ChannelNum);
void PWM_ClearPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);
uint32_t PWM_GetPeriodIntFlag(PWM_T *pwm, uint32_t u32ChannelNum);



/*@}*/ /* end of group NUC505_PWM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_PWM_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__PWM_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
