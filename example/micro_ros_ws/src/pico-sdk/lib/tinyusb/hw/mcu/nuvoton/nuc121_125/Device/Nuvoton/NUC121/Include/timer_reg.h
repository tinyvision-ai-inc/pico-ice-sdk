/**************************************************************************//**
 * @file     timer_reg.h
 * @version  V1.00
 * @brief    TIMER register definition header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __TIMER_REG_H__
#define __TIMER_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup TIMER Timer Controller (TIMER)
    Memory Mapped Structure for TIMER Controller
@{ */

typedef struct
{
    /**
     * @var TIMER_T::CTL
     * Offset: 0x00/0x20  Timer0~3 Control and Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PSC       |Prescale Counter
     * |        |          |Timer input clock or event source is divided by (PSC+1) before it is fed to the timer up counter
     * |        |          |If this field is 0 (PSC = 0), then there is no scaling.
     * |[8]     |TRGPDMA   |Trigger DAC Enable Bit
     * |        |          |If this bit is set to 1, timer time-out interrupt or capture interrupt can trigger PDMA.
     * |        |          |0 = Timer interrupt trigger PDMA Disabled.
     * |        |          |1 = Timer interrupt trigger PDMA Enabled.
     * |        |          |Note: If TRGSSEL (TIMERx_CTL[18]) = 0, time-out interrupt signal will trigger PDMA.
     * |        |          |If TRGSSEL (TIMERx_CTL[18]) = 1, capture interrupt signal will trigger PDMA.
     * |[9]     |TRGBPWM   |Trigger DAC Enable Bit
     * |        |          |If this bit is set to 1, timer time-out interrupt or capture interrupt can trigger BPWM.
     * |        |          |0 = Timer interrupt trigger BPWM Disabled.
     * |        |          |1 = Timer interrupt trigger BPWM Enabled.
     * |        |          |Note: If TRGSSEL (TIMERx_CTL[18]) = 0, time-out interrupt signal will trigger BPWM.
     * |        |          |If TRGSSEL (TIMERx_CTL[18]) = 1, capture interrupt signal will trigger BPWM.
     * |[18]    |TRGSSEL   |Trigger Source Select Bit
     * |        |          |This bit is used to select trigger source from Timer time-out interrupt signal or capture interrupt signal.
     * |        |          |0 = Timer time-out interrupt signal is used to trigger PWM, BPWM, PDMA,ADC and DAC.
     * |        |          |1 = Capture interrupt signal is used to trigger PWM, BPWM, PDMA, ADC and DAC.
     * |[19]    |TRGPWM    |Trigger PWM Enable Bit
     * |        |          |If this bit is set to 1, timer time-out interrupt or capture interrupt can trigger PWM.
     * |        |          |0 = Timer interrupt trigger PWM Disabled.
     * |        |          |1 = Timer interrupt trigger PWM Enabled.
     * |        |          |Note: If TRGSSEL (TIMERx_CTL[18]) = 0, time-out interrupt signal will trigger PWM.
     * |        |          |If TRGSSEL (TIMERx_CTL[18]) = 1, capture interrupt signal will trigger PWM.
     * |[21]    |TRGADC    |Trigger ADC Enable Bit
     * |        |          |If this bit is set to 1, timer time-out interrupt or capture interrupt can trigger ADC.
     * |        |          |0 = Timer interrupt trigger ADC Disabled.
     * |        |          |1 = Timer interrupt trigger ADC Enabled.
     * |        |          |Note: If TRGSSEL (TIMERx_CTL[18]) = 0, time-out interrupt signal will trigger ADC.
     * |        |          |If TRGSSEL (TIMERx_CTL[18]) = 1, capture interrupt signal will trigger ADC.
     * |[22]    |TGLPINSEL |Toggle-output Pin Select
     * |        |          |0 = Toggle mode output to Tx (Timer Event Counter Pin).
     * |        |          |1 = Toggle mode output to Tx_EXT (Timer External Capture Pin).
     * |[23]    |WKEN      |Wake-up Function Enable Bit
     * |        |          |If this bit is set to 1, while timer interrupt flag TIF (TIMERx_INTSTS[0]) is 1 and INTEN (TIMERx_CTL[29]) is enabled, the timer interrupt signal will generate a wake-up trigger event to CPU.
     * |        |          |0 = Wake-up function Disabled if timer interrupt signal generated.
     * |        |          |1 = Wake-up function Enabled if timer interrupt signal generated.
     * |[24]    |EXTCNTEN  |Event Counter Mode Enable Bit
     * |        |          |This bit is for external counting pin function enabled.
     * |        |          |0 = Event counter mode Disabled.
     * |        |          |1 = Event counter mode Enabled.
     * |        |          |Note: When timer is used as an event counter, this bit should be set to 1 and select PCLK as timer clock source.
     * |[25]    |ACTSTS    |Timer Active Status Bit (Read Only)
     * |        |          |This bit indicates the 24-bit up counter status.
     * |        |          |0 = 24-bit up counter is not active.
     * |        |          |1 = 24-bit up counter is active.
     * |[26]    |RSTCNT    |Timer Counter Reset Bit
     * |        |          |Setting this bit will reset the 24-bit up counter value CNT (TIMERx_CNT[23:0]) and also force CNTEN (TIMERx_CTL[30]) to 0 if ACTSTS (TIMERx_CTL[25]) is 1.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset internal 8-bit prescale counter, 24-bit up counter value and CNTEN bit.
     * |[28:27] |OPMODE    |Timer Operating Mode Select
     * |        |          |00 = The Timer controller is operated in One-shot mode.
     * |        |          |01 = The Timer controller is operated in Periodic mode.
     * |        |          |10 = The Timer controller is operated in Toggle-output mode.
     * |        |          |11 = The Timer controller is operated in Continuous Counting mode.
     * |[29]    |INTEN     |Timer Interrupt Enable Bit
     * |        |          |0 = Timer Interrupt Disabled.
     * |        |          |1 = Timer Interrupt Enabled.
     * |        |          |Note: If this bit is enabled, when the timer interrupt flag TIF is set to 1, the timer interrupt signal is generated and inform to CPU.
     * |[30]    |CNTEN     |Timer Counting Enable Bit
     * |        |          |0 = Stops/Suspends counting.
     * |        |          |1 = Starts counting.
     * |        |          |Note1: In stop status, and then set CNTEN to 1 will enable the 24-bit up counter to keep counting from the last stop counting value.
     * |        |          |Note2: This bit is auto-cleared by hardware in one-shot mode (TIMER_CTL[28:27] = 00) when the timer interrupt flag TIF (TIMERx_INTSTS[0]) is generated.
     * |[31]    |ICEDEBUG  |ICE Debug Mode Acknowledge Disable (Write Protect)
     * |        |          |0 = ICE debug mode acknowledgement affects TIMER counting.
     * |        |          |TIMER counter will be held while CPU is held by ICE.
     * |        |          |1 = ICE debug mode acknowledgement Disabled.
     * |        |          |TIMER counter will keep going no matter CPU is held by ICE or not.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var TIMER_T::CMP
     * Offset: 0x04/0x24  Timer0~3 Compare Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |CMPDAT    |Timer Compared Value
     * |        |          |CMPDAT is a 24-bit compared value register
     * |        |          |When the internal 24-bit up counter value is equal to CMPDAT value, the TIF (TIMERx_INTSTS[0] Timer Interrupt Flag) will set to 1.
     * |        |          |Time-out period = (Period of timer clock input) * (8-bit PSC + 1) * (24-bit CMPDAT).
     * |        |          |Note1: Never write 0x0 or 0x1 in CMPDAT field, or the core will run into unknown state.
     * |        |          |Note2: When timer is operating at continuous counting mode, the 24-bit up counter will keep counting continuously even if user writes a new value into CMPDAT field
     * |        |          |But if timer is operating at other modes, the 24-bit up counter will restart counting from 0 and using newest CMPDAT value to be the timer compared value while user writes a new value into CMPDAT field.
     * @var TIMER_T::INTSTS
     * Offset: 0x08/0x28  Timer0~3 Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TIF       |Timer Interrupt Flag
     * |        |          |This bit indicates the interrupt flag status of Timer while 24-bit timer up counter CNT (TIMERx_CNT[23:0]) value reaches to CMPDAT (TIMERx_CMP[23:0]) value.
     * |        |          |0 = No effect.
     * |        |          |1 = CNT value matches the CMPDAT value.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * |[1]     |TWKF      |Timer Wake-up Flag
     * |        |          |This bit indicates the interrupt wake-up flag status of timer.
     * |        |          |0 = Timer does not cause CPU wake-up.
     * |        |          |1 = CPU wake-up from Idle or Power-down mode if timer time-out interrupt signal generated.
     * |        |          |Note: This bit is cleared by writing 1 to it.
     * @var TIMER_T::CNT
     * Offset: 0x0C/0x2C  Timer0~3 Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |CNT       |Timer Data Register
     * |        |          |This field can be reflected the internal 24-bit timer counter value or external event input counter value from Tx (x=0~3) pin.
     * |        |          |If EXTCNTEN (TIMERx_CTL[24] ) is 0, user can read CNT value to get current 24- bit counter value .
     * |        |          |If EXTCNTEN (TIMERx_CTL[24] ) is 1, user can read CNT value to get current 24- bit event input counter value.
     * @var TIMER_T::CAP
     * Offset: 0x10/0x30  Timer0~3 Capture Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[23:0]  |CAPDAT    |Timer Capture Data Register
     * |        |          |When CAPEN (TIMERx_EXTCTL[3]) bit is set, CAPFUNCS (TIMERx_EXTCTL[4]) bit is 0, and a transition on Tx_EXT pin is matched with the CAPEDGE (TIMERx_EXTCTL[2:1]) setting, CAPIF (TIMERx_EINTSTS[0]) will set to 1 and the current timer counter value CNT (TIMERx_CNT[23:0]) will be auto-loaded into this CAPDAT field.
     * @var TIMER_T::EXTCTL
     * Offset: 0x14/0x34  Timer0~3 External Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CNTPHASE  |Timer External Count Phase
     * |        |          |This bit indicates the detection phase of external counting pin Tx (x= 0~3).
     * |        |          |0 = A Falling edge of external counting pin will be counted.
     * |        |          |1 = A Rising edge of external counting pin will be counted.
     * |[2:1]   |CAPEDGE   |Timer External Capture Pin Edge Detect
     * |        |          |00 = A Falling edge on Tx_EXT (x= 0~3) pin will be detected.
     * |        |          |01 = A Rising edge on Tx_EXT (x= 0~3) pin will be detected.
     * |        |          |10 = Either Rising or Falling edge on Tx_EXT (x= 0~3) pin will be detected.
     * |        |          |11 = Reserved.
     * |[3]     |CAPEN     |Timer External Capture Pin Enable
     * |        |          |This bit enables the Tx_EXT pin.
     * |        |          |0 =Tx_EXT (x= 0~3) pin Disabled.
     * |        |          |1 =Tx_EXT (x= 0~3) pin Enabled.
     * |[4]     |CAPFUNCS  |Capture Function Selection
     * |        |          |0 = External Capture Mode Enabled.
     * |        |          |1 = External Reset Mode Enabled.
     * |        |          |Note1: When CAPFUNCS is 0, transition on Tx_EXT (x= 0~3) pin is using to save the 24-bit timer counter value.
     * |        |          |Note2: When CAPFUNCS is 1, transition on Tx_EXT (x= 0~3) pin is using to reset the 24-bit timer counter value.
     * |[5]     |CAPIEN    |Timer External Capture Interrupt Enable Bit
     * |        |          |0 = Tx_EXT (x= 0~3) pin detection Interrupt Disabled.
     * |        |          |1 = Tx_EXT (x= 0~3) pin detection Interrupt Enabled.
     * |        |          |Note: CAPIEN is used to enable timer external interrupt
     * |        |          |If CAPIEN enabled, timer will rise an interrupt when CAPIF (TIMERx_EINTSTS[0]) is 1.
     * |        |          |For example, while CAPIEN = 1, CAPEN = 1, and CAPEDGE = 00, a 1 to 0 transition on the Tx_EXT pin will cause the CAPIF to be set then the interrupt signal is generated and sent to NVIC to inform CPU.
     * |[6]     |CAPDBEN   |Timer External Capture Pin De-bounce Enable Bit
     * |        |          |0 = Tx_EXT (x= 0~3) pin de-bounce Disabled.
     * |        |          |1 = Tx_EXT (x= 0~3) pin de-bounce Enabled.
     * |        |          |Note: If this bit is enabled, the edge detection of Tx_EXT pin is detected with de-bounce circuit.
     * |[7]     |CNTDBEN   |Timer Counter Pin De-bounce Enable Bit
     * |        |          |0 = Tx (x= 0~3) pin de-bounce Disabled.
     * |        |          |1 = Tx (x= 0~3) pin de-bounce Enabled.
     * |        |          |Note: If this bit is enabled, the edge detection of Tx pin is detected with de-bounce circuit.
     * @var TIMER_T::EINTSTS
     * Offset: 0x18/x038  Timer0~3 External Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CAPIF     |Timer External Capture Interrupt Flag
     * |        |          |This bit indicates the timer external capture interrupt flag status.
     * |        |          |0 = Tx_EXT (x= 0~3) pin interrupt did not occur.
     * |        |          |1 = Tx_EXT (x= 0~3) pin interrupt occurred.
     * |        |          |Note1: This bit is cleared by writing 1 to it.
     * |        |          |Note2: When CAPEN (TIMERx_EXTCTL[3]) bit is set, CAPFUNCS (TIMERx_EXTCTL[4]) bit is 0, and a transition on Tx_EXT (x= 0~3) pin is matched with the CAPEDGE (TIMERx_EXTCTL[2:1]) setting, this bit will set to 1 by hardware.
     * |        |          |Note3: There is a new incoming capture event detected before CPU clearing the CAPIF status
     * |        |          |If the above condition occurred, the Timer will keep register TIMERx_CAP unchanged and drop the new capture value.
     */
    __IO uint32_t CTL;                   /*!< [0x0000/0x0020] Timer0~3 Control and Status Register                               */
    __IO uint32_t CMP;                   /*!< [0x0004/0x0024] Timer0~3 Compare Register                                          */
    __IO uint32_t INTSTS;                /*!< [0x0008/0x0028] Timer0~3 Interrupt Status Register                                 */
    __I  uint32_t CNT;                   /*!< [0x000c/0x002c] Timer0~3 Data Register                                             */
    __I  uint32_t CAP;                   /*!< [0x0010/0x0030] Timer0~3 Capture Data Register                                     */
    __IO uint32_t EXTCTL;                /*!< [0x0014/0x0034] Timer0~3 External Control Register                                 */
    __IO uint32_t EINTSTS;               /*!< [0x0018/0x0038] Timer0~3 External Interrupt Status Register                        */
} TIMER_T;

