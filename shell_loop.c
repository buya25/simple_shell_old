#include "shell.h"

/**
 * hsh - main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	int n_ret = 0;
	ssize_t nt = 0;

	while (nt != -1 && n_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		nt = get_input(info);
		if (nt != -1)
		{
			set_info(info, av);
			n_ret = find_builtin(info);
			if (n_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (n_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (n_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int fd, n_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (fd = 0; builtintbl[fd].type; fd++)
		if (_strcmp(info->argv[0], builtintbl[fd].type) == 0)
		{
			info->line_count++;
			n_ret = builtintbl[fd].func(info);
			break;
		}
	return (n_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int jb, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (jb = 0, k = 0; info->arg[jb]; jb++)
		if (!is_delim(info->arg[jb], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread
 * @info: parameter and return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
