#include "main.h"

/**
 * read_line - reads the inputs of string.
 *
 * @i_eof: return value of the getline function
 * Return: inputs string
 */
char *read_line(int *i_eof)
{
	char *inputs = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&inputs, &bufsize, stdin);

	return (inputs);
}