/**
    @addtogroup TIMER_CONST TMR01 Bit Field Definition
    Constant Definitions for TMR01 Controller
@{ */

#define TIMER_CTL_PSC_Pos                (0)                                               /*!< TIMER_T::CTL: PSC Position             */
#define TIMER_CTL_PSC_Msk                (0xfful << TIMER_CTL_PSC_Pos)                     /*!< TIMER_T::CTL: PSC Mask                 */

#define TIMER_CTL_TRGPDMA_Pos            (8)                                               /*!< TIMER_T::CTL: TRGPDMA Position         */
#define TIMER_CTL_TRGPDMA_Msk            (0x1ul << TIMER_CTL_TRGPDMA_Pos)                  /*!< TIMER_T::CTL: TRGPDMA Mask             */

#define TIMER_CTL_TRGBPWM_Pos            (9)                                               /*!< TIMER_T::CTL: TRGBPWM Position         */
#define TIMER_CTL_TRGBPWM_Msk            (0x1ul << TIMER_CTL_TRGBPWM_Pos)                  /*!< TIMER_T::CTL: TRGBPWM Mask             */

#define TIMER_CTL_TRGSSEL_Pos            (18)                                              /*!< TIMER_T::CTL: TRGSSEL Position         */
#define TIMER_CTL_TRGSSEL_Msk            (0x1ul << TIMER_CTL_TRGSSEL_Pos)                  /*!< TIMER_T::CTL: TRGSSEL Mask             */

