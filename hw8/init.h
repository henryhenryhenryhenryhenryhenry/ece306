//------------------------------
//file name:   init.h
//description: contains a bunch of variables used throughout the project
//author:      henry lindbo 9/26/18
//------------------------------



extern volatile unsigned char display_changed;
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;
extern char display_line[4][11];
extern char *display[4];

extern volatile unsigned int button_pressed;
extern volatile unsigned int button_debounce;

extern volatile unsigned int max_state_mchn_state;
extern volatile unsigned int state_mchn_state;
extern volatile unsigned int new_state;
extern volatile unsigned int done;

extern volatile unsigned int ADC_Thumb_raw;
extern volatile unsigned int ADC_Right_Detector_raw;
extern volatile unsigned int ADC_Left_Detector_raw;

extern volatile unsigned int ADC_Thumb;
extern volatile unsigned int ADC_Right_Detector;
extern volatile unsigned int ADC_Left_Detector;
extern char adc_val_str[4];

extern unsigned int R_det_max;
extern unsigned int R_det_min;
extern unsigned int L_det_max;
extern unsigned int L_det_min;

extern volatile unsigned int linefollow_state;

extern volatile unsigned int total_time_running; //time in 100ms

extern volatile unsigned int armed;

extern  double RWheelPercentage ;
extern  double LWheelPercentage ;
extern  unsigned int RWheelSpeed;
extern  unsigned int LWheelSpeed;

extern volatile char uca3_rx_buff[16];
extern volatile char uca3_tx_buff[16];
extern volatile unsigned int uca3_rx_buff_wr;
extern volatile unsigned int uca3_rx_buff_rd;
extern volatile unsigned int uca3_tx_buff_wr;
extern volatile unsigned int uca3_tx_buff_rd;
extern char rx_str[10];

extern volatile char serial_test[10];

extern volatile unsigned int UCA3_index;

