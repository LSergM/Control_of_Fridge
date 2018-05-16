/* Includes ------------------------------------------------------------------*/
  #include "led_digit.h"
  #include "modbus.h"

  struct strc_led str_leds[NUMCHAR];

  uint8_t    
          tdot             = 0,
          datdiv[5]        = {0,0,0,0,0},            
          str_led[NUMCHAR] ,
          flled            = 0,
          mdate[5],
          psym;

  uint16_t DRegs        = 0,                   //Значение для передачи в 
                                               //сдвиговые регистры
           dled         = 1001,
           t1dled       = 0,
           tdled        = 0;

 
  #define SIZE_COD7SEG                  96
  const uint8_t cod7seg[SIZE_COD7SEG] =
  {
    0x00, 0x86, 0x22, 0x49, 0x2D, 0x6B, 0x53, 0x46,
    0x70, 0x0F, 0x63, 0x46, 0x80, 0x40, 0x80, 0x52,
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F, 0x09, 0x58, 0x58, 0x48, 0x4C, 0xA7,
    0x5D, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x7B,
    0x74, 0x30, 0x0E, 0x75, 0x38, 0x55, 0x37, 0x5C,
    0x73, 0x67, 0x49, 0x6D, 0x78, 0x1C, 0x3E, 0x7E,
    0x76, 0x6E, 0x5B, 0x02, 0x64, 0x39, 0x23, 0x08,
    0x02, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71, 0x7B,
    0x74, 0x30, 0x0E, 0x75, 0x38, 0x55, 0x54, 0x5C,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x3E, 0x7E,
    0x76, 0x6E, 0x5B, 0x46, 0x30, 0x70, 0x41, 0x00
  };
  
  const uint8_t leg7seg[] =
  {
        LDIG0,      // DIG1
        LDIG1,       // DIG2
        LDIG2,       // DIG3
        LDIG3,       //  DIG4
  };
  
  void update_str(uint8_t *s)
  {
    register uint8_t c;
    uint8_t t = 0;
    
    while ((c = *s++)) 
    {
        if(c <= 0x20) 
        {
          c = 0;
        }
        else 
        {
          c -= 0x20; 
        }
        if(c < SIZE_COD7SEG)
        {               
          str_leds[t].sym = c;
        }
        //D_pc.ModBUS_r_reg[MB_DIG_1 + t] = str_leds[t].sym;
        if(++t >= NUMCHAR) 
        {
          break;
        }      
    }
    decode_leds();    
    flled |= (1 << UPD_SYMB);
  }
  
  void udate_st_leds(void)
  {
    static uint8_t tdig = 0;
    
    if(tdig >= NUMCHAR) 
    {
      tdig = 0;    
    }
    if(D_pc.ModBUS_rw_reg[CONFIG_LED_OUT] & (1 << OUT_TEST_DIGIT) )
    {
      DRegs = D_pc.ModBUS_rw_reg[TEST_DIGIT_1];
    }
    else
    {
      DRegs |=  (1 << LDIG0 | 1 << LDIG1 | 1 << LDIG2 | 1 << LDIG3 | 1 << LEDA | 1 << LEDB | 1 << LEDC | 1 << LEDD | 1 << LEDE | 1 << LEDF | 1 << LEDG | 1 << CDOT);//отключить все разряды                          
      D_pc.ModBUS_r_reg[MB_DIG_1 + tdig] = str_leds[tdig].csym;
      str_leds[tdig].csym &= ~(1 << leg7seg[tdig]);
      DRegs &= str_leds[tdig].csym;
      //D_pc.ModBUS_r_reg[MB_DIG_1 + tdig] = DRegs;
      tdig++;    
    }
  }
  
  void decode_leds(void)
  {
    static uint8_t    t1dig,
                      tsym;
    static uint16_t   tcsym;    
      
    for(t1dig = 0; t1dig < NUMCHAR; t1dig++)
    {
      tcsym = 0;
      tsym = cod7seg[str_leds[t1dig].sym];
      if (tsym & (1 << 0)) tcsym |= (1 << LEDA); 
      if (tsym & (1 << 1)) tcsym |= (1 << LEDB); 
      if (tsym & (1 << 2)) tcsym |= (1 << LEDC); 
      if (tsym & (1 << 3)) tcsym |= (1 << LEDD); 
      if (tsym & (1 << 4)) tcsym |= (1 << LEDE); 
      if (tsym & (1 << 5)) tcsym |= (1 << LEDF); 
      if (tsym & (1 << 6)) tcsym |= (1 << LEDG);
      str_leds[t1dig].csym = ~tcsym;
    }
  }
  
	void update_hc595(void)
	{
	  static unsigned char cnt_ch595 = 0;
	  
		if (DRegs & (1 << cnt_ch595)) //(1<<i)
		{
			HC595_DS_ON;
		}
		else
			{
				HC595_DS_OFF;
			}
		HC595_CLK;
		if (!cnt_ch595) 
    {
			HC595_STROBE;
			cnt_ch595 = 15;
			udate_st_leds();
		} 
    else
    {
			cnt_ch595--;
    }
	}