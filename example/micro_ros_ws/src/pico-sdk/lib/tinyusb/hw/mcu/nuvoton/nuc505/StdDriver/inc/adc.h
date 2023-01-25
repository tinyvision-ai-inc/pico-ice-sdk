/**************************************************************************//**
 * @file     adc.h
 * @version  V1.00
 * $Revision: 01 $
 * $Date: 14/07/01 1:13p $
 * @brief    NUC505 ADC driver header file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_ADC_Driver ADC Driver
  @{
*/

/** @addtogroup NUC505_ADC_EXPORTED_CONSTANTS ADC Exported Constants
  @{
*/

#define ADC_CH_0_MASK                    (0UL)                       /*!< ADC channel 0 mask  \hideinitializer */
#define ADC_CH_1_MASK                    (1UL)                       /*!< ADC channel 1 mask  \hideinitializer */
#define ADC_CH_2_MASK                    (2UL)                       /*!< ADC channel 2 mask  \hideinitializer */
#define ADC_CH_3_MASK                    (3UL)                       /*!< ADC channel 3 mask  \hideinitializer */
#define ADC_CH_4_MASK                    (4UL)                       /*!< ADC channel 4 mask  \hideinitializer */
#define ADC_CH_5_MASK                    (5UL)                       /*!< ADC channel 5 mask  \hideinitializer */
#define ADC_CH_6_MASK                    (6UL)                       /*!< ADC channel 6 mask  \hideinitializer */
#define ADC_CH_7_MASK                    (7UL)                       /*!< ADC channel 7 mask  \hideinitializer */

#define ADC_ADF_INT                      (ADC_INTCTL_ADCIF_Msk)      /*!< ADC convert complete interrupt \hideinitializer */
#define ADC_KEY_INT                      (ADC_INTCTL_KEYIF_Msk)      /*!< Key pressing interrupt \hideinitializer */
/*@}*/ /* end of group NUC505_ADC_EXPORTED_CONSTANTS */


/** @addtogroup NUC505_ADC_EXPORTED_FUNCTIONS ADC Exported Functions
  @{
*/

/**
  * @brief                      Get the latest ADC conversion data
  * @param[in]  adc             Base address of ADC module
  * @param[in]  u32ChNum        Useless in NUC505 series
  * @return     Latest ADC conversion data
  * \hideinitializer
  */
#define ADC_GET_CONVERSION_DATA(adc, u32ChNum) (adc->DAT)

/**
  * @brief                      Return the user-specified interrupt flags
  * @param[in]  adc             Base address of ADC module
  * @param[in]  u32Mask         The combination of following interrupt status bits. Each bit corresponds to a interrupt status.
  *                             - \ref ADC_ADF_INT
  *                             - \ref ADC_KEY_INT
  * @return     User specified interrupt flags
  * \hideinitializer
  */
#define ADC_GET_INT_FLAG(adc, u32Mask) (adc->INTCTL & (u32Mask))

/**
  * @brief                      This macro clear the selected interrupt status bits
  * @param[in]  adc             Base address of ADC module
  * @param[in]  u32Mask         The combination of following interrupt status bits. Each bit corresponds to a interrupt status.
  *                             - \ref ADC_ADF_INT
  *                             - \ref ADC_KEY_INT
  * @return     None
  * \hideinitializer
  */
#define ADC_CLR_INT_FLAG(adc, u32Mask) (adc->INTCTL = ((adc->INTCTL & ~(ADC_INTCTL_ADCIF_Msk | ADC_INTCTL_KEYIF_Msk)) | u32Mask))

/**
  * @brief                      Get the busy state of ADC
  * @param[in]  adc             Base address of ADC module
  * @return     busy state of ADC
  * @retval     0: ADC is not busy
  * @retval     1: ADC is busy
  * \hideinitializer
  */
#define ADC_IS_BUSY(adc) (adc->CTL & ADC_CTL_SWTRG_Msk ? 1 : 0)


/**
  * @brief                      Power down ADC module
  * @param[in]  adc             Base address of ADC module
  * @return     None
  * \hideinitializer
  */
#define ADC_POWER_DOWN(adc) (adc->CTL |= ADC_CTL_PD_Msk)

/**
  * @brief                      Power on ADC module
  * @param[in]  adc             Base address of ADC module
  * @return     None
  * \hideinitializer
  */
#define ADC_POWER_ON(adc) (adc->CTL &= ~ADC_CTL_PD_Msk)


/**
  * @brief                      Start the A/D conversion.
  * @param[in]  adc             Base address of ADC module
  * @return     None
  * \hideinitializer
  */
#define ADC_START_CONV(adc) (adc->CTL |= ADC_CTL_SWTRG_Msk)

/**
  * @brief                      Stop the A/D conversion.
  * @param[in]  adc             Base address of ADC module
  * @return     None
  * \hideinitializer
  */
#define ADC_STOP_CONV(adc) (ADC->CTL &= ~ADC_CTL_SWTRG_Msk)



void ADC_Open(ADC_T *adc,
              uint32_t u32InputMode,
              uint32_t u32OpMode,
              uint32_t u32ChMask);
void ADC_Close(ADC_T *adc);
void ADC_EnableHWTrigger(ADC_T *adc,
                         uint32_t u32ChMask,
                         uint32_t u32SampleTime);
void ADC_EnableInt(ADC_T *adc, uint32_t u32Mask);
void ADC_DisableInt(ADC_T *adc, uint32_t u32Mask);



/*@}*/ /* end of group NUC505_ADC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_ADC_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__ADC_H__

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/
