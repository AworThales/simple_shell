#include "main.h"

/**
 * bring_line - assigns the line var for the get_line
 * @lineptr: Buffer that store input str
 * @buffer: str which is been called to line
 * @n: size of the line
 * @j: size of the buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read input from the stream
 * @lineptr: buffer that stores input
 * @n: size of the lineptr
 * @stream: stream to the read from
 * Return: The number of the bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t retval;
	char a = 'z';
	char *buffer;
	int b;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (a != '\n')
	{
		b = read(STDIN_FILENO, &a, 1);
		if (b == -1 || (b == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (b == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = a;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (b != 0)
		input = 0;
	return (retval);
}
