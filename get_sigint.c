#include "main.h"

/**
 * get_sigint - Handle the crtl + c call in the prompt
 * @signal: Signal for handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
