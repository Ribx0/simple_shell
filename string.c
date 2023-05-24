#include "shell.h"

/**
 * _strlen - it returns the len of a str
 * @s: str whose len to check
 *
 * Return: returns intgr length of str
 */
int _strlen(char *s)
{
	int l = 0;

	if (!s)
		return (0);

	while (*s++)
		l++;
	return (l);
}

/**
 * _strcmp - perfrms lexicogarphic compars of 2 strangs.
 * @s1: frst strang
 * @s2: scnd strang
 *
 * Return: ngtv if s1 < s2, pstv if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - it checks if needle starts with haystack
 * @haystack: str to srch
 * @needle: substr to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates 2 strgs
 * @dest: the dest bfr
 * @src: the source bufr
 *
 * Return: ptr to dest bufr
 */
char *_strcat(char *dest, char *src)
{
	char *ret1 = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret1);
}
