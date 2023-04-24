#include "main.h"

/**
 * _strcat - concatenate the two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int ab;
	int cd;

	for (ab = 0; dest[ab] != '\0'; ab++)
		;

	for (cd = 0; src[cd] != '\0'; cd++)
	{
		dest[ab] = src[cd];
		ab++;
	}

	dest[ab] = '\0';
	return (dest);
}
/**
 * *_strcpy - Copies this string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t b;

	for (b = 0; src[b] != '\0'; b++)
	{
		dest[b] = src[b];
	}
	dest[b] = '\0';

	return (dest);
}
/**
 * _strcmp - Function which compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int ab;

	for (ab = 0; s1[ab] == s2[ab] && s1[ab]; ab++)
		;

	if (s1[ab] > s2[ab])
		return (1);
	if (s1[ab] < s2[ab])
		return (-1);
	return (0);
}
/**
 * _strchr - locates the character in b string,
 * @s: string.
 * @c: character.
 * Return: the pointer to b first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int ab = 0;

	for (; *(s + ab) != '\0'; ab++)
		if (*(s + ab) == c)
			return (s + ab);
	if (*(s + ab) == c)
		return (s + ab);
	return ('\0');
}
/**
 * _strspn - gets the length of the prefix substring.
 * @s: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
	int ab, cd, bool;

	for (ab = 0; *(s + ab) != '\0'; ab++)
	{
		bool = 1;
		for (cd = 0; *(accept + cd) != '\0'; cd++)
		{
			if (*(s + ab) == *(accept + cd))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (ab);
}
