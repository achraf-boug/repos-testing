#include "shell.h"

/**
 * getHistory - print history list
 * @info: Structure containing arguments.
 *
 *  Return: Always 0
 */
int getHistory(std_infos *info)
{
	showLinkedList(info->history);
	return (0);
}

/**
 * unsetAlias - uset alias
 * @info: struct std_infos
 * @s: alias string
 *
 * Return: 0 if ok, 1 if fails
 */
int unsetAlias(std_infos *info, char *s)
{
	char *p, c;
	int ret;

	p = _strsrch(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rmNodeIndex(&(info->alias),
		nodeIndex(info->alias, nodeStart(info->alias, s, -1)));
	*p = c;
	return (ret);
}

/**
 * setAlias - set alias
 * @info: struct info cmd
 * @s: alias string
 *
 * Return: 0 if ok, 1 if fails
 */
int setAlias(std_infos *info, char *s)
{
	char *p;

	p = _strsrch(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsetAlias(info, s));

	unsetAlias(info, s);
	return (addNode(&(info->alias), s, 0) == NULL);
}

/**
 * printAlias - prints an alias string
 * @n: alias node
 *
 * Return: 0 if ok, 1 if fails
 */
int printAlias(list_str *n)
{
	char *pt = NULL, *a = NULL;

	if (n)
	{
		pt = _strsrch(n->s, '=');
		for (a = n->s; a <= pt; a++)
			_putchar(*a);
		_putchar('\'');
		_putstr(pt + 1);
		_putstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliasShell - man alias
 * @info: Structure containing arguments.
 *
 *  Return: Always 0
 */
int aliasShell(std_infos *info)
{
	int i = 0;
	char *p = NULL;
	list_str *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			printAlias(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strsrch(info->argv[i], '=');
		if (p)
			setAlias(info, info->argv[i]);
		else
			printAlias(nodeStart(info->alias, info->argv[i], '='));
	}

	return (0);
}
