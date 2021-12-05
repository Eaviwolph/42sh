#include "builtin.h"

int my_exec(char *argv[], size_t len)
{
    if (len == 0)
        return 0;
    if (execvp(argv[0], argv + 1) == -1)
        errx(127, "42sh: exec: %s", strerror(errno));
    return 0;
}