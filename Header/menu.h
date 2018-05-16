#ifndef __MENU_H
#define __MENU_H
        #include "ioavr.h"
        #include <stdint.h>

        #define K_ESC           1
        #define K_ENT_UP        2
		#define K_BOTH          3

		#define MAIN_IND_ADR    0       //��������� ������
		#define MAIN_IND_SPEED  1       //��������� ��������
        #define MAIN_MENU_UI    2       //�������� ����
        #define MAIN_PASS       3       //���� ����� ������

        #define LINES_LCD       0       //���������� �����
	#define COLUM_LCD       3       //���������� �������

        #define NOALM       255         //��� �������
        #define NODAT       0        //��� ������
        #define NONDT       255         //��� ????    
        #define DTNO        0   

    //���� "flmenu"
		#define F_KEY_NOT	    1
        #define F_DATA_EDIT     2
        #define F_MENU_EDIT     3
        #define F_KEY_PAD       4
        #define F_MENU_REDRAW   5
	    #define F_CHAR_EDIT     6
     //   #define F_KEY_ENT_UP    5
     //   #define F_KEY_ESC_DOWN  6
	 
	 //��������� ��������� ����� ����
	 const typedef struct _selection {
		 //uint8_t const *mas;	    // ��������� �� �������� ������
		 void (*function)(void); 	//��������� �� ������� ������������� �� ������� �� enter/escape
		 uint8_t calm;     	//��� �������
		 uint8_t *fdat;    				//��������� �� ����������
		 uint8_t ndat;    		// ����� � ������� RW
                 uint8_t tdat;    		// ��� ������
	 } SELECTION;

	 //��������� ��������� ����/�������
	 const typedef struct _menu {
		 unsigned char id;				//����� ����/�������
		 unsigned char num_selections;  //���������� ������� ������� ����/�������
		 SELECTION *m;					//��������� �������� ������� ������� ����/�������
	 } MENU;
	 
	 //������ ����/�������
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
