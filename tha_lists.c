#include "main.h"

/**
 * add_sep_node_end - adds the separator found at end
 * of a second_list.
 * @head: head of a linked list.
 * @sep: separator found (; | &).
 * Return: address of a head.
 */
second_list *add_sep_node_end(second_list **head, char sep)
{
	second_list *new, *temp;

	new = malloc(sizeof(second_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * free_sep_list - frees the second_list
 * @head: head of a linked list.
 * Return: no return.
 */
void free_sep_list(second_list **head)
{
	second_list *temp;
	second_list *curr;

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

/**
 * add_line_node_end - adds the command line at a end
 * of a draw_list.
 * @head: head of a linked list.
 * @line: command line.
 * Return: address of a head.
 */
draw_list *add_line_node_end(draw_list **head, char *line)
{
	draw_list *new, *temp;

	new = malloc(sizeof(draw_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
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
 * free_line_list - frees the draw_list
 * @head: head of a linked list.
 * Return: no return.
 */
void free_line_list(draw_list **head)
{
	draw_list *temp;
	draw_list *curr;

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
