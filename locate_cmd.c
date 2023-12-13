#include "main.h"
/**
 * locate_cmd - a function that locates cmd in the enviroment path.
 * @cmd: a pointer to the command.
 * Return: A pointer to the value of cmd or NULL
 */

char *locate_cmd(char *cmd);
char *locate_cmd(char *cmd)
{
	char *path = NULL, *path_cpy = NULL, *path_token = NULL, *file_path = NULL;
	int command_len = 0, directory_len = 0;
	struct stat buffer;

	/* find var names from env list */
	path = getenv("PATH");

	if (!path)
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
		command_len = strlen(cmd);

		/* break down the path_cpy var int toks */
		path_token = strtok(path_cpy, ":");
		while (path_token != NULL)
		{
			/* get dir_len */
			directory_len = _strlen(path_token);
			/* alloc mem for storing the cmd name together with the dir_name */
			file_path = malloc(command_len + directory_len + 2);
			if (!file_path)
			{
				perror("malloc failed");
				return (NULL);
			}
			file_path[command_len + directory_len + 1] = '\0';
			/*construct full file path */

			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);

			/* test if the filepath exist and return it */
			if (stat(file_path, &buffer) == 0)
			{
				return (file_path);
			}

			free(file_path);

			path_token = strtok(NULL, ":");
		}

		/*free(file_path);*/
		if (stat(cmd, &buffer) == 0)
		{
			return (strdup(cmd));
		}
	}
	return (NULL);
}
