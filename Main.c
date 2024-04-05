#include ".\Header_File\Header.h"
#include "LED.h"
#include "FP.h"
#include "stdio.h"

/*  VALRIABLES INIT*/
volatile unsigned int Time[3] = {
	18, // Hour
	0,	// Minute
	0	// Second
};
volatile unsigned int Date[3] = {
	1990, // Year
	1,	  // Month
	1	  // Day
};
volatile unsigned int Alarm[3] = {
	18, // Hour
	30, // Minute
	0	// Second
};
volatile char Display_Mode[5] = {
	0, // Mode 1:auto
	1, // Mode 2:Date
	2, // Mode 3:Time
	3, // Mode 4:Alarm
	4, // Mode 5:Alarm_occur
};
volatile int CurTime = 0;
volatile int PreTime = 0;
volatile int G_mode = 0;
volatile int Bright_Lv = 0;
volatile int Led_Bright_Lv[6] = {
	15, // Lv4 MAX
	12, // Lv3
	8,	// Lv2
	4,	// Lv1
	0,	// Lv0 OFF
	1,	// Enable
};



/*Function Prototype*/
void Menu(void);
int Check_Format(char *Data);
int Check_Valid_date(int Day, int Month, int Year);
int LeapYearCheck(int Leap_Year);
int Check_Valid(volatile char arr[]);

/* MAIN FUNCTION*/

