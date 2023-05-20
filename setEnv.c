#include "shell.h"
/**
 * setEnv - intialise new an environment
 * @name:  name of the environment to be set
 * @value: value of the environment to be set
 * @tash: data structure
 * Return: no return
 */
void setEnv(char *name, char *value, data_shell *tash)
{
	int c;
	char *var_env, *name_env;

	for (c = 0; tash->_environ[c]; c++)
	{
	var_env = _strdup(tash->_environ[c]);
	name_env = _strtok(var_env, "=");
	if (_strcmp(name_env, name) == 0)
	{
	free(tash->_environ[c]);
	tash->environ[c] = _info(name_env, value);
	free(var_env);
	return;
	}
	free(var_env);
	}
	tash->_environ = _reallocdp(tash->_environ, c, sizeof(char *) * (c + 2));
	tash->_environ[c] = _info(name, value);
	tash->_environ[c + 1] = NULL;
}

/**
 * _info - info to create a new environment
 * @name: name of the env
 * @value: value of the env
 * Return : env
 */

char *_info(char *name, char *value)
{
	char *env;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	env = malloc(sizeof(char) * (len));
	_strcpy(env, name);
	_strcat(env, "=");
	_strcat(env, value);
	_strcat(env, "\0");
	return (env);

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
	setEnv(tash->args[1], tash->args[2], tash);
	return (1);
}

/**
 * unsetenv - it will delete an env variable
 * @tash: environment name
 * Return: 1 on success.
 */
int unsetenv(data_shell *tash)
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
	var_env = _strdup(tash->environ[i]);
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
