#include "main.h"

#define MAX_ARG 64

/**
<<<<<<< HEAD
 * _strcpy - custom strcpy function
 * @dest: The destination pointer
 * @src: The source pointer
*/
char *_strcpy(char *dest, const char *src)
{
	char *ptr = dest;
	if (dest == NULL || src == NULL)
		return NULL;
	while ((*dest++ = *src++))
		;
	return ptr;
}

/**
 * _getline - Custom getline function to handle user input
 * @lineptr: Pointer which points to the line
 * @n: 
 * 
*/
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
=======
 * main - function that serves as a custom unix-like shell.
 * Return: returns 0 on success.
 */

int main(void);
int main(void)
{
	/* char input[MAX_INPUT]; */
>>>>>>> 2852ef17d72f6092750f415cc71e629a8000846a

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
