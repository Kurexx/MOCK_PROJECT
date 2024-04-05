#ifndef SCG__H__
#include ".\Header_File\PCC.h"
#include ".\Header_File\PCR.H"
#include ".\Header_File\NVIC.h"
#include ".\Header_File\GPIO.h"
#include "FP.h"
#include "LED.h"
#include ".\Header_File\LPIT.h"
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : PORT_init
 * Description   : This function will initilize PORT
 * Implements    : PORT
 *END**************************************************************************/
void PORT_init(void)
{
//PCC
	
	//Define PORTE register
		PCC->PORTE |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTE */
		PORTE_PCR->PCR0 |= ALT2;  /* Port E0: MUX = ALT2,LPSPI0_SCK  */
		PORTE_PCR->PCR2 |= ALT2;  /* Port E2: MUX = ALT2,LPSPI0_SOUT */
		PORTE_PCR->PCR6 |= ALT2;  /* Port E6: MUX = ALT2,LPSPI0_PCS2 */
	
	
// PORTC register (UART,Button)
		PCC->PORTC |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTC */
		PORTC_PCR->PCR7 |= ALT2;		 /* Port C7: MUX = ALT2,UART1 TX */
		PORTC_PCR->PCR6 |= ALT2;		 /* Port C6: MUX = ALT2,UART1 RX */
	
		PORTC_PCR->PCR12 =0x000A0100;  /* Port C12:  IRQC=12 interupt when logic 1
																			MUX = ALT1,GPIO BTN0 */	
		PORTC_PCR->PCR13 =0x000A0100;  /* Port C13:  IRQC=12 interupt when logic 1
																			MUX = ALT1,GPIO BTN1 */	
		PORTC_GPIO->PDDR &= ~(3u << 12); //input BTN
	
// PORTD register (LED)
		PCC->PORTD |= PCC_PCCn_CGC_MASK;    /* Enable clock for PORTD */	
		PORTD_PCR->PCR16 |=(ALT1);  /* Port D0: MUX = ALT1,GPIO B_LED */
		PORTD_GPIO->PDDR |= (1u << 16); //output LED
		PORTD_GPIO->PDOR |= (1u << 16); //Default LED off

// NVIC configuration
		NVIC_ISER1 |=(1u<<33%32); //LPUART1 interrupt
		NVIC_ISER1 |=(1u<<48%32); //LPIT0 interrupt
		NVIC_ISER1 |=(1u<<49%32); //LPIT1 interrupt
		NVIC_ISER1 |=(1u<<61%32); //PORTC interrupt
}


/*FUNCTION**********************************************************************
 *
 * Function Name : PORTC_IRQHandler
 * Description   : This function will handle PORT interrupt
 * Implements    : PORT
 *END**************************************************************************/
void PORTC_IRQHandler(void)
{
	if(Display_Mode[G_mode]== ALARM_OCCUR)
	{
			LPIT_REG->CLRTEN |=(1u<<1);	// Disable LPIT1
			Led_Toggle_Count=0; //reset counter
			PORTD_GPIO-> PDOR |=(1u<<16); //Turn off LED
			PORTC_PCR->PCR12 |= (1u << 24);
			PORTC_PCR->PCR13 |= (1u << 24);
			G_mode=0; //Change mode to Auto
	}
	
  if ((PORTC_PCR->PCR12 & (1u << 24)) == (1u << 24))
  {
		PORTC_PCR->PCR12 |= (1u << 24); // set interupt flag to 1
		if(G_mode<3)
		{G_mode++;
		}else G_mode =0;
  }
  else if ((PORTC_PCR->PCR13 & (1u << 24)) == (1u << 24))
  {
		PORTC_PCR->PCR13 |= (1u << 24); // set interupt flag to 1	
		Bright_Lv++;		
	}
}
