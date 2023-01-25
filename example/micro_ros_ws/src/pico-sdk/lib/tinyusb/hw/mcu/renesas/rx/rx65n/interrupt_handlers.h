/************************************************************************/
/*    File Version : V0.5B                                              */
/*    History  : 0.5B  (2015-11-20)  [Hardware Manual Revision : 0.5B]  */
/*    Date Modified: 08/05/2019                                         */
/************************************************************************/

#ifndef INTERRUPT_HANDLERS_H
#define INTERRUPT_HANDLERS_H

// Exception(Supervisor Instruction)
void INT_Excep_SuperVisorInst(void) __attribute__ ((interrupt, weak));

// Exception(Access Instruction)
void INT_Excep_AccessInst(void) __attribute__ ((interrupt, weak));

// Exception(Undefined Instruction)
void INT_Excep_UndefinedInst(void) __attribute__ ((interrupt, weak));

// Exception(Floating Point)
void INT_Excep_FloatingPoint(void) __attribute__ ((interrupt, weak));

// NMI
void INT_NonMaskableInterrupt(void) __attribute__ ((interrupt, weak));

// Dummy
void Dummy(void) __attribute__ ((interrupt, weak));

// BRK
void INT_Excep_BRK(void) __attribute__ ((interrupt, weak));

// vector  1 reserved
// vector  2 reserved
// vector  3 reserved
// vector  4 reserved
// vector  5 reserved
// vector  6 reserved
// vector  7 reserved
// vector  8 reserved
// vector  9 reserved
// vector 10 reserved
// vector 11 reserved
// vector 12 reserved
// vector 13 reserved
// vector 14 reserved
// vector 15 reserved

// BSC BUSERR
void INT_Excep_BSC_BUSERR(void) __attribute__ ((interrupt, weak));

// vector 17 reserved

// RAM RAMERR
void INT_Excep_RAM_RAMERR(void) __attribute__ ((interrupt, weak));

// vector 19 reserved
// vector 20 reserved

// FCU FIFERR
void INT_Excep_FCU_FIFERR(void) __attribute__ ((interrupt, weak));

// vector 22 reserved

// FCU FRDYI
void INT_Excep_FCU_FRDYI(void) __attribute__ ((interrupt, weak));

// vector 24 reserved
// vector 25 reserved

// ICU SWINT2
void INT_Excep_ICU_SWINT2(void) __attribute__ ((interrupt, weak));

// ICU SWINT
void INT_Excep_ICU_SWINT(void) __attribute__ ((interrupt, weak));

// CMT0 CMI0
void INT_Excep_CMT0_CMI0(void) __attribute__ ((interrupt, weak));

// CMT1 CMI1
void INT_Excep_CMT1_CMI1(void) __attribute__ ((interrupt, weak));

// CMTW0 CMWI0
void INT_Excep_CMTW0_CMWI0(void) __attribute__ ((interrupt, weak));

// CMTW1 CMWI1
void INT_Excep_CMTW1_CMWI1(void) __attribute__ ((interrupt, weak));

// vector 32 reserved
// vector 33 reserved

// USB0 D0FIFO0
void INT_Excep_USB0_D0FIFO0(void) __attribute__ ((interrupt, weak));

// USB0 D1FIFO0
void INT_Excep_USB0_D1FIFO0(void) __attribute__ ((interrupt, weak));

// vector 36 reserved
// vector 37 reserved

// RSPI0 SPRI0
void INT_Excep_RSPI0_SPRI0(void) __attribute__ ((interrupt, weak));

// RSPI0 SPTI0
void INT_Excep_RSPI0_SPTI0(void) __attribute__ ((interrupt, weak));

// RSPI1 SPRI1
void INT_Excep_RSPI1_SPRI1(void) __attribute__ ((interrupt, weak));

// RSPI1 SPTI1
void INT_Excep_RSPI1_SPTI1(void) __attribute__ ((interrupt, weak));

// QSPI SPRI
void INT_Excep_QSPI_SPRI(void) __attribute__ ((interrupt, weak));

