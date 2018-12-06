#include  "msp430.h"
#include  "functions.h"
#include "macros.h"
#include "init.h"
#include "led.h"
#include "timers.h"
#include "ports.h"

  volatile unsigned int ADC_Thumb = RESET_STATE;
  volatile unsigned int ADC_Right_Detector = RESET_STATE;
  volatile unsigned int ADC_Left_Detector = RESET_STATE;
  char adc_val_str[FOUR_LINES];

void Init_ADC(void){
  //------------------------------------------------------------------------------
  // Configure ADC12
  

  
  // ADC10CTL0 Register Description
  ADC12CTL0 = RESET_STATE;
  ADC12CTL0 |= ADC12SHT0_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12SHT1_2;     // 16 ADC clocks
  ADC12CTL0 |= ADC12MSC;        // First rising edge SHI signal triggers sampling timer
  ADC12CTL0 |= ADC12ON;         // ADC12 on
  
  // ADC10CTL1 Register Description
  ADC12CTL1 = RESET_STATE;
  ADC12CTL1 |= ADC12PDIV_0;     // Predivide ADC12_B clock source by 1
  ADC12CTL1 |= ADC12SHS_0;      // sample-and-hold source ADC12SC
  ADC12CTL1 |= ADC12SHP;      // SAMPCON signal is sourced from the sampling timer.
  ADC12CTL1 |= ADC12ISSH_0;     // sample-input signal is not inverted
  ADC12CTL1 |= ADC12DIV_0;      // / 1 clock divider
  ADC12CTL1 |= ADC12SSEL0;      // ADC12OSC (MODOSC)
  ADC12CTL1 |= ADC12CONSEQ_3;   // Repeat-sequence-of-channels
  
  // ADC12CTL2 Register Description
  ADC12CTL2 = RESET_STATE;
  ADC12CTL2 |= ADC12RES_2;      // 12-bit conversion results / 14 clock cycle conversion
  ADC12CTL2 |= ADC12DF_0;       // Binary unsigned
  ADC12CTL2 |= ADC12PWRMD_0;    // Regular power mode where sample rate is not restricted
  
  // ADC12CTL3 Register Description
  ADC12CTL3 = RESET_STATE;
  ADC12CTL3 |= ADC12ICH3MAP_0;  // external pin is selected for ADC input channel A26
  ADC12CTL3 |= ADC12ICH2MAP_0;  // external pin is selected for ADC input channel A27
  ADC12CTL3 |= ADC12ICH1MAP_0;  // external pin is selected for ADC input channel A28
  ADC12CTL3 |= ADC12ICH0MAP_0;  // external pin is selected for ADC input channel A29
  ADC12CTL3 |= ADC12TCMAP_1;    // ADC internal temperature sensor ADC input channel A30
  ADC12CTL3 |= ADC12BATMAP_1;   // ADC internal 1/2 x AVCC is ADC input channel A31
  ADC12CTL3 |= ADC12CSTARTADD_0; // 0h to 1Fh, corresponding to ADC12MEM0 to ADC12MEM31
  
  // ADC10MCTL0 Register Description
  ADC12MCTL0 = RESET_STATE;
  ADC12MCTL0 |= ADC12WINC_0;    // Comparator window disabled
  ADC12MCTL0 |= ADC12DIF_0;     // Single-ended mode enabled
  ADC12MCTL0 |= ADC12VRSEL_0;   // VR+ = AVCC, VR- = AVSS
  ADC12MCTL0 |= ADC12INCH_2;    // channel = A2 Thumb Wheel
  
  ADC12MCTL1 = RESET_STATE;
  ADC12MCTL1 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL1 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL1 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL1 |= ADC12INCH_5;  // channel = A5 Left
  
  ADC12MCTL2 = RESET_STATE;
  ADC12MCTL2 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL2 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL2 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL2 |= ADC12INCH_4;  // channel = A4 Right
  
  ADC12MCTL3 = RESET_STATE;
  ADC12MCTL3 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL3 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL3 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL3 |= ADC12INCH_30; // Temp sensor
  
  ADC12MCTL4 = RESET_STATE;
  ADC12MCTL4 |= ADC12WINC_0;  // Comparator window disabled
  ADC12MCTL4 |= ADC12DIF_0;   // Single-ended mode enabled
  ADC12MCTL4 |= ADC12VRSEL_0; // VR+ = AVCC, VR- = AVSS
  ADC12MCTL4 |= ADC12INCH_31; // Battery voltage monitor
  ADC12MCTL4 |= ADC12EOS;     // End of Sequence
  
  // ADC12IER0-2 Register Descriptions
  ADC12IER0 = RESET_STATE;    // Interrupts for channels  0 - 15
  ADC12IER1 = RESET_STATE;    // Interrupts for channels 16 - 31
  ADC12IER2 = RESET_STATE;    // Interrupts for ADC12RDYIE ADC12TOVIE ADC12OVIE
  // ADC12HIIE ADC12LOIE ADC12INIE
  
  ADC12IER0 |= ADC12IE2;      // Generate Interrupt for MEM2 ADC Data load//
  //  ADC12IER0 |= ADC12IE2;    // Generate Interrupt for MEM2 ADC Data load
  //  ADC12IER0 |= ADC12IE0;    // Enable ADC conv complete interrupt
  
  ADC12CTL0 |= ADC12ENC;     // Start conversion
  ADC12CTL0 |= ADC12SC;      // Start sampling
  //------------------------------------------------------------------------------
}


