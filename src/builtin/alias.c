#include <err.h>
#include <string.h>

#include "../shell/shell.h"
#include "../tools/tools.h"

static int index_of(char *s, char c)
{
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == c)
            return i;
    }
    return -1;
}

static int isreserved(char *str)
{
    if (strcmp("while", str) == 0 || strcmp("then", str) == 0
        || strcmp("until", str) == 0 || strcmp("in", str) == 0
        || strcmp("if", str) == 0 || strcmp("for", str) == 0
        || strcmp("fi", str) == 0 || strcmp("esac", str) == 0
        || strcmp("else", str) == 0 || strcmp("elif", str) == 0
        || strcmp("done", str) == 0 || strcmp("case", str) == 0
        || strcmp("do", str) == 0 || strcmp("{", str) == 0
        || strcmp("}", str) == 0 || strcmp("!", str) == 0)
    {
        return 1;
    }
    return 0;
}

int alias(int argc, char **argv, struct shell *s)
{
    int ret = 0;
    if (argc == 1)
    {
        dalias_print(s->alias);
    }
    for (int c = 1; c < argc; c++)
    {
        int i = index_of(argv[c], '=');
        if (i == 0)
        {
            warnx("alias: %s not found", argv[c]);
            ret = 1;
        }
        else if (i == -1)
        {
            char *var = dalias_find(s->alias, argv[c]);
            if (var)
            {
                printf("%s\n", var);
            }
            else
            {
                warn("alias: %s not found", argv[c]);
                ret = 1;
            }
        }
        else
        {
            int index = index_of(argv[c], '=');
            argv[c][index] = '\0';
            if (!isreserved(argv[c]))
            {
                dalias_add_alias(s->alias, mystrdup(argv[c]),
                                 mystrdup(argv[c] + index + 1));
            }
        }
    }
    return ret;
}

int unalias(int argc, char **argv, struct shell *s)
{
    int ret = 0;
    for (int i = 1; i < argc; i++)
    {
        if (!dalias_remove_bname(s->alias, argv[i]))
        {
            warnx("unalias: %s not found", argv[i]);
            ret = 1;
        }
    }
    return ret;
}