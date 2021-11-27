/*
** ast_cmd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Fri Aug 18 22:13:51 2006 Seblu
** Last update Tue Oct 17 17:00:22 2006 seblu
*/

#include "ast.h"

s_ast_node *ast_cmd_create(void)
{
    s_ast_node *node;

    secmalloc(node, sizeof(s_ast_node));
    node->type = T_CMD;
    node->body.child_cmd.argv = NULL;
    node->body.child_cmd.prefix = NULL;
    return node;
}

void ast_cmd_add_prefix(s_ast_node *node, char *assignment_word)
{
    if (node->type != T_CMD)
        return;
    size_t size = 0;
    if (node->body.child_cmd.prefix)
        while (node->body.child_cmd.prefix[size])
            ++size;
    secrealloc(node->body.child_cmd.prefix, node->body.child_cmd.prefix,
               (++size + 1) * sizeof(char *));
    node->body.child_cmd.prefix[size - 1] = assignment_word;
    node->body.child_cmd.prefix[size] = NULL;
}

void ast_cmd_add_argv(s_ast_node *node, char *argv)
{
    if (node->type != T_CMD)
        return;
    size_t size = 0;
    if (node->body.child_cmd.argv)
        while (node->body.child_cmd.argv[size])
            ++size;
    secrealloc(node->body.child_cmd.argv, node->body.child_cmd.argv,
               (++size + 1) * sizeof(char *));
    node->body.child_cmd.argv[size - 1] = argv;
    node->body.child_cmd.argv[size] = NULL;
}

void ast_cmd_print(s_ast_node *node, FILE *fs, unsigned int *node_id)
{
    if (node->type != T_CMD)
        return;
    fprintf(fs, "%u [label = \"Command\\n", *node_id);
    ++*node_id;
    // prefix
    char **prefix = node->body.child_cmd.prefix;
    if (prefix && prefix[0])
    {
        for (int i = 0; prefix && prefix[i]; ++i)
        {
            fprintf(fs, "prefix[%d]:", i);
            size_t last = 0, p = 0;
            for (; prefix[i][p]; ++p)
                if (prefix[i][p] == '"')
                    fprintf(fs, "%.*s\\", (int)(p - last), prefix[i] + last),
                        last = p;
            fprintf(fs, "%*s", (int)(p - last), prefix[i] + last), last = p;
            fprintf(fs, "\\n");
        }
    }
    // arguments
    char **argv = node->body.child_cmd.argv;
    if (argv && argv[0])
        for (int i = 0; argv && argv[i]; ++i)
        {
            fprintf(fs, "argv[%d]:", i);
            size_t last = 0, p = 0;
            for (; argv[i][p]; ++p)
                if (argv[i][p] == '"')
                    fprintf(fs, "%.*s\\", (int)(p - last), argv[i] + last),
                        last = p;
            fprintf(fs, "%*s", (int)(p - last), argv[i] + last), last = p;
            fprintf(fs, "\\n");
        }
    fprintf(fs, "\"];\n");
}

void ast_cmd_destruct_node(s_ast_node *node)
{
    ast_cmd_destruct(node);
}

void ast_cmd_destruct(s_ast_node *node)
{
    if (node->type != T_CMD)
        return;
    if (node->body.child_cmd.argv)
    {
        for (register int i = 0; node->body.child_cmd.argv[i]; ++i)
            free(node->body.child_cmd.argv[i]);
        free(node->body.child_cmd.argv);
    }
    if (node->body.child_cmd.prefix)
    {
        for (register int i = 0; node->body.child_cmd.prefix[i]; ++i)
            free(node->body.child_cmd.prefix[i]);
        free(node->body.child_cmd.prefix);
    }
    free(node);
}
