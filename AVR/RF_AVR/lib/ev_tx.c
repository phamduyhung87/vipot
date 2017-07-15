  

#include "rf_at8.h"

// ================================================
void M_Sent_Bit(unsigned char i)
{
/*
     Ma hoa Manchester:
     Bit 1 --> 10
     Bit 0 --> 01
*/
        if(i)  // toc do truyen 1K
        {
                M_Data_Out(1);
                _delay_us(TIME*3);  
                M_Data_Out(0);
                _delay_us(TIME);
        }                     
        else   // toc do truyen 1K
        {
                M_Data_Out(1);
                _delay_us(TIME);    
                M_Data_Out(0);
                _delay_us(TIME*3);
        }                     
        
}  
// ================================================
void M_Pulse_Start()    // Truyen bit 1 co toc do 4ms de bat dau khung truyen
{
 	M_Data_Out(1);
	_delay_us(TIME*30);    
	M_Data_Out(0);
	_delay_us(TIME);
}                     
 
// ================================================
void M_Sent_Byte(unsigned char byte)
{
        unsigned char temp,i;
        temp=byte;
        for(i=0;i<8;i++)
        {
               // M_Sent_Bit((temp>>i)&0x01);      truyen tu bit thap den bit cao
               M_Sent_Bit(temp&(0x80>>i));      // truyen tu bit cao den bit thap
        }
}

// ================================================
void M_Sent_Array(unsigned char *array,unsigned char length)
{
        unsigned char i;
        for(i=0;i<length;i++)
        {
                M_Sent_Byte(array[i]);
        }
		M_Sent_Byte(13);
}

// ================================================
void M_Sent_Frame(unsigned char *data,unsigned char length)
{  
//        M_Data_Start();
        M_Pulse_Start();
       M_Sent_Array(data,length);
		_delay_us(TIME*35);

		M_Pulse_Start();
       M_Sent_Array(data,length);
	   _delay_us(TIME*35);
/*
		M_Pulse_Start();
       M_Sent_Array(data,length);
	   _delay_ms(10);


		M_Pulse_Start();
        M_Sent_Array(data,length);*/
}

// ------------------END OF FILE-------------------
// ------------------------------------------------
