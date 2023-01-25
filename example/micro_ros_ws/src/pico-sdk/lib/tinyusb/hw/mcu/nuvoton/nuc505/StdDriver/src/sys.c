/*************************************************************************//**
 * @file     sys.c
 * @version  V1.00
 * $Revision: 12 $
 * $Date: 14/07/01 1:13p $
 * @brief    NUC505 SYS driver source file
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "NUC505Series.h"

#include "sys.h"
/** @addtogroup NUC505_Device_Driver NUC505 Device Driver
  @{
*/

/** @addtogroup NUC505_SYS_Driver SYS Driver
  @{
*/


/** @addtogroup NUC505_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief                                This function get product ID.
  * @return       Product ID
  */
uint32_t  SYS_ReadPDID(void)
{
    return SYS->PDID & SYS_PDID_PDID_Msk;
}


/**
  * @brief                      This function is used to change booting device.
  * @param[in]  u32BootSrc        System boot source device
  *                             - \ref SYS_BOOT_ICE_ESPI
  *                             - \ref SYS_BOOT_ICE_SPI
  *                             - \ref SYS_BOOT_ICP
  *                             - \ref SYS_BOOT_ESPI
  *                             - \ref SYS_BOOT_USB
  *                             - \ref SYS_BOOT_SPI
  * @return     None
  */
void SYS_BootSrc(uint32_t u32BootSrc)
{
    SYS->BOOTSET = u32BootSrc;
}

/**
  * @brief                      This function reset chip.
  * @return     None
  */
void SYS_ResetChip(void)
{
    SYS->IPRST0 |= SYS_IPRST0_CHIPRST_Msk;
}

/**
  * @brief                      This function reset CPU.
  * @return     None
  */
void SYS_ResetCPU(void)
{
    SYS->IPRST0 |= SYS_IPRST0_CPURST_Msk;
}

/**
  * @brief                                          This function reset selected modules.
  * @param[in]  u32ModuleIndex  Module index. Valid values include:
  *                             - \ref CHIP_RST
  *                             - \ref CPU_RST
  *                             - \ref UART0_RST
  *                             - \ref UART1_RST
  *                             - \ref TMR0_RST
  *                             - \ref TMR1_RST
  *                             - \ref WDTF_RST
  *                             - \ref TMR2_RST
  *                             - \ref UART2_RST
  *                             - \ref PWM_RST
  *                             - \ref I2C0_RST
  *                             - \ref I2C1_RST
  *                             - \ref SPIM_RST
  *                             - \ref USBD_RST
  *                             - \ref WDTP_RST
  *                             - \ref MTP_RST
  *                             - \ref I2S_RST
  *                             - \ref USBH_RST
  *                             - \ref SDH_RST
  *                             - \ref SRAM_RST
  *                             - \ref GPIO_RST
  *                             - \ref ADC_RST
  *                             - \ref SPI0_RST
  *                             - \ref SPI1_RST
  * @return         None
  */
void SYS_ResetModule(uint32_t u32ModuleIndex)
{
    *(volatile uint32_t *)((uint32_t)&(SYS->IPRST0) + (u32ModuleIndex>>24)) |= 1<<(u32ModuleIndex & 0x00ffffff);
    *(volatile uint32_t *)((uint32_t)&(SYS->IPRST0) + (u32ModuleIndex>>24)) &= ~(1<<(u32ModuleIndex & 0x00ffffff));
}

/**
  * @brief                                This function get the system reset source register value
  * @return                               Reset source
    * @details      The return could be union of following items
    *                             - \ref SYS_RSTSTS_RST
  *                             - \ref SYS_RSTSTS_LVR
  *                             - \ref SYS_RSTSTS_WDT
  *                             - \ref SYS_RSTSTS_CPU
  *                             - \ref SYS_RSTSTS_POR
  */
uint32_t SYS_GetResetSrc(void)
{
    return (SYS->RSTSTS);
}

/**
  * @brief                      This function clear the selected system reset source
  * @param[in]  u32Src          System reset source
  *                             - \ref SYS_RSTSTS_RST
  *                             - \ref SYS_RSTSTS_LVR
  *                             - \ref SYS_RSTSTS_WDT
  *                             - \ref SYS_RSTSTS_CPU
  *                             - \ref SYS_RSTSTS_POR
  * @return         None
  */
void SYS_ClearResetSrc(uint32_t u32Src)
{
    SYS->RSTSTS |= u32Src;
}

/**
  * @brief                                          This function is used to configure LVD function.
  * @param[in]  u32Enable           Enable or disable LVD. Including :
  *                                                 - \ref SYS_LVD_ENABLE
  *                                                 - \ref SYS_LVD_DISABLE
  * @param[in]  u32Level                LVD detection voltage level. Including :
  *                                                 - \ref SYS_LVD_2_6V
  *                                                 - \ref SYS_LVD_2_8V
  *
  * @return         None
  */
