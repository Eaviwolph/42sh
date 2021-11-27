#define _GNU_SOURCE

#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "dtoken.h"
#include "extendedgetline.h"

int cutword(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
            || c == '{' || c == '}' || c == ';' || c == '\n');
}

size_t nextchar(char *s, size_t i)
{
    if (!cutword(s[i]))
    {
        size_t j = i + 1;
        while (s[j] && !isblank(s[j]) && !cutword(s[j]))
        {
            j++;
        }
        return j;
    }
    return i + 1;
}

size_t eatmore(char *s, size_t i, size_t j)
{
    if ((s[i] == '&' && s[j] == '&') || (s[i] == '|' && s[j] == '|'))
    {
        return j + 1;
    }
    if (s[i] == '>' && (s[j] == '>' || s[j] == '|' || s[j] == '&'))
    {
        return j + 1;
    }
    if (s[i] == '<' && (s[j] == '>' || s[j] == '&'))
    {
        return j + 1;
    }
    return j;
}

struct dtoken *str_to_dtoken(struct dtoken *d, char *s)
{
    size_t i = 0;
    while (s[i])
    {
        while (s[i] && isblank(s[i]))
            i++;
        if (s[i])
        {
            size_t j = nextchar(s, i);
            j = eatmore(s, i, j);
            char *c = calloc(j - i + 1, sizeof(char));
            if (!c)
                errx(1, "malloc error");
            for (size_t k = 0; k < j - i; k++)
                c[k] = s[i + k];
            i = j;
            d = dtoken_add(d, c);
        }
    }
    return d;
}

void readlines(int fd)
{
    struct line *buffer = exgetline_start(fd);
    char *line;
    struct dtoken *d = dtoken_init();
    while ((line = exgetline(buffer)) != NULL)
    {
        d = str_to_dtoken(d, line);
        free(line);
    }
    exgetline_end(buffer, fd);
    print_dtoken(d);
    destroy_dtoken(d);
}

