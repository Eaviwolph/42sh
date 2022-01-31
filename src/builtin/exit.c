#include "builtin.h"

int my_exit(char *arg[], size_t len, struct shell *s)
{
    if (len == 1)
        exit(atoi(dvar_find(s->var, "?")));
    char *end;
    long status = strtol(arg[1], &end, 10);
    if (*end)
        fprintf(stderr, "42sh: exit(%s): only numeric argument !\n", arg[0]);
    _exit((!*end) ? status : 255);
    return 1;
}