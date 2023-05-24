#include "shell.h"

/**
 * hsh - the main shell loop
 * @info: prmtr & return info strct
 * @av: the arg vect from main()
 *
 * Return: 0 pour success, 1 pour error, else error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r1 = 0;
	int bltn_r = 0;

	while (r1 != -1 && bltn_r != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r1 = get_input(info);
		if (r1 != -1)
		{
			set_info(info, av);
			bltn_r = find_builtin(info);
			if (bltn_r == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (bltn_r == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
		}
	return (bltn_r);
}

/**
 * find_builtin - finds a bltn cmd
 * @info: the prmtr & return info strct
 *
 * Return: -1 if bltn not found,
 * 0 if bltn executed successfully,
 *	1 if bltn found but not successful,
 *	2 if bltn signals exit()
 */
int find_builtin(info_t *info)
{
	int l, blt_rt;
	builtin_table bltntbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (l = 0; bltntbl[l].type; l++)
		if (_strcmp(info->argv[0], bltntbl[l].type) == 0)
		{
			info->line_count++;
			blt_rt = bltntbl[l].func(info);
			break;
		}
	return (blt_rt);
}


/**
 * find_cmd - finds a cmd in the path
 * @info: the prmtr and return info strct
 *
 * Return: the void
 */
void find_cmd(info_t *info)
{
	char *pth1 = NULL;
	int l, m;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (l = 0, m = 0; info->arg[l]; l++)
		if (!is_delim(info->arg[l], " \t\n"))
			m++;
	if (!m)
		return;

	pth1 = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (pth1)
	{
		info->path = pth1;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an exct thrd to run comd
 * @info: the prmtr & return the info struct
 *
 * Return: the void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pd1;

	child_pd1 = fork();
	if (child_pd1 == -1)
	{
		/* TODO: PUT ERR FNCT */
		perror("Error:");
		return;
	}
	if (child_pd1 == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Prmssion denied\n");
		}
	}
}
