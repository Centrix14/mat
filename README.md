# mat - Minimalistic AutomaTon language
## Purpose of creating language
Undoubtedly, there are already a lot of programming languages in our world, but mat is not intended for developing programs, it is a research language that i created it for the purpose of research of automaton programming.

## Definition
mat -- is a research (experimental) automaton programming language. The main tool of this language is the switching modes (states) of the machine.

## Syntax
The only syntactic rule of the language is the separation of characters of the same type, others, if they are not one character. For example: '53' if it is assumed that '53' are separate numbers 5 and 3, then separate them, for example, with a space!

## States
In mat terminology, the term 'state' denotes a way to process input data, for example, if you switch to the 'add' state, then all input data (numbers) will add up, but if you switch to the 'output to screen' state, the input data will be output to screen.

## Features
An important feature of the mat language is the absence of variables, almost all data is stored on the stack.

## Simple programm
Hello world:
```
output 
Hello world!
```
Here, in the first line, we put the automaton in the "output state", and after that we transmit the data, that is, the phrase "Hello World!"

> An important reminder: after setting the state, everything that is not a command for changing the state is considered data.

# That's all for now, because the language is still in development. I admit, this language is very ugly, but it is research, and will not be used in real programs, it can be said that it is a toy.
