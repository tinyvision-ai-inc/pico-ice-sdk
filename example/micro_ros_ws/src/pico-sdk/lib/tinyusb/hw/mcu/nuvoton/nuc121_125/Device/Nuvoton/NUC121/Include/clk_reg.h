/**************************************************************************//**
 * @file     clk_reg.h
 * @version  V1.00
 * @brief    CLK register definition header file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CLK_REG_H__
#define __CLK_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CLK System Clock Controller (CLK)
    Memory Mapped Structure for CLK Controller
@{ */

typedef struct
{
    /**
     * @var CLK_T::PWRCTL
     * Offset: 0x00  System Power-down Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |XTLEN     |External HXT or LXT Crystal Oscillator Enable Bit (Write Protect)
     * |        |          |The default clock source is from HIRC
     * |        |          |These two bits are default set to "00" and the PF.0 and PF.1 pins are GPIO.
     * |        |          |00 = HXT & LXT Disabled (default).
     * |        |          |01 = HXT Enabled.
     * |        |          |10 = LXT Enabled.
     * |        |          |11 = Reserved.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: This bit is over-written by CFOSC (CONFIG0[26]) after reset.
     * |[2]     |HIRCEN    |HIRC Enable Bit (Write Protect)
     * |        |          |0 = 48 MHz internal high speed RC oscillator (HIRC) Disabled.
     * |        |          |1 = 48 MHz internal high speed RC oscillator (HIRC) Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |LIRCEN    |LIRC Enable Bit (Write Protect)
     * |        |          |0 = 10 kHz internal low speed RC oscillator (LIRC) Disabled.
     * |        |          |1 = 10 kHz internal low speed RC oscillator (LIRC) Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |PDWKDLY   |Enable the Wake-up Delay Counter (Write Protect)
     * |        |          |When the chip wakes up from Power-down mode, the clock control will delay certain clock cycles to wait system clock stable.
     * |        |          |The delayed clock cycle is 4096 clock cycles when chip work at 4~24 MHz external high speed crystal oscillator (HXT), and 512 clock cycles when chip work at 48 MHz internal high speed RC oscillator (HIRC).
     * |        |          |0 = Clock cycles delay Disabled.
     * |        |          |1 = Clock cycles delay Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |PDWKIEN   |Power-down Mode Wake-up Interrupt Enable Bit (Write Protect)
     * |        |          |0 = Power-down mode wake-up interrupt Disabled.
     * |        |          |1 = Power-down mode wake-up interrupt Enabled.
     * |        |          |Note1: The interrupt will occur when both PDWKIF and PDWKIEN are high.
     * |        |          |Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |PDWKIF    |Power-down Mode Wake-up Interrupt Status
     * |        |          |Set by "Power-down wake-up event", it indicates that resume from Power-down mode"
     * |        |          |The flag is set if the EINT0~5, GPIO, USBD, UART0, WDT, BOD, TMR0~3 or I2C0~1 wake-up occurred.
     * |        |          |Note1: Write 1 to clear the bit to 0.
     * |        |          |Note2: This bit works only if PDWKIEN (CLK_PWRCTL[5]) set to 1.
     * |[7]     |PDEN      |System Power-down Enable (Write Protect)
     * |        |          |When this bit is set to 1, Power-down mode is enabled and chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode.
     * |        |          |When chip wakes up from Power-down mode, this bit is auto cleared
     * |        |          |Users need to set this bit again for next Power-down.
     * |        |          |In Power-down mode, HXT and the HIRC will be disabled in this mode, but LXT and LIRC are not controlled by Power-down mode.
     * |        |          |In Power-down mode, the PLL and system clock are disabled, and ignored the clock source selection
     * |        |          |The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from LXT or LIRC.
     * |        |          |0 = Chip operating normally or chip in idle mode because of WFI command.
     * |        |          |1 = Chip enters Power-down mode instant or wait CPU sleep command WFI.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[11:10] |HXTGAIN   |HXT Gain Control Bit (Write Protect)
     * |        |          |This is a protected register. Please refer to open lock sequence to program it.
     * |        |          |Gain control is used to enlarge the gain of crystal to make sure crystal work normally
     * |        |          |If gain control is enabled, crystal will consume more power than gain control off.
     * |        |          |00 = HXT frequency is lower than from 8 MHz.
     * |        |          |01 = HXT frequency is from 8 MHz to 12 MHz.
     * |        |          |10 = HXT frequency is from 12 MHz to 16 MHz.
     * |        |          |11 = HXT frequency is higher than 16 MHz.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: This bit is over-written by XT1XSG (CONFIG0[18:17]) after reset.
     * |[12]    |HXTSELTYP |HXT Crystal Type Select Bit (Write Protect)
     * |        |          |This is a protected register. Please refer to open lock sequence to program it.
     * |        |          |0 = Select INV type.
     * |        |          |1 = Select GM type.
     * |        |          |Note 1: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note 2: This bit is over-written by XT1TYP (CONFIG0[16]) after reset.
     * @var CLK_T::AHBCLK
     * Offset: 0x04  AHB Devices Clock Enable Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |PDMACKEN  |PDMA Controller Clock Enable Bit
     * |        |          |0 = PDMA peripheral clock Disabled.
     * |        |          |1 = PDMA peripheral clock Enabled.
     * |[2]     |ISPCKEN   |Flash ISP Controller Clock Enable Bit
     * |        |          |0 = Flash ISP peripheral clock Disabled.
     * |        |          |1 = Flash ISP peripheral clock Enabled.
     * |[15]    |FMCIDLE   |Flash Memory Controller Clock Enable Bit in IDLE Mode
     * |        |          |0 = FMC peripheral clock Disabled when chip operating at IDLE mode.
     * |        |          |1 = FMC peripheral clock Enabled when chip operating at IDLE mode.
     * |[16]    |GPIOACKEN |General Purpose I/O PA Group Clock Enable Bit
     * |        |          |0 = GPIO PA group clock Disabled.
     * |        |          |1 = GPIO PA group clock Enabled.
     * |[17]    |GPIOBCKEN |General Purpose I/O PB Group Clock Enable Bit
     * |        |          |0 = GPIO PB group clock Disabled.
     * |        |          |1 = GPIO PB group clock Enabled.
     * |[18]    |GPIOCCKEN |General Purpose I/O PC Group Clock Enable Bit
     * |        |          |0 = GPIO PC group clock Disabled.
     * |        |          |1 = GPIO PC group clock Enabled.
     * |[19]    |GPIODCKEN |General Purpose I/O PD Group Clock Enable Bit
     * |        |          |0 = GPIO PD group clock Disabled.
     * |        |          |1 = GPIO PD group clock Enabled.
     * |[20]    |GPIOECKEN |General Purpose I/O PE Group Clock Enable Bit
     * |        |          |0 = GPIO PE group clock Disabled.
     * |        |          |1 = GPIO PE group clock Enabled.
     * |[21]    |GPIOFCKEN |General Purpose I/O PF Group Clock Enable Bit
     * |        |          |0 = GPIO PF group clock Disabled.
     * |        |          |1 = GPIO PF group clock Enabled.
     * @var CLK_T::APBCLK0
     * Offset: 0x08  APB Devices Clock Enable Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |WDTCKEN   |Watchdog Timer Clock Enable Bit (Write Protect)
     * |        |          |0 = Watchdog Timer Clock Disabled.
     * |        |          |1 = Watchdog Timer Clock Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |TMR0CKEN  |Timer0 Clock Enable Bit
     * |        |          |0 = Timer0 Clock Disabled.
     * |        |          |1 = Timer0 Clock Enabled.
     * |[3]     |TMR1CKEN  |Timer1 Clock Enable Bit
     * |        |          |0 = Timer1 Clock Disabled.
     * |        |          |1 = Timer1 Clock Enabled.
     * |[4]     |TMR2CKEN  |Timer2 Clock Enable Bit
     * |        |          |0 = Timer2 Clock Disabled.
     * |        |          |1 = Timer2 Clock Enabled.
     * |[5]     |TMR3CKEN  |Timer3 Clock Enable Bit
     * |        |          |0 = Timer3 Clock Disabled.
     * |        |          |1 = Timer3 Clock Enabled.
     * |[6]     |CLKOCKEN  |CLKO Clock Enable Bit
     * |        |          |0 = CLKO Clock Disabled.
     * |        |          |1 = CLKO Clock Enabled.
     * |[8]     |I2C0CKEN  |I2C0 Clock Enable Bit
     * |        |          |0 = I2C0 Clock Disabled.
     * |        |          |1 = I2C0 Clock Enabled.
     * |[9]     |I2C1CKEN  |I2C1 Clock Enable Bit
     * |        |          |0 = I2C1 Clock Disabled.
     * |        |          |1 = I2C1 Clock Enabled.
     * |[12]    |SPI0CKEN  |SPI0 Clock Enable Bit
     * |        |          |0 = SPI0 Clock Disabled.
     * |        |          |1 = SPI0 Clock Enabled.
     * |[16]    |UART0CKEN |UART0 Clock Enable Bit
     * |        |          |0 = UART0 clock Disabled.
     * |        |          |1 = UART0 clock Enabled.
     * |[20]    |BPWM0CKEN |BPWM0 Clock Enable Bit
     * |        |          |0 = BPWM0 clock Disabled.
     * |        |          |1 = BPWM0 clock Enabled.
     * |[21]    |BPWM1CKEN |BPWM1 Clock Enable Bit
     * |        |          |0 = BPWM1 clock Disabled.
     * |        |          |1 = BPWM1 clock Enabled.
     * |[22]    |PWM0CKEN  |PWM0 Clock Enable Bit
     * |        |          |0 = PWM0 clock Disabled.
     * |        |          |1 = PWM0 clock Enabled.
     * |[23]    |PWM1CKEN  |PWM1 Clock Enable Bit
     * |        |          |0 = PWM1 clock Disabled.
     * |        |          |1 = PWM1 clock Enabled.
     * |[27]    |USBDCKEN  |USB Device Clock Enable Bit
     * |        |          |0 = USB Device clock Disabled.
     * |        |          |1 = USB Device clock Enabled.
     * |[28]    |ADCCKEN   |Analog-digital-converter (EADC) Clock Enable Bit
     * |        |          |0 = ADC clock Disabled.
     * |        |          |1 = ADC clock Enabled.
     * @var CLK_T::STATUS
     * Offset: 0x0C  Clock Status Monitor Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTSTB    |HXT Clock Source Stable Flag (Read Only)
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock is not stable or disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT)clock is stable and enabled.
     * |[1]     |LXTSTB    |LXT Clock Source Stable Flag (Read Only)
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock is not stable or disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock is stabled and enabled.
     * |[2]     |PLLSTB    |Internal PLL Clock Source Stable Flag (Read Only)
     * |        |          |0 = Internal PLL clock is not stable or disabled.
     * |        |          |1 = Internal PLL clock is stable and enabled.
     * |[3]     |LIRCSTB   |LIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = 10 kHz internal low speed RC oscillator (LIRC) clock is not stable or disabled.
     * |        |          |1 = 10 kHz internal low speed RC oscillator (LIRC) clock is stable and enabled.
     * |[4]     |HIRCSTB   |HIRC Clock Source Stable Flag (Read Only)
     * |        |          |0 = 48 MHz internal high speed RC oscillator (HIRC) clock is not stable or disabled.
     * |        |          |1 = 48 MHz internal high speed RC oscillator (HIRC) clock is stabe and enabled.
     * |[7]     |CLKSFAIL  |Clock Switching Fail Flag (Read Only)
     * |        |          |This bit is updated when software switches system clock source
     * |        |          |If switch target clock is stable, this bit will be set to 0
     * |        |          |If switch target clock is not stable, this bit will be set to 1.
     * |        |          |0 = Clock switching success.
     * |        |          |1 = Clock switching failure.
     * |        |          |Note 1: Clock switch will finish automatically when target clcok is stable even if this bit already set to 1.
     * @var CLK_T::CLKSEL0
     * Offset: 0x10  Clock Source Select Control Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |HCLKSEL   |HCLK Clock Source Selection (Write Protect)
     * |        |          |Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
     * |        |          |The default value is reloaded from the value of CFOSC (CONFIG0[26:24]) in user configuration register of Flash controller by any reset
     * |        |          |Therefore the default value is either 000b or 111b.
     * |        |          |000 = Clock source from HXT.
     * |        |          |001 = Clock source from LXT.
     * |        |          |010 = Clock source from PLL clock.
     * |        |          |011 = Clock source from LIRC.
     * |        |          |100 = Clock source from HIRC (48 MHz).
     * |        |          |101 = Clock source from PLL clock divided by 2.
     * |        |          |111 = Clock source from HIRC clock divided by 2 (24 MHz).
     * |        |          |Other = Reserved.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5:3]   |STCLKSEL  |Cortex-M0 SysTick Clock Source Selection (Write Protect)
     * |        |          |If SYST_CTRL[2]=0, SysTick uses listed clock source below.
     * |        |          |000 = Clock source from HXT.
     * |        |          |001 = Clock source from LXT.
     * |        |          |010 = Clock source from HXT/2.
     * |        |          |011 = Clock source from HCLK/2.
     * |        |          |111 = Clock source from HIRC/4 (12 MHz).
     * |        |          |Note: if SysTick clock source is not from HCLK (i.e
     * |        |          |SYST_CTRL[2] = 0), SysTick clock source must less than or equal to HCLK/2.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |PCLK0SEL  |PCLK0 Clock Source Selection (Write Protect)
     * |        |          |0 = APB0 BUS clock source from HCLK.
     * |        |          |1 = APB0 BUS clock source from HCLK/2.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |PCLK1SEL  |PCLK1 Clock Source Selection (Write Protect)
     * |        |          |0 = APB1 BUS clock source from HCLK.
     * |        |          |1 = APB1 BUS clock source from HCLK/2.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var CLK_T::CLKSEL1
     * Offset: 0x14  Clock Source Select Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |WDTSEL    |Watchdog Timer Clock Source Selection (Write Protect)
     * |        |          |00 = Reserved.
     * |        |          |01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |10 = Clock source from HCLK/2048 clock.
     * |        |          |11 = Clock source from 10 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3:2]   |ADCSEL    |ADC Peripheral Clock Source Selection
     * |        |          |00 = Clock source is from HXT.
     * |        |          |01 = Clock source is from PLL.
     * |        |          |10 = Clock source is from PCLK0.
     * |        |          |11 = Clock source is from HIRC/2 (24 MHz).
     * |[10:8]  |TMR0SEL   |TIMER0 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock T0 pin.
     * |        |          |101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from 24 MHz internal high speed RC oscillator (HIRC/2) clock.
     * |        |          |Others = Reserved.
     * |[14:12] |TMR1SEL   |TIMER1 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK0.
     * |        |          |011 = Clock source from external clock T1 pin.
     * |        |          |101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from 24 MHz internal high speed RC oscillator (HIRC/2) clock.
     * |        |          |Others = Reserved.
     * |[18:16] |TMR2SEL   |TIMER2 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock T2 pin.
     * |        |          |101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from 24 MHz internal high speed RC oscillator (HIRC/2) clock.
     * |        |          |Others = Reserved.
     * |[22:20] |TMR3SEL   |TIMER3 Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from PCLK1.
     * |        |          |011 = Clock source from external clock T3 pin.
     * |        |          |101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC) clock.
     * |        |          |111 = Clock source from 24 MHz internal high speed RC oscillator (HIRC/2) clock.
     * |        |          |Others = Reserved.
     * |[25:24] |UARTSEL   |UART Clock Source Selection
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |01 = Clock source from PLL clock.
     * |        |          |10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |11 = Clock source from 24 MHz internal high speed RC oscillator (HIRC/2) clock.
     * |[28]    |BPWM0SEL  |BPWM0 Clock Source Selection
     * |        |          |The peripheral clock source of BPWM0 is defined by BPWM0SEL.
     * |        |          |0 = Clock source from PLL clock.
     * |        |          |1 = Clock source from PCLK0.
     * |[29]    |BPWM1SEL  |BPWM1 Clock Source Selection
     * |        |          |The peripheral clock source of BPWM1 is defined by BPWM1SEL.
     * |        |          |0 = Clock source from PLL clock.
     * |        |          |1 = Clock source from PCLK1.
     * |[30]    |PWM0SEL   |PWM0 Clock Source Selection
     * |        |          |The peripheral clock source of PWM1 is defined by PWM0SEL.
     * |        |          |0 = Clock source from PLL clock.
     * |        |          |1 = Clock source from PCLK0.
     * |[31]    |PWM1SEL   |PWM1 Clock Source Selection
     * |        |          |The peripheral clock source of PWM1 is defined by PWM1SEL.
     * |        |          |0 = Clock source from PLL clock.
     * |        |          |1 = Clock source from PCLK1.
     * @var CLK_T::CLKDIV0
     * Offset: 0x18  Clock Divider Number Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |HCLKDIV   |HCLK Clock Divide Number From HCLK Clock Source
     * |        |          |HCLK clock frequency = (HCLK clock source frequency) / (HCLKDIV + 1).
     * |[7:4]   |USBDIV    |USB Clock Divide Number From PLL Clock
     * |        |          |USB clock frequency = (PLL frequency) / (USBDIV + 1).
     * |[11:8]  |UARTDIV   |UART Clock Divide Number From UART Clock Source
     * |        |          |UART clock frequency = (UART clock source frequency) / (UARTDIV + 1).
     * |[23:16] |ADCDIV    |ADC Clock Divide Number From EADC Clock Source
     * |        |          |ADC clock frequency = (ADC clock source frequency) / (ADCDIV + 1).
     * @var CLK_T::CLKSEL2
     * Offset: 0x1C  Clock Source Select Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:2]   |CLKOSEL   |Clock Divider Clock Source Selection
     * |        |          |000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT) clock.
     * |        |          |010 = Clock source from HCLK.
     * |        |          |011 = Clock source from 48 MHz internal high speed RC oscillator (HIRC) clock and devided by 2
     * |        |          |(HIRC/2 = 24 MHz).
     * |        |          |101 = Clock source from 48 MHz internal high speed RC oscillator (HIRC) clock.
     * |        |          |111 = Clock source from SOF (USB Start Of Frame) event. (not 50% duty cycle)
     * |        |          |Others = Reserved.
     * |[17:16] |WWDTSEL   |Window Watchdog Timer Clock Source Selection
     * |        |          |10 = Clock source from HCLK/2048 clock.
     * |        |          |11 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
     * |        |          |Others = Reserved.
     * |[25:24] |SPI0SEL   |SPI0 Clock Source Selection
     * |        |          |00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT) clock.
     * |        |          |01 = Clock source from PLL clock.
     * |        |          |10 = Clock source from PCLK0.
     * |        |          |11 = Clock source from 48 MHz internal high speed RC oscillator (HIRC) clock.
     * @var CLK_T::PLLCTL
     * Offset: 0x20  PLL Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |FBDIV     |PLL Feedback Divider Control
     * |        |          |Refer to the formulas below the table.
     * |[13:9]  |INDIV     |PLL Input Divider Control
     * |        |          |Refer to the formulas below the table.
     * |[15:14] |OUTDIV    |PLL Output Divider Control
     * |        |          |Refer to the formulas below the table.
     * |[16]    |PD        |Power-down Mode
     * |        |          |If set the PDEN bit to 1 in CLK_PWRCTL register, the PLL will enter Power-down mode, too.
     * |        |          |0 = PLL is in normal mode.
     * |        |          |1 = PLL is in Power-down mode (default).
     * |[17]    |BP        |PLL Bypass Control
     * |        |          |0 = PLL is in normal mode (default).
     * |        |          |1 = PLL clock output is same as PLL input clock FIN.
     * |[18]    |OE        |PLL OE (FOUT Enable) Pin Control
     * |        |          |0 = PLL FOUT Enabled.
     * |        |          |1 = PLL FOUT is fixed low.
     * |[19]    |PLLSRC    |PLL Source Clock Selection
     * |        |          |0 = PLL source clock from external 4~24 MHz high-speed crystal (HXT).
     * |        |          |1 = PLL source clock from internal 24 MHz high-speed oscillator (HIRC/2).
     * |[23]    |STBSEL    |PLL Stable Counter Selection
     * |        |          |0 = PLL stable time is 6144 PLL source clock (suitable for source clock is equal to or less than 12MHz).
     * |        |          |1 = PLL stable time is 12288 PLL source clock (suitable for source clock is larger than 12MHz).
     * @var CLK_T::CLKOCTL
     * Offset: 0x24  Clock Output Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |FREQSEL   |Clock Output Frequency Selection
     * |        |          |The formula of output frequency is
     * |        |          |Fout = Fin/2(N+1).
     * |        |          |Fin is the input clock frequency.
     * |        |          |Fout is the frequency of divider output clock.
     * |        |          |N is the 4-bit value of FREQSEL[3:0].
     * |[4]     |CLKOEN    |Clock Output Enable Bit
     * |        |          |0 = Clock Output function Disabled.
     * |        |          |1 = Clock Output function Enabled.
     * |[5]     |DIV1EN    |Clock Output Divide One Enable Bit
     * |        |          |0 = Clock Output will output clock with source frequency divided by FREQSEL.
     * |        |          |1 = Clock Output will output clock with source frequency.
     * @var CLK_T::APBCLK1
     * Offset: 0x30  APB Devices Clock Enable Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8]     |USCI0CKEN |USCI0 Clock Enable Bit
     * |        |          |0 = USCI0 clock Disabled.
     * |        |          |1 = USCI0 clock Enabled.
     * @var CLK_T::CLKSEL3
     * Offset: 0x34  Clock Source Select Control Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8]     |USBDSEL   |USBD Clock Source Selection
     * |        |          |0 = Clock source from 48MHz internal hight speed RC oscillator clock.
     * |        |          |1 = Clock source from PLL clock.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var CLK_T::CLKDCTL
     * Offset: 0x70  Clock Fail Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4]     |HXTFDEN   |HXT Clock Fail Detector Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock Fail detector Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock Fail detector Enabled.
     * |[5]     |HXTFIEN   |HXT Clock Fail Interrupt Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT)clock Fail interrupt Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT)clock Fail interrupt Enabled.
     * |[12]    |LXTFDEN   |LXT Clock Fail Detector Enable Bit
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail detector Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail detector Enabled.
     * |[13]    |LXTFIEN   |LXT Clock Fail Interrupt Enable Bit
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail interrupt Disabled.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) clock Fail interrupt Enabled.
     * |[16]    |HXTFQDEN  |HXT Clock Frequency Monitor Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor Enabled.
     * |[17]    |HXTFQIEN  |HXT Clock Frequency Monitor Interrupt Enable Bit
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor fail interrupt Disabled.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency monitor fail interrupt Enabled.
     * @var CLK_T::CLKDSTS
     * Offset: 0x74  Clock Fail Detector Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |HXTFIF    |HXT Clock Fail Interrupt Flag
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock normal.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock stop.
     * |        |          |Note: Write 1 to clear the bit to 0.
     * |[1]     |LXTFIF    |LXT Clock Fail Interrupt Flag
     * |        |          |0 = 32.768 kHz external low speed crystal oscillator (LXT) clock normal.
     * |        |          |1 = 32.768 kHz external low speed crystal oscillator (LXT) stop.
     * |        |          |Note: Write 1 to clear the bit to 0.
     * |[8]     |HXTFQIF   |HXT Clock Frequency Monitor Interrupt Flag
     * |        |          |0 = 4~24 MHz external high speed crystal oscillator (HXT) clock normal.
     * |        |          |1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency abnormal.
     * |        |          |Note: Write 1 to clear the bit to 0.
     * @var CLK_T::CDUPB
     * Offset: 0x78  Clock Frequency Detector Upper Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |UPERBD    |HXT Clock Frequency Detector Upper Boundary
     * |        |          |The bits define the high value of frequency monitor window.
     * |        |          |When HXT frequency monitor value higher than this register, the HXT frequency detect fail interrupt flag will set to 1.Note: The boundary is defined as the maximun value of HXT among 266 HIRC clock time
     * @var CLK_T::CDLOWB
     * Offset: 0x7C  Clock Frequency Detector Low Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[9:0]   |LOWERBD   |HXT Clock Frequency Detector Low Boundary
     * |        |          |The bits define the low value of frequency monitor window.
     * |        |          |When HXT frequency monitor value lower than this register, the HXT frequency detect fail interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the minimun value of HXT among 246 HIRC clock time
     */
    __IO uint32_t PWRCTL;                /*!< [0x0000] System Power-down Control Register                               */
    __IO uint32_t AHBCLK;                /*!< [0x0004] AHB Devices Clock Enable Control Register                        */
    __IO uint32_t APBCLK0;               /*!< [0x0008] APB Devices Clock Enable Control Register 0                      */
    __I  uint32_t STATUS;                /*!< [0x000c] Clock Status Monitor Register                                    */
    __IO uint32_t CLKSEL0;               /*!< [0x0010] Clock Source Select Control Register 0                           */
    __IO uint32_t CLKSEL1;               /*!< [0x0014] Clock Source Select Control Register 1                           */
    __IO uint32_t CLKDIV0;               /*!< [0x0018] Clock Divider Number Register 0                                  */
    __IO uint32_t CLKSEL2;               /*!< [0x001c] Clock Source Select Control Register 2                           */
    __IO uint32_t PLLCTL;                /*!< [0x0020] PLL Control Register                                             */
    __IO uint32_t CLKOCTL;               /*!< [0x0024] Clock Output Control Register                                    */
    __I  uint32_t RESERVE0[2];
    __IO uint32_t APBCLK1;               /*!< [0x0030] APB Devices Clock Enable Control Register 1                      */
    __IO uint32_t CLKSEL3;               /*!< [0x0034] Clock Source Select Control Register 3                           */
    __I  uint32_t RESERVE1[14];
    __IO uint32_t CLKDCTL;               /*!< [0x0070] Clock Fail Detector Control Register                             */
    __IO uint32_t CLKDSTS;               /*!< [0x0074] Clock Fail Detector Status Register                              */
    __IO uint32_t CDUPB;                 /*!< [0x0078] Clock Frequency Detector Upper Boundary Register                 */
    __IO uint32_t CDLOWB;                /*!< [0x007c] Clock Frequency Detector Low Boundary Register                   */
} CLK_T;

