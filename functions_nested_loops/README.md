functions_nested_loops

Description

This project introduces the concept of functions and nested loops in C programming. It builds on the fundamentals of variables and control flow and focuses on understanding how functions are declared, defined, and organized using header files.

The main goal is to learn how to structure programs properly using multiple files, function prototypes, and modular programming practices.

Learning Objectives

By the end of this project, I understand:

What nested loops are and how to use them

What a function is and how to use functions

The difference between a function declaration and a function definition

What a function prototype is and why it is necessary

The scope of variables

The purpose of header files and how to use #include

The meaning of gcc flags:
-Wall
-Werror
-Wextra
-pedantic
-std=gnu89

Project Requirements

Compiled on Ubuntu 20.04 LTS

Compiler: gcc

Compilation flags:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89

All files end with a new line

Code follows Betty style

No global variables allowed

Maximum of 5 functions per file

No use of the standard library (printf, puts, etc.)

Only _putchar is allowed

All function prototypes must be declared in main.h

Project Structure

functions_nested_loops/
│
├── main.h
├── _putchar.c (provided by checker)
├── 0-putchar.c
├── other task files...

Key Concepts Practiced

Function Declaration vs Definition

Declaration (prototype):
Tells the compiler that a function exists.

Example:
int my_function(int x);

Definition:
The actual implementation of the function.

Example:
int my_function(int x)
{
return (x + 1);
}

Function Prototype

A function prototype allows the compiler to check that the function is being used correctly before it is defined.

Header Files

Header files (.h) contain function prototypes and are included using:

#include "main.h"

This allows multiple files to share function declarations.

Nested Loops

Nested loops are loops inside other loops.

Example:

for (i = 0; i < 5; i++)
{
for (j = 0; j < 5; j++)
{
_putchar('*');
}
}

Scope of Variables

Variables declared inside a function are local to that function.
They cannot be accessed outside of it.

Compilation Example

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 _putchar.c 0-putchar.c -o 0-putchar

Author

Jorge L. Burgos Cruz
Holberton School – Low Level Programming
