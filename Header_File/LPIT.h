#define LPIT__H__

#define LPIT_base_address 0x40037000
typedef struct LPIT_struct
{
    const volatile unsigned int VERID;
    const volatile unsigned int PARAM;
    volatile unsigned int MCR;
    volatile unsigned int MSR;
    volatile unsigned int MIER;
    volatile unsigned int SETTEN;
    volatile unsigned int CLRTEN;
		char res_0[4];
    volatile unsigned int TVAL0;
    const volatile unsigned int CVAL0;
    volatile unsigned int TCTRL0;
		char res_1[4];
    volatile unsigned int TVAL1;
    const volatile unsigned int CVAL1;
    volatile unsigned int TCTRL1;
		char res_2[4];
		volatile unsigned int TVAL2;
    const volatile unsigned int CVAL2;
    volatile unsigned int TCTRL2;
		char res_3[4];
    volatile unsigned int TVAL3;
    const volatile unsigned int CVAL3;
    volatile unsigned int TCTRL3;
}LPIT_TYPE;

#define LPIT_REG ((LPIT_TYPE *)LPIT_base_address)
