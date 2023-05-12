#include "shell.h"

/**
 * _strcpy -the copies a string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *rtl;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	rtl = malloc(sizeof(char) * (length + 1));
	if (!rtl)
		return (NULL);
	for (length++; length--;)
		rtl[length] = *--str;
	return (rtl);
}

/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int ist = 0;

	if (!str)
		return;
	while (str[ist] != '\0')
	{
		_putchar(str[ist]);
		ist++;
	}
}

/**
 * _putchar - character c to stdout
 * @c: character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int nm;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || nm >= WRITE_BUF_SIZE)
	{
		write(1, buf, nm);
		nm = 0;
	}
	if (c != BUF_FLUSH)
		buf[nm++] = c;
	return (1);
}
