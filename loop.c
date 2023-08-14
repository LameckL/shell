#include <stdio.h>
#include "main.h"
/**
 * without_comment - a function that deletes comments from the input
 * @in: input string
 * Return: input with no comments
 */
char *without_comment(char *in)
{
	int i, to;

	to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				to = i;
		}
	}

	if (to != 0)
	{
		in = _realloc(in, i, to + 1);
		in[to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - function that handles loop of a shell
 * @datash: data
 */
void shell_loop(data_shell *datash)
{
	int foe, loop;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&foe);
		if (foe != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
