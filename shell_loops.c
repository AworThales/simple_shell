#include "main.h"

/**
 * without_comment - deletes comments from input
 *
 * @in: input string
 * Return: input without the comments
 */
char *without_comment(char *in)
{
	int a, reach;

	reach = 0;
	for (a = 0; in[a]; a++)
	{
		if (in[a] == '#')
		{
			if (a == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[a - 1] == ' ' || in[a - 1] == '\t' || in[a - 1] == ';')
				reach = a;
		}
	}

	if (reach != 0)
	{
		in = _realloc(in, a, reach + 1);
		in[reach] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of the shell
 * @shinfo: data relevants (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(shell_info *shinfo)
{
	int loops, i_eof;
	char *input;

	loops = 1;
	while (loops == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(shinfo, input) == 1)
			{
				shinfo->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, shinfo);
			loops = split_commands(shinfo, input);
			shinfo->counter += 1;
			free(input);
		}
		else
		{
			loops = 0;
			free(input);
		}
	}
}

