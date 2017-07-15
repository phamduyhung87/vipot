
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
	for (int i = 0; i < COMMAND; i++){
		code [i] = eeprom_read_byte (Mcode + i);
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
					if (findstr(coderf,COMMAND,str,COMMAND)!=(-1))
						coderf[6]++;
					else
						coderf[6]=0;
					if (coderf[6]==3){
						for (int i = 0 ; i < COMMAND; i++){
							eeprom_write_byte (Mcode + i,str[i]);
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
		}
		else {
			if(rf_len)
		    {   
	 			I_LED(ON);
				printptr(str,COMMAND+1);
				printf("\n");
				if (findstr(code,COMMAND,str,COMMAND + 1)!=(-1))
				{ 
					if (str[COMMAND] == '1')
					{ P_TURN(LIGHT1);printf("L1\n"); sensorin = sensor_in; _delay_ms(50);}
					else
					if (str[COMMAND] == 'a')
					{P_OUT (LIGHT1,0);printf("L10\n"); sensorin = sensor_in; _delay_ms(50);}
					else
					if (str[COMMAND] == 'A')
					{P_OUT (LIGHT1,1);printf("L11\n"); sensorin = sensor_in; _delay_ms(50);}
					else
					if (str[COMMAND] == '0'){
						printf("ALL-0\n");
						P_OUT (LIGHT1,0);
						sensorin = sensor_in;
						_delay_ms(50);
					}
					else
					if (str[COMMAND] == '9'){
						printf("ALL-1\n");
						P_OUT (LIGHT1,1);
						sensorin = sensor_in;;
						_delay_ms(50);
					}
				}
				I_LED(OFF);
			}
			if (sensor_in == 0) {
				I_LED(ON);
				sensorin = sensor_in;
				code[6] = '9';
				M_Sent_Frame(code,7);
				I_LED(OFF);
				_delay_ms(1000);			
			}
			if (sensor_in &&(sensorin == 0)){
				sensorin = sensor_in;
				code[6] = '0';
				M_Sent_Frame(code,7);
			}
			if ((sw_1 &&(sw1 == 0)) || ((sw_1 == 0) &&(sw1)))
			{
				printf("\nL1 %d",sw1);
				sw1 = sw_1;
				P_TURN (LIGHT1);
				code[6] = '9';
				M_Sent_Frame(code,7);
			}
			I_LED(OFF);
		}
	}
}


// ------------------END OF FILE-------------
// ------------------------------------------
