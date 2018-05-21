#include "eemem.h"
#include <stdint.h>

uint16_t ee_buf_adr[EE_BUF_NUM];
uint8_t  ee_buf_data[EE_BUF_NUM];

uint16_t eeb_h=0, eeb_t=0;

void Write_Transmit_Change_Data(uint8_t *data, uint8_t size_data, uint16_t Adr_EE)
{
	uint8_t k=0;

	for(k=0; k<size_data; k++)
	{
	  eeprom_write_byte(Adr_EE, data[k]);	
          Adr_EE++;
	}
}
//************************************************************
void write_buffers_byte_to_EE()
{
  uint16_t EE_ADR;
  uint8_t EE_DATA;
  
    if(eeb_h==eeb_t || EECR & 1<<REG_EEWE) return;  
//  if(eeb_h==eeb_t || EECR & 1<<EEWE) return;
  
  EE_ADR  = ee_buf_adr[eeb_t];
  EE_DATA = ee_buf_data[eeb_t];
  
  __disable_interrupt(); //cli();
  if(!(EECR & 1<<REG_EEWE))
  {
    //Начать запись в EEPROM
    EEAR = EE_ADR;				//Запись адреса
    EEDR = EE_DATA;				//Запись данных
    EECR = 1<<REG_EEMWE;			//Установить флаг "EEMWE"
    EECR = 1<<REG_EEWE;
    eeb_t++;
  }  
  __enable_interrupt(); //sei();
  
  if(eeb_t>=EE_BUF_NUM) eeb_t=0;
}
//////////////////////////////////////////////

//****************************************************************
//		ЗАПИСЬ ДАННЫХ В EEPROM
//****************************************************************
void eeprom_write_byte(uint16_t EE_ADR, uint8_t EE_DATA)
{
  ee_buf_adr[eeb_h]=EE_ADR;
  ee_buf_data[eeb_h++]=EE_DATA;
          
  if(eeb_h>=EE_BUF_NUM) eeb_h=0; 
}

//****************************************************************
//		ЧТЕНИЕ ДАННЫХ ИЗ EEPROM
//****************************************************************
uint8_t eeprom_read_byte(uint16_t EE_ADR)
{
  while(EECR & 1<<REG_EEWE);	        //Ждать завершения предыдущей записи	
  __disable_interrupt(); //cli();
  while(EECR & 1<<REG_EEWE);	        //Ждать завершения предыдущей записи
  EEAR = EE_ADR;			//Запись адреса
  EECR |= 1<<EERE;			//Начать чтение из EEPROM
  __enable_interrupt(); //sei();

  return EEDR;
}

