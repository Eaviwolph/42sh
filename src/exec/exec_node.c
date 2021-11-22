/*
** exec_node.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 14:51:09 2006 Seblu
** Last update Fri Nov 17 14:25:08 2006 seblu
*/

#include "exec.h"

void		exec_node(s_ast_node *node)
{
  assert(node);
  switch (node->type) {
  case T_SEP: exec_sep(&node->body.child_sep);break;
  case T_SEPAND: exec_sepand(&node->body.child_sepand);break;
  case T_CMD: exec_cmd(&node->body.child_cmd); break;
  case T_RED: exec_red(&node->body.child_red); break;
  case T_PIPE: exec_pipe(&node->body.child_pipe); break;
  case T_AND: exec_and(&node->body.child_and); break;
  case T_OR: exec_or(&node->body.child_or); break;
  case T_IF: exec_if(&node->body.child_if); break;
  case T_WHILE: exec_while(&node->body.child_while); break;
  case T_BANG: exec_bang(&node->body.child_bang); break;
  case T_SUBSHELL: exec_subshell(&node->body.child_subshell); break;
  case T_FUNCDEC: exec_funcdec(&node->body.child_funcdec); break;
  case T_FOR: exec_for(&node->body.child_for); break;
  case T_CASE: exec_case(&node->body.child_case); break;
  default: assert(0);
  }
}
