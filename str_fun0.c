#include "main.h"
/**
 * _strlen - to know the lenght of the str
 * @str: the ptr which point to str
 * Return: the lenght
*/
int _strlen(char *str)
{
	int ln = 0;

	while (*str != '\0')
	{
		str++;
		ln++;
	}
	return (ln);
}
/**
 * count_args - cnt args from cmd line
 * @line: commd line
 * Return: nbr of the args
 */
int count_args(char *line)
{
	int l = 0, sr_sc = 1, nbr_arg = 0;

	while (line[l] != '\0')
	{
		if (line[l] != ' ' && sr_sc == 1)
		{
			nbr_arg++;
			sr_sc = 0;
		}
		if (line[l + 1] == ' ')
			sr_sc = 1;
		l++;
	}
	return (nbr_arg);
}

/**
 * _strdup - it duplicates str to an other one
 * @str: strg
 * Return: the buffer
 */
char *_strdup(char *str)
{
	int ln = 0, m = 0;
	char *bfr;

	if (!str)
		return (NULL);
	while (str[ln] != '\0')
		ln++;
	bfr = malloc(sizeof(char) * (ln + 1));
	if (!bfr)
		return (NULL);
	while (str[m] != '\0')
	{
		bfr[m] = str[m];
		m++;
	}
	bfr[m] = '\0';
	return (bfr);
}


/**
 * _strcpy - cp the str to the other.
 * @src: The fr str
 * @dest: to strg
 * Return: success the strg.
*/
char *_strcpy(char *dest, char *src)
{
	int ln = 0, m;

	while (src[ln] != '\0')
		ln++;
	for (m = 0; m <= ln; m++)
		dest[m] = src[m];
	return (dest);
}

/**
 * _strcat - it concats str to other
 * @dest: str to.
 * @src: str from.
 * Return: success the str.
 */
char *_strcat(char *dest, char *src)
{
	int l = 0;

	while (*dest != '\0')
	{
		dest++;
		l++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		l++;
		src++;
	}
	*dest = '\0';
	dest -= l;
	return (dest);
}
