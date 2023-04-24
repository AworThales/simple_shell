#include "main.h"

/**
 * is_cdir - checks ":" if is in this current directory.
 * @path: type char pointer char.
 * @i: type int pointer of the index.
 * Return: 1 if the path is a searchable in the cd, 0 otherwise.
 */
int is_cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locate a command
 *
 * @cmd: command name
 * @_environ: environment of variable
 * Return: location of this command.
 */
char *_which(char *cmd, char **_environ)
{
	int length_dir, len_cmd, i;
	char *path, *ptr_path, *token_path, *dir;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			length_dir = _strlen(token_path);
			dir = malloc(length_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - determines if this is an executable
 *
 * @shinfo: data structure
 * Return: 0 if this is not an executable, other number if it does
 */
int is_executable(shell_info *shinfo)
{
	struct stat st;
	char *typing;
	int i;

	typing = shinfo->args[0];
	for (i = 0; typing[i]; i++)
	{
		if (typing[i] == '.')
		{
			if (typing[i + 1] == '.')
				return (0);
			if (typing[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (typing[i] == '/' && i != 0)
		{
			if (typing[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(typing + i, &st) == 0)
	{
		return (i);
	}
	get_error(shinfo, 127);
	return (-1);
}

/**
 * check_error_cmd - verifies if the user has permissions to access
 *
 * @dir: destination of directory
 * @shinfo: data structure
 * Return: 1 if the was an error, 0 if not
 */
int check_error_cmd(char *dir, shell_info *shinfo)
{
	if (dir == NULL)
	{
		get_error(shinfo, 127);
		return (1);
	}

	if (_strcmp(shinfo->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(shinfo, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shinfo->args[0], X_OK) == -1)
		{
			get_error(shinfo, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - executes command line
 *
 * @shinfo: data relevant (args and input)
 * Return: 1 on success.
 */
int cmd_exec(shell_info *shinfo)
{
	pid_t wpd;
	pid_t pd;
	int states;
	char *dir;
	int execs;
	(void) wpd;

	execs = is_executable(shinfo);
	if (execs == -1)
		return (1);
	if (execs == 0)
	{
		dir = _which(shinfo->args[0], shinfo->_environ);
		if (check_error_cmd(dir, shinfo) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (execs == 0)
			dir = _which(shinfo->args[0], shinfo->_environ);
		else
			dir = shinfo->args[0];
		execve(dir + execs, shinfo->args, shinfo->_environ);
	}
	else if (pd < 0)
	{
		perror(shinfo->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &states, WUNTRACED);
		} while (!WIFEXITED(states) && !WIFSIGNALED(states));
	}

	shinfo->status = states / 256;
	return (1);
}
