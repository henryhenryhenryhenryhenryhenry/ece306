#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"
#include <string.h>

#define RST_OUTPUT 0 //H L C T 8 NULL

void Switches_Process(){
  //char tmp = RST_OUTPUT;
  //char tmp = curr_state;
  if (!(P5IN & BUTTON1)){//button 1 is on the right
    //what to do with button 1
    P1OUT ^= RED_LED;
    strcpy(display_line[LINE_1ST], "  SMCLK  ");
    update_string(display_line[LINE_1ST], LINE_1ST);
    
    Init_Port3(P3_SMCLK);//sends 0x01
    //return 1;    
  }

  if (!(P5IN & BUTTON2)){//button 2 is on the left
    //what to do with button 2
    P1OUT ^= GRN_LED;
    strcpy(display_line[LINE_1ST], "L_REVERSE ");
    update_string(display_line[LINE_1ST], LINE_1ST);
    
    Init_Port3(P3_L_REVERSE);//sends 0x00
    //return 2;
  }
  
  //return 0;// if no buttons pressed return null
}