#include "main.h"

/**
 * exit_shell - exits this shell
 *
 * @shinfo: data relevants (status and args)
 * Return: 0 on success.
 */
int exit_shell(shell_info *shinfo)
{
	int large_num;
	unsigned int usetatus;
	int str_length;
	int is_digit;

	if (shinfo->args[1] != NULL)
	{
		usetatus = _atoi(shinfo->args[1]);
		is_digit = _isdigit(shinfo->args[1]);
		str_length = _strlen(shinfo->args[1]);
		large_num = usetatus > (unsigned int)INT_MAX;
		if (!is_digit || str_length > 10 || large_num)
		{
			get_error(shinfo, 2);
			shinfo->status = 2;
			return (1);
		}
		shinfo->status = (usetatus % 256);
	}
	return (0);
}
