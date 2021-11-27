/*
** builtin_set.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu May 11 09:32:30 2006 Seblu
** Last update Thu Nov 23 11:02:52 2006 seblu
*/

#include <assert.h>
#include <stdio.h>

#include "../shell/shell.h"

int builtin_set(char *argv[])
{
    assert(argv && argv[0]);
    if (argv[1] == NULL)
        for (size_t i = 0; i < shell->var->count; ++i)
            printf("%s='%s'\n", shell->var->table[i].name,
                   shell->var->table[i].value);
    return 0;
}
