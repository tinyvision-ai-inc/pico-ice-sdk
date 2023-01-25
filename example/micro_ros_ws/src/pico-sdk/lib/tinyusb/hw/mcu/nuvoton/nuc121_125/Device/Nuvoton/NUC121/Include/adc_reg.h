/**************************************************************************//**
 * @file     adc_reg.h
 * @version  V1.00
 * @brief    ADC register definition header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __ADC_REG_H__
#define __ADC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup ADC Analog to Digital Converter (ADC)
    Memory Mapped Structure for ADC Controller
@{ */

typedef struct
{
    /**
     * @var ADC_T::ADDR
     * Offset: 0x00~0x7C  ADC Data Register 0~31
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |RSLT      |A/D Conversion Result
     * |        |          |This field contains conversion result of ADC.
     * |[16]    |OVERRUN   |Overrun Flag
     * |        |          |If converted data in RSLT has not been read before new conversion result is loaded to this register, OVERRUN is set to 1
     * |        |          |It is cleared by hardware after ADDR register is read
     * |        |          |0 = Data in RSLT is not overwrote.
     * |        |          |1 = Data in RSLT is overwrote.
     * |[17]    |VALID     |Valid Flag
     * |        |          |This bit will be set to 1 when the conversion of the corresponding channel is completed
     * |        |          |This bit will be cleared to 0 by hardware after ADDR register is read
     * |        |          |0 = Data in RSLT bits is not valid.
     * |        |          |1 = Data in RSLT bits is valid.
     * @var ADC_T::ADCR
     * Offset: 0x80  ADC Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADEN      |A/D Converter Enable Bit
     * |        |          |0 = A/D converter Disabled.
     * |        |          |1 = A/D converter Enabled.
     * |        |          |Note: Before starting A/D conversion function, this bit should be set to 1
     * |        |          |Clear it to 0 to disable A/D converter analog circuit to save power consumption.
     * |[1]     |ADIE      |A/D Interrupt Enable Control
     * |        |          |A/D conversion end interrupt request is generated if ADIE bit is set to 1.
     * |        |          |0 = A/D interrupt function Disabled.
     * |        |          |1 = A/D interrupt function Enabled.
     * |[3:2]   |ADMD      |A/D Converter Operation Mode Control
     * |        |          |00 = Single conversion.
     * |        |          |01 = Burst conversion.
     * |        |          |10 = Single-cycle Scan.
     * |        |          |11 = Continuous Scan.
     * |        |          |Note1: When changing the operation mode, software should clear ADST bit first.
     * |        |          |Note2: In Burst mode, the A/D result data always at Data Register 0.
     * |[5:4]   |TRGS      |Hardware Trigger Source
     * |        |          |00 = A/D conversion is started by external STADC pin.
     * |        |          |01 = Timer0 ~ Timer3 overflow pulse trigger.
     * |        |          |10 = Reserved.
     * |        |          |11 = A/D conversion is started by PWM trigger.
     * |        |          |Note: Software should clear TRGEN bit and ADST bit to 0 before changing TRGS.
     * |[7:6]   |TRGCOND   |External Trigger Condition
     * |        |          |These two bits decide external pin STADC trigger event is level or edge
     * |        |          |The signal must be kept at stable state at least 8 PCLKs for level trigger and at least 4 PCLKs for edge trigger.
     * |        |          |00 = Low level.
     * |        |          |01 = High level.
     * |        |          |10 = Falling edge.
     * |        |          |11 = Rising edge.
     * |[8]     |TRGEN     |External Trigger Enable Control
     * |        |          |Enable or disable triggering of A/D conversion by external STADC pin, PWM trigger and Timer trigger
     * |        |          |If external trigger is enabled, the ADST bit can be set to 1 by the selected hardware trigger source.
     * |        |          |0= External trigger Disabled.
     * |        |          |1= External trigger Enabled.
     * |        |          |Note: The ADC external trigger function is only supported in Single-cycle Scan mode.
     * |[9]     |PTEN      |PDMA Transfer Enable Bit
     * |        |          |When A/D conversion is completed, the converted data is loaded into ADDR0~11, ADDR29~ADDR30
     * |        |          |Software can enable this bit to generate a PDMA data transfer request.
     * |        |          |0 = PDMA data transfer Disabled.
     * |        |          |1 = PDMA data transfer in ADDR0~11, ADDR29~ADDR30 Enabled.
     * |        |          |Note: When PTEN=1, software must set ADIE=0 to disable interrupt.
     * |[10]    |DIFFEN    |Differential Input Mode Control
     * |        |          |Differential input voltage (Vdiff) = Vplus - Vminus,.
     * |        |          |where Vplus is the analog input; Vminus is the inverted analog input.
     * |        |          |The Vplus of differential input paired channel x is from ADC0_CHy pin; Vminus is from ADC0_CHz pin, x=0,1..5, y=2*x, z=y+1.
     * |        |          |0 = Single-end analog input mode.
     * |        |          |1 = Differential analog input mode.
     * |        |          |Note: In Differential Input mode, only the even number of the two corresponding channels needs to be enabled in ADCHER register
     * |        |          |The conversion result will be placed to the corresponding data register of the enabled channel.
     * |[11]    |ADST      |A/D Conversion Start
     * |        |          |ADST bit can be set to 1 from four sources: software, external pin STADC, PWM trigger and Timer trigger
     * |        |          |ADST will be cleared to 0 by hardware automatically at the ends of Single mode and Single-cycle Scan mode
     * |        |          |In Continuous Scan mode and Burst mode, A/D conversion is continuously performed until software writes 0 to this bit or chip is reset.
     * |        |          |0 = Conversion stops and A/D converter enters idle state.
     * |        |          |1 = Conversion starts.
     * |[18:16] |SMPTSEL   |ADC Internal Sampling Time Selection
     * |        |          |Total ADC conversion cycle = sampling cycle + 12.
     * |        |          |000 = 2 ADC clock for sampling ; 14 ADC clock for complete conversion.
     * |        |          |001 = 3 ADC clock for sampling ; 15 ADC clock for complete conversion.
     * |        |          |010 = 4 ADC clock for sampling ; 16 ADC clock for complete conversion.
     * |        |          |011 = 5 ADC clock for sampling ; 17 ADC clock for complete conversion.
     * |        |          |100 = 6 ADC clock for sampling ; 18 ADC clock for complete conversion.
     * |        |          |101 = 7 ADC clock for sampling ; 19 ADC clock for complete conversion.
     * |        |          |110 = 8 ADC clock for sampling ; 20 ADC clock for complete conversion.
     * |        |          |111 = 9 ADC clock for sampling ; 21 ADC clock for complete conversion.
     * |[31]    |DMOF      |Differential Input Mode Output Format
     * |        |          |If user enables differential input mode, the conversion result can be expressed with binary straight format (unsigned format) or 2's complement format (signed format).
     * |        |          |0 = A/D Conversion result will be filled in RSLT at ADDRx registers with unsigned format (straight binary format).
     * |        |          |1 = A/D Conversion result will be filled in RSLT at ADDRx registers with 2's complement format.
     * @var ADC_T::ADCHER
     * Offset: 0x84  ADC Channel Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CHEN      |Analog Input Channel Enable Control
     * |        |          |Set CHEN[11:0] to enable the corresponding analog input channel 11 ~ 0
     * |        |          |If DIFFEN bit is set to 1, only the even number channel needs to be enabled.
     * |        |          |Besides, set CHEN[29] to CHEN[30] will enable internal channel for band-gap voltage and temperature sensor respectively
     * |        |          |Other bits are reserved.
     * |        |          |0 = Channel Disabled.
     * |        |          |1 = Channel Enabled.
     * |        |          |Note 1 : If the internal channel for band-gap voltage (CHEN[29]) is active, the maximum sampling rate will be TBD SPS
     * |        |          |Note 2 : If the internal channel for temperature sensor (CHEN[30]) is active, the maximum sampling rate will be 300k SPS
     * @var ADC_T::ADCMPR
     * Offset: 0x88/0x8C  ADC Compare Register 0 & 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CMPEN     |Compare Enable Control Bit
     * |        |          |Set this bit to 1 to enable ADC controller to compare CMPD[11:0] with specified channel conversion result when converted data is loaded into ADDR register.
     * |        |          |0 = Compare function Disabled.
     * |        |          |1 = Compare function Enabled.
     * |[1]     |CMPIE     |Compare Interrupt Enable Control Bit
     * |        |          |If the compare function is enabled and the compare condition matches the setting of CMPCOND and CMPMATCNT, CMPFx bit will be asserted, in the meanwhile, if CMPIE is set to 1, a compare interrupt request is generated.
     * |        |          |0 = Compare function interrupt Disabled.
     * |        |          |1 = Compare function interrupt Enabled.
     * |[2]     |CMPCOND   |Compare Condition
     * |        |          |0= Set the compare condition as that when a 12-bit A/D conversion result is less than the 12-bit CMPD (ADCMPRx[27:16]), the internal match counter will increase one.
     * |        |          |1= Set the compare condition as that when a 12-bit A/D conversion result is greater than or equal to the 12-bit CMPD (ADCMPRx[27:16]), the internal match counter will increase one.
     * |        |          |Note: When the compare result meets the condition setting, the internal match counter will increase 1, otherwise, the internal match counter will be cleared to 0.
     * |        |          |Note: When the internal counter reaches to (CMPMATCNT +1), the CMPFx bit will be set.
     * |[7:3]   |CMPCH     |Compare Channel Selection
     * |        |          |00000 = Channel 0 conversion result is selected to be compared.
     * |        |          |00001 = Channel 1 conversion result is selected to be compared.
     * |        |          |00010 = Channel 2 conversion result is selected to be compared.
     * |        |          |00011 = Channel 3 conversion result is selected to be compared.
     * |        |          |00100 = Channel 4 conversion result is selected to be compared.
     * |        |          |00101 = Channel 5 conversion result is selected to be compared.
     * |        |          |00110 = Channel 6 conversion result is selected to be compared.
     * |        |          |00111 = Channel 7 conversion result is selected to be compared.
     * |        |          |01000 = Channel 8 conversion result is selected to be compared.
     * |        |          |01001 = Channel 9 conversion result is selected to be compared.
     * |        |          |01010 = Channel 10 conversion result is selected to be compared.
     * |        |          |01011 = Channel 11 conversion result is selected to be compared.
     * |        |          |11101 = Band-gap voltage conversion result is selected to be compared.
     * |        |          |11110 = Temperature sensor conversion result is selected to be compared.
     * |        |          |Others = Reserved.
     * |[11:8]  |CMPMATCNT |Compare Match Count
     * |        |          |When the specified A/D channel analog conversion result matches the compare condition defined by CMPCOND, the internal match counter will increase 1, otherwise, the internal match counter will be cleared to 0
     * |        |          |When the internal counter reaches the value to (CMPMATCNT +1), the CMPFx bit will be set.
     * |[15]    |CMPWEN    |Compare Window Mode Enable Bit
     * |        |          |0 = Compare Window Mode Disabled.
     * |        |          |1 = Compare Window Mode Enabled.
     * |        |          |Note: This bit is only presented in ADCMPR0 register.
     * |[27:16] |CMPD      |Comparison Data
     * |        |          |The 12-bit data is used to compare with conversion result of specified channel.
     * |        |          |Note: CMPD should be filled in unsigned format (straight binary format).
     * @var ADC_T::ADSR0
     * Offset: 0x90  ADC Status Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADF       |A/D Conversion End Flag
     * |        |          |A status flag that indicates the end of A/D conversion. Software can write 1 to clear this bit.
     * |        |          |ADF is set to 1 at the following three conditions:
     * |        |          |1. When A/D conversion ends in Single mode.
     * |        |          |2
     * |        |          |When A/D conversion ends on all specified channels in Single-cycle Scan mode and Continuous Scan mode.
     * |        |          |3. When more than 8 samples in FIFO in Burst mode.
     * |[1]     |CMPF0     |Compare Flag 0
     * |        |          |When the A/D conversion result of the selected channel meets setting condition in ADCMPR0 then this bit is set to 1
     * |        |          |This bit is cleared by writing 1 to it.
     * |        |          |0 = Conversion result in ADDR does not meet ADCMPR0 setting.
     * |        |          |1 = Conversion result in ADDR meets ADCMPR0 setting.
     * |[2]     |CMPF1     |Compare Flag 1
     * |        |          |When the A/D conversion result of the selected channel meets setting condition in ADCMPR1 then this bit is set to 1; it is cleared by writing 1 to it
     * |        |          |0 = Conversion result in ADDR does not meet ADCMPR1 setting.
     * |        |          |1 = Conversion result in ADDR meets ADCMPR1 setting.
     * |[7]     |BUSY      |BUSY/IDLE
     * |        |          |This bit is a mirror of ADST bit in ADCR register. It is read only.
     * |        |          |0 = A/D converter is in idle state.
     * |        |          |1 = A/D converter is busy at conversion.
     * |[8]     |VALIDF    |Data Valid Flag
     * |        |          |If any one of VALID (ADDRx[17]) is set, this flag will be set to 1. This is a read only bit.
     * |        |          |Note: When ADC is in burst mode and any conversion result is valid, this flag will be set to 1
     * |[16]    |OVERRUNF  |Overrun Flag
     * |        |          |If any one of OVERRUN (ADDRx[16]) is set, this flag will be set to 1. This is a read only bit.
     * |        |          |Note: When ADC is in burst mode and the FIFO is overrun, this flag will be set to 1.
     * |[31:27] |CHANNEL   |Current Conversion Channel
     * |        |          |When BUSY=1, this filed reflects current conversion channel
     * |        |          |When BUSY=0, it shows the number of the next converted channel.
     * |        |          |It is read only.
     * @var ADC_T::ADSR1
     * Offset: 0x94  ADC Status Register1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VALID     |Data Valid Flag
     * |        |          |VALID[30:29, 11:0] are the mirror of the VALID bits in ADDR30[17] ~ ADDR29[17], ADDR11[17]~ ADDR0[17]
     * |        |          |The other bits are reserved.
     * |        |          |Note: When ADC is in burst mode and any conversion result is valid, VALID[30:29, 11:0] will be set to 1.
     * @var ADC_T::ADSR2
     * Offset: 0x98  ADC Status Register2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |OVERRUN   |Overrun Flag
     * |        |          |OVERRUN[30:29, 11:0] are the mirror of the OVERRUN bit in ADDR30[16] ~ADDR29[16], ADDR11[16] ~ ADDR0[16]
     * |        |          |The other bits are reserved.
     * |        |          |Note: When ADC is in burst mode and the FIFO is overrun, OVERRUN[30:29, 11:0] will be set to 1.
     * @var ADC_T::ADTDCR
     * Offset: 0x9C  ADC Trigger Delay Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |PTDT      |PWM Trigger Delay Time
     * |        |          |Set this field will delay ADC start conversion time after PWM trigger.
     * |        |          |PWM trigger delay time is (4 * PTDT) * system clock
     * @var ADC_T::ADPDMA
     * Offset: 0x100  ADC PDMA Current Transfer Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:0]  |CURDAT    |ADC PDMA Current Transfer Data Register
     * |        |          |When PDMA transferring, read this register can monitor current PDMA transfer data.
     * |        |          |Current PDMA transfer data could be the content of ADDR0 ~ ADDR11 and ADDR29 ~ ADDR30.
     * |        |          |This is a read only register.
     */
    __I  uint32_t ADDR[32];              /*!< [0x0000~0x007c] A/D Data Register 0~31                                    */
    __IO uint32_t ADCR;                  /*!< [0x0080] ADC Control Register                                             */
    __IO uint32_t ADCHER;                /*!< [0x0084] ADC Channel Enable Register                                      */
    __IO uint32_t ADCMPR[2];             /*!< [0x0088/0x008c] ADC Compare Register 0 & 1                                */
    __IO uint32_t ADSR0;                 /*!< [0x0090] ADC Status Register0                                             */
    __I  uint32_t ADSR1;                 /*!< [0x0094] ADC Status Register1                                             */
    __I  uint32_t ADSR2;                 /*!< [0x0098] ADC Status Register2                                             */
    __IO uint32_t ADTDCR;                /*!< [0x009c] ADC Trigger Delay Control Register                               */
    __I  uint32_t RESERVE0[24];
    __I  uint32_t ADPDMA;                /*!< [0x0100] ADC PDMA Current Transfer Data Register                          */
} ADC_T;

