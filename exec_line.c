#include "main.h"

/**
 * exec_line - finds the builtins and commands
 *
 * @shinfo: data relevants (args)
 * Return: 1 on success.
 */
int exec_line(shell_info *shinfo)
{
	int (*builtin)(shell_info *shinfo);

	if (shinfo->args[0] == NULL)
		return (1);

	builtin = get_builtin(shinfo->args[0]);

	if (builtin != NULL)
		return (builtin(shinfo));

	return (cmd_exec(shinfo));
}
