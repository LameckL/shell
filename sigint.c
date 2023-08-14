#include "main.h"

/**
 * get_sigint - this func deals the crtl + c in prompt
 * @sig: signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
