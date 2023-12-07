#include "main.h"

/**
 * _strcpy - a function that copys a string.
 * @dest: the destination for the copied str.
 * @src: the soucrce string.
 * Return: a pointer to the string.
 */

char *_strcpy(char *dest, const char *src)
{
	char *ptr = dest;

	if (dest == NULL || src == NULL)
		return (NULL);
	while ((*dest++ = *src++))
		;
	return (ptr);
}
