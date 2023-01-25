/**************************************************************************//**
 * @file     i2c_reg.h
 * @version  V1.00
 * @brief    I2C register definition header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __I2C_REG_H__
#define __I2C_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup I2C Inter-IC Bus Controller (I2C)
    Memory Mapped Structure for I2C Controller
@{ */

typedef struct
{
    /**
     * @var I2C_T::CTL
     * Offset: 0x00  I2C Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |AA        |Assert Acknowledge Control
     * |        |          |When AA =1 prior to address or data is received, an acknowledged (low level to SDA) will be returned during the acknowledge clock pulse on the SCL line when 1.) A slave is acknowledging the address sent from master, 2.) The receiver devices are acknowledging the data sent by transmitter
     * |        |          |When AA=0 prior to address or data received, a Not acknowledged (high level to SDA) will be returned during the acknowledge clock pulse on the SCL line
     * |[3]     |SI        |I2C Interrupt Flag
     * |        |          |When a new I2C state is present in the I2C_STATUS register, the SI flag is set by hardware
     * |        |          |If bit INTEN (I2C_CTL [7]) is set, the I2C interrupt is requested
     * |        |          |SI must be cleared by software
     * |        |          |Clear SI by writing 1 to this bit.
     * |        |          |For ACKMEN is set in slave read mode, the SI flag is set in 8th clock period for user to confirm the acknowledge bit and 9th clock period for user to read the data in the data buffer.
     * |[4]     |STO       |I2C STOP Control
     * |        |          |In Master mode, setting STO to transmit a STOP condition to bus then I2C controller will check the bus condition if a STOP condition is detected
     * |        |          |This bit will be cleared by hardware automatically.
     * |[5]     |STA       |I2C START Control
     * |        |          |Setting STA to logic 1 to enter Master mode, the I2C hardware sends a START or repeat START condition to bus when the bus is free.
     * |[6]     |I2CEN     |I2C Controller Enable Bit
     * |        |          |Set to enable I2C serial function controller
     * |        |          |When I2CEN=1 the I2C serial function enable
     * |        |          |The multi-function pin function must set to SDA, and SCL of I2C function first.
     * |        |          |0 = I2C controller Disabled.
     * |        |          |1 = I2C controller Enabled.
     * |[7]     |INTEN     |Enable Interrupt
     * |        |          |0 = I2C interrupt Disabled.
     * |        |          |1 = I2C interrupt Enabled.
     * @var I2C_T::ADDR0
     * Offset: 0x04  I2C Slave Address Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = General Call Function Disabled.
     * |        |          |1 = General Call Function Enabled.
     * |[7:1]   |ADDR      |I2C Address
     * |        |          |The content of this register is irrelevant when I2C is in Master mode
     * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own address
     * |        |          |The I2C hardware will react if either of the address is matched.
     * @var I2C_T::DAT
     * Offset: 0x08  I2C Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DAT       |I2C Data
     * |        |          |Bit [7:0] is located with the 8-bit transferred/received data of I2C serial port.
     * @var I2C_T::STATUS
     * Offset: 0x0C  I2C Status Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |STATUS    |I2C Status
     * |        |          |The three least significant bits are always 0
     * |        |          |The five most significant bits contain the status code
     * |        |          |There are 28 possible status codes
     * |        |          |When the content of I2C_STATUS is F8H, no serial interrupt is requested
     * |        |          |Others I2C_STATUS values correspond to defined I2C states
     * |        |          |When each of these states is entered, a status interrupt is requested (SI = 1)
     * |        |          |A valid status code is present in I2C_STATUS one cycle after SI is set by hardware and is still present one cycle after SI has been reset by software
     * |        |          |In addition, states 00H stands for a Bus Error
     * |        |          |A Bus Error occurs when a START or STOP condition is present at an illegal position in the formation frame
     * |        |          |Example of illegal position are during the serial transfer of an address byte, a data byte or an acknowledge bit.
     * @var I2C_T::CLKDIV
     * Offset: 0x10  I2C Clock Divided Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DIVIDER   |I2C Clock Divided
     * |        |          |Indicates the I2C clock rate: Data Baud Rate of I2C = (system clock) / (4x (I2C_CLKDIV+1)).
     * |        |          |Note: The minimum value of I2C_CLKDIV is 4.
     * @var I2C_T::TOCTL
     * Offset: 0x14  I2C Time-out Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TOIF      |Time-out Flag
     * |        |          |This bit is set by hardware when I2C time-out happened and it can interrupt CPU if I2C interrupt enable bit (INTEN) is set to 1.
     * |        |          |Note: Software can write 1 to clear this bit.
     * |[1]     |TOCDIV4   |Time-out Counter Input Clock Divided by 4
     * |        |          |When it Enabled, The time-out period is extend 4 times.
     * |        |          |0 = Time-out period is extend 4 times Disabled.
     * |        |          |1 = Time-out period is extend 4 times Enabled.
     * |[2]     |TOCEN     |Time-out Counter Enable Bit
     * |        |          |When Enabled, the 14-bit time-out counter will start counting when SI is clear
     * |        |          |Setting flag SI to '1' will reset counter and re-start up counting after SI is cleared.
     * |        |          |0 = Time-out counter Disabled.
     * |        |          |1 = Time-out counter Enabled.
     * @var I2C_T::ADDR1
     * Offset: 0x18  I2C Slave Address Register1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = General Call Function Disabled.
     * |        |          |1 = General Call Function Enabled.
     * |[7:1]   |ADDR      |I2C Address
     * |        |          |The content of this register is irrelevant when I2C is in Master mode
     * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own address
     * |        |          |The I2C hardware will react if either of the address is matched.
     * @var I2C_T::ADDR2
     * Offset: 0x1C  I2C Slave Address Register2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = General Call Function Disabled.
     * |        |          |1 = General Call Function Enabled.
     * |[7:1]   |ADDR      |I2C Address
     * |        |          |The content of this register is irrelevant when I2C is in Master mode
     * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own address
     * |        |          |The I2C hardware will react if either of the address is matched.
     * @var I2C_T::ADDR3
     * Offset: 0x20  I2C Slave Address Register3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |GC        |General Call Function
     * |        |          |0 = General Call Function Disabled.
     * |        |          |1 = General Call Function Enabled.
     * |[7:1]   |ADDR      |I2C Address
     * |        |          |The content of this register is irrelevant when I2C is in Master mode
     * |        |          |In the slave mode, the seven most significant bits must be loaded with the chip's own address
     * |        |          |The I2C hardware will react if either of the address is matched.
     * @var I2C_T::ADDRMSK0
     * Offset: 0x24  I2C Slave Address Mask Register0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |ADDRMSK   |I2C Address Mask
     * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
     * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register
     * |        |          |When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
     * |        |          |If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
     * @var I2C_T::ADDRMSK1
     * Offset: 0x28  I2C Slave Address Mask Register1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |ADDRMSK   |I2C Address Mask
     * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
     * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register
     * |        |          |When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
     * |        |          |If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
     * @var I2C_T::ADDRMSK2
     * Offset: 0x2C  I2C Slave Address Mask Register2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |ADDRMSK   |I2C Address Mask
     * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
     * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register
     * |        |          |When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
     * |        |          |If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
     * @var I2C_T::ADDRMSK3
     * Offset: 0x30  I2C Slave Address Mask Register3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:1]   |ADDRMSK   |I2C Address Mask
     * |        |          |0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
     * |        |          |1 = Mask Enabled (the received corresponding address bit is don't care.).
     * |        |          |I2C bus controllers support multiple address recognition with four address mask register
     * |        |          |When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
     * |        |          |If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
     * @var I2C_T::WKCTL
     * Offset: 0x3C  I2C Wake-up Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WKEN      |I2C Wake-up Enable Bit
     * |        |          |0 = I2C wake-up function Disabled.
     * |        |          |1= I2C wake-up function Enabled.
     * |[7]     |NHDBUSEN  |I2C No Hold BUS Enable Bit
     * |        |          |0 = I2C don't hold bus after wake-up disable.
     * |        |          |1= I2C don't hold bus after wake-up enable.
     * |        |          |Note: I2C controller could response when WKIF event is not clear, it may cause error data transmitted or received
     * |        |          |If data transmitted or received when WKIF event is not clear, user must reset I2C controller and execute the original operation again.
     * @var I2C_T::WKSTS
     * Offset: 0x40  I2C Wake-up Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WKIF      |I2C Wake-up Flag
     * |        |          |When chip is woken up from Power-down mode by I2C, this bit is set to 1
     * |        |          |Software can write 1 to clear this bit.
     * |[1]     |WKAKDONE  |Wakeup Address Frame Acknowledge Bit Done
     * |        |          |0 = The ACK bit cycle of address match frame isn't done.
     * |        |          |1 = The ACK bit cycle of address match frame is done in power-down.
     * |        |          |Note: This bit can't release WKIF. Software can write 1 to clear this bit.
     * |[2]     |WRSTSWK   |Read/Write Status Bit in Address Wakeup Frame
     * |        |          |0 = Write command be record on the address match wakeup frame.
     * |        |          |1 = Read command be record on the address match wakeup frame.
     * |        |          |Note: This bit will be cleared when software can write 1 to WKAKDONE bit.
     * @var I2C_T::CTL1
     * Offset: 0x44  I2C Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TXPDMAEN  |PDMA Transmit Channel Available
     * |        |          |0 = Transmit PDMA function disable.
     * |        |          |1 = Transmit PDMA function enable.
     * |[1]     |RXPDMAEN  |PDMA Receive Channel Available
     * |        |          |0 = Receive PDMA function disable.
     * |        |          |1 = Receive PDMA function enable.
     * |[2]     |PDMARST   |PDMA Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset the PDMA control logic. This bit will be cleared to 0 automatically.
     * |[3]     |OVRIEN    |I2C over Run Interrupt Control Bit
     * |        |          |Setting OVRIEN to logic 1 will send a interrupt to system when the TWOBUFEN bit is enabled and there is over run event in received buffer.
     * |[4]     |UDRIEN    |I2C Under Run Interrupt Control Bit
     * |        |          |Setting UDRIEN to logic 1 will send a interrupt to system when the TWOBUFEN bit is enabled and there is under run event happened in transmitted buffer.
     * |[5]     |TWOBUFEN  |Two-level Buffer Enable Bit
     * |        |          |0 = Two-level buffer Disabled.
     * |        |          |1 = Two-level buffer Enabled.
     * |        |          |Set to enable the two-level buffer for I2C transmitted or received buffer
     * |        |          |It is used to improve the performance of the I2C bus
     * |        |          |If this bit is set = 1, the control bit of STA for repeat start or STO bit should be set after the current SI is clear
     * |        |          |For example: if there are 4 data shall be transmitted and then stop it
     * |        |          |The STO bit shall be set after the 3rd data's SI event being clear
     * |        |          |In this time, the 4th data can be transmitted and the I2C stop after the 4th data transmission done.
     * |[6]     |TWOBUFRST |Two-level Buffer Reset
     * |        |          |0 = No effect.
     * |        |          |1 = Reset the related counters, two-level buffer state machine, and the content of data buffer.
     * |[7]     |NSTRETCH  |No Stretch on the I2C Bus
     * |        |          |0 = The I2C SCL bus is stretched by hardware if the SI is not cleared in master mode.
     * |        |          |1 = The I2C SCL bus is not stretched by hardware if the SI is not cleared in master mode.
     * |[8]     |PDMASTR   |PDMA Stretch Bit
     * |        |          |0 = I2C send STOP automatically after PDMA transfer done. (only master TX)
     * |        |          |1 = I2C SCL bus is stretched by hardware after PDMA transfer done if the SI is not cleared
     * |        |          |(only master TX)
     * @var I2C_T::STATUS1
     * Offset: 0x48  I2C Status Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4]     |FULL      |Two-level Buffer Full
     * |        |          |This bit indicates two-level buffer TX or RX full or not when the TWOBUFEN = 1.
     * |        |          |This bit is set when buffer full.
     * |[5]     |EMPTY     |Two-level Buffer Empty
     * |        |          |This bit indicates two-level buffer TX or RX empty or not when the TWOBUFEN = 1.
     * |        |          |This bit is set when buffer empty.
     * |[6]     |OVR       |I2C over Run Status Bit
     * |        |          |This bit indicates the received two-level buffer TX or RX is over run when the TWOBUFEN = 1.
     * |[7]     |UDR       |I2C Under Run Status Bit
     * |        |          |This bit indicates the transmitted two-level buffer TX or RX is under run when the TWOBUFEN = 1.
     * |[8]     |ONBUSY    |Bus Busy
     * |        |          |Indicates that a communication is in progress on the bus
     * |        |          |It is set by hardware when a START condition is detected
     * |        |          |It is cleared by hardware when a STOP condition is detected.
     * |        |          |0 = The bus is IDLE (both SCLK and SDA High).
     * |        |          |1 = The bus is busy.
     * @var I2C_T::TMCTL
     * Offset: 0x4C  I2C Timing Configure Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |STCTL     |Setup Time Configure Control Register
     * |        |          |This field is used to generate a delay timing between SDA falling edge and SCL rising edge in transmission mode.
     * |        |          |The delay setup time is numbers of peripheral clock = STCTL x PCLK.
     * |        |          |Note: Setup time setting should not make SCL output less than three PCLKs.
     * |[11:6]  |HTCTL     |Hold Time Configure Control Register
     * |        |          |This field is used to generate the delay timing between SCL falling edge and SDA rising edge in transmission mode.
     * |        |          |The delay hold time is numbers of peripheral clock = HTCTL x PCLK.
     */
    __IO uint32_t CTL;                   /*!< [0x0000] I2C Control Register 0                                           */
    __IO uint32_t ADDR0;                 /*!< [0x0004] I2C Slave Address Register0                                      */
    __IO uint32_t DAT;                   /*!< [0x0008] I2C Data Register                                                */
    __I  uint32_t STATUS;                /*!< [0x000c] I2C Status Register 0                                            */
    __IO uint32_t CLKDIV;                /*!< [0x0010] I2C Clock Divided Register                                       */
    __IO uint32_t TOCTL;                 /*!< [0x0014] I2C Time-out Control Register                                    */
    __IO uint32_t ADDR1;                 /*!< [0x0018] I2C Slave Address Register1                                      */
    __IO uint32_t ADDR2;                 /*!< [0x001c] I2C Slave Address Register2                                      */
    __IO uint32_t ADDR3;                 /*!< [0x0020] I2C Slave Address Register3                                      */
    __IO uint32_t ADDRMSK0;              /*!< [0x0024] I2C Slave Address Mask Register0                                 */
    __IO uint32_t ADDRMSK1;              /*!< [0x0028] I2C Slave Address Mask Register1                                 */
    __IO uint32_t ADDRMSK2;              /*!< [0x002c] I2C Slave Address Mask Register2                                 */
    __IO uint32_t ADDRMSK3;              /*!< [0x0030] I2C Slave Address Mask Register3                                 */
    __I  uint32_t RESERVE0[2];
    __IO uint32_t WKCTL;                 /*!< [0x003c] I2C Wake-up Control Register                                     */
    __IO uint32_t WKSTS;                 /*!< [0x0040] I2C Wake-up Status Register                                      */
    __IO uint32_t CTL1;                  /*!< [0x0044] I2C Control Register 1                                           */
    __I  uint32_t STATUS1;               /*!< [0x0048] I2C Status Register 1                                            */
    __IO uint32_t TMCTL;                 /*!< [0x004c] I2C Timing Configure Control Register                            */
} I2C_T;

