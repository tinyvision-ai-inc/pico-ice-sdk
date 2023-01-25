/**************************************************************************//**
 * @file     pdma_reg.h
 * @version  V1.00
 * @brief    PDMA register definition header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __PDMA_REG_H__
#define __PDMA_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup PDMA Peripheral Direct Memory Access Controller (PDMA)
    Memory Mapped Structure for PDMA Controller
@{ */

typedef struct
{
    /**
     * @var PDMA_DSCT_T::CTL
     * Offset: 0x00/0x10/0x20/0x30/0x40  Descriptor Table Control Register of PDMA Channel 0~4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |OPMODE    |PDMA Operation Mode Selection
     * |        |          |00 = Idle state: Channel is stopped or this table is complete, when PDMA finish channel table task, OPMODE will be cleared to idle state automatically.
     * |        |          |01 = Basic mode: The descriptor table only has one task
     * |        |          |When this task is finished, the PDMA_INTSTS[n] will be asserted.
     * |        |          |10 = Scatter-Gather mode: When operating in this mode, user must give the first descriptor table address in PDMA_DSCT_FIRST register; PDMA controller will ignore this task, then load the next task to execute.
     * |        |          |11 = Reserved.
     * |        |          |Note: Before filling transfer task in the Descriptor Table, user must check if the descriptor table is complete.
     * |[2]     |TXTYPE    |Transfer Type
     * |        |          |0 = Burst transfer type.
     * |        |          |1 = Single transfer type.
     * |[6:4]   |BURSIZE   |Burst Size
     * |        |          |This field is used for peripheral to determine the burst size or used for determine the re-arbitration size.
     * |        |          |000 = 128 Transfers.
     * |        |          |001 = 64 Transfers.
     * |        |          |010 = 32 Transfers.
     * |        |          |011 = 16 Transfers.
     * |        |          |100 = 8 Transfers.
     * |        |          |101 = 4 Transfers.
     * |        |          |110 = 2 Transfers.
     * |        |          |111 = 1 Transfers.
     * |        |          |Note: This field is only useful in burst transfer type.
     * |[7]     |TBINTDIS  |Table Interrupt Disable Bit
     * |        |          |This field can be used to decide whether to enable table interrupt or not
     * |        |          |If the TBINTDIS bit is set when PDMA controller finishes transfer task, it will not generates interrupt.
     * |        |          |0 = Table interrupt Enabled.
     * |        |          |1 = Table interrupt Disabled.
     * |        |          |Note: If this bit set to '1', the TEMPTYF will not be set.
     * |[9:8]   |SAINC     |Source Address Increment
     * |        |          |This field is used to set the source address increment size.
     * |        |          |11 = No increment (fixed address).
     * |        |          |Others = Increment and size is depended on TXWIDTH selection.
     * |[11:10] |DAINC     |Destination Address Increment
     * |        |          |This field is used to set the destination address increment size.
     * |        |          |11 = No increment (fixed address).
     * |        |          |Others = Increment and size is depended on TXWIDTH selection.
     * |[13:12] |TXWIDTH   |Transfer Width Selection
     * |        |          |This field is used for transfer width.
     * |        |          |00 = One byte (8 bit) is transferred for every operation.
     * |        |          |01= One half-word (16 bit) is transferred for every operation.
     * |        |          |10 = One word (32-bit) is transferred for every operation.
     * |        |          |11 = Reserved.
     * |        |          |Note: The PDMA transfer source address (PDMA_DSCT_SA) and PDMA transfer destination address (PDMA_DSCT_DA) should be alignment under the TXWIDTH selection
     * |[29:16] |TXCNT     |Transfer Count
     * |        |          |The TXCNT represents the required number of PDMA transfer, the real transfer count is (TXCNT + 1); The maximum transfer count is 16384 , every transfer may be byte, half-word or word that is dependent on TXWIDTH field.
     * |        |          |Note: When PDMA finish each transfer data, this field will be decrease immediately.
     * @var PDMA_DSCT_T::SA
     * Offset: 0x04/0x14/0x24/0x34/0x44  Source Address Register of PDMA Channel 0~4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SA        |PDMA Transfer Source Address Register
     * |        |          |This field indicates a 32-bit source address of PDMA controller.
     * @var PDMA_DSCT_T::DA
     * Offset: 0x08/0x18/0x28/0x38/0x48  Destination Address Register of PDMA Channel 0~4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DA        |PDMA Transfer Destination Address Register
     * |        |          |This field indicates a 32-bit destination address of PDMA controller.
     * @var PDMA_DSCT_T::FIRST
     * Offset: 0x0C/0x1C/0x2C/0x3C/0x4C  First Scatter-Gather Descriptor Table Offset of PDMA Channel 0~4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |FIRST     |PDMA First Descriptor Table Offset
     * |        |          |This field indicates the offset of the first descriptor table address in system memory.
     * |        |          |Write Operation:
     * |        |          |If the system memory based address is 0x2000_0000 (PDMA_SCATBA), and the first descriptor table is start from 0x2000_0100, then this field must fill in 0x0100.
     * |        |          |Read Operation:
     * |        |          |When operating in scatter-gather mode, the last two bits FIRST[1:0] will become reserved.
     * |        |          |Note1: The first descriptor table address must be word boundary.
     * |        |          |Note2: Before filled transfer task in the descriptor table, user must check if the descriptor table is complete.
     */
    __IO uint32_t CTL;             /*!< [0x00/0x10/0x20/0x30/0x40] Descriptor Table Control Register of PDMA Channel 0~4              */
    __IO uint32_t SA;              /*!< [0x04/0x14/0x24/0x34/0x44] Source Address Register of PDMA Channel 0~4                        */
    __IO uint32_t DA;              /*!< [0x08/0x18/0x28/0x38/0x48] Destination Address Register of PDMA Channel 0~4                   */
    union
    {
        __IO uint32_t FIRST;       /*!< [0x0C/0x1C/0x2C/0x3C/0x4C] First Scatter-Gather Descriptor Table Offset of PDMA Channel 0~4   */
        __IO uint32_t NEXT;        /*!< Next Scatter-Gather Descriptor Table Offset                                                   */
    };
} PDMA_DSCT_T;

