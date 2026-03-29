# Doubly Linked Lists

This project is part of the Holberton School low level programming curriculum.

## Description

This project introduces doubly linked lists in C.

## Data structure

```c
typedef struct dlistint_s
{
	int n;
	struct dlistint_s *prev;
	struct dlistint_s *next;
} dlistint_t;
