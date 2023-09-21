#ifndef _SHELL_
#define _SHELL_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer global variables */
#define BUFFER_SIZE 1024
#define BUFFLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define TO_LOWER	1
#define TO_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;


/**
 * struct list_str - defines a list of strings
 * @n: index of the node
 * @s: node's string value
 * @next: Pointer to the next node in the linked list.
 */
typedef struct list_str
{
	int n;
	char *s;
	struct list_str *next;
} list_str;

/**
 *struct info - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: getline's input
 *@argv: list of arguments
 *@path: path value
 *@argc: number of arguments
 *@line_count: the error count
 *@err_num: error number
 *@linecount_flag: if on count this line of input
 *@fname: program filename
 *@env: linked list of environ
 *@environ: custom modified copy of environ from LL env
 *@history: historical node
 *@alias: alias node
 *@env_changed: check if environ was changed
 *@status: status of executed command
 *@cmd_buf: address of pointer to buffer
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: read line input
 *@histcount: line number count of history
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_str *env;
	list_str *history;
	list_str *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} std_infos;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct built_in - contains a built_in string and related function
 *@type: the built_in command flag
 *@func: the function
 */
typedef struct built_in
{
	char *type;
	int (*func)(std_infos *);
} builtin_list;


/* runShell.c */
int runShell(std_infos *, char **);
int getBuiltin(std_infos *);
void checkinPath(std_infos *);
void runFork(std_infos *);

/* fctString2.c */
int getCmdPath(std_infos *, char *);
char *_strncpy2(char *, int, int);
char *returnFullPath(std_infos *, char *, char *);

/* err1.c */
void put_err(char *);
int putchar_err(char);
int putchar_file(char c, int fd);
int put_file(char *str, int fd);

/* fctString.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strstart(const char *, const char *);
char *_strcat(char *, char *);

/* fctString1.c */
char *_strcpy(char *, char *);
char *_strcpy2(const char *);
void _putstr(char *);
int _putchar(char);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strsrch(char *, char);

/* fctString3.c */
char **_strsplit(char *, char *);
char **_strsplit2(char *, char);

/* allocation.c */
char *setMem(char *, char, unsigned int);
void flush_list_str(char **);
void *reallocMem(void *, unsigned int, unsigned int);

/* mem.c */
int flushMem(void **);

/* fctString4.c */
int is_Active(std_infos *);
int is_Delim(char, char *);
int is_Alpha(int);
int _atoi(char *);

/* err2.c */
int _atoi_er(char *);
void flush_err(std_infos *, char *);
int _itod(int, int);
char *_strTonum(long int, int, int);
void remove_coms(char *);

/* built_in.c */
int exitShell(std_infos *);
int cdShell(std_infos *);
int helpShell(std_infos *);

/* built_in1.c */
int getHistory(std_infos *);
int aliasShell(std_infos *);

/* fctBuffer.c */
ssize_t getInput(std_infos *);
int _getline(std_infos *, char **, size_t *);
void sigintHandler(int);

/* getinfo.c */
void unsetInfo(std_infos *);
void setInfo(std_infos *, char **);
void flushInfo(std_infos *, int);

/* env.c */
char *getEnvParam(std_infos *, const char *);
int showEnvp(std_infos *);
int setEnvParam(std_infos *);
int unsetEnvParam(std_infos *);
int initEnvParams(std_infos *);

/* getenv.c */
char **getEnv(std_infos *);
int unsetEnv(std_infos *, char *);
int setEnv(std_infos *, char *, char *);

/* lists.c */
list_str *addNode(list_str **, const char *, int);
size_t showLinkedList(const list_str *);
int rmNodeIndex(list_str **, unsigned int);
void flushLinkedList(list_str **);

/* lists1.c */
char **linkedToList(list_str *);
size_t showLinkedList(const list_str *);
list_str *nodeStart(list_str *, char *, char);
ssize_t nodeIndex(list_str *, list_str *);

/* vars.c */
int setChain(std_infos *, char *, size_t *);
void checkCMD(std_infos *, char *, size_t *, size_t, size_t);
int setAlias(std_infos *);
int getParam(std_infos *);
int _strreplace(char **, char *);

#endif
