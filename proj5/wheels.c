//
//
//

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"
#include "init.h"
#include "led.h"
#include "timers.h"
#include "ports.h"


//wheels off --------------------------------------
void wheel_LR_off(void){
  LEFT_REVERSE_SPEED = WHEEL_OFF;
}

void wheel_LF_off(void){
  LEFT_FORWARD_SPEED = WHEEL_OFF;
}

void wheel_RR_off(void){
  RIGHT_REVERSE_SPEED = WHEEL_OFF;
}

void wheel_RF_off(void){
  RIGHT_FORWARD_SPEED = WHEEL_OFF;
}

//wheels on  ---------------------------------------
void wheel_LR_on(void){
  wheel_LF_off();
  LEFT_REVERSE_SPEED = L_WHEEL_REV;
}

void wheel_LF_on(void){
  wheel_LR_off();
  LEFT_FORWARD_SPEED = L_WHEEL_FWD;
}

void wheel_RR_on(void){
  wheel_RF_off();
  RIGHT_REVERSE_SPEED = R_WHEEL_REV;
}

void wheel_RF_on(void){
  wheel_RR_off();
  RIGHT_FORWARD_SPEED = R_WHEEL_FWD;
}


//control -----------------------------------------
void wheels_off(void){
  wheel_LR_off();
  wheel_LF_off();
  wheel_RR_off();
  wheel_RF_off();
}

void Init_Wheels(void){
  wheels_off();
}

void spin_right(void){
  wheels_off();
  wheel_RF_on();
  wheel_LR_on();
}

void spin_left(void){
  wheels_off();
  wheel_RR_on();
  wheel_LF_on();
}

void move_fwd(void){
  wheels_off();
  wheel_RF_on();
  wheel_LF_on();
}

void move_rev(void){
  wheels_off();
  wheel_RR_on();
  wheel_LR_on();
}






