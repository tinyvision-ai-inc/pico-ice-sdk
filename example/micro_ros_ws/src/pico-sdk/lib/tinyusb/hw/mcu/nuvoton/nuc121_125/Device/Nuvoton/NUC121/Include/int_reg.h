/**************************************************************************//**
 * @file     int_reg.h
 * @version  V1.00
 * @brief    INT register definition header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __INT_REG_H__
#define __INT_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup INT Interrupt Source Register (INT)
    Memory Mapped Structure for INT Controller
@{ */

typedef struct
{
    /**
     * @var INT_T::IRQ_SRC
     * Offset: 0x00~0x7C  IRQ0~31 Interrupt Source Identity
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |INT_SRC   |Interrupt Source
     * |        |          |Define the interrupt sources for interrupt event.
     * @var INT_T::NMI_SEL
     * Offset: 0x80  NMI Source Interrupt Select Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |NMI_SEL   |NMI Interrupt Source Selection
     * |        |          |The NMI interrupt to Cortex-M0 can be selected from one of the peripheral interrupt by setting NMI_SEL.
     * |[8]     |NMI_EN    |NMI Interrupt Enable Bit (Write Protect)
     * |        |          |0 = NMI interrupt Disabled.
     * |        |          |1 = NMI interrupt Enabled.
     * |        |          |Note: This bit is the protected bit, and programming it needs to write "59h", "16h", and "88h" to address 0x5000_0100 to disable register protection
     * |        |          |Refer to the register REGWRPROT at address GCR_BA+0x100.
     * @var INT_T::MCU_IRQ
     * Offset: 0x84  MCU Interrupt Request Source Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MCU_IRQ   |MCU IRQ Source Register
     * |        |          |The MCU_IRQ collects all the interrupts from the peripherals and generates the synchronous interrupt to Cortex-M0
     * |        |          |There are two modes to generate interrupt to Cortex-M0, the normal mode and test mode.
     * |        |          |The MCU_IRQ collects all interrupts from each peripheral and synchronizes them and interrupts the Cortex-M0.
     * |        |          |When the MCU_IRQ[n] is 0: Set MCU_IRQ[n] 1 will generate an interrupt to Cortex-M0 NVIC[n].
     * |        |          |When the MCU_IRQ[n] is 1 (mean an interrupt is assert), setting 1 to the MCU_IRQ[n] 1 will clear the interrupt and setting MCU_IRQ[n] 0: has no effect
     * @var INT_T::MCU_IRQCR
     * Offset: 0x88  MCU Interrupt Request Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FAST_IRQ  |Fast IRQ Latency Enable Bit
     * |        |          |0 = MCU IRQ latency is fixed at 13 clock cycles of HCLK, MCU will enter IRQ handler after this fixed latency when interrupt happened.
     * |        |          |1 = MCU IRQ latency will not fixed, MCU will enter IRQ handler as soon as possible when interrupt happened.
     */
    __I  uint32_t IRQ_SRC[32];           /*!< [0x0000~0x007c] IRQ0~31 Interrupt Source Identity                         */
    __IO uint32_t NMI_SEL;               /*!< [0x0080] NMI Source Interrupt Select Control Register                     */
    __IO uint32_t MCU_IRQ;               /*!< [0x0084] MCU Interrupt Request Source Register                            */
    __IO uint32_t MCU_IRQCR;             /*!< [0x0088] MCU Interrupt Request Control Register                           */
} INT_T;

/**
    @addtogroup INT_CONST INT Bit Field Definition
    Constant Definitions for INT Controller
@{ */

#define INT_IRQ_SRC_INT_SRC_Pos              (0)                                               /*!< INT_T::SRC: INT_SRC Position           */
#define INT_IRQ_SRC_INT_SRC_Msk              (0xful << INT_IRQ_SRC_INT_SRC_Pos)                /*!< INT_T::SRC: INT_SRC Mask               */

#define INT_NMI_SEL_NMI_SEL_Pos              (0)                                               /*!< INT_T::SEL: NMI_SEL Position           */
#define INT_NMI_SEL_NMI_SEL_Msk              (0x1ful << INT_NMI_SEL_NMI_SEL_Pos)               /*!< INT_T::SEL: NMI_SEL Mask               */

#define INT_NMI_SEL_NMI_EN_Pos               (8)                                               /*!< INT_T::SEL: NMI_EN Position            */
#define INT_NMI_SEL_NMI_EN_Msk               (0x1ul << INT_NMI_SEL_NMI_EN_Pos)                 /*!< INT_T::SEL: NMI_EN Mask                */

#define INT_MCU_IRQ_MCU_IRQ_Pos              (0)                                               /*!< INT_T::IRQ: MCU_IRQ Position           */
#define INT_MCU_IRQ_MCU_IRQ_Msk              (0xfffffffful << INT_MCU_IRQ_MCU_IRQ_Pos)         /*!< INT_T::IRQ: MCU_IRQ Mask               */

#define INT_MCU_IRQCR_FAST_IRQ_Pos           (0)                                               /*!< INT_T::IRQCR: FAST_IRQ Position        */
#define INT_MCU_IRQCR_FAST_IRQ_Msk           (0x1ul << INT_MCU_IRQCR_FAST_IRQ_Pos)             /*!< INT_T::IRQCR: FAST_IRQ Mask            */

/**@}*/ /* INT_CONST */
/**@}*/ /* end of INT register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __INT_REG_H__ */
