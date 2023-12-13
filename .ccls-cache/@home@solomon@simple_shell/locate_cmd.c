#include "main.h"
/**
 * locate_cmd - a function that locates cmd in the enviroment path.
 * @cmd: a pointer to the command.
 * Return: A pointer to the value of cmd or NULL
 */

char *locate_cmd(char *cmd);
char *locate_cmd(char *cmd)
{
	char *path, *path_cpy, *path_token, *file_path = NULL;
	int command_len, directory_len;
	struct stat buffer;

	/* find var names from env list */
	path = getenv("PATH");

	if (path == NULL)
	{
		perror("getenv failure");
		return (NULL);
	}

	/* create a copy of path */
	if (path)
	{
		path_cpy = strdup(path);
		if (path_cpy == NULL)
		{
			perror("strdup failure.");
			return (NULL);
		}

		/* get the length of the command */
		command_len = _strlen(cmd);

		/* break down the path_cpy var int toks */
		path_token = _strtok(path_cpy, ":");
		while (path_token != NULL)
		{
			/* get dir_len */
			directory_len = _strlen(path_token);
			/* alloc mem for storing the cmd name together with the dir_name */
			file_path = malloc(command_len + directory_len + 2);
			if (file_path == NULL)
			{
				perror("malloc failed");
				free(path_cpy);
				return (NULL);
			}
			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);
			_strcat(file_path, "\0");

			/* test if the filepath exist and return it */
			if (stat(file_path, &buffer) == 0)
			{
				free(path_cpy);
				free(file_path);
				return (file_path);
			}
			else
			{
				perror("stat failure");
				free(file_path);
			}
			path_token = _strtok(NULL, ":");
		}


		free(path_cpy);
		if (stat(cmd, &buffer) == 0)
		{
			return (strdup(cmd));
		}
		return (NULL);
	}
	return (NULL);
}
