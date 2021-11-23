/*
** basename.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 05:29:46 2006 Seblu
** Last update Tue Nov 14 15:37:34 2006 seblu
*/

#include <string.h>

#include "function.h"

char *basename(const char *path)
{
    size_t start = 0, end = 0, len;
    register size_t i;

    if ((len = strlen(path)) == 0)
        return strdup("");
    // search first char WITHOUT '/' start at end string
    for (i = len - 1;; --i)
    {
        if (path[i] != '/')
        {
            end = i;
            break;
        }
        if (i == 0)
            break;
    }
    if (end == 0)
        return strdup("");
    // search first char '/' from end string
    for (i = end - 1;; --i)
    {
        if (path[i] == '/')
        {
            start = i + 1;
            break;
        }
        if (i == 0)
            break;
    }
    return strndup(path + start, (start > end) ? 0 : end - start + 1);
}
