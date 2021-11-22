/*
** exec_funcdec.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Nov 16 16:06:00 2006 seblu
** Last update Thu Nov 16 17:04:48 2006 seblu
*/

#include "exec.h"
#include "../shell/func.h"

void		exec_funcdec(s_funcdec_node *node)
{
  func_add(shell->func, node->name, node->body);
  node->body = NULL;
  node->name = NULL;
}
