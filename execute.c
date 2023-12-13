#include "main.h"

/**
 * execute - a function thats execute a shell program
 * @argv: var name
 * Return: void
 */
void execute(char **argv)
{
	char *cmd = NULL, *actual_cmd = NULL;

	if (argv && argv[0])
	{
		/* get the command */
		cmd = argv[0];

		/* generate the path to this command before passing it to execve */
		actual_cmd = locate_cmd(cmd);

		if (actual_cmd == NULL)
		{
			perror("command path not found");
			return;
		}

		/* execute the actual command with execve */
		if (execve(actual_cmd, argv, NULL) == -1)
		{
			perror("Error:");
			free(actual_cmd);
			return;
		}
		free(actual_cmd);
	}
}
