/*
** exec_and.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Thu Nov 16 15:07:07 2006 seblu
*/

#include "exec.h"

void exec_or(s_bin_node *node)
{
    assert(node);
    exec_node(node->lhs);
    if (shell->status)
        exec_node(node->rhs);
    else
    {
        for (; node->rhs->type == T_OR; node = &node->rhs->body.child_or)
            ; // do nothing
        if (node->rhs->type == T_AND)
            exec_node(node->rhs->body.child_and.rhs);
    }
}
