#include <stdio.h>
#include "main.h"

/**
 * cd_shell - a function that changes current directory in shell
 * @datash: data
 * Return: 1 - success
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int myhome, myhome2, myddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		myhome = _strcmp("$HOME", dir);
		myhome2 = _strcmp("~", dir);
		myddash = _strcmp("--", dir);
	}

	if (dir == NULL || !myhome || !myhome2 || !myddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
