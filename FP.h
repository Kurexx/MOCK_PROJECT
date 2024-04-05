/*FUNCTION PROTOTYPE*/

// CLOCK
extern void Clock_init(void);

// LPSPI
extern void LPSPI0_init_master(void);
extern void LPSPI0_transmit(unsigned short SPI_data);

// LPUART
extern void LPUART1_init(void);
extern void LPUART1_transmit_char(volatile char send);
extern void LPUART1_transmit_string(volatile char data_string[]);


//PORT/PCC/GPIO
extern void PORT_init(void);

// LPIT
extern void LPIT_init(void);

// Interrupt Handler
extern void LPUART1_RxTx_IRQHandler(void);
extern void LPIT0_Ch0_IRQHandler(void);
extern void LPIT0_Ch1_IRQHandler (void);
extern void LPSPI1_init_master(void);
extern void PORTC_IRQHandler(void);

//  DISPLAY
extern void Time_cal(void);
extern void Enable_LED(void);
extern void DisplayDigit(unsigned short Address, unsigned short Number);
extern void DisplayDate(void);
extern void DisplayClock(volatile unsigned int *Clock);
extern void Check_Mode(void);
extern void Check_Alarm(void);
extern void Check_Bright_Lv(void);

//VALIDATION
extern int Check_Valid(volatile char arr[]);
extern int Check_Format(char Data[]);

// GLOBAL VARIABLES
extern volatile int Led_Toggle_Count;
extern volatile unsigned int Time[3];
extern volatile unsigned int Date[3];
extern volatile unsigned int Alarm[3];
extern volatile int CurTime;
extern volatile int PreTime;
extern volatile char Display_Mode[5];
extern volatile int Led_Bright_Lv[6];
extern volatile int G_mode;
extern volatile int Bright_Lv;
extern  char UART_receive_data[20];
#define H_Y 0
#define M_M 1
#define S_D 2
#define AUTO_M 0
#define DATE_M 1
#define TIME_M 2
#define ALARM_OCCUR 4
#define INVALID 0
#define VALID 1
extern int flag;


extern volatile int Word_Count;
