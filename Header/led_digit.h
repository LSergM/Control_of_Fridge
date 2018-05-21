/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __led_digit
#define __led_digit

  #include "Configuration.h" 
  #include <stdint.h>

  #define LDIG0             14      //
  #define LDIG1             10       //
  #define LDIG2             9       //
  #define LDIG3             8       //
  #define LEDA             0       //  
  #define LEDB             1       //  
  #define LEDC             6       //  
  #define LEDD             4       //  
  #define LEDE             3       //  
  #define LEDF             2       //  
  #define LEDG             7       //  
  #define CDOT             5       //
  
//  #define LED1             8       //

  #define DIG_1             0      //
  #define DIG_2             1       //
  #define DIG_3             2       //

  #define NUMCHAR           4       //���������� �������� � ������ ��� ���������        


  #define C_0             0       //������ "0"            
  #define C_1             1       //������ "1"
  #define C_2             2       //������ "2"
  #define C_3             3       //������ "3"
  #define C_4             4       //������ "4"
  #define C_5             5       //������ "5"
  #define C_6             6       //������ "6"
  #define C_7             7       //������ "7"
  #define C_8             8       //������ "8"
  #define C_9             9       //������ "9"
  #define C_DIG1          10      //������ DIG1_ON and OFF
  #define C_DIG2          11      //������ DIG2_ON and OFF
  #define C_DIG3          12      //������ DIG3_ON and OFF
  #define C_LED1          13      //LED1
  #define C_LED2          14      //LED2
  #define C_LED3          15      //LED3
  #define C_LED4          16      //LED4
  #define C_DP            17      //DP
  #define C_OUT1          18      //OUT1
  #define C_DIG1_ONLY     19      //DIG1_ONLY
  #define C_DIG2_ONLY     20      //DIG2_ONLY
  #define C_DIG3_ONLY     21      //DIG3_ONLY

  #define N_CCOD          22      //���������� �������� � ������� ���������

  #define ST_DIGIT        0x80    //7 ��� �������� �� ��������� ������ ON/OFF
  #define ST_DOT          0x40    //6 ��� �������� �� ��������� ����� ON/OFF

  
  struct strc_led
  {    
    uint8_t dp     :1;
    uint8_t blink  :1;
    uint8_t dig;        //�������� ������� � ������ ���������
    uint16_t cdig;       //�������� �������� ��� �������� ���������
    uint16_t sdig;       //������� �������� ��� �������� ���������
    uint8_t sym;        //������ ��� ���������
    uint16_t csym;       //�������������� ������
  };

  //����� ������ ����������
  #define UPD_CALC       0       // ���������� �������� ��������
  #define UPD_SYMB       1       // �������� �������
  #define UPD_DIV        2       // ���������� ������� �� �������
  #define UPD_H0         3		 //�� ��������� ������� ����
//  #define LED_MENU       1       // ���� ��������� ����

  //��������� ������ ����������
  #define DIG1_ON       1       // ������� ������ 1
  #define DIG2_ON       2       // ������� ������ 2
  #define DIG3_ON       3       // ������� ������ 3

  extern uint8_t stleds;
  extern uint8_t flled;
  extern uint8_t psym;  
  extern uint8_t mdate[5];
  
  extern uint16_t DRegs;        //�������� ��� �������� � 
                                //��������� ��������
  extern uint16_t dled;
  extern uint16_t tdled;
  
  
	#define HC595_DS_ON		        PORTD |= (1<<PD6)
	#define HC595_DS_OFF			PORTD &= ~(1<<PD6)
	#define HC595_STROBE  		        PORTB |= (1<<PB0); PORTB &= ~(1<<PB0)
	#define HC595_CLK			PORTD |= (1<<PD7); PORTD &= ~(1<<PD7)
                      

  void update_str(uint8_t *s);
  void decode_leds(void);
  void udate_str_flash(uint8_t const *s, uint8_t ndp);
  void update_hc595(void);
#endif
