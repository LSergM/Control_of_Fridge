#ifndef _MODBUS_H_
#define _MODBUS_H_

//#include <iotiny2313.h>
#include "ioavr.h"
#include "pwm_pcb.h"

#define UARTBUF                     32
#define NWBUF                       UARTBUF
#define NUMBER_OF_RW_BIT_VARIABLES  8
#define ADRESS_DEVICE               200
#define CNT_SPEED                   240
#define FUNCTION_MODBUS		    1	


//  Flags_Link_To_PC
#define RECIVED_POCET_FROM_PC 0

//ModBUS_r_reg
#define ADC_0            0
#define ADC_1            1
#define CNT_0            2


#define DS18B20_DATA        0
#define DS18B20_CNT_ERROR   1
#define STATE_PUMP          2
#define CNT_ERR_STATE       3
#define COD_ERR_STATE       4
#define MB_DIG_1                5
#define MB_DIG_2                6
#define MB_DIG_3                7
#define MB_DIG_4                8
#define STATE_TIMER             9
#define TIME_OUT_SENSOR         10

#define NUMBER_OF_R_REGS            11

//ModBUS_rw_reg
  #define T_MAX             0
  #define T_MIN             1
  #define TIME_WORK         2
  #define TIME_STOP         3
  #define SYSTEM_CONFIG     4    
    #define WORK_OFF          0 
    #define WORK_FOR_TIME     1

  #define CONFIG_LED_OUT    5
    #define OUT_TEST_DIGIT    0
  #define TEST_DIGIT_1      6


  #define NUM_NOT_TO_EE     5
  #define NUMBER_OF_RW_REGS           7


#define PWM_DATA            0
//#define PINS                1
#define FLAGS               1
        #define CTRL_SOURS      0
#define PWM_CALC            2


struct D_pc_str
{
	unsigned char Num_Byte_RW_To_PC;
	unsigned char Flags_Link_To_PC;
	unsigned char mr[UARTBUF];
	unsigned char mw[UARTBUF];
	unsigned char Counter_Byte_To_PC;
	unsigned int ModBUS_rw_reg[NUMBER_OF_RW_REGS]; 
	unsigned char ModBUS_rwbit[NUMBER_OF_RW_BIT_VARIABLES >> 3]; //байтовый массив для обмена битовыми
	//переменными rw по ModBUS
	unsigned int ModBUS_r_reg[NUMBER_OF_R_REGS];
	unsigned char ModBUS_rw_reg_write_flags[(NUMBER_OF_RW_REGS + 7 >> 3)+(NUMBER_OF_RW_BIT_VARIABLES >> 3)];//byte массив битовых флагов прихода
//данных по ModBUS для rw регистров
} ;

extern struct D_pc_str D_pc;

unsigned int GetCRC16(unsigned char *buf, unsigned char bufsize);
void Link_To_PC(void);
#endif 
