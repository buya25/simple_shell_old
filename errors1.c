#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int l = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (l = 0;  s[l] != '\0'; l++)
	{
		if (s[l] >= '0' && s[l] <= '9')
		{
			result *= 10;
			result += (s[l] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int p, cnt = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (p = 1000000000; p > 1; p /= 10)
	{
		if (_abs_ / p)
		{
			__putchar('0' + current / p);
			cnt++;
		}
		current %= p;
	}
	__putchar('0' + current);
	cnt++;

	return (cnt);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *ar;
	static char buffer[50];
	char gn = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		gn = '-';

	}
	ar = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = ar[n % base];
		n /= base;
	} while (n != 0);

	if (gn)
		*--ptr = gn;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int v;

	for (v = 0; buf[v] != '\0'; v++)
		if (buf[v] == '#' && (!v || buf[v - 1] == ' '))
		{
			buf[v] = '\0';
			break;
		}
}
