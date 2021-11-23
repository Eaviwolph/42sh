/*
** ast_if.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Oct 17 16:30:23 2006 seblu
*/

#include "ast.h"

s_ast_node *ast_if_create(s_ast_node *cond, s_ast_node *cond_true,
                          s_ast_node *cond_false) {
  s_ast_node *node;

  secmalloc(node, sizeof(s_ast_node));
  node->type = T_IF;
  node->body.child_if.cond = cond;
  node->body.child_if.cond_true = cond_true;
  node->body.child_if.cond_false = cond_false;
  return node;
}

void ast_if_print(s_ast_node *node, FILE *fs, unsigned *node_id) {
  unsigned cur_node;

  if (node->type != T_IF)
    return;
  fprintf(fs, "%u [label = \"IF\"];\n", cur_node = *node_id);
  ++*node_id;
  // if
  if (node->body.child_if.cond) {
    fprintf(fs, "%u -> %u\n", cur_node, *node_id);
    ast_print_node(node->body.child_if.cond, fs, node_id);
  }
  // then
  if (node->body.child_if.cond_true) {
    fprintf(fs, "%u -> %u\n", cur_node, *node_id);
    ast_print_node(node->body.child_if.cond_true, fs, node_id);
  }
  // else
  if (node->body.child_if.cond_false) {
    fprintf(fs, "%u -> %u\n", cur_node, *node_id);
    ast_print_node(node->body.child_if.cond_false, fs, node_id);
  }
}

void ast_if_destruct_node(s_ast_node *node) {
  if (node->type != T_IF)
    return;
  free(node);
}

void ast_if_destruct(s_ast_node *node) {
  if (node->type != T_IF)
    return;
  ast_destruct(node->body.child_if.cond);
  ast_destruct(node->body.child_if.cond_true);
  ast_destruct(node->body.child_if.cond_false);
  free(node);
}
