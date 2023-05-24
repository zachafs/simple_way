#include "shell.h"

/**
 * my_env - prints the current environment
 * @strct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int my_env(struc_t *strct)
{
	print_list_str(strct->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @strct: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(struc_t *strct, const char *name)
{
	lis_t *node = strct->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * let_setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @strct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int let_setenv(struc_t *strct)
{
	if (strct->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(strct, strct->argv[1], strct->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @strct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int my_unsetenv(struc_t *strct)
{
	if (strct->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (int i = 1; i <= strct->argc; i++)
		unset_env(strct, strct->argv[i]);

	return (0);
}

/**
 * env_linkedlist - populates env linked list
 * @strct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_linkedlist(struc_t *strct)
{
	lis_t *node = NULL;
	size_t i = 0;

	while (environ[i])
	{
		add_node_e(&node, environ[i], 0);
		i++;
	}

	strct->env = node;
	return (0);
}
