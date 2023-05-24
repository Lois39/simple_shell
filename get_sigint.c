#include "shell.h"

/**
 * get_sigint - handle the copy call in the
 * command prompt
 * @sig: the handler
 */

void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
