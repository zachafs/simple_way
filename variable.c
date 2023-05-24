#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @strct: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(struc_t *strct, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		strct->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		strct->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		strct->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @strct: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(struc_t *strct, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (strct->cmd_buf_type == CMD_AND)
	{
		if (strct->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (strct->cmd_buf_type == CMD_OR)
	{
		if (!strct->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @strct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(struc_t *strct)
{
	int i;
	lis_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodestarts_with(strct->alias, strct->argv[0], '=');
		if (!node)
			return (0);
		free(strct->argv[0]);
		p = chr_str(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		strct->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @strct: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(struc_t *strct)
{
	int i = 0;
	lis_t *node;

	for (i = 0; strct->argv[i]; i++)
	{
		if (strct->argv[i][0] != '$' || !strct->argv[i][1])
			continue;

		if (!compar_str(strct->argv[i], "$?"))
		{
			replace_string(&(strct->argv[i]),
					_strdup(convert_num(strct->status, 10, 0)));
			continue;
		}
		if (!compar_str(strct->argv[i], "$$"))
		{
			replace_string(&(strct->argv[i]),
					_strdup(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = nodestarts_with(strct->env, &strct->argv[i][1], '=');
		if (node)
		{
			replace_string(&(strct->argv[i]),
					_strdup(chr_str(node->str, '=') + 1));
			continue;
		}
		replace_string(&strct->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
