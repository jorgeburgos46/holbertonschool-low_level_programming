0x0B. C - More malloc, free

This project is part of the Holberton School Low Level Programming curriculum.
The purpose of this project is to deepen the understanding of dynamic memory allocation in C using functions like malloc, free, and exit.

In this project we implement functions that allocate memory dynamically and safely handle allocation failures.

Learning Objectives

At the end of this project, you should be able to explain:

How to use malloc and free

What exit is and how to use it

How to check if malloc fails

How to dynamically allocate memory

How to work with memory safely

How to use pointers with dynamically allocated memory

Requirements

Allowed editors: vi, vim, emacs

All files compiled on Ubuntu 20.04

Compilation flags:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89

Code must follow Betty style

No global variables allowed

Maximum 5 functions per file

Prototypes must be included in main.h

Files
File	Description
main.h	Header file containing function prototypes
0-malloc_checked.c	Allocates memory using malloc and exits with status 98 if allocation fails
Function Prototype
void *malloc_checked(unsigned int b);
Description

This function:

Allocates b bytes of memory using malloc

Returns a pointer to the allocated memory

If malloc fails, the function terminates the program with exit(98)

Example
char *buffer;

buffer = malloc_checked(1024);

This allocates 1024 bytes in memory.

Compilation
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
0-main.c 0-malloc_checked.c -o a
Run
./a
Concepts Used

Pointers

Dynamic memory allocation

malloc

free

exit

Memory management

Author

Jorge L. Burgos Cruz
Holberton School – Low Level Programming
