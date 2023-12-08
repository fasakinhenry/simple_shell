#include "main.h"

/**
 * main - a function that interpretes unix-like shell command
 * Return: returns 0 on success.
 */

int main(void);
int main(void)
{
	char **args;
	pid_t pid;
	int status;
	size_t i;

	while (1)
	{
		display_prompt();

		args = get_input();

		if (args == NULL)
			continue;

		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		if (_strcmp(*args, "exit") == 0)
			break;
		pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			free(args);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Error");
				free(args);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);

			if (!WIFEXITED(status))
			{
				fprintf(stderr, "Command execution failed\n");
			}

			for (i = 0; args[i] != NULL; i++)
			{
				free(args[i]);
			}
			free(args);
		}
	}

	return (0);
}
