#include "shell.h"

/**
 **_strncpy - it copies a strg
 *@dest: the destin str to copy to
 *@src: the src str
 *@n: the amount of chars to copy
 *Return: the conc str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int l, m;
	char *s = dest;

	l = 0;
	while (src[l] != '\0' && l < n - 1)
	{
		dest[l] = src[l];
		l++;
	}
	if (l < n)
	{
		m = l;
		while (m < n)
		{
			dest[m] = '\0';
			m++;
		}
	}
	return (s);
}

/**
 **_strncat - it conc 2 strs
 *@dest: the frst str
 *@src: the scnd str
 *@n: amount of the bytes to be max used
 *Return: the conc str
 */
char *_strncat(char *dest, char *src, int n)
{
	int l, m;
	char *s = dest;

	l = 0;
	m = 0;
	while (dest[l] != '\0')
		l++;
	while (src[m] != '\0' && m < n)
	{
		dest[l] = src[m];
		l++;
		m++;
	}
	if (m < n)
		dest[l] = '\0';
	return (s);
}

/**
 **_strchr - it locates a char in a str
 *@s: the str to pars
 *@c: the char to be looked for
 *Return: (s) a ptr to the mmry area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
