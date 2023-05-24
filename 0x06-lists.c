#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const lis_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(lis_t *head)
{
	if (!head)
		return (NULL);
	size_t len = list_len(head);

	if (len == 0)
		return (NULL);
	char **strs = malloc(sizeof(char *) * (len + 1));

	if (!strs)
		return (NULL);
	lis_t *node = head;
	size_t i = 0;

	for (; node; node = node->next, i++)
	{
		size_t str_len = lenGTH_str(node->str);

		char *str = malloc(str_len + 1);

		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		_strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a lis_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const lis_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nodestarts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
lis_t *nodestarts_with(lis_t *node, char *prefix, char c)
{
	while (node)
	{
		char *p = starts_with(node->str, prefix);

		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getnode_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getnode_index(lis_t *head, lis_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
