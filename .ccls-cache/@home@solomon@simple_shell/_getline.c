#include "main.h"
/**
 * _getline - function that reads chars from a stream
 * @linept: an array of pointers
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
	/* allocate size and resize if neccessary. */

	if (*linept == NULL && *n == 0)
	{
		*n = 128;
		*linept = (char *)malloc(*n);
		if (linept == NULL)
		{
			return (-1);
		}
	}
	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		/* resize buffer */

		if (pos >= *n - 1)
		{
			*n = *n * 2;
			temp = (char *)malloc(*n * 2);
			if (temp == NULL)
			{
				return (-1);
			}
			/*copy existing data to new buffer */
			memcpy(temp, *linept, *n);
			/*free old buffer */
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
