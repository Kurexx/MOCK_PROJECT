#include ".\Header_File\LPUART.h"
#include ".\Header_File\PCC.h"

void LPUART1_init(void);
void LPUART1_transmit_char(char send);
void LPUART1_transmit_string(char data_string[]);


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
																		/* ILIE=1 interupt requested when IDLE flag is 1 */
																		/* PE=1 Parity enabled*/
																		/* PT=1 Even parity*/
																		/* RIE=1 Receiver Interrupt Enable */	
}

/* Function to Transmit single Char */
void LPUART1_transmit_char(char send)
{ /* Function to Transmit single Char */
	while ((LPUART1_REG->STAT & LPUART_STAT_TDRE_MASK) >> LPUART_STAT_TDRE_SHIFT == 0)
		;
	/* Wait for transmit buffer to be empty */
	LPUART1_REG->DATA = send; /* Send data */
}


/* Function to Transmit whole string */
void LPUART1_transmit_string(char data_string[])
{ /* Function to Transmit whole string */
	volatile unsigned int i = 0;
	while (data_string[i] != '\0')
	{ /* Send chars one at a time */
		LPUART1_transmit_char(data_string[i]);
		i++;
	}
}

