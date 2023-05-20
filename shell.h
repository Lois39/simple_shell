#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

ssize_t my_getline(char **linee, size_t *n, FILE *stream);
//set env//
void setEnv(char *name, char *value, data_shell *tash)
char *_info(char *name, char *value)
int set_env(data_shell *tash)
int unsetenv(data_shell *tash)

#endif
