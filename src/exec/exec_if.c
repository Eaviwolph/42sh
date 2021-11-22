/*
** exec_if.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 15:27:20 2006 Seblu
** Last update Sun Nov 12 13:11:02 2006 seblu
*/

#include "exec.h"

void		exec_if(s_if_node *node)
{
  assert(node);
  exec_node(node->cond);
  if (!shell->status)
    exec_node(node->cond_true);
  else
    exec_node(node->cond_false);
}
