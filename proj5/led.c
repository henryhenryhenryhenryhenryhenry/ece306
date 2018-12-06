//------------------------------
//file name:   led.c
//description: takes care of blinking the leds on the fram board
//author:      henry lindbo 9/26/18
//------------------------------



#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"


void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT &= ~RED_LED;
  P1OUT &= ~GRN_LED;
//------------------------------------------------------------------------------
}