

#ifndef __MAIN_H
#define __MAIN_H

//------------KHAI BAO THU VIEN--------------
//#include <mega8.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr\io.h>

//--------------CAU HINH I/O-----------------
// PORTB ------------------------------------
// Chan truyen du lieu
#define Data_Out PORTB
#define RF_OUT 0
#define RF_IN 1
#define Data_In (PINB&(1<<RF_IN))

// Lenh truyen va nhan
#define M_Data_Out(x)  (Data_Out = (Data_Out & ~_BV(RF_OUT)) | ((x) << RF_OUT))


// Bat tat chan
#define PortB(y,x)  (PORTB = (PORTB & ~(1<<y)) | ((x) << y))
#define PortD(y,x)  (PORTD = (PORTD & ~(1<<y)) | ((x) << y))
#define PortC(y,x)  (PORTC = (PORTC & ~(1<<y)) | ((x) << y))
#define trnb(x)  ( PORTB = (PORTB & ~(1<<x)) | ((~PORTB)&(1<<x)) )
#define trnd(x)  ( PORTD = (PORTD & ~(1<<x)) | ((~PORTD)&(1<<x)) )
#define trnc(x)  ( PORTC = (PORTC & ~(1<<x)) | ((~PORTC)&(1<<x)) )

//Light output
#define P_OUT(y,x) (PORTD = (PORTD & ~(1<<y)) | ((x) << y))
#define P_TURN(x) ( PORTD = (PORTD & ~(1<<x)) | ((~PORTD)&(1<<x)))

#define LIGHT1 2 //PD2
#define LIGHT2 3 //PD3
#define LIGHT3 4 //PD4
#define LIGHT4 5 //PD5
#define LIGHT5 6 //PD6
#define LIGHT6 7 //PD7

//Light input
#define SW1 0
#define SW2 1
#define SW3 2
#define SW4 3
#define SW5 4
#define SW6 5

#define sw_1 (PINC&(1<<SW1))
#define sw_2 (PINC&(1<<SW2))
#define sw_3 (PINC&(1<<SW3))
#define sw_4 (PINC&(1<<SW4))
#define sw_5 (PINC&(1<<SW5))
#define sw_6 (PINC&(1<<SW6))

#define sensor_in (PINC&(1<<SW2))
#define get_code (PIND&(1<<0))

//User button
//#define UB1 6
//#define UB2 7
//#define ub_1 (PINB&(1<<UB1))
//#define ub_2 (PINB&(1<<UB2))

//Inditation LED
#define LED 2
#define I_LED(x) (PortB(LED,x))

#define ON 0
#define OFF 1
#define COMMAND 6
#define CODE 50 //dia chi cua code trong bo nho eeprom


#define TIME 275



// PORTC ------------------------------------
// PORTD ------------------------------------

#endif
// ------------------END OF FILE-------------
// ------------------------------------------
