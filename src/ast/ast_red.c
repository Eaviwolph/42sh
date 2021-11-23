/*
** ast_cmd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Fri Aug 18 22:13:51 2006 Seblu
** Last update Tue Oct 17 17:16:40 2006 seblu
*/

#include "ast.h"

s_ast_node *ast_red_create(void)
{
    s_ast_node *node;

    secmalloc(node, sizeof(s_ast_node));
    node->type = T_RED;
    node->body.child_red.size = 0;
    node->body.child_red.type = NULL;
    node->body.child_red.fd = NULL;
    node->body.child_red.word = NULL;
    node->body.child_red.mhs = NULL;
    return node;
}

void ast_red_add(s_ast_node *node, e_red_type type, int fd, char *word)
{
    if (node->type != T_RED)
        return;
    s_red_node *reds = (s_red_node *)&node->body.child_red;
    ++reds->size;
    secrealloc(reds->type, reds->type, sizeof(e_red_type) * reds->size);
    reds->type[reds->size - 1] = type;
    secrealloc(reds->fd, reds->fd, sizeof(int) * reds->size);
    reds->fd[reds->size - 1] = fd;
    secrealloc(reds->word, reds->word, sizeof(char *) * reds->size);
    reds->word[reds->size - 1] = word;
}

void ast_red_print(s_ast_node *node, FILE *fs, unsigned *node_id)
{
    unsigned cur_id = *node_id;

    if (node->type != T_RED)
        return;
    s_red_node *reds = (s_red_node *)&node->body.child_red;
    if (reds->size == 0)
        return;
    fprintf(fs, "%u [label = \"Redirection\\n", *node_id);
    ++*node_id;
    for (register size_t i = 0; i < reds->size; ++i)
        fprintf(fs, "id=%zu, fd=%d, type=%d, word=%s\\n", i, reds->fd[i],
                reds->type[i], reds->word[i]);
    fprintf(fs, "\"];\n");
    fprintf(fs, "%u -> %u\n", cur_id, *node_id);
    if (reds->mhs)
        ast_print_node(reds->mhs, fs, node_id);
}

void ast_red_destruct_node(s_ast_node *node)
{
    s_red_node *reds;

    if (node->type != T_RED)
        return;
    reds = (s_red_node *)&node->body.child_red;
    if (reds->size)
    {
        free(reds->type);
        free(reds->fd);
        for (register size_t i = 0; i < reds->size; ++i)
            free(reds->word[i]);
        free(reds->word);
    }
    free(node);
}

void ast_red_destruct(s_ast_node *node)
{
    if (node->type != T_RED)
        return;
    ast_destruct(node->body.child_red.mhs);
    ast_red_destruct_node(node);
}
