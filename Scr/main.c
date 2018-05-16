#include "main.h"
#include "delay.h"
#include <ioavr.h>
#include <stdint.h>
#include <stdio.h>
#include <intrinsics.h>
#include "eemem.h"
#include "led_digit.h"
#include "modbus.h"
#include "menu.h"
#include "un_drebezg.h"
#include "..\\OneWire\OneWireSM.h"
#include "TestData.h"
#include "Configuration.h"


  const uint16_t DEF_TIME_STOP = 900;
  const uint16_t DEF_TIME_WORK = 600;
  
uint8_t fl=0;
char str_buf[NUMCHAR + 10];

#define   STOP          0
#define   STARTING      1
#define   STOPING       2
#define   WORK          3

#define   DETECT_SENSOR          1
#define   NOT_SENSOR             0

#define   F_1MS             0
#define   F_1S              1
#define   DS18B20_TIME_OUT    5
#define   SENSOR_IS_BROKEN    10

void main( void )
{ 
  uint8_t stCompressor = 0;
  uint8_t stSensor; 
  uint8_t timer_flags = 0;
  
  uint16_t timer_1msec = 0;  
  int16_t c18b20 = STOP;

  InitCPU();
/*  
  while(1)
  {
    update_hc595();
  };
*/  
  __enable_interrupt();
  while(1)
  {
//    __watchdog_reset();
      
    if(fl) 
    {      
      fl = 0;
      timer_flags |= (1 << F_1MS);
      if (++timer_1msec > 1000)
      {
        timer_1msec = 0;
        timer_flags |= (1 << F_1S);                
      }
    }
#ifndef TEST_MODE    
    c18b20 = read_ds18b20();
    if (DS1820_ERROR == c18b20)
    {
      if(D_pc.ModBUS_r_reg[DS18B20_CNT_ERROR] > SENSOR_IS_BROKEN)
      {
		  D_pc.ModBUS_rw_reg[SYSTEM_CONFIG] = WORK_FOR_TIME;
	  }
	  else
	  {
		  D_pc.ModBUS_r_reg[DS18B20_CNT_ERROR]++;
	  }
      stSensor = NOT_SENSOR;
//      sprintf(str_buf, "----");
    }
    else if (DS1820_WAITING == c18b20)
    {
      if(timer_flags & (1 << F_1S))
      {
        if (D_pc.ModBUS_r_reg[TIME_OUT_SENSOR] < DS18B20_TIME_OUT)
        {
          D_pc.ModBUS_r_reg[TIME_OUT_SENSOR]++; 
        }
        else
        {
          reset_ds18b20();
          stSensor = NOT_SENSOR;
        }
      }
    }
    else if(DS1820_OK != c18b20)
    {
		D_pc.ModBUS_r_reg[DS18B20_CNT_ERROR] = 0;	
      D_pc.ModBUS_r_reg[TIME_OUT_SENSOR] = 0;
      D_pc.ModBUS_r_reg[DS18B20_DATA] = (int16_t)(0.0625 * c18b20);
      stSensor = DETECT_SENSOR;
//      sprintf(str_buf, "+%d", (int16_t)D_pc.ModBUS_r_reg[DS18B20_DATA]);
    }
//    update_str(str_buf);
#endif    
    
    switch(stCompressor)
    {
    case STOP:
#ifndef TEST_MODE
                  if (D_pc.ModBUS_rw_reg[SYSTEM_CONFIG] == WORK_OFF)
                  {
							stCompressor = STOPING;
                  }
                  else if (D_pc.ModBUS_rw_reg[SYSTEM_CONFIG] == WORK_FOR_TIME)
                  {             
                    if (D_pc.ModBUS_r_reg[STATE_TIMER] >= D_pc.ModBUS_rw_reg[TIME_STOP])
                    {
                      stCompressor = STARTING; 
                    }                                        
                  }
                  else
                  {
                    if (DETECT_SENSOR == stSensor)
                    {
                      if ((int16_t)D_pc.ModBUS_r_reg[DS18B20_DATA] >= (int16_t)D_pc.ModBUS_rw_reg[T_MAX] )
                      {
							if(GetLimit(TIME_WORK) < D_pc.ModBUS_r_reg[STATE_TIMER] )
						   {
								stCompressor = STOPING;
						   }
                      }
                    }
                    else if (D_pc.ModBUS_r_reg[STATE_TIMER] >= D_pc.ModBUS_rw_reg[TIME_STOP])
                    {
                      stCompressor = STARTING; 
                    }                                         
                  }
#else
                    if (D_pc.ModBUS_r_reg[STATE_TIMER] >= DEF_TIME_STOP)
                    {
                      stCompressor = STARTING; 
                    }                                                          
#endif                  
                  break;
    case STARTING:  
                  stCompressor = WORK;
                  D_pc.ModBUS_r_reg[STATE_TIMER] = 0;
                  break;
    case STOPING:   
                  stCompressor = STOP;
                  D_pc.ModBUS_r_reg[STATE_TIMER] = 0;
                  break;
    case WORK:            
#ifndef TEST_MODE      
                  if (D_pc.ModBUS_rw_reg[SYSTEM_CONFIG] == WORK_OFF)
                  {
                    stCompressor = STOPING;
                  }
                  else if (D_pc.ModBUS_rw_reg[SYSTEM_CONFIG] == WORK_FOR_TIME)
                  {
                    if(D_pc.ModBUS_r_reg[STATE_TIMER] >= D_pc.ModBUS_rw_reg[TIME_WORK])
                      {                      
                        stCompressor = STOPING;                     
                      }                      
                  }
                  else
                  {
                    if (DETECT_SENSOR == stSensor)
                    {
                      if((int16_t)D_pc.ModBUS_r_reg[DS18B20_DATA] <= (int16_t)D_pc.ModBUS_rw_reg[T_MIN])                       
                      {
						   if(GetLimit(TIME_STOP) < D_pc.ModBUS_r_reg[STATE_TIMER] )
						   {
								stCompressor = STOPING;
						   }
                      }
                    }
                    else 
                    {    
                      if(D_pc.ModBUS_r_reg[STATE_TIMER] >= D_pc.ModBUS_rw_reg[TIME_WORK])
                      {                      
                        stCompressor = STOPING;                     
                      }                                          
                    }
                  }
#else
                    if(D_pc.ModBUS_r_reg[STATE_TIMER] >= DEF_TIME_WORK)
                    {                      
                      stCompressor = STOPING;                     
                    }
#endif                  
                  break; 
    default:
                D_pc.ModBUS_r_reg[CNT_ERR_STATE]++;
                D_pc.ModBUS_r_reg[COD_ERR_STATE] = stCompressor;
                stCompressor = STOPING;  
                D_pc.ModBUS_r_reg[STATE_TIMER] = 0;
                  break;
    }
    
    if(timer_flags & (1 << F_1S))
	{
		D_pc.ModBUS_r_reg[STATE_TIMER]++;
	}
	
    D_pc.ModBUS_r_reg[STATE_PUMP] = stCompressor;
    if (WORK == stCompressor)
    {
      RELE_ON;
    }
    else
    {
      RELE_OFF;
    }

#ifndef TEST_MODE    
//    update_hc595();
    Link_To_PC();
    write_buffers_byte_to_EE();    
    TestData();
#endif    
    timer_flags = 0;    
  }    
}

