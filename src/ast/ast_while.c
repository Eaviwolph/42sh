/*
** ast_while.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Oct 17 16:44:13 2006 seblu
*/

#include "ast.h"

s_ast_node	*ast_while_create(s_ast_node *cond, s_ast_node *exec)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_WHILE;
  node->body.child_while.cond = cond;
  node->body.child_while.exec = exec;
  return node;
}

void		ast_while_print(s_ast_node *node, FILE *fs, unsigned int *node_id)
{
  unsigned int	lhs_id, rhs_id, cur_id;

  if (node->type != T_WHILE)
    return;
  fprintf(fs, "%u [label = \"while\"];\n", cur_id = *node_id);
  lhs_id = ++*node_id;
  ast_print_node(node->body.child_while.cond, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
  rhs_id = *node_id;
  ast_print_node(node->body.child_while.exec, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, rhs_id);
}

void		ast_while_destruct_node(s_ast_node *node)
{
  if (node->type != T_WHILE)
    return;
  free(node);
}

void		ast_while_destruct(s_ast_node *node)
{
  if (node->type != T_WHILE)
    return;
  ast_destruct(node->body.child_while.cond);
  ast_destruct(node->body.child_while.exec);
  free(node);
}