// QSPI SPTI
void INT_Excep_QSPI_SPTI(void) __attribute__ ((interrupt, weak));

// SDHI SBFAI
void INT_Excep_SDHI_SBFAI(void) __attribute__ ((interrupt, weak));

// MMCIF MBFAI
void INT_Excep_MMCIF_MBFAI(void) __attribute__ ((interrupt, weak));

// vector 46 reserved
// vector 47 reserved
// vector 48 reserved
// vector 49 reserved
// vector 50 reserved
// vector 51 reserved

// RIIC0 RXI0
void INT_Excep_RIIC0_RXI0(void) __attribute__ ((interrupt, weak));

// RIIC0 TXI0
void INT_Excep_RIIC0_TXI0(void) __attribute__ ((interrupt, weak));

// RIIC2 RXI2
void INT_Excep_RIIC2_RXI2(void) __attribute__ ((interrupt, weak));

// RIIC2 TXI2
void INT_Excep_RIIC2_TXI2(void) __attribute__ ((interrupt, weak));

// vector 56 reserved
// vector 57 reserved

// SCI0 RXI0
void INT_Excep_SCI0_RXI0(void) __attribute__ ((interrupt, weak));

// SCI0 TXI0
void INT_Excep_SCI0_TXI0(void) __attribute__ ((interrupt, weak));

// SCI1 RXI1
void INT_Excep_SCI1_RXI1(void) __attribute__ ((interrupt, weak));

// SCI1 TXI1
void INT_Excep_SCI1_TXI1(void) __attribute__ ((interrupt, weak));

// SCI2 RXI2
void INT_Excep_SCI2_RXI2(void) __attribute__ ((interrupt, weak));

// SCI2 TXI2
void INT_Excep_SCI2_TXI2(void) __attribute__ ((interrupt, weak));

// ICU IRQ0
void INT_Excep_ICU_IRQ0(void) __attribute__ ((interrupt, weak));

// ICU IRQ1
void INT_Excep_ICU_IRQ1(void) __attribute__ ((interrupt, weak));

// ICU IRQ2
void INT_Excep_ICU_IRQ2(void) __attribute__ ((interrupt, weak));

// ICU IRQ3
void INT_Excep_ICU_IRQ3(void) __attribute__ ((interrupt, weak));

// ICU IRQ4
void INT_Excep_ICU_IRQ4(void) __attribute__ ((interrupt, weak));

// ICU IRQ5
void INT_Excep_ICU_IRQ5(void) __attribute__ ((interrupt, weak));

// ICU IRQ6
void INT_Excep_ICU_IRQ6(void) __attribute__ ((interrupt, weak));

// ICU IRQ7
void INT_Excep_ICU_IRQ7(void) __attribute__ ((interrupt, weak));

// ICU IRQ8
void INT_Excep_ICU_IRQ8(void) __attribute__ ((interrupt, weak));

// ICU IRQ9
void INT_Excep_ICU_IRQ9(void) __attribute__ ((interrupt, weak));

// ICU IRQ10
void INT_Excep_ICU_IRQ10(void) __attribute__ ((interrupt, weak));

// ICU IRQ11
void INT_Excep_ICU_IRQ11(void) __attribute__ ((interrupt, weak));

// ICU IRQ12
void INT_Excep_ICU_IRQ12(void) __attribute__ ((interrupt, weak));

// ICU IRQ13
void INT_Excep_ICU_IRQ13(void) __attribute__ ((interrupt, weak));

// ICU IRQ14
void INT_Excep_ICU_IRQ14(void) __attribute__ ((interrupt, weak));

// ICU IRQ15
void INT_Excep_ICU_IRQ15(void) __attribute__ ((interrupt, weak));

// SCI3 RXI3
void INT_Excep_SCI3_RXI3(void) __attribute__ ((interrupt, weak));

// SCI3 TXI3
void INT_Excep_SCI3_TXI3(void) __attribute__ ((interrupt, weak));

// SCI4 RXI4
void INT_Excep_SCI4_RXI4(void) __attribute__ ((interrupt, weak));

// SCI4 TXI4
void INT_Excep_SCI4_TXI4(void) __attribute__ ((interrupt, weak));

