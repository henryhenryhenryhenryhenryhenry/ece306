//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Jim Carlson/henry lindbo
//  9/26/18
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"
#include "init.h"
#include "led.h"
#include "timers.h"
#include "ports.h"



/*
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x02) // GREEN LED 1

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x02) // GREEN LED 1
#define PORTS                (0x00) // PORTS
#define PWM_MODE             (0x01) // PWM_MODE
*/

/*
// Global Variables
volatile char slow_input_down;
extern char display_line[4][11];
extern char *display[4];
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
unsigned int test_value;
char pwm_state;
char chosen_direction;
char change;
*/



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
  strcpy(display_line[LINE_1ST], " button ? ");
  update_string(display_line[LINE_1ST], LINE_1ST);
  strcpy(display_line[LINE_2ND], "homework 6");
  update_string(display_line[LINE_3RD], LINE_3RD);
  enable_display_update();
  lcd_BIG_mid();
  
  button_pressed = 0;
//  Display_Update(3,1,0,0);

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    /*
    switch(Time_Sequence){
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
    }
    */
    Display_Process();
    //Switches_Process();
    
    
    switch(button_pressed){
    case BUTTON1PRESSED:
      strcpy(display_line[LINE_1ST], " button 1 ");
      update_string(display_line[LINE_1ST], LINE_1ST);
      break;
    case BUTTON2PRESSED:
      strcpy(display_line[LINE_1ST], " button 2 ");
      update_string(display_line[LINE_1ST], LINE_1ST);
      break;
    case RESET_STATE:
      strcpy(display_line[LINE_1ST], " no button");
      update_string(display_line[LINE_1ST], LINE_1ST);
      break;
    default:
      break;
    }

  }
}

