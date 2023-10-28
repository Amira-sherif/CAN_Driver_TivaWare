/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mahmoud Badr
 *	   	   File:  TM4C123xx.h
 *		  Layer:  LIB
 *       Module:  TM4C123xx
 *		Version:  1.00
 *	
 *  Description:  Register Defination       
 *  
 *********************************************************************************************************************/
 #ifndef TM4C123XX_H
 #define TM4C123XX_H
 
/******************************************** SC Peripheral Definition  **********************************************/

#define SYSCTL_BASE_ADDRESS                         0x400FE000UL

#define SYSCTL_GPIOHBCTL                            *((volatile uint32*)(SYSCTL_BASE_ADDRESS+0x06c))

#define SYSCTL_RCGCGPIO                             *((volatile uint32*)(SYSCTL_BASE_ADDRESS+0x608))

#define SYSCTL_RCGCWD                               *((volatile uint32*)(SYSCTL_BASE_ADDRESS+0x600))

/******************************************** SYSCTL Registers Definition    *********************************************/
typedef struct
{
    volatile uint32 DID0;
    volatile uint32 DID1;
    uint32 Reserved[11];
    volatile uint32 PBORCTL;
    uint32 Reserved2[8];
    volatile uint32 RIS;
    volatile uint32 IMC;
    volatile uint32 MISC;
    volatile uint32 RESC;
    volatile uint32 RCC;
    uint32 Reserved3[3];
    volatile uint32 GPIOHBCTL;
    volatile uint32 RCC2;
    uint32 Reserved4[3];
    volatile uint32 MOSCCTL;
    uint32 Reserved5[50];
    volatile uint32 DSLPCLKCFG;
    uint32 Reserved6[2];
    volatile uint32 SYSPROP;
    volatile uint32 PIOSCCAL;
    volatile uint32 PIOSCSTAT;
    uint32 Reserved7[3];
    volatile uint32 PLLFREQ0;
    volatile uint32 PLLFREQ1;
    volatile uint32 PLLSTAT;
    uint32 Reserved8[8];
    volatile uint32 SLPPWRCFG;
    volatile uint32 NDSLPPWRCFG;
}SYSCRL_RegDef_t;
/******************************************** GPIO Peripheral Definition *********************************************/

#define GPIOA_BASE_ADDRESS					0x40004000UL
#define GPIOB_BASE_ADDRESS					0x40005000UL
#define GPIOC_BASE_ADDRESS					0x40006000UL
#define GPIOD_BASE_ADDRESS					0x40007000UL
#define GPIOE_BASE_ADDRESS					0x40024000UL
#define GPIOF_BASE_ADDRESS					0x40025000UL


/******************************************** GPIO Registers Definition **********************************************/

typedef struct
{
	volatile uint32 DATA[256];           /*GPIO Data*/
	volatile uint32 DIR;                 /*GPIO Direction*/
	volatile uint32 IS;                  /*GPIO Interrupt Sense*/
	volatile uint32 IBE;                 /*GPIO Interrupt Both Edges*/
	volatile uint32 IEV;                 /*GPIO Interrupt Event*/
	volatile uint32 IM;                  /*GPIO Interrupt Mask*/
	volatile uint32 RIS;                 /*GPIO Raw Interrupt Status*/
	volatile uint32 MIS;                 /*GPIO Masked Interrupt Status*/
	volatile uint32 ICR;                 /*GPIO GPIO Interrupt Clear*/
	volatile uint32 AFSEL;               /*GPIO Alternate Function Select*/
	uint32 Reserved[55];
	volatile uint32 DRxR[3];             /*GPIO x-mA Drive Select*/
	volatile uint32 ODR;                 /*GPIO Open Drain Select*/
	volatile uint32 PxR[2];              /*GPIO Pull-Up-Down Select*/
	volatile uint32 SLR;                 /*GPIO Slew Rate Control Select*/
	volatile uint32 DEN;                 /*GPIO Digital Enable*/
	volatile uint32 LOCK;                /*GPIO Lock*/
	volatile uint32 CR;                  /*GPIO Commit*/
	volatile uint32 AMSEL;               /*GPIO Analog Mode Select*/
	volatile uint32 PCTL;                /*GPIO Port Control*/
	volatile uint32 ADCCTL;              /*GPIO ADC Control*/
	volatile uint32 DMACTL;              /*GPIO DMA Control*/
}GPIO_RegDef_t;

