
#include "../lib/rf_at8.h"
#include "../lib/ev_tx.h"
#include "../lib/ev_rx.h"
#include "../lib/uart.h"
#include <avr\io.h>
#include "avr/eeprom.h"


uint8_t Mcode = 10;
unsigned char code[COMMAND+1];
unsigned char coderf[COMMAND+1];
unsigned char sw1 = 1;
unsigned char sw2 = 1;
unsigned char sw3 = 1;
unsigned char sw4 = 1;
unsigned char sw5 = 1;
unsigned char sw6 = 1;
unsigned char sensorin = 1;

int uart_received (unsigned char * uart_command, unsigned int ilent)
{
	if(findstr("rf ",3,uart_command,ilent)!=(-1))
	{
		int i = findstr("rf ",3,uart_command,ilent);
		//printf("\n");
		//printptr(uart_command + 3 + i,ilent - 3 - i);
		M_Sent_Frame(uart_command + 3 + i,ilent - 3 - i);
	}
}

void gpioInit(void){
	//set ouput pin
	DDRB = (1<<LED)|(1<<RF_OUT);
	DDRD = (1<<LIGHT1)|(1<<LIGHT2)|(1<<LIGHT3)|(1<<LIGHT4)|(1<<LIGHT5)|(1<<LIGHT6);
	PORTD = (1<<LIGHT2)|(1<<LIGHT3)|(1<<LIGHT4)|(1<<LIGHT5)|(1<<LIGHT6);
	//indication LED on
	I_LED(0);
	//initial input pin to High
	PORTC = (1<<SW1)|(1<<SW2)|(1<<SW3)|(1<<SW4)|(1<<SW5)|(1<<SW6); // Light
	PORTB = (1<<LED); //User button
	PORTD |= (1<<0); // get code button
}
void getCode(void){
	// Khai bao cac mang chua du lieu can truyen di
	char str[COMMAND + 1];
	uint8_t datalen;	

	// Nhan code tu bo nho EPPROM
	code [0] = eeprom_read_byte (Mcode);
	code [1] = eeprom_read_byte (Mcode + 1); 
	code [2] = eeprom_read_byte (Mcode + 2);
	code [3] = eeprom_read_byte (Mcode + 3);
	code [4] = eeprom_read_byte (Mcode + 4);
	code [5] = eeprom_read_byte (Mcode + 5);
	code [6] = 0;

	if ((code [0] == 0xFF)&&(code [1] == 0xFF)&&(code [2] == 0xFF))
	{
	//	set_default();
		code [0] = 'a';
		code [1] = 'b'; 
		code [2] = 'c';
		code [3] = 'd';
		code [4] = 'e'; 
		code [5] = 'f';
		printf("code = default = abcdef\n");
	}
	else
	{
		printf("code = %c%c%c%c%c%c\n", code[0], code[1], code[2], code[3], code[4], code[5]);
	}
}
int main(void)
{
	// Khoi tao PORT IN/OUT
	gpioInit();
	// Khoi tao uart
	uartInit();
	I_LED(ON);
	printf("Start\n");
	I_LED(OFF);
	getCode();

	// Khai bao cac mang cac ma thiet bi
	// ban tin rf
	char str[15];
	uint8_t rf_len;

	
	while (1)
	{
		// Nhan duoc du lieu
		//printf("\n%d",PIND);
		
		if ((sensor_in &&(sensorin == 0)) || ((sensor_in == 0) &&(sensorin)))
		{
			I_LED(ON);
			printf("\nsensor %d",sensorin);
			sensorin = sensor_in;
			if(sensorin)
				code[6] = '0';
			else
			{
				code[6] = '9';
			}
			M_Sent_Frame(code,7);
			I_LED(OFF);
		}
		if ((sw_1 &&(sw1 == 0)) || ((sw_1 == 0) &&(sw1)))
		{
			printf("\nL1 %d",sw1);
			sw1 = sw_1;
			P_TURN (LIGHT1);
		}
	}
}


// ------------------END OF FILE-------------
// ------------------------------------------
