#include "shell.h"

/**
 * free_data - frees data
 * @tash: the data
 * Return: no return
 */

void free_data(data_shell *tash)
{
	unsigned int i;

	for (i = 0; tash->_environ[i]; i++)
	{
	free(tash->_environ[i]);
	}
	free(tash->_environ);
	free(tash->pid);
}

/**
 * set_data - to initialize data structure
 * @tash: the data
 * @ar: argument struct
 * Return: none
 */
void set_data(data_shell *tash, char **ar)
{
	unsigned int i;

	tash->ar = ar;
	tash->input = NULL;
	tash->args = NULL;
	tash->status = 0;
	tash->counter = 1;

	for (i = 0; environ[i]; i++)
	;
	tash->_environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
	tash->_environ[i] = _strdup(environ[i]);
	}
	tash->_environ[i] = NULL;
	tash->pid = aux_itoa(getpid());
}
/**
 * main - Entry point
 * @ac: argument count
 * @ar: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **ar)
{
	data_shell tash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&tash, ar);
	shell_loop(&tash);
	free_data(&tash);
	if (tash.status < 0)
	return (255);
	return (tash.status);
}