#define GPIOA							((GPIO_RegDef_t*) GPIOA_BASE_ADDRESS)
#define GPIOB                           ((GPIO_RegDef_t*) GPIOB_BASE_ADDRESS)
#define GPIOC                           ((GPIO_RegDef_t*) GPIOC_BASE_ADDRESS)
#define GPIOD                           ((GPIO_RegDef_t*) GPIOD_BASE_ADDRESS)
#define GPIOE                           ((GPIO_RegDef_t*) GPIOE_BASE_ADDRESS)
#define GPIOF                           ((GPIO_RegDef_t*) GPIOF_BASE_ADDRESS)

/******************************************** STK Peripheral Definition *********************************************/

#define STK_BASE_ADDRESS					0xE000E010UL

/******************************************** STK Registers Definition **********************************************/

typedef struct
{
	volatile uint32 CTRL;				/*SysTick Control and Status Register*/
	volatile uint32 LOAD;              /*SysTick Reload Value Register*/
	volatile uint32 CURRENT;           /*SysTick Current Value Register*/
}STK_RegDef_t;

#define STK                             ((STK_RegDef_t*) STK_BASE_ADDRESS)

/******************************************** NVIC Peripheral Definition *********************************************/

#define NVIC_BASE_ADDRESS					0xE000E100UL

/******************************************** NVIC Registers Definition **********************************************/

typedef struct
{
	volatile uint32 EN[5];                    /*Interrupt Set Enable*/
	uint32 Reserved[27];
	volatile uint32 DIS[5];                   /*Interrupt clear Enable*/
	uint32 Reserved2[27];
	volatile uint32 PEND[5];                  /*Interrupt Set Pending*/
	uint32 Reserved3[27];
	volatile uint32 UNPEND[5];                /*Interrupt clear Pending*/
	uint32 Reserved4[27];
	volatile uint32 ACTIVE[5];                /*Interrupt Active Bit*/
	uint32 Reserved5[59];
	volatile uint8 PRI[140];                  /*Interrupt Priority*/
	volatile uint32 SWTRIG;				   /*Software Trigger Interrupt*/
}NVIC_RegDef_t;

#define NVIC						((NVIC_RegDef_t*) NVIC_BASE_ADDRESS)

/******************************************** SCB Peripheral Definition *********************************************/

#define SCB_BASE_ADDRESS					0xE000ED00UL

/******************************************** NVIC Registers Definition **********************************************/

typedef struct
{
	volatile uint32 CPUID;                     /*CPU ID Base*/
	volatile uint32 INTCTRL;                   /*Interrupt Control and State*/
	volatile uint32 VTABLE;                    /*Vector Table Offset*/
	volatile uint32 APINT;                     /*Application Interrupt and Reset Control*/
	volatile uint32 SYSCTRL;                   /*System Control*/
	volatile uint32 CFGCTRL;                   /*Configuration and Control*/
	volatile uint32 SYSPRI[3];                 /*System Handler Priority*/
	volatile uint32 SYSHNDCTRL;                /*System Handler Control and State*/
	volatile uint32 FAULTSTAT;                 /*Configurable Fault Status*/
	volatile uint32 HFAULTSTAT;                /*Hard Fault Status*/
	uint32 Reserved[2];
	volatile uint32 MMADDR;                    /*Memory Management Fault Address*/
	volatile uint32 FAULTADDR;                 /*Bus Fault Address*/
}SCB_RegDef_t;

#define SCB							((SCB_RegDef_t*)SCB_BASE_ADDRESS)

#endif	/*TM4C123XX_H*/
/**********************************************************************************************************************
 *  END OF FILE: TM4c123xx.h
 *********************************************************************************************************************/
