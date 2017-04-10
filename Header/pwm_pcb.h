/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __pwm_pcb
#define __pwm_pcb

#ifdef __cplusplus
 extern "C" {
#endif 

//#include <iotiny2313.h>
#include "ioavr.h"   
	 
/* Init LCD PINS	*/	
   
//#define ESC_DOWN          0
//#define ENT_UP            1   
	 
#define INn           3
typedef enum 
{	 
  ESC_DOWN    = 0,
  ENT_UP      = 1,
  DOOR_CLOSE  = 2,
}PWM_TypeDef;

#define ESC_DOWN_PIN                    PORTB7
#define ESC_DOWN_PORT                   PINB
#define ESC_DOWN_TIME			20

#define ENT_UP_PIN                      PORTD5
#define ENT_UP_PORT                 	PIND
#define ENT_UP_TIME			20

#define DOOR_CLOSE_PIN                  PORTD6
#define DOOR_CLOSE_PORT                 PIND
#define DOOR_CLOSE_TIME			20
/*
#define PWM_D3_PIN                   	PORTD7
#define PWM_D3_PORT                	PIND
#define PWM_D3_TIME			20
*/
extern __flash unsigned char volatile __io* IN_PORT[INn];
extern __flash const unsigned char IN_PIN[INn];
extern __flash const unsigned char IN_TIME[INn];

#define RELE_ON                  PORTB |=  (1 << PORTB1)
#define RELE_OFF                 PORTB &= ~(1 << PORTB1)



/*
void LcdPinOff(LDC_TypeDef lcdpin);
void LcdPinOn(LDC_TypeDef lcdpin);
void LcdDataPinsOff(void);
void LcdDataPinsOn(void);
void LcdDataPinsOut(void);
void LcdDataPinsIn(void);
void LcdPinsOut(void);
void InsInit(void);
*/
#ifdef __cplusplus
}
#endif


#endif