/**
    @addtogroup I2C_CONST I2C Bit Field Definition
    Constant Definitions for I2C Controller
@{ */

#define I2C_CTL_AA_Pos                   (2)                                               /*!< I2C_T::CTL: AA Position                */
#define I2C_CTL_AA_Msk                   (0x1ul << I2C_CTL_AA_Pos)                         /*!< I2C_T::CTL: AA Mask                    */

#define I2C_CTL_SI_Pos                   (3)                                               /*!< I2C_T::CTL: SI Position                */
#define I2C_CTL_SI_Msk                   (0x1ul << I2C_CTL_SI_Pos)                         /*!< I2C_T::CTL: SI Mask                    */

#define I2C_CTL_STO_Pos                  (4)                                               /*!< I2C_T::CTL: STO Position               */
#define I2C_CTL_STO_Msk                  (0x1ul << I2C_CTL_STO_Pos)                        /*!< I2C_T::CTL: STO Mask                   */

#define I2C_CTL_STA_Pos                  (5)                                               /*!< I2C_T::CTL: STA Position               */
#define I2C_CTL_STA_Msk                  (0x1ul << I2C_CTL_STA_Pos)                        /*!< I2C_T::CTL: STA Mask                   */

#define I2C_CTL_I2CEN_Pos                (6)                                               /*!< I2C_T::CTL: I2CEN Position             */
#define I2C_CTL_I2CEN_Msk                (0x1ul << I2C_CTL_I2CEN_Pos)                      /*!< I2C_T::CTL: I2CEN Mask                 */

