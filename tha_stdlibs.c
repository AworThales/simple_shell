#include "main.h"

/**
 * get_len - Get lenghts of a number.
 * @n: type of int number.
 * Return: Lenght of number.
 */
int get_len(int n)
{
	unsigned int num1;
	int lenghts = 1;

	if (n < 0)
	{
		lenghts++;
		num1 = n * -1;
	}
	else
	{
		num1 = n;
	}
	while (num1 > 9)
	{
		lenghts++;
		num1 = num1 / 10;
	}

	return (lenghts);
}
/**
 * tha_itoa - function that converts int to string.
 * @n: type of int number
 * Return: String.
 */
char *tha_itoa(int n)
{
	unsigned int num1;
	int lenghts = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenghts + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenghts) = '\0';

	if (n < 0)
	{
		num1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = n;
	}

	lenghts--;
	do {
		*(buffer + lenghts) = (num1 % 10) + '0';
		num1 = num1 / 10;
		lenghts--;
	}
	while (num1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pins = 1, mes = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pins *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				mes *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * mes);
		mes /= 10;
	}
	return (oi * pins);
}
