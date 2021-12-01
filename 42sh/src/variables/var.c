#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dvar.h"

static char *strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, s, len);
}

static char *concat(char *dst, char *src, int lendst)
{
    int i = 0;
    if (lendst > 0)
    {
        dst[lendst] = ' ';
        lendst++;
    }
    while (src[i])
    {
        dst[lendst] = src[i];
        i++;
        lendst++;
    }
    dst[lendst] = '\0';
    return dst;
}

static int testshortvar(char c)
{
    return isdigit(c) || c == '#' || c == '@' || c == '$' || c == '?'
        || c == '*';
}

static char *my_itoa(int value, char *s)
{
    if (value == 0)
    {
        s[0] = '0';
        s[1] = '\0';
    }
    else
    {
        size_t i = 0;
        if (value < 0)
        {
            s[0] = '-';
            value = -value;
            i++;
        }
        size_t cp = value;
        while (cp > 0)
        {
            cp /= 10;
            i++;
        }
        s[i] = '\0';
        i--;
        while (value > 0)
        {
            s[i] = '0' + (value % 10);
            i--;
            value /= 10;
        }
    }
    return s;
}

static char *get_random(void)
{
    int r;
    for (int i = 0; i < 10; i++)
        r = rand() % 32767;
    char *s = calloc(7, sizeof(char));
    s = my_itoa(r, s);
    return s;
}

static char *get_fnprintf(char *s, int j, int io, struct dvar *var)
{
    int i = io - 1;
    if (s[i] == '{')
    {
        i--;
    }
    char *name = calloc(j - io + 1, sizeof(char));
    for (int k = 0; k < j - io; k++)
    {
        name[k] = s[io + k];
    }
    if (strcmp(name, "RANDOM") == 0)
    {
        dvar_add_var(var, strdup("RANDOM"), get_random());
    }
    char *val = dvar_find(var, name);
    if (!val)
    {
        val = "";
    }
    free(name);
    if (s[j] == '}')
    {
        j++;
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
    if (s[j] == '}')
    {
        j++;
    }
    int len = strlen(s);
    int len2 = strlen(t);
    *i = j + len2 - len;
    return len2;
}

char *varstrrep(char *s, struct dvar *var)
{
    int i = 0;
    int len = strlen(s);
    while (i < len)
    {
        if (s[i] == '$' && s[i + 1] && !isblank(s[i + 1]))
        {
            int io = i + 1;
            int j = io + 1;
            if (s[io] == '{')
            {
                io++;
                j = io + 1;
                while (s[j] && s[j] != '}')
                {
                    if (isblank(s[j]))
                        return NULL;
                    j++;
                }
                if (!s[j] || s[io] == '}')
                    return NULL;
            }
            else if (testshortvar(s[io]))
            {}
            else
            {
                while (s[j] && !isblank(s[j]) && s[j] != '$')
                {
                    j++;
                }
            }
            char *t = get_fnprintf(s, j, io, var);
            len = newchar(s, j, &i, t);
            free(s);
            s = t;
        }
        else
        {
            i++;
        }
    }
    return s;
}

struct dvar *initvars(char **names, char **vars, int size)
{
    struct dvar *d = dvar_init();
    int i = 0;
    char *list = NULL;
    while (i < size)
    {
        if (i > 0)
        {
            int lenlist = (list) ? strlen(list) : 0;
            list =
                realloc(list, sizeof(char) * (lenlist + strlen(vars[i])) + 2);
            list = concat(list, vars[i], lenlist);
        }
        dvar_add_var(d, names[i], vars[i]);
        i++;
    }
    char *s = calloc(12, sizeof(char));
    if (size > 0)
    {
        size--;
    }
    sprintf(s, "%d", size);
    dvar_add_var(d, strdup("#"), s);
    dvar_add_var(d, strdup("?"), strdup("0"));
    if (list)
    {
        dvar_add_var(d, strdup("*"), list);
        dvar_add_var(d, strdup("@"), strdup(list));
    }
    return d;
}
