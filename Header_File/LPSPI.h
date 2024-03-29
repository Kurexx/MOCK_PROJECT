#define LPSPI__H__
#define LPSPI0_base_address (0x4002C000u)
#define LPSPI1_base_address (0x4002D000u)
#define LPSPI2_base_address (0x4002E000u)
typedef struct
{
    const volatile unsigned int VERID; // read only
    const volatile unsigned int PARAM; // read only
    char res_0[8];
    volatile unsigned int CR;
    volatile unsigned int SR;
    volatile unsigned int IER;
    volatile unsigned int DER;
    volatile unsigned int CFGR0;
    volatile unsigned int CFGR1;
    char res_1[8];
    volatile unsigned int DMR0;
    volatile unsigned int DMR1;
    char res_2[8];
    volatile unsigned int CCR;
    char res_3[20];
    volatile unsigned int FCR;
    const volatile unsigned int FSR; // read only
    volatile unsigned int TCR;
    volatile unsigned int TDR;
    char res_4[8];
    const volatile unsigned int RSR; // read only
    const volatile unsigned int RDR; // read only
} LPSPI_Type;

#define LPSPI0_REG ((LPSPI_Type *)LPSPI0_base_address)
#define LPSPI1_REG ((LPSPI_Type *)LPSPI1_base_address)
#define LPSPI2_REG ((LPSPI_Type *)LPSPI2_base_address)
