/*
** exec_sep.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Sun Nov 12 03:46:19 2006 seblu
*/

#include "exec.h"

void		exec_sep(s_bin_node *node)
{
  assert(node);
  exec_node(node->lhs);
  if (node->rhs)
    exec_node(node->rhs);
}
