#include "main.h"

/**
 * _getline - Reads input from a stream
 * @linept: A buffer for input
 * @n: The size of the pointer
 * @stream: The stream
 *
 * Return: number of bytes read
 */
ssize_t _getline(char **linept, size_t *n, FILE *stream);

ssize_t _getline(char **linept, size_t *n, FILE *stream)
{
	size_t pos = 0;
	int c;
	char *temp = NULL;

	if (linept == NULL || n == NULL || stream == NULL)
	{
		return (-1);
	}

	/* allocate size and resize if necessary */
	if (*linept == NULL && *n == 0)
	{
		*n = 128;
		*linept = (char *)malloc(*n);
		if (*linept == NULL)
		{
			return (-1);
		}
	}

	while (read(STDIN_FILENO, &c, 1) == 1 && c != '\n')
	{
		/* resize buffer */
		if (pos >= *n - 1)
		{
			*n = *n * 2;
			temp = (char *)malloc(*n);
			if (temp == NULL)
			{
				free(*linept);
				return (-1);
			}

			/* copy existing data to new buffer */
			write(STDOUT_FILENO, *linept, *n);

			/* free old buffer */
			free(*linept);

			*linept = temp;
		}
		(*linept)[pos++] = (char)c;
	}

	if (c == EOF && pos == 0)
	{
		return (-1);
	}

	(*linept)[pos] = '\0';
	return (pos);
}
