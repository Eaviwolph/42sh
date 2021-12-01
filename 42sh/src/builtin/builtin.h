#ifndef BUILTIN_H
#define BUILTIN_H

#include <ctype.h>
#include <err.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void my_echo(char *arg[], size_t len);
void my_exit(char *arg[], size_t len);
void my_cd(char *arg[], size_t len);

#endif