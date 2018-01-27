/*
 * IO_Config.h
 *
 *  Created on: 2017Äê11ÔÂ25ÈÕ
 *      Author: leo
 */

#ifndef IO_CONFIG_H_
#define IO_CONFIG_H_

#include <stdbool.h>

void IO_init(void);
void Fan1_Set(bool fan_state);
void Fan2_Set(bool fan_state);
void O3_Driver_Set(bool driver_state);
void O3_Power_Set(bool power_state);

#endif /* IO_CONFIG_H_ */
