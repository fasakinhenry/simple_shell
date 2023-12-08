#include "main.h"
/**
 * _strcmp - compare string values
 * @str1: input value
 * @str2: input value
 *
 * Return: str[j] - str2[j]
 */
int _strcmp(char *str1, char *str2)
{
	int j;

	j = 0;
	while (str1[j] != '\0' && str2[j] != '\0')
	{
		if (str1[j] != str2[j])
		{
			return (str1[j] - str2[j]);
		}
		j++;
	}
	return (0);
}
