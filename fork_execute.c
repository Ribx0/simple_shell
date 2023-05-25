#include "main.h"
/**
 * super_execute - exect file
 * @command_line: flie to exct
 * @nameof: frst argv of main
 * Return: status of lst process
*/
int super_execute(char *command_line, char *nameof)
{
	pid_t pd;
	char **ars = NULL, **ev = environ, *pth;
	int n_ars, st = 0;

	if (*command_line != '\0' && *command_line != '#')
	{
		command_line = look_for_comment(command_line);
		n_ars = count_args(command_line);
		ars = allocate_buffer(n_ars, command_line);
		pth = full_path(ars[0]);
		if (pth != NULL)
		{
			pd = fork();
			if (pd == 0)
			{
				execve(pth, ars, ev);
				perror(ars[0]);
			}
			else if (pd > 0)
				waitpid(pd, &st, 0);
			else
				perror("fork");
		}
		else
		{
			write(STDERR_FILENO, nameof, strlen(nameof));
			write(STDERR_FILENO, ": 1: ", 5);
			write(STDERR_FILENO, ars[0], strlen(ars[0]));
			write(STDERR_FILENO, ": not found\n", 12);
		}
		if (pth != ars[0])
			free(pth);
		special_free(ars);
	}
	return (st);
}

/**
 * full_path - gives full path
 * @file_name: file looking for
 * Return: the pntr the path of file
*/
char *full_path(char *file_name)
{
	char r_pth[BUFF_SIZE], *p_pth, **ev = environ, *pths, *f_pths;
	int l = 0;

	if (access(file_name, F_OK) == 0)
		return (file_name);
	while (ev[l] != NULL)
	{
		if (our_strncmp(ev[l], "PATH=", 5) == 0)
		{
			pths = _strdup(ev[l] + 5);
			f_pths = strtok(pths, ":");
			while (f_pths)
			{
				p_pth = _strcpy(r_pth, f_pths);
				p_pth = _strcat(r_pth, "/");
				p_pth = _strdup(_strcat(r_pth, file_name));
				if (access(p_pth, X_OK) == 0)
				{
					free(pths);
					return (p_pth);
				}
				free(p_pth);
				f_pths = strtok(NULL, ":");
			}
			free(pths);
		}
		l++;
	}
	return (NULL);
}
