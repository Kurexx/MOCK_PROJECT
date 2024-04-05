#include ".\Header_File\LPSPI.h"
#include ".\Header_File\PCC.h"
#include "FP.h"



/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI0_init_master
 * Description   : This function will initilize SPI0
 * Implements    : LPIT
 *END**************************************************************************/
 void LPSPI0_init_master(void)
{
	unsigned int TCR_mask =((2u<<27)|(2u<<24)|(15u<<0));
	PCC->LPSPI0 &=~(PCC_PCCn_CGC_MASK);
	PCC->LPSPI0 |=(PCC_PCCn_CGC_MASK| (6u<<24)); //CLK option 6 SPLL_DIV2 (36Mhz)
  LPSPI0_REG->CR =0; //Disable module for config
	LPSPI0_REG->CFGR1 = 0x00000009; 	/* MASTER=1: Master mode */
																		/* NOSTALL FIFO underun  */
	LPSPI0_REG->TCR =TCR_mask;
																		/* CPOL=0: SCK inactive state is low */
																		/* CPHA=0: Change data on SCK lead edge,  changed on following edge*/
																		/* PRESCALE=2: Functional clock divided by 4 = 36/4=9(Mhz) =(111ns) */
																		/* PCS=2: Transfer using PCS2 */
																		/* FRAMESZ=15: # bits in frame =15+1=16 */
	LPSPI0_REG->CCR =0;															
																		/* SCKPCS=0: SCK to PCS delay  = 2 		(222ns)  */
																		/* PCSSCK=0: PCS to SCK delay = 1 		(111ns) */
																		/* DBT=0: Delay between Transfers = 1 (111ns) */
																		/* SCKDIV=0: SCK period = 2		  			(222ns)  */		
	LPSPI0_REG->FCR = 0x0000000;	
																		/* RXWATER=0: Rx flags set when Rx FIFO >0 */
																		/* TXWATER=0: Tx flags set when Tx FIFO <= 3 */
																		
	LPSPI0_REG->CR = 0x00000009; 			/* Enable module for operation */
																		/* DBGEN=1: module enabled in debug mode */
																		/* MEN=1: Module is enabled */					
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSPI0_transmit
 * Description   : This function will transmit data to device
 * Implements    : LPIT
 *END**************************************************************************/
void LPSPI0_transmit(unsigned short SPI_data)
{
	while((LPSPI0_REG->SR & (1u<<0))>>0 ==0){}
	 LPSPI0_REG->TDR = SPI_data ;
		LPSPI0_REG->SR &= ~(1u<<0);
}

