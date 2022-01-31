#include <err.h>
#include <string.h>

#include "../shell/shell.h"
#include "../tools/tools.h"

int unset(int argc, char *argv[], struct shell *s)
{
    for (int c = 1; c < argc; c++)
    {
        dvar_add_var(s->var, mystrdup(argv[c]), mystrdup(""));
    }
    return 0;
}