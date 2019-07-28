# Guide to using the mfi file interpreter.

To run a program on mat using mfi, use the command `mat filename.mat`. Please note that mfi can interpret only one program in one pass.
To make sure that you have done everything correctly, copy the text below into test.mat
```c
output
A new line
~ A single line ~
:8/2+90-6r

```

If you have done everything correctly you will see the following message:

```c

A new line
88

```

## mfi configuration options
As of version 0.3.1, the mfi added the ability configuration. For this are used .mic (mat interpreter configuration) files. In these files, the configuration is written in plain text. The configuration file is passed to the mfi as follows: 

```sh
mat <source> <config>
```

At the moment there are 2 options:

  + `silence` -- This option disables the display of errors.

**Example**

**source.mat**
```c
:qwerty

```

**config.mic**
```c
silence

```
In this case, the error message will not be displayed because the `silence` option is specified in the mic file.

  + `noStop` -- This option allows you to disable stop on error.

**Example**

source.mat
```c

:qwerty
output_Hi there!

```
config.mic
```c
silence noStop

```
This program is not strange will not display an error message, and will not stop. Therefore, the result will be a message on the screen: `Hi there!`.

# If you encounter problems, try the steps in [this](main.md) guide, if the problem persists, then write to the e-mail given [there](main.md).
