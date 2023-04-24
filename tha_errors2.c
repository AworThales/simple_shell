#include "main.h"

/**
 * error_env - error sms for this env in get_env.
 * @shinfo: data for relevants (counter, arguments)
 * Return: ck_error for the sms.
 */
char *error_env(shell_info *shinfo)
{
	int lengths;
	char *ck_error;
	char *v_stri;
	char *sms;

	v_stri = tha_itoa(shinfo->counter);
	sms = ": Unable to add/remove from environment\n";
	lengths = _strlen(shinfo->av[0]) + _strlen(v_stri);
	lengths += _strlen(shinfo->args[0]) + _strlen(sms) + 4;
	ck_error = malloc(sizeof(char) * (lengths + 1));
	if (ck_error == 0)
	{
		free(ck_error);
		free(v_stri);
		return (NULL);
	}

	_strcpy(ck_error, shinfo->av[0]);
	_strcat(ck_error, ": ");
	_strcat(ck_error, v_stri);
	_strcat(ck_error, ": ");
	_strcat(ck_error, shinfo->args[0]);
	_strcat(ck_error, sms);
	_strcat(ck_error, "\0");
	free(v_stri);

	return (ck_error);
}
/**
 * error_path_126 - error sms for path and failure denied permission.
 * @shinfo: data the relevants (counter, arguments).
 *
 * Return: The ck_error for the string.
 */
char *error_path_126(shell_info *shinfo)
{
	int lengths;
	char *v_stri;
	char *ck_error;

	v_stri = tha_itoa(shinfo->counter);
	lengths = _strlen(shinfo->av[0]) + _strlen(v_stri);
	lengths += _strlen(shinfo->args[0]) + 24;
	ck_error = malloc(sizeof(char) * (lengths + 1));
	if (ck_error == 0)
	{
		free(ck_error);
		free(v_stri);
		return (NULL);
	}
	_strcpy(ck_error, shinfo->av[0]);
	_strcat(ck_error, ": ");
	_strcat(ck_error, v_stri);
	_strcat(ck_error, ": ");
	_strcat(ck_error, shinfo->args[0]);
	_strcat(ck_error, ": Permission denied\n");
	_strcat(ck_error, "\0");
	free(v_stri);
	return (ck_error);
}
