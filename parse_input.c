#include "main.h"

/**
 * parse_input - a function that parses  input
 * @input: the input to be parsed.
 * @arg_count: the number of arguments.
 * Return: returns the arg.
 */

char **parse_input(char *input, size_t *arg_count)
{
	char **args = NULL;
	char *token = strtok(input, " \n");

	while (token != NULL)
	{
		args = realloc(args, (*arg_count + 1) * sizeof(char *));
		args[*arg_count] = strdup(token);
		(*arg_count)++;

		token = strtok(NULL, " \n");
	}

	args = realloc(args, (*arg_count + 1) * sizeof(char *));
	args[*arg_count] = NULL;

	return (args);
}
