/*
** exec_while.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Sun Nov 12 03:46:34 2006 seblu
*/

#include "exec.h"

void exec_while(s_while_node *node)
{
    assert(node);
    for (exec_node(node->cond); !shell->status; exec_node(node->cond))
        exec_node(node->exec);
}
