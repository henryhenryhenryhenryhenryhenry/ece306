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

//extern volatile char enable_DL;

