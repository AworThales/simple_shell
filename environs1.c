#include "main.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int a;

	for (a = 0; nenv[a] != '='; a++)
	{
		if (nenv[a] != name[a])
		{
			return (0);
		}
	}

	return (a + 1);
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_envir;
	int a, ma;

	/* Initialize ptr_envir value */
	ptr_envir = NULL;
	ma = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (a = 0; _environ[a]; a++)
	{
		/* If name and env are equal */
		ma = cmp_env_name(_environ[a], name);
		if (ma)
		{
			ptr_envir = _environ[a];
			break;
		}
	}

	return (ptr_envir + ma);
}

/**
 * _env - prints the evironment variables
 *
 * @shinfo: data relevant.
 * Return: 1 on success.
 */
int _env(shell_info *shinfo)
{
	int a, b;

	for (a = 0; shinfo->_environ[a]; a++)
	{

		for (b = 0; shinfo->_environ[a][b]; b++)
			;

		write(STDOUT_FILENO, shinfo->_environ[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	shinfo->status = 0;

	return (1);
}