#define I2C_CTL_INTEN_Pos                (7)                                               /*!< I2C_T::CTL: INTEN Position             */
#define I2C_CTL_INTEN_Msk                (0x1ul << I2C_CTL_INTEN_Pos)                      /*!< I2C_T::CTL: INTEN Mask                 */

#define I2C_ADDR0_GC_Pos                 (0)                                               /*!< I2C_T::ADDR0: GC Position              */
#define I2C_ADDR0_GC_Msk                 (0x1ul << I2C_ADDR0_GC_Pos)                       /*!< I2C_T::ADDR0: GC Mask                  */

#define I2C_ADDR0_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR0: ADDR Position            */
#define I2C_ADDR0_ADDR_Msk               (0x7ful << I2C_ADDR0_ADDR_Pos)                    /*!< I2C_T::ADDR0: ADDR Mask                */

#define I2C_DAT_DAT_Pos                  (0)                                               /*!< I2C_T::DAT: DAT Position               */
#define I2C_DAT_DAT_Msk                  (0xfful << I2C_DAT_DAT_Pos)                       /*!< I2C_T::DAT: DAT Mask                   */

#define I2C_STATUS_STATUS_Pos            (0)                                               /*!< I2C_T::STATUS: STATUS Position         */
#define I2C_STATUS_STATUS_Msk            (0xfful << I2C_STATUS_STATUS_Pos)                 /*!< I2C_T::STATUS: STATUS Mask             */

