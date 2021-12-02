#include "builtin.h"

void my_export(char *arg[], size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        char *tmp = arg[i];
        char *token = strtok_r(tmp, "=", &tmp);
        setenv(token, tmp, !0);
        i++;
    }
}