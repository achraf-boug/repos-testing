#include "shell.h"

/**
 * setChain - Identify and set command chaining type.
 * @in: Pointer to the shell information struct.
 * @buffer: Command buffer containing the command and chaining symbol.
 * @ad: Pointer to the index where the chaining symbol is located.
 *
 * Return: 1 if a valid chaining symbol is found, 0 otherwise.
 */

int setChain(std_infos *in, char *buffer, size_t *ad)
{
	size_t j = *ad;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		in->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		in->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		in->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ad = j;
	return (1);
}

/**
 * checkCMD - Check and adjust command buffer based on chaining type.
 * @in: Pointer to the shell information struct.
 * @buffer: Command buffer containing the command and chaining symbol.
 * @pst: Pointer to the index tracking the position within the buffer.
 * @i: Current index position within the buffer.
 * @lg: Length of the buffer.
 *
 * Return: none
 */
void checkCMD(std_infos *in, char *buffer, size_t *pst, size_t i, size_t lg)
{
	size_t j = *pst;

	if (in->cmd_buf_type == CMD_AND)
	{
		if (in->status)
		{
			buffer[i] = 0;
			j = lg;
		}
	}
	if (in->cmd_buf_type == CMD_OR)
	{
		if (!in->status)
		{
			buffer[i] = 0;
			j = lg;
		}
	}

	*pst = j;
}

/**
 * setAlias - Replace command name with alias argument from the alias list.
 * @in: Pointer to the shell information struct.
 *
 * Return: 1 on success, 0 on failure.
 */
int setAlias(std_infos *in)
{
	int i;
	list_str *st;
	char *par;

	for (i = 0; i < 10; i++)
	{
		st = nodeStart(in->alias, in->argv[0], '=');
		if (!st)
			return (0);
		free(in->argv[0]);
		par = _strsrch(st->s, '=');
		if (!par)
			return (0);
		par = _strcpy2(par + 1);
		if (!par)
			return (0);
		in->argv[0] = par;
	}
	return (1);
}

/**
 * getParam - Replace variables in command arguments with their values.
 * @in: Pointer to the shell information struct.
 *
 * Return: 0 on successful replacement.
 */
int getParam(std_infos *in)
{
	int i = 0;
	list_str *str;

	for (i = 0; in->argv[i]; i++)
	{
		if (in->argv[i][0] != '$' || !in->argv[i][1])
			continue;

		if (!_strcmp(in->argv[i], "$?"))
		{
			_strreplace(&(in->argv[i]), _strcpy2(_strTonum(in->status, 10, 0)));
			continue;
		}
		if (!_strcmp(in->argv[i], "$$"))
		{
			_strreplace(&(in->argv[i]), _strcpy2(_strTonum(getpid(), 10, 0)));
			continue;
		}
		str = nodeStart(in->env, &in->argv[i][1], '=');
		if (str)
		{
			_strreplace(&(in->argv[i]), _strcpy2(_strsrch(str->s, '=') + 1));
			continue;
		}
		_strreplace(&in->argv[i], _strcpy2(""));

	}
	return (0);
}

/**
 * _strreplace - Replace old string with a new one.
 * @strold: Pointer to the old string to be replaced.
 * @strnew: Pointer to the new string to replace with.
 *
 * Return: 1 to indicate successful replacement.
 */
int _strreplace(char **strold, char *strnew)
{
	free(*strold);
	*strold = strnew;
	return (1);
}
