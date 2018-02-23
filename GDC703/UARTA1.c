/*
 * UARTA1.c
 *
 *  Created on: 2018年2月21日
 *      Author: leo
 */
/*
 * UARTA0.c
 *
 *  Created on: 2017年12月20日
 *      Author: leo
 */
#include <msp430.h>
//#include "UARTA1.h"
//unsigned char switch_number1_flag = 0;//判断switch 1的状态？？？？？
unsigned char received_data = 0;
void UART1_Init(void)
{
  unsigned char i = 0;
  //P1DIR |= BIT6;
  P1SEL |= BIT6+BIT7;                       // P2.4,5 UART option select
//  UCA1CTL1 |= UCSWRST;
  UCA1CTL1 |= UCSSEL_1;                     // CLK = ACLK

  UCA1BR0 = 0x03;                           // 32k/9600 - 3.41
  UCA1BR1 = 0x00;                           //
  UCA1MCTL = 0x02;//0x06;                          // Modulation
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UC1IE |= UCA1RXIE;                 // Enable USCI_A0 TX/RX interrupt

  //__bis_SR_register(GIE);// Enter LPM3 w/ interrupts enabled
  _EINT();
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCI_A1_RX (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB1RX_VECTOR))) USCI_A1_RX (void)
#else
#error Compiler not supported!
#endif
{
#if 0
	receive_queue.data[receive_queue.tail] = UCA0RXBUF;                        // RXBUF1 to TXBUF1
	if(receive_queue.data[receive_queue.tail] == 0x0D)//cr
		receive_queue.command_complete_flag++;
	receive_queue.tail++;
	if(receive_queue.tail >= QUEUE_SIZE)
		receive_queue.tail = 0;
#else
	  while(!(UC1IFG&UCA1TXIFG));
	  //UCA1TXBUF = UCA1RXBUF;                    // TX -> RXed character
	  received_data = UCA1RXBUF;
	  UCA1TXBUF = received_data;
#endif

}

void USCI_A1_TX (char* buffer, unsigned char size)
{
	unsigned char i = 0;
	for(i=0;i<size;i++)
	{
		while(!(UC1IFG&UCA0TXIFG));
		UCA1TXBUF = buffer[i];// Transmit character
		//UCA1TXBUF = 0x55;
	}
}