// SCI5 RXI5
void INT_Excep_SCI5_RXI5(void) __attribute__ ((interrupt, weak));

// SCI5 TXI5
void INT_Excep_SCI5_TXI5(void) __attribute__ ((interrupt, weak));

// SCI6 RXI6
void INT_Excep_SCI6_RXI6(void) __attribute__ ((interrupt, weak));

// SCI6 TXI6
void INT_Excep_SCI6_TXI6(void) __attribute__ ((interrupt, weak));

// LVD1 LVD1
void INT_Excep_LVD1_LVD1(void) __attribute__ ((interrupt, weak));

// LVD2 LVD2
void INT_Excep_LVD2_LVD2(void) __attribute__ ((interrupt, weak));

// USB0 USBR0
void INT_Excep_USB0_USBR0(void) __attribute__ ((interrupt, weak));

// RTC ALM
void INT_Excep_RTC_ALM(void) __attribute__ ((interrupt, weak));

// RTC PRD
void INT_Excep_RTC_PRD(void) __attribute__ ((interrupt, weak));

// USBA USBAR
void INT_Excep_USBA_USBAR(void) __attribute__ ((interrupt, weak));

// IWDT IWUNI
void INT_Excep_IWDT_IWUNI(void) __attribute__ ((interrupt, weak));

// WDT WUNI
void INT_Excep_WDT_WUNI(void) __attribute__ ((interrupt, weak));

// PDC PCDFI
void INT_Excep_PDC_PCDFI(void) __attribute__ ((interrupt, weak));

// SCI7 RXI7
void INT_Excep_SCI7_RXI7(void) __attribute__ ((interrupt, weak));

// SCI7 TXI7
void INT_Excep_SCI7_TXI7(void) __attribute__ ((interrupt, weak));

// SCI8 RXI8
void INT_Excep_SCI8_RXI8(void) __attribute__ ((interrupt, weak));

// SCI8 TXI8
void INT_Excep_SCI8_TXI8(void) __attribute__ ((interrupt, weak));

// SCI9 RXI9
void INT_Excep_SCI9_RXI9(void) __attribute__ ((interrupt, weak));

// SCI9 TXI9
void INT_Excep_SCI9_TXI9(void) __attribute__ ((interrupt, weak));

// SCI10 RXI10
void INT_Excep_SCI10_RXI10(void) __attribute__ ((interrupt, weak));

// SCI10 TXI10
void INT_Excep_SCI10_TXI10(void) __attribute__ ((interrupt, weak));

// ICU GROUPBE0
void INT_Excep_ICU_GROUPBE0(void) __attribute__ ((interrupt, weak));

// ICU GROUPBL2
void INT_Excep_ICU_GROUPBL2(void) __attribute__ ((interrupt, weak));

// RSPI2 SPRI2
void INT_Excep_RSPI2_SPRI2(void) __attribute__ ((interrupt, weak));

// RSPI2 SPTI2
void INT_Excep_RSPI2_SPTI2(void) __attribute__ ((interrupt, weak));

// ICU GROUPBL0
void INT_Excep_ICU_GROUPBL0(void) __attribute__ ((interrupt, weak));

// ICU GROUPBL1
void INT_Excep_ICU_GROUPBL1(void) __attribute__ ((interrupt, weak));

// ICU GROUPAL0
void INT_Excep_ICU_GROUPAL0(void) __attribute__ ((interrupt, weak));

// ICU GROUPAL1
void INT_Excep_ICU_GROUPAL1(void) __attribute__ ((interrupt, weak));

// SCI11 RXI11
void INT_Excep_SCI11_RXI11(void) __attribute__ ((interrupt, weak));

// SCI11 TXI11
void INT_Excep_SCI11_TXI11(void) __attribute__ ((interrupt, weak));

// SCI12 RXI12
void INT_Excep_SCI12_RXI12(void) __attribute__ ((interrupt, weak));

// SCI12 TXI12
void INT_Excep_SCI12_TXI12(void) __attribute__ ((interrupt, weak));

// vector 118 reserved
// vector 119 reserved

