#ifndef SCG__H__
#include ".\Header_File\SCG.h"
#endif

 void SOSC_init_8MHz(void);
 void SPLL_init_72Mhz (void);
 void RUNmode_72MHz (void);


  void SOSC_init_8MHz(void)
{
SCG->SOSCCFG=0x0000002C; /* Range=2: Medium freq (SOSC between 1MHz-8MHz)*/
												 /* HGO=0: Config xtal osc for low power */
												 /* EREFS=1: Input is external XTAL */
while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
SCG->SOSCCSR=0x00000001;  /* LK=0: SOSCCSR can be written */
													/* SOSCEN=1: Enable OSC */
while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}

 void SPLL_init_72Mhz (void) 
{
	SCG->SPLLCSR =0; //Disable SPLL
	while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); //wait LK bit to 0
	SCG->SPLLDIV = 0x00000200; 	 //DIV2 =2 72/2=36
	SCG->SPLLCFG=0x00020000;     //MULT =2  MULT factor (2+16=18)
															 //DIV =0 DIV factor (0+1=1)
															 //SPLL_CLK= (8*(18))/((1)*2)=72
	while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); //wait LK bit to 0
	SCG->SPLLCSR =0x00000001; //enable SPLL
while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); //Wait SPLL valid
}



 void RUNmode_72MHz (void) { /* Change to  RUN mode with 72MHz SPLL*/
SCG->RCCR =0x06000012; /* SPLL as clock source*/
											 /* DIVCORE=0, div. by 1: Core clock = 72 MHz*/
											 /* DIVBUS=1, div. by 2: bus clock = 36 MHz*/
											 /* DIVSLOW=2, div. by 3: SCG slow, flash clock= 24 MHz*/
while (((SCG->CSR & (6u<<24))>>24) != 6u){}
/* Wait for sys clk src = SPLL */
}
