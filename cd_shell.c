#include "main.h"

/**
 * cd_shell - changes the current directory
 *
 * @shinfo: data relevants
 * Return: 1 on success
 */
int cd_shell(shell_info *shinfo)
{
	char *directory;
	int if_home, if_home1, if_dash;

	directory = shinfo->args[1];

	if (directory != NULL)
	{
		if_home = _strcmp("$HOME", directory);
		if_home1 = _strcmp("~", directory);
		if_dash = _strcmp("--", directory);
	}

	if (directory == NULL || !if_home || !if_home1 || !if_dash)
	{
		cd_to_home(shinfo);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_previous(shinfo);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_dot(shinfo);
		return (1);
	}

	cd_to(shinfo);

	return (1);
}