void SYS_EnableLVD(uint32_t u32Enable, uint32_t u32Level)
{
    uint32_t u32Reg = SYS->LVDCTL;
    if(u32Enable==SYS_LVD_ENABLE)
        u32Reg = u32Reg| SYS_LVD_ENABLE;
    else
        u32Reg = u32Reg & ~SYS_LVD_ENABLE;
    if(u32Level==SYS_LVD_2_8V)
        SYS->LVDCTL = u32Reg | SYS_LVD_2_8V;
    else
        SYS->LVDCTL = u32Reg & ~SYS_LVD_2_8V;
}

/**
  * @brief                      This function disable LVD function.
  * @return         None
  */
void SYS_DisableLVD(void)
{
    SYS->LVDCTL = SYS->LVDCTL & ~SYS_LVD_ENABLE;
}

/**
  * @brief                                        This function remap the specified physical memory space to virtual memory space 0.
  * @param[in]  u32Address        Remapped physical address.
  * @param[in]  u32Len                Remapped physical length. Unit is KB. Range from 0~0x0FF.
  * @return         None
  */
void SYS_RemapPhysicalAddress(uint32_t u32Address, uint32_t u32Len)
{
    SYS->LVMPADDR = u32Address;
    SYS->LVMPLEN = u32Len;
    SYS->RVMPLEN = SYS->RVMPLEN | SYS_RVMPLEN_RLDVMP_Msk;
}

/**
  * @brief                      This function sets driving strength of GPA[7:0]/GPD[4:2] that are analog and digital shared pins.
  * @param[in]  u32Port         General purpose IO port. Valid values include:
  *                             - \ref SYS_PORT_A
  *                             - \ref SYS_PORT_D
  * @param[in]  u32Pin          General purpose IO pin. Valid values include:
  *                             - \ref SYS_PIN_0
  *                             - \ref SYS_PIN_1
  *                             - \ref SYS_PIN_2
  *                             - \ref SYS_PIN_3
  *                             - \ref SYS_PIN_4
  *                             - \ref SYS_PIN_5
  *                             - \ref SYS_PIN_6
  *                             - \ref SYS_PIN_7
    * @param[in]  u32DrivingLevel Driving strength
  *                             - \ref SYS_DRIVING_STRENGTH_2MA
  *                             - \ref SYS_DRIVING_STRENGTH_6P5MA
  *                             - \ref SYS_DRIVING_STRENGTH_8P7MA
  *                             - \ref SYS_DRIVING_STRENGTH_13MA
  *                             - \ref SYS_DRIVING_STRENGTH_15P2MA
  *                             - \ref SYS_DRIVING_STRENGTH_19P5MA
  *                             - \ref SYS_DRIVING_STRENGTH_21P7MA
  *                             - \ref SYS_DRIVING_STRENGTH_26P1MA
  * @return None
  */
void SYS_SharedPinDrivingStrangth(uint32_t u32Port, uint32_t u32Pin, uint32_t u32DrivingLevel)
{
    if(u32DrivingLevel>7)
        return;
    if( u32Port == SYS_PORT_A ) //GPA
    {
        if(u32Pin>7)//Only GPA[7:0] support driving strength
            return;
        SYS->GPADS = (SYS->GPADS & ~(7<<(u32Pin*4))) | (u32DrivingLevel <<(u32Pin*4));
    }
    else if( u32Port == SYS_PORT_D )  //GPD
    {
        if( (u32Pin>4) || (u32Pin<2))//Only GPD[4:2] support driving strength
            return;
        SYS->GPDDS = (SYS->GPDDS & ~(7<<((u32Pin-2)*4))) | (u32DrivingLevel <<((u32Pin-2)*4));
    }

}

/**
  * @brief                      This function is used to set analog and digital shared pin input type.
  *                             Analog and digital shared pin means GPA[7:0] or GPD[4:2].
  * @param[in]  u32Port         General purpose IO port. Valid values include:
  *                             - \ref SYS_PORT_A
  *                             - \ref SYS_PORT_D
  * @param[in]  u32Pin          General purpose IO pin. Valid values include:
  *                             - \ref SYS_PIN_0
  *                             - \ref SYS_PIN_1
  *                             - \ref SYS_PIN_2
  *                             - \ref SYS_PIN_3
  *                             - \ref SYS_PIN_4
  *                             - \ref SYS_PIN_5
  *                             - \ref SYS_PIN_6
  *                             - \ref SYS_PIN_7
  * @param[in]  u32InputType    Specified pin for analog input pin or digital pin.
    *                             0 : Analog pin.
    *                             1 : Digital pin.
  * @param[in]  u32BufferType   The parameter is valid if specified pin is digital pin.
    *                             0 : CMOS Input Buffer.
    *                             1 : Schmitt Trigger Input Buffer.
  * @return None
  */
