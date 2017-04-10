#ifndef _Test_Data_h
#define _Test_Data_h

  #include "stdint.h"

	#define NUMBER_OF_BITS	4
		#if (NUMBER_OF_BITS == 0)
			#error "TestData.h NUMBER_OF_BITS == 0"
		#endif
	#define SIZE_MBITS	((NUMBER_OF_BITS/8) + 1)	

  uint8_t TestData(void);
  void SetTestBitAll(void);
  uint16_t GetLimit(uint8_t index_limit);

#endif
