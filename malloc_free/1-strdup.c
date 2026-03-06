#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a duplicated string
 * @str: string to duplicate
 *
 * Return: pointer to the new string, or NULL if it fails
 */
char *_strdup(char *str)
{
	char *copy;
	int i, len;

	if (str == NULL)
		return (NULL);

	len = 0;

	while (str[len] != '\0')
		len++;

	copy = malloc(sizeof(char) * (len + 1));

	if (copy == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		copy[i] = str[i];

	return (copy);
}
