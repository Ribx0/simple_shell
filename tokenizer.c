#include "shell.h"

/**
 * **strtow - it splits str into words. Repeat delimiters are ignored
 * @str: input str
 * @d: delimeter strg
 * Return: a ptr to an arr of strgs, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int l, n, kh, h, nmwrd = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (l = 0; str[l] != '\0'; l++)
		if (!is_delim(str[l], d) && (is_delim(str[l + 1], d) || !str[l + 1]))
			nmwrd++;

	if (nmwrd == 0)
		return (NULL);
	ss = malloc((1 + nmwrd) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (l = 0, n = 0; n < nmwrd; n++)
	{
		while (is_delim(str[l], d))
			l++;
		kh = 0;
		while (!is_delim(str[l + kh], d) && str[l + kh])
			kh++;
		ss[n] = malloc((kh + 1) * sizeof(char));
		if (!ss[n])
		{
			for (kh = 0; kh < n; kh++)
				free(ss[kh]);
			free(ss);
			return (NULL);
		}
		for (h = 0; h < kh; h++)
			ss[n][h] = str[l++];
		ss[n][h] = 0;
	}
	ss[n] = NULL;
	return (ss);
}

/**
 * **strtow2 - it splits a str into the words
 * @str: input str
 * @d: delimeter
 * Return: ptr to an arr of strgs, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int l, n, kh, h, nmwrd = 0;
	char **ss;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (l = 0; str[l] != '\0'; l++)
		if ((str[l] != d && str[l + 1] == d) ||
				    (str[l] != d && !str[l + 1]) || str[l + 1] == d)
			nmwrd++;
	if (nmwrd == 0)
		return (NULL);
	ss = malloc((1 + nmwrd) * sizeof(char *));
	if (!ss)
		return (NULL);
	for (l = 0, n = 0; n < nmwrd; n++)
	{
		while (str[l] == d && str[l] != d)
			l++;
		kh = 0;
		while (str[l + kh] != d && str[l + kh] && str[l + kh] != d)
			kh++;
		ss[n] = malloc((kh + 1) * sizeof(char));
		if (!ss[n])
		{
			for (kh = 0; kh < n; kh++)
				free(ss[kh]);
			free(ss);
			return (NULL);
		}
		for (h = 0; h < kh; h++)
			ss[n][h] = str[l++];
		ss[n][h] = 0;
	}
	ss[n] = NULL;
	return (ss);
}
