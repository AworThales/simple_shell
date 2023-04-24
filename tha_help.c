#include "main.h"

/**
 * tha_help_env - Help information for this builtin env
 * Return: no return
 */
void tha_help_env(void)
{
	char *helpers = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, helpers, _strlen(helpers));

}
/**
 * tha_help_setenv - Help information for this builtin setenv
 * Return: no return
 */
void tha_help_setenv(void)
{

	char *helpers = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "int replace)\n\t";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}
/**
 * tha_help_unsetenv - Help information for builtin unsetenv
 * Return: no return
 */
void tha_help_unsetenv(void)
{
	char *helpers = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}


/**
 * tha_help_general - Entry point for helpers info for this helpers builtin
 * Return: no return
 */
void tha_help_general(void)
{
	char *helpers = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "These command are define internally.Type 'helpers' to see a list";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "Type 'helpers name' to finout more about the func 'name'.\n\n ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "unsetenv [variable]\n";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}
/**
 * tha_help_exit - Help information for this builint exit
 * Return: no return
 */
void tha_help_exit(void)
{
	char *helpers = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
	helpers = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, helpers, _strlen(helpers));
}
