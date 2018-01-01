#include <msp430.h> 

#include "IO_Config.h"
#include "SPI.h"
#include "UARTA0.h"

//operation mode

#define NORMAL_OPERATION_MODE 0
#define INITIAL_MODE_1_2      1
#define INITIALL_MODE_2       3
#define INITIAL_MODE_1_1      4

unsigned char switch_operation_flag = 0;
/*
 * main.c
 */
unsigned char set_operation_mode(void)
{
	switch(switch_operation_flag)
	{
	case NORMAL_OPERATION_MODE:
		break;
	case INITIAL_MODE_1_2:
		break;
	case INITIALL_MODE_2:
		break;
	case INITIAL_MODE_1_1:
	    break;
	default:
		break;
	}
}

void system_init(void)
{
    unsigned char temp = 0;
	//set baudrate
    temp = Get_Baudrate();
	Set_baudrate(temp);
	//set opertion mode
	set_operation_mode();
}



int main(void) {

      volatile unsigned int i;

	  WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
	  FLL_CTL0 |= XCAP11PF;                     // Configure load caps

	  // Wait for xtal to stabilize
	  do
	  {
	    IFG1 &= ~OFIFG;                           // Clear OSCFault flag
	    for (i = 0x47FF; i > 0; i--);             // Time for flag to set
	  }
	  while ((IFG1 & OFIFG));                   // OSCFault flag still set?

	  for(i=2100;i>0;i--);                      // Now with stable ACLK, wait for
	                                              // DCO to stabilize.

	  IO_init();
	  SPI_init();

	  while(1)
	  {

	  }
	return 0;
}
