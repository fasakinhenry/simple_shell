#include "main.h"

/**
 * _strtok - Custom strtok function
 * @str: String to be tokenized
 * @delim: Delimiter characters
 *
 * Return: Pointer to the next token or NULL if there are no more tokens
 */

char *_strtok(char *str, const char *delim)
{
	char *last = NULL;
	char *token;

	if (str != NULL)
		last = str;

	if (last == NULL || *last == '\0')
		return (NULL);

	token = last;

	while (*last != '\0' && !strchr(delim, *last))
		last++;

	if (*last != '\0')
		*last++ = '\0';

	return (token);
}
