//------------------------------
//file name:   ports.c
//description: sets up the ports for the msp430
//author:      henry lindbo 9/26/18
//------------------------------



#include "macros.h"
#include "ports.h"
#include "msp430.h"
#include "init.h"
#include "functions.h"


//init ports
//
void Init_Ports(){
  char port_type = P3_L_REVERSE; //P3_SMCLK or P3_L_REVERSE
  
  Init_Port1();
  Init_Port2();
  Init_Port3(port_type);
  Init_Port4();
  Init_Port5();
  Init_Port6();
  Init_Port7();
  Init_Port8();
  Init_PortJ();
}

//init port 1
//1.0 ledred gpio out
//1.1 ledgrn gpio in
//1.2 thumbwheel analog2
//1.3 testprobe gpio out
//1.4 rightdetector analog4
//1.5 leftdetector analog5
//1.6 SD_MOSI ucb0simo
//1.7 SD_MISO ucb0somi
void Init_Port1(){
  //config port 1
  P1SEL0 = RESET_STATE;
  P1SEL1 = RESET_STATE;
  P1DIR  = RESET_STATE;
  P1OUT = RESET_STATE;
  //P1_0
  P1SEL0 &= ~RED_LED;
  P1SEL1 &= ~RED_LED;
  P1OUT |= RED_LED;
  P1DIR |= RED_LED;
  //P1_1
  P1SEL0 &= ~GRN_LED;
  P1SEL1 &= ~GRN_LED;
  P1OUT |= GRN_LED;
  P1DIR |= GRN_LED;
  //P1_2
  P1SEL0 |= V_THUMB;
  P1SEL1 |= V_THUMB;
  //P1_3
  P1SEL0 &= ~TEST_PROBE;
  P1SEL1 &= ~TEST_PROBE;
  P1OUT &= ~TEST_PROBE;
  P1DIR |= TEST_PROBE;
  //P1_4
  P1SEL0 |= V_DETECT_R;
  P1SEL1 |= V_DETECT_R;
  //P1_5
  P1SEL0 |= V_DETECT_L;
  P1SEL1 |= V_DETECT_L;
  //P1_6
  P1SEL0 &= ~SD_UCB0SIMO;
  P1SEL1 |= SD_UCB0SIMO;
  //P1_7
  P1SEL0 &= ~SD_UCB0SOMI;
  P1SEL1 |= SD_UCB0SOMI;
}

//init port 2
//2.0 UCA0TXD
//2.1 UCA0RXD
//2.2 SD_SPICLK ucb0clk
//2.3 unused gpio in
//2.4 unused gpio in
//2.5 UCA1TXD
//2.6 UCA1RXD
//2.7 unused gpio in
void Init_Port2(){
  P2SEL0 = RESET_STATE;
  P2SEL1 = RESET_STATE;
  P2DIR = RESET_STATE;
  //P2_0
  P2SEL0 &= ~UCA0TXD;
  P2SEL1 |= UCA0TXD;
  //P2_1
  P2SEL0 &= ~UCA0RXD;
  P2SEL1 |= UCA0RXD;
  //P2_2
  P2SEL0 &= ~UCB0CLK;
  P2SEL1 |= UCB0CLK;
  //P2_3
  P2SEL0 &= ~P2_3;
  P2SEL1 &= ~P2_3;
  P2DIR &= ~P2_3;
  //P2_4
  P2SEL0 &= ~P2_4;
  P2SEL1 &= ~P2_4;
  P2DIR &= ~P2_4;
  //P2_5
  P2SEL0 &= ~UCA1TXD;
  P2SEL1 |= UCA1TXD;
  //P2_6
  P2SEL0 &= ~UCA1RXD;
  P2SEL1 |= UCA1RXD;
  //P2_7
  P2SEL0 &= ~P2_7;
  P2SEL1 &= ~P2_7;
  P2DIR &= ~P2_7;
}