/**
    @addtogroup ADC_CONST ADC Bit Field Definition
    Constant Definitions for ADC Controller
@{ */

/* ADDR Bit Field Definitions */
#define ADC_ADDR_RSLT_Pos               (0)                                                /*!< ADC_T::ADDR: RSLT Position             */
#define ADC_ADDR_RSLT_Msk               (0xfffful << ADC_ADDR_RSLT_Pos)                    /*!< ADC_T::ADDR: RSLT Mask                 */

#define ADC_ADDR_OVERRUN_Pos            (16)                                               /*!< ADC_T::ADDR: OVERRUN Position          */
#define ADC_ADDR_OVERRUN_Msk            (0x1ul << ADC_ADDR_OVERRUN_Pos)                    /*!< ADC_T::ADDR: OVERRUN Mask              */

#define ADC_ADDR_VALID_Pos              (17)                                               /*!< ADC_T::ADDR: VALID Position            */
#define ADC_ADDR_VALID_Msk              (0x1ul << ADC_ADDR_VALID_Pos)                      /*!< ADC_T::ADDR: VALID Mask                */

/* ADCR Bit Field Definitions */
#define ADC_ADCR_ADEN_Pos                (0)                                               /*!< ADC_T::ADCR: ADEN Position             */
#define ADC_ADCR_ADEN_Msk                (0x1ul << ADC_ADCR_ADEN_Pos)                      /*!< ADC_T::ADCR: ADEN Mask                 */

