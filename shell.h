#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>


#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;
/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* getline */
ssize_t my_getline(char **linee, size_t *n, FILE *stream);
<<<<<<< HEAD
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);

/* setEnv.c */
char *copy_info(char *name, char *value);
void se_tenv(char *name, char *value, data_shell *tash);
int set_env(data_shell *tash);
int _unsetenv(data_shell *tash);


/* getEnv1.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *tash);

/*  change_dir.c */
void cd_first(data_shell *tash);
void cd_to(data_shell *tash);
void cd_previous(data_shell *tash);
void cd_to_home(data_shell *tash);

/* getError.c */
int get_error(data_shell *tash, int eval)

/* get_sigint.c */
void get_sigint(int sig)

/* aux_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *tash);
char *error_not_found(data_shell *tash);
char *error_exit_shell(data_shell *tash);

/* help.c */
void aux_help_env(void)
void aux_help_setenv(void)
void aux_help_unsetenv(void)
void aux_help_general(void)
void aux_help_exit(void)

/* Str.c */
char *_strchr(char *s, char c)
int _strcmp(char *s1, char *s2)
char *_strcpy(char *dest, char *src)
char *_strcat(char *dest, const char *src)
int _strspn(char *s, char *accept)

/* aux_help.c */
void aux_help_cd(void)
void aux_help_alias(void)
void aux_help(void)

/* str1.c */
char *_strdup(const char *s)
int _strlen(const char *s)
int cmp_chars(char str[], const char *delim)
char *_strtok(char str[], const char *delim)

/* str2.c */
void rev_string(char *s)
int _isdigit(const char *s)

/* get_len.c */
int get_len(int n)
int _atoi(char *s)
char *aux_itoa(int n)
=======
/* set env */
void setEnv(char *name, char *value, data_shell *tash)
char *_info(char *name, char *value)
int set_env(data_shell *tash)
int unsetenv(data_shell *tash)
>>>>>>> 1d52b90bb5adbd5046d32319d27efb640502a395

#endif
