#include "shell.h"

/**
 * getCmdPath - Check if a given path points to a regular file.
 * @in: Pointer to the std_infos struct (not used in this function).
 * @p: Path to be checked for regular file status.
 *
 * Return: 1 if the path points to a regular file, 0 otherwise.
 */
int getCmdPath(std_infos *in, char *p)
{
	struct stat str;

	(void)in;
	if (!p || stat(p, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _strncpy - Create a duplicate substring from a given range in a string.
 * @str: Pointer to the input string.
 * @tart: Starting index of the substring.
 * @top: Ending index of the substring.
 *
 * Return: Pointer to the duplicated substring.
 */
char *_strncpy(char *str, int tart, int top)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = tart; i < top; i++)
		if (str[i] != ':')
			buffer[j++] = str[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * returnFullPath - Find and return the full path of a command.
 * @in: Pointer to std_infos struct.
 * @str: Colon-separated paths.
 * @cd: Command name.
 *
 * Return: Full path if found, else NULL.
 */
char *returnFullPath(std_infos *in, char *str, char *cd)
{
	int i = 0, position = 0;
	char *ph;

	if (!str)
		return (NULL);
	if ((_strlen(cd) > 2) && _strstart(cd, "./"))
	{
		if (getCmdPath(in, cd))
			return (cd);
	}
	while (1)
	{
		if (!str[i] || str[i] == ':')
		{
			ph = _strncpy(str, position, i);
			if (!*ph)
				_strcat(ph, cd);
			else
			{
				_strcat(ph, "/");
				_strcat(ph, cd);
			}
			if (getCmdPath(in, ph))
				return (ph);
			if (!str[i])
				break;
			position = i;
		}
		i++;
	}
	return (NULL);
}