typedef struct
{
    /**
     * @var PDMA_T::CURSCAT
     * Offset: 0x50~0x60  Current Scatter-Gather Descriptor Table Address of PDMA Channel 0~4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |CURADDR   |PDMA Current Description Address Register (Read Only)
     * |        |          |This field indicates a 32-bit current external description address of PDMA controller.
     * |        |          |Note: This field is read only and only used for Scatter-Gather mode to indicate the current external description address.
     * @var PDMA_T::CHCTL
     * Offset: 0x400  PDMA Channel Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CHEN0     |PDMA Channel N Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Set PDMA_PAUSE or PDMA_RESET register will also clear this bit.
     * |[1]     |CHEN1     |PDMA Channel N Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Set PDMA_PAUSE or PDMA_RESET register will also clear this bit.
     * |[2]     |CHEN2     |PDMA Channel N Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Set PDMA_PAUSE or PDMA_RESET register will also clear this bit.
     * |[3]     |CHEN3     |PDMA Channel N Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Set PDMA_PAUSE or PDMA_RESET register will also clear this bit.
     * |[4]     |CHEN4     |PDMA Channel N Enable Bit
     * |        |          |Set this bit to 1 to enable PDMAn operation. Channel cannot be active if it is not set as enabled.
     * |        |          |0 = PDMA channel [n] Disabled.
     * |        |          |1 = PDMA channel [n] Enabled.
     * |        |          |Note: Set PDMA_PAUSE or PDMA_RESET register will also clear this bit.
     * @var PDMA_T::PAUSE
     * Offset: 0x404  PDMA Transfer Pause Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PAUSE0    |PDMA Channel N Transfer Pause Control Register (Write Only)
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer
     * |        |          |When user sets PDMA_PAUSE bit, the operation will pause the on-going transfer, but not finish the rest of transfers, and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable the paused channel agian, the remaining transfers will be processed.
     * |[1]     |PAUSE1    |PDMA Channel N Transfer Pause Control Register (Write Only)
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer
     * |        |          |When user sets PDMA_PAUSE bit, the operation will pause the on-going transfer, but not finish the rest of transfers, and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable the paused channel agian, the remaining transfers will be processed.
     * |[2]     |PAUSE2    |PDMA Channel N Transfer Pause Control Register (Write Only)
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer
     * |        |          |When user sets PDMA_PAUSE bit, the operation will pause the on-going transfer, but not finish the rest of transfers, and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable the paused channel agian, the remaining transfers will be processed.
     * |[3]     |PAUSE3    |PDMA Channel N Transfer Pause Control Register (Write Only)
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer
     * |        |          |When user sets PDMA_PAUSE bit, the operation will pause the on-going transfer, but not finish the rest of transfers, and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable the paused channel agian, the remaining transfers will be processed.
     * |[4]     |PAUSE4    |PDMA Channel N Transfer Pause Control Register (Write Only)
     * |        |          |User can set PAUSEn bit field to pause the PDMA transfer.
     * |        |          |0 = No effect.
     * |        |          |1 = Pause PDMA channel n transfer
     * |        |          |When user sets PDMA_PAUSE bit, the operation will pause the on-going transfer, but not finish the rest of transfers, and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable the paused channel agian, the remaining transfers will be processed.
     * @var PDMA_T::SWREQ
     * Offset: 0x408  PDMA Software Request Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SWREQ0    |PDMA Channel N Software Request Register (Write Only)
     * |        |          |Set this bit to 1 to generate a software request to PDMA channel n.
     * |        |          |0 = No effect.
     * |        |          |1 = Generate a software request.
     * |        |          |Note1: User can read PDMA_TRGSTS register to know which channel is on active
     * |        |          |Active flag may be triggered by software request or peripheral request.
     * |        |          |Note2: If user does not enable corresponding PDMA channel, the software request will be ignored.
     * |[1]     |SWREQ1    |PDMA Channel N Software Request Register (Write Only)
     * |        |          |Set this bit to 1 to generate a software request to PDMA channel n.
     * |        |          |0 = No effect.
     * |        |          |1 = Generate a software request.
     * |        |          |Note1: User can read PDMA_TRGSTS register to know which channel is on active
     * |        |          |Active flag may be triggered by software request or peripheral request.
     * |        |          |Note2: If user does not enable corresponding PDMA channel, the software request will be ignored.
     * |[2]     |SWREQ2    |PDMA Channel N Software Request Register (Write Only)
     * |        |          |Set this bit to 1 to generate a software request to PDMA channel n.
     * |        |          |0 = No effect.
     * |        |          |1 = Generate a software request.
     * |        |          |Note1: User can read PDMA_TRGSTS register to know which channel is on active
     * |        |          |Active flag may be triggered by software request or peripheral request.
     * |        |          |Note2: If user does not enable corresponding PDMA channel, the software request will be ignored.
     * |[3]     |SWREQ3    |PDMA Channel N Software Request Register (Write Only)
     * |        |          |Set this bit to 1 to generate a software request to PDMA channel n.
     * |        |          |0 = No effect.
     * |        |          |1 = Generate a software request.
     * |        |          |Note1: User can read PDMA_TRGSTS register to know which channel is on active
     * |        |          |Active flag may be triggered by software request or peripheral request.
     * |        |          |Note2: If user does not enable corresponding PDMA channel, the software request will be ignored.
     * |[4]     |SWREQ4    |PDMA Channel N Software Request Register (Write Only)
     * |        |          |Set this bit to 1 to generate a software request to PDMA channel n.
     * |        |          |0 = No effect.
     * |        |          |1 = Generate a software request.
     * |        |          |Note1: User can read PDMA_TRGSTS register to know which channel is on active
     * |        |          |Active flag may be triggered by software request or peripheral request.
     * |        |          |Note2: If user does not enable corresponding PDMA channel, the software request will be ignored.
     * @var PDMA_T::TRGSTS
     * Offset: 0x40C  PDMA Channel Request Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |REQSTS0   |PDMA Channel N Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_RESET register respectively, this bit will be cleared automatically after finishing current transfer.
     * |[1]     |REQSTS1   |PDMA Channel N Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_RESET register respectively, this bit will be cleared automatically after finishing current transfer.
     * |[2]     |REQSTS2   |PDMA Channel N Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_RESET register respectively, this bit will be cleared automatically after finishing current transfer.
     * |[3]     |REQSTS3   |PDMA Channel N Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_RESET register respectively, this bit will be cleared automatically after finishing current transfer.
     * |[4]     |REQSTS4   |PDMA Channel N Request Status (Read Only)
     * |        |          |This flag indicates whether channel[n] have a request or not, no matter request from software or peripheral
     * |        |          |When PDMA controller finishes channel transfer, this bit will be cleared automatically.
     * |        |          |0 = PDMA Channel n has no request.
     * |        |          |1 = PDMA Channel n has a request.
     * |        |          |Note: If user pauses or resets each PDMA transfer by setting PDMA_PAUSE or PDMA_RESET register respectively, this bit will be cleared automatically after finishing current transfer.
     * @var PDMA_T::PRISET
     * Offset: 0x410  PDMA Fixed Priority Setting Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FPRISET0  |PDMA Channel N Fixed Priority Setting Register
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field only set to fixed priority, user should use PDMA_PRICLR register to clear fixed priority.
     * |[1]     |FPRISET1  |PDMA Channel N Fixed Priority Setting Register
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field only set to fixed priority, user should use PDMA_PRICLR register to clear fixed priority.
     * |[2]     |FPRISET2  |PDMA Channel N Fixed Priority Setting Register
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field only set to fixed priority, user should use PDMA_PRICLR register to clear fixed priority.
     * |[3]     |FPRISET3  |PDMA Channel N Fixed Priority Setting Register
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field only set to fixed priority, user should use PDMA_PRICLR register to clear fixed priority.
     * |[4]     |FPRISET4  |PDMA Channel N Fixed Priority Setting Register
     * |        |          |Set this bit to 1 to enable fixed priority level.
     * |        |          |Write Operation:
     * |        |          |0 = No effect.
     * |        |          |1 = Set PDMA channel [n] to fixed priority channel.
     * |        |          |Read Operation:
     * |        |          |0 = Corresponding PDMA channel is round-robin priority.
     * |        |          |1 = Corresponding PDMA channel is fixed priority.
     * |        |          |Note: This field only set to fixed priority, user should use PDMA_PRICLR register to clear fixed priority.
     * @var PDMA_T::PRICLR
     * Offset: 0x414  PDMA Fixed Priority Clear Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FPRICLR0  |PDMA Channel N Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * |[1]     |FPRICLR1  |PDMA Channel N Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * |[2]     |FPRICLR2  |PDMA Channel N Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * |[3]     |FPRICLR3  |PDMA Channel N Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * |[4]     |FPRICLR4  |PDMA Channel N Fixed Priority Clear Register (Write Only)
     * |        |          |Set this bit to 1 to clear fixed priority level.
     * |        |          |0 = No effect.
     * |        |          |1 = Clear PDMA channel [n] fixed priority setting.
     * |        |          |Note: User can read PDMA_PRISET register to know the channel priority.
     * @var PDMA_T::INTEN
     * Offset: 0x418  PDMA Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INTEN0    |PDMA Channel N Interrupt Enable Register
     * |        |          |This field is used for enabling PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * |[1]     |INTEN1    |PDMA Channel N Interrupt Enable Register
     * |        |          |This field is used for enabling PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * |[2]     |INTEN2    |PDMA Channel N Interrupt Enable Register
     * |        |          |This field is used for enabling PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * |[3]     |INTEN3    |PDMA Channel N Interrupt Enable Register
     * |        |          |This field is used for enabling PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * |[4]     |INTEN4    |PDMA Channel N Interrupt Enable Register
     * |        |          |This field is used for enabling PDMA channel[n] interrupt.
     * |        |          |0 = PDMA channel n interrupt Disabled.
     * |        |          |1 = PDMA channel n interrupt Enabled.
     * @var PDMA_T::INTSTS
     * Offset: 0x41C  PDMA Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ABTIF     |PDMA Read/Write Target Abort Interrupt Flag (Read-only)
     * |        |          |This bit indicates that PDMA has target abort error; Software can read PDMA_ABTSTS register to find which channel has target abort error.
     * |        |          |0 = No AHB bus ERROR response received.
     * |        |          |1 = AHB bus ERROR response received.
     * |[1]     |TDIF      |Transfer Done Interrupt Flag (Read Only)
     * |        |          |This bit indicates that PDMA controller has finished transmission; User can read PDMA_TDSTS register to indicate which channel finished transfer.
     * |        |          |0 = Not finished yet.
     * |        |          |1 = PDMA channel has finished transmission.
     * |[2]     |TEIF      |Table Empty Interrupt Flag (Read Only)
     * |        |          |This bit indicates PDMA channel scatter-gather table is empty
     * |        |          |User can read PDMA_SCATSTS register to indicate which channel scatter-gather table is empty.
     * |        |          |0 = PDMA channel scatter-gather table is not empty.
     * |        |          |1 = PDMA channel scatter-gather table is empty.
     * |[8]     |REQTOF0   |PDMA Channel N Request Time-out Flag
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by PDMA_TOCn, user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * |[9]     |REQTOF1   |PDMA Channel N Request Time-out Flag
     * |        |          |This flag indicates that PDMA controller has waited peripheral request for a period defined by PDMA_TOCn, user can write 1 to clear these bits.
     * |        |          |0 = No request time-out.
     * |        |          |1 = Peripheral request time-out.
     * @var PDMA_T::ABTSTS
     * Offset: 0x420  PDMA Channel Read/Write Target Abort Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ABTIF0    |PDMA Channel N Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error or transfer source and destination address not alignment; User can write 1 to clear these bits.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * |[1]     |ABTIF1    |PDMA Channel N Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error or transfer source and destination address not alignment; User can write 1 to clear these bits.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * |[2]     |ABTIF2    |PDMA Channel N Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error or transfer source and destination address not alignment; User can write 1 to clear these bits.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * |[3]     |ABTIF3    |PDMA Channel N Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error or transfer source and destination address not alignment; User can write 1 to clear these bits.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * |[4]     |ABTIF4    |PDMA Channel N Read/Write Target Abort Interrupt Status Flag
     * |        |          |This bit indicates which PDMA controller has target abort error or transfer source and destination address not alignment; User can write 1 to clear these bits.
     * |        |          |0 = No AHB bus ERROR response received when channel n transfer.
     * |        |          |1 = AHB bus ERROR response received when channel n transfer.
     * @var PDMA_T::TDSTS
     * Offset: 0x424  PDMA Channel Transfer Done Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TDIF0     |PDMA Channel N Transfer Done Flag Register
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not, user can write 1 to clear these bits.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * |[1]     |TDIF1     |PDMA Channel N Transfer Done Flag Register
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not, user can write 1 to clear these bits.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * |[2]     |TDIF2     |PDMA Channel N Transfer Done Flag Register
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not, user can write 1 to clear these bits.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * |[3]     |TDIF3     |PDMA Channel N Transfer Done Flag Register
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not, user can write 1 to clear these bits.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * |[4]     |TDIF4     |PDMA Channel N Transfer Done Flag Register
     * |        |          |This bit indicates whether PDMA controller channel transfer has been finished or not, user can write 1 to clear these bits.
     * |        |          |0 = PDMA channel transfer has not finished.
     * |        |          |1 = PDMA channel has finished transmission.
     * @var PDMA_T::SCATSTS
     * Offset: 0x428  PDMA Scatter-Gather Table Empty Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TEMPTYF0  |This bit indicates which PDMA channel table is empty
     * |        |          |when channel have a request ,
     * |        |          |no matter request from software or peripheral,
     * |        |          |but operation mode of channel descriptor table is idle mode,
     * |        |          |or channel has finished current transfer and
     * |        |          |next table operation mode is idle mode for PDMA Scatter-Gather mode.
     * |        |          |User can write 1 to clear these bits.
     * |        |          |0 = PDMA channel scatter-gather table is not empty.
     * |        |          |1 = PDMA channel scatter-gather table is empty.
     * |[1]     |TEMPTYF1  |This bit indicates which PDMA channel table is empty
     * |        |          |when channel have a request ,
     * |        |          |no matter request from software or peripheral,
     * |        |          |but operation mode of channel descriptor table is idle mode,
     * |        |          |or channel has finished current transfer and
     * |        |          |next table operation mode is idle mode for PDMA Scatter-Gather mode.
     * |        |          |User can write 1 to clear these bits.
     * |        |          |0 = PDMA channel scatter-gather table is not empty.
     * |        |          |1 = PDMA channel scatter-gather table is empty.
     * |[2]     |TEMPTYF2  |This bit indicates which PDMA channel table is empty
     * |        |          |when channel have a request ,
     * |        |          |no matter request from software or peripheral,
     * |        |          |but operation mode of channel descriptor table is idle mode,
     * |        |          |or channel has finished current transfer and
     * |        |          |next table operation mode is idle mode for PDMA Scatter-Gather mode.
     * |        |          |User can write 1 to clear these bits.
     * |        |          |0 = PDMA channel scatter-gather table is not empty.
     * |        |          |1 = PDMA channel scatter-gather table is empty.
     * |[3]     |TEMPTYF3  |This bit indicates which PDMA channel table is empty
     * |        |          |when channel have a request ,
     * |        |          |no matter request from software or peripheral,
     * |        |          |but operation mode of channel descriptor table is idle mode,
     * |        |          |or channel has finished current transfer and
     * |        |          |next table operation mode is idle mode for PDMA Scatter-Gather mode.
     * |        |          |User can write 1 to clear these bits.
     * |        |          |0 = PDMA channel scatter-gather table is not empty.
     * |        |          |1 = PDMA channel scatter-gather table is empty.
     * |[4]     |TEMPTYF4  |This bit indicates which PDMA channel table is empty
     * |        |          |when channel have a request ,
     * |        |          |no matter request from software or peripheral,
     * |        |          |but operation mode of channel descriptor table is idle mode,
     * |        |          |or channel has finished current transfer and
     * |        |          |next table operation mode is idle mode for PDMA Scatter-Gather mode.
     * |        |          |User can write 1 to clear these bits.
     * |        |          |0 = PDMA channel scatter-gather table is not empty.
     * |        |          |1 = PDMA channel scatter-gather table is empty.
     * @var PDMA_T::TACTSTS
     * Offset: 0x42C  PDMA Transfer Active Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TXACTF0   |PDMA Channel N Transfer on Active Flag Register (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is not finished.
     * |        |          |1 = PDMA channel is active.
     * |[1]     |TXACTF1   |PDMA Channel N Transfer on Active Flag Register (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is not finished.
     * |        |          |1 = PDMA channel is active.
     * |[2]     |TXACTF2   |PDMA Channel N Transfer on Active Flag Register (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is not finished.
     * |        |          |1 = PDMA channel is active.
     * |[3]     |TXACTF3   |PDMA Channel N Transfer on Active Flag Register (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is not finished.
     * |        |          |1 = PDMA channel is active.
     * |[4]     |TXACTF4   |PDMA Channel N Transfer on Active Flag Register (Read Only)
     * |        |          |This bit indicates which PDMA channel is in active.
     * |        |          |0 = PDMA channel is not finished.
     * |        |          |1 = PDMA channel is active.
     * @var PDMA_T::TOUTPSC
     * Offset: 0x430  PDMA Time-out Prescaler Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TOUTPSC0  |PDMA Channel 0 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 0 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 0 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 0 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 0 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 0 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 0 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 0 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 0 time-out clock source is HCLK/215.
     * |[6:4]   |TOUTPSC1  |PDMA Channel 1 Time-out Clock Source Prescaler Bits
     * |        |          |000 = PDMA channel 1 time-out clock source is HCLK/28.
     * |        |          |001 = PDMA channel 1 time-out clock source is HCLK/29.
     * |        |          |010 = PDMA channel 1 time-out clock source is HCLK/210.
     * |        |          |011 = PDMA channel 1 time-out clock source is HCLK/211.
     * |        |          |100 = PDMA channel 1 time-out clock source is HCLK/212.
     * |        |          |101 = PDMA channel 1 time-out clock source is HCLK/213.
     * |        |          |110 = PDMA channel 1 time-out clock source is HCLK/214.
     * |        |          |111 = PDMA channel 1 time-out clock source is HCLK/215.
     * @var PDMA_T::TOUTEN
     * Offset: 0x434  PDMA Time-out Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TOUTEN0   |PDMA Channel 0 Time-out Enable Bit
     * |        |          |0 = PDMA Channel 0 time-out function Disable.
     * |        |          |1 = PDMA Channel 0 time-out function Enable.
     * |[1]     |TOUTEN1   |PDMA Channel 1 Time-out Enable Bit
     * |        |          |0 = PDMA Channel 1 time-out function Disable.
     * |        |          |1 = PDMA Channel 1 time-out function Enable.
     * @var PDMA_T::TOUTIEN
     * Offset: 0x438  PDMA Time-out Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TOUTIEN0  |PDMA Channel 0 Time-out Interrupt Enable Bit
     * |        |          |0 = PDMA Channel 0 time-out interrupt Disable.
     * |        |          |1 = PDMA Channel 0 time-out interrupt Enable.
     * |[1]     |TOUTIEN1  |PDMA Channel 1 Time-out Interrupt Enable Bit
     * |        |          |0 = PDMA Channel 1 time-out interrupt Disable.
     * |        |          |1 = PDMA Channel 1 time-out interrupt Enable.
     * @var PDMA_T::SCATBA
     * Offset: 0x43C  PDMA Scatter-Gather Descriptor Table Base Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:16] |SCATBA    |PDMA Scatter-gather Descriptor Table Address Register
     * |        |          |In Scatter-Gather mode, this is the base address for calculating the next link - list address
     * |        |          |The next link address equation is
     * |        |          |Next Link Address = PDMA_SCATBA + PDMA_DSCT_FIRST.
     * |        |          |Note: Only useful in Scatter-Gather mode.
     * @var PDMA_T::TOC0_1
     * Offset: 0x440  PDMA Channel 0 and Channel 1 Time-out Counter Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |TOC0      |Time-out Counter for Channel 0
     * |        |          |This controls the period of time-out function for channel 0
     * |        |          |The calculation unit is based on TOUTPSC0 (PDMA_TOUTPSC[2:0]) clock.
     * |        |          |Time-out period = (Period of time-out clock) * (16-bit TOCn),n = 0 ~ 1.
     * |[31:16] |TOC1      |Time-out Counter for Channel 1
     * |        |          |This controls the period of time-out function for channel 1
     * |        |          |The calculation unit is based on TOUTPSC1 (PDMA_TOUTPSC[6:4]) clock
     * |        |          |The example of time-out period can refer TOC0 bit description.
     * @var PDMA_T::RESET
     * Offset: 0x460  PDMA channel Reset Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RESET0    |PDMA Channel N Reset Control Register
     * |        |          |User can set this bit field to reset the PDMA channel.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset PDMA channel n
     * |        |          |When user sets PDMA_RESET bit, the operation will finish the on-going transfer and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable channel after channel reset, PDMA will re-load the channel description table to execute PDMA task.
     * |        |          |Note: This bit will be cleared automatically after finishing reset process.
     * |[1]     |RESET1    |PDMA Channel N Reset Control Register
     * |        |          |User can set this bit field to reset the PDMA channel.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset PDMA channel n
     * |        |          |When user sets PDMA_RESET bit, the operation will finish the on-going transfer and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable channel after channel reset, PDMA will re-load the channel description table to execute PDMA task.
     * |        |          |Note: This bit will be cleared automatically after finishing reset process.
     * |[2]     |RESET2    |PDMA Channel N Reset Control Register
     * |        |          |User can set this bit field to reset the PDMA channel.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset PDMA channel n
     * |        |          |When user sets PDMA_RESET bit, the operation will finish the on-going transfer and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable channel after channel reset, PDMA will re-load the channel description table to execute PDMA task.
     * |        |          |Note: This bit will be cleared automatically after finishing reset process.
     * |[3]     |RESET3    |PDMA Channel N Reset Control Register
     * |        |          |User can set this bit field to reset the PDMA channel.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset PDMA channel n
     * |        |          |When user sets PDMA_RESET bit, the operation will finish the on-going transfer and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable channel after channel reset, PDMA will re-load the channel description table to execute PDMA task.
     * |        |          |Note: This bit will be cleared automatically after finishing reset process.
     * |[4]     |RESET4    |PDMA Channel N Reset Control Register
     * |        |          |User can set this bit field to reset the PDMA channel.
     * |        |          |0 = No effect.
     * |        |          |1 = Reset PDMA channel n
     * |        |          |When user sets PDMA_RESET bit, the operation will finish the on-going transfer and then clear the channel enable bit (PDMA_CHCTL [CHEN]) and clear request active flag
     * |        |          |If re-enable channel after channel reset, PDMA will re-load the channel description table to execute PDMA task.
     * |        |          |Note: This bit will be cleared automatically after finishing reset process.
     * @var PDMA_T::REQSEL0_3
     * Offset: 0x480  PDMA Channel 0 to Channel 3 Request Source Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |REQSRC0   |Channel 0 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 0
     * |        |          |User can configure the peripheral by setting REQSRC0.
     * |        |          |0 = Disable PDMA peripheral request.
     * |        |          |1 = reserved.
     * |        |          |4 = Channel connects to UART_TX.
     * |        |          |5 = Channel connects to UART_RX.
     * |        |          |6 = Reserved.
     * |        |          |7 = Reserved.
     * |        |          |8 = Reserved.
     * |        |          |9 = Reserved.
     * |        |          |10 = Channel connects to USCI_TX.
     * |        |          |11 = Channel connects to USCI_RX.
     * |        |          |12 = Reserved.
     * |        |          |13 = Reserved.
     * |        |          |14 = Reserved.
     * |        |          |15 = Reserved.
     * |        |          |16 = Channel connects to SPI_TX.
     * |        |          |17 = Channel connects to SPI_RX.
     * |        |          |18 = Reserved.
     * |        |          |19 = Reserved.
     * |        |          |20 = Channel connects to ADC_RX.
     * |        |          |21 = Channel connects to PWM0_P0_RX.
     * |        |          |22 = Channel connects to PWM0_P1_RX.
     * |        |          |23 = Channel connects to PWM0_P2_RX.
     * |        |          |24 = Channel connects to PWM1_P0_RX.
     * |        |          |25 = Channel connects to PWM1_P1_RX.
     * |        |          |26 = Channel connects to PWM1_P2_RX.
     * |        |          |27 = Reserved.
     * |        |          |28 = Channel connects to I2C0_TX.
     * |        |          |29 = Channel connects to I2C0_RX.
     * |        |          |30 = Channel connects to I2C1_TX.
     * |        |          |31 = Channel connects to I2C1_RX.
     * |        |          |32 = Channel connects to TMR0.
     * |        |          |33 = Channel connects to TMR1.
     * |        |          |34 = Channel connects to TMR2.
     * |        |          |35 = Channel connects to TMR3.
     * |        |          |Others = Reserved.
     * |        |          |Note 1: A peripheral can't assign to two channels at the same time.
     * |        |          |Note 2: This field is useless when transfer between memory and memory.
     * |[13:8]  |REQSRC1   |Channel 1 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 1
     * |        |          |User can configure the peripheral setting by REQSRC1.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[21:16] |REQSRC2   |Channel 2 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 2
     * |        |          |User can configure the peripheral setting by REQSRC2.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * |[29:24] |REQSRC3   |Channel 3 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 3
     * |        |          |User can configure the peripheral setting by REQSRC3.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     * @var PDMA_T::REQSEL4
     * Offset: 0x484  PDMA Channel 4 Request Source Select Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |REQSRC4   |Channel 4 Request Source Selection
     * |        |          |This filed defines which peripheral is connected to PDMA channel 4
     * |        |          |User can configure the peripheral setting by REQSRC4.
     * |        |          |Note: The channel configuration is the same as REQSRC0 field
     * |        |          |Please refer to the explanation of REQSRC0.
     */
    PDMA_DSCT_T   DSCT[5];               /*!< [0x0000~0x004C] Descriptor Table Control Register of PDMA Channel 0~4     */
    __I  uint32_t CURSCAT[5];            /*!< [0x0050~0x0060] Current Scatter-Gather Descriptor Table Address of PDMA Channel 0~4 */
    __I  uint32_t RESERVE0[231];
    __IO uint32_t CHCTL;                 /*!< [0x0400] PDMA Channel Control Register                                    */
    __O  uint32_t PAUSE;                 /*!< [0x0404] PDMA Transfer Pause Control Register                             */
    __O  uint32_t SWREQ;                 /*!< [0x0408] PDMA Software Request Register                                   */
    __I  uint32_t TRGSTS;                /*!< [0x040c] PDMA Channel Request Status Register                             */
    __IO uint32_t PRISET;                /*!< [0x0410] PDMA Fixed Priority Setting Register                             */
    __O  uint32_t PRICLR;                /*!< [0x0414] PDMA Fixed Priority Clear Register                               */
    __IO uint32_t INTEN;                 /*!< [0x0418] PDMA Interrupt Enable Register                                   */
    __IO uint32_t INTSTS;                /*!< [0x041c] PDMA Interrupt Status Register                                   */
    __IO uint32_t ABTSTS;                /*!< [0x0420] PDMA Channel Read/Write Target Abort Flag Register               */
    __IO uint32_t TDSTS;                 /*!< [0x0424] PDMA Channel Transfer Done Flag Register                         */
    __IO uint32_t SCATSTS;               /*!< [0x0428] PDMA Scatter-Gather Table Empty Status Register                  */
    __I  uint32_t TACTSTS;               /*!< [0x042c] PDMA Transfer Active Flag Register                               */
    __IO uint32_t TOUTPSC;               /*!< [0x0430] PDMA Time-out Prescaler Register                                 */
    __IO uint32_t TOUTEN;                /*!< [0x0434] PDMA Time-out Enable Register                                    */
    __IO uint32_t TOUTIEN;               /*!< [0x0438] PDMA Time-out Interrupt Enable Register                          */
    __IO uint32_t SCATBA;                /*!< [0x043c] PDMA Scatter-Gather Descriptor Table Base Address Register       */
    __IO uint32_t TOC0_1;                /*!< [0x0440] PDMA Channel 0 and Channel 1 Time-out Counter Register           */
    __I  uint32_t RESERVE1[7];
    __IO uint32_t RESET;                 /*!< [0x0460] PDMA channel Reset Control Register                              */
    __I  uint32_t RESERVE2[7];
    __IO uint32_t REQSEL0_3;             /*!< [0x0480] PDMA Channel 0 to Channel 3 Request Source Select Register       */
    __IO uint32_t REQSEL4;               /*!< [0x0484] PDMA Channel 4 Request Source Select Register                    */
} PDMA_T;