#define I2C_CLKDIV_DIVIDER_Pos           (0)                                               /*!< I2C_T::CLKDIV: DIVIDER Position        */
#define I2C_CLKDIV_DIVIDER_Msk           (0xfful << I2C_CLKDIV_DIVIDER_Pos)                /*!< I2C_T::CLKDIV: DIVIDER Mask            */

#define I2C_TOCTL_TOIF_Pos               (0)                                               /*!< I2C_T::TOCTL: TOIF Position            */
#define I2C_TOCTL_TOIF_Msk               (0x1ul << I2C_TOCTL_TOIF_Pos)                     /*!< I2C_T::TOCTL: TOIF Mask                */

#define I2C_TOCTL_TOCDIV4_Pos            (1)                                               /*!< I2C_T::TOCTL: TOCDIV4 Position         */
#define I2C_TOCTL_TOCDIV4_Msk            (0x1ul << I2C_TOCTL_TOCDIV4_Pos)                  /*!< I2C_T::TOCTL: TOCDIV4 Mask             */

#define I2C_TOCTL_TOCEN_Pos              (2)                                               /*!< I2C_T::TOCTL: TOCEN Position           */
#define I2C_TOCTL_TOCEN_Msk              (0x1ul << I2C_TOCTL_TOCEN_Pos)                    /*!< I2C_T::TOCTL: TOCEN Mask               */

