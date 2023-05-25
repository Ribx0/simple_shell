#include "main.h"
/**
 * built_in - it checks for built_in cmd.
 * @command: cmd to chck.
 * @free_line: line to free if is ext cmd.
 * @process_status: status of lst process.
 * Return: 1 pour success.
 * cas fails 0 returned.
*/
int built_in(char *command, char *free_line, int process_status)
{
	int ck_blt_in;

	ck_blt_in = get_built_in(command);
	if (ck_blt_in == 0)
	{
		free(free_line);
		exit(WEXITSTATUS(process_status));
	}
	else if (ck_blt_in == 1)
	{
		puts_env();
		return (1);
	}
	return (0);
}

/**
 * puts_env - it prints all the envr vars.
*/
void puts_env(void)
{
	int l;

	for (l = 0; environ[l]; l++)
	{
		write(STDOUT_FILENO, environ[l], _strlen(environ[l]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * look_for_comment - it checks for cmnt.
 * @command_line: cmd line.
 * Return: cmd line.
*/
char *look_for_comment(char *command_line)
{
	int l = 0;

	if (_strlen(command_line) >= 2)
	{
		while (command_line[l])
		{
			if (command_line[l] == '#' && command_line[l - 1] == ' ')
			{
				command_line[l - 1] = '\0';
				break;
			}
			l++;
		}
	}
	return (command_line);
}