/**
    @addtogroup PDMA_CONST PDMA Bit Field Definition
    Constant Definitions for PDMA Controller
@{ */

#define PDMA_DSCT_CTL_OPMODE_Pos        (0)                                                /*!< PDMA_T::DSCT_CTL: OPMODE Position      */
#define PDMA_DSCT_CTL_OPMODE_Msk        (0x3ul << PDMA_DSCT_CTL_OPMODE_Pos)                /*!< PDMA_T::DSCT_CTL: OPMODE Mask          */

#define PDMA_DSCT_CTL_TXTYPE_Pos        (2)                                                /*!< PDMA_T::DSCT_CTL: TXTYPE Position      */
#define PDMA_DSCT_CTL_TXTYPE_Msk        (0x1ul << PDMA_DSCT_CTL_TXTYPE_Pos)                /*!< PDMA_T::DSCT_CTL: TXTYPE Mask          */

#define PDMA_DSCT_CTL_BURSIZE_Pos       (4)                                                /*!< PDMA_T::DSCT_CTL: BURSIZE Position     */
#define PDMA_DSCT_CTL_BURSIZE_Msk       (0x7ul << PDMA_DSCT_CTL_BURSIZE_Pos)               /*!< PDMA_T::DSCT_CTL: BURSIZE Mask         */

