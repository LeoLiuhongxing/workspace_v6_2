/*
 * UARTA0.h
 *
 *  Created on: 2018Äê1ÔÂ1ÈÕ
 *      Author: leo
 */

#ifndef UARTA0_H_
#define UARTA0_H_

#define	BAUDRATE9600 0
#define	BAUDRATE4800 1
#define	BAUDRATE2400 2
#define	BAUDRATE1200 3
#define QUEUE_SIZE 64

typedef struct
{
	volatile unsigned char head;
	volatile unsigned char tail;
    volatile unsigned char data[QUEUE_SIZE];
    volatile unsigned char command_complete_flag;
}receive_queue_;


receive_queue_ receive_queue;
void Set_baudrate(unsigned char baudrate);
unsigned char Get_Baudrate(void);
void USCI_A0_TX (char* buffer, unsigned char size);
#endif /* UARTA0_H_ */
