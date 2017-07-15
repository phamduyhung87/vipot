
     
#include "rf_at8.h"

//==============================================================================
unsigned char M_Get_Pulsestart()
{
     unsigned int i;
//	 printf("\n%d",i);
	 if(Data_In)
	 {	
  	   if((Data_In));
  		   for(i=0;i<35;i++)
 	 	   {
			  _delay_us(TIME);
 	         if((Data_In)==0) break;        
 		    }
			//printf("\n%d",i);
  	   if((i<29)&&(i>=0)) {return 0;}
   		  else if (i>30) {return 0;}
  	   else { while((Data_In)==0); return 1;}
	}
	else return 0;

}


//==============================================================================
unsigned char M_Get_Byte()
{
     unsigned char data,i;
     data=0;
	 
     for(i=0;i<8;i++)
     {       
		_delay_us(2*TIME);
		if ((Data_In))
		{
		  	data|=(1<<(7-i));	// nhan bit cao truoc
			while (Data_In);
		}
		while ((Data_In)==0);
      }                  
     return data;
}

//==============================================================================
unsigned int M_Get_Array(unsigned char *array,unsigned char length)
{
     unsigned char i;
     for(i=0;i<length;i++)
     {
          array[i]=M_Get_Byte();
		  if (array[i] == '\r')
		  	return (i);
     }
	 return i;
}

//==============================================================================
unsigned int M_Get_Frame(unsigned char *data, unsigned int length)
{
	 if (M_Get_Pulsestart())
	 {
	 	
		unsigned int i = M_Get_Array(data,length);
		return i;
	}	
	return 0;
	 	       
}
                                
// ------------------END OF FILE-------------------
// ------------------------------------------------
