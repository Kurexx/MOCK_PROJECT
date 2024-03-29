#define LPUART__H__


#define LPUART0_Base_address 0x4006A000
#define LPUART1_Base_address 0x4006B000
#define LPUART2_Base_address 0x4006C000

typedef struct LPUART
{
    const volatile unsigned int VERID; // read only
    const volatile unsigned int PARAM; // read only
    volatile unsigned int GLOBAL;
    volatile unsigned int PINCFG;
    volatile unsigned int BAUD;
    volatile unsigned int STAT;
    volatile unsigned int CTRL;
    volatile unsigned int DATA;
    volatile unsigned int MATCH;
    volatile unsigned int MODIR;
    volatile unsigned int FIFO;
    volatile unsigned int WATER;
}LPUART_type;

#define LPUART0_REG ((LPUART_type*) LPUART0_Base_address)
#define LPUART1_REG ((LPUART_type*) LPUART1_Base_address)
#define LPUART2_REG ((LPUART_type*) LPUART2_Base_address)

#define LPUART_STAT_RDRF_MASK (1u<<21) //receive
#define LPUART_STAT_RDRF_SHIFT 21

#define LPUART_STAT_TDRE_MASK (1u<<23) //transmit
#define LPUART_STAT_TDRE_SHIFT 23

static volatile unsigned int UART_Data[8]={0,1,2,3,4,5,6,7};
