	#include "TestData.h"
	#include "modbus.h"
	
	#define TYPE_U16	0
	#define TYPE_S16	1
	
	static uint8_t mbits[SIZE_MBITS];
		 
	struct Struct_MinMaxDef {
		uint16_t min;
		uint16_t max;
		uint16_t def;
	};
	
	const struct Struct_MinMaxDef MinMaxDef[NUMBER_OF_BITS] = {
		{5,     10,   8}, 		// T_MAX
		{0,     3,    0}, 		// T_MIN
		{300,   1200, 400}, // TIME_WORK
		{300,   1200, 800}	// TIME_STOP		
	};

	uint16_t GetLimit(uint8_t index_limit)
	{
		if (index_limit >= NUMBER_OF_BITS)
		{
			return 0;
		}
		return MinMaxDef[index_limit].min;
	}
  
	void SetTestBit(uint8_t i)
	{
		mbits[i/8] |= (1 << (i & 7));
	}

	void ClearTestBit(uint8_t i)
	{
		mbits[i/8] &= ~(1 << (i & 7));
	}	
	
	void SetTestBitAll(void)
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
		uint16_t data;
		
		
		if (mbits[i/8] & (1 << (i & 7)))
		{						
        data = D_pc.ModBUS_rw_reg[i];
				if (	(data > MinMaxDef[i].max)
					 || (data < MinMaxDef[i].min) )
				{
					D_pc.ModBUS_rw_reg[i] = MinMaxDef[i].def;
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
	
	
