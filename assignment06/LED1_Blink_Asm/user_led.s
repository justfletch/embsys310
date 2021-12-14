/*******************************************************************************
File name       : user_led.s
Description     : Assembly language function for controlling the user LED
*******************************************************************************/   

    EXTERN delay                    // delay() is defined outside this file

    PUBLIC control_user_led1        // Exports symbols to other modules

// Code is split into logical sections using the SECTION directive.
// Source: http://ftp.iar.se/WWWfiles/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf
// SECTION  section  :type [:flag] [(align)]
//      The data section is used for declaring initialized data or constants. This data does not change at runtime
//      The bss section is used for declaring variables. The syntax for declaring bss section is -
//      The text section is used for keeping the actual code.

// CODE: Interprets subsequent instructions as Arm or Thumb instructions, 
// depending on the setting of related assembler options.

// NOREORDER (the default mode) starts a new fragment in the section
// with the given name, or a new section if no such section exists.
// REORDER starts a new section with the given name.

// NOROOT means that the section fragment is discarded by the linker if
// no symbols in this section fragment are referred to. Normally, all
// section fragments except startup code and interrupt vectors should
// set this flag.

// The (2) is for the (align)
// The power of two to which the address should be aligned.
// The permitted range is 0 to 8. 
// Code aligned at 4 Bytes.

    SECTION .text:CODE:REORDER:NOROOT(2)
    
    THUMB               // Indicates THUMB code is used
                        // Subsequent instructions are assembled as THUMB instructions
    
/*******************************************************************************
Function Name   : control_user_led1
Description     : - Uses Peripheral registers at base 0x4800.0000
                    to set GPIOA Output Data Register.
                  - Calls another assembly function delay to insert
                    delay loop

C Prototype     : void control_user_led(uint8_t state, uint32_t duration)
                : Where state indicates if LED should be on or off.
Parameters      : R0: uint8_t state
                : R1: uint32_t duration
Return value    : None
*******************************************************************************/  

GPIOA_BASE  EQU 0x48000000
GPIOA_ODR   EQU 0x14
GPIOA_BIT_5 EQU 0x20

control_user_led1
//Clock is already enabled. MODER is alraedy set. Just need to set ODR to given state
//R0 is state
//R1 is delay duration

    LDR R2, =GPIOA_BASE         //load the base address in R2
    LDR R3, [R2, #GPIOA_ODR]    //load the value at [R2 (GPIOA_BASE) + ODR offset]
    CMP R0, #1                  //compare with 1. LED gets turned on if 1
    BEQ LED1_ON                 //if equal, branch to LED1_ON
    CMP R0, #0                  //else compare with 0. LED gets turn off if 0
    BEQ LED1_OFF                //if equal, branch to LED1_OFF
    BX LR                       //else LED state was not given correctly, exit function
    
LED1_ON                         //Label for instructions to turn LED1 on
    ORR R0, R3, #GPIOA_BIT_5    //OR with GPIOA_BIT_5 to turn PA5 on (LED1)
    B SET_LED_AND_DELAY         //Branch down to set (store) the new value into the GPIO_ODR register & delay
    
LED1_OFF                        //Label for instructions to turn LED1 off
    BIC R0, R3, #GPIOA_BIT_5    //BIC (bit clear) with GPIOA_BIT_5 to turn PA5 off (LED1)
    B SET_LED_AND_DELAY         //Branch down to set (store) the new value into the GPIO_ODR register & delay
    
SET_LED_AND_DELAY               //Label for instruction to set (store) new GPIO_ODR value, then call delay function
    STR R0, [R2, #GPIOA_ODR]    //store the GPIO_ODR value to it's address (GPIOA_BASE + ODR offset)
    PUSH {LR}                   //save LR to stack since we are calling another function, and need to retain it
    MOV R0, R1                  //R1 is the given delay duration, move to R0 so delay can use it as the input argument
    B delay                     //Branch to delay
    POP {LR}                    //Returned from delay, pop LR off stack
    BX LR                       //Branch to LR
    
    END
