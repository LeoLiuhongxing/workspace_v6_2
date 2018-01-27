#include <msp430.h> 

#include "IO_Config.h"
#include "SPI.h"
#include "UARTA0.h"
#include "com_protocol.h"
#include "TimerA.h"
#include "MCP23S17.h"
#include "AD5064.h"
#include "ad717x.h"
#include "led_driver.h"
#include "DS18B20.h"
//operation mode

#define NORMAL_OPERATION_MODE 0
#define INITIAL_MODE_1_2      1
#define INITIALL_MODE_2       3
#define INITIAL_MODE_1_1      4
#define TEMPRATURE 50 //?????????????????????????????

#define GAS_DIVDER_FUNCTION 1
#define CONVERTER_FUNCTION  0

unsigned char function_selected = GAS_DIVDER_FUNCTION;

unsigned char switch_operation_flag = 0;

unsigned char half_hour_minutes_timer = 0;

unsigned char warm_up_flag = 0;
unsigned char warm_up_Led_state = 0;
//90 command
unsigned char component_gas_setting = 0;//1,2,3,4,5,6,7
unsigned char bas_gas_setting = 0;//1,2
unsigned char max_number_div_100 = 0;//0 1 2 3 4
unsigned char max_number_div_10 = 0; //0-9
unsigned char max_number_div_1 = 0;//
unsigned char gas_concentration_flag = '+';
unsigned char gas_concentration_PPM_INT = 0;
unsigned char gas_concentration_PPM_POINT = '.';
unsigned char gas_concentration_PPM_FRACTION0 = 0;
unsigned char gas_concentration_PPM_FRACTION1 = 0;
unsigned char gas_concentration_PPM_FRACTION2 = 0;
unsigned char gas_concentration_PPM_FRACTION3 = 0;
unsigned char gas_concentration_PPM_E = 'E';
unsigned char gas_concentration_PPM_flag1 = '+';
unsigned char gas_concentration_PPM_10_1 = 0;
unsigned char gas_concentration_PPM_10_2 = 0;

//91 command
unsigned char division_ration_100 = 0;
unsigned char division_ration_10 = 0;
unsigned char division_ration_1 = 0;



/*
 * main.c
 */
void set_operation_mode(void)
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
      unsigned int tempature = 0;

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
	  system_init();
	  TimerA_Init();
	  InitMCP_Output();
	  InitMCP_Input();
	  //AD717X_Setup();
	  UART0_Init();

	  //power led on
	  led_control_on(1,POWER_LIGHT_ON);
      while(1)
	  {
		  //
		  parse_command();
		  //timer
		  if(interrupt_count == 1)//1 second
		  {
			  interrupt_count = 0;

			  //Led flicker
			  if(warm_up_flag == 0)
			  {
				  half_hour_minutes_timer++;
				  if(function_selected == GAS_DIVDER_FUNCTION)
				  {
                      if(warm_up_Led_state == 0)
                      {
                    	  led_control_on(warm_up_Led_state,GD_LIGHT_ON);
                    	  warm_up_Led_state = 1;
                      }else
                      {
                    	  warm_up_Led_state = 0;
                    	  led_control_on(warm_up_Led_state,GD_LIGHT_ON);
                      }
				  }else if(function_selected == CONVERTER_FUNCTION)
				  {
                      if(warm_up_Led_state == 0)
                      {
                    	  led_control_on(warm_up_Led_state,CC_LIGHT_ON);
                    	  warm_up_Led_state = 1;
                      }else
                      {
                    	  warm_up_Led_state = 0;
                    	  led_control_on(warm_up_Led_state,CC_LIGHT_ON);
                      }

				  }
			  }else
			  {
				  if(function_selected == GAS_DIVDER_FUNCTION)
				  {
					  led_control_on(1,GD_LIGHT_ON);
				  }else if(function_selected == CONVERTER_FUNCTION)
				  {
					  led_control_on(1,CC_LIGHT_ON);
				  }
			  }

		  }

		  if(half_hour_minutes_timer == 1800)//30 minutes
		  {
			  half_hour_minutes_timer =0;
			  //warm up end
			  warm_up_flag = 1;
		  }

		  //check temperature
		  tempature = Do1Convert();
		  if(tempature & 0xFF00 == 0)
		  {
			 tempature = tempature>>4;
			 if(tempature > TEMPRATURE)
			 {
				 P9OUT |= BIT0+BIT1;//FAN1 AND FAN2
			 }else
			 {
				 P9OUT ^=~( BIT0+BIT1);//FAN1 AND FAN2
			 }
		  }

	  }
	return 0;
}
