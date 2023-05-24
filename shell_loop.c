
#include "shell.h"

/**
 * mainshell_loop - main shell loop
 * @strct: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int mainshell_loop(struc_t *strct, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(strct);
		if (is_active(strct))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(strct);
		if (r != -1)
		{
			set_info(strct, av);
			builtin_ret = find_builtin(strct);
			if (builtin_ret == -1)
				find_cmdPath(strct);
		}
		else if (is_active(strct))
			_putchar('\n');
		free_info(strct, 0);
	}
	wr_story(strct);
	free_info(strct, 1);
	if (!is_active(strct) && strct->status)
		exit(strct->status);
	if (builtin_ret == -2)
	{
		if (strct->err_num == -1)
			exit(strct->status);
		exit(strct->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @strct: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int find_builtin(struc_t *strct)
{
	int i = 0;
	int built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_story},
		{"setenv", let_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	while (builtintbl[i].type)
	{

		if (compar_str(strct->argv[0], builtintbl[i].type) == 0)
		{
			strct->line_count++;
			built_in_ret = builtintbl[i].func(strct);
			break;
		}
		i++;
	}
	return (built_in_ret);
}

/**
 * find_cmdPath - finds a command in PATH
 * @strct: the parameter & return info struct
 *
 * Return: void
 */
void find_cmdPath(struc_t *strct)
{
	char *path = NULL;
	int i;
	int num_args = 0;

	strct->path = strct->argv[0];

	if (strct->linecount_flag == 1)
	{
		strct->line_count++;
		strct->linecount_flag = 0;
	}

	while (strct->arg[i])
	{
	if (!is_delim(strct->arg[i], " \t\n"))
	{
	num_args++;
	}
	i++;
	}
	if (!num_args)
		return;

	path = search_path(strct, get_env(strct, "PATH="), strct->argv[0]);
	if (path)
	{
		strct->path = path;
		fork_cmd(strct);
	}
	else
	{
		if ((is_active(strct) || get_env(strct, "PATH=")
					|| strct->argv[0][0] == '/') && exec_cmd(strct, strct->argv[0]))
			fork_cmd(strct);
		else if (*(strct->arg) != '\n')
		{
			strct->status = 127;
			msg_error(strct, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @strct: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(struc_t *strct)
{
	pid_t child_pid	= fork();

	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(strct->path, strct->argv, get_environ(strct)) == -1)
		{
			free_info(strct, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(strct->status));
		if (WIFEXITED(strct->status))
		{
			strct->status = WEXITSTATUS(strct->status);
			if (strct->status == 126)
				msg_error(strct, "Permission denied\n");
		}
	}
}
