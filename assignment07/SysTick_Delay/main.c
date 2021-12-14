#include "delay.h"
#include "stm32l475xx.h"
#include "stm32l4xx_it.h"

// LD1 --> PA5 -- Homework
// LD2 --> PB14 -- In Class

#define SYS_CLOCK_HZ 4000000u   // Default clock after startup
// Section 3.11 in STM32L475 datasheet DS10969

//1ms = 1sec/1000. 4,000,000 hz, so 4,000,000 counts per second. 
//4,000,000/1sec = 1sec/1000
//4,000,000/1000 = 4,000 counts per ms
#define SYS_CLOCK_MS_TICKS 4000u;

unsigned int delayInterruptCounts;

void SysTick_Initialize(void);

void main(void)
{
  // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)
  
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
  
  // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
  // PA5 mode is controlled by MODER5[1:0], which is bit 10 & bit 11 of it's GPIO mode register. Set MODER5[1:0] to 0x01
  GPIOA->MODER &= ~GPIO_MODER_MODE5_1; //set GPIOA MODER5[1] zero
  GPIOA->MODER |= GPIO_MODER_MODE5_0; //set GPIOA MODER5[0] one
  
  SysTick_Initialize();
  
  while(1)
  {
    GPIOA->ODR ^= GPIO_ODR_OD5;
    delay(500);
  }    
}

void SysTick_Initialize(void)
{
  //this is one second
  //SysTick->LOAD = SYS_CLOCK_HZ - 1;    // 0xE000E014 - Counts down to 0.
  //this is one millisecond
  SysTick->LOAD = SYS_CLOCK_MS_TICKS - 1;
  SysTick->VAL = 0x0;                     // 0xE000E018 - Clears initial value
  SysTick->CTRL = 0x7;                    // 0xE000E010 - Enable interrupts
}

void SysTick_Handler(void)
{
  //decrement the delay counter if it is set above 0
  if(delayInterruptCounts > 0) {
    delayInterruptCounts--;
  }
}