#define ADC_ADCR_ADIE_Pos                (1)                                               /*!< ADC_T::ADCR: ADIE Position             */
#define ADC_ADCR_ADIE_Msk                (0x1ul << ADC_ADCR_ADIE_Pos)                      /*!< ADC_T::ADCR: ADIE Mask                 */

#define ADC_ADCR_ADMD_Pos                (2)                                               /*!< ADC_T::ADCR: ADMD Position             */
#define ADC_ADCR_ADMD_Msk                (0x3ul << ADC_ADCR_ADMD_Pos)                      /*!< ADC_T::ADCR: ADMD Mask                 */

#define ADC_ADCR_TRGS_Pos                (4)                                               /*!< ADC_T::ADCR: TRGS Position             */
#define ADC_ADCR_TRGS_Msk                (0x3ul << ADC_ADCR_TRGS_Pos)                      /*!< ADC_T::ADCR: TRGS Mask                 */

#define ADC_ADCR_TRGCOND_Pos             (6)                                               /*!< ADC_T::ADCR: TRGCOND Position          */
#define ADC_ADCR_TRGCOND_Msk             (0x3ul << ADC_ADCR_TRGCOND_Pos)                   /*!< ADC_T::ADCR: TRGCOND Mask              */

#define ADC_ADCR_TRGEN_Pos               (8)                                               /*!< ADC_T::ADCR: TRGEN Position            */
#define ADC_ADCR_TRGEN_Msk               (0x1ul << ADC_ADCR_TRGEN_Pos)                     /*!< ADC_T::ADCR: TRGEN Mask                */

