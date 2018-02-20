/*
 * IIC.h
 *
 *  Created on: 2017Äê11ÔÂ30ÈÕ
 *      Author: leo
 */

#ifndef IIC_H_
#define IIC_H_
#define   TRUE                1
#define   FALSE               0
#define   AckError            0x55
#define   OutOfRang           0xaa
#define   OutOfAddr           0xbb
#define SDA_IN            P2DIR &=~BIT1    // P2.1 IN
#define SDA_OUT           P2DIR |=BIT1     // P2.1 OUT
#define SDA_LOW           P2OUT &=~BIT1   // sda=0
#define SDA_HIGH          P2OUT |=BIT1   // sda=1
#define SCL_IN            P2DIR &=~BIT2    // P2.2 IN
#define SCL_OUT           P2DIR |=BIT2    // P2.2 OUT
#define SCL_LOW           P2OUT &=~BIT2
#define SCL_HIGH          P2OUT |=BIT2
void i2c_delay(unsigned char us);
void i2c_delay_ms(unsigned char ms);
void i2c_start();
void i2c_stop(void);
void i2c_SendAck(void);
void i2c_SendNoAck(void);
unsigned char i2c_check_ACK(void);
void i2c_SendByte(unsigned char data);
unsigned char i2c_RevByte(void);

#endif /* IIC_H_ */
