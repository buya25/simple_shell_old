#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t g = 0;

	while (h)
	{
		h = h->next;
		g++;
	}
	return (g);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	char **sts;
        char *str;
	size_t f = list_len(head), j;

	if (!head || !f)
		return (NULL);
	str = malloc(sizeof(char *) * (f + 1));
	if (!sts)
		return (NULL);
	for (f = 0; node; node = node->next, f++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < f; j++)
				free(sts[j]);
			free(sts);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		sts[f] = str;
	}
	sts[f] = NULL;
	return (sts);
}


/**
 * print_list - prints elements of list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @prefix: string to match
 * @c: the next character after prefix to match
 * @node: pointer to list head
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @node: pointer to the node
 * @head: pointer to list head
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t p = 0;

	while (head)
	{
		if (head == node)
			return (p);
		head = head->next;
		p++;
	}
	return (-1);
}
