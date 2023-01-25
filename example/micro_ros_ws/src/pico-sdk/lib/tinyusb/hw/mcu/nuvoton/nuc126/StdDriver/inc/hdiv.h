/**************************************************************************//**
 * @file     hdiv.h
 * @version  V3.0
 * $Revision: 4 $
 * $Date: 16/10/25 4:25p $
 * @brief    NUC126 series Hardware Divider(HDIV) driver header file
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __HDIV_H__
#define __HDIV_H__

#include "NUC126.h"

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup HDIV_Driver HDIV Driver
  @{
*/

/** @addtogroup HDIV_EXPORTED_FUNCTIONS HDIV Exported Functions
  @{
*/

/**
 * @brief      Division function to calculate (x/y)
 *
 * @param[in]  x the dividend of the division
 * @param[in]  y the divisor of the division
 *
 * @return     The result of (x/y)
 *
 * @details    This is a division function to calculate x/y
 *
 */
static __INLINE int32_t HDIV_Div(int32_t x, int16_t y)
{
    uint32_t *p32;

    p32 = (uint32_t *)HDIV_BASE;
    *p32++ = x;
    *p32++ = y;
    return *p32;
}


/**
 * @brief      To calculate the remainder of x/y, i.e., the result of x mod y.
 *
 * @param[in]  x the dividend of the division
 * @param[in]  y the divisor of the division
 *
 * @return     The remainder of (x/y)
 *
 * @details    This function is used to calculate the remainder of x/y.
 */
static __INLINE int16_t HDIV_Mod(int32_t x, int16_t y)
{
    uint32_t *p32;

    p32 = (uint32_t *)HDIV_BASE;
    *p32++ = x;
    *p32++ = y;
    return p32[1];
}

/*@}*/ /* end of group HDIV_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group HDIV_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif //__HDIV_H__

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/


