//------------------------------
//file name:   shapes.c
//description: takes care of some of the shap moving functions
//author:      henry lindbo 10/7/18
//------------------------------



#include "macros.h"
#include "init.h"
#include "msp430.h"
#include "functions.h"
#include "ports.h"
#include <string.h>


#define R_WHEEL_ON    7
#define L_WHEEL_ON    9

#define R_WHEEL_CCW     1
#define L_WHEEL_CCW     9


#define R_WHEEL_CW     9
#define L_WHEEL_CW     1

void StopWheels(){
  P3OUT &= ~R_FORWARD;
  P3OUT &= ~L_FORWARD;
}

void Run_Line(unsigned int time){
  //
  if(time < R_WHEEL_ON){
    P3OUT |= R_FORWARD;
  }else{
    P3OUT &= ~R_FORWARD;
  }
  
  if(time < L_WHEEL_ON){
    P3OUT |= L_FORWARD;
  }else{
    P3OUT &= ~L_FORWARD;
  }
}

void Run_Circle(unsigned int time){
  //
  if(time < R_WHEEL_CCW){
    P3OUT |= R_FORWARD;
  }else{
    P3OUT &= ~R_FORWARD;
  }
  
  if(time < L_WHEEL_CCW){
    P3OUT |= L_FORWARD;
  }else{
    P3OUT &= ~L_FORWARD;
  }
}

void Run_RCircle(unsigned int time){
  //
  if(time < R_WHEEL_CW){
    P3OUT |= R_FORWARD;
  }else{
    P3OUT &= ~R_FORWARD;
  }
  
  if(time < L_WHEEL_CW){
    P3OUT |= L_FORWARD;
  }else{
    P3OUT &= ~L_FORWARD;
  }
}

void Turn_Left(unsigned int time){
  //
  P3OUT |= R_FORWARD;
  P3OUT &= ~L_FORWARD;
}

void Turn_Right(unsigned int time){
  //
}


void disp_shape(char state){
  switch(state){
    case 'H':
        strcpy(display_line[LINE_1ST], "hold still");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    case 'L':
        strcpy(display_line[LINE_1ST], "line      ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    case 'C':
        strcpy(display_line[LINE_1ST], "circle    ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    case '8':
        strcpy(display_line[LINE_1ST], "figure 8  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    case 'T':
        strcpy(display_line[LINE_1ST], "triangle  ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    case 'R':
        strcpy(display_line[LINE_1ST], "ready     ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    default:
        strcpy(display_line[LINE_1ST], "waiting   ");
        update_string(display_line[LINE_1ST], LINE_1ST);
        display_changed = ALWAYS;
        break;
    }
  
  
}

//runs the shape given to it
//state will be L C 8 T H or NULL
//time will be from 0 to 99
void Run_Shape(char state, unsigned int time){
  //disp_shape(state);
  switch(state){
  case 'H':
    //hold still
    StopWheels();
    break;
  case 'R':
    //hold still
    StopWheels();
    break;
  case 'L':
    //do line
    Run_Line(time%10);
    break;
  case 't':
    //turn
    //Turn_Left(time%10);
    //doesn't work for some reason
  case 'C':
    //do CCW circle
    Run_Circle(time%10);
    break;
  case 'c':
    //do CW circle
    Run_RCircle(time%10);
    break;
  case 'T':
    //do triangle
    //should not be used
    break;
  case '8':
    //do fig 8
    //should not be used
    break;
  default:
    //hold still
    StopWheels();
    break;
  }
  
}