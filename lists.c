#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @num: node index used by history
 * @head: address of pointer to head node
 * @str: str field of node
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *nh;

	if (!head)
		return (NULL);
	nh = malloc(sizeof(list_t));
	if (!nh)
		return (NULL);
	_memset((void *)nh, 0, sizeof(list_t));
	nh->num = num;
	if (str)
	{
		nh->str = _strdup(str);
		if (!nh->str)
		{
			free(nh);
			return (NULL);
		}
	}
	nh->next = *head;
	*head = nh;
	return (nh);
}

/**
 * add_node_end - adds a node to the end of the list
 * @str: str field of node
 * @num: node index used by history
 * @head: address of pointer to head node
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_d, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_d = malloc(sizeof(list_t));
	if (!new_d)
		return (NULL);
	_memset((void *)new_d, 0, sizeof(list_t));
	new_d->num = num;
	if (str)
	{
		new_d->str = _strdup(str);
		if (!new_d->str)
		{
			free(new_d);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_d;
	}
	else
		*head = new_d;
	return (new_d);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t d = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		d++;
	}
	return (d);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
