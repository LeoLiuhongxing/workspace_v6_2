/*
 * led_driver.c
 *
 *  Created on: 2017��12��2��
 *      Author: leo
 */

#include "IIC.h"
#include <stdbool.h>
#include "led_driver.h"

unsigned char led_control_lux(bool led_lux, unsigned char led)
{
	unsigned char Dev_addr;
	unsigned char tmp;

	Dev_addr =CAT3626_ADDRESS;
	i2c_start();

	//dev address
	i2c_SendByte(Dev_addr);
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}
	i2c_delay_ms(5);//

	//register_address
	i2c_SendByte(led);
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}

	i2c_SendByte(LED_LUX);//current data
	if(i2c_check_ACK() == FALSE)
	{
	return AckError;
	}


	i2c_stop();
	i2c_delay_ms(10);
	return 0;
}

unsigned char led_control_on(bool led_state, unsigned char led)
{
	unsigned char Dev_addr;
	unsigned char tmp;

	Dev_addr =CAT3626_ADDRESS;
	i2c_start();

	//dev address
	i2c_SendByte(Dev_addr);
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}
	i2c_delay_ms(5);//

	//register_address
	i2c_SendByte(3);
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}

	tmp = read_led_state();
	if(led_state == LED_ON)
	{
		tmp |= led;
	}else
	{
		tmp &=~led;
	}

	i2c_SendByte((unsigned char)tmp);//current data
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}


	i2c_stop();
	i2c_delay_ms(10);
	return 0;
}

unsigned char read_led_state(void)
{
	unsigned char Dev_addr;
	unsigned char tmp;

	Dev_addr = 0xCD;
	i2c_start();

	//dev address
	i2c_SendByte(Dev_addr);
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}
	i2c_delay_ms(5);//

	//register_address
	i2c_SendByte(3);
	if(i2c_check_ACK() == FALSE)
	{
		return AckError;
	}

	tmp = i2c_RevByte();//current data
	i2c_SendAck();

	i2c_stop();
	i2c_delay_ms(10);
	return tmp;
}
