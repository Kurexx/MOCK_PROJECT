#include "LED.h"
#include ".\Header_File\LPSPI.h"
#include "FP.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : DisplayDigit
 * Description   : This function is designed to control the 7-segment LED. When called, 
 the function will receive input information such as:
Number to display: The function will use this information to determine which 
segments on the 7-segment LED need to be turned on to display the corresponding number.
Brightness setting: The function allows users to adjust the brightness of the 7-segment LED.
 * Implements    : DisplayLed
 *END**************************************************************************/
void DisplayDigit(unsigned short Address, unsigned short Number)
{
	int Address_shifted = Address << LED_Address_bit;
	int Number_shifted = Number << LED_Data_bit;
	int TimeOutput = (Address_shifted | Number_shifted);

	LPSPI0_transmit((unsigned short)TimeOutput);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Enable_LED
 * Description   : This function is designed to init the 7-segment LED. When called, 
 the function will receive input information such as:
Change to normal operation:
Determine which segment to be displayed: 
Init Decode mode
 * Implements    : DisplayLed
 *END**************************************************************************/
void Enable_LED(void)
{
	LPSPI0_transmit(0xC01); // Normal operation
	LPSPI0_transmit(0xB07); // Scan limit
	LPSPI0_transmit(0x9FF); // Decode mode
	LPSPI0_transmit(0xA0F); // Default Max intensify
	DisplayClock(Time);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Time_cal
 * Description   : This function is used for increase the time each time LPIT interrupt
 * Implements    : LPIT_interrupt
 *END**************************************************************************/
void Time_cal(void)
{
	Time[S_D]++;
	CurTime=(int)Time[S_D];
	if (Time[S_D] >= 60)
	{
		Time[M_M]++;
		Time[S_D] = 0; // reset second
		CurTime=0; 
		PreTime=0;
	}

	if (Time[M_M] >= 60)
	{
		Time[H_Y]++;
		Time[M_M] = 0; // reset Min
	}

	if (Time[H_Y] > 24)
	{
		Time[H_Y] = 0; // reset Hour
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Time_cal
 * Description   : This function is used for display the time 
 * Implements    : Display
 *END**************************************************************************/
void DisplayClock(volatile unsigned int *Clock)
{
	DisplayDigit(Add[1], Seg[Clock[S_D] % 10]);
	DisplayDigit(Add[2], Seg[Clock[S_D] / 10]);
	DisplayDigit(Add[3], Seg[10]);
	DisplayDigit(Add[4], Seg[Clock[M_M] % 10]);
	DisplayDigit(Add[5], Seg[Clock[M_M] / 10]);
	DisplayDigit(Add[6], Seg[10]);
	DisplayDigit(Add[7], Seg[Clock[H_Y] % 10]);
	DisplayDigit(Add[8], Seg[Clock[H_Y] / 10]);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Time_cal
 * Description   : This function is used for display the date 
 * Implements    : Display
 *END**************************************************************************/
void DisplayDate(void)
{

	DisplayDigit(Add[7], Seg[Date[S_D] % 10]); // x1
	DisplayDigit(Add[8], Seg[Date[S_D] / 10]); // 1x
	DisplayDigit(Add[5], Seg[Date[M_M] % 10]); // x1
	DisplayDigit(Add[6], Seg[Date[M_M] / 10]); // 1x
	DisplayDigit(Add[1], Seg[Date[H_Y] % 10]);		   // xxx1
	DisplayDigit(Add[2], Seg[(Date[H_Y] % 100) / 10]); // xx1x
	DisplayDigit(Add[3], Seg[(Date[H_Y] / 100) % 10]); // x1xx
	DisplayDigit(Add[4], Seg[Date[H_Y] / 1000]);	   // 1xxx
}


