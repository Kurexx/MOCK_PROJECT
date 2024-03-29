#ifndef PCR__H__
#define PCR__H__

#ifndef PORT_BASE__H__
#include "PORT_BASE.h"
#endif

typedef struct PCR_struct
{
    volatile unsigned int PCR0;
    volatile unsigned int PCR1;
    volatile unsigned int PCR2;
    volatile unsigned int PCR3;
    volatile unsigned int PCR4;
    volatile unsigned int PCR5;
    volatile unsigned int PCR6;
    volatile unsigned int PCR7;
    volatile unsigned int PCR8;
    volatile unsigned int PCR9;
    volatile unsigned int PCR10;
    volatile unsigned int PCR11;
    volatile unsigned int PCR12;
    volatile unsigned int PCR13;
    volatile unsigned int PCR14;
    volatile unsigned int PCR15;
    volatile unsigned int PCR16;
    volatile unsigned int PCR17;
    volatile unsigned int PCR18;
    volatile unsigned int PCR19;
    volatile unsigned int PCR20;
    volatile unsigned int PCR21;
    volatile unsigned int PCR22;
    volatile unsigned int PCR23;
    volatile unsigned int PCR24;
    volatile unsigned int PCR25;
    volatile unsigned int PCR26;
    volatile unsigned int PCR27;
    volatile unsigned int PCR28;
    volatile unsigned int PCR29;
    volatile unsigned int PCR30;
    volatile unsigned int PCR31;
    volatile unsigned int GPCLR;
    volatile unsigned int GPCHR;
    volatile unsigned int GICLR;
    volatile unsigned int GICHR;
    char res_0[20];
    volatile unsigned int ISFR;
    char res_1[32];
    volatile unsigned int DFER;
    volatile unsigned int DFCR;
    volatile unsigned int DFWR;
}PCR_type;

#define PORTA_PCR ((PCR_type*) PORTA_BASE)
#define PORTB_PCR ((PCR_type*) PORTB_BASE)
#define PORTC_PCR ((PCR_type*) PORTC_BASE)
#define PORTD_PCR ((PCR_type*) PORTD_BASE)
#define PORTE_PCR ((PCR_type*) PORTE_BASE)

/* Config PCR */
//Interupt Stat
#define PCR_ISF (1u<<24) //Interup detected
//Interupt
#define IC_Disable ((0<<16)|(0<<17)|(0<<18)|(0<<19))
#define IC_DMA_rising (1u<<16)
#define IC_DMA_falling (2u<<16)
#define IC_DMA_either (3u<<16)
#define IC_logic_0 (8u<<16)
#define IC_rising (9u<<16)
#define IC_falling (10u<<16)
#define IC_either (11u<<16)
#define IC_logic_1 (12u<<16)
//Lock register
#define LK (1u<<15)
//Pin Mux
#define GPIO (1u<<8)
//Drive Strength
#define DSE (1u<<6)
//Passive filter
#define PFE (1u<<4)
//Pull enable
#define PE (1u<<1)
//Pull mode
#define PS (1u<<0)

#define ALT0 (0u<<8)
#define ALT1 (1u<<8)
#define ALT2 (2u<<8)
#define ALT3 (3u<<8)
#define ALT4 (4u<<8)
#define ALT5 (5u<<8)
#define ALT6 (6u<<8)
#define ALT7 (7u<<8)

#endif
