	#include "OneWireSM.h"
	#include "OWIBitFunctions.h"
        #include "OWIPolled.h"
        #include <intrinsics.h>
	
	typedef struct
	{	
		uint8_t nb  : 3;      //Number bit
		uint8_t ws;    	  	  //Word State
		uint8_t dat;    	  //Date
	} Str_OW_operation;
	
  Str_OW_operation OW_operation;
	uint8_t st_1wio = 0;
	int16_t ttemp = 0;
		
	#define DETECT_DEVICE			1
	#define NO_DETECT_DEVICE		0
	#define OK_OPERATION			0
	#define END_OPERATION			1		
			
	void detect_device(void)
	{
		__disable_interrupt();	
		
		OWI_PULL_BUS_LOW(OWI_PIN_DS18B20_1);		// Drive bus low and delay.
    __delay_cycles(OWI_DELAY_C_STD_MODE);
		__delay_cycles(OWI_DELAY_H_STD_MODE);
		OWI_RELEASE_BUS(OWI_PIN_DS18B20_1);
		__delay_cycles(OWI_DELAY_I_STD_MODE);
		  if (((OWI_PIN) & OWI_PIN_DS18B20_1))
		  {
			st_1wio = NO_DETECT_DEVICE; //Error  
		  }
		  else
		  {
			st_1wio = DETECT_DEVICE; //Detect device   
		  }
		__delay_cycles(OWI_DELAY_J_STD_MODE);
		__enable_interrupt();	  
	}
	
	void SendByte(void)
	{		
		__disable_interrupt();	
		
		OWI_PULL_BUS_LOW(OWI_PIN_DS18B20_1);		// Drive bus low and delay.
		__delay_cycles(OWI_DELAY_A_STD_MODE);
		  if (OW_operation.dat & (1 << OW_operation.nb) )
		  {
			OWI_RELEASE_BUS(OWI_PIN_DS18B20_1);  
			 __delay_cycles(OWI_DELAY_B_STD_MODE);
		  }
		  else
		  {
			__delay_cycles(OWI_DELAY_F_STD_MODE);
                        OWI_RELEASE_BUS(OWI_PIN_DS18B20_1);
		  }
		  if(++OW_operation.nb) 
				st_1wio = OK_OPERATION;
		  else		
				st_1wio = END_OPERATION;
			
		__enable_interrupt();		
	}

	void ReadByte(void)
	{
		__disable_interrupt();					
			  
		  if (OWI_ReadBit(OWI_PIN_DS18B20_1))
		  {
			OW_operation.dat |= (1 << OW_operation.nb); //Error  
		  }

		  if(++OW_operation.nb) 
				st_1wio = OK_OPERATION;
		  else		
				st_1wio = END_OPERATION;
			
		__enable_interrupt();				
	}	
	
	
	
	
	int16_t read_ds18b20(void)
	{				
		switch(OW_operation.ws)	//Передача байта 
		{
			case 0:					
				detect_device();
				if(st_1wio == DETECT_DEVICE)
				{
					OW_operation.dat = DS1820_SKIP_ROM;
          OW_operation.nb  = 0;
					OW_operation.ws  = 1;
					return DS1820_OK;
				}	
				break;
			case 1:
				SendByte();
				if (st_1wio == END_OPERATION)
				{
					OW_operation.dat = DS1820_START_CONVERSION;	
					OW_operation.ws  = 2;	
				}
				return DS1820_OK;
			case 2:
				SendByte();
				if (st_1wio == END_OPERATION)
				{
                                        //__delay_cycles(OWI_DELAY_F_STD_MODE);
					OW_operation.ws = 3;	
				}
				return DS1820_OK;
			case 3:
				if (OWI_ReadBit(OWI_PIN_DS18B20_1))
        {
          OW_operation.ws = 4;
          return DS1820_OK;
        }
				return DS1820_WAITING;	
			case 4:	
				detect_device();
				if(st_1wio == DETECT_DEVICE)
				{
					OW_operation.dat = DS1820_SKIP_ROM;
          OW_operation.nb  = 0;
					OW_operation.ws  = 5;
					return DS1820_OK;
				}		
        break;
			case 5:
				SendByte();
				if (st_1wio == END_OPERATION)
				{
					OW_operation.dat = DS1820_READ_SCRATCHPAD;
					OW_operation.ws  = 6;	
				}
				return DS1820_OK;
			case 6:
				SendByte();
				if (st_1wio == END_OPERATION)
				{
					ttemp = 0;
					OW_operation.dat = 0;
					OW_operation.ws  = 7;	
				}
				return DS1820_OK;                               
			case 7:	
				ReadByte();
				if (st_1wio == END_OPERATION)
				{
					ttemp = OW_operation.dat;
          OW_operation.dat = 0;
					OW_operation.ws  = 8;	
				}
				return DS1820_OK;
			case 8:
				ReadByte();
				if (st_1wio == END_OPERATION)
				{
					ttemp |= (OW_operation.dat << 8);
					OW_operation.ws = 0;	
					return ttemp;
				}
				return DS1820_OK;
		}	
    OW_operation.ws = 0;
    return DS1820_ERROR;
	}
  
  void reset_ds18b20(void)
  {
    OW_operation.nb  = 0;
    OW_operation.ws  = 0;
  }
  