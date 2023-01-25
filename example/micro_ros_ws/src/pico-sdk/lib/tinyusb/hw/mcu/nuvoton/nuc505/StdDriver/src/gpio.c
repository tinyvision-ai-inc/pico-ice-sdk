/**************************************************************************//**
 * @file     gpio.c
 * @version  V1.00
 * $Revision: 8 $
 * $Date: 14/05/29 1:13p $
 * @brief    NUC505 GPIO driver source file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NUC505Series.h"


static uint32_t volatile * const s_pu32INTEN[4] = {&PA->INTEN, &PB->INTEN, &PC->INTEN, &PD->INTEN};
static uint32_t volatile * const s_pu32INTSRCGP[4] = {&PA->INTSRCGP, &PB->INTSRCGP, &PC->INTSRCGP, &PD->INTSRCGP};

/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_GPIO_Driver GPIO Driver
  @{
*/


/** @addtogroup NUC505_GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Set GPIO operation mode
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 * @param[in]   u32Mode     Operation mode. It could be \n
 *          - \ref GPIO_MODE_INPUT
 *          - \ref GPIO_MODE_OUTPUT
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetMode(void *gpio, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;
    GPIO_PA_T *p = (GPIO_PA_T *)gpio;

    for (i=0; i<GPIO_PIN_MAX; i++)
    {
        if (u32PinMask & (1 << i))
        {
            p->MODE = (p->MODE & ~(0x1 << i)) | (u32Mode << i);
        }
    }
}

/**
 * @brief       Enable GPIO interrupt
 *
 * @param[in]   gpio            GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32Pin          The pin of specified GPIO port. It could be 0 ~ 15.
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *          - \ref GPIO_INT_RISING
 *          - \ref GPIO_INT_FALLING
 *          - \ref GPIO_INT_BOTH_EDGE
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_EnableInt(void *gpio, uint32_t u32Pin, uint32_t u32IntAttribs)
{
    uint32_t u32Value;
    uint32_t u32Idx;

    GPIO->INTCTL |= GPIO_INTCTL_INTCTL_Msk;
    u32Idx = GPIO_GET_OFFSET((uint32_t)gpio);

    u32Value = *s_pu32INTEN[u32Idx];
    *s_pu32INTEN[u32Idx] = (u32Value & ~(0x00010001 << u32Pin)) | (u32IntAttribs << u32Pin);
}

/**
 * @brief       Disable GPIO interrupt
 *
 * @param[in]   gpio        GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32Pin      The pin of specified GPIO port. It could be 0 ~ 15.
 *
 * @return      None
 *
 * @details     This function is used to disable specified GPIO pin interrupt.
 */
void GPIO_DisableInt(void *gpio, uint32_t u32Pin)
{
    uint32_t u32Idx;

    u32Idx = GPIO_GET_OFFSET((uint32_t)gpio);

    *s_pu32INTEN[u32Idx] &= ~((0x00010001UL) << u32Pin);
}

/**
 * @brief       Set GPIO interrupt group
 *
 * @param[in]   gpio            GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32Pin          The pin of specified GPIO port. It could be 0 ~ 15.
 * @param[in]   u32IntGroup   The interrupt group of specified GPIO pin. It could be \n
 *          - \ref GPIO_INTSRCGP_EINT0
 *          - \ref GPIO_INTSRCGP_EINT1
 *          - \ref GPIO_INTSRCGP_EINT2
 *          - \ref GPIO_INTSRCGP_EINT3
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO pin interrupt group.
 */
void GPIO_SetIntGroup(void *gpio, uint32_t u32Pin, uint32_t u32IntGroup)
{
    uint32_t u32Value;
    uint32_t u32Idx;

    u32Idx = GPIO_GET_OFFSET((uint32_t)gpio);

    u32Value = *s_pu32INTSRCGP[u32Idx];
    *s_pu32INTSRCGP[u32Idx] = (u32Value & ~(0x03 << (u32Pin<<1))) | (u32IntGroup << (u32Pin<<1));
}

/**
 * @brief       Set GPIO pull mode
 *
 * @param[in]   gpio            GPIO port. It could be PA, PB, ... or PD.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port.
 * @param[in]   u32Mode   The pull mode of specified GPIO pin. It could be \n
 *          - \ref GPIO_PULL_DISABLE
 *          - \ref GPIO_PULL_UP_EN
 *          - \ref GPIO_PULL_DOWN_EN
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO pin pull mode.
 */
void GPIO_SetPullMode(void *gpio, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;
    GPIO_PA_T *p = (GPIO_PA_T *)gpio;

    for (i=0; i<GPIO_PIN_MAX; i++)
    {
        if (u32PinMask & (1 << i))
        {
            p->PUEN = (p->PUEN & ~(0x03 << (i << 1))) | (u32Mode << (i << 1));
        }
    }
}

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
void GPIO_ClrIntFlag(void *gpio, uint32_t u32PinMask)
{
    uint32_t i, u32Value, u32Offset;
    u32Offset = GPIO_GET_OFFSET((uint32_t)gpio);
    u32Value = *(__IO uint32_t *) (&GPIO->INTSTSA_B + (u32Offset >> 1));
    for (i=0; i<GPIO_PIN_MAX; i++)
    {
        if (u32PinMask & (1 << i))
        {
            if((u32Offset % 2) == 0)
                u32Value |= ((0x00000001UL) << i);
            else
                u32Value |= ((0x00000001UL) << (i + 16));
        }
    }
    *(__IO uint32_t *) (&GPIO->INTSTSA_B + (u32Offset >> 1)) = u32Value;
}


/*@}*/ /* end of group NUC505_GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_GPIO_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
