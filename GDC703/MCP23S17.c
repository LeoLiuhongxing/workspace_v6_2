/*
 * MCP23S17.c
 *
 *  Created on: 2017Äê12ÔÂ23ÈÕ
 *      Author: leo
 */
#include <msp430.h>
#include "MCP23S17.h"
#include "SPI.h"

#define WrtCmd  0
#define RdCmd   1
unsigned char gControlByte = 0x40;
unsigned char gAddrPins = 0;
/*************************************************************
   Function Name:  InitMCP
   Return Value:   void
   Parameters:     void
   Description:    Initializes the MCP23X17 devices
**************************************************************/

void InitMCP_Output( void )
{
    //Configure 23S17
    //Write23X17(GPPUA,  0x0F);   // Pullups
   // Write23X17(IOCONB, 0x40);   //
    Write23X17_Output(IODIRA, 0x00);   //All outputs by default (this is the POR default)
    Write23X17_Output(IODIRB, 0x00);   //All outputs by default (this is the POR default)
}

void InitMCP_Input(void)
{
	   //Configure 23S17
	    //Write23X17(GPPUA,  0x0F);   // Pullups
	   // Write23X17(IOCONB, 0x40);   //
	Write23X17_Input(IODIRA, 0xFF);   //All outputs by default (this is the POR default)
	Write23X17_Input(IODIRB, 0xFF);
}

void Write23X17_Output(unsigned char reg, unsigned char data)
{
	char temp[2];
	P5OUT &= ~(1<<7);
	temp[0] = gControlByte | WrtCmd | gAddrPins;
	spi_tx_frame(temp,1);
	temp[0] = reg;
	temp[1] = data;
	spi_tx_frame(temp, 2);
	P5OUT |= (1<<7);
}

unsigned char Read23X17_Output(unsigned char reg)
{
    unsigned char data;
	P5OUT &= ~(1<<7);
    data = gControlByte | RdCmd | gAddrPins;
    spi_tx_frame(&data,1);
    spi_tx_frame(&reg,1);
    SPI_Read(0,&data,1);
	P5OUT |= (1<<7);
    return(data);
}

void Write23X17_Input(unsigned char reg, unsigned char data)
{
	char temp[2];
	P5OUT &= ~(1<<5);
	temp[0] = gControlByte | WrtCmd | gAddrPins;
	spi_tx_frame(temp,1);
	temp[0] = reg;
	temp[1] = data;
	spi_tx_frame(temp, 2);
	P5OUT |= (1<<5);
}
/*************************************************************
   Function Name:  Read23X17
   Return Value:   void
   Parameters:     Register address
   Description:    Reads a 23X17 register. I2C or SPI is in
                   global byte
**************************************************************/
unsigned char Read23X17_Input(unsigned char reg)
{
    unsigned char data;
	P5OUT &= ~(1<<5);
    data = gControlByte | RdCmd | gAddrPins;
    spi_tx_frame(&data,1);
    spi_tx_frame(&reg,1);
    SPI_Read(0,&data,1);
	P5OUT |= (1<<5);
    return(data);
}





