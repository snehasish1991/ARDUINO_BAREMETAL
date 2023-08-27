/*
 * ARDUINO_BAREMETAL.c
 *
 * Created: 24-08-2023 17:26:52
 * Author : snehasish
 */ 


#include <inttypes.h>
#include <string.h>
#include "Drivers/include/uart_devel.h"

void setup_peripherals(struct uartConfig *__UART_CONFIGURATION) 
{

	/***********UART Initial Configuration begin*********************/
	
	
	__UART_CONFIGURATION->mode = Asynchronous;
	__UART_CONFIGURATION->parity = NO_PARITY;
	__UART_CONFIGURATION->stopBit = 1;
	__UART_CONFIGURATION->dataBit = 8;
	__UART_CONFIGURATION->baudrate = 9600;
	UART_inital_configuration(__UART_CONFIGURATION);

	/***********UART Initial Configuration ends*********************/
}

int32_t main(void)
{
    /* Replace with your application code */
	char buffer[20]={0x00}; //{0x01, 0x02, 0x03, 0x04, 0x05};
	struct uartConfig __UART_CONFIGURATION;
	setup_peripherals(&__UART_CONFIGURATION);
	int32_t len = 0x00; //strlen("hello world");
    while (1) 
    {
		_delay_ms(10000);
    }
	return 0x00;
}

