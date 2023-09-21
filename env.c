#include "shell.h"

/**
 * showEnvp - prints the environment
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int showEnvp(std_infos *info)
{
	showLinkedList(info->env);
	return (0);
}

/**
 * getEnvParam - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: environ name
 *
 * Return: the environ value
 */
char *getEnvParam(std_infos *info, const char *name)
{
	list_str *node = info->env;
	char *p;

	while (node)
	{
		p = _strstart(node->s, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvParam - set a environment variable
 * @i: Structure containing potential arguments
 *
 *  Return: 0 if ok 1 if fails
 */
int setEnvParam(std_infos *i)
{
	if (i->argc != 3)
	{
		put_err("Incorrect number of arguements\n");
		return (1);
	}
	if (setEnv(i, i->argv[1], i->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvParam - unset env variable
 * @info: Structure containing arguments
 *  Return: 0 if ok 1 if fails
 */
int unsetEnvParam(std_infos *info)
{
	int i;

	if (info->argc == 1)
	{
		put_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetEnv(info, info->argv[i]);

	return (0);
}

/**
 * initEnvParams - init list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initEnvParams(std_infos *info)
{
	list_str *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNode(&node, environ[i], 0);
	info->env = node;
	return (0);
}
