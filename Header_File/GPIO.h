#define GPIO__H__
#define GPIOA_BASE 0x400FF000
#define GPIOB_BASE 0x400FF040
#define GPIOC_BASE 0x400FF080
#define GPIOD_BASE 0x400FF0C0
#define GPIOE_BASE 0x400FF100	

typedef struct GPIO_struct
{
    volatile unsigned int PDOR;
    volatile unsigned int PSOR;
    volatile unsigned int PCOR;
    volatile unsigned int PTOR;
    const volatile unsigned int PDIR; //read only
    volatile unsigned int PDDR;
    volatile unsigned int PIDR;
}GPIO_TYPE;

#define PORTA_GPIO ((GPIO_TYPE*) GPIOA_BASE)
#define PORTB_GPIO ((GPIO_TYPE*) GPIOB_BASE)
#define PORTC_GPIO ((GPIO_TYPE*) GPIOC_BASE)
#define PORTD_GPIO ((GPIO_TYPE*) GPIOD_BASE)
#define PORTE_GPIO ((GPIO_TYPE*) GPIOE_BASE)
