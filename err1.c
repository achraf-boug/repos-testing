#include "shell.h"

/**
 * put_err - Print a string to stderr.
 * @s: Source string to be printed.
 *
 * Return: None.
 */
void put_err(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		putchar_err(s[i]);
		i++;
	}
}

/**
 * putchar_err - Write a character to stderr or flush buffer.
 * @str: Character to be written or BUFFLUSH to flush.
 *
 * Return: 1 after writing or flushing.
 */
int putchar_err(char str)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (str == BUFFLUSH || i >= BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (str != BUFFLUSH)
		buffer[i++] = str;
	return (1);
}

/**
 * putchar_file - Write a character to a file or flush buffer.
 * @str: Character to be written or BUFFLUSH to flush.
 * @file: File descriptor to write to.
 *
 * Return: 1 after writing or flushing.
 */
int putchar_file(char str, int file)
{
	static int i;
	static char buffer[BUFFER_SIZE];

	if (str == BUFFLUSH || i >= BUFFER_SIZE)
	{
		write(file, buffer, i);
		i = 0;
	}
	if (str != BUFFLUSH)
		buffer[i++] = str;
	return (1);
}

/**
 * put_file - Write a string to a file.
 * @str: Source string to be written.
 * @file: File descriptor to write to.
 *
 * Return: Number of characters written.
 */
int put_file(char *str, int file)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putchar_file(*str++, file);
	}
	return (i);
}
