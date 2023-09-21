#include "shell.h"

/**
 * _atoi_er - Convert a string to an integer with error handling.
 * @str: Pointer to the input string.
 *
 * Return: The converted integer value or -1 on error.
 */
int _atoi_er(char *str)
{
	int i = 0;
	unsigned long int res = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			res *= 10;
			res += (str[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * flush_err - Print error message to stderr.
 * @in: Pointer to std_infos struct.
 * @str: Error message string.
 *
 * Return: None.
 */
void flush_err(std_infos *in, char *str)
{
	put_err(in->fname);
	put_err(": ");
	_itod(in->line_count, STDERR_FILENO);
	put_err(": ");
	put_err(in->argv[0]);
	put_err(": ");
	put_err(str);
}

/**
 * _itod - Print an integer in decimal format.
 * @put: Integer to be printed.
 * @file: File descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int _itod(int put, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, cnt = 0;
	unsigned int _abs_, c;

	if (file == STDERR_FILENO)
		__putchar = putchar_err;
	if (put < 0)
	{
		_abs_ = -put;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = put;
	c = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + c / i);
			cnt++;
		}
		c %= i;
	}
	__putchar('0' + c);
	cnt++;

	return (cnt);
}

/**
 * _strTonum - Convert a number to a specified base and format.
 * @m: Number to be converted.
 * @b: Base for conversion (e.g., 16 for hexadecimal).
 * @fl: Conversion format flags.
 *
 * Return: Pointer to the converted number string.
 */
char *_strTonum(long int m, int b, int fl)
{
	static char *ar;
	static char buffer[50];
	char s = 0;
	char *poiter;
	unsigned long n = m;

	if (!(fl & TO_UNSIGNED) && m < 0)
	{
		n = -m;
		s = '-';

	}
	ar = fl & TO_LOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	poiter = &buffer[49];
	*poiter = '\0';

	do	{
		*--poiter = ar[n % b];
		n /= b;
	} while (n != 0);

	if (s)
		*--poiter = s;
	return (poiter);
}

/**
 * remove_coms - Remove comments from a string buffer.
 * @buffer: Input string buffer to process.
 *
 * Return: None.
 */
void remove_coms(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
