#include "shell.h"

/**
 * interactive - it Returns true if the shell is in an interactive mode
 * @info: The addrs structred
 *
 * Return: it returns 1 if it's an interactive mode, else it returns 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if the char is a delmtr
 * @c: The char checked
 * @delim: The delmtr strd
 * Return: it return 1 if it's true, else 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checker for the alphabetic char
 * @c: The char that should be input
 * Return: if c is alphabetic it returns 1, else 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - it converts the str to an int
 * @s: String converted
 * Return: if no nbrs in str it returns 0, else convert the nb
 */

int _atoi(char *s)
{
	int f, sg = 1, fg = 0, oput;
	unsigned int rst = 0;

	for (f = 0; s[f] != '\0' && fg != 2; f++)
	{
		if (s[f] == '-')
			sg *= -1;

		if (s[f] >= '0' && s[f] <= '9')
		{
			fg = 1;
			rst *= 10;
			rst += (s[f] - '0');
		}
		else if (fg == 1)
			fg = 2;
	}

	if (sg == -1)
		oput = -rst;
	else
		oput = rst;

	return (oput);
}
