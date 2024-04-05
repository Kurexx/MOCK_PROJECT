#include ".\Header_File\LPIT.h"
#include ".\Header_File\PCC.h"
#include ".\Header_File\GPIO.h"
#include "FP.h"

volatile int Led_Toggle_Count=0;

/*FUNCTION**********************************************************************
 *
 * Function Name : LPIT_init
 * Description   : This function will initilize LPIT
 * Implements    : LPIT
 *END**************************************************************************/
void LPIT_init(void)
{
	PCC->LPIT |= (PCC_PCCn_CGC_MASK | (6u << 24)); // CLK option 6 SPLL_DIV2 (36Mhz)
	LPIT_REG->MCR = 0x00000009;					   // DBG_EN=1 timer continue to run in debug
																				 // M_CEN=1 enable PPC
	LPIT_REG->MIER = 0x00000003;				   // TIE0 =1 Enable Channel 0,1 interrupt
	LPIT_REG->TVAL1 = 0x112A880;				   // 0.5s
	LPIT_REG->TVAL0 = 0x2255100;				   // 1s
	LPIT_REG->SETTEN = 0x00000001;				 // enable LPIT0
	
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPIT0_Ch0_IRQHandler
 * Description   :These actions may include:
Data processing: Reading data from the data register of the corresponding LPIT channel.
Status update: Updating the status information of LPIT and the system.
Function call: Calling 	Time_cal();Check_Bright_Lv();Check_Alarm();Check_Mode(); functions to perform specific tasks 
 * Implements    : LPIT
 *END**************************************************************************/
void LPIT0_Ch0_IRQHandler(void)
{	 
	
	LPIT_REG->MSR |=(1u<<0); //Clear interrupt flag
	Time_cal();
	Check_Bright_Lv();
	Check_Alarm();
	Check_Mode();
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPIT0_Ch1_IRQHandler
 * Description   : Toggle alarm led when handle interrupt
 * Implements    : LPIT
 *END**************************************************************************/
void LPIT0_Ch1_IRQHandler (void)
{
		LPIT_REG->MSR |=(1u<<1);  //Clear interrupt flag
	if(Led_Toggle_Count<20)
		{
	PORTD_GPIO-> PDOR ^=(1u<<16); //Toggle LED
		}
		Led_Toggle_Count++;
}
