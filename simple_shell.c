#include "main.h"
/**
 * main - smpl shell.
 * @argc: nbr of the args
 * @argv: ptr to arr of str of the args
 * Return: 0 toujours
*/
int main(int argc __attribute__((unused)), char *argv[])
{
	size_t leng;
	char *ln = NULL, *cmd;
	int n, lp = 0, st = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#omar/sfn$ ", 11);
		n = getline(&ln, &leng, stdin);
		if (n >= 0)
		{
			ln[n - 1] = '\0';
			cmd = ignore_spaces(ln);
			if (!built_in(cmd, ln, st))
				st = super_execute(cmd, argv[0]);
			free(ln);
			ln = NULL;
		}
		else
		{
			free(ln);
			break;
		}
		lp++;
	}
	return (0);
}

/**
 * ignore_spaces - ignr surrounded spcs in cmd
 * @old_line: the cmd line
 * Return: the cmd line after rmv spaces
*/
char *ignore_spaces(char *old_line)
{
	char *fin_ln, *nw_ln = old_line;

	while (*nw_ln == ' ')
		nw_ln++;
	fin_ln = nw_ln + (_strlen(nw_ln) - 1);
	while (fin_ln > nw_ln && *fin_ln == ' ')
		fin_ln--;
	*(fin_ln + 1) = '\0';
	return (nw_ln);
}

/**
 * allocate_buffer - it allocates mmry for the args
 * @num_args: the nbr of the args
 * @command: cmd line
 * Return: the args
 */
char **allocate_buffer(int num_args, char *command)
{
	char **ags, *dlmt = " ", *ag_u;
	int l = 0;

	ags = malloc((num_args + 1) * sizeof(char *));
	if (!ags)
		return (NULL);
	ag_u = strtok(command, dlmt);
	while (ag_u != NULL)
	{
		ags[l] = _strdup(ag_u);
		ag_u = strtok(NULL, dlmt);
		l++;
	}
	ags[l] = NULL;
	return (ags);
}
/**
 * special_free - fr all memo
 * @args: it pointes to the ptr
 */
void special_free(char **args)
{
	int l = 0;

	if (args != NULL)
	{
		while (args[l] != NULL)
		{
			free(args[l]);
			l++;
		}
		free(args[l]);
		free(args);
	}
}
