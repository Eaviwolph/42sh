/*
** exec_bang.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Sun Nov 12 03:44:33 2006 seblu
*/

#include "exec.h"

void exec_bang(s_bin_node *node)
{
    assert(node && node->lhs);
    exec_node(node->lhs);
    shell->status = !shell->status;
}
