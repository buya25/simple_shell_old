#include "shell.h"

/**
 * **strtow - Repeat delimiters are ignored
 * @str: input string
 * @d: delimeter string
 * Return: array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int n, zj, k, m, nmw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], d) && (is_delim(str[n + 1], d) || !str[n + 1]))
			nmw++;

	if (nmw == 0)
		return (NULL);
	s = malloc((1 + nmw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (n = 0, zj = 0; zj < nmw; zj++)
	{
		while (is_delim(str[n], d))
			n++;
		k = 0;
		while (!is_delim(str[n + k], d) && str[n + k])
			k++;
		s[zj] = malloc((k + 1) * sizeof(char));
		if (!s[zj])
		{
			for (k = 0; k < zj; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[zj][m] = str[n++];
		s[zj][m] = 0;
	}
	s[zj] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer, or NULL on failure
 */
char **strtow2(char d, char *str)
{
	int p, j, y, m, nmw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (p = 0; str[p] != '\0'; p++)
		if ((str[p] != d && str[p + 1] == d) ||
				    (str[p] != d && !str[p + 1]) || str[p + 1] == d)
			nmw++;
	if (nmw == 0)
		return (NULL);
	s = malloc((1 + nmw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (p = 0, j = 0; j < nmw; j++)
	{
		while (str[p] == d && str[p] != d)
			p++;
		y = 0;
		while (str[p + y] != d && str[p + y] && str[p + y] != d)
			y++;
		s[j] = malloc((y + 1) * sizeof(char));
		if (!s[j])
		{
			for (y = 0; y < j; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < y; m++)
			s[j][m] = str[p++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
