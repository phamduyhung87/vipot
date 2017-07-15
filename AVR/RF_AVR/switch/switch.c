
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

int uart_received (unsigned char * uart_command, unsigned int ilent)
{
	if(findstr("rf ",3,uart_command,ilent)!=(-1))
	{
		int i = findstr("rf ",3,uart_command,ilent);
		//printf("\n");
		//printptr(uart_command + 3 + i,ilent - 3 - i);
		M_Sent_Frame(uart_command + 3 + i,ilent - 3 - i);
	}
	return 0;
}

void gpioInit(void){
	//set ouput pin
	DDRB = (1<<LED)|(1<<RF_OUT);
	DDRD = (1<<LIGHT1)|(1<<LIGHT2)|(1<<LIGHT3)|(1<<LIGHT4)|(1<<LIGHT5)|(1<<LIGHT6);
	I_LED(0);
	//initial input pin to High
	PORTC = (1<<SW1)|(1<<SW2)|(1<<SW3)|(1<<SW4)|(1<<SW5)|(1<<SW6); // Light
	PORTB = (1<<LED); //User button
	PORTD |= (1<<0); // get code button
}
void getCode(void){
	// Khai bao cac mang chua du lieu can truyen di
//	char str[COMMAND + 1];

	// Nhan code tu bo nho EPPROM
	for (int i = 0; i < COMMAND; i++){
		code [i] = (unsigned char) eeprom_read_byte (Mcode + i);
	}
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
void scene(unsigned char * str, uint8_t len){
	uint8_t port = 0;
	printf("scene: ");
	printptr(str,len);
	printf("\n");
	for (int i = 0; i < len; i++){
		port = 10*port + (str[i] - '0');
	}
	printf("%d\n",port);
	if (port&(1<<7))
		{P_OUT (LIGHT1,1);}
	else
		{P_OUT (LIGHT1,0);}
	
	if (port&(1<<6))
		P_OUT (LIGHT2,1);
	else
		P_OUT (LIGHT2,0);
	
	if (port&(1<<5))
		P_OUT (LIGHT3,1);
	else
		P_OUT (LIGHT3,0);
	
	if (port&(1<<4))
		P_OUT (LIGHT4,1);
	else
		P_OUT (LIGHT4,0);
	
	if (port&(1<<3))
		P_OUT (LIGHT5,1);
	else
		P_OUT (LIGHT5,0);
	
	if (port&(1<<2))
		P_OUT (LIGHT6,1);
	else
		P_OUT (LIGHT6,0);
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
	sw1 = sw_1;
	sw2 = sw_2;
	sw3 = sw_3;
	sw4 = sw_4;
	sw5 = sw_5;
	sw6 = sw_6;

	// Khai bao cac mang cac ma thiet bi
	// ban tin rf
	unsigned char str[15];
	uint8_t rf_len;

	
	while (1)
	{
		// Nhan duoc du lieu
		//printf("\n%d",PIND);
		rf_len = M_Get_Frame(str,15);
		
		if(!get_code){
			I_LED(ON);
			if(rf_len){
				if (coderf[6]==0){
					for (int i = 0; i < COMMAND; i++){
					coderf[i] = str[i];
					}
					coderf[6]++;
				}
				else{
					if (findstr((char)coderf,COMMAND,str,COMMAND)!=(-1))
						coderf[6]++;
					else
						coderf[6]=0;
					if (coderf[6]==3){
						for (int i = 0 ; i < COMMAND; i++){
							eeprom_write_byte (Mcode + i, str[i]);
						}
						code[6]=0;
						I_LED(OFF);
						printf("new code = %c%c%c%c%c%c\n", str[0],str[1],str[2],str[3],str[4],str[5]);
						printf("reset to apply changesss\n");
						I_LED(ON);
						_delay_ms(100);
						I_LED(OFF);
						_delay_ms(1000);
					}
				}
			}
			rf_len = 0;
		}
		else {
			if(rf_len)
			{
				I_LED(ON);
				//printf("rf_len = %d\n",rf_len);
				printf("msg ");
				printptr(str,rf_len);
				printf("\r");
				if (findstr(code,COMMAND,str,COMMAND + 1)!=(-1))
				{ 
					if (str[COMMAND] == '1')
					{ P_TURN(LIGHT1);printf("L1\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == '2')
				  	{ P_TURN(LIGHT2);printf("L2\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == '3')
				  	{ P_TURN(LIGHT3);printf("L3\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == '4')
				  	{ P_TURN(LIGHT4);printf("L4\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == '5')
				  	{ P_TURN(LIGHT5);printf("L5\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == '6')
				  	{ P_TURN(LIGHT6);printf("L6\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'a')
					{P_OUT (LIGHT1,0);printf("L10\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'b')
				  	{P_OUT (LIGHT2,0);printf("L20\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'c')
				  	{P_OUT (LIGHT3,0);printf("L30\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'd')
				  	{P_OUT (LIGHT4,0);printf("L40\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'e')
				  	{P_OUT (LIGHT5,0);printf("L50\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'f')
				  	{P_OUT (LIGHT6,0);printf("L60\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'A')
					{P_OUT (LIGHT1,1);printf("L11\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'B')
				  	{P_OUT (LIGHT2,1);printf("L21\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'C')
				  	{P_OUT (LIGHT3,1);printf("L31\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'D')
				  	{P_OUT (LIGHT4,1);printf("L41\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'E')
				  	{P_OUT (LIGHT5,1);printf("L51\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == 'F')
				  	{P_OUT (LIGHT6,1);printf("L61\n"); _delay_ms(50);}
					else
					if (str[COMMAND] == '0'){
						printf("ALL-0\n");
						P_OUT (LIGHT1,0);
						P_OUT (LIGHT2,0);
						P_OUT (LIGHT3,0);
						P_OUT (LIGHT4,0);
						P_OUT (LIGHT5,0);
						P_OUT (LIGHT6,0); 					
						_delay_ms(50);
						sw2 = sw_2;
					}
					else
					if (str[COMMAND] == '9'){
						printf("ALL-1\n");
						P_OUT (LIGHT1,1);
						P_OUT (LIGHT2,1);
						P_OUT (LIGHT3,1);
						P_OUT (LIGHT4,1);
						P_OUT (LIGHT5,1);
						P_OUT (LIGHT6,1); 
						_delay_ms(50);
						sw2 = sw_2;
					}
					else
					if (str[COMMAND] == '-'){
						scene(str + COMMAND + 1,rf_len - COMMAND - 1);
					}
				}
				I_LED(OFF);
			}
			//printf("rf_len = %d\n",rf_len);
			//printf("sw 1 = %u\n",sw_1);
			//printf("sw 2 = %u\n",sw_2);
			if ((sw_1 &&(sw1 == 0)) || ((sw_1 == 0) &&(sw1)))
			{
				I_LED(ON);
				_delay_ms(100);
				printf("\nL1 %u", sw1);
				sw1 = sw_1;
				P_TURN(LIGHT1);
			}

			if ((sw_2 &&(sw2 == 0)) || ((sw_2 == 0) &&(sw2)))
			{
				I_LED(ON);
				_delay_ms(100);
				printf("\nL2");
				sw2 = sw_2;
				P_TURN(LIGHT2);
			}
			if ((sw_3 &&(sw3 == 0)) || ((sw_3 == 0) &&(sw3)))
			{
				I_LED(ON);
				_delay_ms(100);
				printf("\nL3");
				sw3 = sw_3;
				P_TURN(LIGHT3);
			}
			if ((sw_4 &&(sw4 == 0)) || ((sw_4 == 0) &&(sw4)))
			{
				I_LED(ON);
				_delay_ms(100);
				printf("\nL4");
				sw4 = sw_4;
				P_TURN(LIGHT4);
			}

			if ((sw_5 &&(sw5 == 0)) || ((sw_5 == 0) &&(sw5)))
			{
				I_LED(ON);
				_delay_ms(100);
				printf("\nL5");
				sw5 = sw_5;
				P_TURN(LIGHT5);
			}
			if ((sw_6 &&(sw6 == 0)) || ((sw_6 == 0) &&(sw6)))
			{
				I_LED(ON);
				_delay_ms(100);
				printf("\nL6");
				P_TURN(LIGHT6);
				sw6 = sw_6;
			}
			I_LED(OFF);
		}
	}
}


// ------------------END OF FILE-------------
// ------------------------------------------
