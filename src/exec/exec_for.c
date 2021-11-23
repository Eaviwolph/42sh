/*
** exec_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Thu Nov 23 14:38:27 2006 seblu
*/

#include "exec.h"

void exec_for(s_for_node *node)
{
    assert(node && node->varname);
    for (int i = 0; node->values[i]; ++i)
    {
        var_add(shell->var, node->varname, node->values[i]);
        exec_node(node->exec);
    }
}
