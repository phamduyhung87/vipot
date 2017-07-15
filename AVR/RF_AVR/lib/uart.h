//----------------------------------------------------------------------------
// Writen by NTTam - PTITHCM
//----------------------------------------------------------------------------
#ifndef UART_H
#define UART_H

#include <avr/pgmspace.h>
//----------------------------------------------------------------------------
#define UART_TX_BUFFER_SIZE		8
#define UART_RX_BUFFER_SIZE		8
//--------------------------------------------------------------------------------------
#ifndef UART_INTERRUPT_HANDLER
#define UART_INTERRUPT_HANDLER	SIGNAL
#endif
//define for ATmega32 register
#define USR UCSRA
#define UCR UCSRB
#define UBRR UBRRL
#define EICR EICRB
#define USART_RX USART_RXC_vect  
#define USART_TX USART_TXC_vect  
//--------------------------------------------------------------------------------------

void uartInit(void);
void printptr ( unsigned char * pbuff, int ilent);

int printfP(const prog_char *format, ...);

int uart_received (unsigned char * uart_command, unsigned int ilent);
int is_command(unsigned char * str);
unsigned int findstr(char * str,unsigned int lens, unsigned char * buffer, unsigned int lenb);

//--------------------------------------------------------------------------------------
#endif //UART_H
