#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <unistd.h>

enum error
{
    ERROR_RED = 1, // redirection error
    ERROR_PARSE = 2, // parser or lex error
    ERROR_MEM = 42, // no memory left
    ERROR_FORK = 128, // error in fork
    ERROR_PIPE = 128, // error in pipe
};
#define secmalloc(name, size)                                                  \
    if (!(name = malloc(size)))                                                \
    exit(ERROR_MEM)
#define secrealloc(ret, name, size)                                            \
    if (!(ret = realloc(name, size)))                                          \
    exit(ERROR_MEM)
#define secstrdup(ret, str)                                                    \
    if (!(ret = strdup(str)))                                                  \
    exit(ERROR_MEM)

#define isinteractive() (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))

#endif