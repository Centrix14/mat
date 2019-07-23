# Guidelines for using the embedded EMI interpreter.

## What is emi?
emi -- is a special implementation of the mat interpreter designed for embedding in C programs.

## How to compile emi?
To compile the library, use the make utility as mentioned [here](main.md).

## Functions available in emi.
  + matrun()  
    Prototype: `void matrun(char *prog);`  
	Appointment -- Interprets a program written in the zero format of a terminated string. The program is passed through the prog argument.

**Example**
As an example, consider the following C program:

```c
#include <stdio.h>
#include "emi.h" /* This header is required for emi to work. */

int main(void) {
	/* Call the matrun function, with an argument in the form of a C-string with a program on mat. */
	matrun("output_Hi from mat!\n");
	printf("Hi from C!");
	return 0;
}
```

Now compile our program using gcc (This is just an example in your case flags can be cast):

```sh
gcc -L. -I. -o testemi testemi.c libemi.a
```

  + matfrun()  
    Prototype: `void matfrun(char *fname);`  
	Appointment -- Interpretation of the program file with the name fname.

**Example**
As an example, consider the following C program:

```c
// testemi.c
#include <stdio.h>
#include "emi.h"

int main(void) {
	matfrun("test.mat");
	printf("Hi from C!\n");
	return 0;
}
```

And the program on the mat:

```c
output
A new line
:8/2+90-6r

```

After compile testemi.c:

```sh
gcc -L. -I. -o testemi testemi.c libemi.a
```

The result of the program will be the following output:

```c

A new line
88
Hi from C!

```

  + getCommandOn, setCommandOn  
    Prototypes: `int getCommandOn();` `void setCommandOn(int newState);`  
	Appointment -- Changing / read the `commandOn` parameter, which in the ON state indicates that the word being read is a reserved mat keyword.

# If you have any problems then repeat the procedures you have done again. If you have another problem, you can contact me by e-mail from [here](main.md).