// DMAC DMAC0I
void INT_Excep_DMAC_DMAC0I(void) __attribute__ ((interrupt, weak));

// DMAC DMAC1I
void INT_Excep_DMAC_DMAC1I(void) __attribute__ ((interrupt, weak));

// DMAC DMAC2I
void INT_Excep_DMAC_DMAC2I(void) __attribute__ ((interrupt, weak));

// DMAC DMAC3I
void INT_Excep_DMAC_DMAC3I(void) __attribute__ ((interrupt, weak));

// DMAC DMAC74I
void INT_Excep_DMAC_DMAC74I(void) __attribute__ ((interrupt, weak));

// OST OSTDI
void INT_Excep_OST_OSTDI(void) __attribute__ ((interrupt, weak));

// EXDMAC EXDMAC0I
void INT_Excep_EXDMAC_EXDMAC0I(void) __attribute__ ((interrupt, weak));

// EXDMAC EXDMAC1I
void INT_Excep_EXDMAC_EXDMAC1I(void) __attribute__ ((interrupt, weak));

// PERIB INTB128
void INT_Excep_PERIB_INTB128(void) __attribute__ ((interrupt, weak));

// PERIB INTB129
void INT_Excep_PERIB_INTB129(void) __attribute__ ((interrupt, weak));

// PERIB INTB130
void INT_Excep_PERIB_INTB130(void) __attribute__ ((interrupt, weak));

// PERIB INTB131
void INT_Excep_PERIB_INTB131(void) __attribute__ ((interrupt, weak));

// PERIB INTB132
void INT_Excep_PERIB_INTB132(void) __attribute__ ((interrupt, weak));

// PERIB INTB133
void INT_Excep_PERIB_INTB133(void) __attribute__ ((interrupt, weak));

// PERIB INTB134
void INT_Excep_PERIB_INTB134(void) __attribute__ ((interrupt, weak));

// PERIB INTB135
void INT_Excep_PERIB_INTB135(void) __attribute__ ((interrupt, weak));

// PERIB INTB136
void INT_Excep_PERIB_INTB136(void) __attribute__ ((interrupt, weak));

// PERIB INTB137
void INT_Excep_PERIB_INTB137(void) __attribute__ ((interrupt, weak));

// PERIB INTB138
void INT_Excep_PERIB_INTB138(void) __attribute__ ((interrupt, weak));

// PERIB INTB139
void INT_Excep_PERIB_INTB139(void) __attribute__ ((interrupt, weak));

// PERIB INTB140
void INT_Excep_PERIB_INTB140(void) __attribute__ ((interrupt, weak));

// PERIB INTB141
void INT_Excep_PERIB_INTB141(void) __attribute__ ((interrupt, weak));

// PERIB INTB142
void INT_Excep_PERIB_INTB142(void) __attribute__ ((interrupt, weak));

// PERIB INTB143
void INT_Excep_PERIB_INTB143(void) __attribute__ ((interrupt, weak));

// PERIB INTB144
void INT_Excep_PERIB_INTB144(void) __attribute__ ((interrupt, weak));

// PERIB INTB145
void INT_Excep_PERIB_INTB145(void) __attribute__ ((interrupt, weak));

// PERIB INTB146
void INT_Excep_PERIB_INTB146(void) __attribute__ ((interrupt, weak));

// PERIB INTB147
void INT_Excep_PERIB_INTB147(void) __attribute__ ((interrupt, weak));

// PERIB INTB148
void INT_Excep_PERIB_INTB148(void) __attribute__ ((interrupt, weak));

// PERIB INTB149
void INT_Excep_PERIB_INTB149(void) __attribute__ ((interrupt, weak));

// PERIB INTB150
void INT_Excep_PERIB_INTB150(void) __attribute__ ((interrupt, weak));

// PERIB INTB151
void INT_Excep_PERIB_INTB151(void) __attribute__ ((interrupt, weak));

// PERIB INTB152
void INT_Excep_PERIB_INTB152(void) __attribute__ ((interrupt, weak));

// PERIB INTB153
void INT_Excep_PERIB_INTB153(void) __attribute__ ((interrupt, weak));

