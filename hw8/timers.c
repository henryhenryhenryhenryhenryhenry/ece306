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

void Init_Timer_B0(void){
  //SMCLK source, up count mode, PWM right side
  //TB0.3 : P3.4 L_REVERSE
  //TB0.4 : P3.5 L_FORWARD
  //TB0.1 : P3.6 R_REVERSE
  //TB0.2 : P3.7 R_FORWARD
  
  TB0CTL = TBSSEL__SMCLK;
  TB0CTL |= MC__UP;
  TB0CTL |= TBCLR;
  
  TB0CCR0 = WHEEL_PERIOD;
  
  TB0CCTL3 = OUTMOD_7;
  LEFT_REVERSE_SPEED = WHEEL_OFF;
  
  TB0CCTL4 = OUTMOD_7;
  LEFT_FORWARD_SPEED = WHEEL_OFF;
  
  TB0CCTL5 = OUTMOD_7;
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
  
  TB0CCTL6 = OUTMOD_7;
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
  
  
}

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
  TA1CTL |= ID__8;               //divide clock by 8
  
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

void Init_Timer_A2(void){
  TA2CTL = TASSEL__SMCLK;        //smclk source
  TA2CTL |= TACLR;               //resets TA0R, clock divider, count direction
  TA2CTL |= MC__CONTINUOUS;       //continuous up (why is there a spelling mistake in the #define?)
  TA2CTL |= ID__2;               //divide clock by 2
  
  TA2EX0 = TAIDEX__8;            //divide clock by another 8
  
  TA2CCR0 = TA2CCR0_INTERVAL;    //ccr0
  TA2CCTL0 |= CCIE;              //ccr0 enable interupt 
  
  //TA2CCR1 = TA2CCR1_INTERVAL;    //ccr1
  //TA2CCTL1 |= CCIE;              //ccr1 enable interupt
  //TA2CCTL1 &= ~CCIE; 
  
  //TA2CCR2 = TA2CCR2_INTERVAL;    //ccr2
  //TA2CCTL2 |= CCIE;              //ccr2 enable interupt
  
  TA2CTL &= ~TAIE;               //disable overflow interrupt
  TA2CTL &= ~TAIFG;              //clear overflow interrupt flag
}


void Init_Timers(void){
  Init_Timer_A0();
  Init_Timer_A1();
  Init_Timer_A2();
  Init_Timer_B0();
  
  
}