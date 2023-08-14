#include <stdio.h>
#include "main.h"

/**
 * exit_shell - a function that exits a shell
 * @datash: data; args and status
 * Return: 0 - success
 */
int exit_shell(data_shell *datash)
{
	unsigned int ustatus;
	int num;
	int number;
	int str_len;

	if (datash->args[1] != NULL)
	{
		ustatus = _atoi(datash->args[1]);
		num = _isdigit(datash->args[1]);
		str_len = _strlen(datash->args[1]);
		number = ustatus > (unsigned int)INT_MAX;
		if (!num || str_len > 10 || number)
		{
			get_error(datash, 2);
			datash->status = 2;
			return (1);
		}
		datash->status = (ustatus % 256);
	}
	return (0);
}
