#include "main.h"

/**
 * add_rvar_node - adds the variable at the end
 * of the r_var_l list.
 * @head: head of a linked list.
 * @lvar: length of a variable.
 * @val: value of a variable.
 * @lval: length of a value.
 * Return: address of a head.
 */
r_var_l *add_rvar_node(r_var_l **head, int lvar, char *val, int lval)
{
	r_var_l *new, *temp;

	new = malloc(sizeof(r_var_l));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_rvar_list - frees the r_var_l list
 * @head: head of a linked list.
 * Return: no return.
 */
void free_rvar_list(r_var_l **head)
{
	r_var_l *temp;
	r_var_l *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
