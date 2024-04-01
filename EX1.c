#include ".\Header_File\Header.h"
#include "LED.h"
#include "FP.h"
#include "stdio.h"
/* GLOBAL VALRIABLES INIT*/
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

void Check_Mode(void);
void Check_Alarm(void);
void Check_Bright_Lv(void);
void Menu(void);
int Check_Format(char *Data);
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
	while (1)
	{
	}
}
void Menu(void)
{
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

void Check_Alarm(void)
{
	if ((Time[H_Y] - Alarm[H_Y] == 0) && (Time[M_M] - Alarm[M_M] == 0) && (Time[S_D] - Alarm[S_D] == 0))
		G_mode = 4;
}

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

int Check_Format(char Data[])
{
	unsigned int Hour_Year, Minute_Month, Second_Day;
	for (unsigned int i = 1; i < sizeof(&Data); i++)
	{
		if (Data[i] == '-')
		{
			continue;
		}
		else if (Data[i] < '0' || Data[i] > '9')
			return INVALID;
	}
	switch (Data[0])
	{
	case 'T':
		sscanf(Data, "T-%d-%d-%d", &Hour_Year, &Minute_Month, &Second_Day);
		Time[S_D] = Second_Day;
		Time[M_M] = Minute_Month;
		Time[H_Y] = Hour_Year;
		break;
	case 'D':
		sscanf(Data, "D-%d-%d-%d", &Hour_Year, &Minute_Month, &Second_Day);
		Date[S_D] = Second_Day;
		Date[M_M] = Minute_Month;
		Date[H_Y] = Hour_Year;
		break;
	case 'A':
		sscanf(Data, "A-%d-%d-%d", &Hour_Year, &Minute_Month, &Second_Day);
		Alarm[S_D] = Second_Day;
		Alarm[M_M] = Minute_Month;
		Alarm[H_Y] = Hour_Year;
		break;
	default:
		return INVALID;
	}
	return VALID;
}

