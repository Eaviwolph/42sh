/*
** ast_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Oct 17 17:15:27 2006 seblu
*/

#include "ast.h"

s_ast_node	*ast_for_create(char		*varname,
				char		**values,
				s_ast_node	*exec)
{
  s_ast_node	*node;

  secmalloc(node, sizeof (s_ast_node));
  node->type = T_FOR;
  node->body.child_for.varname = varname;
  node->body.child_for.values = values;
  node->body.child_for.exec = exec;
  return node;
}

void		ast_for_print(s_ast_node *node, FILE *fs, unsigned *node_id)
{
  unsigned	cur_node;

  if (node->type != T_FOR)
    return;
  fprintf(fs, "%u [label = \"FOR\\nvariable: %s\"];\n",
	  cur_node = *node_id, node->body.child_for.varname);
  ++*node_id;
  //values
  if (node->body.child_for.values) {
    fprintf(fs, "%u -> %u\n", cur_node, *node_id);
    fprintf(fs, "%u [ label = \"Values\\n", *node_id);
    ++*node_id;
    for (register size_t i = 0; node->body.child_for.values[i]; ++i)
      fprintf(fs, "id=%zu %s\\n", i, node->body.child_for.values[i]);
    fprintf(fs, "\"];");
  }
  //execution
  if (node->body.child_for.exec) {
    fprintf(fs, "%u -> %u\n", cur_node, *node_id);
    ast_print_node(node->body.child_for.exec, fs, node_id);
  }
}

void		ast_for_destruct_node(s_ast_node *node)
{
  if (node->type != T_FOR)
    return;
  free(node->body.child_for.varname);
  for (register int i = 0; node->body.child_for.values[i]; ++i)
    free(node->body.child_for.values[i]);
  free(node->body.child_for.values);
  free(node);
}

void		ast_for_destruct(s_ast_node *node)
{
  if (node->type != T_FOR)
    return;
  ast_destruct(node->body.child_for.exec);
  ast_for_destruct_node(node);
}
