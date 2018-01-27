/*
 * IO_Config.c
 *
 *  Created on: 2017Äê11ÔÂ25ÈÕ
 *      Author: leo
 */
#include <msp430.h>
#include "IO_Config.h"


void IO_init(void)
{
	P9DIR |= BIT0;//p9.0 OUTPUT For Fan1 control
	P9DIR |= BIT1;//p9.1 output for fan2 control
	P9DIR |= BIT2;//p9.2 output for O3 driver signal control
	P9DIR |= BIT3;//p9.2 output for O3 power signal control

//	P7DIR |= 0xFF;//p7.0~p7.7 output for valve control
//	P8DIR |= 0xFF;//p8.0~p8.7 output for valve control
	P5DIR |=BIT5+BIT7;//p5.5 CS_SPI_IO_IN //P5.7 CS_SPI_IO_OUT
	P5OUT |= (1<<5);//SPI in disable
	P5OUT |= (1<<7);//spi out disable
}


void Fan1_Set(bool fan_state)
{
	if(fan_state == true)
	    P9OUT |= (1<<0);
	else
		P9OUT &= ~(1<<0);
}

void Fan2_Set(bool fan_state)
{
	if(fan_state == true)
	    P9OUT |= (1<<1);
	else
		P9OUT &= ~(1<<1);
}

void O3_Driver_Set(bool driver_state)
{
	if(driver_state == true)
	    P9OUT |= (1<<2);
	else
		P9OUT &= ~(1<<2);
}

void O3_Power_Set(bool power_state)
{
	if(power_state == true)
	    P9OUT |= (1<<2);
	else
		P9OUT &= ~(1<<2);
}

