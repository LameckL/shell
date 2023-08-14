#include <stdio.h>
#include "main.h"

/**
 * _memcpy - a func that copies info between void pointers
 * @newptr: pointer to
 * @ptr:  pointer from
 * @size: size of the new pointer
 * Return: none
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc -  a func that reallocates memory block
 * @ptr: pointer to the previously allocated memory
 * @old_size: size of the space allocated of pointer
 * @new_size: new size of the new memory block
 * Return: ptr - if new_size == old_size, returns ptr n changes. Return NULL - fail
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
 * _reallocdp - a func that reallocates a memory block of a double pointer
 * @ptr: double pointer to the previously allocated memory
 * @old_size: size of the space allocated
 * @new_size: new size of the new memory block
 * Return: ptr - if new_size == old_size, returns ptr n changes. Return NULL - fail
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
