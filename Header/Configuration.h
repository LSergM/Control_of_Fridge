#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_
    
    #include"stdint.h"

	#define IAR_COMPILER	1
	#define GCC_COMPILER	2
	#define COPMPILER		GCC_COMPILER

	#define MCU_ATMEGA_168A	1
	#define MCU_ATMEGA_8A	2
	#define MCU_TYPE		MCU_ATMEGA_168A

	#if COPMPILER == IAR_COMPILER
		#include <ioavr.h>
        #include <intrinsics.h>    
		#define FLASH_DECLARE(x) __flash x
	#elif COPMPILER == GCC_COMPILER
		#include <avr/io.h>
        #include <avr/interrupt.h>
		#define FLASH_DECLARE(x) x __attribute__((__progmem__))
	#else
		#error "Error, compiler doesn't chosen"
	#endif

  //#define TEST_MODE
    
  #if (MCU_TYPE	==	MCU_ATMEGA_168A)
    #define REG_EEWE      EEPE
    #define REG_EEMWE     EEMPE
    #define REG_TIMSK_1   TIMSK1  
    #define REG_TIMSK_2   TIMSK2  
    #define REG_UCSRA     UCSR0A  
    #define REG_UCSRB     UCSR0B  
    #define REG_UCSRC     UCSR0C  
    #define REG_UBRRL     UBRR0L  
    #define REG_UBRRH     UBRR0H    
    #define REG_UDR       UDR0  
    #define B_U2X         U2X0  
    #define B_MPCM        MPCM0
    #define B_RXCIE       RXCIE0
    #define B_TXCIE       TXCIE0  
    #define B_UDRIE       UDRIE0  
    #define B_RXEN        RXEN0    
    #define B_TXEN        TXEN0  
    #define B_UCSZ2       UCSZ02
    #define B_RXB8        RXB80  
    #define B_TXB8        TXB80
    #define B_UMSEL       UMSEL00  
    #define B_UPM0        UPM00    
    #define B_UPM1        UPM01  
    #define B_USBS        USBS0    
    #define B_UCSZ0       UCSZ00    
    #define B_UCSZ1       UCSZ01      
    #define B_UCPOL       UCPOL0        
    #define DEF_USART_TXC_vect USART_TX_vect
    #define DEF_USART_RXC_vect USART_RX_vect  
    #define REG_TCCR2       TCCR2B        
  
  #elif (MCU_TYPE	==	MCU_ATMEGA_8A)
    #define REG_EEWE      EEWE
    #define REG_EEMWE     EEMWE
    #define REG_TIMSK_1   TIMSK 
    #define REG_TIMSK_2   TIMSK   
    #define REG_UCSRA     UCSRA  
    #define REG_UCSRB     UCSRB
    #define REG_UCSRC     UCSRC  
    #define REG_UBRRL     UBRRL  
    #define REG_UBRRH     UBRRH      
    #define REG_UDR       UDR
    #define B_U2X         U2X  
    #define B_B_MPCM      MPCM 
    #define B_RXCIE       RXCIE  
    #define B_TXCIE       TXCIE  
    #define B_UDRIE       UDRIE
    #define B_RXEN        RXEN 
    #define B_TXEN        TXEN  
    #define B_UCSZ2       UCSZ2
    #define B_RXB8        RXB8 
    #define B_TXB8        TXB8 
    #define B_UMSEL       UMSEL0
    #define B_UPM1        UPM1
    #define B_UPM0        UPM0 
    #define B_USBS        USBS
    #define B_UCSZ0       UCSZ0    
    #define B_UCSZ1       UCSZ1
    #define B_UCPOL       UCPOL
    #define DEF_USART_TXC_vect USART_TXC_vect
    #define DEF_USART_RXC_vect USART_RXC_vect
    #define REG_TCCR2       TCCR2  
  #else  
    #error
  #endif
  
#endif
