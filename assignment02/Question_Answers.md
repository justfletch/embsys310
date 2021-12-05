# Assignment 02 Questions
Starting code used in main.c file:

```int main() {
int counter = 0;
counter ++;
counter ++;
counter ++;
counter ++;
counter ++;
counter ++;
counter ++;
return 0;
}
```

>### 1. Inject 0x7FFFFFFF for the “counter” value in the variable window, then step thru the program only once to increment “counter”.
> a) What is the value of the “counter” from the “Locals” window?

The value is 0x80000000, which is -2147483648 in decimal. It is now a negative.

> b) What is the value of the “counter” in the “Registers” window?

R1 in the Registers window is also 0x80000000.

> c) Please note down which flags are set in the APSR register. And explain why.

In the APSR register, the 'N' & 'V' flags are set. 'N' is the negative flag, showing that the result is negative. 'V' is the overflow flag, showing that the result has gone out of bounds of a signed int; a positive number rolled over to a negative. Counter is an 'int' type, which is 32-bit here. It's also in two's complement, which means that the most significant bit is the value's sign bit. 0x7FFFFFFF in binary is 0b01111111111111111111111111111111. This is the highest possible positive number that the counter int can hold. Adding 1 to it pushes a 1 into the sign bit, which turns it negative. 0x80000000 = 0b10000000000000000000000000000000

>### 2. If your write all Fs (0XFFFFFFFF) in the Register value for “counter” then step thru the program once to increment “counter”
> a) What happens to the value of “counter” in the “Locals” window?

The value is 0x00000000, which is just zero.

> b) Please note down which are set in the APSR register. And explain why.

In the APSR register, the 'Z' & 'V' flags are set. 'Z' is the zero flag, which is obviously the case. 'V' is the overflow flag, showing that the result has gone out of bounds. In this case a negative number rolled over to a positive (indicated by the sign bit, even though the value is zero).

>### 3. Change the “counter” variable type in your code to “unsigned int”. Inject the values “0x7FFFFFFF” then step thru the program to increment the “counter” once:
> a) What is the value of “counter” in the “Locals” window after incrementing for each value?

The value is 0x80000000, which is 2147483648 in decimal, as an unsigned int. It continues to increment each step: 0x80000001 [2147483649], 0x80000002 [2147483650], ... 0x80000006 [2147483654].

> b) Please note down which flags are set in the APSR register. And explain why.

For the first increment (0x7FFFFFFF to 0x80000000) the 'N' & 'V' flags are set. 'N' is the negative flag, showing that the result is negative. 'V' is the overflow flag, showing that the result has gone out of bounds; a positive number rolled over to a negative. This is because it is treated as if the number was a signed int). However, the result is not actually negative, nor did the value roll over, because it is an unsigned int. The APSR registers are acting as if the type is a signed int. Continuing to increment the counter variable, the 'N' flag is still set (negative), but the overflow flag is cleared, since the most significant bit is unchanged.


>### 4. Change the “counter” variable type in your code to “unsigned”. Inject the values “0xFFFFFFFF” then step thru the program to increment the “counter” once:
>a) What is the value of “counter” in the “Locals” window after incrementing for each value?

The value is 0x00000000 [0] after one increment. The value continues to increment by one each step: 0x00000001 [1], 0x00000002 [2], ... 0x00000006 [6].

>b) Please note down which are set in the APSR register. And explain why.

For the first increment (0xFFFFFFFF to 0x00000000) the 'C' & 'Z' flags are set. 'C' is the carry flag, showing that the result has a carry bit, which is past the 32-bit's MSB. 'Z' is the zero flag, showing that the result is zero. This is because the value has gone beyond what a 32-bit value can represent. If the result was more than zero, the carry flag would be the only one set. The remaining increments do not result in any of the APSR flags being set because they are all low value additions of positive numbers.


>### 5. Move the “counter” variable outside of main (at the top of the file):
>a) What is the scope of the variable “counter”?

The scope of counter is now global.

>b) Is it still visible in the “Locals” view?

"counter" is no longer visible in the locals view.

>c) In which window view can we track “counter” now?

The Watch window [Watch 1] gives visibility of "counter".

>d) What is the address of the “counter” variable in memory?

It is 0x20000000.

>### 6. Change the source code to the following, then run the program in the simulator:

```int counter = 0x0;
int main() {
int *p_int = (int *)0x20000000;
++(*p_int);
++(*p_int);
++(*p_int);
counter ++;
return 0;
}
```

>a) What is the value of “counter” at the end of the program (halting at the return 0 statement)

The value is 0x00000004 [4].

>b) Explain why the counter value has changed?

p_int is an integer pointer. It contains the address of an integer, which was set to the address that we saw "counter" get set to as a global variable. The "++(*p_int)" lines are saying to add one to the value at the integer point p_int, which is the address of counter, thus the value of counter increases.

>### 7. Change the setting of IAR to run the same program on the evaluation board:

>a) What is the address where “counter” is stored?

The address of counter is the same as it was in the simulator, 0x20000000

>b) Is the “counter” variable stored in RAM or ROM?

It is stored in RAM.

>c) What is the value of “counter” at the end of the program (halting at the return 0 statement).

The value of "counter" is the same as it was in the simulator, 0x00000004 [4].