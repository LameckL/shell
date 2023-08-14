#include <stdio.h>
#include "main.h"

/**
 * get_error - a function calling an error according the builtin, permission or syntax
 * @datash: data structure
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *datash, int eval)
{
	char *err;

	switch (eval)
	{
	case -1:
		err = err_env(datash);
		break;
	case 126:
		err = err_path_126(datash);
		break;
	case 127:
		err = err_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			err = err_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			err = err_get_cd(datash);
		break;
	}

	if (err)
	{
		write(STDERR_FILENO, err, _strlen(err));
		free(err);
	}

	datash->status = eval;
	return (eval);
}
