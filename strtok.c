#include "main.h"

/**
 * compare_char - function that compares a char with chars in a str
 * @s: the character used to compare
 * @str: the string being checked
 * Return: 1 if match or 0 if not same
 */

unsigned int compare_char(char s, const char *str)
{
	unsigned int j = 0;

	while (str[j] != '\0')
	{
		if (s == *str)
			return (1);
		j++;
	}

	return (0);
}

/**
 * _strtok - Custom strtok function
 * @str: String to be tokenized
 * @delim: Delimiter characters
 *
 * Return: Pointer to the next token or NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim);
char *_strtok(char *str, const char *delim)
{
	static char *last;
	static char *token;
	unsigned int i = 0;

	if (str != NULL)
		last = str;

	token = last;

	if (token == NULL)
		return (NULL);

	while (last[i] != '\0')
	{
		if (compare_char(last[i], delim) == 0)
			break;
		i++;
	}

	if (*last == '\0' || *last == '#')
	{
		*last = '\0';
		return (NULL);
	}

	token = last + i;
	last = token;

	i = 0;

	while (last[i] != '\0')
	{
		if (compare_char(last[i], delim) == 1)
			break;
		i++;
	}

	if (last[i] == '\0')
		last = NULL;
	else
	{
		last[i] = '\0';
		last = last + i + 1;
		if (*last == '\0')
			last = NULL;
	}
	return (token);
}
