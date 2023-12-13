#include "main.h"

/**
 * _strlen - returns the length of a string
 * @str: string
 * Return: length
 */
int _strlen(char *str)
{
	int str_len = 0;

	while (*str != '\0')
	{
		str_len++;
		str++;
	}

	return (str_len);
}