#define TIMER_CTL_TRGPWM_Pos             (19)                                              /*!< TIMER_T::CTL: TRGPWM Position          */
#define TIMER_CTL_TRGPWM_Msk             (0x1ul << TIMER_CTL_TRGPWM_Pos)                   /*!< TIMER_T::CTL: TRGPWM Mask              */

#define TIMER_CTL_TRGADC_Pos             (21)                                              /*!< TIMER_T::CTL: TRGADC Position          */
#define TIMER_CTL_TRGADC_Msk             (0x1ul << TIMER_CTL_TRGADC_Pos)                   /*!< TIMER_T::CTL: TRGADC Mask              */

#define TIMER_CTL_TGLPINSEL_Pos          (22)                                              /*!< TIMER_T::CTL: TGLPINSEL Position       */
#define TIMER_CTL_TGLPINSEL_Msk          (0x1ul << TIMER_CTL_TGLPINSEL_Pos)                /*!< TIMER_T::CTL: TGLPINSEL Mask           */

#define TIMER_CTL_WKEN_Pos               (23)                                              /*!< TIMER_T::CTL: WKEN Position            */
#define TIMER_CTL_WKEN_Msk               (0x1ul << TIMER_CTL_WKEN_Pos)                     /*!< TIMER_T::CTL: WKEN Mask                */

