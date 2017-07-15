
#ifndef __MAN_CODE_H
#define __MAN_CODE_H

unsigned char M_Get_Start();            // Ham kiem tra de bat dau qua trinh nhan du lieu
unsigned char M_Get_Pulsestart();       // Ham kiem tra bit bat dau khung truyen
unsigned char M_Get_Byte();             // Ham nhan 1 byte du lieu
void M_Get_Array(unsigned char *array,unsigned char length);     // Ham nhan cac bye du lieu 
unsigned int M_Get_Frame(unsigned char *data,unsigned char length);  // Ham kiem tra khung du lieu va nhan du lieu duoc truyen den

#endif
// ------------------END OF FILE-------------------
// ------------------------------------------------
