#ifndef _Test_Data_h
#define _Test_Data_h

	#define NUMBER_OF_BITS	8
		#if (NUMBER_OF_BITS == 0)
			#error "TestData.h NUMBER_OF_BITS == 0"
		#endif
	#define SIZE_MBITS	((NUMBER_OF_BITS/8) + 1)	
#endif
