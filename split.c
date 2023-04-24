#include "main.h"

/**
 * swap_char - swaps | and & for the non-printed chars
 *
 * @input: input string
 * @bool: type of the swap
 * Return: swapped string
 */
char *swap_char(char *input, int bool)
{
	int a;

	if (bool == 0)
	{
		for (a = 0; input[a]; a++)
		{
			if (input[a] == '|')
			{
				if (input[a + 1] != '|')
					input[a] = 16;
				else
					a++;
			}

			if (input[a] == '&')
			{
				if (input[a + 1] != '&')
					input[a] = 12;
				else
					a++;
			}
		}
	}
	else
	{
		for (a = 0; input[a]; a++)
		{
			input[a] = (input[a] == 16 ? '|' : input[a]);
			input[a] = (input[a] == 12 ? '&' : input[a]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command lines in lists
 *
 * @head_s: head of the separator list
 * @head_l: head of the command lines list
 * @input: input string
 * Return: no return
 */
void add_nodes(second_list **head_s, draw_list **head_l, char *input)
{
	int a;
	char *line;

	input = swap_char(input, 0);

	for (a = 0; input[a]; a++)
	{
		if (input[a] == ';')
			add_sep_node_end(head_s, input[a]);

		if (input[a] == '|' || input[a] == '&')
		{
			add_sep_node_end(head_s, input[a]);
			a++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * go_next - go to next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @shinfo: data structure
 * Return: no return
 */
void go_next(second_list **list_s, draw_list **list_l, shell_info *shinfo)
{
	int loop_sep;
	second_list *ls_s;
	draw_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shinfo->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @shinfo: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int split_commands(shell_info *shinfo, char *input)
{

	second_list *head_s, *list_s;
	draw_list *head_l, *list_l;
	int run;

	head_s = NULL;
	head_l = NULL;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shinfo->input = list_l->line;
		shinfo->args = split_line(shinfo->input);
		run = exec_line(shinfo);
		free(shinfo->args);

		if (run == 0)
			break;

		go_next(&list_s, &list_l, shinfo);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	if (run == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenize this input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t a;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (a = 1; token != NULL; a++)
	{
		if (a == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, a, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[a] = token;
	}

	return (tokens);
}
