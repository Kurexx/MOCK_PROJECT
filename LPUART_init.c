#include ".\Header_File\LPUART.h"
#include ".\Header_File\PCC.h"
#include "FP.h"
#include "stdio.h"
#include "string.h"

 char UART_receive_data[20];
volatile int Word_Count =0;
int flag =0;


/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_init
 * Description   : The function will initilize UART
 * Implements    : LPUART1
 *END**************************************************************************/
void LPUART1_init(void) /* Init. summary: 38400 baud, 1 stop bit, 8 bit format, even parity */
{
    PCC->LPUART1 = 0x46000000; 	  	/* Enable clock for LPUART1 regs */
																	  /* Clock Src= 6 (SPLLDIV2_CVK) */
    LPUART1_REG->BAUD = 0x0D000043; /* Initialize for 38400 baud, 1 stop: */
                                    /* SBR=67 (0x43): baud divisor = 36Mhz/(38400*14) = 67 */
                                    /* OSR=13: Over sampling ratio = 13+1=14 */
                                    /* SBNS=0: One stop bit */									
    LPUART1_REG->CTRL = 0x003C0016; /* Enable transmitter & receiver, even parity, 9 bit char: */
																		/* RE=1: Receiver enabled */
																		/* TE=1: Transmitter enabled */
																		/* ILT=1 Idle char count after stop bit*/
																		/* PE=1 Parity enabled*/
																		/* PT=1 Even parity*/
																		/* RIE=1 Receiver Interrupt Enable */	
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_transmit_char
 * Description   : Function to Transmit single Char
 * Implements    : LPUART1
 *END**************************************************************************/
void LPUART1_transmit_char(volatile char send)
{ /* Function to Transmit single Char */
	while((LPUART1_REG->STAT &(1u<<23))!=(1u<<23));
	LPUART1_REG->DATA = send; /* Send data */
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_transmit_string
 * Description   : Function to Transmit whole string
 * Implements    : LPUART1
 *END**************************************************************************/
void LPUART1_transmit_string(volatile char data_string[])
{ /* Function to Transmit whole string */
	volatile unsigned int i = 0;
	while (data_string[i] != 0)
	{ /* Send chars one at a time */
		LPUART1_transmit_char(data_string[i]);
		i++;
	}
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART1_RxTx_IRQHandler
 * Description   : Handle UART interrupt, when this function is called
if RDRF pin is 1 receive data from terminal, when IDLE pin is 1: clear IDLE and increase flag to 1
 * Implements    : LPUART1
 *END**************************************************************************/
void LPUART1_RxTx_IRQHandler (void)
{
	if((LPUART1_REG->STAT &(1u<<21)) ==(1u<<21))
{
	UART_receive_data[Word_Count]= (char) LPUART1_REG->DATA;
		Word_Count++;
}

if((LPUART1_REG->STAT &(1u<<20)) ==(1u<<20))
	{LPUART1_REG->STAT |= (1u<<20);
		flag=1;
	}
}
