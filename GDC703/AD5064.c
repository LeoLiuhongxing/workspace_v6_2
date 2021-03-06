#include <msp430.h>
#include "AD5064.h"
#include "SPI.h"

#define AD5064_MAX_DAC_CHANNELS			8
#define AD5064_MAX_VREFS			    4

#define AD5064_ADDR(x)				((x) << 20)
#define AD5064_CMD(x)				((x) << 24)

#define AD5064_ADDR_ALL_DAC			0xF

#define AD5064_CMD_WRITE_INPUT_N		    0x0
#define AD5064_CMD_UPDATE_DAC_N			    0x1
#define AD5064_CMD_WRITE_INPUT_N_UPDATE_ALL	0x2
#define AD5064_CMD_WRITE_INPUT_N_UPDATE_N	0x3
#define AD5064_CMD_POWERDOWN_DAC		    0x4
#define AD5064_CMD_CLEAR			        0x5
#define AD5064_CMD_LDAC_MASK			    0x6
#define AD5064_CMD_RESET			        0x7
#define AD5064_CMD_CONFIG			        0x8

#define AD5064_CMD_RESET_V2			        0x5
#define AD5064_CMD_CONFIG_V2			    0x7

#define AD5064_CONFIG_DAISY_CHAIN_ENABLE	BIT(1)
#define AD5064_CONFIG_INT_VREF_ENABLE		BIT(0)

#define AD5064_LDAC_PWRDN_NONE			0x0
#define AD5064_LDAC_PWRDN_1K			0x1
#define AD5064_LDAC_PWRDN_100K			0x2
#define AD5064_LDAC_PWRDN_3STATE		0x3

void ad5064_spi_write(unsigned int cmd,	unsigned int addr, unsigned int val)
{
	unsigned int temp;

	temp = (AD5064_CMD(cmd) | AD5064_ADDR(addr) | val);
	spi_write(0, &temp, 4);
}


void ad5064_write_raw(unsigned char channel, unsigned int value)
{

	value = value<<4;
	ad5064_write(AD5064_CMD_WRITE_INPUT_N_UPDATE_N, channel, value);

}
