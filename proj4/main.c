//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson/henry lindbo
//  9/26/18
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"
#include "init.h"
#include "led.h"
#include "ports.h"

void circle(void);
void fig8(void);
void triangle(void);

unsigned int my_time;
unsigned int old_time;
unsigned int temp_time;
char enable_DL;
char shape_state = 0; //H C T 8 R NULL
char command = 0; //same options

unsigned int butt1presses = 0;
unsigned int butt2presses = 0;
char newButtPress = 0;

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//
//------------------------------------------------------------------------------
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  //Init_Ports();
  PM5CTL0 &= ~LOCKLPM5;
  Init_Ports();                        // Initialize Ports
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[LINE_0TH], " hdlindbo ");
  update_string(display_line[LINE_0TH], LINE_0TH);
  strcpy(display_line[LINE_1ST], "#200140104");
  update_string(display_line[LINE_1ST], LINE_1ST);
  strcpy(display_line[LINE_2ND], "  ECE306  ");
  update_string(display_line[LINE_3RD], LINE_3RD);
  enable_display_update();
  
//  Display_Update(3,1,0,0);

  //enable_DL = 1;
  lcd_BIG_mid();
  //lcd_4line();
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    /*switch(Time_Sequence){
      case TIME_A:                        //
        if(one_time){
          Init_LEDs();
          lcd_BIG_mid();
          display_changed = ALWAYS;
          one_time = RESET_STATE;
        }
        Time_Sequence = RESET_STATE;             //
        break;
      case TIME_B:                        //
        if(one_time){
          P1OUT |= GRN_LED;            // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;
      case TIME_C:                         //
        if(one_time){
          P1OUT |= RED_LED;            // Change State of LED 4
          P1OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;
      case TIME_D:                         //
        if(one_time){
          lcd_4line();
          P1OUT |= GRN_LED;            // Change State of LED 5
          display_changed = ALWAYS;
          one_time = RESET_STATE;
        }
        break;
      case  TIME_E:                        //
        if(one_time){
          P1OUT &= ~RED_LED;           // Change State of LED 4
          P1OUT &= ~GRN_LED;           // Change State of LED 5
          one_time = RESET_STATE;
        }
        break;                         //
      default: break;
    }*/
    
    
    
    
    Display_Process();
    //Switches_Process();
    
    
    //process button input -----------------------------------------------------
    if((shape_state == 'R')||(shape_state == 0)){
      command = Switches_Process(0);
      switch(command){
      case 0:
        newButtPress = 0;
        break;
      case 1:
        newButtPress = 1;
        butt1presses++;
        break;
      case 2:
        newButtPress = 1;
        butt2presses++;
        break;
      default:
        break;
      }
    }
    
    //figure out shape to run --------------------------------------------------
    if(((shape_state == 'R')||(shape_state == 0))&& newButtPress){
      newButtPress = 0;
      my_time = 0;
      switch(butt1presses){
      case 0:
        //do nothing
        break;
      case 1:
        shape_state = 'C';
        break;
      case 2:
        shape_state = '8';
        break;
      case 3:
        shape_state = 'T';
        break;
      case 4:
        butt1presses = 0;
        break;
      default:
        butt1presses = 0;
        break;
      }
    }
    
    
    //act out the shape --------------------------------------------------------
    disp_shape(shape_state);
    switch(shape_state){
    case 'C':
      circle();
      break;
    case '8':
      fig8();
      break;
    case 'T':
      triangle();
      break;
    case 'R':
      P1OUT |= GRN_LED;
      StopWheels();
      break;
    default: break;
    }
    
    
    //Run_Shape(shape_state, my_time);
    
    //timer stuff --------------------------------------------------------------
    temp_time = Time_Sequence;
    if(temp_time != old_time){
      old_time = Time_Sequence;
      my_time++;
    }
    /*
    if(my_time >= 100){
      my_time = 0;
    }*/
    
    if(my_time%10 > 5){
      P1OUT &= ~RED_LED;
    }else{
      P1OUT |= RED_LED;
    }
    
  }
}

void circle(){
  if(my_time < GTFO){
    //hold still a bit
    Run_Shape('H', my_time);
  }else if((my_time < 130 + GTFO)&&(my_time >= GTFO)){
    Run_Shape('C', my_time);
  }else{
    my_time = 0;
    shape_state = 'R';
  }
}

