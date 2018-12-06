#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"
#include <string.h>

#define RST_OUTPUT 0 //H L C T 8 NULL

char Switches_Process(char curr_state){
  //char tmp = RST_OUTPUT;
  //char tmp = curr_state;
  if (!(P5IN & BUTTON1)){//button 1 is on the right
    //what to do with button 1
    P1OUT &= ~GRN_LED;
    return 1;    
  }

  if (!(P5IN & BUTTON2)){//button 2 is on the left
    //what to do with button 2
    P1OUT &= ~GRN_LED;
    return 2;
  }
  
  return 0;// if no buttons pressed return null
}