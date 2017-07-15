
#ifndef __MA_HOA_H
#define __MA_HOA_H

#include "ev_tx.h"

void M_Pulse_Start();         // Truyen 1 bit bat dau khung truyen
void M_Sent_Bit(unsigned char i);            // Ham truyen 1 bit du lieu
void M_Sent_Byte(unsigned char byte);        // Ham truyen 1 byte du lieu
void M_Sent_Array(unsigned char *array,unsigned char length);    // Ham truyen nhieu byte du lieu
void M_Sent_Frame(unsigned char *data,unsigned char length);     // Ham truyen khung truyen 

#endif 
// ------------------END OF FILE-------------
// ------------------------------------------
