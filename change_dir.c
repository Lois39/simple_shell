#include "shell.h"

/**
 * cd_first - changes to the parent directory
 * @tash: data relevant (environ)
 * Return: no return
 */
void cd_first(data_shell *tash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	se_tenv("OLDPWD", cp_pwd, tash);
	dir = tash->args[1];
	if (_strcmp(".", dir) == 0)
	{
	se_tenv("PWD", cp_pwd, tash);
	free(cp_pwd);
	return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
	free(cp_pwd);
	return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
	cp_strtok_pwd = _strtok(NULL, "\0");
	if (cp_strtok_pwd != NULL)
	rev_string(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
	chdir(cp_strtok_pwd);
	se_tenv("PWD", cp_strtok_pwd, tash);
	}
	else
	{
	chdir("/");
	se_tenv("PWD", "/", tash);
	}
	tash->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory when given
 * @tash: directories
 * Return: no return
 */
void cd_to(data_shell *tash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = tash->args[1];
	if (chdir(dir) == -1)
	{
	get_error(tash, 2);
	return;
	}
	cp_pwd = _strdup(pwd);
	se_tenv("OLDPWD", cp_pwd, datash);
	cp_dir = _strdup(dir);
	se_tenv("PWD", cp_dir, datash);
	free(cp_pwd);
	free(cp_dir);
	tash->status = 0;
	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 * @tash: data of the environ
 * Return: no return
 */
void cd_previous(data_shell *tash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", tash->_environ);

	if (p_oldpwd == NULL)
	cp_oldpwd = cp_pwd;
	else
	cp_oldpwd = _strdup(p_oldpwd);
	se_tenv("OLDPWD", cp_pwd, tash);
	if (chdir(cp_oldpwd) == -1)
	se_tenv("PWD", cp_pwd, tash);
	else
	se_tenv("PWD", cp_oldpwd, tash);

	p_pwd = _getenv("PWD", tash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
	free(cp_oldpwd);
	tash->status = 0;
	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 * @tash: data of the environ
 * Return: no return
 */
void cd_to_home(data_shell *tash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
	se_tenv("OLDPWD", p_pwd, datash);
	free(p_pwd);
	return;
	}
	if (chdir(home) == -1)
	{
	get_error(tash, 2);
	free(p_pwd);
	return;
	}
	se_tenv("OLDPWD", p_pwd, tash);
	se_tenv("PWD", home, tash);
	free(p_pwd);
	tash->status = 0;
}