// PERIB INTB154
void INT_Excep_PERIB_INTB154(void) __attribute__ ((interrupt, weak));

// PERIB INTB155
void INT_Excep_PERIB_INTB155(void) __attribute__ ((interrupt, weak));

// PERIB INTB156
void INT_Excep_PERIB_INTB156(void) __attribute__ ((interrupt, weak));

// PERIB INTB157
void INT_Excep_PERIB_INTB157(void) __attribute__ ((interrupt, weak));

// PERIB INTB158
void INT_Excep_PERIB_INTB158(void) __attribute__ ((interrupt, weak));

// PERIB INTB159
void INT_Excep_PERIB_INTB159(void) __attribute__ ((interrupt, weak));

// PERIB INTB160
void INT_Excep_PERIB_INTB160(void) __attribute__ ((interrupt, weak));

// PERIB INTB161
void INT_Excep_PERIB_INTB161(void) __attribute__ ((interrupt, weak));

// PERIB INTB162
void INT_Excep_PERIB_INTB162(void) __attribute__ ((interrupt, weak));

// PERIB INTB163
void INT_Excep_PERIB_INTB163(void) __attribute__ ((interrupt, weak));

// PERIB INTB164
void INT_Excep_PERIB_INTB164(void) __attribute__ ((interrupt, weak));

// PERIB INTB165
void INT_Excep_PERIB_INTB165(void) __attribute__ ((interrupt, weak));

// PERIB INTB166
void INT_Excep_PERIB_INTB166(void) __attribute__ ((interrupt, weak));

// PERIB INTB167
void INT_Excep_PERIB_INTB167(void) __attribute__ ((interrupt, weak));

// PERIB INTB168
void INT_Excep_PERIB_INTB168(void) __attribute__ ((interrupt, weak));

// PERIB INTB169
void INT_Excep_PERIB_INTB169(void) __attribute__ ((interrupt, weak));

// PERIB INTB170
void INT_Excep_PERIB_INTB170(void) __attribute__ ((interrupt, weak));

// PERIB INTB171
void INT_Excep_PERIB_INTB171(void) __attribute__ ((interrupt, weak));

// PERIB INTB172
void INT_Excep_PERIB_INTB172(void) __attribute__ ((interrupt, weak));

// PERIB INTB173
void INT_Excep_PERIB_INTB173(void) __attribute__ ((interrupt, weak));

// PERIB INTB174
void INT_Excep_PERIB_INTB174(void) __attribute__ ((interrupt, weak));

// PERIB INTB175
void INT_Excep_PERIB_INTB175(void) __attribute__ ((interrupt, weak));

// PERIB INTB176
void INT_Excep_PERIB_INTB176(void) __attribute__ ((interrupt, weak));

// PERIB INTB177
void INT_Excep_PERIB_INTB177(void) __attribute__ ((interrupt, weak));

// PERIB INTB178
void INT_Excep_PERIB_INTB178(void) __attribute__ ((interrupt, weak));

// PERIB INTB179
void INT_Excep_PERIB_INTB179(void) __attribute__ ((interrupt, weak));

// PERIB INTB180
void INT_Excep_PERIB_INTB180(void) __attribute__ ((interrupt, weak));

// PERIB INTB181
void INT_Excep_PERIB_INTB181(void) __attribute__ ((interrupt, weak));

// PERIB INTB182
void INT_Excep_PERIB_INTB182(void) __attribute__ ((interrupt, weak));

// PERIB INTB183
void INT_Excep_PERIB_INTB183(void) __attribute__ ((interrupt, weak));

// PERIB INTB184
void INT_Excep_PERIB_INTB184(void) __attribute__ ((interrupt, weak));

// PERIB INTB185
void INT_Excep_PERIB_INTB185(void) __attribute__ ((interrupt, weak));

// PERIB INTB186
void INT_Excep_PERIB_INTB186(void) __attribute__ ((interrupt, weak));

// PERIB INTB187
void INT_Excep_PERIB_INTB187(void) __attribute__ ((interrupt, weak));

