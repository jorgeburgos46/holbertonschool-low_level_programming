#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_char - prints a char
 * @args: list of arguments
 * @separator: separator to print before the value
 */
void print_char(va_list *args, char *separator)
{
	printf("%s%c", separator, va_arg(*args, int));
}

/**
 * print_int - prints an integer
 * @args: list of arguments
 * @separator: separator to print before the value
 */
void print_int(va_list *args, char *separator)
{
	printf("%s%d", separator, va_arg(*args, int));
}

/**
 * print_float - prints a float
 * @args: list of arguments
 * @separator: separator to print before the value
 */
void print_float(va_list *args, char *separator)
{
	printf("%s%f", separator, va_arg(*args, double));
}

/**
 * print_string - prints a string
 * @args: list of arguments
 * @separator: separator to print before the value
 */
void print_string(va_list *args, char *separator)
{
	char *str;

	str = va_arg(*args, char *);

	if (str == NULL)
		str = "(nil)";

	printf("%s%s", separator, str);
}

/**
 * print_all - prints anything
 * @format: list of types of arguments passed to the function
 */
void print_all(const char * const format, ...)
{
	unsigned int i, j;
	char *separator;
	va_list args;
	print_t types[] = {
		{"c", print_char},
		{"i", print_int},
		{"f", print_float},
		{"s", print_string},
		{NULL, NULL}
	};

	va_start(args, format);

	i = 0;
	separator = "";
	while (format != NULL && format[i] != '\0')
	{
		j = 0;
		while (types[j].type != NULL)
		{
			if (format[i] == types[j].type[0])
			{
				types[j].f(&args, separator);
				separator = ", ";
				break;
			}
			j++;
		}
		i++;
	}

	va_end(args);

	printf("\n");
}
