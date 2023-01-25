/**************************************************************************//**
 * @file     adc.c
 * @version  V1.00
 * $Revision: 12 $
 * $Date: 14/07/01 1:13p $
 * @brief    NUC505 ADC driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC505Series.h"

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_ADC_Driver ADC Driver
  @{
*/


/** @addtogroup NUC505_ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief                      Enable ADC module
  * @param[in]  adc             Base address of ADC module
  * @param[in]  u32InputMode    Useless in NUC505 series
  * @param[in]  u32OpMode       Useless in NUC505 series
  * @param[in]  u32ChMask       Channel enable bit. Valid values are:
  *                             - \ref ADC_CH_0_MASK
  *                             - \ref ADC_CH_1_MASK
  *                             - \ref ADC_CH_2_MASK
  *                             - \ref ADC_CH_3_MASK
  *                             - \ref ADC_CH_4_MASK
  *                             - \ref ADC_CH_5_MASK
  *                             - \ref ADC_CH_6_MASK
  *                             - \ref ADC_CH_7_MASK
  * @return  None
  */
void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask)
{
    (void)adc;
    (void)u32InputMode;
    (void)u32OpMode;
    ADC->CTL  = (ADC->CTL & ~(ADC_CTL_PD_Msk | ADC_CTL_PDKEY_Msk |ADC_CTL_CHSEL_Msk))\
                | (u32ChMask<<ADC_CTL_CHSEL_Pos);
}

/**
  * @brief                      Disable ADC module
  * @param[in]  adc             Base address of ADC module
  * @return     None
  */
void ADC_Close(ADC_T *adc)
{
    (void)adc;
    ADC->CTL  = ADC->CTL | ADC_CTL_CHSEL_Msk;           /* Switching to channel 7 to save power */
    ADC->CTL  = ADC->CTL | (ADC_CTL_PD_Msk | ADC_CTL_PDKEY_Msk);
}

/**
  * @brief                      Configure the hardware trigger condition and enable hardware trigger
  * @param[in]  adc             Base address of ADC module
  * @param[in]  u32ChMask       Decides the hardware trigger source. Valid values are:
  *                             - \ref ADC_CH_0_MASK
  *                             - \ref ADC_CH_1_MASK
  *                             - \ref ADC_CH_2_MASK
  *                             - \ref ADC_CH_3_MASK
  *                             - \ref ADC_CH_4_MASK
  *                             - \ref ADC_CH_5_MASK
  *                             - \ref ADC_CH_6_MASK
  *                             - \ref ADC_CH_7_MASK
  * @param[in]  u32SampleTime   When A/D converting at high conversion rate,
    *                             the sampling time of analog input voltage may not enough if input channel loading is heavy.
    *                                                   Programmer can extend A/D sampling time after trigger source is coming to get enough sampling time.
    *                                                   The range is from 0 ~ 255 ADC clock. The unit is SAR-ADC clock.
  * @return     None
  */
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32ChMask,
                         uint32_t u32SampleTime)
{
    (void)adc;
    ADC->CTL  = (ADC->CTL & ~(ADC_CTL_CHSEL_Msk|ADC_CTL_EXTSMPT_Msk)) |\
                ((u32ChMask<<ADC_CTL_CHSEL_Pos) | (u32SampleTime<<ADC_CTL_EXTSMPT_Pos));
    ADC->CTL |= ADC_CTL_SWTRG_Msk;
    return;
}

/**
  * @brief Enable the interrupt(s) selected by u32Mask parameter.
  * @param[in] adc              Base address of ADC module
  * @param[in] u32Mask          The combination of interrupt status bits listed below. Each bit\n
  *                             corresponds to a interrupt status. This parameter decides which\n
  *                             interrupts will be enabled.
  *                             - \ref ADC_ADF_INT
  *                             - \ref ADC_KEY_INT
  * @return     None
  */
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask)
{
    (void)adc;
    if(u32Mask & ADC_ADF_INT)
        ADC->INTCTL |= ADC_INTCTL_ADCIEN_Msk;
    if(u32Mask & ADC_KEY_INT)
        ADC->INTCTL |= ADC_INTCTL_KEYIEN_Msk;
}

/**
  * @brief                      Disable the interrupt(s) selected by u32Mask parameter.
  * @param[in]  adc             Base address of ADC module
  * @param[in]  u32Mask         The combination of interrupt status bits listed below. Each bit\n
  *                             corresponds to a interrupt status. This parameter decides which
  *                             interrupts will be disabled.
  *                             - \ref ADC_ADF_INT
  *                             - \ref ADC_KEY_INT
  * @return      None
  */
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask)
{
    (void)adc;
    if(u32Mask & ADC_ADF_INT)
        ADC->INTCTL &= ~ADC_INTCTL_ADCIEN_Msk;
    if(u32Mask & ADC_KEY_INT)
        ADC->INTCTL &= ~ADC_INTCTL_KEYIEN_Msk;
}



/*@}*/ /* end of group NUC505_ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_ADC_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
