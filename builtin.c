#include "shell.h"

/**
 * _myexit - Ext shell
 * @info: Struct cont the potential args. it is Used to be maintain
 * const fct prttype.
 * Return: the exits with the given exit status
 * (0) si info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int extch;

	if (info->argv[1]) /* s'il y a un argument */
	{
		extch = _erratoi(info->argv[1]);
		if (extch == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);

}

/**
 * _mycd - it changes the current rep of  process
 * @info: The Struct containing potential args. Used to maintain
 * the const fct prototype.
 * Return: Toujours 0
 */
int _mycd(info_t *info)
{
	char *v, *d, bfr[1024];
	int chdir_ret;

	v = getcwd(bfr, 1024);
	if (!v)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		d = _getenv(info, "HOME=");
		if (!d)
			chdir_ret = /* TODO: que doit etre? */
				chdir((d = _getenv(info, "PWD=")) ? d : "/");
		else
			chdir_ret = chdir(d);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(v);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: que doit etre? */
			chdir((d = _getenv(info, "OLDPWD=")) ? d : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(bfr, 1024));
	}
	return (0);
}


/**
 * _myhelp - the changes of the current dir of this process
 * @info: Struct contain the potential args. Used to maintain
 * the const fct prototype.
 * Return: Toujours 0
 */
int _myhelp(info_t *info)
{
	char **ag_arr;

	ag_arr = info->argv;
	_puts("The help call works. Fct not implemented yet\n");
	if (0)
		_puts(*ag_arr); /* temporary unused workaround */
	return (0);
}
