# Assignment 07 Questions

>### Generate the map file for your program and provide details on:
>a. How much total ROM your program is occupying?

372 bytes (code) + 82 bytes (data) = 454 bytes total.

>b. How much total RAM your program is using?

8,268 bytes

>c. What part of your program is using the most ROM?

The code is using the most (372 bytes). The largest inside of that is main, which is 120 bytes.

>d. What part of your program is using the most RAM?

Reservation of the stack memory is the most, which is 8,264 bytes. The other 4 bytes are from the global variable "delayInterruptCounts" in main.