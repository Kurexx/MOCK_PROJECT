#include ".\Header_File\GPIO.h"
#include ".\Header_File\PCR.H"
#include ".\Header_File\LPIT.h"
#include "FP.h"
#include "LED.h"

void Button_init(void);
void PORTC_IRQHandler(void);

void Button_init(void)
{
		PORTD_GPIO->PDDR |= ((1u << 15));//output LED
		PORTC_GPIO->PDDR &= ~(3u << 12); //input BTN
		PORTD_GPIO-> PDOR |=(1u<<15); //Default LED off
}
 
void PORTC_IRQHandler(void)
{
	if(Display_Mode[G_mode]== ALARM_OCCUR)
	{
			LPIT_REG->CLRTEN |=(1u<<1);	// Disable LPIT1
			PORTD_GPIO-> PDOR |=(1u<<15); //Turn off LED
			PORTC_PCR->PCR12 |= (1u << 24);
			PORTC_PCR->PCR13 |= (1u << 24);
	}
	
  if ((PORTC_PCR->PCR12 & (1u << 24)) == (1u << 24))
  {
		PORTC_PCR->PCR12 |= (1u << 24); // set interupt flag to 1
		if(G_mode<4)
		{G_mode++;
		}else G_mode =0;
  }
  else if ((PORTC_PCR->PCR13 & (1u << 24)) == (1u << 24))
  {
		PORTC_PCR->PCR13 |= (1u << 24); // set interupt flag to 1
		if(Bright_Lv>5)
		{Bright_Lv=0;}
		Bright_Lv++;
		SettingBrightLv();
   
  }

}
