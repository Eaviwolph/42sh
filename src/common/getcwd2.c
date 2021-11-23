/*
** getcwd2.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 14:20:08 2006 seblu
** Last update Tue Nov 14 14:23:39 2006 seblu
*/

#include <limits.h>
#include <unistd.h>

#include "macro.h"

char *getcwd2(void)
{
    char *get;
    const size_t BUF_SIZE = PATH_MAX * sizeof(char);

    secmalloc(get, BUF_SIZE);
    return getcwd(get, BUF_SIZE);
}
