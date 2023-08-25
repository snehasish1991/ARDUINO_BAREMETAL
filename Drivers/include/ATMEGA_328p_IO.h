
/*
 * Author: Snehasish Kar
 * Date: 15/08/2023
 * Desc: Header file for IO map  
 */

#include <inttypes.h>
#if 0
#define _SFR_READ_16_Bits(address) (*(volatile uint16_t *) address)
#define _SFR_READ_8_Bits(address) (*(volatile uint8_t *) address)

//UART Registers
//address as per ATMEGA user manual:
//https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf

#define UBRR0	_SFR_READ_16_Bits(0xC4) 
#define UBRR0H _SFR_READ_8_Bits(0xc5)
#define UBRR0L _SFR_READ_8_Bits(0xc4)

//for Pin numbers of the register see the below link:
//http://exploreembedded.com/wiki/UART_Programming_with_Atmega128

#define UCSR0B _SFR_READ_8_Bits(0xc1)
#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5 
#define RXEN0  4
#define TXEN0  3 
#define UCSZ02 2 
#define RXB80  1
#define TXB80  0

#define UCSR0C _SFR_READ_8_Bits(0xc2)
#define UMSEL01 7
#define UMSEL00 6
#define UPM01	5
#define UPM00	4
#define USBS0	3
#define UCSZ01	2
#define UCSZ00	1
#define UCPHA0  1
#define UCPOL0	0

#define UCSR0A _SFR_READ_8_Bits(0xc0)
#define RXC0	7
#define TXC0	6
#define UDRE0	5
#define FE0	    4
#define DOR0	3
#define UPE0	2
#define U2X0	1
#define MPCM0	0

#define UDR0 _SFR_READ_8_Bits(0xc6)
#endif