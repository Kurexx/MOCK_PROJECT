#ifndef pin_mux_H_
#define PCC__H__

#ifndef PCR__H__
#include "PCR.H"
#endif

#define PCC_BASE 0x40065000

typedef struct PCC_struct
{
  char res_0[128];
  volatile unsigned int FTFC;   // 80
  volatile unsigned int DMAMUX; // 84
  char res_1[8];
  volatile unsigned int FlexCAN0; // 90
  volatile unsigned int FlexCAN1; // 94
  volatile unsigned int FTM3;     // 98
  volatile unsigned int ADC1;     // 9C
  char res_2[12];
  volatile unsigned int FlexCAN2; // AC
  volatile unsigned int LPSPI0;   // B0
  volatile unsigned int LPSPI1;   // B4
  volatile unsigned int LPSPI2;   // B8
  char res_3[8];
  volatile unsigned int PDB1; // C4
  volatile unsigned int CRC;  // C8
  char res_4[12];
  volatile unsigned int PDB0; // D8
  volatile unsigned int LPIT; // DC
  volatile unsigned int FTM0; // E0
  volatile unsigned int FTM1; // E4
  volatile unsigned int FTM2; // E8
  volatile unsigned int ADC0; // EC
  char res_5[4];
  volatile unsigned int RTC; // F4
  char res_6[8];
  volatile unsigned int LPTMR0; // 100
  char res_7[32];
  volatile unsigned int PORTA; // 124
  volatile unsigned int PORTB; // 128
  volatile unsigned int PORTC; // 12C
  volatile unsigned int PORTD; // 130
  volatile unsigned int PORTE; // 134
  char res_8[24];
  volatile unsigned int SAI0; // 150
  volatile unsigned int SAI1; // 154
  char res_9[16];
  volatile unsigned int FlexIO; // 168
  char res_10[24];
  volatile unsigned int EWM; // 184
  char res_11[16];
  volatile unsigned int LPI2C0; // 198
  volatile unsigned int LPI2C1; // 19C
  char res_12[8];
  volatile unsigned int LPUART0; // 1A8
  volatile unsigned int LPUART1; // 1AC
  volatile unsigned int LPUART2; // 1B0
  char res_13[4];
  volatile unsigned int FTM4; // 1B8
  volatile unsigned int FTM5; // 1BC
  volatile unsigned int FTM6; // 1C0
  volatile unsigned int FTM7; // 1C4
  char res_14[4];
  volatile unsigned int CMP0; // 1CC
  char res_15[8];
  volatile unsigned int QSPI; // 1D8
  char res_16[8];
  volatile unsigned int ENET; // 1E4
} PCC_TYPE;

#define PCC ((PCC_TYPE *)PCC_BASE)
#define PCC_PCCn_CGC_MASK (1u<<30)

#endif
