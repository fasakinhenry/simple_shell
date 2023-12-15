#include "main.h"

#define READSIZE 2048
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
	static char buffer[READSIZE];
	static size_t buffer_pos = 0;
	static size_t buffer_size = 0;
	size_t pos = 0;
	int c;
	/*char *temp = NULL;*/

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

	while (1)
	{

		/* resize buffer */
		if (buffer_pos >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, READSIZE);
			buffer_pos = 0;

			if (buffer_size == 0)
			{
				if (pos == 0)
					return (-1);
				break;
			}
			else if (buffer_size <= 0)
				return (-1);
		}

		c = buffer[buffer_pos++];

		if (c == '\n' || c == EOF)
		{
			break;
		}

		/* resize buffer if necessary */
		if (pos >= *n - 1)
		{
			*n = *n * 2;
			*linept = (char *)realloc(*linept, *n);
			if (*linept == NULL)
			{
				return (-1);
			}
		}
		(*linept)[pos++] = (char)c;
	}
	(*linept)[pos] = '\0';
	return (pos);
}
