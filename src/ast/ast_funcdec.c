/*
** ast_funcdec.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Thu Nov 16 17:07:14 2006 seblu
*/

#include "ast.h"

s_ast_node *ast_funcdec_create(char *name, s_ast_node *body) {
  s_ast_node *node;

  secmalloc(node, sizeof(s_ast_node));
  node->type = T_FUNCDEC;
  node->body.child_funcdec.name = name;
  node->body.child_funcdec.body = body;
  return node;
}

void ast_funcdec_print(s_ast_node *node, FILE *fs, unsigned *node_id) {
  unsigned int lhs_id, cur_id;

  if (node->type != T_FUNCDEC)
    return;
  fprintf(fs, "%u [label = \"FuncDec\\nname: %s\"];\n", cur_id = *node_id,
          node->body.child_funcdec.name);
  lhs_id = ++*node_id;
  ast_print_node(node->body.child_funcdec.body, fs, node_id);
  fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
}

void ast_funcdec_destruct_node(s_ast_node *node) {
  if (node->type != T_FUNCDEC)
    return;
  if (node->body.child_funcdec.name)
    free(node->body.child_funcdec.name);
  free(node);
}

void ast_funcdec_destruct(s_ast_node *node) {
  if (node->type != T_FUNCDEC)
    return;
  if (node->body.child_funcdec.name)
    free(node->body.child_funcdec.name);
  if (node->body.child_funcdec.body)
    ast_destruct(node->body.child_funcdec.body);
  free(node);
}
