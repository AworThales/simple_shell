#include "main.h"

/**
 * strcat_cd - function that concatenates sms for cd _error
 *
 * @shinfo: data relevant (directory)
 * @sms: sms to be print
 * @ck_error: output for sms
 * @v_stri: counter lines
 * Return: error of sms
 */
char *strcat_cd(shell_info *shinfo, char *sms, char *ck_error, char *v_stri)
{
	char *not_legal_flag;

	_strcpy(ck_error, shinfo->av[0]);
	_strcat(ck_error, ": ");
	_strcat(ck_error, v_stri);
	_strcat(ck_error, ": ");
	_strcat(ck_error, shinfo->args[0]);
	_strcat(ck_error, sms);
	if (shinfo->args[1][0] == '-')
	{
		not_legal_flag = malloc(3);
		not_legal_flag[0] = '-';
		not_legal_flag[1] = shinfo->args[1][1];
		not_legal_flag[2] = '\0';
		_strcat(ck_error, not_legal_flag);
		free(not_legal_flag);
	}
	else
	{
		_strcat(ck_error, shinfo->args[1]);
	}

	_strcat(ck_error, "\n");
	_strcat(ck_error, "\0");
	return (ck_error);
}

/**
 * error_get_cd - error sms for the cd command in get_cd
 * @shinfo: data relevants (directory)
 * Return: Error sms
 */
char *error_get_cd(shell_info *shinfo)
{
	int lengths, len_id;
	char *ck_error, *v_stri, *sms;

	v_stri = tha_itoa(shinfo->counter);
	if (shinfo->args[1][0] == '-')
	{
		sms = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		sms = ": can't cd to ";
		len_id = _strlen(shinfo->args[1]);
	}

	lengths = _strlen(shinfo->av[0]) + _strlen(shinfo->args[0]);
	lengths += _strlen(v_stri) + _strlen(sms) + len_id + 5;
	ck_error = malloc(sizeof(char) * (lengths + 1));

	if (ck_error == 0)
	{
		free(v_stri);
		return (NULL);
	}

	ck_error = strcat_cd(shinfo, sms, ck_error, v_stri);

	free(v_stri);

	return (ck_error);
}

/**
 * error_not_found - generic error sms for the command not found
 * @shinfo: data relevants (counter, arguments)
 * Return: Error sms
 */
char *error_not_found(shell_info *shinfo)
{
	int lengths;
	char *ck_error;
	char *v_stri;

	v_stri = tha_itoa(shinfo->counter);
	lengths = _strlen(shinfo->av[0]) + _strlen(v_stri);
	lengths += _strlen(shinfo->args[0]) + 16;
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
	_strcat(ck_error, ": not found\n");
	_strcat(ck_error, "\0");
	free(v_stri);
	return (ck_error);
}

/**
 * error_exit_shell - generic error sms for the exit in get_exit
 * @shinfo: data relevant (counter, arguments)
 *
 * Return: Error for sms
 */
char *error_exit_shell(shell_info *shinfo)
{
	int lengths;
	char *ck_error;
	char *v_stri;

	v_stri = tha_itoa(shinfo->counter);
	lengths = _strlen(shinfo->av[0]) + _strlen(v_stri);
	lengths += _strlen(shinfo->args[0]) + _strlen(shinfo->args[1]) + 23;
	ck_error = malloc(sizeof(char) * (lengths + 1));
	if (ck_error == 0)
	{
		free(v_stri);
		return (NULL);
	}
	_strcpy(ck_error, shinfo->av[0]);
	_strcat(ck_error, ": ");
	_strcat(ck_error, v_stri);
	_strcat(ck_error, ": ");
	_strcat(ck_error, shinfo->args[0]);
	_strcat(ck_error, ": Illegal number: ");
	_strcat(ck_error, shinfo->args[1]);
	_strcat(ck_error, "\n\0");
	free(v_stri);

	return (ck_error);
}
