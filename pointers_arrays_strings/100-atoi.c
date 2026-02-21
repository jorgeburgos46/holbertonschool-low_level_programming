#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 *
 * Return: integer value found in the string, or 0 if none
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int num = 0;
	int started = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
		{
			started = 1;
			num = num * 10 + (s[i] - '0');
		}
		else if (started)
			break;
		i++;
	}

	return (num * sign);
}
