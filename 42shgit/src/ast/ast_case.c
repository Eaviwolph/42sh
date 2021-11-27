/*
** ast_for.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 02:41:37 2006 Seblu
** Last update Tue Oct 17 16:36:25 2006 seblu
*/

#include "ast.h"

s_ast_node *ast_case_create(char *word)
{
    s_ast_node *node;

    secmalloc(node, sizeof(s_ast_node));
    node->type = T_CASE;
    node->body.child_case.word = word;
    node->body.child_case.items = NULL;
    return node;
}

void ast_case_add_item(s_ast_node *node, char **pattern, s_ast_node *exec)
{
    s_case_item *item;
    s_case_item **this;

    if (node->type != T_CASE)
        return;
    secmalloc(item, sizeof(s_case_item));
    item->pattern = pattern;
    item->exec = exec;
    item->next = NULL;
    for (this = &node->body.child_case.items; *this; this = &(*this)->next)
        ; // do nothing
    *this = item;
}

void ast_case_print(s_ast_node *node, FILE *fs, unsigned *node_id)
{
    unsigned cur_node;
    s_case_item *item;
    unsigned item_id;
    unsigned item_node;

    if (node->type != T_CASE)
        return;
    fprintf(fs, "%u [label = \"CASE\\nword: %s\"];\n", cur_node = *node_id,
            node->body.child_case.word);
    ++*node_id;
    // show items
    for (item = node->body.child_case.items, item_id = 0; item;
         item = item->next, ++item_id)
    {
        fprintf(fs, "%u -> %u\n", cur_node, *node_id);
        fprintf(fs, "%u [label = \"Item %u\\n", item_node = *node_id, item_id);
        ++*node_id;
        // print pattern
        if (item->pattern)
            for (int i = 0; item->pattern[i]; ++i)
                fprintf(fs, "%s\\n", item->pattern[i]);
        fprintf(fs, "\"];\n");
        // print exec
        if (item->exec)
        {
            fprintf(fs, "%u -> %u\n", item_node, *node_id);
            ast_print_node(item->exec, fs, node_id);
        }
    }
}

void ast_case_destruct_node(s_ast_node *node)
{
    s_case_item *this, *buf;

    if (node->type != T_CASE)
        return;
    free(node->body.child_case.word);
    for (this = node->body.child_case.items; this; this = buf)
    {
        for (register int i = 0; this->pattern[i]; ++i)
            free(this->pattern[i]);
        free(this->pattern);
        buf = this->next;
        free(this);
    }
    free(node);
}

void ast_case_destruct(s_ast_node *node)
{
    s_case_item *this, *buf;

    if (node->type != T_CASE)
        return;
    free(node->body.child_case.word);
    for (this = node->body.child_case.items; this; this = buf)
    {
        for (register int i = 0; this->pattern[i]; ++i)
            free(this->pattern[i]);
        free(this->pattern);
        ast_destruct(this->exec);
        buf = this->next;
        free(this);
    }
    free(node);
}