#define TIMER_CTL_EXTCNTEN_Pos           (24)                                              /*!< TIMER_T::CTL: EXTCNTEN Position        */
#define TIMER_CTL_EXTCNTEN_Msk           (0x1ul << TIMER_CTL_EXTCNTEN_Pos)                 /*!< TIMER_T::CTL: EXTCNTEN Mask            */

#define TIMER_CTL_ACTSTS_Pos             (25)                                              /*!< TIMER_T::CTL: ACTSTS Position          */
#define TIMER_CTL_ACTSTS_Msk             (0x1ul << TIMER_CTL_ACTSTS_Pos)                   /*!< TIMER_T::CTL: ACTSTS Mask              */

#define TIMER_CTL_RSTCNT_Pos             (26)                                              /*!< TIMER_T::CTL: RSTCNT Position          */
#define TIMER_CTL_RSTCNT_Msk             (0x1ul << TIMER_CTL_RSTCNT_Pos)                   /*!< TIMER_T::CTL: RSTCNT Mask              */

#define TIMER_CTL_OPMODE_Pos             (27)                                              /*!< TIMER_T::CTL: OPMODE Position          */
#define TIMER_CTL_OPMODE_Msk             (0x3ul << TIMER_CTL_OPMODE_Pos)                   /*!< TIMER_T::CTL: OPMODE Mask              */

