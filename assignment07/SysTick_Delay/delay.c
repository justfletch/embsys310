#include "delay.h"

extern unsigned int delayInterruptCounts;

void delay(unsigned int delayInMilliseconds)
{
    delayInterruptCounts = delayInMilliseconds;
    while (delayInterruptCounts > 0)
    {
        //wait for SysTick timer to decrement delayInterruptsCounts to 0
    }
}