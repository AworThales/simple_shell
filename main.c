#include "main.h"

/**
 * free_data - the frees data structure
 *
 * @shinfo: the data structure
 * Return: no return
 */
void free_data(shell_info *shinfo)
{
	unsigned int i;

	for (i = 0; shinfo->_environ[i]; i++)
	{
		free(shinfo->_environ[i]);
	}

	free(shinfo->_environ);
	free(shinfo->pid);
}

/**
 * set_data - Initialize the data structure
 *
 * @shinfo: the data structure
 * @av: the argument vector
 * Return: no return
 */
void set_data(shell_info *shinfo, char **av)
{
	unsigned int i;

	shinfo->av = av;
	shinfo->input = NULL;
	shinfo->args = NULL;
	shinfo->status = 0;
	shinfo->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	shinfo->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shinfo->_environ[i] = _strdup(environ[i]);
	}

	shinfo->_environ[i] = NULL;
	shinfo->pid = tha_itoa(getpid());
}

/**
 * main - Entry of point
 *
 * @ac: the argument count
 * @av: the argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shell_info shinfo;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&shinfo, av);
	shell_loop(&shinfo);
	free_data(&shinfo);
	if (shinfo.status < 0)
		return (255);
	return (shinfo.status);
}
