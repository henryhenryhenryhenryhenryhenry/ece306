//------------------------------
//file name:   timers.c
//description: congigures the timers for the project
//author:      henry lindbo 10/12/18
//------------------------------

#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"
#include "timers.h"



void Init_Timer_A0(void){
  TA0CTL = TASSEL__SMCLK;        //smclk source
  TA0CTL |= TACLR;               //resets TA0R, clock divider, count direction
  TA0CTL |= MC__CONTINUOUS;       //continuous up (why is there a spelling mistake in the #define?)
  TA0CTL |= ID__2;               //divide clock by 2
  
  TA0EX0 = TAIDEX__8;            //divide clock by another 8
  
  TA0CCR0 = TA0CCR0_INTERVAL;    //ccr0
  TA0CCTL0 |= CCIE;              //ccr0 enable interupt
  
  //TA0CCR1 = TA0CCR1_INTERVAL;    //ccr1
  //TA0CCTL1 |= CCIE;              //ccr1 enable interupt
  //TA0CCTL1 &= ~CCIE; 
  
  //TA0CCR2 = TA0CCR2_INTERVAL;    //ccr2
  //TA0CCTL2 |= CCIE;              //ccr2 enable interupt
  
  TA0CTL &= ~TAIE;               //disable overflow interrupt
  TA0CTL &= ~TAIFG;              //clear overflow interrupt flag
}

void Init_Timer_A1(void){
  TA1CTL = TASSEL__SMCLK;        //smclk source
  TA1CTL |= TACLR;               //resets TA0R, clock divider, count direction
  TA1CTL |= MC__CONTINUOUS;       //continuous up (why is there a spelling mistake in the #define?)
  TA1CTL |= ID__8;               //divide clock by 2
  
  TA1EX0 = TAIDEX__8;            //divide clock by another 8
  
  TA1CCR0 = TA1CCR0_INTERVAL;    //ccr0
  //TA1CCTL0 |= CCIE;              //ccr0 enable interupt //disabled b/c the buttons will turn it on
  
  //TA1CCR1 = TA1CCR1_INTERVAL;    //ccr1
  //TA1CCTL1 |= CCIE;              //ccr1 enable interupt
  //TA1CCTL1 &= ~CCIE; 
  
  //TA1CCR2 = TA0CCR2_INTERVAL;    //ccr2
  //TA1CCTL2 |= CCIE;              //ccr2 enable interupt
  
  TA1CTL &= ~TAIE;               //disable overflow interrupt
  TA1CTL &= ~TAIFG;              //clear overflow interrupt flag
}


void Init_Timers(void){
  Init_Timer_A0();
  Init_Timer_A1();
  
  
  
}