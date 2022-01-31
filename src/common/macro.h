#ifndef MACRO_H
#define MACRO_H

#include <stdlib.h>
#include <unistd.h>

enum error
{
    ERROR_ONREDIRECTION = 1, // redirection error
    ERROR_ONPARSING = 2, // parser or lex error
    ERROR_ONMALLOC = 3, // no memory left
    ERROR_ONFORKPROC = 4, // error in fork
    ERROR_ONPIPELINK = 5, // error in pipe
};
enum prompt {
  TYPEIN_PS1 = 1,
  TYPEIN_PS2 = 2,
  TYPEIN_PS4 = 4
};

#define safe_malloc(varname, size)                                                  \
    if (!(varname = malloc(size)))                                                \
    exit(ERROR_ONMALLOC)
#define safe_calloc(varname, count, size)                                                  \
    if (!(varname = calloc(count, size)))                                                \
    exit(ERROR_ONMALLOC)
#define safe_realloc(newname, oldname, size)                                            \
    if (!(newname = realloc(oldname, size)))                                          \
    exit(ERROR_ONMALLOC)
#define safe_strdup(new, old)                                                    \
    if (!(new = strdup(old)))                                                  \
    exit(ERROR_ONMALLOC)

#define is_valid_fd() (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))

#endif