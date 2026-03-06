malloc_free

This project is part of the Holberton School Low Level Programming curriculum.
The goal of this project is to learn how to work with dynamic memory allocation in C using malloc and free.

Dynamic memory allows programs to allocate memory during runtime instead of compile time.

Learning Objectives

At the end of this project, you should be able to explain:

What is dynamic memory allocation

What is the difference between automatic and dynamic allocation

How to use malloc

How to use free

When and why to use malloc

How to check if malloc fails

How memory works in C

Requirements

Allowed editors: vi, vim, emacs

All files compiled on Ubuntu 20.04

Compilation flags:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89

Code must follow Betty style

No global variables

Maximum 5 functions per file

Prototypes must be included in main.h

Files
File	Description
main.h	Header file containing function prototypes
0-create_array.c	Creates an array of chars and initializes it with a specific char
Function Prototype
char *create_array(unsigned int size, char c);
Description

This function:

Allocates memory for an array of characters

Initializes each element with the character c

Returns a pointer to the allocated memory

Returns NULL if size is 0

Returns NULL if memory allocation fails

Example
char *buffer;

buffer = create_array(98, 'H');

Output in hexadecimal:

0x48 0x48 0x48 0x48 ...

Because:

'H' = ASCII 72 = 0x48
Compilation
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 0-main.c 0-create_array.c -o a

Run:

./a
Concepts Used

Pointers

Arrays

Dynamic memory allocation

malloc

free

Memory management

Author

Jorge L. Burgos Cruz

Holberton School
Low Level Programming Project
