# Assignment 05 Questions
   

>### 1. Create a function in “C” that allows swapping of two pointers.
>a. Explain what the “main” function does in order to setup the input arguments prior to calling the swap_pointer() function?

The pointers themselves are not used as the input arguments. Just like a swap value function, which would use the pointers of the values as input arguments, this swap pointer function uses the pointers of the pointers as input arguments: &aPtr, &bPtr. Both are **int types.

>b. What are the values in R0 & R1 when swap_pointer() is called?

R0 and R1 are the addresses of aPtr and bPtr, respectively, which are the inputs for swap_pointer().

>c. Share a screen shot of the local variables inside of “main” after the function swap_pointer() returns showing the values of the pointers and what they are pointing to (similar to the picture below).

![Swap_Pointers_Locals_Results](https://user-images.githubusercontent.com/36116408/145793671-8c11ee94-9dfb-445d-94c5-aec0f70d8bd6.png)


>### 2. Create a new file divAsm.s and add the file to the same HelloWorld project above.
>f. Run your program on the board and capture a snapshot image of the output from TeraTerm showing the result of the divAsm.

![Asm_Division_Serial_Output](https://user-images.githubusercontent.com/36116408/145793700-40c872a0-28c2-47de-bc15-fa29f982e5ec.png)
