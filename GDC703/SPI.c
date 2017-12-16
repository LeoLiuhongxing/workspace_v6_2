/*
 * SPI.c
 *
 *  Created on: 2017Äê11ÔÂ20ÈÕ
 *      Author: leo
 */
#include "SPI.h"
#include <msp430.h>
void SPI_init(void)
{

	P3DIR |= BIT4+BIT5+BIT6;//Chip Select

	P3SEL |= BIT1 + BIT2 + BIT3;
	UCB0CTL0 |= UCMST+UCSYNC+UCMSB;    //3-pin, 8-bit SPI master
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	UCB0BR0 = 0x02;                           // /2
	UCB0BR1 = 0;                              //
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
//	IE2 |= UCB0RXIE;                          // Enable USCI_A0 RX interrupt

}

//--------------------------------------------------------------------------------------------------
unsigned char spi_transfer_byte(unsigned char data){
	UCB0TXBUF = data;    // write
	while (!(IFG2 & UCB0RXIFG)); // wait for transfer to complete
	IFG2 &= ~UCB0RXIFG; // clear the rx flag
    return(UCB0RXIFG);
}

//--------------------------------------------------------------------------------------------------
void spi_rx_frame(unsigned char* dst, unsigned char size){
    while(size){
    	UCB0TXBUF = 0x00;     // dummy write
    	while (!(IFG2 & UCB0RXIFG)); // wait for transfer to complete
        *dst = UCB0RXBUF;
        dst++;
        size--;
    }
}

//--------------------------------------------------------------------------------------------------
void spi_tx_frame(const unsigned char* src, unsigned char size){
    while(size){
    	while (!(IFG2 & UCB0TXIFG));
    	UCB0TXBUF = *src;
        src++;
        size--;
    }
   // while ((SPI_UCSTAT & UCBUSY) == 1); // wait for transfer to complete
    IFG2 &= ~UCB0RXIFG; // clear the rx flag
}

int SPI_Read(unsigned char slave_select_id,	unsigned char* dst,int size)
{
    while(size){
        UCB0TXBUF = 0x00;     // dummy write
		while (!(IFG2 & UCB0RXIFG)); // wait for transfer to complete
		*dst = UCB0RXBUF;
		dst++;
		size--;
    }
    return 0;
}

int SPI_Write(unsigned char slave_select_id,unsigned char* src, int size)
{
    while(size){
    	while (!(IFG2 & UCB0TXIFG));
    	UCB0TXBUF = *src;
        src++;
        size--;
    }
   // while ((SPI_UCSTAT & UCBUSY) == 1); // wait for transfer to complete
    IFG2 &= ~UCB0RXIFG; // clear the rx flag
    return 0;
}

