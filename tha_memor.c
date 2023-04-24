#include "main.h"

/**
 * _memcpy - copies information between the void pointers.
 * @newptr: destination of pointer.
 * @ptr: source pointer.
 * @size: size of new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	unsigned int ab;
	char *char_newptr = (char *)newptr;
	char *char_ptr = (char *)ptr;

	for (ab = 0; ab < size; ab++)
		char_newptr[ab] = char_ptr[ab];
}

/**
 * _realloc - reallocates the memory block.
 * @ptr: pointer to memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in a bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdp - reallocates the memory block of the double pointer.
 * @ptr: double pointer to memory previously allocated.
 * @old_size: size, in a bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of a new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without the changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int ab;
	char **newptr;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (ab = 0; ab < old_size; ab++)
		newptr[ab] = ptr[ab];

	free(ptr);

	return (newptr);
}
