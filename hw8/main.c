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
  volatile unsigned int total_time_running = RST;//time running in ms
  armed = RST;
  
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
  Init_ADC();
  init_serial_UCA3(1152);//115200
  // Place the contents of what you want on the display, in between the quotes
  // Limited to 10 characters per line
  //
  
  strcpy(display_line[LINE_0TH], " hdlindbo ");
  update_string(display_line[LINE_0TH], LINE_0TH);
  
  strcpy(display_line[LINE_1ST], "homework 8");
  update_string(display_line[LINE_1ST], LINE_1ST);
  
  strcpy(display_line[LINE_2ND], "  serial  ");
  update_string(display_line[LINE_2ND], LINE_2ND);
  
  strcpy(display_line[LINE_3RD], "  comms   ");
  update_string(display_line[LINE_3RD], LINE_3RD);
  
  enable_display_update();
  
  update_display = ALWAYS;
  display_changed = ALWAYS;
  
  //lcd_BIG_mid();
  
  button_pressed = RESET_STATE;
  state_mchn_state = RESET_STATE;
  new_state = RESET_STATE;
  done = RESET_STATE;
  
  linefollow_state = 0;
  //0: spin and calibrate
  //1: go fwd untill line
  //2: spin until on line
  //3: follow line
  //4: spin off line
  //5: go fwd to center of circle
  //6: stop
  
  unsigned int R_det_max = ADC_Right_Detector;
  unsigned int R_det_min = ADC_Right_Detector;
  unsigned int L_det_max = ADC_Left_Detector;
  unsigned int L_det_min = ADC_Left_Detector;
  
  //  Display_Update(3,1,0,0);
  
  UCA3_index = 0;
  //UCA3IE |= UCTXIE; //enable uca3 tx interrupt
  UCA3TXBUF = serial_test[0];
  
  unsigned int hw8_state = 0;
  
  //------------------------------------------------------------------------------
  // Begining of the "While" Operating System
  //------------------------------------------------------------------------------
  while(ALWAYS) {                      // Can the Operating system run
    
    /*
    if( ADC_Thumb_raw && ADC_Right_Detector_raw && ADC_Left_Detector_raw){
    ADC_Thumb = ADC_Thumb_raw;
    ADC_Right_Detector = ADC_Right_Detector_raw;
    ADC_Left_Detector = ADC_Left_Detector_raw;
  }
    */
    
    Display_Process();
    
    //display_values();
    
    //proj7();
    
    switch(hw8_state){
    case 0://splash info
      max_state_mchn_state = 10+1;
      if(state_mchn_state >=10){
        state_mchn_state = RST;
        hw8_state = 1;
      }else{
        hw8_state = 0;
      }
      break;
    case 1://baud 115200
      
      max_state_mchn_state = 2+1;
      if(state_mchn_state >=2){
        state_mchn_state = RST;
        hw8_state = 2;
      }else{
        strcpy(display_line[LINE_0TH], "          ");
        update_string(display_line[LINE_0TH], LINE_0TH);
        strcpy(display_line[LINE_1ST], "          ");
        update_string(display_line[LINE_1ST], LINE_1ST); 
        strcpy(display_line[LINE_2ND], "baudrate: ");
        update_string(display_line[LINE_2ND], LINE_2ND);
        strcpy(display_line[LINE_3RD], "115200 Hz ");
        update_string(display_line[LINE_3RD], LINE_3RD);
        
        hw8_state = 1;
      }
      break;
    case 2:
      strcpy(display_line[LINE_0TH], "recieved: ");
      update_string(display_line[LINE_0TH], LINE_0TH);
      
      UCA3IE |= UCTXIE; //enable uca3 tx interrupt
      
      //rx_str = uca3_rx_buff;
      //strcpy(rx_str, uca3_rx_buff);

      for(int j=0;j<10;j++){
        rx_str[j] = uca3_rx_buff[j];
      }
      
      strcpy(display_line[LINE_1ST], rx_str);
      update_string(display_line[LINE_1ST], LINE_1ST);
      
      if(!(P5IN & BUTTON2)){// pressed button 2 - switch to 460800 baud
        hw8_state = 3;
        init_serial_UCA3(4608);
        state_mchn_state = RST;
      }else if(!(P5IN & BUTTON1)){
        hw8_state = 1;
        init_serial_UCA3(1152);
        state_mchn_state = RST;
      }
      
      break;
    case 3://baud 460800
      
      max_state_mchn_state = 2+1;
      if(state_mchn_state >=2){
        state_mchn_state = RST;
        hw8_state = 4;
      }else{
        strcpy(display_line[LINE_0TH], "          ");
        update_string(display_line[LINE_0TH], LINE_0TH);
        strcpy(display_line[LINE_1ST], "          ");
        update_string(display_line[LINE_1ST], LINE_1ST); 
        strcpy(display_line[LINE_2ND], "baudrate: ");
        update_string(display_line[LINE_2ND], LINE_2ND);
        strcpy(display_line[LINE_3RD], "460800 Hz ");
        update_string(display_line[LINE_3RD], LINE_3RD);
        
        hw8_state = 3;
      }
      break;
    case 4:
      strcpy(display_line[LINE_0TH], "recieved: ");
      update_string(display_line[LINE_0TH], LINE_0TH);
      
      UCA3IE |= UCTXIE; //enable uca3 tx interrupt
      
      //rx_str = uca3_rx_buff;
      //strcpy(rx_str, uca3_rx_buff);

      for(int j=0;j<10;j++){
        rx_str[j] = uca3_rx_buff[j];
      }
      
      strcpy(display_line[LINE_1ST], rx_str);
      update_string(display_line[LINE_1ST], LINE_1ST);
      
      if(!(P5IN & BUTTON1)){// pressed button 1 - switch to 115200 baud
        hw8_state = 1;
        init_serial_UCA3(1152);
        state_mchn_state = RST;
      }else if(!(P5IN & BUTTON2)){
        hw8_state = 3;
        init_serial_UCA3(4608);
        state_mchn_state = RST;
      }
      break;
    default:
      
      break;      
    }
    
    
  }
}