//init port 3
//3.0 iotrst gpio out
//3.1 iotprogmode gpio in
//3.2 iotlink gpio in
//3.3 iotprogsel gpio in
//3.4 lrev gpio out 
//3.5 lfwd gpio out
//3.6 rrev gpio out
//3.7 rfwd gpio out
void Init_Port3(char port_type){
  P3DIR = 0xFF;
  P3OUT = RESET_STATE;
  P3SEL0 = RESET_STATE;
  P3SEL1 = RESET_STATE;
  //P3_0
  P3SEL0 &= ~IOT_RST;
  P3SEL1 &= ~IOT_RST;
  P3OUT &= ~IOT_RST;
  P3DIR |= IOT_RST;
  //P3_1
  P3SEL0 &= ~IOT_PROG_MODE;
  P3SEL1 &= ~IOT_PROG_MODE;
  P3DIR &= ~IOT_PROG_MODE;
  //P3_2
  P3SEL0 &= ~IOT_LINK;
  P3SEL1 &= ~IOT_LINK;
  P3DIR &= ~IOT_LINK;
  //P3_3
  P3SEL0 &= ~IOT_PROG_SEL;
  P3SEL1 &= ~IOT_PROG_SEL;
  P3DIR &= ~IOT_PROG_SEL;
  
  //P3_4
  //this is the one that changes
  if(port_type){// 0x00 for P3_L_REVERSE, 0x01 for P3_SMCLK
    //SMCLK
    P3SEL0 |= L_REVERSE;
    P3SEL1 |= L_REVERSE;  
    P3DIR |= L_REVERSE;
  }else{
    //L_REVERSE
    P3SEL0 |= L_REVERSE;
    P3SEL1 &= ~L_REVERSE; 
    //P3OUT &= ~L_REVERSE; 
    //P3DIR |= L_REVERSE; 
  }
  
  //P3_5
  P3SEL0 |= L_FORWARD;
  P3SEL1 &= ~L_FORWARD;
  //P3OUT &= ~L_FORWARD;
  //P3DIR |= L_FORWARD;
  
  //P3_6
  P3SEL0 |= R_REVERSE;
  P3SEL1 &= ~R_REVERSE;
  //P3OUT &= ~R_REVERSE;
  //P3DIR |= R_REVERSE;
  
  //P3_7
  P3SEL0 |= R_FORWARD;
  P3SEL1 &= ~R_FORWARD;
  //P3OUT &= ~R_FORWARD;
  //P3DIR |= R_FORWARD;
}

//init port 4
//4.0
//4.1
//4.2
//4.3
//4.4
//4.5
//4.6
//4.7
void Init_Port4(){
  P4SEL0 = RESET_STATE;
  P4SEL1 = RESET_STATE;
  P4DIR = RESET_STATE;
  P4OUT = RESET_STATE;
  //P4_0
  P4SEL0 &= ~SD_CS;
  P4SEL1 &= ~SD_CS;
  P4DIR &= ~SD_CS;
  //P4_1
  P4SEL0 &= ~J4_31;
  P4SEL1 &= ~J4_31;
  P4DIR &= ~J4_31;
  //P4_2
  P4SEL0 &= ~J4_32;
  P4SEL1 &= ~J4_32;
  P4DIR &= ~J4_32;
  //P4_3
  P4SEL0 &= ~J4_33;
  P4SEL1 &= ~J4_33;
  P4DIR &= ~J4_33;
  //P4_4
  P4SEL0 &= ~UCB1_CS_LCD;
  P4SEL1 &= ~UCB1_CS_LCD;
  P4DIR |= UCB1_CS_LCD;
  P4OUT &= ~UCB1_CS_LCD;//
  //P4_5
  P4SEL0 &= ~P4_5;
  P4SEL1 &= ~P4_5;
  P4DIR &= ~P4_5;
  //P4_6
  P4SEL0 &= ~P4_6;
  P4SEL1 &= ~P4_6;
  P4DIR &= ~P4_6;
  //P4_7
  P4SEL0 &= ~J3_29;
  P4SEL1 &= ~J3_29;
  P4DIR &= ~J3_29;
}

void Init_Port5(){
  P5SEL0 = RESET_STATE;
  P5SEL1 = RESET_STATE;
  P5OUT = RESET_STATE;
  P5DIR = RESET_STATE;
  P5REN = RESET_STATE;
  //P5_0
  P5SEL0 |= SPI_UCB1SIMO;
  P5SEL1 &= ~SPI_UCB1SIMO;
  //P5_1
  P5SEL0 |= SPI_UCB1SOMI;
  P5SEL1 &= ~SPI_UCB1SOMI;
  //P5_2
  P5SEL0 |= SPI_UCB1CLK;
  P5SEL1 &= ~SPI_UCB1CLK;
  //P5_3
  P5SEL0 &= ~RST_LCD;
  P5SEL1 &= ~RST_LCD;
  P5OUT |= RST_LCD;
  P5DIR |= RST_LCD;//
  //P5_4
  P5SEL0 &= ~P5_4;
  P5SEL1 &= ~P5_4;
  P5DIR &= ~P5_4;
  //P5_5
  P5SEL0 &= ~BUTTON2;
  P5SEL1 &= ~BUTTON2;
  P5OUT |= BUTTON2;
  P5DIR &= ~BUTTON2;
  P5REN |= BUTTON2;
  P5IES |= BUTTON2;//
  P5IFG &= ~BUTTON2;//
  P5IE |= BUTTON2;//
  //P5_6
  P5SEL0 &= ~BUTTON1;
  P5SEL1 &= ~BUTTON1;
  P5OUT |= BUTTON1;
  P5DIR &= ~BUTTON1;
  P5REN |= BUTTON1;
  P5IES |= BUTTON1;//
  P5IFG &= ~BUTTON1;//
  P5IE |= BUTTON1;//
  //P5_7
  P5SEL0 &= ~LCD_BACKLIGHT;
  P5SEL1 &= ~LCD_BACKLIGHT;
  P5OUT |= LCD_BACKLIGHT;
  P5DIR |= LCD_BACKLIGHT;
}