// PERIB INTB188
void INT_Excep_PERIB_INTB188(void) __attribute__ ((interrupt, weak));

// PERIB INTB189
void INT_Excep_PERIB_INTB189(void) __attribute__ ((interrupt, weak));

// PERIB INTB190
void INT_Excep_PERIB_INTB190(void) __attribute__ ((interrupt, weak));

// PERIB INTB191
void INT_Excep_PERIB_INTB191(void) __attribute__ ((interrupt, weak));

// PERIB INTB192
void INT_Excep_PERIB_INTB192(void) __attribute__ ((interrupt, weak));

// PERIB INTB193
void INT_Excep_PERIB_INTB193(void) __attribute__ ((interrupt, weak));

// PERIB INTB194
void INT_Excep_PERIB_INTB194(void) __attribute__ ((interrupt, weak));

// PERIB INTB195
void INT_Excep_PERIB_INTB195(void) __attribute__ ((interrupt, weak));

// PERIB INTB196
void INT_Excep_PERIB_INTB196(void) __attribute__ ((interrupt, weak));

// PERIB INTB197
void INT_Excep_PERIB_INTB197(void) __attribute__ ((interrupt, weak));

// PERIB INTB198
void INT_Excep_PERIB_INTB198(void) __attribute__ ((interrupt, weak));

// PERIB INTB199
void INT_Excep_PERIB_INTB199(void) __attribute__ ((interrupt, weak));

// PERIB INTB200
void INT_Excep_PERIB_INTB200(void) __attribute__ ((interrupt, weak));

// PERIB INTB201
void INT_Excep_PERIB_INTB201(void) __attribute__ ((interrupt, weak));

// PERIB INTB202
void INT_Excep_PERIB_INTB202(void) __attribute__ ((interrupt, weak));

// PERIB INTB203
void INT_Excep_PERIB_INTB203(void) __attribute__ ((interrupt, weak));

// PERIB INTB204
void INT_Excep_PERIB_INTB204(void) __attribute__ ((interrupt, weak));

// PERIB INTB205
void INT_Excep_PERIB_INTB205(void) __attribute__ ((interrupt, weak));

// PERIB INTB206
void INT_Excep_PERIB_INTB206(void) __attribute__ ((interrupt, weak));

// PERIB INTB207
void INT_Excep_PERIB_INTB207(void) __attribute__ ((interrupt, weak));

// PERIA INTA208
void INT_Excep_PERIA_INTA208(void) __attribute__ ((interrupt, weak));

// PERIA INTA209
void INT_Excep_PERIA_INTA209(void) __attribute__ ((interrupt, weak));

// PERIA INTA210
void INT_Excep_PERIA_INTA210(void) __attribute__ ((interrupt, weak));

// PERIA INTA211
void INT_Excep_PERIA_INTA211(void) __attribute__ ((interrupt, weak));

// PERIA INTA212
void INT_Excep_PERIA_INTA212(void) __attribute__ ((interrupt, weak));

// PERIA INTA213
void INT_Excep_PERIA_INTA213(void) __attribute__ ((interrupt, weak));

// PERIA INTA214
void INT_Excep_PERIA_INTA214(void) __attribute__ ((interrupt, weak));

// PERIA INTA215
void INT_Excep_PERIA_INTA215(void) __attribute__ ((interrupt, weak));

// PERIA INTA216
void INT_Excep_PERIA_INTA216(void) __attribute__ ((interrupt, weak));

// PERIA INTA217
void INT_Excep_PERIA_INTA217(void) __attribute__ ((interrupt, weak));

// PERIA INTA218
void INT_Excep_PERIA_INTA218(void) __attribute__ ((interrupt, weak));

// PERIA INTA219
void INT_Excep_PERIA_INTA219(void) __attribute__ ((interrupt, weak));

// PERIA INTA220
void INT_Excep_PERIA_INTA220(void) __attribute__ ((interrupt, weak));

// PERIA INTA221
void INT_Excep_PERIA_INTA221(void) __attribute__ ((interrupt, weak));

// PERIA INTA222
void INT_Excep_PERIA_INTA222(void) __attribute__ ((interrupt, weak));

