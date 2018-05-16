
#include "buttons.h"

        uint8_t countDeb[BUT_AMOUNT],
		stateBut[BUT_AMOUNT];

//#define FLAG_BUT_PRESSED    (1<<0)
//#define FLAG_BUT_HOLD       (1<<1)
//#define FLAG_BUT_RELEASED   (1<<2)

/*границы для счетчика антидребезга и двойного клика*/
#define BUT_COUNT_MAX        (BUT_COUNT_HELD + 1)

/************************************************/

void BUT_Check(uint8_t state, uint8_t i)
{
 i--;
 	
 uint8_t stateTmp, countDebTmp;       
 stateTmp = stateBut[i];

 countDebTmp = countDeb[i];
  
 if (state){
    if (countDebTmp < BUT_COUNT_MAX){
       countDebTmp++;

       if (countDebTmp > BUT_COUNT_THR){
          if (!(stateTmp & FLAG_BUT_PRESSED)){
             stateTmp |= FLAG_BUT_PRESSED;             
          }
       }
       
       if (countDebTmp > BUT_COUNT_HELD){
         if (!(stateTmp & FLAG_BUT_HOLD)){
            stateTmp &= ~(FLAG_BUT_RELEASED);
            stateTmp |= FLAG_BUT_HOLD;
         }
       }    
    }    
  }
  else{
                      
     countDebTmp = 0;
	 stateTmp |=  (FLAG_BUT_RELEASED);
     stateTmp &= ~(FLAG_BUT_PRESSED|FLAG_BUT_HOLD);
  }
         
  countDeb[i] = countDebTmp;
  stateBut[i] = stateTmp; 
}

/******************************************************/

void BUT_Init(void)
{
  uint8_t i;
  
  for(i = 0; i < BUT_AMOUNT; i++){
     countDeb[i] = 0;
     stateBut[i] = 0;          
  }    
} 
