#include "main.h"

/**
 * copy_info - copies info to the create
 * a latest env or alias
 * @name: name (env or alias)
 * @value: values (env or alias)
 *
 * Return: latest of env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *latest;
	int length_name, length_value, length;

	length_name = _strlen(name);
	length_value = _strlen(value);
	length = length_name + length_value + 2;
	latest = malloc(sizeof(char) * (length));
	_strcpy(latest, name);
	_strcat(latest, "=");
	_strcat(latest, value);
	_strcat(latest, "\0");

	return (latest);
}

/**
 * set_env - sets the environment variable
 *
 * @name: name of environment variable
 * @value: value of environment variable
 * @shinfo: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, shell_info *shinfo)
{
	int a;
	char *var_envir, *name_envir;

	for (a = 0; shinfo->_environ[a]; a++)
	{
		var_envir = _strdup(shinfo->_environ[a]);
		name_envir = _strtok(var_envir, "=");
		if (_strcmp(name_envir, name) == 0)
		{
			free(shinfo->_environ[a]);
			shinfo->_environ[a] = copy_info(name_envir, value);
			free(var_envir);
			return;
		}
		free(var_envir);
	}

	shinfo->_environ = _reallocdp(shinfo->_environ, a, sizeof(char *) * (a + 2));
	shinfo->_environ[a] = copy_info(name, value);
	shinfo->_environ[a + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @shinfo: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shell_info *shinfo)
{

	if (shinfo->args[1] == NULL || shinfo->args[2] == NULL)
	{
		get_error(shinfo, -1);
		return (1);
	}

	set_env(shinfo->args[1], shinfo->args[2], shinfo);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @shinfo: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shell_info *shinfo)
{
	char **realloc_environ;
	char *var_envir, *name_envir;
	int a, j, k;

	if (shinfo->args[1] == NULL)
	{
		get_error(shinfo, -1);
		return (1);
	}
	k = -1;
	for (a = 0; shinfo->_environ[a]; a++)
	{
		var_envir = _strdup(shinfo->_environ[a]);
		name_envir = _strtok(var_envir, "=");
		if (_strcmp(name_envir, shinfo->args[1]) == 0)
		{
			k = a;
		}
		free(var_envir);
	}
	if (k == -1)
	{
		get_error(shinfo, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (a));
	for (a = j = 0; shinfo->_environ[a]; a++)
	{
		if (a != k)
		{
			realloc_environ[j] = shinfo->_environ[a];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(shinfo->_environ[k]);
	free(shinfo->_environ);
	shinfo->_environ = realloc_environ;
	return (1);
}
