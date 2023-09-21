#include "shell.h"

/**
 * exitShell - Handle shell exit command.
 * @in: Pointer to the shell information struct.
 *
 * Return: Signal to terminate shell or error code.
 */
int exitShell(std_infos *in)
{
	int ext;

	if (in->argv[1])
	{
		ext = _atoi_er(in->argv[1]);
		if (ext == -1)
		{
			in->status = 2;
			flush_err(in, "Illegal number: ");
			put_err(in->argv[1]);
			putchar_err('\n');
			return (1);
		}
		in->err_num = _atoi_er(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * cdShell - Handle shell 'cd' command.
 * @in: Pointer to the shell information struct.
 *
 * Return: 0 on success, 1 on informational output, -1 on failure.
 */
int cdShell(std_infos *in)
{
	char *str, *d, buffer[1024];
	int ret;

	str = getcwd(buffer, 1024);
	if (!str)
		_putstr("TODO: >>getcwd failure emsg here<<\n");
	if (!in->argv[1])
	{
		d = getEnvParam(in, "HOME=");
		if (!d)
			ret = chdir((d = getEnvParam(in, "PWD=")) ? d : "/");
		else
			ret = chdir(d);
	}
	else if (_strcmp(in->argv[1], "-") == 0)
	{
		if (!getEnvParam(in, "OLDPWD="))
		{
			_putstr(str);
			_putchar('\n');
			return (1);
		}
		_putstr(getEnvParam(in, "OLDPWD=")), _putchar('\n');
		ret = chdir((d = getEnvParam(in, "OLDPWD=")) ? d : "/");
	}
	else
		ret = chdir(in->argv[1]);
	if (ret == -1)
	{
		flush_err(in, "can't cd to ");
		put_err(in->argv[1]), putchar_err('\n');
	}
	else
	{
		setEnv(in, "OLDPWD", getEnvParam(in, "PWD="));
		setEnv(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpShell - Handle shell 'help' command.
 * @in: Pointer to the shell information struct.
 *
 * Return: Always returns 0.
 */
int helpShell(std_infos *in)
{
	char **ar;

	ar = in->argv;
	_putstr("help call works. Function not yet implemented \n");
	if (0)
		_putstr(*ar);
	return (0);
}
