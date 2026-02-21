#include "main.h"

/**
 * _strncat - concatenates two strings using at most n bytes of src
 * @dest: destination buffer
 * @src: source string
 * @n: maximum number of bytes to use from src
 *
 * Return: pointer to dest
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0;
	int j = 0;

	/* move to end of dest */
	while (dest[i] != '\0')
	{
		i++;
	}

	/* append up to n chars from src */
	while (j < n && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}
