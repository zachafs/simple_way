#include "shell.h"

/**
 * clear_info - initializes struc_t struct
 * @strct: struct address
 */
void clear_info(struc_t *strct)
{
	strct->arg = NULL;
	strct->argv = NULL;
	strct->path = NULL;
	strct->argc = 0;
}

/**
 * set_info- initializes struc_t struct
 * @strct: struct address
 * @av: argument vector
 */
void set_info(struc_t *strct, char **av)
{
	int count = 0;
	char **temp = strct->argv;

	strct->fname = av[0];
	if (strct->arg)
	{
		strct->argv = splits_strtow(strct->arg, " \t");
		if (!strct->argv)
		{
			strct->argv = malloc(sizeof(char *) * 2);
			if (strct->argv)
			{
				strct->argv[0] = _strdup(strct->arg);
				strct->argv[1] = NULL;
			}
		}
		else
		{
		while (*temp)
		{
			count++;
			temp++;
		}
		strct->argc = count;
		}
		replace_alias(strct);
		replace_vars(strct);
	}
}

/**
 * free_info - frees struc_t struct fields
 * @strct: struct address
 * @all: true if freeing all fields
 */
void free_info(struc_t *strct, int all)
{
	ffree(strct->argv);
	strct->argv = NULL;
	strct->path = NULL;
	if (all)
	{
		if (!strct->cmd_buf)
			free(strct->arg);
		free_nodelist(&(strct->env));
		free_nodelist(&(strct->history));
		free_nodelist(&(strct->alias));
		ffree(strct->environ);
		strct->environ = NULL;
		freeptr((void **)strct->cmd_buf);

		if (strct->readfd > 2)
			close(strct->readfd);

		_putchar(BUF_FLUSH);
	}
}
