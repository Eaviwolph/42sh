/*
** exec_and.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Thu Nov 16 15:02:58 2006 seblu
*/

#include "exec.h"

void		exec_and(s_bin_node *node)
{
  assert(node);
  exec_node(node->lhs);
  if (!shell->status)
    exec_node(node->rhs);
  else {
    for (; node->rhs->type == T_AND; node = &node->rhs->body.child_and)
      ; //do nothing
    if (node->rhs->type == T_OR)
      exec_node(node->rhs->body.child_or.rhs);
  }
}
