#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @strct: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ(struc_t *strct)
{
	if (!strct->environ || strct->env_changed)
	{
		strct->environ = list_to_strings(strct->env);
		strct->env_changed = 0;
	}

	return (strct->environ);
}

/**
 * unset_env - Remove an environment variable
 * @strct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int unset_env(struc_t *strct, char *var)
{
	lis_t *node = strct->env;
	size_t i = 0;

	if (!strct->env || !var)
		return (0);

	while (node)
	{
		char *p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			strct->env_changed = deletenode_index(&(strct->env), i);
			i = 0;
			node = strct->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (strct->env_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *             or modify an existing one
 * @strct: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int set_env(struc_t *strct, char *var, char *value)
{
	if (!var || !value)
		return (0);

	char *buf = malloc(lenGTH_str(var) + lenGTH_str(value) + 2);

	if (!buf)
	{
		return (1);
	}
	_strcpy(buf, var);
	concat_2str(buf, "=");
	concat_2str(buf, value);

	lis_t *node = strct->env;

	while (node)
	{
		char *p = starts_with(node->str, var);

		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			strct->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_e(&(strct->env), buf, 0);
	free(buf);
	strct->env_changed = 1;
	return (0);
}
