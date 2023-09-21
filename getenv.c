#include "shell.h"

/**
 * getEnv - Retrieve environment variables as an array.
 * @info: Pointer to std_infos structure with environment data.
 *
 * Return: Array of strings containing environment variables.
 */
char **getEnv(std_infos *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = linkedToList(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * unsetEnv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int unsetEnv(std_infos *info, char *v)
{
	list_str *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !v)
		return (0);

	while (node)
	{
		p = _strstart(node->s, v);
		if (p && *p == '=')
		{
			info->env_changed = rmNodeIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}



/**
 * setEnv - Set or update an environment variable.
 * @info: Pointer to std_infos structure with environment data.
 * @v: Variable name.
 * @val: Variable value.
 *
 * Return: 0 on success, 1 on memory allocation error.
 */
int setEnv(std_infos *info, char *v, char *val)
{
	char *buffer = NULL;
	list_str *node;
	char *p;

	if (!v || !val)
		return (0);

	buffer = malloc(_strlen(v) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, v);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	node = info->env;
	while (node)
	{
		p = _strstart(node->s, v);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	addNode(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