#define ADC_ADCR_PTEN_Pos                (9)                                               /*!< ADC_T::ADCR: PTEN Position             */
#define ADC_ADCR_PTEN_Msk                (0x1ul << ADC_ADCR_PTEN_Pos)                      /*!< ADC_T::ADCR: PTEN Mask                 */

#define ADC_ADCR_DIFFEN_Pos              (10)                                              /*!< ADC_T::ADCR: DIFFEN Position           */
#define ADC_ADCR_DIFFEN_Msk              (0x1ul << ADC_ADCR_DIFFEN_Pos)                    /*!< ADC_T::ADCR: DIFFEN Mask               */

#define ADC_ADCR_ADST_Pos                (11)                                              /*!< ADC_T::ADCR: ADST Position             */
#define ADC_ADCR_ADST_Msk                (0x1ul << ADC_ADCR_ADST_Pos)                      /*!< ADC_T::ADCR: ADST Mask                 */

#define ADC_ADCR_SMPTSEL_Pos             (16)                                              /*!< ADC_T::ADCR: SMPTSEL Position          */
#define ADC_ADCR_SMPTSEL_Msk             (0x7ul << ADC_ADCR_SMPTSEL_Pos)                   /*!< ADC_T::ADCR: SMPTSEL Mask              */

#define ADC_ADCR_DMOF_Pos                (31)                                              /*!< ADC_T::ADCR: DMOF Position             */
#define ADC_ADCR_DMOF_Msk                (0x1ul << ADC_ADCR_DMOF_Pos)                      /*!< ADC_T::ADCR: DMOF Mask                 */