#define TIMER_CTL_INTEN_Pos              (29)                                              /*!< TIMER_T::CTL: INTEN Position           */
#define TIMER_CTL_INTEN_Msk              (0x1ul << TIMER_CTL_INTEN_Pos)                    /*!< TIMER_T::CTL: INTEN Mask               */

#define TIMER_CTL_CNTEN_Pos              (30)                                              /*!< TIMER_T::CTL: CNTEN Position           */
#define TIMER_CTL_CNTEN_Msk              (0x1ul << TIMER_CTL_CNTEN_Pos)                    /*!< TIMER_T::CTL: CNTEN Mask               */

#define TIMER_CTL_ICEDEBUG_Pos           (31)                                              /*!< TIMER_T::CTL: ICEDEBUG Position        */
#define TIMER_CTL_ICEDEBUG_Msk           (0x1ul << TIMER_CTL_ICEDEBUG_Pos)                 /*!< TIMER_T::CTL: ICEDEBUG Mask            */

#define TIMER_CMP_CMPDAT_Pos             (0)                                               /*!< TIMER_T::CMP: CMPDAT Position          */
#define TIMER_CMP_CMPDAT_Msk             (0xfffffful << TIMER_CMP_CMPDAT_Pos)              /*!< TIMER_T::CMP: CMPDAT Mask              */

#define TIMER_INTSTS_TIF_Pos             (0)                                               /*!< TIMER_T::INTSTS: TIF Position          */
#define TIMER_INTSTS_TIF_Msk             (0x1ul << TIMER_INTSTS_TIF_Pos)                   /*!< TIMER_T::INTSTS: TIF Mask              */

