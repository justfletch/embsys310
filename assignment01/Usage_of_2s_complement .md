# What is two's complement?

It is a way to express signed numbers using binary. To get the negative version of a "10" in two's complement (for an 8 bit type), for instance, requires these two steps: 

1. Invert each digit.
    Positive 10: 00001010
    Inverted 10: 11110101
    
2. Then, add 1
    Inverted 10: 11110101
    "Inverted 10"+1: 11110110

The "Inverted 10"+1 value is "-10" in two's complement.


# Two's complement is useful for a few reasons:

1. It works for existing mathematical functions. If you were to do a boolean addition operation for a positive and negative number, the result of that operation is correct. Using One's complement results in an answer that is off by 1, so would require a special addition operation. This reduces complexity for addition circuits. It can also be used 


2. It is more efficient than One's compliment, in that it does not waste multiple binary values as "0". For example, in a 4-bit table of One's complement compared to Two's complement:

## One's Complement
|     |     |     |     | Value |
| --- | --- | --- | --- | ----- |
| 1   | 0   | 0   | 0   | -7    |
| 1   | 0   | 0   | 1   | -6    |
| 1   | 0   | 1   | 0   | -5    |
| 1   | 0   | 1   | 1   | -4    |
| 1   | 1   | 0   | 0   | -3    |
| 1   | 1   | 0   | 1   | -2    |
| 1   | 1   | 1   | 0   | -1    |
| 1   | 1   | 1   | 1   | 0     |
| 0   | 0   | 0   | 0   | 0     |
| 0   | 0   | 0   | 1   | 1     |
| 0   | 0   | 1   | 0   | 2     |
| 0   | 0   | 1   | 1   | 3     |
| 0   | 1   | 0   | 0   | 4     |
| 0   | 1   | 0   | 1   | 5     |
| 0   | 1   | 1   | 0   | 6     |
| 0   | 1   | 1   | 1   | 7     |


## Two's Complement
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