/*
 * led_driver.h
 *
 *  Created on: 2017��12��2��
 *      Author: leo
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#define CAT3626_ADDRESS 0xCC
#define POWER_LIGHT 0//register A
#define OPE_LIGHT   0//register A
#define ALM_LIGHT   1//register B
#define GD_LIGHT    1//register B
#define CC_LIGHT    2//register C

#define POWER_LIGHT_ON 1//register A
#define OPE_LIGHT_ON   2//register A
#define ALM_LIGHT_ON   4//register B
#define GD_LIGHT_ON    8//register B
#define CC_LIGHT_ON    16//register C

#define LED_LUX 0x3F//lightest

#define LED_ON  1
#define LED_OFF 0
unsigned char led_control_lux(bool led_lux, unsigned char led);
unsigned char led_control_on(bool led_state, unsigned char led);
unsigned char read_led_state(void);
#endif /* LED_DRIVER_H_ */