//interrupt for ADC
#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void){
  switch(__even_in_range(ADC12IV, ADC12IV__ADC12RDYIFG)){
  case ADC12IV__NONE:        break;   //vector  0: no interrupt
  case ADC12IV__ADC12OVIFG:  break;   //vector  2: ADC12MEMx overflow
  case ADC12IV__ADC12TOVIFG: break;   //vector  4: conversion time overflow
  case ADC12IV__ADC12HIIFG:  break;   //vector  6: ADC12BHI - dont know what this is 
  case ADC12IV__ADC12LOIFG:  break;   //vector  8: ADC12BLO - dont know what this is 
  case ADC12IV__ADC12INIFG:  break;   //vector 10: ADC12BIN - dont know what this is 
  
  case ADC12IV__ADC12IFG0:   break;   //vector 12: ADC12MEM0 interrupt
  case ADC12IV__ADC12IFG1:   break;
  case ADC12IV__ADC12IFG2:            //vector 16: ADC12MEM2 interrupt
    
    ADC_Thumb = ADC12MEM0;
    ADC_Right_Detector = ADC12MEM1;  //big # means black, small # means white
    ADC_Left_Detector = ADC12MEM2;   //big # means black, small # means white
    break;
    
  case ADC12IV__ADC12IFG3: break;
  case ADC12IV__ADC12IFG4: break;
  case ADC12IV__ADC12IFG5: break;
  case ADC12IV__ADC12IFG6: break;
  case ADC12IV__ADC12IFG7: break;
  case ADC12IV__ADC12IFG8: break;
  
  case ADC12IV__ADC12IFG9: break;
  case ADC12IV__ADC12IFG10: break;
  case ADC12IV__ADC12IFG11: break;
  case ADC12IV__ADC12IFG12: break;
  case ADC12IV__ADC12IFG13: break;
  case ADC12IV__ADC12IFG14: break;
  case ADC12IV__ADC12IFG15: break;
  case ADC12IV__ADC12IFG16: break;
  case ADC12IV__ADC12IFG17: break;
  case ADC12IV__ADC12IFG18: break;
  case ADC12IV__ADC12IFG19: break;
  case ADC12IV__ADC12IFG20: break;
  case ADC12IV__ADC12IFG21: break;
  case ADC12IV__ADC12IFG22: break;
  case ADC12IV__ADC12IFG23: break;
  case ADC12IV__ADC12IFG24: break;
  case ADC12IV__ADC12IFG25: break;
  case ADC12IV__ADC12IFG26: break;
  case ADC12IV__ADC12IFG27: break;
  case ADC12IV__ADC12IFG28: break;
  case ADC12IV__ADC12IFG29: break;
  case ADC12IV__ADC12IFG30: break;
  case ADC12IV__ADC12IFG31: break;
  case ADC12IV__ADC12RDYIFG: break;
  default: break;
  }
}

void HEXtoBCD(int hex_value){// what does BCD stand for? who knows
  int value =RESET_STATE;
  adc_val_str[LINE_0TH] = '0'; //MSB
  adc_val_str[LINE_1ST] = '0';
  adc_val_str[LINE_2ND] = '0';
  adc_val_str[LINE_3RD] = '0'; //LSB
  
  while(hex_value >= THOUSAND){
    hex_value -= THOUSAND;
    value++;
    adc_val_str[LINE_0TH] = HEX_ZERO + value;
  }
  value = RESET_STATE;
  while(hex_value >= HUNDRED){
    hex_value -= HUNDRED;
    value++;
    adc_val_str[LINE_1ST] = HEX_ZERO + value;
  }
  value = RESET_STATE;
  while(hex_value >= TEN){
    hex_value -= TEN;
    value++;
    adc_val_str[LINE_2ND] = HEX_ZERO + value;
  }
  value = RESET_STATE;
  while(hex_value >= ONE){
    hex_value -= ONE;
    value++;
    adc_val_str[LINE_3RD] = HEX_ZERO + value;
  }
  
}