#define PDMA_DSCT_CTL_TBINTDIS_Pos      (7)                                                /*!< PDMA_T::DSCT_CTL: TBINTDIS Position    */
#define PDMA_DSCT_CTL_TBINTDIS_Msk      (0x1ul << PDMA_DSCT_CTL_TBINTDIS_Pos)              /*!< PDMA_T::DSCT_CTL: TBINTDIS Mask        */

#define PDMA_DSCT_CTL_SAINC_Pos         (8)                                                /*!< PDMA_T::DSCT_CTL: SAINC Position       */
#define PDMA_DSCT_CTL_SAINC_Msk         (0x3ul << PDMA_DSCT_CTL_SAINC_Pos)                 /*!< PDMA_T::DSCT_CTL: SAINC Mask           */

#define PDMA_DSCT_CTL_DAINC_Pos         (10)                                               /*!< PDMA_T::DSCT_CTL: DAINC Position       */
#define PDMA_DSCT_CTL_DAINC_Msk         (0x3ul << PDMA_DSCT_CTL_DAINC_Pos)                 /*!< PDMA_T::DSCT_CTL: DAINC Mask           */

#define PDMA_DSCT_CTL_TXWIDTH_Pos       (12)                                               /*!< PDMA_T::DSCT_CTL: TXWIDTH Position     */
#define PDMA_DSCT_CTL_TXWIDTH_Msk       (0x3ul << PDMA_DSCT_CTL_TXWIDTH_Pos)               /*!< PDMA_T::DSCT_CTL: TXWIDTH Mask         */

