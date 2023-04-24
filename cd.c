#include "main.h"

/**
 * cd_dot - changes to the parents directory
 *
 * @shinfo: data relevants (environ)
 *
 * Return: no return
 */
void cd_dot(shell_info *shinfo)
{
	char paswd[PATH_MAX];
	char *directory, *cp_paswd, *cp_strtok_paswd;

	getcwd(paswd, sizeof(paswd));
	cp_paswd = _strdup(paswd);
	set_env("OLDPWD", cp_paswd, shinfo);
	directory = shinfo->args[1];
	if (_strcmp(".", directory) == 0)
	{
		set_env("PWD", cp_paswd, shinfo);
		free(cp_paswd);
		return;
	}
	if (_strcmp("/", cp_paswd) == 0)
	{
		free(cp_paswd);
		return;
	}
	cp_strtok_paswd = cp_paswd;
	rev_string(cp_strtok_paswd);
	cp_strtok_paswd = _strtok(cp_strtok_paswd, "/");
	if (cp_strtok_paswd != NULL)
	{
		cp_strtok_paswd = _strtok(NULL, "\0");

		if (cp_strtok_paswd != NULL)
			rev_string(cp_strtok_paswd);
	}
	if (cp_strtok_paswd != NULL)
	{
		chdir(cp_strtok_paswd);
		set_env("PWD", cp_strtok_paswd, shinfo);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", shinfo);
	}
	shinfo->status = 0;
	free(cp_paswd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @shinfo: data relevants (directories)
 * Return: no return
 */
void cd_to(shell_info *shinfo)
{
	char paswd[PATH_MAX];
	char *directory, *cp_paswd, *cp_dir;

	getcwd(paswd, sizeof(paswd));

	directory = shinfo->args[1];
	if (chdir(directory) == -1)
	{
		get_error(shinfo, 2);
		return;
	}

	cp_paswd = _strdup(paswd);
	set_env("OLDPWD", cp_paswd, shinfo);

	cp_dir = _strdup(directory);
	set_env("PWD", cp_dir, shinfo);

	free(cp_paswd);
	free(cp_dir);

	shinfo->status = 0;

	chdir(directory);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @shinfo: data relevant (environ)
 * Return: no return
 */
void cd_previous(shell_info *shinfo)
{
	char paswd[PATH_MAX];
	char *p_paswd, *p_oldpaswd, *cp_paswd, *cp_oldpaswd;

	getcwd(paswd, sizeof(paswd));
	cp_paswd = _strdup(paswd);

	p_oldpaswd = _getenv("OLDPWD", shinfo->_environ);

	if (p_oldpaswd == NULL)
		cp_oldpaswd = cp_paswd;
	else
		cp_oldpaswd = _strdup(p_oldpaswd);

	set_env("OLDPWD", cp_paswd, shinfo);

	if (chdir(cp_oldpaswd) == -1)
		set_env("PWD", cp_paswd, shinfo);
	else
		set_env("PWD", cp_oldpaswd, shinfo);

	p_paswd = _getenv("PWD", shinfo->_environ);

	write(STDOUT_FILENO, p_paswd, _strlen(p_paswd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_paswd);
	if (p_oldpaswd)
		free(cp_oldpaswd);

	shinfo->status = 0;

	chdir(p_paswd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @shinfo: data relevants (environ)
 * Return: no return
 */
void cd_to_home(shell_info *shinfo)
{
	char *p_paswd, *home;
	char paswd[PATH_MAX];

	getcwd(paswd, sizeof(paswd));
	p_paswd = _strdup(paswd);

	home = _getenv("HOME", shinfo->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_paswd, shinfo);
		free(p_paswd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(shinfo, 2);
		free(p_paswd);
		return;
	}

	set_env("OLDPWD", p_paswd, shinfo);
	set_env("PWD", home, shinfo);
	free(p_paswd);
	shinfo->status = 0;
}
