#include "shell.h"

/**
 * _erratoi - converts the str to int
 * @s: the str to convert
 * Return: 0 if no nbrs in str, converted nbr otherwise
 *       -1 on err
 */
int _erratoi(char *s)
{
	int l = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;  /* TODO: why does it makes main return 255? */
	for (l = 0;  s[l] != '\0'; l++)
	{
		if (s[l] >= '0' && s[l] <= '9')
		{
			res *= 10;
			res += (s[l] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - it prints the error msg
 * @info: the parmtr & return the info struct
 * @estr: strg containing the specified err type
 * Return: returns 0 if no nbrs in str, converted nbr otherwise
 *        -1 on err
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - fct prints a decimal (int) nbr (base 10)
 * @input: input
 * @fd: filedesc to write to
 *
 * Return: nbr of chars to be printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int l, count = 0;
	unsigned int _abs_, curr;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (_abs_ / l)
		{
			__putchar('0' + curr / l);
			count++;
		}
		curr %= l;
	}
	__putchar('0' + curr);
	count++;

	return (count);
}

/**
 * convert_number - convert the function, clone of itoa
 * @num: the nbr
 * @base: the base
 * @flags: the arg flags
 *
 * Return: it returns string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buff[50];
	char sin = 0;
	char *ptr2;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sin = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr2 = &buff[49];
	*ptr2 = '\0';

	do	{
		*--ptr2 = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sin)
		*--ptr2 = sin;
	return (ptr2);
}

/**
 * remove_comments - fct replaces frst inst of '#' with '\0'
 * @buf: the address of string to mod
 *
 * Return: Toujours 0;
 */
void remove_comments(char *buf)
{
	int l;

	for (l = 0; buf[l] != '\0'; l++)
		if (buf[l] == '#' && (!l || buf[l - 1] == ' '))
		{
			buf[l] = '\0';
			break;
		}
}