#define PDMA_DSCT_CTL_TXCNT_Pos         (16)                                               /*!< PDMA_T::DSCT_CTL: TXCNT Position       */
#define PDMA_DSCT_CTL_TXCNT_Msk         (0x3ffful << PDMA_DSCT_CTL_TXCNT_Pos)              /*!< PDMA_T::DSCT_CTL: TXCNT Mask           */

#define PDMA_DSCT_SA_SA_Pos             (0)                                                /*!< PDMA_T::DSCT_SA: SA Position           */
#define PDMA_DSCT_SA_SA_Msk             (0xfffffffful << PDMA_DSCT_SA_SA_Pos)              /*!< PDMA_T::DSCT_SA: SA Mask               */

#define PDMA_DSCT_DA_DA_Pos             (0)                                                /*!< PDMA_T::DSCT_DA: DA Position           */
#define PDMA_DSCT_DA_DA_Msk             (0xfffffffful << PDMA_DSCT_DA_DA_Pos)              /*!< PDMA_T::DSCT_DA: DA Mask               */

#define PDMA_DSCT_FIRST_FIRST_Pos       (0)                                                /*!< PDMA_T::DSCT_FIRST: FIRST Position     */
#define PDMA_DSCT_FIRST_FIRST_Msk       (0xfffful << PDMA_DSCT_FIRST_FIRST_Pos)            /*!< PDMA_T::DSCT_FIRST: FIRST Mask         */

#define PDMA_CHCTL_CHEN0_Pos             (0)                                               /*!< PDMA_T::CHCTL: CHEN0 Position          */
#define PDMA_CHCTL_CHEN0_Msk             (0x1ul << PDMA_CHCTL_CHEN0_Pos)                   /*!< PDMA_T::CHCTL: CHEN0 Mask              */

#define PDMA_CHCTL_CHEN1_Pos             (1)                                               /*!< PDMA_T::CHCTL: CHEN1 Position          */
#define PDMA_CHCTL_CHEN1_Msk             (0x1ul << PDMA_CHCTL_CHEN1_Pos)                   /*!< PDMA_T::CHCTL: CHEN1 Mask              */

#define PDMA_CHCTL_CHEN2_Pos             (2)                                               /*!< PDMA_T::CHCTL: CHEN2 Position          */
#define PDMA_CHCTL_CHEN2_Msk             (0x1ul << PDMA_CHCTL_CHEN2_Pos)                   /*!< PDMA_T::CHCTL: CHEN2 Mask              */

#define PDMA_CHCTL_CHEN3_Pos             (3)                                               /*!< PDMA_T::CHCTL: CHEN3 Position          */
#define PDMA_CHCTL_CHEN3_Msk             (0x1ul << PDMA_CHCTL_CHEN3_Pos)                   /*!< PDMA_T::CHCTL: CHEN3 Mask              */

#define PDMA_CHCTL_CHEN4_Pos             (4)                                               /*!< PDMA_T::CHCTL: CHEN4 Position          */
#define PDMA_CHCTL_CHEN4_Msk             (0x1ul << PDMA_CHCTL_CHEN4_Pos)                   /*!< PDMA_T::CHCTL: CHEN4 Mask              */

#define PDMA_PAUSE_PAUSE0_Pos            (0)                                               /*!< PDMA_T::PAUSE: PAUSE0 Position         */
#define PDMA_PAUSE_PAUSE0_Msk            (0x1ul << PDMA_PAUSE_PAUSE0_Pos)                  /*!< PDMA_T::PAUSE: PAUSE0 Mask             */

