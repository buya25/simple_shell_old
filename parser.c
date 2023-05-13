#include "shell.h"

/**
 * is_cmd - determines file is an executable command
 * @path: path to the file
 * @info: info struct
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat s;

	(void)info;
	if (!path || stat(path, &s))
		return (0);

	if (s.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @start: starting index
 * @stop: stopping index
 * @pathstr: PATH string
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	int j = 0, t = 0;
	static char buf[1024];

	for (t = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buf[t++] = pathstr[j];
	buf[t] = 0;
	return (buf);
}

/**
 * find_path - finds cmd in the PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, crps = 0;
	char *ph;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			ph = dup_chars(pathstr, crps, i);
			if (!*ph)
				_strcat(ph, cmd);
			else
			{
				_strcat(ph, "/");
				_strcat(ph, cmd);
			}
			if (is_cmd(info, ph))
				return (ph);
			if (!pathstr[i])
				break;
			crps = i;
		}
		i++;
	}
	return (NULL);
}
