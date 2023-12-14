#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

extern char **environ;

#define MAX_ARG 64
#define INITIAL_BUFFER_SIZE 1024
#define MAX_LINE 256
char *_strtok(char *str, const char *delim);
char *_strcpy(char *dest, char *src);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char **parse_input(char *input, size_t *arg_count);
char **get_input(void);
int _strlen(char *c);
char *_strcat(char *dest, char *src);
void display_prompt(void);
char *_strtok(char *str, const char *delim);
int _strcmp(char *str1, char *str2);
char *locate_cmd(char *cmd);
void execute(char **argv);
int print_environment(void);
#endif