int main()
{
	Clock_init();
	PORT_init();
	LPUART1_init();
	Menu();
	LPSPI0_init_master();
	Enable_LED();
	LPIT_init();
	volatile int Result;
	while (1)
	{
		if((flag==1))
		{
			Result=Check_Valid(UART_receive_data);
			flag=0;
			if(Result)
			LPUART1_transmit_string(" Change !\n");
			else
			{	LPUART1_transmit_string(" WRONG FORMAT\n");}
			Word_Count=0;
		}
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Menu
 * Description   : This function is designed to print the device's user manual to the terminal. 
When called, this function will access the device's user manual, 
then process and format the information for clear and easy display on the terminal
 *
 * Implements    : Main.c
 *END**************************************************************************/
void Menu(void)
{
	
/*FUNCTION**********************************************************************
 *
 * Function Name : Check_Mode
 * Description   : This function is designed to print the device's user manual to the terminal. 
When called, this function will access the device's user manual, 
then process and format the information for clear and easy display on the terminal
 *
 * Implements    : Main.c
 *END**************************************************************************/	
	
	LPUART1_transmit_string("[NGUYEN PHUNG HOANG LONG]-MOCK PROJECT\n\n");
	LPUART1_transmit_string("-----------------------------------------\n");
	LPUART1_transmit_string("------------[USER INTRUCTION]------------\n");
	LPUART1_transmit_string("-----------------------------------------\n\n");
	LPUART1_transmit_string("-->BAM NUT 1 DE THAY DOI HIEN THI\n");
	LPUART1_transmit_string("----------AUTO/GIO/THANG/ALARM-----------\n\n");
	LPUART1_transmit_string("-->BAM NUT 2 DE DIU CHINH CUONG DO SANG\n");
	LPUART1_transmit_string("-------5 MUC DO SANG TU MAX TOI OFF------\n\n");
	LPUART1_transmit_string("-->THAY DOI GIO/THANG/ALARM\n");
	LPUART1_transmit_string("--NHAP THEO FORMAT:\n");
	LPUART1_transmit_string("[T-hh-mm-ss] 	DE THAY DOI GIO\n");
	LPUART1_transmit_string("[D-dd-mm-yyyy] DE THAY DOI NGAY\n");
	LPUART1_transmit_string("[A-hh-mm-ss]	  DE THAY DOI ALARM\n");
	LPUART1_transmit_string("!Vi du: nhap T-hh-mm-ss la format dung\n\n");
	LPUART1_transmit_string("!! KHI XUAT HIEN BAO THUC THI BAM 1 TRONG 2 NUT DE TAT DEN BAO\n");
}

void Check_Mode(void)
{
	switch (Display_Mode[G_mode])
	{
	case 0:

		if ((CurTime - PreTime) <= 5)
		{
			DisplayClock(Time);
		}
		else
		{
			DisplayDate();
			if ((CurTime - PreTime) > 7)
			{
				PreTime = CurTime;
			}
		}
		break;
	case 1:
		DisplayDate();
		break;
	case 2:
		DisplayClock(Time);
		break;
	case 3:
		DisplayClock(Alarm);
		break;
	case 4:
		LPIT_REG->SETTEN = 0x00000002; // enable LPIT1
		DisplayClock(Time);
		break;
	}
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Check_Alarm
 * Description   : This function is designed to calculate the remaining time before the alarm clock goes off.
When called, the function will perform the following steps:
Get the current time information: The function will access the system to get the current time information (e.g., hour, minute, second).
Get the alarm time information: The function will access the alarm setting information to get the alarm time information (e.g., hour, minute, second).
Calculate the remaining time: The function will compare the current time information with the alarm time information to calculate the remaining time before the alarm clock goes off.
 *
 * Implements    : Main.c
 *END**************************************************************************/
void Check_Alarm(void)
{
	if ((Time[H_Y] - Alarm[H_Y] == 0) && (Time[M_M] - Alarm[M_M] == 0) && (Time[S_D] - Alarm[S_D] == 0))
		G_mode = 4;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_Bright_Lv
 * Description   : This function is designed to check the light brightness variable 
and adjust the light brightness based on the variable value
 *
 * Implements    : Main.c
 *END**************************************************************************/
void Check_Bright_Lv(void)
{
	if (Led_Bright_Lv[Bright_Lv] == 0)
	{
		LPSPI0_transmit(0xC00); // Turn off
	}
	else if (Led_Bright_Lv[Bright_Lv] == 1)
	{
		// Enable_LED();
		LPSPI0_transmit(0xC01); // Normal operation
		Bright_Lv = 0;
	}
	DisplayDigit(Add[10], Seg[Led_Bright_Lv[Bright_Lv]]);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Check_Valid
 * Description   : This function is designed to validate the format of the time input by the user. 
When called, the function will perform the following steps:

Determine the time format: The function will use the provided input information 
(e.g., time string) to determine the time format used ([T-hh-mm-ss],).
Validate the time value: The function will check each part
of the time value (e.g., day, month, year, hour, minute, second) 
to ensure that they are within a valid range (e.g., day from 1 to 31, month from 1 to 12, etc.).
 *
 * Implements    : Main.c
 *END**************************************************************************/
	int Check_Valid(volatile char arr[])
{
	for (int i = 1; i < Word_Count; i++)//Check input data is right format
    {
        if (arr[i] == '-')
        {
            continue;
        }
        else if (arr[i] < '0' || arr[i] > '9')
        {
            return INVALID;
        }
    }
    int Hour, Minute, Second; 
		int Year=0,Month=0,Day=0;
   switch (arr[0])
    {
    case 'D':
    case 'd':
		sscanf(UART_receive_data, "D-%d-%d-%d",&Day , &Month, &Year);
    if(!(Check_Valid_date(Day,Month,Year)))
		{
			return INVALID;
		}else{
			Date[S_D]=(unsigned int) Day;
			Date[M_M]=(unsigned int) Month;
			Date[H_Y]=(unsigned int) Year;	
			return VALID;	
		}		
		
    case 'A':
    case 'a':
 		sscanf(UART_receive_data, "A-%d-%d-%d", &Hour, &Minute, &Second);
        if (Second > 59 || Minute> 59 || Hour > 23)
        {
            return INVALID;
        }else{
			Alarm[S_D]=(unsigned int) Second;
			Alarm[M_M]=(unsigned int) Minute;
			Alarm[H_Y]=(unsigned int) Hour;
        }
						return VALID;
				
		case 'T':
    case 't':
		sscanf(UART_receive_data, "T-%d-%d-%d",&Second , &Minute,&Hour );
        if (Second > 59 || Minute> 59 || Hour > 23)
        {
            return INVALID;
        }else{
			Time[S_D]=(unsigned int) Hour;
			Time[M_M]=(unsigned int) Minute;
			Time[H_Y]=(unsigned int) Second;
        }
				return VALID;
				default:
        return INVALID;
}    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_Valid_date
 * Description   : The function will validate the validity of each component 
(e.g., day must be between 1 and 31, month must be between 1 and 12, year must be a positive number) 
 *
 * Implements    : Main.c
 *END**************************************************************************/
int Check_Valid_date(int Day, int Month, int Year)
	{
    if (Year < 1) {
        return INVALID;
    }

    if (Month < 1 || Month > 12) {
        return INVALID;
    }

    int Days_of_month = 31;
    switch (Month) {
        case 4: case 6: case 9: case 11:
            Days_of_month = 30;
            break;
        case 2:
            Days_of_month = LeapYearCheck(Year) ? 29 : 28;
            break;
    }
    if (Day < 1 || Day > Days_of_month) {
        return INVALID;
    }
    return VALID;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LeapYearCheck
 * Description   : The function will validate Leap year *
 * Implements    : Main.c
 *END**************************************************************************/
int LeapYearCheck(int Leap_Year) 
{
    return (Leap_Year % 4 == 0 && (Leap_Year % 100 != 0 || Leap_Year % 400 == 0));
}

