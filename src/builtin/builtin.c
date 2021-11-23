/*
** builtin.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Apr 11 00:22:44 2006 Seblu
** Last update Fri Nov 17 13:12:22 2006 seblu
*/

#include "builtin.h"

#include <assert.h>
#include <string.h>

enum
{
    BUILTIN_COUNT = 12
};

struct builtin_table
{
    const char *name;
    f_builtin func;
};

static struct builtin_table builtin_table[BUILTIN_COUNT] = {
    { "cd", builtin_cd },
    { "echo", builtin_echo },
    { "exit", builtin_exit },
    { "shopt", builtin_shopt },
    { "alias", builtin_alias },
    { "unalias", builtin_unalias },
    { "source", NULL }, // builtin_source},
    { ".", NULL }, // builtin_source},
    { "set", builtin_set },
    { "unset", builtin_unset },
    { "export", builtin_export },
    { "exec", builtin_exec }
};

int is_a_builtin(const char *name)
{
    for (register int i = 0; i < BUILTIN_COUNT; ++i)
        if (!strcmp(name, builtin_table[i].name))
            return 1;
    return 0;
}

f_builtin get_builtin(const char *name)
{
    for (register int i = 0; i < BUILTIN_COUNT; ++i)
        if (!strcmp(name, builtin_table[i].name))
        {
            assert(builtin_table[i].func);
            return builtin_table[i].func;
        }
    assert(0);
    return NULL;
}
