#include "main.h"

/**
 * _strdup - duplicates the str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	size_t lent;
	char *latest;

	lent = _strlen(s);
	latest = malloc(sizeof(char) * (lent + 1));
	if (latest == NULL)
		return (NULL);
	_memcpy(latest, s, lent + 1);
	return (latest);
}

/**
 * _strlen - Returns the length of the string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int lent;

	for (lent = 0; s[lent] != 0; lent++)
	{
	}
	return (lent);
}

/**
 * cmp_chars - compare chars of the strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int ab, cd, ef;

	for (ab = 0, ef = 0; str[ab]; ab++)
	{
		for (cd = 0; delim[cd]; cd++)
		{
			if (str[ab] == delim[cd])
			{
				ef++;
				break;
			}
		}
	}
	if (ab == ef)
		return (1);
	return (0);
}

/**
 * _strtok - splits the string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	char *str_starts;
	static char *splitted, *str_end;
	unsigned int ab, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*Stores first address*/
		ab = _strlen(str);
		str_end = &str[ab]; /*Stores last address*/
	}
	str_starts = splitted;
	if (str_starts == str_end) /*Reaching the ends*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loops finding the next token*/
		if (splitted != str_starts)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for the null char*/
		for (ab = 0; delim[ab]; ab++)
		{
			if (*splitted == delim[ab])
			{
				*splitted = '\0';
				if (splitted == str_starts)
					str_starts++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_starts);
}

/**
 * _isdigit - defines if the string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in the other case.
 */
int _isdigit(const char *s)
{
	unsigned int ab;

	for (ab = 0; s[ab]; ab++)
	{
		if (s[ab] < 48 || s[ab] > 57)
			return (0);
	}
	return (1);
}
