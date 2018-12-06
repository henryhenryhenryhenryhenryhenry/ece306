//------------------------------
//file name:   interupts_buttons.c
//description: processes button input via interrupts
//author:      henry lindbo 10/12/18
//------------------------------

#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"
#include "timers.h"
#include <string.h>



volatile unsigned int button_pressed;
volatile unsigned int button_debounce;

#pragma vector = PORT5_VECTOR
__interrupt void BUTTON_interrupt(void){
  //button1
  if(P5IFG & BUTTON1){
    //P5OUT &= ~LCD_BACKLIGHT;
    P1OUT &= ~RED_LED;
    button_pressed = BUTTON1PRESSED;
    button_debounce = BUTTON1PRESSED;
    P5IE &= ~BUTTON1;
    
    //TA0CTL &= ~TAIE;
    //TA0CCTL0 &= ~CCIE;
  }
  //button2
  if(P5IFG & BUTTON2){
    //P5OUT |= LCD_BACKLIGHT;
    P1OUT &= ~RED_LED;
    button_pressed = BUTTON2PRESSED;
    button_debounce = BUTTON2PRESSED;
    P5IE &= ~BUTTON2;
    
    //TA0CTL &= ~TAIE;
    //TA0CCTL0 |= CCIE;
  }
  
  //enable timer interrupt for debounce
  TA1CTL &= ~TAIFG;
  TA1CCTL0 |= CCIE;
  //TA0CCTL0 &= ~CCIE;
}






