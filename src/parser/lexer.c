#include <ctype.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tree/tree.h"
#include "dtoken.h"
#include "extendedgetline.h"
#include "parser.h"

int cutword(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')'
            || c == ';' || c == '\n' || c == '"' || c == '\'' || c == '!');
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
        j++;
    }
    else if (s[i] == '>' && (s[j] == '>' || s[j] == '|' || s[j] == '&'))
    {
        j++;
    }
    else if (s[i] == '<' && (s[j] == '>' || s[j] == '&'))
    {
        j++;
    }
    else if (s[i] == ';' && s[j] == ';')
    {
        j++;
    }
    else if (s[i] == '<' && s[j] == '<')
    {
        j++;
        if (s[j] == '-')
            j++;
    }
    return j;
}

struct dtoken *dtokenaddquote(struct dtoken *d, char *s, size_t *i,
                              char *quoted)
{
    size_t j = *i;
    while (s[*i] && s[*i] != *quoted)
    {
        *i += 1;
    }
    size_t k = strlen(d->tail->data.val);
    d->tail->data.val =
        realloc(d->tail->data.val, (k + *i - j + 1) * sizeof(char));
    size_t l = k;
    while (j < *i)
    {
        d->tail->data.val[l] = s[j];
        j++;
        l++;
    }
    d->tail->data.val[l] = '\0';
    if (s[*i] == *quoted)
    {
        *quoted = '\0';
        *i += 1;
    }
    return d;
}

struct dtoken *str_to_dtoken(struct dtoken *d, char *s, char *quoted)
{
    size_t i = 0;
    size_t len = strlen(s);
    while (i < len)
    {
        while (*quoted == '\0' && (i < len && isblank(s[i])))
            i++;
        if (*quoted || s[i] == '\'' || s[i] == '"')
        {
            if (!*quoted)
            {
                d = dtoken_add(d, calloc(1, sizeof(char)));
                *quoted = s[i];
                i++;
            }
            d = dtokenaddquote(d, s, &i, quoted);
        }
        else if (i < len)
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
            if (s[i] == '\'' || s[i] == '"')
            {
                *quoted = s[i];
                i++;
                d = dtokenaddquote(d, s, &i, quoted);
            }
        }
    }
    return d;
}

struct dtoken *readlines(int fd)
{
    struct line *buffer = exgetline_start(fd);
    char *line;
    struct dtoken *d = dtoken_init();
    char quote = '\0';
    while ((line = exgetline(buffer)) != NULL)
    {
        d = str_to_dtoken(d, line, &quote);
        free(line);
    }
    // if quote != '\0' => error
    exgetline_end(buffer, fd);
    d = dtoken_add(d, calloc(1, sizeof(char)));
    d->tail->data.op = LEOF;
    return d;
}
