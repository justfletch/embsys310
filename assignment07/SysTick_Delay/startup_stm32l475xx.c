#include "stm32l4xx_it.h"


#pragma section="CSTACK"

void __iar_program_start(void);

void Unused_Handler(void);

//const to keep in ROM
int const __vector_table[] @ ".intvec" = {
  
  //iar method for getting end of stack
    (int)__section_end("CSTACK"),    // Pointer to Top of Stack, sets SP
    //iar name for where to start executing the program
    (int)&__iar_program_start,       // Pointer to Reset Handler, sets PC
    (int)&NMI_Handler,
    (int)&HardFault_Handler,
    (int)&MemManage_Handler,
    (int)&BusFault_Handler,
    (int)&UsageFault_Handler,
    0,      // Reserved
    0,      // Reserved
    0,      // Reserved
    0,      // Reserved
    (int)&SVC_Handler,
    (int)&DebugMon_Handler,
    0,      // Reserved
    (int)&PendSV_Handler,
    (int)&SysTick_Handler
};

void NMI_Handler(void)
{
    while(1)
    {
    }
}

// When the SP register drops below the start of RAM,
// the processor enters the HardFault exception
void HardFault_Handler(void)
{
    Unused_Handler();
}

void MemManage_Handler(void)
{
    while(1)
    {
    }
}

void BusFault_Handler(void)
{
    while(1)
    {
    }
}

void UsageFault_Handler(void)
{
    while(1)
    {
    }
}

void Unused_Handler(void)
{
    while(1)
    {
    }
}

#pragma weak SVC_Handler = Unused_Handler
#pragma weak DebugMon_Handler = Unused_Handler
#pragma weak PendSV_Handler = Unused_Handler

//overriding SysTick_Handler in main
#pragma weak SysTick_Handler = Unused_Handler

// The below is another way of achieving the above...
//__weak void SVC_Handler(void)
//{
//    Unused_Handler();
//}
//
//__weak void DebugMon_Handler(void)
//{
//    Unused_Handler();
//}
//
//__weak void PendSV_Handler(void)
//{
//    Unused_Handler();
//}
//
//__weak void SysTick_Handler(void)
//{
//    Unused_Handler();
//}
