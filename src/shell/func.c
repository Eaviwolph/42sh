/*
** func.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 14:52:39 2006 seblu
** Last update Thu Nov 23 11:38:33 2006 seblu
*/

/*
** ============
** DECLARATIONS
** ============
*/

#include "func.h"

#include <string.h>

#include "../ast/ast.h"
#include "../common/macro.h"

/*
** ===========
** DEFINITIONS
** ===========
*/

s_func *func_init(void)
{
    s_func *new;

    secmalloc(new, sizeof(s_func));
    new->count = 0;
    new->size = FUNC_DEFAULT_SIZE;
    secmalloc(new->table, new->size * sizeof(s_func_item));
    return new;
}

int func_exist(s_func *func, const char *name)
{
    assert(func && name);
    for (register size_t i = 0; i < func->count; ++i)
        if (!strcmp(name, func->table[i].name))
            return 1;
    return 0;
}

int func_add(s_func *func, char *name, s_ast_node *body)
{
    assert(func && name);
    // check for add or update
    for (register size_t i = 0; i < func->count; ++i)
        if (!strcmp(name, func->table[i].name))
        {
            // update time
            ast_destruct(func->table[i].body);
            func->table[i].body = body;
            return 1;
        }
    // add time
    ++func->count;
    if (func->size < func->count)
    {
        func->size += FUNC_PADDING;
        secrealloc(func->table, func->table, func->size * sizeof(s_func_item));
    }
    func->table[func->count - 1].name = name;
    func->table[func->count - 1].body = body;
    return 0;
}

int func_del(s_func *func, const char *name)
{
    register size_t i;

    assert(func && name);
    for (i = 0; i < func->count; ++i)
        if (!strcmp(name, func->table[i].name))
            break;
    if (i >= func->count)
        return 0;
    free(func->table[i].name);
    ast_destruct(func->table[i].body);
    func->table[i] = func->table[--func->count];
    if (func->size - func->count > 2 * FUNC_PADDING)
    {
        func->size -= FUNC_PADDING;
        secrealloc(func->table, func->table, func->size * sizeof(s_func_item));
    }
    return 1;
}

s_ast_node *func_get(s_func *func, const char *name)
{
    assert(func && name);
    for (register size_t i = 0; i < func->count; ++i)
        if (!strcmp(name, func->table[i].name))
            return func->table[i].body;
    return NULL;
}