#define PDMA_PAUSE_PAUSE1_Pos            (1)                                               /*!< PDMA_T::PAUSE: PAUSE1 Position         */
#define PDMA_PAUSE_PAUSE1_Msk            (0x1ul << PDMA_PAUSE_PAUSE1_Pos)                  /*!< PDMA_T::PAUSE: PAUSE1 Mask             */

#define PDMA_PAUSE_PAUSE2_Pos            (2)                                               /*!< PDMA_T::PAUSE: PAUSE2 Position         */
#define PDMA_PAUSE_PAUSE2_Msk            (0x1ul << PDMA_PAUSE_PAUSE2_Pos)                  /*!< PDMA_T::PAUSE: PAUSE2 Mask             */

#define PDMA_PAUSE_PAUSE3_Pos            (3)                                               /*!< PDMA_T::PAUSE: PAUSE3 Position         */
#define PDMA_PAUSE_PAUSE3_Msk            (0x1ul << PDMA_PAUSE_PAUSE3_Pos)                  /*!< PDMA_T::PAUSE: PAUSE3 Mask             */

#define PDMA_PAUSE_PAUSE4_Pos            (4)                                               /*!< PDMA_T::PAUSE: PAUSE4 Position         */
#define PDMA_PAUSE_PAUSE4_Msk            (0x1ul << PDMA_PAUSE_PAUSE4_Pos)                  /*!< PDMA_T::PAUSE: PAUSE4 Mask             */

#define PDMA_SWREQ_SWREQ0_Pos            (0)                                               /*!< PDMA_T::SWREQ: SWREQ0 Position         */
#define PDMA_SWREQ_SWREQ0_Msk            (0x1ul << PDMA_SWREQ_SWREQ0_Pos)                  /*!< PDMA_T::SWREQ: SWREQ0 Mask             */

#define PDMA_SWREQ_SWREQ1_Pos            (1)                                               /*!< PDMA_T::SWREQ: SWREQ1 Position         */
#define PDMA_SWREQ_SWREQ1_Msk            (0x1ul << PDMA_SWREQ_SWREQ1_Pos)                  /*!< PDMA_T::SWREQ: SWREQ1 Mask             */

#define PDMA_SWREQ_SWREQ2_Pos            (2)                                               /*!< PDMA_T::SWREQ: SWREQ2 Position         */
#define PDMA_SWREQ_SWREQ2_Msk            (0x1ul << PDMA_SWREQ_SWREQ2_Pos)                  /*!< PDMA_T::SWREQ: SWREQ2 Mask             */

#define PDMA_SWREQ_SWREQ3_Pos            (3)                                               /*!< PDMA_T::SWREQ: SWREQ3 Position         */
#define PDMA_SWREQ_SWREQ3_Msk            (0x1ul << PDMA_SWREQ_SWREQ3_Pos)                  /*!< PDMA_T::SWREQ: SWREQ3 Mask             */

#define PDMA_SWREQ_SWREQ4_Pos            (4)                                               /*!< PDMA_T::SWREQ: SWREQ4 Position         */
#define PDMA_SWREQ_SWREQ4_Msk            (0x1ul << PDMA_SWREQ_SWREQ4_Pos)                  /*!< PDMA_T::SWREQ: SWREQ4 Mask             */

#define PDMA_TRGSTS_REQSTS0_Pos          (0)                                               /*!< PDMA_T::TRGSTS: REQSTS0 Position       */
#define PDMA_TRGSTS_REQSTS0_Msk          (0x1ul << PDMA_TRGSTS_REQSTS0_Pos)                /*!< PDMA_T::TRGSTS: REQSTS0 Mask           */

#define PDMA_TRGSTS_REQSTS1_Pos          (1)                                               /*!< PDMA_T::TRGSTS: REQSTS1 Position       */
#define PDMA_TRGSTS_REQSTS1_Msk          (0x1ul << PDMA_TRGSTS_REQSTS1_Pos)                /*!< PDMA_T::TRGSTS: REQSTS1 Mask           */

#define PDMA_TRGSTS_REQSTS2_Pos          (2)                                               /*!< PDMA_T::TRGSTS: REQSTS2 Position       */
#define PDMA_TRGSTS_REQSTS2_Msk          (0x1ul << PDMA_TRGSTS_REQSTS2_Pos)                /*!< PDMA_T::TRGSTS: REQSTS2 Mask           */

#define PDMA_TRGSTS_REQSTS3_Pos          (3)                                               /*!< PDMA_T::TRGSTS: REQSTS3 Position       */
#define PDMA_TRGSTS_REQSTS3_Msk          (0x1ul << PDMA_TRGSTS_REQSTS3_Pos)                /*!< PDMA_T::TRGSTS: REQSTS3 Mask           */

#define PDMA_TRGSTS_REQSTS4_Pos          (4)                                               /*!< PDMA_T::TRGSTS: REQSTS4 Position       */
#define PDMA_TRGSTS_REQSTS4_Msk          (0x1ul << PDMA_TRGSTS_REQSTS4_Pos)                /*!< PDMA_T::TRGSTS: REQSTS4 Mask           */

#define PDMA_PRISET_FPRISET0_Pos         (0)                                               /*!< PDMA_T::PRISET: FPRISET0 Position      */
#define PDMA_PRISET_FPRISET0_Msk         (0x1ul << PDMA_PRISET_FPRISET0_Pos)               /*!< PDMA_T::PRISET: FPRISET0 Mask          */

#define PDMA_PRISET_FPRISET1_Pos         (1)                                               /*!< PDMA_T::PRISET: FPRISET1 Position      */
#define PDMA_PRISET_FPRISET1_Msk         (0x1ul << PDMA_PRISET_FPRISET1_Pos)               /*!< PDMA_T::PRISET: FPRISET1 Mask          */

#define PDMA_PRISET_FPRISET2_Pos         (2)                                               /*!< PDMA_T::PRISET: FPRISET2 Position      */
#define PDMA_PRISET_FPRISET2_Msk         (0x1ul << PDMA_PRISET_FPRISET2_Pos)               /*!< PDMA_T::PRISET: FPRISET2 Mask          */

#define PDMA_PRISET_FPRISET3_Pos         (3)                                               /*!< PDMA_T::PRISET: FPRISET3 Position      */
#define PDMA_PRISET_FPRISET3_Msk         (0x1ul << PDMA_PRISET_FPRISET3_Pos)               /*!< PDMA_T::PRISET: FPRISET3 Mask          */

#define PDMA_PRISET_FPRISET4_Pos         (4)                                               /*!< PDMA_T::PRISET: FPRISET4 Position      */
#define PDMA_PRISET_FPRISET4_Msk         (0x1ul << PDMA_PRISET_FPRISET4_Pos)               /*!< PDMA_T::PRISET: FPRISET4 Mask          */

#define PDMA_PRICLR_FPRICLR0_Pos         (0)                                               /*!< PDMA_T::PRICLR: FPRICLR0 Position      */
#define PDMA_PRICLR_FPRICLR0_Msk         (0x1ul << PDMA_PRICLR_FPRICLR0_Pos)               /*!< PDMA_T::PRICLR: FPRICLR0 Mask          */

#define PDMA_PRICLR_FPRICLR1_Pos         (1)                                               /*!< PDMA_T::PRICLR: FPRICLR1 Position      */
#define PDMA_PRICLR_FPRICLR1_Msk         (0x1ul << PDMA_PRICLR_FPRICLR1_Pos)               /*!< PDMA_T::PRICLR: FPRICLR1 Mask          */

#define PDMA_PRICLR_FPRICLR2_Pos         (2)                                               /*!< PDMA_T::PRICLR: FPRICLR2 Position      */
#define PDMA_PRICLR_FPRICLR2_Msk         (0x1ul << PDMA_PRICLR_FPRICLR2_Pos)               /*!< PDMA_T::PRICLR: FPRICLR2 Mask          */

#define PDMA_PRICLR_FPRICLR3_Pos         (3)                                               /*!< PDMA_T::PRICLR: FPRICLR3 Position      */
#define PDMA_PRICLR_FPRICLR3_Msk         (0x1ul << PDMA_PRICLR_FPRICLR3_Pos)               /*!< PDMA_T::PRICLR: FPRICLR3 Mask          */

#define PDMA_PRICLR_FPRICLR4_Pos         (4)                                               /*!< PDMA_T::PRICLR: FPRICLR4 Position      */
#define PDMA_PRICLR_FPRICLR4_Msk         (0x1ul << PDMA_PRICLR_FPRICLR4_Pos)               /*!< PDMA_T::PRICLR: FPRICLR4 Mask          */

