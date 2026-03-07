# Structures and Typedef in C

This project focuses on understanding and using **structures (`struct`)** in the C programming language. Structures allow grouping different data types into a single unit, making it easier to manage related information.

## Learning Objectives

At the end of this project, you should be able to explain:

- What structures are in C
- How to define and use a structure
- How to access members of a structure
- The difference between a structure and a pointer to a structure
- How to use `typedef` with structures

## Project Files

| File | Description |
|-----|-------------|
| `dog.h` | Header file containing the definition of `struct dog` |
| `0-main.c` | Example file used to test the `struct dog` structure |

## Structure Definition

The project defines a new type called `struct dog` with the following elements:

- `name` → pointer to a character string (`char *`)
- `age` → floating point number (`float`)
- `owner` → pointer to a character string (`char *`)

Example:

```c
struct dog
{
    char *name;
    float age;
    char *owner;
};
