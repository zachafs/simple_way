#include "shell.h"

/**
 * my_exit - exits the shell
 * @strct: Structure containing potential arguments
 * Return: exits with a given exit status
 * (0) if strct.argv[0] != "exit"
 */
int my_exit(struc_t *strct)
{
	if (strct->argv[1])
	{
		int exitcheck = err_convert(strct->argv[1]);

		if (exitcheck == -1)
		{
			strct->status = 2;
			msg_error(strct, "Illegal number: ");
			_eputs(strct->argv[1]);
			_eputchar('\n');
			return (1);
		}
		strct->err_num = exitcheck;
		return (-2);
	}
	strct->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of shell
 * @strct: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int my_cd(struc_t *strct)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!strct->argv[1])
	{
		dir = get_env(strct, "HOME=");
		if (!dir)
		chdir_ret = chdir((dir = get_env(strct, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (compar_str(strct->argv[1], "-") == 0)
	{
		if (!get_env(strct, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(strct, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = get_env(strct, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(strct->argv[1]);
	if (chdir_ret == -1)
	{
		msg_error(strct, "can't cd to ");
		_eputs(strct->argv[1]);
		_eputchar('\n');
	}
	else
	{
		set_env(strct, "OLDPWD", get_env(strct, "PWD="));
		set_env(strct, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @strct: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_help(struc_t *strct)
{
	char **arg_array;

	arg_array = strct->argv;
	_puts("help call works. Function not yet implemented \n");
	while (0)
		_puts(*arg_array);
	return (0);
}

