#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>

#define MAX_LINE 256
#define INITIAL_BUFFER_SIZE 120
char *_strtok(char *str, const char *delim);

#endif