void fig8(){
  if(my_time < GTFO){
    //hold still a bit
    Run_Shape('H', my_time);
  }else if((my_time < FIG8_TM  + GTFO)&&(my_time >= GTFO)){
    Run_Shape('C', my_time);
  }else if((my_time >= FIG8_TM + GTFO)&&(my_time < 2*FIG8_TM + GTFO)){
    Run_Shape('c', my_time);
  }else if((my_time >= 2*FIG8_TM + GTFO)&&(my_time < 3*FIG8_TM + GTFO)){
    Run_Shape('C', my_time);
  }else if((my_time >= 3*FIG8_TM + GTFO)&&(my_time < 4*FIG8_TM + GTFO)){
    Run_Shape('c', my_time);
  }else{
    my_time = 0;
    shape_state = 'R';
  }
}

void triangle(){
  if(my_time < GTFO){
    //hold still a bit
    Run_Shape('H', my_time);
  }else if((my_time < TRI_MV_TM + GTFO) && (my_time >= GTFO)){
    //straight 1
    Run_Shape('L', my_time);
  }else if((my_time >= TRI_MV_TM + GTFO)&&(my_time < TRI_MV_TM + TRI_TN_TM + GTFO)){
    //turn
    P3OUT |= R_FORWARD;
    P3OUT &= ~L_FORWARD;
  }else if((my_time >= TRI_MV_TM + TRI_TN_TM + GTFO)&&(my_time < 2*TRI_MV_TM + TRI_TN_TM + GTFO)){
    //straight 2
    Run_Shape('L', my_time);
  }else if((my_time >= 2*TRI_MV_TM + TRI_TN_TM + GTFO)&&(my_time < 2*TRI_MV_TM + 2*TRI_TN_TM + GTFO)){
    //turn
    P3OUT |= R_FORWARD;
    P3OUT &= ~L_FORWARD;
  }else if((my_time >= 2*TRI_MV_TM + 2*TRI_TN_TM + GTFO)&&(my_time < 3*TRI_MV_TM + 2*TRI_TN_TM + GTFO)){
    //straight 3
    Run_Shape('L', my_time);
  }else if((my_time >= 3*TRI_MV_TM + 2*TRI_TN_TM + GTFO)&&(my_time < 3*TRI_MV_TM + 3*TRI_TN_TM + GTFO)){
    //turn
    P3OUT |= R_FORWARD;
    P3OUT &= ~L_FORWARD;
  }else if((my_time >= 3*TRI_MV_TM + 3*TRI_TN_TM + GTFO)&&(my_time < 4*TRI_MV_TM + 3*TRI_TN_TM + GTFO)){
    //straight 1
    Run_Shape('L', my_time);
  }else if((my_time >= 4*TRI_MV_TM + 3*TRI_TN_TM + GTFO)&&(my_time < 4*TRI_MV_TM + 4*TRI_TN_TM + GTFO)){
    //turn
    P3OUT |= R_FORWARD;
    P3OUT &= ~L_FORWARD;
  }else if((my_time >= 4*TRI_MV_TM + 4*TRI_TN_TM + GTFO)&&(my_time < 5*TRI_MV_TM + 4*TRI_TN_TM + GTFO)){
    //straight 2
    Run_Shape('L', my_time);
  }else if((my_time >= 5*TRI_MV_TM + 4*TRI_TN_TM + GTFO)&&(my_time < 5*TRI_MV_TM + 5*TRI_TN_TM + GTFO)){
    //turn
    P3OUT |= R_FORWARD;
    P3OUT &= ~L_FORWARD;
  }else if((my_time >= 5*TRI_MV_TM + 5*TRI_TN_TM + GTFO)&&(my_time < 6*TRI_MV_TM + 5*TRI_TN_TM + GTFO)){
    //straight 3
    Run_Shape('L', my_time);
  }else if((my_time >= 6*TRI_MV_TM + 5*TRI_TN_TM + GTFO)&&(my_time < 6*TRI_MV_TM + 6*TRI_TN_TM + GTFO)){
    //turn
    P3OUT |= R_FORWARD;
    P3OUT &= ~L_FORWARD;
  }else{
    my_time = 0;
    shape_state = 'R';
  }
    
}



