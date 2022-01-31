#include "../tools/tools.h"
#include "tree.h"

struct node *tree_for_create(char *var, char **vals, struct node *command)
{
    char **valstmp = NULL;
    if (vals)
    {
        size_t len = 0;
        while (vals[len])
        {
            len++;
        }
        valstmp = calloc(len + 1, sizeof(char *));
        for (size_t i = 0; i < len; i++)
        {
            valstmp[i] = mystrdup(vals[i]);
        }
    }
    free(vals);
    struct node *new;
    safe_malloc(new, sizeof(struct node));
    new->type = FOR;
    new->data.fornode.var = mystrdup(var);
    new->data.fornode.vals = valstmp;
    new->data.fornode.command = command;
    return new;
}

void tree_for_print(struct node *n, FILE *stream)
{
    fprintf(stream, "for %s in", n->data.fornode.var);
    for (size_t i = 0; n->data.fornode.vals[i]; ++i)
        fprintf(stream, " %s", n->data.fornode.vals[i]);
    fprintf(stream, "\ndo\n");
    if (n->data.fornode.command)
    {
        tree_print_node(n->data.fornode.command, stream);
    }
    fprintf(stream, "\ndone\n");
}

void tree_for_destroy(struct node *n)
{
    tree_destroy(n->data.fornode.command);
    free(n->data.fornode.var);
    if (n->data.fornode.vals)
    {
        for (int i = 0; n->data.fornode.vals[i]; i++)
            free(n->data.fornode.vals[i]);
        free(n->data.fornode.vals);
    }
    free(n);
}