// PERIA INTA223
void INT_Excep_PERIA_INTA223(void) __attribute__ ((interrupt, weak));

// PERIA INTA224
void INT_Excep_PERIA_INTA224(void) __attribute__ ((interrupt, weak));

// PERIA INTA225
void INT_Excep_PERIA_INTA225(void) __attribute__ ((interrupt, weak));

// PERIA INTA226
void INT_Excep_PERIA_INTA226(void) __attribute__ ((interrupt, weak));

// PERIA INTA227
void INT_Excep_PERIA_INTA227(void) __attribute__ ((interrupt, weak));

// PERIA INTA228
void INT_Excep_PERIA_INTA228(void) __attribute__ ((interrupt, weak));

// PERIA INTA229
void INT_Excep_PERIA_INTA229(void) __attribute__ ((interrupt, weak));

// PERIA INTA230
void INT_Excep_PERIA_INTA230(void) __attribute__ ((interrupt, weak));

// PERIA INTA231
void INT_Excep_PERIA_INTA231(void) __attribute__ ((interrupt, weak));

// PERIA INTA232
void INT_Excep_PERIA_INTA232(void) __attribute__ ((interrupt, weak));

// PERIA INTA233
void INT_Excep_PERIA_INTA233(void) __attribute__ ((interrupt, weak));

// PERIA INTA234
void INT_Excep_PERIA_INTA234(void) __attribute__ ((interrupt, weak));

// PERIA INTA235
void INT_Excep_PERIA_INTA235(void) __attribute__ ((interrupt, weak));

// PERIA INTA236
void INT_Excep_PERIA_INTA236(void) __attribute__ ((interrupt, weak));

// PERIA INTA237
void INT_Excep_PERIA_INTA237(void) __attribute__ ((interrupt, weak));

// PERIA INTA238
void INT_Excep_PERIA_INTA238(void) __attribute__ ((interrupt, weak));

// PERIA INTA239
void INT_Excep_PERIA_INTA239(void) __attribute__ ((interrupt, weak));

// PERIA INTA240
void INT_Excep_PERIA_INTA240(void) __attribute__ ((interrupt, weak));

// PERIA INTA241
void INT_Excep_PERIA_INTA241(void) __attribute__ ((interrupt, weak));

// PERIA INTA242
void INT_Excep_PERIA_INTA242(void) __attribute__ ((interrupt, weak));

// PERIA INTA243
void INT_Excep_PERIA_INTA243(void) __attribute__ ((interrupt, weak));

// PERIA INTA244
void INT_Excep_PERIA_INTA244(void) __attribute__ ((interrupt, weak));

// PERIA INTA245
void INT_Excep_PERIA_INTA245(void) __attribute__ ((interrupt, weak));

// PERIA INTA246
void INT_Excep_PERIA_INTA246(void) __attribute__ ((interrupt, weak));

// PERIA INTA247
void INT_Excep_PERIA_INTA247(void) __attribute__ ((interrupt, weak));

// PERIA INTA248
void INT_Excep_PERIA_INTA248(void) __attribute__ ((interrupt, weak));

// PERIA INTA249
void INT_Excep_PERIA_INTA249(void) __attribute__ ((interrupt, weak));

// PERIA INTA250
void INT_Excep_PERIA_INTA250(void) __attribute__ ((interrupt, weak));

// PERIA INTA251
void INT_Excep_PERIA_INTA251(void) __attribute__ ((interrupt, weak));

// PERIA INTA252
void INT_Excep_PERIA_INTA252(void) __attribute__ ((interrupt, weak));

// PERIA INTA253
void INT_Excep_PERIA_INTA253(void) __attribute__ ((interrupt, weak));

// PERIA INTA254
void INT_Excep_PERIA_INTA254(void) __attribute__ ((interrupt, weak));

// PERIA INTA255
void INT_Excep_PERIA_INTA255(void) __attribute__ ((interrupt, weak));

//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
extern void PowerON_Reset(void) __attribute__ ((interrupt, weak));
//;<<VECTOR DATA END (POWER ON RESET)>>

#endif
