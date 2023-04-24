#include "main.h"

/**
 * get_error - calls this error according the builtin, syntax or permission
 * @shinfo: data structure that carries arguments
 * @eval: error for value
 * Return: error
 */
int get_error(shell_info *shinfo, int eval)
{
	char *check_error;

	switch (eval)
	{
	case -1:
		check_error = error_env(shinfo);
		break;
	case 126:
		check_error = error_path_126(shinfo);
		break;
	case 127:
		check_error = error_not_found(shinfo);
		break;
	case 2:
		if (_strcmp("exit", shinfo->args[0]) == 0)
			check_error = error_exit_shell(shinfo);
		else if (_strcmp("cd", shinfo->args[0]) == 0)
			check_error = error_get_cd(shinfo);
		break;
	}

	if (check_error)
	{
		write(STDERR_FILENO, check_error, _strlen(check_error));
		free(check_error);
	}

	shinfo->status = eval;
	return (eval);
}
