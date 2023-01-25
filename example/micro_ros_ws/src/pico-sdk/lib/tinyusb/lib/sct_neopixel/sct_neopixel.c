/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Greg Steiert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "sct_neopixel.h"
#include "board.h"
#include "fsl_device_registers.h"
#include "fsl_sctimer.h"


//--------------------------------------------------------------------+
// Variables
//--------------------------------------------------------------------+
uint32_t          *_sctpix_data[NEO_SCT_OUTPUTS];
uint32_t          _sctpix_size[NEO_SCT_OUTPUTS];
uint32_t          _sctpix_max_count = 0;
uint32_t          _sctpix_start = 23;
volatile uint32_t _sctpix_count = 0;
volatile bool     _sctpix_busy = false;
bool              _sctpix_syncUpdate = true;


//--------------------------------------------------------------------+
// Interrupt
//--------------------------------------------------------------------+
void sctpix_int_handler(void){
  uint32_t eventFlag = NEO_SCT->EVFLAG;
  if (eventFlag & (1 << NEO_EVENT_RESET)) {
    _sctpix_busy = false;
  } else if (eventFlag & (1 << NEO_EVENT_LAST)) {
    _sctpix_count += 1;
    if (_sctpix_count < _sctpix_max_count) {
      NEO_SCT->STATE = _sctpix_start; 
      if (_sctpix_count < _sctpix_size[0]) {
        NEO_SCT->EV[NEO_EVENT_CH_0].STATE = (~_sctpix_data[0][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[1]) {
        NEO_SCT->EV[NEO_EVENT_CH_1].STATE = (~_sctpix_data[1][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[2]) {
        NEO_SCT->EV[NEO_EVENT_CH_2].STATE = (~_sctpix_data[2][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[3]) {
        NEO_SCT->EV[NEO_EVENT_CH_3].STATE = (~_sctpix_data[3][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[4]) {
        NEO_SCT->EV[NEO_EVENT_CH_4].STATE = (~_sctpix_data[4][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[5]) {
        NEO_SCT->EV[NEO_EVENT_CH_5].STATE = (~_sctpix_data[5][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[6]) {
        NEO_SCT->EV[NEO_EVENT_CH_6].STATE = (~_sctpix_data[6][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[7]) {
        NEO_SCT->EV[NEO_EVENT_CH_7].STATE = (~_sctpix_data[7][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[8]) {
        NEO_SCT->EV[NEO_EVENT_CH_8].STATE = (~_sctpix_data[8][_sctpix_count]); }
      if (_sctpix_count < _sctpix_size[9]) {
        NEO_SCT->EV[NEO_EVENT_CH_9].STATE = (~_sctpix_data[9][_sctpix_count]); }
      NEO_SCT->CTRL = SCT_CTRL_CLRCTR_L_MASK;
    } else {
      NEO_SCT->CTRL = 0x0;    
    }
  }
  NEO_SCT->EVFLAG = eventFlag;
}

void SCT0_DriverIRQHandler(void){
  sctpix_int_handler();
  SDK_ISR_EXIT_BARRIER;
}

//--------------------------------------------------------------------+
// User Functions
//--------------------------------------------------------------------+
void sctpix_setPixel(uint32_t ch, uint32_t pixel, uint32_t color){
  if (ch < NEO_SCT_OUTPUTS) {
    if (pixel < _sctpix_size[ch]) {
      if (_sctpix_syncUpdate) {
        while (_sctpix_busy) { __NOP(); }
      }
      _sctpix_data[ch][pixel] = color;
    }
  }
}

void sctpix_show(void){
//  while (NEO_SCT->CTRL & SCT_CTRL_HALT_L_MASK);
  while (_sctpix_busy) {__NOP();}
  _sctpix_busy = true;
  _sctpix_count = 0;
  NEO_SCT->STATE = _sctpix_start; 
  if (_sctpix_size[0]) { NEO_SCT->EV[NEO_EVENT_CH_0].STATE = (~_sctpix_data[0][0]); }
  if (_sctpix_size[1]) { NEO_SCT->EV[NEO_EVENT_CH_1].STATE = (~_sctpix_data[1][0]); }
  if (_sctpix_size[2]) { NEO_SCT->EV[NEO_EVENT_CH_2].STATE = (~_sctpix_data[2][0]); }
  if (_sctpix_size[3]) { NEO_SCT->EV[NEO_EVENT_CH_3].STATE = (~_sctpix_data[3][0]); }
  if (_sctpix_size[4]) { NEO_SCT->EV[NEO_EVENT_CH_4].STATE = (~_sctpix_data[4][0]); }
  if (_sctpix_size[5]) { NEO_SCT->EV[NEO_EVENT_CH_5].STATE = (~_sctpix_data[5][0]); }
  if (_sctpix_size[6]) { NEO_SCT->EV[NEO_EVENT_CH_6].STATE = (~_sctpix_data[6][0]); }
  if (_sctpix_size[7]) { NEO_SCT->EV[NEO_EVENT_CH_7].STATE = (~_sctpix_data[7][0]); }
  if (_sctpix_size[8]) { NEO_SCT->EV[NEO_EVENT_CH_8].STATE = (~_sctpix_data[8][0]); }
  if (_sctpix_size[9]) { NEO_SCT->EV[NEO_EVENT_CH_9].STATE = (~_sctpix_data[9][0]); }
  NEO_SCT->CTRL = SCT_CTRL_CLRCTR_L_MASK;
}

bool sctpix_canShow(void) {
  return !_sctpix_busy;
}

void sctpix_addCh(uint32_t ch, uint32_t *data, uint32_t size) {
  if (ch < NEO_SCT_OUTPUTS) {
    _sctpix_data[ch] = data;
    _sctpix_size[ch] = size;
    if (size > _sctpix_max_count) {
      _sctpix_max_count = size;
    }
  }
}

void sctpix_rmCh(uint32_t ch){
  if (ch < NEO_SCT_OUTPUTS){
    // clear channel configuration
    _sctpix_data[ch] = NULL;
    _sctpix_size[ch] = 0;
    // recalculate max pixel count
    _sctpix_max_count = 0;
    for (uint32_t i = 0; i < NEO_SCT_OUTPUTS; i++){
      if (_sctpix_max_count < _sctpix_size[i]){
        _sctpix_max_count = _sctpix_size[i];
      }
    }
  }
}

void sctpix_init(uint32_t neoPixelType) {
  CLOCK_EnableClock(kCLOCK_Sct0);
  RESET_PeripheralReset(kSCT0_RST_SHIFT_RSTn);

// Set start state based on pixel type (TBD)
  _sctpix_start = 23;
  _sctpix_max_count = 0;
  _sctpix_syncUpdate = true;
  for (uint32_t i=0; i < NEO_SCT_OUTPUTS; i++) {
    _sctpix_data[i] = NULL;
    _sctpix_size[i] = 0;
  }

  NEO_SCT->CONFIG = (
    SCT_CONFIG_UNIFY(1) | 
    SCT_CONFIG_CLKMODE(kSCTIMER_System_ClockMode) | 
    SCT_CONFIG_NORELOAD_L(1) );
  NEO_SCT->CTRL = ( 
    SCT_CTRL_HALT_L(1) |
    SCT_CTRL_CLRCTR_L(1) );

  NEO_SCT->MATCH[NEO_MATCH_RISE] = NEO_COUNT_RISE;
  NEO_SCT->MATCH[NEO_MATCH_PERIOD] = NEO_COUNT_PERIOD;
  NEO_SCT->MATCH[NEO_MATCH_0] = NEO_COUNT_FALL0;
  NEO_SCT->MATCH[NEO_MATCH_1] = NEO_COUNT_FALL1;
  NEO_SCT->MATCH[NEO_MATCH_RESET] = NEO_COUNT_RESET;
  NEO_SCT->EV[NEO_EVENT_RISE].STATE = 0xFFFFFFFF;
  NEO_SCT->EV[NEO_EVENT_RISE].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_RISE) );
  NEO_SCT->EV[NEO_EVENT_CH_0].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_0].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_1].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_1].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_2].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_2].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_3].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_3].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_4].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_4].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_5].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_5].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_6].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_6].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_7].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_7].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_8].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_8].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_CH_9].STATE = 0xF0F0F0F0;
  NEO_SCT->EV[NEO_EVENT_CH_9].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_0) );
  NEO_SCT->EV[NEO_EVENT_FALL_1].STATE = 0xFFFFFFFF;
  NEO_SCT->EV[NEO_EVENT_FALL_1].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_1) );
  NEO_SCT->EV[NEO_EVENT_NEXT].STATE = 0xFFFFFFFE;
  NEO_SCT->EV[NEO_EVENT_NEXT].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_PERIOD) | 
    SCT_EV_CTRL_STATELD(0) | SCT_EV_CTRL_STATEV(31));
  NEO_SCT->EV[NEO_EVENT_LAST].STATE = 0x1;
  NEO_SCT->EV[NEO_EVENT_LAST].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_PERIOD) );
  NEO_SCT->EV[NEO_EVENT_RESET].STATE = 0xFFFFFFFF;
  NEO_SCT->EV[NEO_EVENT_RESET].CTRL = (
    kSCTIMER_MatchEventOnly | SCT_EV_CTRL_MATCHSEL(NEO_MATCH_RESET) );

  NEO_SCT->LIMIT = (1 << NEO_EVENT_NEXT) | (1 << NEO_EVENT_RESET);
  NEO_SCT->HALT = (1 << NEO_EVENT_LAST) | (1 << NEO_EVENT_RESET);
  NEO_SCT->START = 0x0;

  NEO_SCT->OUT[0].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[0].CLR = (1 << NEO_EVENT_CH_0) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[1].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[1].CLR = (1 << NEO_EVENT_CH_1) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[2].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[2].CLR = (1 << NEO_EVENT_CH_2) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[3].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[3].CLR = (1 << NEO_EVENT_CH_3) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[4].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[4].CLR = (1 << NEO_EVENT_CH_4) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[5].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[5].CLR = (1 << NEO_EVENT_CH_5) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[6].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[6].CLR = (1 << NEO_EVENT_CH_6) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[7].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[7].CLR = (1 << NEO_EVENT_CH_7) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[8].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[8].CLR = (1 << NEO_EVENT_CH_8) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  NEO_SCT->OUT[9].SET = (1 << NEO_EVENT_RISE);
  NEO_SCT->OUT[9].CLR = (1 << NEO_EVENT_CH_9) | (1 << NEO_EVENT_FALL_1) | (1 << NEO_EVENT_LAST);
  
  NEO_SCT->OUTPUT = 0x0;
  NEO_SCT->RES = SCT_RES_O6RES(0x2);
  NEO_SCT->EVEN = (1 << NEO_EVENT_LAST) | (1 << NEO_EVENT_RESET);
  NEO_SCT->EVFLAG = 0xFFFFFFFF;
  EnableIRQ(SCT0_IRQn);

}
