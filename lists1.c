#include "shell.h"

/**
 * lislength - Calculate the length of a linked list.
 * @len: Pointer to the start of the linked list.
 *
 * Return: Number of elements in the linked list.
 */
size_t lislength(const list_str *len)
{
	size_t i = 0;

	while (len)
	{
		len = len->next;
		i++;
	}
	return (i);
}

/**
 * linkedToList - Convert linked list to array of strings.
 * @str: Pointer to the start of the linked list.
 *
 * Return: Array of strings converted from linked list.
 */
char **linkedToList(list_str *str)
{
	list_str *no = str;
	size_t i = lislength(str), j;
	char **c;
	char *st;

	if (!str || !i)
		return (NULL);
	c = malloc(sizeof(char *) * (i + 1));
	if (!c)
		return (NULL);
	for (i = 0; no; no = no->next, i++)
	{
		st = malloc(_strlen(no->s) + 1);
		if (!st)
		{
			for (j = 0; j < i; j++)
				free(c[j]);
			free(c);
			return (NULL);
		}

		st = _strcpy(st, no->s);
		c[i] = st;
	}
	c[i] = NULL;
	return (c);
}


/**
 * showLinkedList - Print a linked list of numbers and strings.
 * @lt: Pointer to the start of the linked list.
 *
 * Return: Number of elements printed.
 */
size_t showLinkedList(const list_str *lt)
{
	size_t i = 0;

	while (lt)
	{
		_putstr(_strTonum(lt->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_putstr(lt->s ? lt->s : "(nil)");
		_putstr("\n");
		lt = lt->next;
		i++;
	}
	return (i);
}

/**
 * nodeStart - Find a linked list node that starts with a given string.
 * @st: Pointer to the start of the linked list.
 * @ch: String to search for at the beginning of a node's string.
 * @str: Character to match at the start of the found node's string.
 *
 * Return: Pointer to the found node or NULL if not found.
 */
list_str *nodeStart(list_str *st, char *ch, char str)
{
	char *k = NULL;

	while (st)
	{
		k = _strstart(st->s, ch);
		if (k && ((str == -1) || (*k == str)))
			return (st);
		st = st->next;
	}
	return (NULL);
}

/**
 * nodeIndex - Find the index of a linked list node.
 * @in: Pointer to the start of the linked list.
 * @dex: Pointer to the node to find the index for.
 *
 * Return: Index of the found node or -1 if not found.
 */
ssize_t nodeIndex(list_str *in, list_str *dex)
{
	size_t i = 0;

	while (in)
	{
		if (in == dex)
			return (i);
		in = in->next;
		i++;
	}
	return (-1);
}
