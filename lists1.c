#include <stdio.h>
#include "main.h"

/**
 * add_rvar_node - a function that puts a variable at the end of a r_var list
 * @head: head of a linked list
 * @lvar: length of a variable
 * @val: value of ta variable.
 * @lval: length of a value.
 * Return: head address
 */
void add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *temp;

	new = malloc(sizeof(r_var));
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
 * free_rvar_list - a func that frees a r_var list
 * @head: head of a linked list
 * Return: none
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *curr;

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