#define TIMER_INTSTS_TWKF_Pos            (1)                                               /*!< TIMER_T::INTSTS: TWKF Position         */
#define TIMER_INTSTS_TWKF_Msk            (0x1ul << TIMER_INTSTS_TWKF_Pos)                  /*!< TIMER_T::INTSTS: TWKF Mask             */

#define TIMER_CNT_CNT_Pos                (0)                                               /*!< TIMER_T::CNT: CNT Position             */
#define TIMER_CNT_CNT_Msk                (0xfffffful << TIMER_CNT_CNT_Pos)                 /*!< TIMER_T::CNT: CNT Mask                 */

#define TIMER_CAP_CAPDAT_Pos             (0)                                               /*!< TIMER_T::CAP: CAPDAT Position          */
#define TIMER_CAP_CAPDAT_Msk             (0xfffffful << TIMER_CAP_CAPDAT_Pos)              /*!< TIMER_T::CAP: CAPDAT Mask              */

#define TIMER_EXTCTL_CNTPHASE_Pos        (0)                                               /*!< TIMER_T::EXTCTL: CNTPHASE Position     */
#define TIMER_EXTCTL_CNTPHASE_Msk        (0x1ul << TIMER_EXTCTL_CNTPHASE_Pos)              /*!< TIMER_T::EXTCTL: CNTPHASE Mask         */

#define TIMER_EXTCTL_CAPEDGE_Pos         (1)                                               /*!< TIMER_T::EXTCTL: CAPEDGE Position      */
#define TIMER_EXTCTL_CAPEDGE_Msk         (0x3ul << TIMER_EXTCTL_CAPEDGE_Pos)               /*!< TIMER_T::EXTCTL: CAPEDGE Mask          */

#define TIMER_EXTCTL_CAPEN_Pos           (3)                                               /*!< TIMER_T::EXTCTL: CAPEN Position        */
#define TIMER_EXTCTL_CAPEN_Msk           (0x1ul << TIMER_EXTCTL_CAPEN_Pos)                 /*!< TIMER_T::EXTCTL: CAPEN Mask            */

#define TIMER_EXTCTL_CAPFUNCS_Pos        (4)                                               /*!< TIMER_T::EXTCTL: CAPFUNCS Position     */
#define TIMER_EXTCTL_CAPFUNCS_Msk        (0x1ul << TIMER_EXTCTL_CAPFUNCS_Pos)              /*!< TIMER_T::EXTCTL: CAPFUNCS Mask         */

#define TIMER_EXTCTL_CAPIEN_Pos          (5)                                               /*!< TIMER_T::EXTCTL: CAPIEN Position       */
#define TIMER_EXTCTL_CAPIEN_Msk          (0x1ul << TIMER_EXTCTL_CAPIEN_Pos)                /*!< TIMER_T::EXTCTL: CAPIEN Mask           */

#define TIMER_EXTCTL_CAPDBEN_Pos         (6)                                               /*!< TIMER_T::EXTCTL: CAPDBEN Position      */
#define TIMER_EXTCTL_CAPDBEN_Msk         (0x1ul << TIMER_EXTCTL_CAPDBEN_Pos)               /*!< TIMER_T::EXTCTL: CAPDBEN Mask          */

#define TIMER_EXTCTL_CNTDBEN_Pos         (7)                                               /*!< TIMER_T::EXTCTL: CNTDBEN Position      */
#define TIMER_EXTCTL_CNTDBEN_Msk         (0x1ul << TIMER_EXTCTL_CNTDBEN_Pos)               /*!< TIMER_T::EXTCTL: CNTDBEN Mask          */

#define TIMER_EINTSTS_CAPIF_Pos          (0)                                               /*!< TIMER_T::EINTSTS: CAPIF Position       */
#define TIMER_EINTSTS_CAPIF_Msk          (0x1ul << TIMER_EINTSTS_CAPIF_Pos)                /*!< TIMER_T::EINTSTS: CAPIF Mask           */

/**@}*/ /* TIMER_CONST */
/**@}*/ /* end of TIMER register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __TIMER_REG_H__ */