#define I2C_ADDR1_GC_Pos                 (0)                                               /*!< I2C_T::ADDR1: GC Position              */
#define I2C_ADDR1_GC_Msk                 (0x1ul << I2C_ADDR1_GC_Pos)                       /*!< I2C_T::ADDR1: GC Mask                  */

#define I2C_ADDR1_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR1: ADDR Position            */
#define I2C_ADDR1_ADDR_Msk               (0x7ful << I2C_ADDR1_ADDR_Pos)                    /*!< I2C_T::ADDR1: ADDR Mask                */

#define I2C_ADDR2_GC_Pos                 (0)                                               /*!< I2C_T::ADDR2: GC Position              */
#define I2C_ADDR2_GC_Msk                 (0x1ul << I2C_ADDR2_GC_Pos)                       /*!< I2C_T::ADDR2: GC Mask                  */

#define I2C_ADDR2_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR2: ADDR Position            */
#define I2C_ADDR2_ADDR_Msk               (0x7ful << I2C_ADDR2_ADDR_Pos)                    /*!< I2C_T::ADDR2: ADDR Mask                */

#define I2C_ADDR3_GC_Pos                 (0)                                               /*!< I2C_T::ADDR3: GC Position              */
#define I2C_ADDR3_GC_Msk                 (0x1ul << I2C_ADDR3_GC_Pos)                       /*!< I2C_T::ADDR3: GC Mask                  */

