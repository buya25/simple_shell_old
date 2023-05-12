#include "shell.h"

/**
 * get_environ - returns string array copy
 * @info: Used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * _unsetenv - Remove an environment variable       
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *nd = info->env;
	size_t st = 0;
	char *p;

	if (!nd || !var)
		return (0);

	while (nd)
	{
		p = starts_with(nd->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), st);
			st = 0;
			nd = info->env;
			continue;
		}
		nd = nd->next;
		st++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize an environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * @value: the string env var value
 * @var: the string env var property
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *nd;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	nd = info->env;
	while (nd)
	{
		p = starts_with(nd->str, var);
		if (p && *p == '=')
		{
			free(nd->str);
			nd->str = buf;
			info->env_changed = 1;
			return (0);
		}
		nd = nd->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
