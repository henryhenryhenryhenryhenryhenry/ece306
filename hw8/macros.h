//------------------------------
//file name:   macros.h
//description: macros and magic #s for main.c etc
//author:      henry lindbo 9/26/18
//------------------------------



//#define RED_LED              (0x01) // RED LED 0
//#define GRN_LED              (0x02) // GREEN LED 1

#define RST                      0
#define TRU                      1

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
#define FOUR_LINES               4

#define BUTTON1PRESSED 1
#define BUTTON2PRESSED 2

#define LEFT_REVERSE_SPEED  (TB0CCR3)
#define LEFT_FORWARD_SPEED  (TB0CCR4)
#define RIGHT_REVERSE_SPEED (TB0CCR5)
#define RIGHT_FORWARD_SPEED (TB0CCR6)

#define WHEEL_PERIOD            10000
#define WHEEL_OFF                   0
#define L_WHEEL_REV              2000
#define L_WHEEL_FWD              2000
#define R_WHEEL_REV              2000
#define R_WHEEL_FWD              2000

#define THOUSAND                1000
#define HUNDRED                 100
#define TEN                     10
#define ONE                     1
#define HEX_ZERO                0x30

#define CASE0DELAY              6
#define CASE1DELAY              0
#define CASE2DELAY              0
#define CASE3DELAY              100
#define CASE4DELAY              1
#define CASE5DELAY              3
#define CASE6DELAY              0

#define BLACK 2000
#define GREY  1000

#define A_LITTLE_BIT 50
#define SLOW         400
#define REAL_SLOW    300

#define LF0   0  //line follow state 0
#define LF1   1
#define LF2   2
#define LF3   3
#define LF4   4
#define LF5   5
#define LF6   6