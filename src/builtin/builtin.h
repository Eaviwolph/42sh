#ifndef BUILTIN_H
#define BUILTIN_H

#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../shell/shell.h"
#define PATH_MAX 4096

int my_echo(char *arg[], size_t len);
int my_exit(char *arg[], size_t len, struct shell *s);
int my_cd(char *arg[], size_t len);
int my_export(char *arg[], size_t len);
int my_dot(char *argv[], size_t len);
int alias(int argc, char **argv, struct shell *s);
int unalias(int argc, char **argv, struct shell *s);
int unset(int argc, char *argv[], struct shell *s);

#endif
