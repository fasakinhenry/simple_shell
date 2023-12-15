#include "main.h"

#define MAX_ARG 64

/**
 * main - function that serves as a custom unix-like shell.
 * Return: returns 0 on success.
 */

int main(void);
int main(void)
{
	/* char input[MAX_INPUT]; */

	while (1)
	{
		/* variable declarations */
		pid_t pid;
		char *line = NULL;
		size_t n = 0;
		ssize_t char_read;
		char *argv[MAX_ARG];
		char *token = NULL;
		int status, i = 0;

		/* read user input and check if nothing was read */

		/*check if shell is in interactive mode */
		if (isatty(STDIN_FILENO) == 1)
			display_prompt();

		char_read = _getline(&line, &n, stdin);
		if (char_read == -1)
		{
			perror("error.\n");
			free(line);
			exit(EXIT_FAILURE);
		}

		token = _strtok(line, " \t\n");
		while (token != NULL && i < MAX_ARG - 1)
		{
			argv[i] = token;
			token = _strtok(NULL, "  \t\n");
			i++;
		}
		argv[i] = NULL;
		/* exit the shell if user enters exit */
		if (_strcmp(argv[0], "exit") == 0)
			break;
		else if (_strcmp(argv[0], "env") == 0)
		{
			print_environment();
			continue;
		}
		/* fork a child process and check if fork was successful */
		pid = fork();

		if (pid == -1)
		{
			perror("fork failure.\n");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			/* execute command */
			execute(argv);
		}
		else
		{
			/* parent process */
			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid failure.\n");
				free(line);
				exit(EXIT_FAILURE);
			}
		}
		free(line);
	}

	return (0);
}
