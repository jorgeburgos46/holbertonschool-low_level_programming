#include "main.h"
#include <limits.h>

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

	/* Find sign(s) before the number */
	while (s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
			break;
		i++;
	}

	/* Convert digits */
	while (s[i] != '\0' && (s[i] >= '0' && s[i] <= '9'))
	{
		int digit = s[i] - '0';

		started = 1;

		if (sign == 1)
		{
			/* Check overflow before: num = num * 10 + digit */
			if (num > (INT_MAX - digit) / 10)
				return (INT_MAX);
			num = num * 10 + digit;
		}
		else
		{
			/* Build as negative to safely support INT_MIN */
			/* Check underflow before: num = num * 10 - digit */
			if (num < (INT_MIN + digit) / 10)
				return (INT_MIN);
			num = num * 10 - digit;
		}

		i++;
	}

	if (!started)
		return (0);

	return (num);
}
