//------------------------------
//file name:   macros.h
//description: macros and magic #s for main.c etc
//author:      henry lindbo 9/26/18
//------------------------------



//#define RED_LED              (0x01) // RED LED 0
//#define GRN_LED              (0x02) // GREEN LED 1

#define ALWAYS                  (1)
#define RESET_STATE             (0)
#define INV_RST_STATE           (0xFF)
//#define RED_LED              (0x01) // RED LED 0
//#define GRN_LED              (0x02) // GREEN LED 1
#define PORTS                (0x00) // PORTS
#define PWM_MODE             (0x01) // PWM_MODE

#define TIME_A                   125
#define TIME_B                   100
#define TIME_C                   75
#define TIME_D                   50
#define TIME_E                   25

#define LINE_0TH                 0
#define LINE_1ST                 1
#define LINE_2ND                 2
#define LINE_3RD                 3

#define BUTTON1PRESSED 1
#define BUTTON2PRESSED 2

#define LEFT_REVERSE_SPEED  (TB0CCR3)
#define LEFT_FORWARD_SPEED  (TB0CCR4)
#define RIGHT_REVERSE_SPEED (TB0CCR5)
#define RIGHT_FORWARD_SPEED (TB0CCR6)

#define WHEEL_PERIOD            10000
#define WHEEL_OFF                   0
#define L_WHEEL_REV              5000
#define L_WHEEL_FWD              5000
#define R_WHEEL_REV              5000
#define R_WHEEL_FWD              5000



