/**************************************************************************//**
 * @file     I2C.h
 * @version  V3.00
 * @brief    NUC121 series I2C driver header file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup I2C_Driver I2C Driver
  @{
*/

/** @addtogroup I2C_EXPORTED_CONSTANTS I2C Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C_CTL constant definitions.                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
#define I2C_CTL_STA_STO_SI        0x38UL /*!< I2C_CTL setting for I2C control bits. It would set STA, STO and SI bits     */
#define I2C_CTL_STA_STO_SI_AA     0x3CUL /*!< I2C_CTL setting for I2C control bits. It would set STA, STO, SI and AA bits */
#define I2C_CTL_STA_SI            0x28UL /*!< I2C_CTL setting for I2C control bits. It would set STA and SI bits          */
#define I2C_CTL_STA_SI_AA         0x2CUL /*!< I2C_CTL setting for I2C control bits. It would set STA, SI and AA bits      */
#define I2C_CTL_STO_SI            0x18UL /*!< I2C_CTL setting for I2C control bits. It would set STO and SI bits          */
#define I2C_CTL_STO_SI_AA         0x1CUL /*!< I2C_CTL setting for I2C control bits. It would set STO, SI and AA bits      */
#define I2C_CTL_SI                0x08UL /*!< I2C_CTL setting for I2C control bits. It would set SI bit                   */
#define I2C_CTL_SI_AA             0x0CUL /*!< I2C_CTL setting for I2C control bits. It would set SI and AA bits           */
#define I2C_CTL_STA               0x20UL /*!< I2C_CTL setting for I2C control bits. It would set STA bit                  */
#define I2C_CTL_STO               0x10UL /*!< I2C_CTL setting for I2C control bits. It would set STO bit                  */
#define I2C_CTL_AA                0x04UL /*!< I2C_CTL setting for I2C control bits. It would set AA bit                   */

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C GCMode constant definitions.                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
#define I2C_GCMODE_ENABLE           1    /*!< Enable  I2C GC Mode                                                         */
#define I2C_GCMODE_DISABLE          0    /*!< Disable I2C GC Mode                                                         */

/*@}*/ /* end of group I2C_EXPORTED_CONSTANTS */

/** @addtogroup I2C_EXPORTED_FUNCTIONS I2C Exported Functions
  @{
*/
/**
 *    @brief        The macro is used to set I2C bus condition at One Time
 *
 *    @param[in]    i2c        Specify I2C port
 *    @param[in]    u8Ctrl     A byte writes to I2C control register
 *
 *    @return       None
 *
 *    @details      Set I2C_CTL register to control I2C bus conditions of START, STOP, SI, ACK.
 *
 *    \hideinitializer
 */
#define I2C_SET_CONTROL_REG(i2c, u8Ctrl) ((i2c)->CTL = ((i2c)->CTL & ~0x3c) | (u8Ctrl))

/**
 *    @brief        The macro is used to set START condition of I2C Bus
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       None
 *
 *    @details      Set the I2C bus START condition in I2C_CTL register.
 *
 *    \hideinitializer
 */
#define I2C_START(i2c)  ((i2c)->CTL = ((i2c)->CTL | I2C_CTL_SI_Msk) | I2C_CTL_STA_Msk)

/**
 *    @brief        The macro is used to set STOP condition of I2C Bus
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       None
 *
 *    @details      Set the I2C bus STOP condition in I2C_CTL register.
 *
 *    \hideinitializer
 */
#define I2C_STOP(i2c)   ((i2c)->CTL = ((i2c)->CTL | I2C_CTL_SI_Msk) | I2C_CTL_STO_Msk)

/**
 *    @brief        The macro is used to wait I2C bus status get ready
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       None
 *
 *    @details      When a new status is presented of I2C bus, the SI flag will be set in I2C_CTL register.
 *
 *    \hideinitializer
 */
#define I2C_WAIT_READY(i2c)     while(!((i2c)->CTL & I2C_CTL_SI_Msk))

/**
 *    @brief        The macro is used to Read I2C Bus Data Register
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       A byte of I2C data register
 *
 *    @details      I2C controller read data from bus and save it in I2CDAT register.
 *
 *    \hideinitializer
 */
#define I2C_GET_DATA(i2c)   ((i2c)->DAT)

/**
 *    @brief        Write a Data to I2C Data Register
 *
 *    @param[in]    i2c         Specify I2C port
 *    @param[in]    u8Data      A byte that writes to data register
 *
 *    @return       None
 *
 *    @details      When write a data to I2C_DAT register, the I2C controller will shift it to I2C bus.
 *
 *    \hideinitializer
 */
#define I2C_SET_DATA(i2c, u8Data) ((i2c)->DAT = (u8Data))

/**
 *    @brief        Get I2C Bus status code
 *
 *    @param[in]    i2c        Specify I2C port
 *
 *    @return       I2C status code
 *
 *    @details      To get this status code to monitor I2C bus event.
 *
 *    \hideinitializer
 */
#define I2C_GET_STATUS(i2c) ((i2c)->STATUS)

/**
 *    @brief        Get Time-out flag from I2C Bus
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @retval       0       I2C Bus time-out is not happened
 *    @retval       1       I2C Bus time-out is happened
 *
 *    @details      When I2C bus occurs time-out event, the time-out flag will be set.
 *
 *    \hideinitializer
 */
