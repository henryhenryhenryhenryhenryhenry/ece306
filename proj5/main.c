//------------------------------------------------------------------------------
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  henry lindbo
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
  Init_Wheels();
  // Place the contents of what you want on the display, in between the quotes
  // Limited to 10 characters per line
  //
  
  strcpy(display_line[LINE_0TH], " hdlindbo ");
  update_string(display_line[LINE_0TH], LINE_0TH);
  strcpy(display_line[LINE_1ST], " waiting  ");
  update_string(display_line[LINE_1ST], LINE_1ST);
  strcpy(display_line[LINE_2ND], "project 5 ");
  update_string(display_line[LINE_3RD], LINE_3RD);
  enable_display_update();
  lcd_BIG_mid();
  
  button_pressed = 0;
  state_mchn_state = 0;
  new_state = 0;
  done = 0;
  //  Display_Update(3,1,0,0);
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    Display_Process();
    //Switches_Process();
    
    if( new_state == 1 && done == 0){
      
      switch(state_mchn_state){
      case 0://start
        wheels_off();
        strcpy(display_line[LINE_1ST], " waiting  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 2://move fwd one sec
        wheels_off();
        move_fwd();
        strcpy(display_line[LINE_1ST], "moving fwd");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 4://stop one sec
        wheels_off();
        strcpy(display_line[LINE_1ST], " waiting  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 6://move rev two sec
        wheels_off();
        move_rev();
        strcpy(display_line[LINE_1ST], "moving rev");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 10://stop one sec
        wheels_off();
        strcpy(display_line[LINE_1ST], " waiting  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 12://move fwd one sec
        wheels_off();
        move_fwd();
        strcpy(display_line[LINE_1ST], "moving fwd");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 14://stop one sec
        wheels_off();
        strcpy(display_line[LINE_1ST], " waiting  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 16://spin right three sec
        wheels_off();
        spin_right();
        strcpy(display_line[LINE_1ST], "spin right");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 22://stop two sec
        wheels_off();
        strcpy(display_line[LINE_1ST], " waiting  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 26://spin left three sec
        wheels_off();
        spin_left();
        strcpy(display_line[LINE_1ST], "spin left ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 30://stop two sec
        wheels_off();
        strcpy(display_line[LINE_1ST], " waiting  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      case 32:
        wheels_off();
        done = 1;
        strcpy(display_line[LINE_1ST], "   done   ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        break;
      default:
        //wheels_off();
        break;
      }
      new_state = 0;
    }
  }
}

