#include "shell.h"

/**
 * my_story - displays the history list, one command by line,
 * starting at 0.
 * @strct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_story(struc_t *strct)
{
	print_list(strct->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @strct: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(struc_t *strct, char *str)
{
	char *p = chr_str(str, '=');

	if (!p)
		return (1);
	char saved_char = *p;

	*p = 0;
	int ret = deletenode_index(&(strct->alias),
	getnode_index(strct->alias, nodestarts_with(strct->alias, str, -1)));
	*p = saved_char;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @strct: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(struc_t *strct, char *str)
{
	char *p;

	p = chr_str(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(strct, str));

	unset_alias(strct, str);
	return (add_node_e(&(strct->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(lis_t *node)
{
	if (node)
	{
		char *p = chr_str(node->str, '=');
		char *a = node->str;

		while (a <= p)
		{
			_putchar(*a);
			a++;
		}
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - mimics the alias builtin (man alias)
 * @strct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_alias(struc_t *strct)
{
	if (strct->argc == 1)
	{
	lis_t *node = strct->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	int i = 0;
	char *p = NULL;

	for (i = 1; strct->argv[i]; i++)
	{
		p = chr_str(strct->argv[i], '=');
		if (p)
			set_alias(strct, strct->argv[i]);
		else
			print_alias(nodestarts_with(strct->alias, strct->argv[i], '='));
	}

	return (0);
}