#define I2C_GET_TIMEOUT_FLAG(i2c)   ( ((i2c)->TOCTL & I2C_TOCTL_TOIF_Msk) == I2C_TOCTL_TOIF_Msk ? 1:0 )

/**
 *    @brief        To get wake-up flag from I2C Bus
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @retval       0       Chip is not woken-up from power-down mode
 *    @retval       1       Chip is woken-up from power-down mode
 *
 *    @details      I2C bus occurs wake-up event, wake-up flag will be set.
 *
 *    \hideinitializer
 */
#define I2C_GET_WAKEUP_FLAG(i2c) ( ((i2c)->WKSTS & I2C_WKSTS_WKIF_Msk) == I2C_WKSTS_WKIF_Msk ? 1:0  )

/**
 *    @brief        To clear wake-up flag
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @return       None
 *
 *    @details      If wake-up flag is set, use this macro to clear it.
 *
 *    \hideinitializer
 */
#define I2C_CLEAR_WAKEUP_FLAG(i2c)  ((i2c)->WKSTS = I2C_WKSTS_WKIF_Msk)

/**
 *    @brief        To get wake-up address frame ACK done flag from I2C Bus
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @retval       0       The ACK bit cycle of address match frame is not done
 *    @retval       1       The ACK bit cycle of address match frame is done in power-down
 *
 *    @details      I2C bus occurs wake-up event and address frame ACK is done, this flag will be set.
 *
 *    \hideinitializer
 */
#define I2C_GET_WAKEUP_DONE(i2c) ( ((i2c)->WKSTS & I2C_WKSTS_WKAKDONE_Msk) == I2C_WKSTS_WKAKDONE_Msk ? 1:0  )

/**
 *    @brief        To clear address frame ACK done flag
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @return       None
 *
 *    @details      If wake-up done is set, use this macro to clear it.
 *
 *    \hideinitializer
 */
#define I2C_CLEAR_WAKEUP_DONE(i2c)  ((i2c)->WKSTS = I2C_WKSTS_WKAKDONE_Msk)

/**
 *    @brief        To get read/write status bit in address wakeup frame
 *
 *    @param[in]    i2c     Specify I2C port
 *
 *    @retval       0       Write command be record on the address match wakeup frame
 *    @retval       1       Read command be record on the address match wakeup frame.
 *
 *    @details      I2C bus occurs wake-up event and address frame is received, this bit will record read/write status.
 *
 *    \hideinitializer
*/
#define I2C_GET_WAKEUP_WR_STATUS(i2c) ( ((i2c)->WKSTS & I2C_WKSTS_WRSTSWK_Msk) == I2C_WKSTS_WRSTSWK_Msk ? 1:0  )

void I2C_ClearTimeoutFlag(I2C_T *i2c);
void I2C_Close(I2C_T *i2c);
void I2C_Trigger(I2C_T *i2c, uint8_t u8Start, uint8_t u8Stop, uint8_t u8Si, uint8_t u8Ack);
void I2C_DisableInt(I2C_T *i2c);
void I2C_EnableInt(I2C_T *i2c);
uint32_t I2C_GetBusClockFreq(I2C_T *i2c);
uint32_t I2C_SetBusClockFreq(I2C_T *i2c, uint32_t u32BusClock);
uint32_t I2C_GetIntFlag(I2C_T *i2c);
uint32_t I2C_GetStatus(I2C_T *i2c);
uint32_t I2C_Open(I2C_T *i2c, uint32_t u32BusClock);
uint8_t I2C_GetData(I2C_T *i2c);
void I2C_SetSlaveAddr(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddr, uint8_t u8GCMode);
void I2C_SetSlaveAddrMask(I2C_T *i2c, uint8_t u8SlaveNo, uint8_t u8SlaveAddrMask);
void I2C_EnableTimeout(I2C_T *i2c, uint8_t u8LongTimeout);
void I2C_DisableTimeout(I2C_T *i2c);
void I2C_EnableWakeup(I2C_T *i2c);
void I2C_DisableWakeup(I2C_T *i2c);
void I2C_SetData(I2C_T *i2c, uint8_t u8Data);
uint8_t I2C_WriteByte(I2C_T *i2c, uint8_t u8SlaveAddr, const uint8_t data);
uint32_t I2C_WriteMultiBytes(I2C_T *i2c, uint8_t u8SlaveAddr, const uint8_t *data, uint32_t u32wLen);
uint8_t I2C_WriteByteOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, const uint8_t data);
uint32_t I2C_WriteMultiBytesOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, const uint8_t *data, uint32_t u32wLen);
uint8_t I2C_WriteByteTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, const uint8_t data);
uint32_t I2C_WriteMultiBytesTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, const uint8_t *data, uint32_t u32wLen);
uint8_t I2C_ReadByte(I2C_T *i2c, uint8_t u8SlaveAddr);
uint32_t I2C_ReadMultiBytes(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t *rdata, uint32_t u32rLen);
uint8_t I2C_ReadByteOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr);
uint32_t I2C_ReadMultiBytesOneReg(I2C_T *i2c, uint8_t u8SlaveAddr, uint8_t u8DataAddr, uint8_t *rdata, uint32_t u32rLen);
uint8_t I2C_ReadByteTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr);
uint32_t I2C_ReadMultiBytesTwoRegs(I2C_T *i2c, uint8_t u8SlaveAddr, uint16_t u16DataAddr, uint8_t *rdata, uint32_t u32rLen);

/*@}*/ /* end of group I2C_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group I2C_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif
#endif //__I2C_H__

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
