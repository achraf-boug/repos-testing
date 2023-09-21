#include "shell.h"

/**
 * _strcpy - Copy a string to another.
 * @est: Destination string.
 * @sc: Source string.
 *
 * Return: Pointer to the destination string 'est'.
 */
char *_strcpy(char *est, char *sc)
{
	int i = 0;

	if (est == sc || sc == 0)
		return (est);
	while (sc[i])
	{
		est[i] = sc[i];
		i++;
	}
	est[i] = 0;
	return (est);
}

/**
 * _strcpy2 - Create a duplicate of a string.
 * @st: Source string to be duplicated.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */
char *_strcpy2(const char *st)
{
	int lg = 0;
	char *r;

	if (st == NULL)
		return (NULL);
	while (*st++)
		lg++;
	r = malloc(sizeof(char) * (lg + 1));
	if (!r)
		return (NULL);
	for (lg++; lg--;)
		r[lg] = *--st;
	return (r);
}

/**
 * _putstr - Print a string to stdout.
 * @s: Source string to be printed.
 *
 * Return: None.
 */
void _putstr(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - Write a character to stdout or flush buffer.
 * @str: Character to be written or BUFFLUSH to flush.
 *
 * Return: 1 after writing or flushing.
 */
int _putchar(char str)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (str == BUFFLUSH || i >= BUFFER_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (str != BUFFLUSH)
		buffer[i++] = str;
	return (1);
}
