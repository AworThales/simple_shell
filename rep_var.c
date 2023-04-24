#include "main.h"

/**
 * check_env - checks if typed variable is of an env variable
 *
 * @h: head of the linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env(r_var_l **h, char *in, shell_info *data)
{
	char **_envr;
	int rows, check, c, lval;

	_envr = data->_environ;
	for (rows = 0; _envr[rows]; rows++)
	{
		for (c = 1, check = 0; _envr[rows][check]; check++)
		{
			if (_envr[rows][check] == '=')
			{
				lval = _strlen(_envr[rows] + check + 1);
				add_rvar_node(h, c, _envr[rows] + check + 1, lval);
				return;
			}

			if (in[c] == _envr[rows][check])
				c++;
			else
				break;
		}
	}

	for (c = 0; in[c]; c++)
	{
		if (in[c] == ' ' || in[c] == '\t' || in[c] == ';' || in[c] == '\n')
			break;
	}

	add_rvar_node(h, c, NULL, 0);
}

/**
 * check_vars - check if typed variable is $$ or $?
 *
 * @h: head of linked list
 * @in: input string
 * @st: last status of Shell
 * @data: data structure
 * Return: no return
 */
int check_vars(r_var_l **h, char *in, char *st, shell_info *data)
{
	int a, list, lpd;

	list = _strlen(st);
	lpd = _strlen(data->pid);

	for (a = 0; in[a]; a++)
	{
		if (in[a] == '$')
		{
			if (in[a + 1] == '?')
				add_rvar_node(h, 2, st, list), a++;
			else if (in[a + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), a++;
			else if (in[a + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[a + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + a, data);
		}
	}

	return (a);
}

/**
 * replaced_input - replaces string into the variables
 *
 * @head: head of linked list
 * @input: input string
 * @new_input: new input strings (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var_l **head, char *input, char *new_input, int nlen)
{
	r_var_l *indx;
	int a, c, b;

	indx = *head;
	for (c = a = 0; a < nlen; a++)
	{
		if (input[c] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[a] = input[c];
				c++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (b = 0; b < indx->len_var; b++)
					c++;
				a--;
			}
			else
			{
				for (b = 0; b < indx->len_val; b++)
				{
					new_input[a] = indx->val[b];
					a++;
				}
				c += (indx->len_var);
				a--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[a] = input[c];
			c++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into the vars
 *
 * @input: input the string
 * @shinfo: data structure
 * Return: replaced string
 */
char *rep_var(char *input, shell_info *shinfo)
{
	r_var_l *head, *indx;
	char *status, *new_input;
	int olength, nlen;

	status = tha_itoa(shinfo->status);
	head = NULL;

	olength = check_vars(&head, input, status, shinfo);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olength;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
