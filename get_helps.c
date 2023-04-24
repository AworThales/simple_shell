#include "main.h"

/**
 * get_help - the function that retrieves help messages according builtin
 * @shinfo: the data structure (args and input)
 * Return: Return 0
*/
int get_help(shell_info *shinfo)
{

	if (shinfo->args[1] == 0)
		tha_help_general();
	else if (_strcmp(shinfo->args[1], "setenv") == 0)
		tha_help_setenv();
	else if (_strcmp(shinfo->args[1], "env") == 0)
		tha_help_env();
	else if (_strcmp(shinfo->args[1], "unsetenv") == 0)
		tha_help_unsetenv();
	else if (_strcmp(shinfo->args[1], "help") == 0)
		tha_help();
	else if (_strcmp(shinfo->args[1], "exit") == 0)
		tha_help_exit();
	else if (_strcmp(shinfo->args[1], "cd") == 0)
		tha_help_cd();
	else if (_strcmp(shinfo->args[1], "alias") == 0)
		tha_help_alias();
	else
		write(STDERR_FILENO, shinfo->args[0],
		      _strlen(shinfo->args[0]));

	shinfo->status = 0;
	return (1);
}
