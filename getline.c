#include "main.h"
#define INITIAL_BUFFER_SIZE 1024
/**
 * _getline - a func that reads a line from stdin or a stream
 * @lineptr: a double ptr to a char set to the first char of the line
 * @n: a pointer set to the length of the line
 * @stream: a pointer to a file object.
 * Return: return no of chars read
 */


ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t bufsize = 0;
	ssize_t chars_read = 0;
	int c;

	if (lineptr == NULL || n == NULL)
		return (-1);

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
		return (0);

	(*lineptr)[chars_read] = '\0';
	return (chars_read);
}
