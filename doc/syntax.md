# mat syntax documentation
## Fundamentals
**There is 1 syntax rule in mat**
  1. If consecutive characters are of the same type (numbers, letters, signs), they are all perceived as one word explanation: '53' will be perceived as one number, but if you want to 5 and 3 were considered separate , then divide them, such as a letter or a sign or something else.
  
**States**  

The mat language has the concept of 'state' - this is the way of processing the input data. Once a state is set, anything that is not a command to move to another state is considered data. To change the state, you must use the switch to the desired state command.    

**Example**. When you enter the output state, anything that is not a state change command will be displayed. If we then write the addition command, now all input data will be added, but will not be displayed. If we assume that the command to go to the output state is `output`, and the command to go to the addition state is `+`, then the description above can be composed of the following program:
```c
output
Some text
+
5 6 7 8 9

```
The result of this program will be output to the console:
```sh
Some text

```

And also change the number stored in the accumulator (the accumulator stores the results of all mathematical operations). Initially there was 0, but now the accumulator stores the sum of the numbers 5, 6, 7, 8 and 9, that is 35. You can use the `r` state to verify this.   
To execute programs on a mat whose code is in the some.mat file, you can use mfi (mat file interpreter), which is called with the `mat` command. Then it turns out the command `mat some.mat`

## States supported mfi interpreter v0.3.x 
### Mathematical States
  + `+`, `-`, `*`, `/` `^`, `abs`, `neg`, `sqrt` -- These States correspond to their mathematical analog, with one difference, all operations are performed on the integer from the accumulator and the transmitted number. This means that the record +2 is the same as acc = acc + 2, where acc is the number stored in the accumulator.
  + `:` -- This state is used to initialize the accumulator, initially there is 0, but using this state you can change 0 to another number. In general, if you want to change the value to, say, 5, you can simply use the `+5` or `:5` construct. However, i recommend that the second option be used for such purposes.
  + `r` -- This state is used to display the battery value on the screen.

  **Important note. Commands are executed in the order in which they are written**

  For this reason, the construction `:2+2*2r` will display the value 8, because the commands will be executed in the sequence in which they are written.

**Example** 
```c
:100/2*50+5-2r

```
Explanations. First, we initialize the value of the accumulator, then divide this value by 2 and store it in the accumulator, then multiply it by 50, add 5, subtract 2, (of course, each time we store the value in the accumulator). And then with the help of `r`, we derive the value of the accumulator to the screen.
  + `>`, `<`, `>=`, `<=`, `=`, `!=` -- These States are used to compare numbers with the value in the battery. After comparison, the logical result (1 - true, 0 - false) of the operation is stored in a special variable cmpResult.
  **Example**
```c
:5>0

```
Explanations. In this mini program, the battery value (5) is compared with the transmitted number (0). A logical result of the operation is stored in cmpResult.

  + `cmpr` -- This state allows you to display the cmpResult value.
  **Example**
```
:5>0 cmpr

```
  Explanations. In this mini-program the result of comparison 5 and 0 (1) is displayed.
### The rest of the state.
  + `output` -- This state is used to display values on the screen. Note: to move to a new line, just use enter, and to tab, use the corresponding key on the keyboard.

**Example**
```c
output
Hi! I'm a useless text being printed by another useless programming language!

```
The result of the program.
```c

Hi! I'm a useless text being printed by another useless programming language!

```
Explanations. In this example, we first translate the machine into the state of data output to the screen, and then give the data that will be displayed on the screen.

Note. As you may have noticed, the phrase was printed on a new line. This is because after switching to print mode on the screen, we moved to a new line, and it was also printed. If you want to avoid this, you can use the following construct: `output_some text`, where `_` is a null character. Also notice that the `output` and `some` in the given example these are two different lexemes.

  + `term` -- This state can be used to access an external terminal. In the term state, the following syntax is used to enter commands into the terminal:

```c
term
<command>$

```
  Note. The `$` symbol indicates that the command is over and can be executed.

  **Example**
```c
term echo Hi from terminal! $

```
Explanation. In this example, first the transition to the term state is made, then the command that will be passed to the terminal is written, and when the command is over, we put the symbol `$`, thus indicating that the room is over and can be transferred to the terminal.

The result of the program:

```sh
Hi from terminal!

```

Note. In the situation when it is impossible to access the terminal, the machine generates an error (see details [here](errorlist.md)).

  + Control structures. In mat, control constructs differ from those in other languages. In General, the if-else expression is organized as follows:
```c
Expression (1)
TRUE (2)
    ~ some code ~
FALSE (3)
    ~ some code ~
END (4)
```
  Explanations. The expression (1) must change the cmpResult value, for example, the expression can be used `>`, `<`, `>=`, `<=`, `!=` `=`. All code after `TRUE` (2) will be executed only if the expression (1) is true. If the expression (1) is false, all code after `FALSE` (3) will be executed. When the if-else block is over, you need to write the `END`command.

  However, need not block `FALSE`, so it can not write, also if not block `FALSE`, then you should not write the command `END`. Thus, the incomplete form of branching looks like this:
```c
Expression (1)
TRUE (2)
    ~ some code ~
	
```
  Here everything is the same as in full form. Just removed unnecessary items.

**Example**
```c
:5>0
TRUE output_5 bigger than 0
FALSE output_5 smaller than 0
END
```
  This program will naturally output `5 bigger than 0`. However, it can be optimized in this way:
```c
:5>0
TRUE output_5 bigger than 0
```

## Other means
  + Comments. As in normal programming languages, comments in mat do not affect the result and execution of the program. There is only one type of comment in mat -- multiline. The text of the comment is framed by `~` (tilde) on both sides. For example. 

  ```c
  output_A first line
  ~ A second line ~

  ```
  The message `A second line` will not be displayed, as it is the text of the comment.

  **But we draw your attention to the first syntax rule mat:** ***Characters of the same type are not a single token, must be separated***. **Therefore, the expression `~:90~` is not a comment, since `~` and`:` are characters and will be read as one token `~:`.**

# At the moment this is all for now, do not forget that this programming language is still in development!
