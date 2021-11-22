/*
** ast_or.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Oct 17 17:01:20 2006 seblu
*/

#include "ast.h"

s_ast_node	*ast_or_create(s_ast_node *lhs, s_ast_node *rhs)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_OR;
  node->body.child_or.lhs = lhs;
  node->body.child_or.rhs = rhs;
  return node;
}

void		ast_or_print(s_ast_node *node, FILE *fs, unsigned int *node_id)
{
  unsigned int	lhs_id, rhs_id, cur_id;

  if (node->type != T_OR)
    return;
  fprintf(fs, "%u [label = \"||\"];\n", cur_id = *node_id);
  lhs_id = ++*node_id;
  ast_print_node(node->body.child_or.lhs, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
  rhs_id = *node_id;
  ast_print_node(node->body.child_or.rhs, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, rhs_id);
}

void		ast_or_destruct_node(s_ast_node *node)
{
  if (node->type != T_OR)
    return;
  free(node);
}

void		ast_or_destruct(s_ast_node *node)
{
  if (node->type != T_OR)
    return;
  ast_destruct(node->body.child_or.lhs);
  ast_destruct(node->body.child_or.rhs);
  free(node);
}

