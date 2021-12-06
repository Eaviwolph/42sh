#ifndef BUILTIN_H
#define BUILTIN_H

#include <ctype.h>
#include <err.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#define PATH_MAX 4096

int my_echo(char *arg[], size_t len);
int my_exit(char *arg[], size_t len);
int my_cd(char *arg[], size_t len);
int my_export(char *arg[], size_t len);
int my_exec(char *argv[], size_t len);

#endif
