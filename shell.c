#include "main.h"

/**
 * _strcpy - Copies a string
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
    char *ptr = dest;

    if (dest == NULL || src == NULL)
        return NULL;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';  /* Null-terminate the destination string */
    return ptr;
}

/**
 * _getline - custom getline function
 * @lineptr: pointer to the buffer storing the line
 * @n: pointer to the size of the buffer
 * @stream: input stream
 *
 * Return: the number of characters read (including newline),
 * or -1 on failure, 0 on EOF
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t bufsize = 0;
	int c;
	ssize_t chars_read = 0;

	if (lineptr == NULL || n == NULL)
	{
		return -1;
	}

	if (*lineptr == NULL || *n == 0)
	{
		bufsize = 120; /* Initial buffer size, adjust as needed */
		*lineptr = malloc(bufsize);

		if (*lineptr == NULL)
		{
			perror("Failed to allocate memory");
			exit(EXIT_FAILURE);
		}

		*n = bufsize;
	}

	while ((c = fgetc(stream)) != EOF)
	{
		(*lineptr)[chars_read++] = (char)c;

		if (chars_read == (ssize_t)(*n - 1))
		{
			bufsize += 120; /* Adjust as needed */
			*lineptr = realloc(*lineptr, bufsize);

			if (*lineptr == NULL)
			{
				perror("Failed to reallocate memory");
				exit(EXIT_FAILURE);
			}

			*n = bufsize;
		}

		if (c == '\n')
		{
			break;
		}
	}

	if (chars_read == 0)
	{
		return 0; /* EOF */
	}

	(*lineptr)[chars_read] = '\0';

	return chars_read;
}

void display_prompt();
char **get_input();

int main()
{
	char **args;
	pid_t pid;
	int status;

	while (1)
	{
		display_prompt();

		args = get_input();

		if (args == NULL)
		{
			continue;
		}

		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		pid = fork();

		if (pid == -1)
		{
			perror("Fork failed");
			free(args);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (access(args[0], X_OK) == 0)
			{
				if (execve(args[0], args, NULL) == -1)
				{
					perror("Error");
					free(args);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fprintf(stderr, "Command not found\n");
				free(args);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{
			}
			else
			{
				fprintf(stderr, "Command execution failed\n");
			}

			free(args);
		}
	}

	return 0;
}

void display_prompt()
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * parse_input - This handles the cd command and conditio	ns
 * @input: the input to be parsed
 * @arg_count: Number of arguments passed
 *
 * Return: on success, 0
 * else -1 is returned and the errno is set appropriately
 */

char **parse_input(char *input, size_t *arg_count)
{
	char **args = NULL;
	char *token = _strtok(input, " \n");

	while (token != NULL)
	{
		char **temp = realloc(args, (*arg_count + 1) * sizeof(char *));

		if (temp == NULL)
		{
			perror("bash: realloc");
			exit(EXIT_FAILURE);
		}

		args = temp;
		args[*arg_count] = malloc(strlen(token) + 1);

		if (args[*arg_count] == NULL)
		{
			perror("bash: malloc:");
			exit(EXIT_FAILURE);
		}

		_strcpy(args[*arg_count], token);
		(*arg_count)++;
		token = _strtok(NULL, " \n");
	}

	return (args);
}

char **get_input(void)
{
	ssize_t response;
	size_t arg_count = 0, len = 0;
	char *input = NULL, **args = NULL;

	/* write(STDOUT_FILENO, "$ ", 2); */
	response = _getline(&input, &len, stdin);

	if (response == (ssize_t)-1)
	{
		free(input);
		exit(EXIT_FAILURE);
	}
	else if (response == 0)
	{
		free(input);
		exit(EXIT_SUCCESS);
	}

	args = parse_input(input, &arg_count);

	free(input);

	return args;
}
