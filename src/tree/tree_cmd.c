#include "../tools/tools.h"
#include "tree.h"

struct node *tree_cmd_create(void)
{
    struct node *n;
    safe_calloc(n, 1, sizeof(struct node));
    n->type = CMD;
    n->data.cmdnode.argv = calloc(1, sizeof(char *));
    n->data.cmdnode.pref = calloc(1, sizeof(char *));
    n->data.cmdnode.sizea = 0;
    n->data.cmdnode.sizep = 0;
    return n;
}

void tree_cmd_pref(struct node *node, char *word)
{
    node->data.cmdnode.sizep += 1;
    safe_realloc(node->data.cmdnode.pref, node->data.cmdnode.pref,
                 (node->data.cmdnode.sizep + 1) * sizeof(char *));

    node->data.cmdnode.pref[node->data.cmdnode.sizep - 1] = mystrdup(word);
    node->data.cmdnode.pref[node->data.cmdnode.sizep] = NULL;
}

void tree_cmd_argv(struct node *node, char *argv)
{
    node->data.cmdnode.sizea += 1;
    safe_realloc(node->data.cmdnode.argv, node->data.cmdnode.argv,
                 (node->data.cmdnode.sizea + 1) * sizeof(char *));

    node->data.cmdnode.argv[node->data.cmdnode.sizea - 1] = mystrdup(argv);
    node->data.cmdnode.argv[node->data.cmdnode.sizea] = NULL;
}

void tree_cmd_print(struct node *node, FILE *stream)
{
    fprintf(stream, "{");
    if (node->data.cmdnode.sizep)
    {
        fprintf(stream, "pref:(");
        for (size_t i = 0; i < node->data.cmdnode.sizep; i++)
        {
            fprintf(stream, "%s", node->data.cmdnode.pref[i]);
            if (i + 1 < node->data.cmdnode.sizep)
            {
                fprintf(stream, " ");
            }
        }
        fprintf(stream, ")");
    }
    if (node->data.cmdnode.sizea)
    {
        fprintf(stream, "args:(");
        for (size_t i = 0; i < node->data.cmdnode.sizea; i++)
        {
            fprintf(stream, "%s", node->data.cmdnode.argv[i]);
            if (i + 1 < node->data.cmdnode.sizea)
            {
                fprintf(stream, " ");
            }
        }
        fprintf(stream, ")");
    }
    fprintf(stream, "} ");
    fflush(stream);
}

void tree_cmd_destroy(struct node *node)
{
    for (size_t i = 0; i < node->data.cmdnode.sizea; i++)
    {
        free(node->data.cmdnode.argv[i]);
    }
    free(node->data.cmdnode.argv);
    for (size_t i = 0; i < node->data.cmdnode.sizep; i++)
    {
        free(node->data.cmdnode.pref[i]);
    }
    free(node->data.cmdnode.pref);
    free(node);
}