#include "builtin.h"

void my_exit(char *arg[], size_t len)
{
    (void)len;
    char *end;
    long status = strtol(arg[0], &end, 10);
    if (*end)
        fprintf(stderr, "42sh: exit(%s): only numeric argument !\n", arg[0]);
    _exit((!*end) ? status : 255);
}