/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
@{ */

#define CLK_PWRCTL_XTLEN_Pos             (0)                                               /*!< CLK_T::PWRCTL: XTLEN Position          */
#define CLK_PWRCTL_XTLEN_Msk             (0x3ul << CLK_PWRCTL_XTLEN_Pos)                   /*!< CLK_T::PWRCTL: XTLEN Mask              */

#define CLK_PWRCTL_HIRCEN_Pos            (2)                                               /*!< CLK_T::PWRCTL: HIRCEN Position         */
#define CLK_PWRCTL_HIRCEN_Msk            (0x1ul << CLK_PWRCTL_HIRCEN_Pos)                  /*!< CLK_T::PWRCTL: HIRCEN Mask             */

#define CLK_PWRCTL_LIRCEN_Pos            (3)                                               /*!< CLK_T::PWRCTL: LIRCEN Position         */
#define CLK_PWRCTL_LIRCEN_Msk            (0x1ul << CLK_PWRCTL_LIRCEN_Pos)                  /*!< CLK_T::PWRCTL: LIRCEN Mask             */

#define CLK_PWRCTL_PDWKDLY_Pos           (4)                                               /*!< CLK_T::PWRCTL: PDWKDLY Position        */
#define CLK_PWRCTL_PDWKDLY_Msk           (0x1ul << CLK_PWRCTL_PDWKDLY_Pos)                 /*!< CLK_T::PWRCTL: PDWKDLY Mask            */

#define CLK_PWRCTL_PDWKIEN_Pos           (5)                                               /*!< CLK_T::PWRCTL: PDWKIEN Position        */
#define CLK_PWRCTL_PDWKIEN_Msk           (0x1ul << CLK_PWRCTL_PDWKIEN_Pos)                 /*!< CLK_T::PWRCTL: PDWKIEN Mask            */

#define CLK_PWRCTL_PDWKIF_Pos            (6)                                               /*!< CLK_T::PWRCTL: PDWKIF Position         */
#define CLK_PWRCTL_PDWKIF_Msk            (0x1ul << CLK_PWRCTL_PDWKIF_Pos)                  /*!< CLK_T::PWRCTL: PDWKIF Mask             */

#define CLK_PWRCTL_PDEN_Pos              (7)                                               /*!< CLK_T::PWRCTL: PDEN Position           */
#define CLK_PWRCTL_PDEN_Msk              (0x1ul << CLK_PWRCTL_PDEN_Pos)                    /*!< CLK_T::PWRCTL: PDEN Mask               */

#define CLK_PWRCTL_HXTGAIN_Pos           (10)                                              /*!< CLK_T::PWRCTL: HXTGAIN Position        */
#define CLK_PWRCTL_HXTGAIN_Msk           (0x3ul << CLK_PWRCTL_HXTGAIN_Pos)                 /*!< CLK_T::PWRCTL: HXTGAIN Mask            */

#define CLK_PWRCTL_HXTSELTYP_Pos         (12)                                              /*!< CLK_T::PWRCTL: HXTSELTYP Position      */
#define CLK_PWRCTL_HXTSELTYP_Msk         (0x1ul << CLK_PWRCTL_HXTSELTYP_Pos)               /*!< CLK_T::PWRCTL: HXTSELTYP Mask          */

#define CLK_AHBCLK_PDMACKEN_Pos          (1)                                               /*!< CLK_T::AHBCLK: PDMACKEN Position       */
#define CLK_AHBCLK_PDMACKEN_Msk          (0x1ul << CLK_AHBCLK_PDMACKEN_Pos)                /*!< CLK_T::AHBCLK: PDMACKEN Mask           */

#define CLK_AHBCLK_ISPCKEN_Pos           (2)                                               /*!< CLK_T::AHBCLK: ISPCKEN Position        */
#define CLK_AHBCLK_ISPCKEN_Msk           (0x1ul << CLK_AHBCLK_ISPCKEN_Pos)                 /*!< CLK_T::AHBCLK: ISPCKEN Mask            */

#define CLK_AHBCLK_FMCIDLE_Pos           (15)                                              /*!< CLK_T::AHBCLK: FMCIDLE Position        */
#define CLK_AHBCLK_FMCIDLE_Msk           (0x1ul << CLK_AHBCLK_FMCIDLE_Pos)                 /*!< CLK_T::AHBCLK: FMCIDLE Mask            */

#define CLK_AHBCLK_GPIOACKEN_Pos         (16)                                              /*!< CLK_T::AHBCLK: GPIOACKEN Position      */
#define CLK_AHBCLK_GPIOACKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOACKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOACKEN Mask          */

#define CLK_AHBCLK_GPIOBCKEN_Pos         (17)                                              /*!< CLK_T::AHBCLK: GPIOBCKEN Position      */
#define CLK_AHBCLK_GPIOBCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOBCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOBCKEN Mask          */

#define CLK_AHBCLK_GPIOCCKEN_Pos         (18)                                              /*!< CLK_T::AHBCLK: GPIOCCKEN Position      */
#define CLK_AHBCLK_GPIOCCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOCCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOCCKEN Mask          */

#define CLK_AHBCLK_GPIODCKEN_Pos         (19)                                              /*!< CLK_T::AHBCLK: GPIODCKEN Position      */
#define CLK_AHBCLK_GPIODCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIODCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIODCKEN Mask          */

#define CLK_AHBCLK_GPIOECKEN_Pos         (20)                                              /*!< CLK_T::AHBCLK: GPIOECKEN Position      */
#define CLK_AHBCLK_GPIOECKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOECKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOECKEN Mask          */

#define CLK_AHBCLK_GPIOFCKEN_Pos         (21)                                              /*!< CLK_T::AHBCLK: GPIOFCKEN Position      */
#define CLK_AHBCLK_GPIOFCKEN_Msk         (0x1ul << CLK_AHBCLK_GPIOFCKEN_Pos)               /*!< CLK_T::AHBCLK: GPIOFCKEN Mask          */

#define CLK_APBCLK0_WDTCKEN_Pos          (0)                                               /*!< CLK_T::APBCLK0: WDTCKEN Position       */
#define CLK_APBCLK0_WDTCKEN_Msk          (0x1ul << CLK_APBCLK0_WDTCKEN_Pos)                /*!< CLK_T::APBCLK0: WDTCKEN Mask           */

#define CLK_APBCLK0_TMR0CKEN_Pos         (2)                                               /*!< CLK_T::APBCLK0: TMR0CKEN Position      */
#define CLK_APBCLK0_TMR0CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR0CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR0CKEN Mask          */

#define CLK_APBCLK0_TMR1CKEN_Pos         (3)                                               /*!< CLK_T::APBCLK0: TMR1CKEN Position      */
#define CLK_APBCLK0_TMR1CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR1CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR1CKEN Mask          */

#define CLK_APBCLK0_TMR2CKEN_Pos         (4)                                               /*!< CLK_T::APBCLK0: TMR2CKEN Position      */
#define CLK_APBCLK0_TMR2CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR2CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR2CKEN Mask          */

#define CLK_APBCLK0_TMR3CKEN_Pos         (5)                                               /*!< CLK_T::APBCLK0: TMR3CKEN Position      */
#define CLK_APBCLK0_TMR3CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR3CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR3CKEN Mask          */

#define CLK_APBCLK0_CLKOCKEN_Pos         (6)                                               /*!< CLK_T::APBCLK0: CLKOCKEN Position      */
#define CLK_APBCLK0_CLKOCKEN_Msk         (0x1ul << CLK_APBCLK0_CLKOCKEN_Pos)               /*!< CLK_T::APBCLK0: CLKOCKEN Mask          */

#define CLK_APBCLK0_I2C0CKEN_Pos         (8)                                               /*!< CLK_T::APBCLK0: I2C0CKEN Position      */
#define CLK_APBCLK0_I2C0CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C0CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C0CKEN Mask          */

#define CLK_APBCLK0_I2C1CKEN_Pos         (9)                                               /*!< CLK_T::APBCLK0: I2C1CKEN Position      */
#define CLK_APBCLK0_I2C1CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C1CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C1CKEN Mask          */

#define CLK_APBCLK0_SPI0CKEN_Pos         (12)                                              /*!< CLK_T::APBCLK0: SPI0CKEN Position      */
#define CLK_APBCLK0_SPI0CKEN_Msk         (0x1ul << CLK_APBCLK0_SPI0CKEN_Pos)               /*!< CLK_T::APBCLK0: SPI0CKEN Mask          */

#define CLK_APBCLK0_UART0CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK0: UART0CKEN Position     */
#define CLK_APBCLK0_UART0CKEN_Msk        (0x1ul << CLK_APBCLK0_UART0CKEN_Pos)              /*!< CLK_T::APBCLK0: UART0CKEN Mask         */

#define CLK_APBCLK0_BPWM0CKEN_Pos        (20)                                              /*!< CLK_T::APBCLK0: BPWM0CKEN Position     */
#define CLK_APBCLK0_BPWM0CKEN_Msk        (0x1ul << CLK_APBCLK0_BPWM0CKEN_Pos)              /*!< CLK_T::APBCLK0: BPWM0CKEN Mask         */

#define CLK_APBCLK0_BPWM1CKEN_Pos        (21)                                              /*!< CLK_T::APBCLK0: BPWM1CKEN Position     */
#define CLK_APBCLK0_BPWM1CKEN_Msk        (0x1ul << CLK_APBCLK0_BPWM1CKEN_Pos)              /*!< CLK_T::APBCLK0: BPWM1CKEN Mask         */

#define CLK_APBCLK0_PWM0CKEN_Pos         (22)                                              /*!< CLK_T::APBCLK0: PWM0CKEN Position      */
#define CLK_APBCLK0_PWM0CKEN_Msk         (0x1ul << CLK_APBCLK0_PWM0CKEN_Pos)               /*!< CLK_T::APBCLK0: PWM0CKEN Mask          */

#define CLK_APBCLK0_PWM1CKEN_Pos         (23)                                              /*!< CLK_T::APBCLK0: PWM1CKEN Position      */
#define CLK_APBCLK0_PWM1CKEN_Msk         (0x1ul << CLK_APBCLK0_PWM1CKEN_Pos)               /*!< CLK_T::APBCLK0: PWM1CKEN Mask          */

#define CLK_APBCLK0_USBDCKEN_Pos         (27)                                              /*!< CLK_T::APBCLK0: USBDCKEN Position      */
#define CLK_APBCLK0_USBDCKEN_Msk         (0x1ul << CLK_APBCLK0_USBDCKEN_Pos)               /*!< CLK_T::APBCLK0: USBDCKEN Mask          */

#define CLK_APBCLK0_ADCCKEN_Pos          (28)                                              /*!< CLK_T::APBCLK0: ADCCKEN Position       */
#define CLK_APBCLK0_ADCCKEN_Msk          (0x1ul << CLK_APBCLK0_ADCCKEN_Pos)                /*!< CLK_T::APBCLK0: ADCCKEN Mask           */

#define CLK_STATUS_HXTSTB_Pos            (0)                                               /*!< CLK_T::STATUS: HXTSTB Position         */
#define CLK_STATUS_HXTSTB_Msk            (0x1ul << CLK_STATUS_HXTSTB_Pos)                  /*!< CLK_T::STATUS: HXTSTB Mask             */

#define CLK_STATUS_LXTSTB_Pos            (1)                                               /*!< CLK_T::STATUS: LXTSTB Position         */
#define CLK_STATUS_LXTSTB_Msk            (0x1ul << CLK_STATUS_LXTSTB_Pos)                  /*!< CLK_T::STATUS: LXTSTB Mask             */

#define CLK_STATUS_PLLSTB_Pos            (2)                                               /*!< CLK_T::STATUS: PLLSTB Position         */
#define CLK_STATUS_PLLSTB_Msk            (0x1ul << CLK_STATUS_PLLSTB_Pos)                  /*!< CLK_T::STATUS: PLLSTB Mask             */

#define CLK_STATUS_LIRCSTB_Pos           (3)                                               /*!< CLK_T::STATUS: LIRCSTB Position        */
#define CLK_STATUS_LIRCSTB_Msk           (0x1ul << CLK_STATUS_LIRCSTB_Pos)                 /*!< CLK_T::STATUS: LIRCSTB Mask            */

#define CLK_STATUS_HIRCSTB_Pos           (4)                                               /*!< CLK_T::STATUS: HIRCSTB Position        */
#define CLK_STATUS_HIRCSTB_Msk           (0x1ul << CLK_STATUS_HIRCSTB_Pos)                 /*!< CLK_T::STATUS: HIRCSTB Mask            */

#define CLK_STATUS_CLKSFAIL_Pos          (7)                                               /*!< CLK_T::STATUS: CLKSFAIL Position       */
#define CLK_STATUS_CLKSFAIL_Msk          (0x1ul << CLK_STATUS_CLKSFAIL_Pos)                /*!< CLK_T::STATUS: CLKSFAIL Mask           */

#define CLK_CLKSEL0_HCLKSEL_Pos          (0)                                               /*!< CLK_T::CLKSEL0: HCLKSEL Position       */
#define CLK_CLKSEL0_HCLKSEL_Msk          (0x7ul << CLK_CLKSEL0_HCLKSEL_Pos)                /*!< CLK_T::CLKSEL0: HCLKSEL Mask           */

#define CLK_CLKSEL0_STCLKSEL_Pos         (3)                                               /*!< CLK_T::CLKSEL0: STCLKSEL Position      */
#define CLK_CLKSEL0_STCLKSEL_Msk         (0x7ul << CLK_CLKSEL0_STCLKSEL_Pos)               /*!< CLK_T::CLKSEL0: STCLKSEL Mask          */

#define CLK_CLKSEL0_PCLK0SEL_Pos         (6)                                               /*!< CLK_T::CLKSEL0: PCLK0SEL Position      */
#define CLK_CLKSEL0_PCLK0SEL_Msk         (0x1ul << CLK_CLKSEL0_PCLK0SEL_Pos)               /*!< CLK_T::CLKSEL0: PCLK0SEL Mask          */

#define CLK_CLKSEL0_PCLK1SEL_Pos         (7)                                               /*!< CLK_T::CLKSEL0: PCLK1SEL Position      */
#define CLK_CLKSEL0_PCLK1SEL_Msk         (0x1ul << CLK_CLKSEL0_PCLK1SEL_Pos)               /*!< CLK_T::CLKSEL0: PCLK1SEL Mask          */

#define CLK_CLKSEL1_WDTSEL_Pos           (0)                                               /*!< CLK_T::CLKSEL1: WDTSEL Position        */
#define CLK_CLKSEL1_WDTSEL_Msk           (0x3ul << CLK_CLKSEL1_WDTSEL_Pos)                 /*!< CLK_T::CLKSEL1: WDTSEL Mask            */

#define CLK_CLKSEL1_ADCSEL_Pos           (2)                                               /*!< CLK_T::CLKSEL1: ADCSEL Position        */
#define CLK_CLKSEL1_ADCSEL_Msk           (0x3ul << CLK_CLKSEL1_ADCSEL_Pos)                 /*!< CLK_T::CLKSEL1: ADCSEL Mask            */

#define CLK_CLKSEL1_TMR0SEL_Pos          (8)                                               /*!< CLK_T::CLKSEL1: TMR0SEL Position       */
#define CLK_CLKSEL1_TMR0SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR0SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR0SEL Mask           */

#define CLK_CLKSEL1_TMR1SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL1: TMR1SEL Position       */
#define CLK_CLKSEL1_TMR1SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR1SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR1SEL Mask           */

#define CLK_CLKSEL1_TMR2SEL_Pos          (16)                                              /*!< CLK_T::CLKSEL1: TMR2SEL Position       */
#define CLK_CLKSEL1_TMR2SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR2SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR2SEL Mask           */

#define CLK_CLKSEL1_TMR3SEL_Pos          (20)                                              /*!< CLK_T::CLKSEL1: TMR3SEL Position       */
#define CLK_CLKSEL1_TMR3SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR3SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR3SEL Mask           */

#define CLK_CLKSEL1_UARTSEL_Pos          (24)                                              /*!< CLK_T::CLKSEL1: UARTSEL Position       */
#define CLK_CLKSEL1_UARTSEL_Msk          (0x3ul << CLK_CLKSEL1_UARTSEL_Pos)                /*!< CLK_T::CLKSEL1: UARTSEL Mask           */

#define CLK_CLKSEL1_BPWM0SEL_Pos         (28)                                              /*!< CLK_T::CLKSEL1: BPWM0SEL Position      */
#define CLK_CLKSEL1_BPWM0SEL_Msk         (0x1ul << CLK_CLKSEL1_BPWM0SEL_Pos)               /*!< CLK_T::CLKSEL1: BPWM0SEL Mask          */

#define CLK_CLKSEL1_BPWM1SEL_Pos         (29)                                              /*!< CLK_T::CLKSEL1: BPWM1SEL Position      */
#define CLK_CLKSEL1_BPWM1SEL_Msk         (0x1ul << CLK_CLKSEL1_BPWM1SEL_Pos)               /*!< CLK_T::CLKSEL1: BPWM1SEL Mask          */

#define CLK_CLKSEL1_PWM0SEL_Pos          (30)                                              /*!< CLK_T::CLKSEL1: PWM0SEL Position       */
#define CLK_CLKSEL1_PWM0SEL_Msk          (0x1ul << CLK_CLKSEL1_PWM0SEL_Pos)                /*!< CLK_T::CLKSEL1: PWM0SEL Mask           */

#define CLK_CLKSEL1_PWM1SEL_Pos          (31)                                              /*!< CLK_T::CLKSEL1: PWM1SEL Position       */
#define CLK_CLKSEL1_PWM1SEL_Msk          (0x1ul << CLK_CLKSEL1_PWM1SEL_Pos)                /*!< CLK_T::CLKSEL1: PWM1SEL Mask           */

#define CLK_CLKDIV0_HCLKDIV_Pos          (0)                                               /*!< CLK_T::CLKDIV0: HCLKDIV Position       */
#define CLK_CLKDIV0_HCLKDIV_Msk          (0xful << CLK_CLKDIV0_HCLKDIV_Pos)                /*!< CLK_T::CLKDIV0: HCLKDIV Mask           */

#define CLK_CLKDIV0_USBDIV_Pos           (4)                                               /*!< CLK_T::CLKDIV0: USBDIV Position        */
#define CLK_CLKDIV0_USBDIV_Msk           (0xful << CLK_CLKDIV0_USBDIV_Pos)                 /*!< CLK_T::CLKDIV0: USBDIV Mask            */

#define CLK_CLKDIV0_UARTDIV_Pos          (8)                                               /*!< CLK_T::CLKDIV0: UARTDIV Position       */
#define CLK_CLKDIV0_UARTDIV_Msk          (0xful << CLK_CLKDIV0_UARTDIV_Pos)                /*!< CLK_T::CLKDIV0: UARTDIV Mask           */

#define CLK_CLKDIV0_ADCDIV_Pos           (16)                                              /*!< CLK_T::CLKDIV0: ADCDIV Position        */
#define CLK_CLKDIV0_ADCDIV_Msk           (0xfful << CLK_CLKDIV0_ADCDIV_Pos)                /*!< CLK_T::CLKDIV0: ADCDIV Mask            */

#define CLK_CLKSEL2_CLKOSEL_Pos          (2)                                               /*!< CLK_T::CLKSEL2: CLKOSEL Position       */
#define CLK_CLKSEL2_CLKOSEL_Msk          (0x7ul << CLK_CLKSEL2_CLKOSEL_Pos)                /*!< CLK_T::CLKSEL2: CLKOSEL Mask           */

#define CLK_CLKSEL2_WWDTSEL_Pos          (16)                                              /*!< CLK_T::CLKSEL2: WWDTSEL Position       */
#define CLK_CLKSEL2_WWDTSEL_Msk          (0x3ul << CLK_CLKSEL2_WWDTSEL_Pos)                /*!< CLK_T::CLKSEL2: WWDTSEL Mask           */

#define CLK_CLKSEL2_SPI0SEL_Pos          (24)                                              /*!< CLK_T::CLKSEL2: SPI0SEL Position       */
#define CLK_CLKSEL2_SPI0SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI0SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI0SEL Mask           */

#define CLK_PLLCTL_FBDIV_Pos             (0)                                               /*!< CLK_T::PLLCTL: FBDIV Position          */
#define CLK_PLLCTL_FBDIV_Msk             (0x1fful << CLK_PLLCTL_FBDIV_Pos)                 /*!< CLK_T::PLLCTL: FBDIV Mask              */

#define CLK_PLLCTL_INDIV_Pos             (9)                                               /*!< CLK_T::PLLCTL: INDIV Position          */
#define CLK_PLLCTL_INDIV_Msk             (0x1ful << CLK_PLLCTL_INDIV_Pos)                  /*!< CLK_T::PLLCTL: INDIV Mask              */

#define CLK_PLLCTL_OUTDIV_Pos            (14)                                              /*!< CLK_T::PLLCTL: OUTDIV Position         */
#define CLK_PLLCTL_OUTDIV_Msk            (0x3ul << CLK_PLLCTL_OUTDIV_Pos)                  /*!< CLK_T::PLLCTL: OUTDIV Mask             */

#define CLK_PLLCTL_PD_Pos                (16)                                              /*!< CLK_T::PLLCTL: PD Position             */
#define CLK_PLLCTL_PD_Msk                (0x1ul << CLK_PLLCTL_PD_Pos)                      /*!< CLK_T::PLLCTL: PD Mask                 */

#define CLK_PLLCTL_BP_Pos                (17)                                              /*!< CLK_T::PLLCTL: BP Position             */
#define CLK_PLLCTL_BP_Msk                (0x1ul << CLK_PLLCTL_BP_Pos)                      /*!< CLK_T::PLLCTL: BP Mask                 */

#define CLK_PLLCTL_OE_Pos                (18)                                              /*!< CLK_T::PLLCTL: OE Position             */
#define CLK_PLLCTL_OE_Msk                (0x1ul << CLK_PLLCTL_OE_Pos)                      /*!< CLK_T::PLLCTL: OE Mask                 */

#define CLK_PLLCTL_PLLSRC_Pos            (19)                                              /*!< CLK_T::PLLCTL: PLLSRC Position         */
#define CLK_PLLCTL_PLLSRC_Msk            (0x1ul << CLK_PLLCTL_PLLSRC_Pos)                  /*!< CLK_T::PLLCTL: PLLSRC Mask             */

#define CLK_PLLCTL_STBSEL_Pos            (23)                                              /*!< CLK_T::PLLCTL: STBSEL Position         */
#define CLK_PLLCTL_STBSEL_Msk            (0x1ul << CLK_PLLCTL_STBSEL_Pos)                  /*!< CLK_T::PLLCTL: STBSEL Mask             */

#define CLK_CLKOCTL_FREQSEL_Pos          (0)                                               /*!< CLK_T::CLKOCTL: FREQSEL Position       */
#define CLK_CLKOCTL_FREQSEL_Msk          (0xful << CLK_CLKOCTL_FREQSEL_Pos)                /*!< CLK_T::CLKOCTL: FREQSEL Mask           */

#define CLK_CLKOCTL_CLKOEN_Pos           (4)                                               /*!< CLK_T::CLKOCTL: CLKOEN Position        */
#define CLK_CLKOCTL_CLKOEN_Msk           (0x1ul << CLK_CLKOCTL_CLKOEN_Pos)                 /*!< CLK_T::CLKOCTL: CLKOEN Mask            */

#define CLK_CLKOCTL_DIV1EN_Pos           (5)                                               /*!< CLK_T::CLKOCTL: DIV1EN Position        */
#define CLK_CLKOCTL_DIV1EN_Msk           (0x1ul << CLK_CLKOCTL_DIV1EN_Pos)                 /*!< CLK_T::CLKOCTL: DIV1EN Mask            */

#define CLK_APBCLK1_USCI0CKEN_Pos        (8)                                               /*!< CLK_T::APBCLK1: USCI0CKEN Position     */
#define CLK_APBCLK1_USCI0CKEN_Msk        (0x1ul << CLK_APBCLK1_USCI0CKEN_Pos)              /*!< CLK_T::APBCLK1: USCI0CKEN Mask         */

#define CLK_CLKSEL3_USBDSEL_Pos          (8)                                               /*!< CLK_T::CLKSEL3: USBDSEL Position       */
#define CLK_CLKSEL3_USBDSEL_Msk          (0x1ul << CLK_CLKSEL3_USBDSEL_Pos)                /*!< CLK_T::CLKSEL3: USBDSEL Mask           */

#define CLK_CLKDCTL_HXTFDEN_Pos          (4)                                               /*!< CLK_T::CLKDCTL: HXTFDEN Position       */
#define CLK_CLKDCTL_HXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFDEN Mask           */

#define CLK_CLKDCTL_HXTFIEN_Pos          (5)                                               /*!< CLK_T::CLKDCTL: HXTFIEN Position       */
#define CLK_CLKDCTL_HXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFIEN Mask           */

#define CLK_CLKDCTL_LXTFDEN_Pos          (12)                                              /*!< CLK_T::CLKDCTL: LXTFDEN Position       */
#define CLK_CLKDCTL_LXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFDEN Mask           */

#define CLK_CLKDCTL_LXTFIEN_Pos          (13)                                              /*!< CLK_T::CLKDCTL: LXTFIEN Position       */
#define CLK_CLKDCTL_LXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFIEN Mask           */

#define CLK_CLKDCTL_HXTFQDEN_Pos         (16)                                              /*!< CLK_T::CLKDCTL: HXTFQDEN Position      */
#define CLK_CLKDCTL_HXTFQDEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQDEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQDEN Mask          */

#define CLK_CLKDCTL_HXTFQIEN_Pos         (17)                                              /*!< CLK_T::CLKDCTL: HXTFQIEN Position      */
#define CLK_CLKDCTL_HXTFQIEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQIEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQIEN Mask          */

#define CLK_CLKDSTS_HXTFIF_Pos           (0)                                               /*!< CLK_T::CLKDSTS: HXTFIF Position        */
#define CLK_CLKDSTS_HXTFIF_Msk           (0x1ul << CLK_CLKDSTS_HXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: HXTFIF Mask            */

#define CLK_CLKDSTS_LXTFIF_Pos           (1)                                               /*!< CLK_T::CLKDSTS: LXTFIF Position        */
#define CLK_CLKDSTS_LXTFIF_Msk           (0x1ul << CLK_CLKDSTS_LXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: LXTFIF Mask            */

#define CLK_CLKDSTS_HXTFQIF_Pos          (8)                                               /*!< CLK_T::CLKDSTS: HXTFQIF Position       */
#define CLK_CLKDSTS_HXTFQIF_Msk          (0x1ul << CLK_CLKDSTS_HXTFQIF_Pos)                /*!< CLK_T::CLKDSTS: HXTFQIF Mask           */

#define CLK_CDUPB_UPERBD_Pos             (0)                                               /*!< CLK_T::CDUPB: UPERBD Position          */
#define CLK_CDUPB_UPERBD_Msk             (0x3fful << CLK_CDUPB_UPERBD_Pos)                 /*!< CLK_T::CDUPB: UPERBD Mask              */

#define CLK_CDLOWB_LOWERBD_Pos           (0)                                               /*!< CLK_T::CDLOWB: LOWERBD Position        */
#define CLK_CDLOWB_LOWERBD_Msk           (0x3fful << CLK_CDLOWB_LOWERBD_Pos)               /*!< CLK_T::CDLOWB: LOWERBD Mask            */

/**@}*/ /* CLK_CONST */
/**@}*/ /* end of CLK register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __CLK_REG_H__ */
