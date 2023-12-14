#include "main.h"

/**
 * print_environment - Prints the environment variables
 * It is initailized using the 'env' command
*/

void print_environment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