#define PDMA_INTEN_INTEN0_Pos            (0)                                               /*!< PDMA_T::INTEN: INTEN0 Position         */
#define PDMA_INTEN_INTEN0_Msk            (0x1ul << PDMA_INTEN_INTEN0_Pos)                  /*!< PDMA_T::INTEN: INTEN0 Mask             */

#define PDMA_INTEN_INTEN1_Pos            (1)                                               /*!< PDMA_T::INTEN: INTEN1 Position         */
#define PDMA_INTEN_INTEN1_Msk            (0x1ul << PDMA_INTEN_INTEN1_Pos)                  /*!< PDMA_T::INTEN: INTEN1 Mask             */

#define PDMA_INTEN_INTEN2_Pos            (2)                                               /*!< PDMA_T::INTEN: INTEN2 Position         */
#define PDMA_INTEN_INTEN2_Msk            (0x1ul << PDMA_INTEN_INTEN2_Pos)                  /*!< PDMA_T::INTEN: INTEN2 Mask             */

#define PDMA_INTEN_INTEN3_Pos            (3)                                               /*!< PDMA_T::INTEN: INTEN3 Position         */
#define PDMA_INTEN_INTEN3_Msk            (0x1ul << PDMA_INTEN_INTEN3_Pos)                  /*!< PDMA_T::INTEN: INTEN3 Mask             */

#define PDMA_INTEN_INTEN4_Pos            (4)                                               /*!< PDMA_T::INTEN: INTEN4 Position         */
#define PDMA_INTEN_INTEN4_Msk            (0x1ul << PDMA_INTEN_INTEN4_Pos)                  /*!< PDMA_T::INTEN: INTEN4 Mask             */

#define PDMA_INTSTS_ABTIF_Pos            (0)                                               /*!< PDMA_T::INTSTS: ABTIF Position         */
#define PDMA_INTSTS_ABTIF_Msk            (0x1ul << PDMA_INTSTS_ABTIF_Pos)                  /*!< PDMA_T::INTSTS: ABTIF Mask             */

#define PDMA_INTSTS_TDIF_Pos             (1)                                               /*!< PDMA_T::INTSTS: TDIF Position          */
#define PDMA_INTSTS_TDIF_Msk             (0x1ul << PDMA_INTSTS_TDIF_Pos)                   /*!< PDMA_T::INTSTS: TDIF Mask              */

#define PDMA_INTSTS_TEIF_Pos             (2)                                               /*!< PDMA_T::INTSTS: TEIF Position          */
#define PDMA_INTSTS_TEIF_Msk             (0x1ul << PDMA_INTSTS_TEIF_Pos)                   /*!< PDMA_T::INTSTS: TEIF Mask              */

#define PDMA_INTSTS_REQTOF0_Pos          (8)                                               /*!< PDMA_T::INTSTS: REQTOF0 Position       */
#define PDMA_INTSTS_REQTOF0_Msk          (0x1ul << PDMA_INTSTS_REQTOF0_Pos)                /*!< PDMA_T::INTSTS: REQTOF0 Mask           */

#define PDMA_INTSTS_REQTOF1_Pos          (9)                                               /*!< PDMA_T::INTSTS: REQTOF1 Position       */
#define PDMA_INTSTS_REQTOF1_Msk          (0x1ul << PDMA_INTSTS_REQTOF1_Pos)                /*!< PDMA_T::INTSTS: REQTOF1 Mask           */

#define PDMA_ABTSTS_ABTIF0_Pos           (0)                                               /*!< PDMA_T::ABTSTS: ABTIF0 Position        */
#define PDMA_ABTSTS_ABTIF0_Msk           (0x1ul << PDMA_ABTSTS_ABTIF0_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF0 Mask            */

#define PDMA_ABTSTS_ABTIF1_Pos           (1)                                               /*!< PDMA_T::ABTSTS: ABTIF1 Position        */
#define PDMA_ABTSTS_ABTIF1_Msk           (0x1ul << PDMA_ABTSTS_ABTIF1_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF1 Mask            */

#define PDMA_ABTSTS_ABTIF2_Pos           (2)                                               /*!< PDMA_T::ABTSTS: ABTIF2 Position        */
#define PDMA_ABTSTS_ABTIF2_Msk           (0x1ul << PDMA_ABTSTS_ABTIF2_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF2 Mask            */

#define PDMA_ABTSTS_ABTIF3_Pos           (3)                                               /*!< PDMA_T::ABTSTS: ABTIF3 Position        */
#define PDMA_ABTSTS_ABTIF3_Msk           (0x1ul << PDMA_ABTSTS_ABTIF3_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF3 Mask            */

#define PDMA_ABTSTS_ABTIF4_Pos           (4)                                               /*!< PDMA_T::ABTSTS: ABTIF4 Position        */
#define PDMA_ABTSTS_ABTIF4_Msk           (0x1ul << PDMA_ABTSTS_ABTIF4_Pos)                 /*!< PDMA_T::ABTSTS: ABTIF4 Mask            */

#define PDMA_TDSTS_TDIF0_Pos             (0)                                               /*!< PDMA_T::TDSTS: TDIF0 Position          */
#define PDMA_TDSTS_TDIF0_Msk             (0x1ul << PDMA_TDSTS_TDIF0_Pos)                   /*!< PDMA_T::TDSTS: TDIF0 Mask              */

#define PDMA_TDSTS_TDIF1_Pos             (1)                                               /*!< PDMA_T::TDSTS: TDIF1 Position          */
#define PDMA_TDSTS_TDIF1_Msk             (0x1ul << PDMA_TDSTS_TDIF1_Pos)                   /*!< PDMA_T::TDSTS: TDIF1 Mask              */

#define PDMA_TDSTS_TDIF2_Pos             (2)                                               /*!< PDMA_T::TDSTS: TDIF2 Position          */
#define PDMA_TDSTS_TDIF2_Msk             (0x1ul << PDMA_TDSTS_TDIF2_Pos)                   /*!< PDMA_T::TDSTS: TDIF2 Mask              */

#define PDMA_TDSTS_TDIF3_Pos             (3)                                               /*!< PDMA_T::TDSTS: TDIF3 Position          */
#define PDMA_TDSTS_TDIF3_Msk             (0x1ul << PDMA_TDSTS_TDIF3_Pos)                   /*!< PDMA_T::TDSTS: TDIF3 Mask              */

#define PDMA_TDSTS_TDIF4_Pos             (4)                                               /*!< PDMA_T::TDSTS: TDIF4 Position          */
#define PDMA_TDSTS_TDIF4_Msk             (0x1ul << PDMA_TDSTS_TDIF4_Pos)                   /*!< PDMA_T::TDSTS: TDIF4 Mask              */

#define PDMA_SCATSTS_TEMPTYF0_Pos        (0)                                               /*!< PDMA_T::SCATST: TEMPTYF0 Position      */
#define PDMA_SCATSTS_TEMPTYF0_Msk        (0x1ul << PDMA_SCATSTS_TEMPTYF0_Pos)              /*!< PDMA_T::SCATST: TEMPTYF0 Mask          */

#define PDMA_SCATSTS_TEMPTYF1_Pos        (1)                                               /*!< PDMA_T::SCATST: TEMPTYF1 Position      */
#define PDMA_SCATSTS_TEMPTYF1_Msk        (0x1ul << PDMA_SCATSTS_TEMPTYF1_Pos)              /*!< PDMA_T::SCATST: TEMPTYF1 Mask          */

#define PDMA_SCATSTS_TEMPTYF2_Pos        (2)                                               /*!< PDMA_T::SCATST: TEMPTYF2 Position      */
#define PDMA_SCATSTS_TEMPTYF2_Msk        (0x1ul << PDMA_SCATSTS_TEMPTYF2_Pos)              /*!< PDMA_T::SCATST: TEMPTYF2 Mask          */

#define PDMA_SCATSTS_TEMPTYF3_Pos        (3)                                               /*!< PDMA_T::SCATST: TEMPTYF3 Position      */
#define PDMA_SCATSTS_TEMPTYF3_Msk        (0x1ul << PDMA_SCATSTS_TEMPTYF3_Pos)              /*!< PDMA_T::SCATST: TEMPTYF3 Mask          */

