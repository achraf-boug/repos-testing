#include "shell.h"

/**
 * unsetInfo - initializes info_t struct
 * @info: struct address
 */
void unsetInfo(std_infos *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - init struct std_infos
 * @info: struct info cmd
 * @a: init values
 */
void setInfo(std_infos *info, char **a)
{
	int i = 0;

	info->fname = a[0];
	if (info->arg)
	{
		info->argv = _strsplit(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strcpy2(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		setAlias(info);
		getParam(info);
	}
}

/**
 * flushInfo - free std_infos struct
 * @info: pointer to struct
 * @a: true if ok
 */
void flushInfo(std_infos *info, int a)
{
	flush_list_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (a)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			flushLinkedList(&(info->env));
		if (info->history)
			flushLinkedList(&(info->history));
		if (info->alias)
			flushLinkedList(&(info->alias));
		flush_list_str(info->environ);
			info->environ = NULL;
		flushMem((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFLUSH);
	}
}
