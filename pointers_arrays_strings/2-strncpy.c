#include "main.h"

/**
 * _strncpy - copies a string
 * @dest: destination buffer
 * @src: source string
 * @n: maximum number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	i = 0;

	/* copy characters from src */
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	/* fill remaining space with '\0' */
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}
