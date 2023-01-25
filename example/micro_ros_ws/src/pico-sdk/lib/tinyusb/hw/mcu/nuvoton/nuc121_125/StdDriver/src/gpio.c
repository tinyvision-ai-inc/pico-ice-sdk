/**************************************************************************//**
 * @file     gpio.c
 * @version  V3.00
 * @brief    NUC121 series GPIO driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup GPIO_Driver GPIO Driver
  @{
*/

/** @addtogroup GPIO_EXPORTED_FUNCTIONS GPIO Exported Functions
  @{
*/

/**
 * @brief       Set GPIO operation mode
 *
 * @param[in]   port        GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32PinMask  The single or multiple pins of specified GPIO port. \n
 *                          It could be BIT11 ~ BIT15 for PA. \n
 *                          It could be BIT0 ~ BIT15(exclude BIT11) for PB. \n
 *                          It could be BIT0 ~ BIT13(exclude BIT6、BIT7) for PC. \n
 *                          It could be BIT0 ~ BIT11(exclude BIT6、BIT7) for PD. \n
 *                          It could be BIT0 ~ BIT2 for PE. \n
 *                          It could be BIT0 ~ BIT5 for PF.
 *
 * @param[in]   u32Mode     Operation mode.  It could be \n
 *                          GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_OPEN_DRAIN, GPIO_MODE_QUASI.
 *
 * @return      None
 *
 * @details     This function is used to set specified GPIO operation mode.
 */
void GPIO_SetMode(GPIO_T *port, uint32_t u32PinMask, uint32_t u32Mode)
{
    uint32_t i;

    for (i = 0; i < GPIO_PIN_MAX; i++)
    {
        if (u32PinMask & (1 << i))
        {
            port->MODE = (port->MODE & ~(0x3 << (i << 1))) | (u32Mode << (i << 1));
        }
    }
}

/**
 * @brief       Enable GPIO interrupt
 *
 * @param[in]   port            GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Pin          The pin of specified GPIO port. \n
 *                              It could be 11 ~ 15 for PA. \n
 *                              It could be 0 ~ 15(exclude 11) for PB. \n
 *                              It could be 0 ~ 13(exclude 6、7) for PC. \n
 *                              It could be 0 ~ 11(exclude 6、7) for PD. \n
 *                              It could be 0 ~ 2 for PE. \n
 *                              It could be 0 ~ 5 for PF.
 *
 * @param[in]   u32IntAttribs   The interrupt attribute of specified GPIO pin. It could be \n
 *                              GPIO_INT_RISING, GPIO_INT_FALLING, GPIO_INT_BOTH_EDGE, GPIO_INT_HIGH, GPIO_INT_LOW.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_EnableInt(GPIO_T *port, uint32_t u32Pin, uint32_t u32IntAttribs)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE |= (((u32IntAttribs >> 24) & 0xFFUL) << u32Pin);

    /* Enable interrupt function of specified pin */
    port->INTEN |= ((u32IntAttribs & 0xFFFFFFUL) << u32Pin);
}


/**
 * @brief       Disable GPIO interrupt
 *
 * @param[in]   port            GPIO port. It could be PA, PB, PC, PD, PE or PF.
 * @param[in]   u32Pin          The pin of specified GPIO port. \n
 *                              It could be 11 ~ 15 for PA. \n
 *                              It could be 0 ~ 15(exclude 11) for PB. \n
 *                              It could be 0 ~ 13(exclude 6、7) for PC. \n
 *                              It could be 0 ~ 11(exclude 6、7) for PD. \n
 *                              It could be 0 ~ 2 for PE. \n
 *                              It could be 0 ~ 5 for PF.
 *
 * @return      None
 *
 * @details     This function is used to enable specified GPIO pin interrupt.
 */
void GPIO_DisableInt(GPIO_T *port, uint32_t u32Pin)
{
    /* Configure interrupt mode of specified pin */
    port->INTTYPE &= ~(1UL << u32Pin);

    /* Disable interrupt function of specified pin */
    port->INTEN &= ~((0x00010001UL) << u32Pin);
}


/*@}*/ /* end of group GPIO_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group GPIO_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
