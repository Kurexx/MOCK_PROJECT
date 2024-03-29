#include ".\Header_File\Header.h"
#include "LED.h"
#include "FP.h"

//static unsigned short N_Op =(15u<<8); //LED normal operation

/* Define Interupt */

void LPSPI1_init_master(void);
void PORTC_IRQHandler(void);
int main ()
{
	SOSC_init_8MHz();
	SPLL_init_72Mhz(); //DIV2=36Mhz
	RUNmode_72MHz();
	PORT_init();
	LPUART1_init();
	LPSPI0_init_master();
	LPUART1_transmit_string("[NGUYEN PHUNG HOANG LONG]-MOCK PROJECT\n");
	
	//Test LED
//	LPSPI0_transmit(N_Op);
//	LPSPI0_transmit(0xB07);
//	LPSPI0_transmit(0x133);

	while(1){
	}	
}