#define PDMA_SCATSTS_TEMPTYF4_Pos        (4)                                               /*!< PDMA_T::SCATST: TEMPTYF4 Position      */
#define PDMA_SCATSTS_TEMPTYF4_Msk        (0x1ul << PDMA_SCATSTS_TEMPTYF4_Pos)              /*!< PDMA_T::SCATST: TEMPTYF4 Mask          */

#define PDMA_TACTSTS_TXACTF0_Pos         (0)                                               /*!< PDMA_T::TACTSTS: TXACTF0 Position      */
#define PDMA_TACTSTS_TXACTF0_Msk         (0x1ul << PDMA_TACTSTS_TXACTF0_Pos)               /*!< PDMA_T::TACTSTS: TXACTF0 Mask          */

#define PDMA_TACTSTS_TXACTF1_Pos         (1)                                               /*!< PDMA_T::TACTSTS: TXACTF1 Position      */
#define PDMA_TACTSTS_TXACTF1_Msk         (0x1ul << PDMA_TACTSTS_TXACTF1_Pos)               /*!< PDMA_T::TACTSTS: TXACTF1 Mask          */

#define PDMA_TACTSTS_TXACTF2_Pos         (2)                                               /*!< PDMA_T::TACTSTS: TXACTF2 Position      */
#define PDMA_TACTSTS_TXACTF2_Msk         (0x1ul << PDMA_TACTSTS_TXACTF2_Pos)               /*!< PDMA_T::TACTSTS: TXACTF2 Mask          */

#define PDMA_TACTSTS_TXACTF3_Pos         (3)                                               /*!< PDMA_T::TACTSTS: TXACTF3 Position      */
#define PDMA_TACTSTS_TXACTF3_Msk         (0x1ul << PDMA_TACTSTS_TXACTF3_Pos)               /*!< PDMA_T::TACTSTS: TXACTF3 Mask          */

#define PDMA_TACTSTS_TXACTF4_Pos         (4)                                               /*!< PDMA_T::TACTSTS: TXACTF4 Position      */
#define PDMA_TACTSTS_TXACTF4_Msk         (0x1ul << PDMA_TACTSTS_TXACTF4_Pos)               /*!< PDMA_T::TACTSTS: TXACTF4 Mask          */

#define PDMA_TOUTPSC_TOUTPSC0_Pos        (0)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC0 Position     */
#define PDMA_TOUTPSC_TOUTPSC0_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC0_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC0 Mask         */

#define PDMA_TOUTPSC_TOUTPSC1_Pos        (4)                                               /*!< PDMA_T::TOUTPSC: TOUTPSC1 Position     */
#define PDMA_TOUTPSC_TOUTPSC1_Msk        (0x7ul << PDMA_TOUTPSC_TOUTPSC1_Pos)              /*!< PDMA_T::TOUTPSC: TOUTPSC1 Mask         */

#define PDMA_TOUTEN_TOUTEN0_Pos          (0)                                               /*!< PDMA_T::TOUTEN: TOUTEN0 Position       */
#define PDMA_TOUTEN_TOUTEN0_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN0_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN0 Mask           */

#define PDMA_TOUTEN_TOUTEN1_Pos          (1)                                               /*!< PDMA_T::TOUTEN: TOUTEN1 Position       */
#define PDMA_TOUTEN_TOUTEN1_Msk          (0x1ul << PDMA_TOUTEN_TOUTEN1_Pos)                /*!< PDMA_T::TOUTEN: TOUTEN1 Mask           */

#define PDMA_TOUTIEN_TOUTIEN0_Pos        (0)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN0 Position     */
#define PDMA_TOUTIEN_TOUTIEN0_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN0_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN0 Mask         */

#define PDMA_TOUTIEN_TOUTIEN1_Pos        (1)                                               /*!< PDMA_T::TOUTIEN: TOUTIEN1 Position     */
#define PDMA_TOUTIEN_TOUTIEN1_Msk        (0x1ul << PDMA_TOUTIEN_TOUTIEN1_Pos)              /*!< PDMA_T::TOUTIEN: TOUTIEN1 Mask         */

#define PDMA_SCATBA_SCATBA_Pos           (16)                                              /*!< PDMA_T::SCATBA: SCATBA Position        */
#define PDMA_SCATBA_SCATBA_Msk           (0xfffful << PDMA_SCATBA_SCATBA_Pos)              /*!< PDMA_T::SCATBA: SCATBA Mask            */

#define PDMA_TOC0_1_TOC0_Pos             (0)                                               /*!< PDMA_T::TOC0_1: TOC0 Position          */
#define PDMA_TOC0_1_TOC0_Msk             (0xfffful << PDMA_TOC0_1_TOC0_Pos)                /*!< PDMA_T::TOC0_1: TOC0 Mask              */

#define PDMA_TOC0_1_TOC1_Pos             (16)                                              /*!< PDMA_T::TOC0_1: TOC1 Position          */
#define PDMA_TOC0_1_TOC1_Msk             (0xfffful << PDMA_TOC0_1_TOC1_Pos)                /*!< PDMA_T::TOC0_1: TOC1 Mask              */

#define PDMA_RESET_RESET0_Pos            (0)                                               /*!< PDMA_T::RESET: RESET0 Position         */
#define PDMA_RESET_RESET0_Msk            (0x1ul << PDMA_RESET_RESET0_Pos)                  /*!< PDMA_T::RESET: RESET0 Mask             */

#define PDMA_RESET_RESET1_Pos            (1)                                               /*!< PDMA_T::RESET: RESET1 Position         */
#define PDMA_RESET_RESET1_Msk            (0x1ul << PDMA_RESET_RESET1_Pos)                  /*!< PDMA_T::RESET: RESET1 Mask             */

#define PDMA_RESET_RESET2_Pos            (2)                                               /*!< PDMA_T::RESET: RESET2 Position         */
#define PDMA_RESET_RESET2_Msk            (0x1ul << PDMA_RESET_RESET2_Pos)                  /*!< PDMA_T::RESET: RESET2 Mask             */

#define PDMA_RESET_RESET3_Pos            (3)                                               /*!< PDMA_T::RESET: RESET3 Position         */
#define PDMA_RESET_RESET3_Msk            (0x1ul << PDMA_RESET_RESET3_Pos)                  /*!< PDMA_T::RESET: RESET3 Mask             */

#define PDMA_RESET_RESET4_Pos            (4)                                               /*!< PDMA_T::RESET: RESET4 Position         */
#define PDMA_RESET_RESET4_Msk            (0x1ul << PDMA_RESET_RESET4_Pos)                  /*!< PDMA_T::RESET: RESET4 Mask             */

#define PDMA_REQSEL0_3_REQSRC0_Pos       (0)                                               /*!< PDMA_T::REQSEL0_3: REQSRC0 Position    */
#define PDMA_REQSEL0_3_REQSRC0_Msk       (0x3ful << PDMA_REQSEL0_3_REQSRC0_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC0 Mask        */

#define PDMA_REQSEL0_3_REQSRC1_Pos       (8)                                               /*!< PDMA_T::REQSEL0_3: REQSRC1 Position    */
#define PDMA_REQSEL0_3_REQSRC1_Msk       (0x3ful << PDMA_REQSEL0_3_REQSRC1_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC1 Mask        */

#define PDMA_REQSEL0_3_REQSRC2_Pos       (16)                                              /*!< PDMA_T::REQSEL0_3: REQSRC2 Position    */
#define PDMA_REQSEL0_3_REQSRC2_Msk       (0x3ful << PDMA_REQSEL0_3_REQSRC2_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC2 Mask        */

#define PDMA_REQSEL0_3_REQSRC3_Pos       (24)                                              /*!< PDMA_T::REQSEL0_3: REQSRC3 Position    */
#define PDMA_REQSEL0_3_REQSRC3_Msk       (0x3ful << PDMA_REQSEL0_3_REQSRC3_Pos)            /*!< PDMA_T::REQSEL0_3: REQSRC3 Mask        */

#define PDMA_REQSEL4_REQSRC4_Pos         (0)                                               /*!< PDMA_T::REQSEL4: REQSRC4 Position      */
#define PDMA_REQSEL4_REQSRC4_Msk         (0x3ful << PDMA_REQSEL4_REQSRC4_Pos)              /*!< PDMA_T::REQSEL4: REQSRC4 Mask          */

/**@}*/ /* PDMA_CONST */
/**@}*/ /* end of PDMA register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __PDMA_REG_H__ */
