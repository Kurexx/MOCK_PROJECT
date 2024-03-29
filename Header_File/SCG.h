#define SCG__H__

#define SCG_BASE 0x40064000

typedef struct SCG_struct
{
    const volatile unsigned int VERID; // 0
    const volatile unsigned int PARAM; // 4
    char res_0[8];
    const volatile unsigned int CSR;  // 10
    volatile unsigned int RCCR;       // 14
    volatile unsigned int VCCR;       // 18
    volatile unsigned int HCCR;       // 1C
    volatile unsigned int CLKOUTCNFG; // 20
    char res_1[220];
    volatile unsigned int SOSCCSR; // 100
    volatile unsigned int SOSCDIV; // 104
    volatile unsigned int SOSCCFG; // 108
    char res_2[244];
    volatile unsigned int SIRCCSR; // 200
    volatile unsigned int SIRCDIV; // 204
    volatile unsigned int SIRCCFG; // 208
    char res_3[244];
    volatile unsigned int FIRCCSR; // 300
    volatile unsigned int FIRCDIV; // 304
    volatile unsigned int FIRCCFG; // 308
    char res_4[756];
    volatile unsigned int SPLLCSR; // 600
    volatile unsigned int SPLLDIV; // 604
    volatile unsigned int SPLLCFG; // 608
} SCG_type;

#define SCG ((SCG_type *)SCG_BASE)

// Resigter SCG
#define SCG_SOSCCSR_SOSCVLD_MASK (1u << 24) // Valid
#define SCG_SOSCCSR_LK_MASK (1u << 23)      // Lock Resigter
// Resigter SOSC feature

#define SCG_SOSCCSR_SOSCVLD_MASK (1u << 24) // Valid
#define SCG_SOSCCSR_LK_MASK (1u << 23)      // Lock Resigter

// Resigter SIRC	feature

#define SCG_SIRCCSR_SIRCVLD_MASK (1u << 24) // Valid
#define SCG_SIRCCSR_LK_MASK (1u << 23)      // Lock Resigter

// Resigter FIRC	feature

#define SCG_FIRCCSR_FIRCVLD_MASK (1u << 24) // Valid
#define SCG_FIRCCSR_LK_MASK (1u << 23)      // Lock Resigter
#define SCG_FIRCCSR_FIRCVLD_SHIFT 24 
// Resigter SPLL	feature

#define SCG_SPLLCSR_SPLLVLD_MASK (1u << 24) // Valid
#define SCG_SPLLCSR_LK_MASK (1u << 23)      // Lock Resigter
#define SCG_SPLLCSR_SPLLVLD_SHIFT 24 
// Resisgter CSR mask
#define SCG_CSR_SCS_MASK (6u << 24)
#define SCG_CSR_SCS_SHIFT 24