/* ADCHER Bit Field Definitions */
#define ADC_ADCHER_CHEN_Pos              (0)                                               /*!< ADC_T::ADCHER: CHEN Position           */
#define ADC_ADCHER_CHEN_Msk              (0xfffffffful << ADC_ADCHER_CHEN_Pos)             /*!< ADC_T::ADCHER: CHEN Mask               */

/* ADCMPR Bit Field Definitions */
#define ADC_ADCMPR_CMPEN_Pos             (0)                                               /*!< ADC_T::ADCMPR: CMPEN Position          */
#define ADC_ADCMPR_CMPEN_Msk             (0x1ul << ADC_ADCMPR_CMPEN_Pos)                   /*!< ADC_T::ADCMPR: CMPEN Mask              */

#define ADC_ADCMPR_CMPIE_Pos             (1)                                               /*!< ADC_T::ADCMPR: CMPIE Position          */
#define ADC_ADCMPR_CMPIE_Msk             (0x1ul << ADC_ADCMPR_CMPIE_Pos)                   /*!< ADC_T::ADCMPR: CMPIE Mask              */

#define ADC_ADCMPR_CMPCOND_Pos           (2)                                               /*!< ADC_T::ADCMPR: CMPCOND Position        */
#define ADC_ADCMPR_CMPCOND_Msk           (0x1ul << ADC_ADCMPR_CMPCOND_Pos)                 /*!< ADC_T::ADCMPR: CMPCOND Mask            */

