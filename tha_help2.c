#include "main.h"

/**
 * tha_help - Help information for builtin helpers.
 * Return: no return
 */
void tha_help(void)
{
	char *helpers = "helpers: helpers [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}
/**
 * tha_help_alias - Help information for builtin alias.
 * Return: no return
 */
void tha_help_alias(void)
{
	char *helpers = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}
/**
 * tha_help_cd - Help information for builtin alias.
 * Return: no return
 */
void tha_help_cd(void)
{
	char *helpers = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}
