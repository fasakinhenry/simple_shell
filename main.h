#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

#define INITIAL_BUFFER_SIZE 1024
#define MAX_LINE 256
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, const char *src);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **parse_input(char *input, size_t *arg_count);
char **get_input(void);
void display_prompt(void);
char *_strtok(char *str, const char *delim);

#endif
