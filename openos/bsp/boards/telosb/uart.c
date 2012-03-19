/**
\brief TelosB-specific definition of the "uart" bsp module.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012.
*/

#include "msp430f1611.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"
#include "openserial.h"

//=========================== defines =========================================
//=========================== variables =======================================
//=========================== prototypes ======================================
//=========================== public ==========================================

void uart_init() {
   P3SEL                     =  0xC0;            // P3.6,7 = UART1TX/RX
   
   UCTL1                     =  SWRST;           // hold UART1 module in reset
   UCTL1                    |=  CHAR;            // 8-bit character
   
//#ifdef UART_BAUDRATE_115200
   //115200 baud, clocked from 4.8MHz SMCLK
//   UTCTL1                   |=  SSEL1;           // clocking from SMCLK
//   UBR01                     =  41;              // 4.8MHz/115200 - 41.66
//   UBR11                     =  0x00;            //
//   UMCTL1                    =  0x4A;            // modulation
//#else
   //9600 baud, clocked from 32kHz ACLK
   UTCTL1                   |=  SSEL0;           // clocking from ACLK
   UBR01                     =  0x03;            // 32768/9600 = 3.41
   UBR11                     =  0x00;            //
   UMCTL1                    =  0x4A;            // modulation
//#endif
   
   ME2                      |=  UTXE1 + URXE1;   // enable UART1 TX/RX
   UCTL1                    &= ~SWRST;           // clear UART1 reset bit
}


void    uart_enableInterrupts(){
  IE2 |=  (URXIE1 | UTXIE1);  
}

void    uart_disableInterrupts(){
  IE2 &= ~(URXIE1 | UTXIE1);
}

void    uart_clearRxInterrupts(){
  IFG2   &= ~URXIFG1;
}

void    uart_clearTxInterrupts(){
  IFG2   &= ~UTXIFG1;
}

void    uart_writeByte(uint8_t byteToWrite){
  U1TXBUF = byteToWrite;
}

uint8_t uart_readByte(){
  return U1RXBUF;
}


//=========================== private =========================================
//=========================== interrupt handlers ==============================

uint8_t uart_isr_tx() {
   uart_clearTxInterrupts(); // TODO: do not clear, but disable when done
   isr_openserial_tx();
   return 0;
}

uint8_t uart_isr_rx() {
   uart_clearRxInterrupts(); // TODO: do not clear, but disable when done
   isr_openserial_rx();
   return 0;
}