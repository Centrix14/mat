# Error list

This document provides a list of errors that you can get when working with mfi or mi2.

## Errors
   1. Type error. Type error. This is an error that occurs when the expected data and the actual data do not match. For example, you set the addition mode, which implies that the input data is numbers, but passed the word. Then the interpreter will give an error and stop working.
  **Example**
  As an example, the following failed program
  ```c
  :qwerty

  ```
  When the program starts, mfi (or mi2) will display the following message:
> [:]: Type error in line 1: expected number but passed 'qwerty'

  From this message we can conclude that the error occurred in the initialization state `:`, in 1 line. Also, it is further explained that the expected number, but the expression was passed in quotation marks.

## Warnings
  1. Operation with 0. This warning is given when a mathematical operation with 0 is performed.
  **Comment**. Since version 0.2.4, 2 zero operations are allowed: `&` -- logical And, `:` -- assigning a value to the battery. Therefore, when using constructs such as `:0` and `&0`, no warning will be issued.
  **Example**
  As an example, the following failed program
  ```c
  :0

  ```
  When the program starts, mfi will display the following message:
> Warning line 1: operation with 0.	

  From this message, you can conclude that a zero operation is performed on the line.
  **It is worth noting that despite the warning status, after issuing this message, mfi and mi2 will stop working!**