void SYS_SetSharedPinType(uint32_t u32Port, uint32_t u32Pin, uint32_t u32InputType, uint32_t u32BufferType)
{
    if( u32Port == SYS_PORT_A )     /* GPA */
    {
        if(u32Pin>7)    /* Only GPA[7:0] support driving strength */
            return;
        if(u32InputType>1)
            return;

        if(u32InputType==0) /* Analog input */
        {
            SYS->GPAIBE = (SYS->GPAIBE & ~((1<<u32Pin)<<16));
            return;
        }
        else    /* Digital input */
        {
            SYS->GPAIBE = (SYS->GPAIBE | ((1<<u32Pin)<<16));
            if(u32BufferType>1)
                return;
            if(u32BufferType)   /* Buffer type: Schmitt Trigger Input Type */
                SYS->GPAIBE = (SYS->GPAIBE | (1<<u32Pin));
            else                /* Buffer type: CMOS Input Type */
                SYS->GPAIBE = (SYS->GPAIBE & ~(1<<u32Pin));
        }
    }
    else if(u32Port == SYS_PORT_D)  /* GPD */
    {
        if( (u32Pin>4) || (u32Pin<2))/* Only GPD[4:2] support driving strength */
            return;
        if(u32InputType>1)
            return;
        if(u32InputType==0) /* Analog input */
        {
            SYS->GPDIBE = (SYS->GPDIBE & ~((1<<u32Pin)<<16));
            return;
        }
        else    /*Digital input*/
        {
            SYS->GPDIBE = (SYS->GPAIBE | ((1<<u32Pin)<<16));
            if(u32BufferType>1)
                return;
            if(u32BufferType)   /* Buffer type: Schmitt Trigger Input Type */
                SYS->GPDIBE = (SYS->GPDIBE | (1<<u32Pin));
            else                /* Buffer type: CMOS Input Type */
                SYS->GPDIBE = (SYS->GPDIBE & ~(1<<u32Pin));
        }
    }
}

/**
  * @brief  This function selects digital pin input type: GPA[15:8], GPB[15:0], GPC[14:0] and GPD[1:0] are digital pins only.
  * @param[in]  u32Port     General purpose IO port. Valid values include:
  *                             - \ref SYS_PORT_A
  *                             - \ref SYS_PORT_B
  *                             - \ref SYS_PORT_C
  *                             - \ref SYS_PORT_D
  * @param[in]  u32Pin      General purpose IO pin. Valid values include:
  *                             - \ref SYS_PIN_0
  *                             - \ref SYS_PIN_1
  *                             - \ref SYS_PIN_2
  *                             - \ref SYS_PIN_3
  *                             - \ref SYS_PIN_4
  *                             - \ref SYS_PIN_5
  *                             - \ref SYS_PIN_6
  *                             - \ref SYS_PIN_7
  *                             - \ref SYS_PIN_8
  *                             - \ref SYS_PIN_9
  *                             - \ref SYS_PIN_10
  *                             - \ref SYS_PIN_11
  *                             - \ref SYS_PIN_12
  *                             - \ref SYS_PIN_13
  *                             - \ref SYS_PIN_14
  *                             - \ref SYS_PIN_15
  * @param[in]  u32BufferType   General purpose IO pin input buffer type
    *                             0 : CMOS Input Buffer.
  *                             1 : Schmitt Trigger Input Buffer.
  * @return     None
  */
void SYS_SetDigitalPinInputType(uint32_t u32Port, uint32_t u32Pin, uint32_t u32BufferType)
{
    uint32_t u32Offset = 0;
    if(u32BufferType>1)
        return;
    if( u32Port == SYS_PORT_A ) /* GPA */
    {
        if((u32Pin>15)||(u32Pin<8))/* GPA[15:8] support input buffer select */
            return;
    }
    else if( u32Port == SYS_PORT_B )  /* GPB */
    {
        if(u32Pin>15)/* GPB[15:0] support input buffer select */
            return;
        u32Offset = 0x04;
    }
    else if( u32Port == SYS_PORT_C )  /* GPC */
    {
        if(u32Pin>14)/* GPC[14:0] support input buffer select */
            return;
        u32Offset = 0x08;
    }
    else  //GPD
    {
        if(u32Pin>2)/* GPD[1:0] support input buffer select */
            return;
        if(u32BufferType>1)
            return;
        u32Offset = 0x0C;
    }
    if(u32BufferType==0)    /* CMOS Input Type */
    {
        uint32_t addr = (uint32_t)&SYS->GPAIBE+u32Offset;
        *(volatile uint32_t *)(addr) = *(volatile uint32_t *)(addr) | (1<<u32Pin);
        *(volatile uint32_t *)(addr) = *(volatile uint32_t *)(addr) & ~((1<<u32Pin)<<16);
        return;
    }
    else                    /* Schmitt Trigger Input Type */
    {
        uint32_t addr = (uint32_t)&SYS->GPAIBE+u32Offset;
        *(volatile uint32_t *)(addr) = *(volatile uint32_t *)(addr) & ~(1<<u32Pin);
        *(volatile uint32_t *)(addr) = *(volatile uint32_t *)(addr) | ((1<<u32Pin)<<16);
    }
}

/*@}*/ /* end of group NUC505_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC505_SYS_Driver */

/*@}*/ /* end of group NUC505_Device_Driver */

/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/