void Init_Port6(){
  P6SEL0 = RESET_STATE;
  P6SEL1 = RESET_STATE;
  P6DIR = RESET_STATE;
  P6OUT = RESET_STATE;
  //P6_0
  P6SEL0 |= UCA3TXD;
  P6SEL1 &= ~UCA3TXD;
  //P6_1
  P6SEL0 |= UCA3RXD;
  P6SEL1 &= ~UCA3RXD;
  //P6_2
  P6SEL0 &= ~J1_5;
  P6SEL1 &= ~J1_5;
  P6DIR &= ~J1_5;
  //P6_3
  P6SEL0 &= ~MAG_INT;
  P6SEL1 &= ~MAG_INT;
  P6DIR &= ~MAG_INT;
  //P6_4
  P6SEL0 |= P6_4;
  P6SEL1 &= ~P6_4;
  //P6DIR &= ~P6_4;
  //P6_5
  P6SEL0 |= P6_5;
  P6SEL1 &= ~P6_5;
  //P6DIR &= ~P6_5;
  //P6_6
  P6SEL0 |= P6_6;
  P6SEL1 &= ~P6_6;
  //P6DIR &= ~P6_6;
  //P6_7
  P6SEL0 |= P6_7;
  P6SEL1 &= ~P6_7;
  //P6DIR &= ~P6_7;
}

void Init_Port7(){
  P7SEL0 = RESET_STATE;
  P7SEL1 = RESET_STATE;
  P7DIR = RESET_STATE;
  //P7_0
  P7SEL0 |= UCB2SDA;
  P7SEL1 &= ~UCB2SDA;
  //P7_1
  P7SEL0 |= UCB2SCL;
  P7SEL1 &= ~UCB2SCL;
  //P7_2
  P7SEL0 &= ~SD_DETECT;
  P7SEL1 &= ~SD_DETECT;
  P7DIR &= ~SD_DETECT;
  //P7_3
  P7SEL0 &= ~J4_36;
  P7SEL1 &= ~J4_36;
  P7DIR &= ~J4_36;
  //P7_4
  P7SEL0 &= ~P7_4;
  P7SEL1 &= ~P7_4;
  P7DIR &= ~P7_4;
  //P7_5
  P7SEL0 &= ~P7_5;
  P7SEL1 &= ~P7_5;
  P7DIR &= ~P7_5;
  //P7_6
  P7SEL0 &= ~P7_6;
  P7SEL1 &= ~P7_6;
  P7DIR &= ~P7_6;
  //P7_7
  P7SEL0 &= ~P7_7;
  P7SEL1 &= ~P7_7;
  P7DIR &= ~P7_7;
}

void Init_Port8(){
  P8SEL0 = SMALL_RST;
  P8SEL1 = SMALL_RST;
  P8DIR = SMALL_RST;
  //P8_0
  P8SEL0 &= ~IR_LED;
  P8SEL1 &= ~IR_LED;
  P8DIR &= ~IR_LED;
  //P8_1
  P8SEL0 &= ~OPT_INT;
  P8SEL1 &= ~OPT_INT;
  P8DIR &= ~OPT_INT;
  //P8_2
  P8SEL0 &= ~TMP_INT;
  P8SEL1 &= ~TMP_INT;
  P8DIR &= ~TMP_INT;
  //P8_3
  P8SEL0 &= ~INT2;
  P8SEL1 &= ~INT2;
  P8DIR &= ~INT2;
}

void Init_PortJ(){
  PJSEL0 = RESET_STATE;
  PJSEL1 = RESET_STATE;
  PJDIR = RESET_STATE;
  PJOUT = RESET_STATE;
  //PJ_0 smclk
  PJSEL0 &= ~PJ_0;
  PJSEL1 |= PJ_0;
  PJDIR &= ~PJ_0;
  //PJ_1 mclk
  PJSEL0 &= ~PJ_1;
  PJSEL1 |= PJ_1;
  PJDIR &= ~PJ_1;
  //PJ_2 aclk
  PJSEL0 &= ~PJ_2;
  PJSEL1 |= PJ_2;
  PJDIR &= ~PJ_2;
  //PJ_3 tck
  PJSEL0 &= ~PJ_3;
  PJSEL1 |= PJ_3;
  PJDIR &= ~PJ_3;
  //PJ_4
  PJSEL0 |= LFXIN;
  PJSEL1 &= ~LFXIN;
  //PJ_5
  PJSEL0 |= LFXOUT;
  PJSEL1 &= ~LFXOUT;
  //PJ_6
  PJSEL0 &= ~HFXIN;
  PJSEL1 &= ~HFXIN;
  PJOUT &= ~HFXIN;
  PJDIR |= HFXIN;
  //PJ_7
  PJSEL0 &= ~HFXOUT;
  PJSEL1 &= ~HFXOUT;
  PJOUT &= ~HFXOUT;
  PJDIR |= HFXOUT;
}