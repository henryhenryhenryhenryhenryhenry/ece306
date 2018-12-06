//------------------------------
//file name:   ports.h
//description: all the macros for ports.c
//author:      henry lindbo 9/26/18
//------------------------------


//port 1 pins
#define RED_LED     0x01
#define GRN_LED     0x02
#define V_THUMB     0x04
#define TEST_PROBE  0x08
#define V_DETECT_R  0x10
#define V_DETECT_L  0x20
#define SD_UCB0SIMO 0x40
#define SD_UCB0SOMI 0x80

//port 2 pins
#define UCA0TXD   0x01
#define UCA0RXD   0x02
#define UCB0CLK 0x04
#define P2_3      0x08
#define P2_4      0x10
#define UCA1TXD   0x20
#define UCA1RXD   0x40
#define P2_7      0x80

//port 3 pins
#define IOT_RST       0x01
#define IOT_PROG_MODE 0x02
#define IOT_LINK      0x04
#define IOT_PROG_SEL  0x08
#define L_REVERSE     0x10
#define L_FORWARD     0x20
#define R_REVERSE     0x40
#define R_FORWARD     0x80

//port 4 pins
#define SD_CS       0x01
#define J4_31       0x02
#define J4_32       0x04
#define J4_33       0x08
#define UCB1_CS_LCD 0x10
#define P4_5        0x20
#define P4_6        0x40
#define J3_29       0x80

//port 5 pins
#define SPI_UCB1SIMO  0x01
#define SPI_UCB1SOMI  0x02
#define SPI_UCB1CLK   0x04
#define RST_LCD       0x08
#define P5_4          0x10
#define BUTTON2       0x20
#define BUTTON1       0x40
#define LCD_BACKLIGHT 0x80

//port 6 pins
#define UCA3TXD 0x01
#define UCA3RXD 0x02
#define J1_5    0x04
#define MAG_INT 0x08
#define P6_4    0x10
#define P6_5    0x20
#define P6_6    0x40
#define P6_7    0x80

//port 7 pins
#define UCB2SDA    0x01
#define UCB2SCL    0x02
#define SD_DETECT 0x04
#define J4_36     0x08
#define P7_4      0x10
#define P7_5      0x20
#define P7_6      0x40
#define P7_7      0x80

//port 8 pins
#define SMALL_RST 0x0
#define IR_LED  0x01
#define OPT_INT 0x02
#define TMP_INT 0x04
#define INT2    0x08

//port J pins
#define PJ_0   0x01
#define PJ_1   0x02
#define PJ_2   0x04
#define PJ_3   0x08
#define LFXIN  0x10
#define LFXOUT 0x20
#define HFXIN  0x40
#define HFXOUT 0x80

extern void Init_Ports(void);
extern void Init_Port1(void);
extern void Init_Port2(void);
//extern void Init_Port3(char port_type);
extern void Init_Port3(void);
extern void Init_Port4(void);
extern void Init_Port5(void);
extern void Init_Port6(void);
extern void Init_Port7(void);
extern void Init_Port8(void);
extern void Init_PortJ(void);
