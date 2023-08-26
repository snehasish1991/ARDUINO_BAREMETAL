/*
 * Author: Snehasish Kar
 * Date: 14/08/2023
 * Desc:
 */

#include "../include/uart_devel.h"
#include <string.h>

#define __USE_INTERUPPT 1
#ifndef FOSC
	#define FOSC 16000000UL //Arduino has a 16MHz clock
	#warning Considering Default clock of 16MHz
#endif
#define F_CPU FOSC
#define calc_UBRR(x,y) y = (FOSC/16/x) - 1
#define MTU 10
uint8_t ringBuff[2*MTU] ={0x00};
int8_t startIndex = 0x00, currentIndex = 0x00, dataReady = 0x00;

//function to set baud rate
void set_baudRate(uint16_t *baudrate) {
    uint16_t _UBRRn = 0x00; //(int16_t)(FOSC/(16/(__baudrate))) - 1;
	calc_UBRR(*baudrate, _UBRRn);
	UBRR0H = (uint8_t)((_UBRRn & UBRRnH_MASK)>>8);
	UBRR0L = (uint8_t)(_UBRRn & UBRRnL_MASK);
}

//function to set initial configuration
void UART_inital_configuration(struct uartConfig *__UART_CONFIGURATION) {
	set_baudRate(&__UART_CONFIGURATION->baudrate);
    //UCSR0B is a 8bit Register where each bit means a configuration
    //see ATMEGA_328p_IO.h for reference.
	if(!__USE_INTERUPPT)
		UCSR0B = (1<<RXEN0)|(1<<TXEN0); //enable both receiver and tranmitter
	else {
		startIndex = currentIndex = 0x00;
		UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0); //enable both receiver and tranmitter, also enable interupt for Rx and User Data Registry Empty
		sei();
	}
    // Set frame format: 8data, 2stop bit */
    //set data format
    //case 5: 5bit
    //case 6: 6bit
    //case 7: 7bit
    //case 8: 8bit
    switch(__UART_CONFIGURATION->dataBit)
    {
        case 5: break;
        case 6: UCSR0C = 0x1<<UCSZ00;
                break;
        case 7: UCSR0C = 0x2<<UCSZ00;
                break;
        case 8: UCSR0C = 0x3<<UCSZ00;
                break;
        case 9: UCSR0C = 0x7<<UCSZ00;
                break;
    }
    //stop bit configuration
    //see http://exploreembedded.com/wiki/UART_Programming_with_Atmega128 
    //for more clarity
    //case 1: 1 bit for stop bit
    //case 2: 2 bits for stop bit
    switch(__UART_CONFIGURATION->stopBit)
    {
        case 1: break;
        case 2: UCSR0C|= 0x1<<UCSZ00;
                break;
    }
    //parity configuration
    //see http://exploreembedded.com/wiki/UART_Programming_with_Atmega128 
    //for more clarity
    //case 0: No parity
    //case 1: even parity
    //case 2: odd parity
    switch(__UART_CONFIGURATION->parity) {
        case 0: break; 
        case 1: UCSR0C|= 0x2<<UPM00;
        case 2: UCSR0C|= 0x3<<UPM00;
    }    
    //mode configuration
    //see http://exploreembedded.com/wiki/UART_Programming_with_Atmega128 
    //for more clarity
    //case 0: Asynchronous mode
    //case 1: Synchronous mode
    switch(__UART_CONFIGURATION->mode) {
        case 0: break;
        case 1: UCSR0C|= 0x1<<UMSEL00;
                break;
    }
}

//function to transmit byte by byte over UART channel using polling
void transmitUART_Poll(uint8_t *buffer, int32_t *len, struct uartConfig *__UART_CONFIGURATION) {
    int32_t i = 0x00;
	uint8_t byte = 0x00;
    switch(__UART_CONFIGURATION->dataBit) {
        case 5:
        case 6:
        case 7:
        case 8: for(i=0;i<(*len);i++) {
                    while (!(UCSR0A & (1<<UDRE0))); //wait for trasnmit buffer to be empty
					byte = (uint8_t)buffer[i];
                    UDR0 = byte; //(uint8_t)buffer[i]; //copy data to register to be trasnmitted
                    while (!(UCSR0A & (1<<TXC0))); //check if transmission is complete
                }
                break;
        case 9: //TODO
                /*for (i=0;i<len;i++) {
                    while (!(UCSR0A & (1<<UDRE0))); //wait for trasnmit buffer to be empty
                    
                }*/
                break;
    }
}

//function to receive byte by byte over UART channel using polling
void readUART_Poll(uint8_t *buffer, int32_t *len, struct uartConfig *__UART_CONFIGURATION) {
    int32_t i = 0x00;
	switch(__UART_CONFIGURATION->dataBit) {
        case 5:
        case 6:
        case 7:
        case 8: for(i=0;i<(*len);i++) {
                    while(!(UCSR0A & (1<<RXC0))); //wait for stop bit to be received
                    buffer[i] = UDR0; //copy received byte to buffer
                }
                break;
        case 9: //TODO for databit size 9
                break;
    }
    
}

void popRingBuffer(uint8_t *buffer, int32_t *len) {
	memcpy(buffer, (const void *)ringBuff[currentIndex], sizeof(uint8_t)*MTU);
	dataReady = 0x00;
	*len = MTU;
	currentIndex+= MTU;
	if(currentIndex>=(2*MTU)) {
		currentIndex = 0x00;
	}
}

ISR(USART_RX_vect) {
	ringBuff[startIndex] = UDR0;
	if((startIndex%MTU)==0x00)
		dataReady = 0x1;
	startIndex++;
	if(startIndex>=(2*MTU)) 
		startIndex = 0x00;	
}
