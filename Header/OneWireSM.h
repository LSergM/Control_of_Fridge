#ifndef _ONE_WIRE_SM_H_
#define _ONE_WIRE_SM_H_

  #include <stdint.h>
  
  #define DS1820_FAMILY_ID                0x10 

  #define DS1820_SKIP_ROM                 0xcc
  #define DS1820_START_CONVERSION         0x44
  #define DS1820_READ_SCRATCHPAD          0xbe
  #define DS1820_ERROR                    -1000   // Return code. Outside temperature range.
  #define DS1820_OK                       -1001   // Return code. Outside temperature range.
  #define DS1820_WAITING                  -1002   // Return code. Outside temperature range.
//  #define DS1820_TEMP_READ_END			  2			

    int16_t read_ds18b20(void);
    void reset_ds18b20(void);
	
#endif