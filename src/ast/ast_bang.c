/*
** ast_bang.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Oct 17 17:12:13 2006 seblu
*/

#include "ast.h"

s_ast_node *ast_bang_create(s_ast_node *child) {
  s_ast_node *node;

  secmalloc(node, sizeof(s_ast_node));
  node->type = T_BANG;
  node->body.child_bang.lhs = child;
  node->body.child_bang.rhs = NULL;
  return node;
}

void ast_bang_print(s_ast_node *node, FILE *fs, unsigned int *node_id) {
  unsigned int lhs_id, cur_id;

  if (node->type != T_BANG)
    return;
  fprintf(fs, "%u [label = \"!\"];\n", cur_id = *node_id);
  lhs_id = ++*node_id;
  ast_print_node(node->body.child_bang.lhs, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
}

void ast_bang_destruct_node(s_ast_node *node) {
  if (node->type != T_BANG)
    return;
  free(node);
}

void ast_bang_destruct(s_ast_node *node) {
  if (node->type != T_BANG)
    return;
  ast_destruct(node->body.child_bang.lhs);
  free(node);
}
