//------------------------------
//file name:   init.c
//description: initializes everything on the msp430 so that main can run
//author:      henry lindbo 9/26/18
//------------------------------



#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"

// Global Variables
volatile char slow_input_down;
//extern char display_line[4][11];
//extern char *display[4];
unsigned char display_mode;
//extern volatile unsigned char display_changed;
//extern volatile unsigned char update_display;
//extern volatile unsigned int update_display_count;
//extern volatile unsigned int Time_Sequence;
//extern volatile char one_time;
unsigned int test_value;
char pwm_state;
char chosen_direction;
char change;

void Init_Conditions(void){
//------------------------------------------------------------------------------
  int i;

  for(i=0;i<11;i++){
    display_line[0][i] = RESET_STATE;
    display_line[1][i] = RESET_STATE;
    display_line[2][i] = RESET_STATE;
    display_line[3][i] = RESET_STATE;
  }
  display_line[0][10] = 0;
  display_line[1][10] = 0;
  display_line[2][10] = 0;
  display_line[3][10] = 0;

  display[0] = &display_line[0][0];
  display[1] = &display_line[1][0];
  display[2] = &display_line[2][0];
  display[3] = &display_line[3][0];
  update_display = 0;
  update_display_count = 0;
  pwm_state = PORTS;
// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}