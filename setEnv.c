#include "shell.h"
/**
 * se_tenv - intialise new an environment
 * @name:  name of the environment to be set
 * @value: value of the environment to be set
 * @tash: data structure
 * Return: no return
 */
void se_tenv(char *name, char *value, data_shell *tash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; tash->_environ[i]; i++)
	{
	var_env = _strdup(tash->_environ[i]);
	name_env = _strtok(var_env, "=");
	if (_strcmp(name_env, name) == 0)
	{
	free(tash->_environ[i]);
	tash->_environ[i] = copy_info(name_env, value);
	free(var_env);
	return;
	}
	free(var_env);
	}
	tash->_environ = _reallocdp(tash->_environ, i, sizeof(char *) * (i + 2));
	tash->_environ[i] = copy_info(name, value);
	tash->_environ[i + 1] = NULL;
}

/**
 * copy_info - info to create a new environment
 * @name: name of the env
 * @value: value of the env
 * Return : new
 */

char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");
	return (new);

}

/**
 * set_env - to compare environment variables
 * @tash: environ name and environment value
 * Return: On success return 1.
 */

int set_env(data_shell *tash)
{
	if (tash->args[1] == NULL || tash->args[2] == NULL)
	{
	get_error(tash, -1);
	return (1);
	}
	se_tenv(tash->args[1], tash->args[2], tash);
	return (1);
}

/**
 * _unsetenv - it will delete an env variable
 * @tash: environment name
 * Return: 1 on success.
 */
int _unsetenv(data_shell *tash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (tash->args[1] == NULL)
	{
	get_error(tash, -1);
	return (1);
	}
	k = -1;
	for (i = 0; tash->_environ[i]; i++)
	{
	var_env = _strdup(tash->_environ[i]);
	name_env = _strtok(var_env, "=");
	if (_strcmp(name_env, tash->args[i]) == 0)
	{
	k = i;
	}
	free(var_env);
	}
	if (k == -1)
	{
	get_error(tash, -1);
	return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; tash->_environ[i]; i++)
	{
	if (i != k)
	{
	realloc_environ[j] = tash->_environ[i];
	j++;
	}
	}
	realloc_environ[j] = NULL;
	free(tash->_environ[k]);
	free(tash->_environ);
	tash->_environ = realloc_environ;
	return (1);
}
