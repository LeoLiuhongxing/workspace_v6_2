/*
 * valve.c
 *
 *  Created on: Jan 11, 2018
 *      Author: leo.liu
 */

//p5.5 CS_SPI_IO_IN
//P5.7 CS_SPI_IO_OUT
#include "valve.h"
#include "MCP23S17.h"

void control_valve(unsigned char valve,unsigned char group)//output high
{
    if(group == GROUP0)
    {
    	Write23X17_Output(GPIOA, valve);
    }else if(group == GROUP1)
	{
    	Write23X17_Output(GPIOB, valve);
	}
}

void control_single_valve(unsigned char valve_number,unsigned char value)//output high, value==0:close   value==1: open
{
    unsigned char group;
    unsigned char data;
    group = valve_number/8;

	if(group == GROUP0)
	{

	}else if(group == GROUP1)
	{

	}
}

void control_valve_command_80(void)//stop
{
	control_valve(0x00,GROUP0);
	control_valve(0x00,GROUP1);
}

void control_valve_command_91(void)//run
{
	control_valve(0x49,GROUP0);
	control_valve(0x08,GROUP1);
}

void control_valve_command_92(void)//purg1
{
	control_valve(0xA6,GROUP0);
	control_valve(0x07,GROUP1);
}

void control_valve_command_93(void)//purg2
{
	control_valve(0xA6,GROUP0);
	control_valve(0x1F,GROUP1);
}


