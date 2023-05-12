#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * @name: env var name
 * _getenv - gets the value of an environ variable
 * @info: containing potential arguments. Used to maintain
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *nd = info->env;
	char *p;

	while (nd)
	{
		p = starts_with(nd->str, name);
		if (p && *p)
			return (p);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * @info: Structure containing potential arguments. Used to maintain
 * 		constant function prototype
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * @info: Structure containing potential arguments. Used to maintain
 * 		constant function prototype.
 * _myunsetenv - Remove an environment variable
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int c;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (c = 0; c <= info->argc; c++)
		_unsetenv(info, info->argv[c]);

	return (0);
}

/**
 * @info: Structure containing potential arguments.
 * 		constant function prototype.
 * populate_env_list - populates env linked list
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t v;

	for (v = 0; environ[v]; v++)
		add_node_end(&node, environ[v], 0);
	info->env = node;
	return (0);
}