#define I2C_ADDR3_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR3: ADDR Position            */
#define I2C_ADDR3_ADDR_Msk               (0x7ful << I2C_ADDR3_ADDR_Pos)                    /*!< I2C_T::ADDR3: ADDR Mask                */

#define I2C_ADDRMSK0_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK0: ADDRMSK Position      */
#define I2C_ADDRMSK0_ADDRMSK_Msk         (0x7ful << I2C_ADDRMSK0_ADDRMSK_Pos)              /*!< I2C_T::ADDRMSK0: ADDRMSK Mask          */

#define I2C_ADDRMSK1_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK1: ADDRMSK Position      */
#define I2C_ADDRMSK1_ADDRMSK_Msk         (0x7ful << I2C_ADDRMSK1_ADDRMSK_Pos)              /*!< I2C_T::ADDRMSK1: ADDRMSK Mask          */

#define I2C_ADDRMSK2_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK2: ADDRMSK Position      */
#define I2C_ADDRMSK2_ADDRMSK_Msk         (0x7ful << I2C_ADDRMSK2_ADDRMSK_Pos)              /*!< I2C_T::ADDRMSK2: ADDRMSK Mask          */

#define I2C_ADDRMSK3_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK3: ADDRMSK Position      */
#define I2C_ADDRMSK3_ADDRMSK_Msk         (0x7ful << I2C_ADDRMSK3_ADDRMSK_Pos)              /*!< I2C_T::ADDRMSK3: ADDRMSK Mask          */

#define I2C_WKCTL_WKEN_Pos               (0)                                               /*!< I2C_T::WKCTL: WKEN Position            */
#define I2C_WKCTL_WKEN_Msk               (0x1ul << I2C_WKCTL_WKEN_Pos)                     /*!< I2C_T::WKCTL: WKEN Mask                */

#define I2C_WKCTL_NHDBUSEN_Pos           (7)                                               /*!< I2C_T::WKCTL: NHDBUSEN Position        */
#define I2C_WKCTL_NHDBUSEN_Msk           (0x1ul << I2C_WKCTL_NHDBUSEN_Pos)                 /*!< I2C_T::WKCTL: NHDBUSEN Mask            */

#define I2C_WKSTS_WKIF_Pos               (0)                                               /*!< I2C_T::WKSTS: WKIF Position            */
#define I2C_WKSTS_WKIF_Msk               (0x1ul << I2C_WKSTS_WKIF_Pos)                     /*!< I2C_T::WKSTS: WKIF Mask                */

#define I2C_WKSTS_WKAKDONE_Pos           (1)                                               /*!< I2C_T::WKSTS: WKAKDONE Position        */
#define I2C_WKSTS_WKAKDONE_Msk           (0x1ul << I2C_WKSTS_WKAKDONE_Pos)                 /*!< I2C_T::WKSTS: WKAKDONE Mask            */

#define I2C_WKSTS_WRSTSWK_Pos            (2)                                               /*!< I2C_T::WKSTS: WRSTSWK Position         */
#define I2C_WKSTS_WRSTSWK_Msk            (0x1ul << I2C_WKSTS_WRSTSWK_Pos)                  /*!< I2C_T::WKSTS: WRSTSWK Mask             */

#define I2C_CTL1_TXPDMAEN_Pos            (0)                                               /*!< I2C_T::CTL1: TXPDMAEN Position         */
#define I2C_CTL1_TXPDMAEN_Msk            (0x1ul << I2C_CTL1_TXPDMAEN_Pos)                  /*!< I2C_T::CTL1: TXPDMAEN Mask             */

#define I2C_CTL1_RXPDMAEN_Pos            (1)                                               /*!< I2C_T::CTL1: RXPDMAEN Position         */
#define I2C_CTL1_RXPDMAEN_Msk            (0x1ul << I2C_CTL1_RXPDMAEN_Pos)                  /*!< I2C_T::CTL1: RXPDMAEN Mask             */

#define I2C_CTL1_PDMARST_Pos             (2)                                               /*!< I2C_T::CTL1: PDMARST Position          */
#define I2C_CTL1_PDMARST_Msk             (0x1ul << I2C_CTL1_PDMARST_Pos)                   /*!< I2C_T::CTL1: PDMARST Mask              */

