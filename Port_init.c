#ifndef SCG__H__
#include "D:\Study\FPTEmbedded\Student\Modun_EMB\Header_File\PCC.h"
#include "D:\Study\FPTEmbedded\Student\Modun_EMB\Header_File\PCR.H"
#include "D:\Study\FPTEmbedded\Student\Modun_EMB\Header_File\GPIO.h"
#include "D:\Study\FPTEmbedded\Student\Modun_EMB\Header_File\NVIC.h"
#endif
void PORT_init(void);

void PORT_init(void)
{
//PCC
//		PCC->PORTB |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTB */
		PCC->PORTC |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTC */
	//	PCC->PORTD |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTD */
	  PCC->PORTE |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTE */
	
	//Define SPI register
		PORTE_PCR->PCR0 |= ALT2;  /* Port E0: MUX = ALT2,LPSPI0_SCK */
		PORTE_PCR->PCR2 |= ALT2;  /* Port E2: MUX = ALT2,LPSPI0_SOUT */
    PORTE_PCR->PCR6 |= ALT2;  /* Port E6: MUX = ALT2,LPSPI0_PCS2 */
	
//Define UART register
	PORTC_PCR->PCR7 |= ALT2;		 /* Port C7: MUX = ALT2,UART1 TX */
	PORTC_PCR->PCR6 |= 0x000C0200;	 /* Port C6: MUX = ALT2,UART1 RX */
	
//// LED,Button register
//		PORTD_PCR->PCR0 |=(ALT1);  /* Port D15: MUX = ALT1,GPIO B_LED */
//		PORTC_PCR->PCR12 =0x000c0100;  /* Port C12:  IRQC=12 interupt when logic 1
//																			MUX = ALT1,GPIO BTN0 */	
//		PORTC_PCR->PCR13 =0x000c0100;  /* Port C13:  IRQC=12 interupt when logic 1
//																			MUX = ALT1,GPIO BTN1 */	
//	


////GPIO Config
//		PORTD_GPIO->PDDR |= ((1u << 15));//output LED
//		PORTC_GPIO->PDDR &= ~(3u << 12); //input BTN
//	PORTD_GPIO-> PDOR |=(1u<<15); //Default LED off

// NVIC configuration
		NVIC_ISER0 |=(1u<<26%32); //LPSPI0 interrupt
		NVIC_ISER1 |=(1u<<33%32); //LPUART1 interrupt
//		NVIC_ISER1 |=(1u<<61%32); //PORTC interrupt



}
