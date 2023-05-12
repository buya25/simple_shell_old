#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *fname = get_history_file(info);
	list_t *nd = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (nd = info->history; nd; nd = nd->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * @info: parameter struct
 * read_history - reads history from file
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int nt, las = 0, lnct = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (nt = 0; nt < fsize; nt++)
		if (buf[nt] == '\n')
		{
			buf[nt] = 0;
			build_history_list(info, buf + las, lnct++);
			las = nt + 1;
		}
	if (las != nt)
		build_history_list(info, buf + las, lnct++);
	free(buf);
	info->histcount = lnct;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a linked list
 * @info: containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *nd = NULL;

	if (info->history)
		nd = info->history;
	add_node_end(&nd, buf, linecount);

	if (!info->history)
		info->history = nd;
	return (0);
}

/**
 * renumber_history - linked list after changes
 * @info: Structure Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *nd = info->history;
	int ls = 0;

	while (nd)
	{
		nd->num = ls++;
		nd = nd->next;
	}
	return (info->histcount = ls);
}
