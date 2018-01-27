/*
 * com_protocol.c
 *
 *  Created on: 2017Äê12ÔÂ23ÈÕ
 *      Author: leo
 */
#include "UARTA0.h"
//90 command
extern unsigned char component_gas_setting;//1,2,3,4,5,6,7
extern unsigned char bas_gas_setting;//1,2
extern unsigned char max_number_div_100;//0 1 2 3 4
extern unsigned char max_number_div_10; //0-9
extern unsigned char max_number_div_1;//
extern unsigned char gas_concentration_flag;
extern unsigned char gas_concentration_PPM_INT;
extern unsigned char gas_concentration_PPM_POINT;
extern unsigned char gas_concentration_PPM_FRACTION0;
extern unsigned char gas_concentration_PPM_FRACTION1;
extern unsigned char gas_concentration_PPM_FRACTION2;
extern unsigned char gas_concentration_PPM_FRACTION3;
extern unsigned char gas_concentration_PPM_E;
extern unsigned char gas_concentration_PPM_flag1;
extern unsigned char gas_concentration_PPM_10_1;
extern unsigned char gas_concentration_PPM_10_2;

//91 command
extern unsigned char division_ration_100;
extern unsigned char division_ration_10;
extern unsigned char division_ration_1;

extern unsigned char function_selected;
void stop_function_response(void)
{
    unsigned char data[5];
	//stop GD

	//stop MFC

	//stop CC

	//send response
    data[0] = '8';
    data[1] = '0';
    data[2] = 'O';
    data[3] = 'K';
    data[4] = 0x0D;
    USCI_A0_TX(data,5);
}

void select_function(unsigned char temp)//cc or GDC
{

	unsigned char data[5];
	function_selected = temp;

	//send response
    data[0] = '8';
    data[1] = '1';
    data[2] = 'O';
    data[3] = 'K';
    data[4] = 0x0D;
    USCI_A0_TX(data,5);

}

void component_gas_setting_90(void)
{
	unsigned char data[5];

	//send response
    data[0] = '9';
    data[1] = '0';
    data[2] = 'O';
    data[3] = 'K';
    data[4] = 0x0D;
    USCI_A0_TX(data,5);

}

void division_ratio_set_91(void)
{
	unsigned char data[5];

	//send response
    data[0] = '9';
    data[1] = '1';
    data[2] = 'O';
    data[3] = 'K';
    data[4] = 0x0D;
    USCI_A0_TX(data,5);

}

void set_conversion_factor_B2(void)//??????????????????????????????
{

}

void parse_command(void)
{
	unsigned char temp[2];
	if(receive_queue.command_complete_flag)
	{
        temp[0] = receive_queue.data[receive_queue.head];
        receive_queue.head +=1;
        if(receive_queue.head >= QUEUE_SIZE)
        	receive_queue.head = 0;
        temp[1] = receive_queue.data[receive_queue.head+1];
        receive_queue.head +=1;
        if(receive_queue.head >= QUEUE_SIZE)
        	receive_queue.head = 0;
        if((temp[0] == '8') && (temp[0] == '0'))//Stop function
        {
            temp[0] = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            if(temp[0] == 0x0D)
            {
            	stop_function_response();
            }

        }else if((temp[0] == '8') && (temp[0] == '1'))
        {
            temp[0] = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;
            temp[1] = receive_queue.data[receive_queue.head+1];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            if(temp[1] == 0x0D)
            {
            	select_function(temp[0]);
            }

        }else if((temp[0] == '8') && (temp[0] == '2'))
        {

        }else if((temp[0] == '8') && (temp[0] == '3'))
        {

        }else if((temp[0] == '8') && (temp[0] == '4'))
        {

        }else if((temp[0] == '8') && (temp[0] == '5'))
        {

        }else if((temp[0] == '9') && (temp[0] == '0'))//component gas setting
        {

        	component_gas_setting = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            bas_gas_setting = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            max_number_div_100 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            max_number_div_10 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            max_number_div_1 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_flag = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_INT = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_POINT = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_FRACTION0 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_FRACTION1 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_FRACTION2 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_FRACTION3 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_E = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_flag1 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_10_1 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            gas_concentration_PPM_10_2 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            temp[1] = receive_queue.data[receive_queue.head+1];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            if(temp[1] == 0x0D)
            {
            	component_gas_setting_90();
            }



        }else if((temp[0] == '9') && (temp[0] == '1'))
        {
        	division_ration_100 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            division_ration_10 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            division_ration_1 = receive_queue.data[receive_queue.head];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            temp[1] = receive_queue.data[receive_queue.head+1];
            receive_queue.head +=1;
            if(receive_queue.head >= QUEUE_SIZE)
            	receive_queue.head = 0;

            if(temp[1] == 0x0D)
            {
            	division_ratio_set_91();
            }


        }else if((temp[0] == '9') && (temp[0] == '2'))
        {

        }else if((temp[0] == '9') && (temp[0] == '3'))
        {

		}else if((temp[0] == '9') && (temp[0] == '4'))//????????????????????????????????????????
        {

		}else if((temp[0] == 'A') && (temp[0] == '0'))
		{

		}else if((temp[0] == 'A') && (temp[0] == '1'))
		{

		}else if((temp[0] == 'A') && (temp[0] == '2'))
		{

		}else if((temp[0] == 'A') && (temp[0] == '3'))
		{

		}else if((temp[0] == 'B') && (temp[0] == '6'))
		{

		}else if((temp[0] == 'B') && (temp[0] == '7'))
		{

		}else if((temp[0] == 'B') && (temp[0] == '8'))
		{

		}else if((temp[0] == 'B') && (temp[0] == '9'))
		{

		}else if((temp[0] == 'B') && (temp[0] == 'A'))
		{

		}else if((temp[0] == 'B') && (temp[0] == 'B'))
		{

		}else if((temp[0] == 'B') && (temp[0] == 'C'))
		{

		}else if((temp[0] == 'B') && (temp[0] == 'D'))
		{

		}
        receive_queue.command_complete_flag--;
	}
}
