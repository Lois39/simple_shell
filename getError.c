#include "shell.h"

/**
 * get_error - it will call the error according sytnax
 * @tash: data structure
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *tash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
	error = error_env(tash);
	break;
	case 126:
	error = error_path_126(tash);
	break;
	case 127:
	error = error_not_found(tash);
	break;
	case 2:
	if (_strcmp("exit", tash->args[0]) == 0)
	error = error_exit_shell(tash);
	else if (_strcmp("cd", tash->args[0]) == 0)
	error = error_get_cd(tash);
	break;
	}
	if (error)
	{
	write(STDERR_FILENO, error, _strlen(error));
	free(error);
	}
	tash->status = eval;
	return (eval);
}
