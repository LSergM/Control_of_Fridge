	#include "TestData.h"
	#include "MODBUS_DATA.h"
	
	#define TYPE_U16	0
	#define TYPE_S16	1
	
	static uint8_t mbits[SIZE_MBITS];
		
	union SU_16 {
		uint16_t u16;
		int16_t  s16;
	};
	
	struct Struct_MinMaxDef {
		SU_16 min;
		SU_16 max;
		SU_16 def;
		uint8_t d_type;
	};
	
	Struct_MinMaxDef MinMaxDef[NUMBER_OF_BITS] = {
		{5, 10, 8, TYPE_S16}, 		// T_MAX
		{-3, 0, 8, TYPE_S16}, 		// T_MIN
		{600, 1200, 800, TYPE_U16}, // TIME_STOP
		{300, 600, 400, TYPE_U16}	// TIME_WORK		
	};
	
	void SetTestBit(uint8_t i)
	{
		mbits[i/8] |= (1 << (i & 7));
	}

	void ClearTestBit(uint8_t i)
	{
		mbits[i/8] &= ~(1 << (i & 7));
	}	
	
	void SetTestBitAll(uint8_t i)
	{
		uint8_t k;
		
		for(k = 0; k < (SIZE_MBITS * 8); k++)
		{
			if (k < NUMBER_OF_BITS)
				SetTestBit(k);	
			else
				ClearTestBit(k);	
		}
	}
	
	uint8_t TestData(void)
	{
		static uint8_t i = 0;
		SU_16 data;
		
		
		if (mbits[i/8] & (1 << (i & 7)))
		{
			data = ;
			
			if (TYPE_U16 == MinMaxDef[i].d_type)
			{
				if (	(data.u16 > MinMaxDef[i].max.u16)
					 || (data.u16 < MinMaxDef[i].min.u16) )
				{
					data.u16 = MinMaxDef[i].def.u16;
				}
			}
			else if (TYPE_S16 == MinMaxDef[i].d_type)
			{
				if (	(data.s16 > MinMaxDef[i].max.s16)
					 || (data.s16 < MinMaxDef[i].min.s16) )
				{
					data.s16 = MinMaxDef[i].def.s16;
				}				
			}
			ClearTestBit(i);	
		}
		
		if (++i >= NUMBER_OF_BITS)
		{
			i = 0;
			return 1;
		}
		else
			return 0;
	}
	
	