/*******************************************************************************
File name       : swapCharsAsm.s
Description     : Assembly language function for swapping two chars
*******************************************************************************/   

    
    PUBLIC swapCharsAsm       // Exports symbols to other modules
    // Making swapCharsAsm available to other modules.
    
// Code is split into logical sections using the SECTION directive.
// Source: http://ftp.iar.se/WWWfiles/arm/webic/doc/EWARM_AssemblerReference.ENU.pdf
// SECTION  section  :type [:flag] [(align)]
//      The data section is used for declaring initialized data or constants. This data does not change at runtime
//      The bss section is used for declaring variables.
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
Function Name   : swapCharsAsm
Description     : Swaps two chars. Returns 0 if chars are identical. Else returns 1.
C Prototype     : int swapCharsAsm(*char1, *char2)
                : char1 and char2 will be swapped. *&char1 = char2, *&char2 = char1
Parameters      : R0: char1, R1: char2
Return value    : R0
*******************************************************************************/  
swapCharsAsm
    LDRB R2, [R0]       // Load value of char1 (byte), which is at address [R0], to scratch reg (R2)
    LDRB R3, [R1]       // Load value of char2 (byte), which is at address [R1], to scratch reg (R3)
    CMP R2, R3          // Compare R2 and R3 to see if the are equal
    BEQ CHARS_EQUAL     // Branch to "CHARS_EQUAL" if equal, else next operation
    STR R2, [R1]        // If char1 != char2, need to actually swap them. Store R2 (char1 value) back to address in R1 (char2's address)
    STR R3, [R0]        // 2nd half of swap. Store R3 (char2 value) back to address in R0 (char1's address)
    MOV R0, #1          // Since the characters were not equal, return 1
    BX LR               // Function complete. Result is in R0


CHARS_EQUAL             //chars are equal label
    MOV R0, #0          // Since the characters were equal, no need to swap. Return 0
    BX LR               // Function complete. Result is in R0

    END
    


