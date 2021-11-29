#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void my_exit(char *s)
{
    char *end;
    long status = strtol(s, &end, 10);
    if (*end)
        fprintf(stderr, "42sh: exit(%s): only numeric argument !\n", s);
    _exit((!*end) ? status : 255);
}