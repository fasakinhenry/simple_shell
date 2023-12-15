#include "main.h"

/**
 * print_environment - Prints the environment variables
 * Return: On success, Always o
 * -1 is returned on error
 * It is initailized using the 'env' command
 */

int print_environment(void)
{
	char **env_ptr = environ;

	while (*env_ptr)
	{
		size_t len = 0;

		while ((*env_ptr)[len])
			len++;

		write(STDOUT_FILENO, *env_ptr, len);
		write(STDOUT_FILENO, "\n", 1);

		env_ptr++;
	}

	return (0);
}
