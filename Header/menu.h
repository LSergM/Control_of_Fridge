#ifndef __MENU_H
#define __MENU_H
        #include "ioavr.h"
        #include <stdint.h>

        #define K_ESC           1
        #define K_ENT_UP        2
		#define K_BOTH          3

		#define MAIN_IND_ADR    0       //Индикация адреса
		#define MAIN_IND_SPEED  1       //Индикация скорости
        #define MAIN_MENU_UI    2       //Корневое меню
        #define MAIN_PASS       3       //Меню ввода пароля

        #define LINES_LCD       0       //количество строк
	#define COLUM_LCD       3       //количество колонок

        #define NOALM       255         //нет событий
        #define NODAT       0        //нет данных
        #define NONDT       255         //нет ????    
        #define DTNO        0   

    //Биты "flmenu"
		#define F_KEY_NOT	    1
        #define F_DATA_EDIT     2
        #define F_MENU_EDIT     3
        #define F_KEY_PAD       4
        #define F_MENU_REDRAW   5
	    #define F_CHAR_EDIT     6
     //   #define F_KEY_ENT_UP    5
     //   #define F_KEY_ESC_DOWN  6
	 
	 //Структура описывает пункт меню
	 const typedef struct _selection {
		 //uint8_t const *mas;	    // Указатель на название пункта
		 void (*function)(void); 	//Указатель на функцию выполняющуюся по нажатии на enter/escape
		 uint8_t calm;     	//Код события
		 uint8_t *fdat;    				//Указатель на переменную
		 uint8_t ndat;    		// Номер в массиве RW
                 uint8_t tdat;    		// Тип данных
	 } SELECTION;

	 //Структура описывает меню/подменю
	 const typedef struct _menu {
		 unsigned char id;				//Номер меню/подменю
		 unsigned char num_selections;  //Количество пунктов данного меню/подменю
		 SELECTION *m;					//Указатель намассив пунктов данного меню/подменю
	 } MENU;
	 
	 //Номера меню/подменю
	 enum __menu__id {
		 MAIN_MENU,						//0
		 SETTINGS_MENU,					//1
		 CLOCK,							//2
		 CONECT,						//3
		 PROTECTION_MENU,				//4
		 EXTERN_PROTECTION_MENU,		//5
		 CARRENT_ZASH,					//6
		 I_OTS_ZASH,
	 };
         
        #define SIZE_MENU		3
     extern   MENU  menu_all[SIZE_MENU];
     extern   MENU  *menu;
     extern uint8_t stmenu;
     extern uint16_t cdelkey;
     void mstate_menu(void);
#endif
