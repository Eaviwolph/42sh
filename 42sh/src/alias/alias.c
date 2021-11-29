#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dalias.h"

static char *get_fnprintf(char *s, int j, int i, struct dalias *alias)
{
    char *name = calloc(j - i + 1, sizeof(char));
    for (int k = 0; k < j - i; k++)
    {
        name[k] = s[i + k];
    }
    char *val = dalias_find(alias, name);
    free(name);
    if (!val)
    {
        return NULL;
    }
    int slen = strlen(s);
    int vlen = strlen(val);
    int flen = vlen + i + (slen - j + 1);
    char *final = calloc(flen, sizeof(char));
    snprintf(final, flen, "%.*s%s%.*s", i, s, val, slen - j, s + j);
    return final;
}

static int newchar(char *s, int j, int *i, char *t)
{
    int len = strlen(s);
    int len2 = strlen(t);
    *i += j + len2 - len;
    return len2;
}

char *aliasstrrep(char *s, struct dalias *alias)
{
    int i = 0;
    int len = strlen(s);
    while (i < len)
    {
        while (i < len && isblank(s[i]))
        {
            i++;
        }
        int j = i + 1;
        while (j < len && !isblank(s[j]))
        {
            j++;
        }
        char *t = get_fnprintf(s, j, i, alias);
        if (t)
        {
            len = newchar(s, j, &i, t);
            free(s);
            s = t;
        }
        else
        {
            i = j;
        }
    }
    return s;
}
