/*
 * DS18B20.h
 *
 *  Created on: Jan 17, 2018
 *      Author: leo.liu
 */

#ifndef DS18B20_H_
#define DS18B20_H_

void DelayNus(unsigned int n);
unsigned char Init_18B20(void);
void Write_18B20(unsigned char wdata);
unsigned char Read_18B20(void);
void Skip(void);
void Convert(void);
void Read_SP(void);
unsigned int ReadTemp(void);
unsigned int Do1Convert(void);

#endif /* DS18B20_H_ */
