/*
 * Author: Snehasish Kar
 * Date: 14/08/2023
 * Desc: Header file for UART  
 */

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Mask for setting UBRR 
#define UBRRnH_MASK 0xf00
#define UBRRnL_MASK 0xff

//structure for UART Configuartion
struct uartConfig
{
    uint8_t mode;
    uint8_t parity;
    uint8_t stopBit;
    uint8_t dataBit; 
    uint16_t baudrate;
};

enum UART_MODE {Asynchronous, Synchronous};
enum UART_PARITY {NO_PARITY, EVEN_PARITY, ODD_PARITY};

void UART_inital_configuration(struct uartConfig *__UART_CONFIGURATION);
void set_baudRate(uint16_t *baudrate);
void readUART_Poll(uint8_t *buffer, int32_t *len, struct uartConfig *__UART_CONFIGURATION);
void transmitUART_Poll(uint8_t *buffer, int32_t *len, struct uartConfig *__UART_CONFIGURATION);
void popRingBuffer(uint8_t *buffer, int32_t *len);

extern int8_t dataReady;


