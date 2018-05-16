#ifndef BUT_H
#define BUT_H


	#include <ioavr.h>
        #include <stdint.h>

	#define FLAG_BUT_PRESSED    (1<<0)
	#define FLAG_BUT_HOLD       (1<<1)
	#define FLAG_BUT_RELEASED   (1<<2)

/***************** настройки драйвера *********************/

/*количество кнопок*/

#define BUT_AMOUNT           4

/*сколько циклов опроса нужно удерживать 
кнопку, чтобы она считалась нажатой. 
должно быть меньше BUT_COUNT_HELD */

#define BUT_COUNT_THR        2

/*сколько циклов опроса нужно удерживать кнопку,
чтобы она считалась длительно нажатой
должно быть больше BUT_COUNT_THR */

#define BUT_COUNT_HELD       100

extern uint8_t stateBut[BUT_AMOUNT];
/**************** пользовательские функции *****************/

/*инициализация. 
вызывается в начале программы*/

void BUT_Init(void);

void BUT_Check(uint8_t state, uint8_t i);

#endif //BUT_H

