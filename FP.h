/*FUNCTION PROTOTYPE*/

extern void SOSC_init_8MHz(void);
extern void SPLL_init_72Mhz (void);
extern void RUNmode_72MHz (void);

extern void LPSPI0_init_master(void);
extern void LPSPI0_transmit(unsigned short SPI_data);


extern void LPUART1_init(void);
extern void LPUART1_transmit_char(char send);
extern void LPUART1_transmit_string(char data_string[]);

extern void PORT_init(void);



