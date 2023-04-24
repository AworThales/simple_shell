#include "main.h"

/**
 * repeated_char - counts the repetition of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - finds the syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - finds index of  this first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when the syntax error is found
 *
 * @shinfo: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void print_syntax_error(shell_info *shinfo, char *input, int i, int bool)
{
	char *msg, *msg_one, *msg_two, *error, *counter;
	int lent;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg_one = ": Syntax error: \"";
	msg_two = "\" unexpected\n";
	counter = tha_itoa(shinfo->counter);
	lent = _strlen(shinfo->av[0]) + _strlen(counter);
	lent += _strlen(msg) + _strlen(msg_one) + _strlen(msg_two) + 2;

	error = malloc(sizeof(char) * (lent + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, shinfo->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg_one);
	_strcat(error, msg);
	_strcat(error, msg_two);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, lent);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate the function to
 * find and print a syntax error
 *
 * @shinfo: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(shell_info *shinfo, char *input)
{
	int d_char = 0;
	int begin = 0;
	int i = 0;

	d_char = first_char(input, &begin);
	if (d_char == -1)
	{
		print_syntax_error(shinfo, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_error(shinfo, input, begin + i, 1);
		return (1);
	}

	return (0);
}
