#include <avr/io.h> 
#include <avr/interrupt.h>
//#include <util/delay.h>
#include <stdio.h>

unsigned int count;
unsigned char command[30];
//unsigned int bl;

//chuong trinh con phat du lieu 
void uart_char_tx(unsigned char chr){ 
    if(chr == '\n') uart_char_tx('\r');
	while (bit_is_clear(UCSRA,UDRE)) {}; //cho den khi bit UDRE=1     
            UDR=chr;
}

static FILE uartstd = FDEV_SETUP_STREAM(uart_char_tx, NULL, _FDEV_SETUP_WRITE);
void uartInit(void)
	{     
	//set baud, 9600 ung voi f=16Mhz, xem bang 70 trang 165, Atmega32 datasheet 
    UBRRH=0;     
    UBRRL=51;
     
    //set khung truyen va kich hoat bo nhan du lieu 
    UCSRA=0x00; 
    UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0); 
    UCSRB= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	stdout = &uartstd;
	sei();
}

void printptr ( unsigned char * pbuff, int ilent)
{
 	int i = 0;
	while (i<ilent)
	{
		uart_char_tx(pbuff[i]);
		i++;
	}

}
		
ISR(SIG_UART_RECV)
{ //trinh phuc vu ngat USART hoan tat nhan  
command [count+3] = UDR;
//	printf("%u\r\n",command[count+3]);
	
	if (command [count+3]==13)
		{
			int er = uart_received(command +3,count);
			if (er) printf("\nBad Command\n-> ");
			else printf("\n");//printf("\n-> ");
			count = 0;
			clear();
		}
	else 
	{
		uart_char_tx(command [count+3]);
		count = (count + 1) %29;
	}
}

void proc()
{
		
}

void clear()
{
	for (int i = 0; i < 30; i++)
		command[i]= 0;
}

unsigned int findstr(char * str,unsigned int lens, unsigned char * buffer, unsigned int lenb)
{
	for(int i = 0; i <= lenb;i++)
	{
		for (int j = 0; j <= lens; j++)
		{
			if (str[j] != buffer[i+j])
				j = lens+1;
			//printf("\n%u",j);
			if (j == lens - 1)
				return i;
		}
		
	}
	return (-1);
}

int is_command(unsigned char * str)
{
	int i = 0;
	while (str[i] != 0) {
		if (str[i] != command[i + 3])
			return 0;
		i++;
	}
	return 1;
}

