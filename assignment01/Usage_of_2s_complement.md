# What is two's complement?

It is a way to express signed numbers using binary. To get the negative version of a "10" in two's complement (in a signed 8-bit integer), for instance, requires these two steps: 

* Invert each digit.
    * Positive 10:          00001010
    * Inverted 10:          11110101
    
* Then, add 1.
    * Inverted 10:          11110101
    * "Inverted 10" + 1:    11110110

The "Inverted 10" + 1 value [0b11110110] is "-10" in two's complement.


# Two's complement is useful for a few reasons:

1. It works for existing mathematical functions. If you were to do a boolean addition operation for a positive and negative number, the result of that operation is correct. Using one's complement results in an answer that is off by 1, so would require a special addition operation. Two's complement can use existing addition circuits. It also makes it possible to use the addition operation as subtraction, where numbers to be subtracted are turned to their negative value by two's complement. The addition is then the first number plus the negative of the second number, which is accomplishing the same thing as subtracting the second number from the first number.

#### Addition (two's complement): 
2 [0b0010] + 3 [0b0011]= 5 [0b0101]

#### Subtraction (two's complement):
2 [0b0010] + (-3) [0b1101] = -1 [0b1111]


2. It is more efficient than one's compliment (where bits are inverted, without any more steps), in that it does not waste binary values as "-0". For example, in a 4-bit table of one's complement compared to two's complement, a "-0" exists in one's complement at 0b1111, but not two's complement:

### One's Complement
|     |     |     |     | Value |
| --- | --- | --- | --- | ----- |
| 1   | 0   | 0   | 0   | -7    |
| 1   | 0   | 0   | 1   | -6    |
| 1   | 0   | 1   | 0   | -5    |
| 1   | 0   | 1   | 1   | -4    |
| 1   | 1   | 0   | 0   | -3    |
| 1   | 1   | 0   | 1   | -2    |
| 1   | 1   | 1   | 0   | -1    |
| 1   | 1   | 1   | 1   | -0    |
| 0   | 0   | 0   | 0   | 0     |
| 0   | 0   | 0   | 1   | 1     |
| 0   | 0   | 1   | 0   | 2     |
| 0   | 0   | 1   | 1   | 3     |
| 0   | 1   | 0   | 0   | 4     |
| 0   | 1   | 0   | 1   | 5     |
| 0   | 1   | 1   | 0   | 6     |
| 0   | 1   | 1   | 1   | 7     |


### Two's Complement
|     |     |     |     | Value |
| --- | --- | --- | --- | ----- |
| 1   | 0   | 0   | 0   | -8    |
| 1   | 0   | 0   | 1   | -7    |
| 1   | 0   | 1   | 0   | -6    |
| 1   | 0   | 1   | 1   | -5    |
| 1   | 1   | 0   | 0   | -4    |
| 1   | 1   | 0   | 1   | -3    |
| 1   | 1   | 1   | 0   | -2    |
| 1   | 1   | 1   | 1   | -1    |
| 0   | 0   | 0   | 0   | 0     |
| 0   | 0   | 0   | 1   | 1     |
| 0   | 0   | 1   | 0   | 2     |
| 0   | 0   | 1   | 1   | 3     |
| 0   | 1   | 0   | 0   | 4     |
| 0   | 1   | 0   | 1   | 5     |
| 0   | 1   | 1   | 0   | 6     |
| 0   | 1   | 1   | 1   | 7     |


3. It's easy to detect an overflow. For addition, if the resulting value is greater than that which can be represented by the type, an overflow flag can be generated. This is done by noting the sign of each number before it is added. If they are both positive (sign bit is 0), then a negative number (sign bit is 1) should not be the result. Adding 7 [0b0111] + 7 [0b0111] would result in 14 [0b1110], which, if using 4-bit signed integers, is out of range because 0b1110 is actually -2. Knowing that both input numbers were positive, but the output was negative, it's obvious that the result has overflowed. Likewise, if adding two negative numbers (sign bit is 1) results in a positive value (sign bit is 0), then an overflow has occured: -6 [0b1010] + -6 [0b1010] = 4 [0b0100]. Adding a positive and negative number should only bring the result closer to zero, so there is no potential for overflow in the case of both input numbers having different sign bits.


4. One of the neat outcomes of two's complement is that the sign bit can be treated as a negative value of the place it would represent in an unsigned type. For example, with a 4-bit signed integer, the value can be calculated by assigning the value of -8 to the most significant bit:

* 0100 = (-8\*0) + (4\*1) + (2\*0) + (1\*0) = 0+4+0+0 = 4
* 1100 = (-8\*1) + (4\*1) + (2\*0) + (1\*0) = -8+4+0+0 = -4


Resources used:
* Thomas Finley, Cornell, Two's complement https://www.cs.cornell.edu/~tomf/notes/cps104/twoscomp.html
* MIT OpenCourseware, Worked Examples: Two's Complement Addition https://www.youtube.com/watch?v=ydboHy_yNts
* Computerphile, Binary: Plusses & Minuses https://www.youtube.com/watch?v=lKTsv6iVxV4
* Ben Eater, Twos complement: Negative numbers in binary https://www.youtube.com/watch?v=4qH4unVtJkE