void InitCPU(void)
{
    DDRB  = (0 << DDB7 | 0 << DDB6 | 1 << DDB5 | 1 << DDB4 | 1 << DDB3 | 0 << DDB2 | 1 << DDB1 | 1 << DDB0);
    PORTB = (1 << PORTB7 | 1 << PORTB6 | 1 << PORTB2 | 0 << PORTB1 | 0 << PORTB0);
    
    DDRD  = (1<<DDD7 | 1<<DDD6 | 0<<DDD5);
    PORTD = (1 << PORTB5);
    
    TCCR1B = (0<<ICNC1|0<<ICES1|0<<WGM13|0<<WGM12|0<<CS12|1<<CS11|0<<CS10); //Таймер - 0 "Остановлен"
    REG_TIMSK_1  = (1 << TOIE1);//
    REG_UCSRA  = 0;
    REG_UCSRB  = 0;
#ifndef TEST_MODE    
    REG_TIMSK_2 |= 1<<TOIE2;//
      
    REG_UCSRA =(1<<B_U2X|0<<B_MPCM);
    REG_UCSRB =(1<<B_RXCIE|0<<B_TXCIE|0<<B_UDRIE|1<<B_RXEN|1<<B_TXEN|0<<B_UCSZ2|0<<B_RXB8|0<<B_TXB8);
    REG_UCSRC =(         0<<B_UMSEL|0<<B_UPM1|0<<B_UPM0|0<<B_USBS|1<<B_UCSZ1|1<<B_UCSZ0|0<<B_UCPOL);
    REG_UBRRH = 0;
    REG_UBRRL = 51;//??? 19200 bit/s
       
    unsigned char adr;
    for(unsigned char i=0; i < NUM_NOT_TO_EE; i++)
    {
      adr = i*2;
      D_pc.ModBUS_rw_reg[i] =  (eeprom_read_byte(adr + START_ADR_EE_DATA)<<8)
                              + eeprom_read_byte(adr + START_ADR_EE_DATA + 1);      
    }
    SetTestBitAll();
    while(0 == TestData());
#endif    
}

#pragma vector = DEF_USART_TXC_vect
__interrupt void Usart1TxVect(void) 
{
	D_pc.Counter_Byte_To_PC++;
	if (D_pc.Counter_Byte_To_PC < D_pc.Num_Byte_RW_To_PC) 
  {
     REG_UDR = D_pc.mw[D_pc.Counter_Byte_To_PC];
  }
	else 
      {   
        D_pc.Counter_Byte_To_PC = 0;
		    REG_UCSRB &= ~(1<<B_TXEN|1<<B_TXCIE);
		    REG_UCSRB |= (1<<B_RXEN|1<<B_RXCIE);
	    }	
}

#pragma vector = DEF_USART_RXC_vect
__interrupt void Usart1RxVect(void) 
{
	REG_TCCR2 = 0; //Остановить таймер 0
	
	if (D_pc.Counter_Byte_To_PC < UARTBUF)  
  {
    D_pc.mr[D_pc.Counter_Byte_To_PC] = REG_UDR;
    D_pc.Counter_Byte_To_PC++;          
  }
  else REG_UCSRB &= ~(1<<B_RXEN | 1<<B_RXCIE);

	TCNT2 = CNT_SPEED; //237    //Обнулить таймер 0 1,25 мс
	REG_TCCR2 = 0x07;//0B00000101; //Запустить таймер 0 c предделителем /1024	
}


#pragma vector = TIMER2_OVF_vect
__interrupt void Timer2OverFVect(void) 
{
    REG_TCCR2 = 0;     
    REG_UCSRB &= ~(1<<B_RXEN|1<<B_RXCIE); //	Отключить приемник UART ModBus																										//	Запретить прерывание приемника UARt
    D_pc.Flags_Link_To_PC |= (1<<RECIVED_POCET_FROM_PC);
}

#pragma vector = TIMER1_OVF_vect
__interrupt void Timer1OverFVect(void) 
{  
  fl    = 1;
  TCNT1 = 64535;
}

