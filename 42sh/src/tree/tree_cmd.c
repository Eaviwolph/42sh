#include "tree.h"

struct node *tree_cmd_create(void)
{
    struct node *n;
    safe_malloc(n, sizeof(struct node));
    n->type = CMD;
    n->data.cmdnode.argv = NULL;
    n->data.cmdnode.pref = NULL;
    return n;
}

void tree_cmd_pref(struct node *node, char *word)
{
    if (node->type != CMD)
        return;
    size_t size = 0;
    if (node->data.cmdnode.pref)
        while (node->data.cmdnode.pref[size])
            ++size;
    safe_realloc(node->data.cmdnode.pref, node->data.cmdnode.pref,
               (++size + 1) * sizeof(char *));
    node->data.cmdnode.pref[size - 1] = word;
    node->data.cmdnode.pref[size] = NULL;
}

void tree_cmd_argv(struct node *node, char *argv)
{
    if (node->type != CMD)
        return;
    size_t size = 0;
    if (node->data.cmdnode.argv)
        while (node->data.cmdnode.argv[size])
            ++size;
    safe_realloc(node->data.cmdnode.argv, node->data.cmdnode.argv,
               (++size + 1) * sizeof(char *));
    node->data.cmdnode.argv[size - 1] = argv;
    node->data.cmdnode.argv[size] = NULL;
}

void tree_cmd_print(struct node *node, FILE *stream)
{
    if (node->type != CMD)
        return;

    // if prefix exists
    char **prefix = node->data.cmdnode.pref;
    if (prefix && prefix[0])
    {
        for (int i = 0; prefix && prefix[i]; i++)
        {
            fprintf(stream, "prefix[%d]:", i);
            size_t last = 0, p = 0;
            for (; prefix[i][p]; ++p)
                if (prefix[i][p] == '"')
                    fprintf(stream, "%.*s\\", (int)(p - last), prefix[i] + last),
                        last = p;
            fprintf(stream, "%*s", (int)(p - last), prefix[i] + last), last = p;
            fprintf(stream, "\\n");
        }
    }

    // arguments
    char **argv = node->data.cmdnode.argv;
    if (argv && argv[0])
        for (int i = 0; argv && argv[i]; ++i)
        {
            fprintf(stream, "argv[%d]:", i);
            size_t last = 0, p = 0;
            for (; argv[i][p]; ++p)
                if (argv[i][p] == '"')
                    fprintf(stream, "%.*s\\", (int)(p - last), argv[i] + last),
                        last = p;
            fprintf(stream, "%*s", (int)(p - last), argv[i] + last), last = p;
            fprintf(stream, "\\n");
        }
    fprintf(stream, "\"];\n");
}

void tree_cmd_destroy_node(struct node *node)
{
    tree_cmd_destroy(node);
}

void tree_cmd_destroy(struct node *node)
{
    if (node->type != CMD)
        return;
    if (node->data.cmdnode.argv)
    {
        for (register int i = 0; node->data.cmdnode.argv[i]; ++i)
            free(node->data.cmdnode.argv[i]);
        free(node->data.cmdnode.argv);
    }
    if (node->data.cmdnode.pref)
    {
        for (register int i = 0; node->data.cmdnode.pref[i]; ++i)
            free(node->data.cmdnode.pref[i]);
        free(node->data.cmdnode.pref);
    }
    free(node);
}
