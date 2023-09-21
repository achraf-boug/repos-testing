#include "shell.h"

/**
 * historyfile - Generate history file path.
 * @in: Pointer to the shell information struct.
 *
 * Return: Pointer to the generated history file path or NULL on failure.
 */

char *historyfile(std_infos *in)
{
	char *buffer, *d;

	d = getEnvParam(in, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(d) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, d);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * creathistory - Create history file.
 * @in: Pointer to the shell information struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int creathistory(std_infos *in)
{
	ssize_t file;
	char *name = historyfile(in);
	list_str *c = NULL;

	if (!name)
		return (-1);

	file = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (file == -1)
		return (-1);
	for (c = in->history; c; c = c->next)
	{
		put_file(c->s, file);
		putchar_file('\n', file);
	}
	putchar_file(BUFFLUSH, file);
	close(file);
	return (1);
}

/**
 * readHistory - Read history from file and populate list.
 * @in: Pointer to the shell information struct.
 *
 * Return: Number of history entries read and added to the list.
 */
int readHistory(std_infos *in)
{
	int i, lt = 0, lcount = 0;
	ssize_t file, len, sz = 0;
	struct stat str;
	char *buffer = NULL, *name = historyfile(in);

	if (!name)
		return (0);

	file = open(name, O_RDONLY);
	free(name);
	if (file == -1)
		return (0);
	if (!fstat(file, &str))
		sz = str.st_size;
	if (sz < 2)
		return (0);
	buffer = malloc(sizeof(char) * (sz + 1));
	if (!buffer)
		return (0);
	len = read(file, buffer, sz);
	buffer[sz] = 0;
	if (len <= 0)
		return (free(buffer), 0);
	close(file);
	for (i = 0; i < sz; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			buildHistoList(in, buffer + lt, lcount++);
			lt = i + 1;
		}
	if (lt != i)
		buildHistoList(in, buffer + lt, lcount++);
	free(buffer);
	in->histcount = lcount;
	while (in->histcount-- >= HIST_MAX)
		rmNodeIndex(&(in->history), 0);
	renumHistory(in);
	return (in->histcount);
}

/**
 * buildHistoList - Build command history list.
 * @in: Pointer to the shell information struct.
 * @buffer: Command string to be added to history.
 * @lcount: Line number of the command in the history file.
 *
 * Return: 0 on success.
 */
int buildHistoList(std_infos *in, char *buffer, int lcount)
{
	list_str *str = NULL;

	if (in->history)
		str = in->history;
	addNode(&str, buffer, lcount);

	if (!in->history)
		in->history = str;
	return (0);
}

/**
 * renumHistory - Renumber history list entries.
 * @in: Pointer to the shell information struct.
 *
 * Return: New history count after renumbering.
 */
int renumHistory(std_infos *in)
{
	list_str *str = in->history;
	int i = 0;

	while (str)
	{
		str->n = i++;
		str = str->next;
	}
	return (in->histcount = i);
}