#define I2C_CTL1_OVRIEN_Pos              (3)                                               /*!< I2C_T::CTL1: OVRIEN Position           */
#define I2C_CTL1_OVRIEN_Msk              (0x1ul << I2C_CTL1_OVRIEN_Pos)                    /*!< I2C_T::CTL1: OVRIEN Mask               */

#define I2C_CTL1_UDRIEN_Pos              (4)                                               /*!< I2C_T::CTL1: UDRIEN Position           */
#define I2C_CTL1_UDRIEN_Msk              (0x1ul << I2C_CTL1_UDRIEN_Pos)                    /*!< I2C_T::CTL1: UDRIEN Mask               */

#define I2C_CTL1_TWOBUFEN_Pos            (5)                                               /*!< I2C_T::CTL1: TWOBUFEN Position         */
#define I2C_CTL1_TWOBUFEN_Msk            (0x1ul << I2C_CTL1_TWOBUFEN_Pos)                  /*!< I2C_T::CTL1: TWOBUFEN Mask             */

#define I2C_CTL1_TWOBUFRST_Pos           (6)                                               /*!< I2C_T::CTL1: TWOBUFRST Position        */
#define I2C_CTL1_TWOBUFRST_Msk           (0x1ul << I2C_CTL1_TWOBUFRST_Pos)                 /*!< I2C_T::CTL1: TWOBUFRST Mask            */

#define I2C_CTL1_NSTRETCH_Pos            (7)                                               /*!< I2C_T::CTL1: NSTRETCH Position         */
#define I2C_CTL1_NSTRETCH_Msk            (0x1ul << I2C_CTL1_NSTRETCH_Pos)                  /*!< I2C_T::CTL1: NSTRETCH Mask             */

#define I2C_CTL1_PDMASTR_Pos             (8)                                               /*!< I2C_T::CTL1: PDMASTR Position          */
#define I2C_CTL1_PDMASTR_Msk             (0x1ul << I2C_CTL1_PDMASTR_Pos)                   /*!< I2C_T::CTL1: PDMASTR Mask              */

#define I2C_STATUS1_FULL_Pos             (4)                                               /*!< I2C_T::STATUS1: FULL Position          */
#define I2C_STATUS1_FULL_Msk             (0x1ul << I2C_STATUS1_FULL_Pos)                   /*!< I2C_T::STATUS1: FULL Mask              */

#define I2C_STATUS1_EMPTY_Pos            (5)                                               /*!< I2C_T::STATUS1: EMPTY Position         */
#define I2C_STATUS1_EMPTY_Msk            (0x1ul << I2C_STATUS1_EMPTY_Pos)                  /*!< I2C_T::STATUS1: EMPTY Mask             */

#define I2C_STATUS1_OVR_Pos              (6)                                               /*!< I2C_T::STATUS1: OVR Position           */
#define I2C_STATUS1_OVR_Msk              (0x1ul << I2C_STATUS1_OVR_Pos)                    /*!< I2C_T::STATUS1: OVR Mask               */

#define I2C_STATUS1_UDR_Pos              (7)                                               /*!< I2C_T::STATUS1: UDR Position           */
#define I2C_STATUS1_UDR_Msk              (0x1ul << I2C_STATUS1_UDR_Pos)                    /*!< I2C_T::STATUS1: UDR Mask               */

#define I2C_STATUS1_ONBUSY_Pos           (8)                                               /*!< I2C_T::STATUS1: ONBUSY Position        */
#define I2C_STATUS1_ONBUSY_Msk           (0x1ul << I2C_STATUS1_ONBUSY_Pos)                 /*!< I2C_T::STATUS1: ONBUSY Mask            */

#define I2C_TMCTL_STCTL_Pos              (0)                                               /*!< I2C_T::TMCTL: STCTL Position           */
#define I2C_TMCTL_STCTL_Msk              (0x3ful << I2C_TMCTL_STCTL_Pos)                   /*!< I2C_T::TMCTL: STCTL Mask               */

#define I2C_TMCTL_HTCTL_Pos              (6)                                               /*!< I2C_T::TMCTL: HTCTL Position           */
#define I2C_TMCTL_HTCTL_Msk              (0x3ful << I2C_TMCTL_HTCTL_Pos)                   /*!< I2C_T::TMCTL: HTCTL Mask               */

/**@}*/ /* I2C_CONST */
/**@}*/ /* end of I2C register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __I2C_REG_H__ */
