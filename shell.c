#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INITIAL_BUFFER_SIZE 1024

char *_strcpy(char *dest, const char *src)
{
	char *ptr = dest;
	if (dest == NULL || src == NULL)
		return NULL;
	while ((*dest++ = *src++))
		;
	return ptr;
}

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t bufsize = 0;
	ssize_t chars_read = 0;
	int c;
	if (lineptr == NULL || n == NULL)
		return -1;

	if (*lineptr == NULL || *n == 0)
	{
		bufsize = INITIAL_BUFFER_SIZE;
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
			char *temp = realloc(*lineptr, bufsize + INITIAL_BUFFER_SIZE);

			if (temp == NULL)
			{
				perror("Failed to reallocate memory");
				exit(EXIT_FAILURE);
			}

			*lineptr = temp;
			*n += INITIAL_BUFFER_SIZE;
		}

		if (c == '\n')
			break;
	}

	if (chars_read == 0)
		return 0;

	(*lineptr)[chars_read] = '\0';
	return chars_read;
}

void display_prompt()
{
	write(STDOUT_FILENO, "$ ", 2);
}

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

	return args;
}

char **get_input(void)
{
	ssize_t response;
	size_t arg_count = 0, len = 0;
	char *input = NULL, **args = NULL;

	response = _getline(&input, &len, stdin);

	if (response == -1)
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

int main()
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

	return 0;
}
