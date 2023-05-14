#include "shell.h"

/**
 * is_chain - char in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t m = *p;

	if (buf[m] == '|' && buf[m + 1] == '|')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[m] == '&' && buf[m + 1] == '&')
	{
		buf[m] = 0;
		m++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[m] == ';') /* found end of this command */
	{
		buf[m] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}

/**
 * check_chain - chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 * @i: position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jg = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			jg = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			jg = len;
		}
	}

	*p = jg;
}

/**
 * replace_alias - replaces an alias in the token string
 * @info: parameter struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int k;
	list_t *nd;
	char *pt;

	for (k = 0; k < 10; k++)
	{
		nd = node_starts_with(info->alias, info->argv[0], '=');
		if (!nd)
			return (0);
		free(info->argv[0]);
		pt = _strchr(nd->str, '=');
		if (!pt)
			return (0);
		pt = _strdup(pt + 1);
		if (!pt)
			return (0);
		info->argv[0] = pt;
	}
	return (1);
}

/**
 * replace_vars - replaces the token string
 * @info: parameter struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *nd;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_starts_with(info->env, &info->argv[j][1], '=');
		if (nd)
		{
			replace_string(&(info->argv[j]),
					_strdup(_strchr(nd->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string for
 * @old: address old string
 * @new: new string
 *
 * Return: 1 if replaced or 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
