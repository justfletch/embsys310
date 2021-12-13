
# Assignment 04 Questions

>### 1. Follow the same steps as we did in the class to blink LED1 (PA5) at a visible rate using the bit-band region to enable the clock for Port A, then answer the following:
>a. What instructions does the compiler produce in assembly for “writing” to the RCC_AHB2ENR bit when using bit-band address?

It was a store (STR) instruction of the value of R0 (0x1) directly to 0x42420980, which is the address of the GPIOA port block enable bit.

 >b. What were the instructions produced when writing to the RCC_AHB2ENR without using bit-banding?

The whole RCC_AHB2ENR register value is loaded into R1. It is then bit-wise OR'd with 0x1 (ORRS.W) back into R1. The new value in R1 is then stored back to the RCC_AHB2ENR register.

>### 2. Create a function “func1” with 5 arguments and call “func1” from within another function “func2”. Trace thru the assembler and note:
>a. How does the calling function “func2” pass the values to the called function “func1”?

Input5 was stored (STR.W) to the SP
Input4 is stored in R3
Input3 is stored in R2
Input2 is stored in R1
Input1 is stored in R0

>b. What extra code did the compiler generate before calling the function “func1” with the multiple arguments?

At the start of func2, R2-R8 and the Link Register are pushed to the stack. R4-R8 are used for the input1-5 variables, before moving to the registers shown in (a.).

>c. What extra code did the compiler generate inside the called function “func1” with the list of multiple arguments?

At the start of func1, R4-R8 and the Link register are pushed to the stack. The fifth input is loaded directly from the address in the stack. After the addition is complete, the return pops R4-R8 and PC from the stack. So PC is set to what the LR was at the beginning.

>d. Any other observations?

LR is used as a register for one of the input values during the addition process, which is probably why it was also pushed to the stack. The LR in func2 is popped from the stack into the PC when it returns. 

Adding more arguments (7 total) and looking at how they are handled shows that the stack gets used in an interesting way. The arguments 5-7 are stored to the stack using (STR.W), but argument 6 and argument 7 are stored to a known stack location [SP, #0x8] for argument 7, [SP, #x0x4] for argument 6. So, the compiler is always making enough space on the stack for passing the needed function arguments. Going up to 10 arguments, the compiler adds a SUB instruction to the stack counter, in order to reserve the larger amount needed.