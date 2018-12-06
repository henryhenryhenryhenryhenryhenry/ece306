#include  "msp430.h"
#include  "functions.h"
#include <string.h>
#include "macros.h"
#include "init.h"
#include "led.h"
#include "timers.h"
#include "ports.h"

volatile char uca3_rx_buff[16];
volatile char uca3_tx_buff[16];
volatile unsigned int uca3_rx_buff_wr;
volatile unsigned int uca3_rx_buff_rd;
volatile unsigned int uca3_tx_buff_wr;
volatile unsigned int uca3_tx_buff_rd;
volatile char serial_test[10];
volatile unsigned int UCA3_index;
char rx_str[10];

void init_serial_UCA3(unsigned int br){//baudrate * 100 = actual desired baud
  
  serial_test[0] = '^';
  serial_test[1] = 'N';
  serial_test[2] = 'C';
  serial_test[3] = 'S';
  serial_test[4] = 'U';
  serial_test[5] = ' ';
  serial_test[6] = ' ';
  serial_test[7] = '#';
  serial_test[8] = '1';
  
  int i;
  for(i=0;i<16;i++){
    uca3_rx_buff[i] = 0x00;
  }
  uca3_rx_buff_wr = 0;
  uca3_rx_buff_rd = 0;
  
  for(i=0;i<16;i++){
    uca3_tx_buff[i] = 0x00;
  }
  uca3_tx_buff_wr = 0;
  uca3_tx_buff_rd = 0;
  
  
  UCA3CTLW0 = 0;
  UCA3CTLW0 |= UCSSEL__SMCLK;
  UCA3CTLW0 |= UCSWRST;
  
  switch(br){
  case 1152: //115200
    UCA3BRW = 4;       //changes based on baudrate
    UCA3MCTLW = 0x5551; //changes based on baudrate
    break;
  case 4608: //460800
    UCA3BRW = 1;       //changes based on baudrate
    UCA3MCTLW = 0x4A11; //changes based on baudrate
    break;
  case 96: //9600
    UCA3BRW = 52;       //changes based on baudrate
    UCA3MCTLW = 0x4911; //changes based on baudrate
    break;
  }
  
  UCA3CTL1 &= ~UCSWRST;
  UCA3IE |= UCRXIE; //RX interrupt
  
  //for different baud rates see below
  //-----------------------------------------------------------------------------
  //9600 baud rate
  //1. N = fBRCLK / baudrate
  //   N = SMCLK / 9600 = 8000000 / 9600 = 833.333
  //   if N > 16 goto step 3, otherwise goto 2
  //2. OS16 = 0, UCBRx = INT(N)
  //   goto step 4
  //3. OS16 = 1,
  //   UCx = INT(N/16) = 833.333/16 = 52
  //   UCFx = INT([(N/16) - INT(N/16)] * 16)
  //        = INT([833.333/16 - INT(833.33/16)] * 16)
  //        = 1
  //4. UCSx = look up fractional part of N (N-INT(N)) in table 18-4
  //   8000000/9600 = 833.333 -> 0.333 yields 0x49 [see table]
  //5. if OS16 = 0, perform error calculation
  //
  // BRCLK   baudrate  UCOS16  UCBRx  UCFx  UCSx
  // 8000000 9600      1       52     1     0x49
  //
  //UCA3BRW = 52
  //UCA3MCTLW = UCSx concat. UCFx concat. UCOS16 = 0x49_1_1
  //UCA3MCTLW = 0x4911
  //-----------------------------------------------------------------------------
  
  //115200 baud rate
  //1. N = fBRCLK / baudrate
  //   N = SMCLK / 115200 = 8000000 / 115200 = 69.444
  //   if N > 16 goto step 3, otherwise goto 2
  //2. OS16 = 0, UCBRx = INT(N)
  //   goto step 4
  //3. OS16 = 1,
  //   UCx = INT(N/16) = 69.444/16 = 4
  //   UCFx = INT([(N/16) - INT(N/16)] * 16)
  //        = INT([69.444/16 - INT(69.444/16)] * 16)
  //        = 5
  //4. UCSx = look up fractional part of N (N-INT(N)) in table 18-4
  //   8000000/115200 = 69.444 -> 0.444 yields 0x55 [see table]
  //5. if OS16 = 0, perform error calculation
  //
  // BRCLK   baudrate  UCOS16  UCBRx  UCFx  UCSx
  // 8000000 115200    1       4      5     0x55
  //
  //UCA3BRW = 4
  //UCA3MCTLW = UCSx concat. UCFx concat. UCOS16 = 0x55_5_1
  //UCA3MCTLW = 0x5551
  //-----------------------------------------------------------------------------
  
  //460800 baud rate
  //1. N = fBRCLK / baudrate
  //   N = SMCLK / 460800 = 8000000 / 460800 = 17.36111
  //   if N > 16 goto step 3, otherwise goto 2
  //2. OS16 = 0, UCBRx = INT(N)
  //   goto step 4
  //3. OS16 = 1,
  //   UCx = INT(N/16) = 17.36111/16 = 1
  //   UCFx = INT([(N/16) - INT(N/16)] * 16)
  //        = INT([17.36111/16 - INT(17.36111/16)] * 16)
  //        = 1
  //4. UCSx = look up fractional part of N (N-INT(N)) in table 18-4
  //   8000000/460800 = 17.36111 -> 0.36111 yields 0x4A [see table]
  //5. if OS16 = 0, perform error calculation
  //
  // BRCLK   baudrate  UCOS16  UCBRx  UCFx  UCSx
  // 8000000 460800    1       1      1     0x4A
  //
  //UCA3BRW = 1
  //UCA3MCTLW = UCSx concat. UCFx concat. UCOS16 = 0x4A_1_1
  //UCA3MCTLW = 0x4A11
}

/*
//UCA3 TX interrupt
#pragma vector = USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
  switch(UCA3_index++){
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
    UCA3TXBUF = serial_test[UCA3_index];
    break;
  case 9:
    UCA3TXBUF = 0x0D;
    break;
  case 10:
    UCA3TXBUF = 0x0A;
    break;
  default:
    UCA3_index = 0;
    UCA3IE &= ~UCTXIE; //disable tx interrupt
    break;
  }
}
*/

//UCA3 RX interrupt
#pragma vector = USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
  unsigned int temp;
  switch(__even_in_range(UCA3IV,0x08)){
  case 0: //no interrupt
    break;
  case 2: //RXIFG
    temp = uca3_rx_buff_wr;
    uca3_rx_buff[temp] = UCA3RXBUF;
    if(uca3_rx_buff_wr++ >= 16){
      uca3_rx_buff_wr = 0;
    }
    break;
  case 4: //TXIFG
    switch(UCA3_index++){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      UCA3TXBUF = serial_test[UCA3_index];
      break;
    case 9:
      UCA3TXBUF = 0x0D;
      break;
    case 10:
      UCA3TXBUF = 0x0A;
      break;
    default:
      UCA3_index = 0;
      UCA3IE &= ~UCTXIE; //disable tx interrupt
      break;
    }
    break;
  default:
    break;
  }
}

void outchar(char character){
  while(!(UCA3IFG & UCTXIFG)); //USCI_A3 TX buffer ready?
  UCA3TXBUF = character;
}