#define ADC_ADCMPR_CMPCH_Pos             (3)                                               /*!< ADC_T::ADCMPR: CMPCH Position          */
#define ADC_ADCMPR_CMPCH_Msk             (0x1ful << ADC_ADCMPR_CMPCH_Pos)                  /*!< ADC_T::ADCMPR: CMPCH Mask              */

#define ADC_ADCMPR_CMPMATCNT_Pos         (8)                                               /*!< ADC_T::ADCMPR: CMPMATCNT Position      */
#define ADC_ADCMPR_CMPMATCNT_Msk         (0xful << ADC_ADCMPR_CMPMATCNT_Pos)               /*!< ADC_T::ADCMPR: CMPMATCNT Mask          */

#define ADC_ADCMPR_CMPWEN_Pos            (15)                                              /*!< ADC_T::ADCMPR: CMPWEN Position         */
#define ADC_ADCMPR_CMPWEN_Msk            (0x1ul << ADC_ADCMPR_CMPWEN_Pos)                  /*!< ADC_T::ADCMPR: CMPWEN Mask             */

#define ADC_ADCMPR_CMPD_Pos              (16)                                              /*!< ADC_T::ADCMPR: CMPD Position           */
#define ADC_ADCMPR_CMPD_Msk              (0xffful << ADC_ADCMPR_CMPD_Pos)                  /*!< ADC_T::ADCMPR: CMPD Mask               */

