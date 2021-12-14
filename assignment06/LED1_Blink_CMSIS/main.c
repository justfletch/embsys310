#include "stm32l475xx.h"

//Using CMSIS. Need to set "Use CMSIS" in library options for other CMSIS files.

volatile int counter=0;

void main(void)
{     
    // RCC AHB2 peripheral clock enable register (RCC_AHB2ENR)

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    
    // GPIO port mode register (GPIOx_MODER) (x = A..E and H)
    // PA5 mode is controlled by MODER5[1:0], which is bit 10 & bit 11 of it's GPIO mode register. Set MODER5[1:0] to 0x01
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1; //set GPIOA MODER5[1] zero
    GPIOA->MODER |= GPIO_MODER_MODE5_0; //set GPIOA MODER5[0] one
    
    
    while(1)
    {
       // GPIOB->ODR |= GPIO_ODR_OD14;
      if(counter >= 50000) {
        //GPIO Port A, output register 5 toggle (PA5, for LED1)
        GPIOA->ODR ^= GPIO_ODR_OD5;
        counter = 0;
      }
        counter++;
    }    
    

}

