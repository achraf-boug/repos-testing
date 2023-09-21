#include "shell.h"

/**
 * runShell - Execute the main shell loop.
 * @in: Pointer to the std_infos struct containing shell information.
 * @str: Array of strings containing command line arguments.
 *
 * Return: the status code to indicate the exit condition of the shell.
 */
int runShell(std_infos *in, char **str)
{
	ssize_t i = 0;
	int ret = 0;

	while (i != -1 && ret != -2)
	{
		unsetInfo(in);
		if (is_Active(in))
			_putstr("$ ");
		putchar_err(BUFFLUSH);
		i = getInput(in);
		if (i != -1)
		{
			setInfo(in, str);
			ret = getBuiltin(in);
			if (ret == -1)
				checkinPath(in);
		}
		else if (is_Active(in))
			_putchar('\n');
		flushInfo(in, 0);
	}
	creathistory(in);
	flushInfo(in, 1);
	if (!is_Active(in) && in->status)
		exit(in->status);
	if (ret == -2)
	{
		if (in->err_num == -1)
			exit(in->status);
		exit(in->err_num);
	}
	return (ret);
}

/**
 * getBuiltin - Find and execute a built-in command.
 * @in: Pointer to the std_infos struct containing shell information.
 *
 * Return: the result of executing the built-in command or -1 if the command
 * is not found.
 */
int getBuiltin(std_infos *in)
{
	int i, ret = -1;
	builtin_list table[] = {
		{"exit", exitShell},
		{"env", showEnvp},
		{"help", helpShell},
		{"history", getHistory},
		{"setenv", setEnvParam},
		{"unsetenv", unsetEnvParam},
		{"cd", cdShell},
		{"alias", aliasShell},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
		if (_strcmp(in->argv[0], table[i].type) == 0)
		{
			in->line_count++;
			ret = table[i].func(in);
			break;
		}
	return (ret);
}

/**
 * checkinPath - Handle non-built-in commands by searching in the PATH.
 * @in: Pointer to the std_infos struct containing shell information.
 *
 * Return: none
 */
void checkinPath(std_infos *in)
{
	char *th = NULL;
	int i, j;

	in->path = in->argv[0];
	if (in->linecount_flag == 1)
	{
		in->line_count++;
		in->linecount_flag = 0;
	}
	for (i = 0, j = 0; in->arg[i]; i++)
		if (!is_Delim(in->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	th = returnFullPath(in, getEnvParam(in, "PATH="), in->argv[0]);
	if (th)
	{
		in->path = th;
		runFork(in);
	}
	else
	{
		if ((is_Active(in) || getEnvParam(in, "PATH=")
			|| in->argv[0][0] == '/') && getCmdPath(in, in->argv[0]))
			runFork(in);
		else if (*(in->arg) != '\n')
		{
			in->status = 127;
			flush_err(in, "not found\n");
		}
	}
}

/**
 * runFork - Fork and execute a command in a child process.
 * @in: Pointer to the std_infos struct containing shell information.
 *
 * Return: none
 */
void runFork(std_infos *in)
{
	pid_t id;

	id = fork();
	if (id == -1)
	{
		perror("Error:");
		return;
	}
	if (id == 0)
	{
		if (execve(in->path, in->argv, getEnv(in)) == -1)
		{
			flushInfo(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(in->status));
		if (WIFEXITED(in->status))
		{
			in->status = WEXITSTATUS(in->status);
			if (in->status == 126)
				flush_err(in, "Permission denied\n");
		}
	}
}