/* ADSR0 Bit Field Definitions */
#define ADC_ADSR0_ADF_Pos                (0)                                               /*!< ADC_T::ADSR0: ADF Position             */
#define ADC_ADSR0_ADF_Msk                (0x1ul << ADC_ADSR0_ADF_Pos)                      /*!< ADC_T::ADSR0: ADF Mask                 */

#define ADC_ADSR0_CMPF0_Pos              (1)                                               /*!< ADC_T::ADSR0: CMPF0 Position           */
#define ADC_ADSR0_CMPF0_Msk              (0x1ul << ADC_ADSR0_CMPF0_Pos)                    /*!< ADC_T::ADSR0: CMPF0 Mask               */

#define ADC_ADSR0_CMPF1_Pos              (2)                                               /*!< ADC_T::ADSR0: CMPF1 Position           */
#define ADC_ADSR0_CMPF1_Msk              (0x1ul << ADC_ADSR0_CMPF1_Pos)                    /*!< ADC_T::ADSR0: CMPF1 Mask               */

#define ADC_ADSR0_BUSY_Pos               (7)                                               /*!< ADC_T::ADSR0: BUSY Position            */
#define ADC_ADSR0_BUSY_Msk               (0x1ul << ADC_ADSR0_BUSY_Pos)                     /*!< ADC_T::ADSR0: BUSY Mask                */

#define ADC_ADSR0_VALIDF_Pos             (8)                                               /*!< ADC_T::ADSR0: VALIDF Position          */
#define ADC_ADSR0_VALIDF_Msk             (0x1ul << ADC_ADSR0_VALIDF_Pos)                   /*!< ADC_T::ADSR0: VALIDF Mask              */

#define ADC_ADSR0_OVERRUNF_Pos           (16)                                              /*!< ADC_T::ADSR0: OVERRUNF Position        */
#define ADC_ADSR0_OVERRUNF_Msk           (0x1ul << ADC_ADSR0_OVERRUNF_Pos)                 /*!< ADC_T::ADSR0: OVERRUNF Mask            */

#define ADC_ADSR0_CHANNEL_Pos            (27)                                              /*!< ADC_T::ADSR0: CHANNEL Position         */
#define ADC_ADSR0_CHANNEL_Msk            (0x1ful << ADC_ADSR0_CHANNEL_Pos)                 /*!< ADC_T::ADSR0: CHANNEL Mask             */

/* ADSR1 Bit Field Definitions */
#define ADC_ADSR1_VALID_Pos              (0)                                               /*!< ADC_T::ADSR1: VALID Position           */
#define ADC_ADSR1_VALID_Msk              (0xfffffffful << ADC_ADSR1_VALID_Pos)             /*!< ADC_T::ADSR1: VALID Mask               */

/* ADSR2 Bit Field Definitions */
#define ADC_ADSR2_OVERRUN_Pos            (0)                                               /*!< ADC_T::ADSR2: OVERRUN Position         */
#define ADC_ADSR2_OVERRUN_Msk            (0xfffffffful << ADC_ADSR2_OVERRUN_Pos)           /*!< ADC_T::ADSR2: OVERRUN Mask             */

/* ADTDCR Bit Field Definitions */
#define ADC_ADTDCR_PTDT_Pos              (0)                                               /*!< ADC_T::ADTDCR: PTDT Position           */
#define ADC_ADTDCR_PTDT_Msk              (0xfful << ADC_ADTDCR_PTDT_Pos)                   /*!< ADC_T::ADTDCR: PTDT Mask               */

/* ADPDMA Bit Field Definitions */
#define ADC_ADPDMA_CURDAT_Pos            (0)                                               /*!< ADC_T::ADPDMA: CURDAT Position         */
#define ADC_ADPDMA_CURDAT_Msk            (0x3fffful << ADC_ADPDMA_CURDAT_Pos)              /*!< ADC_T::ADPDMA: CURDAT Mask             */

/**@}*/ /* ADC_CONST */
/**@}*/ /* end of ADC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __ADC_REG_H__ */
