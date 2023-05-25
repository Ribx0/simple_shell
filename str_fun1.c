#include "main.h"
/**
 * our_strncmp - it compares to strg by idx
 * @f_str: the frst str
 * @s_str: the scnd str
 * @n: indx
 * Return: 0 pour success
 * sinon error -1 returns
*/
int our_strncmp(char *f_str, char *s_str, int n)
{
	int l = 0;

	while (l < n)
	{
	if (f_str[l] != s_str[l])
		return (-1);
	l++;
	}
	return (0);
}
/**
 * get_built_in - get built in cmds
 * @str: cmds
 * Return: 0 si success
 */
int get_built_in(char *str)
{
	int l = -1;

	if (_strlen(str) == 4 && our_strncmp(str, "exit", 4) == 0)
		l = 0;
	else if (_strlen(str) == 3 && our_strncmp(str, "env", 3) == 0)
		l = 1;
	return (l);
}
