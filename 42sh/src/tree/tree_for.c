#include "tree.h"

struct node *tree_for_createvoid(char *var, char **vals, struct node *command)
{
    struct node *new;
    safe_malloc(new, sizeof(struct node));
    new->type = FOR;
    new->data.fornode.var = var;
    new->data.fornode.vals = vals;
    new->data.fornode.command = command;
    return new;
}

void tree_for_print(struct node *n, FILE *stream)
{
    if (n->type != FOR)
        return;
    // if values exist
    if (n->data.fornode.vals)
    {
        fprintf(stream, "for { ");
        for (size_t i = 0; n->data.fornode.vals[i]; ++i)
            fprintf(stream, "value:%s\n", n->data.fornode.vals[i]);
    }
    // execution
    if (n->data.fornode.command)
    {
        tree_print_node(n->data.fornode.command, stream);
    }
}

void tree_for_destroy_node(struct node *n)
{
    if (n->type != FOR)
        return;
    free(n->data.fornode.var);
    for (int i = 0; n->data.fornode.vals[i]; i++)
        free(n->data.fornode.vals[i]);
    free(n->data.fornode.vals);
    free(n);
}

void tree_for_destroy(struct node *n)
{
    if (n->type != FOR)
        return;
    tree_destroy(n->data.fornode.command);
    tree_for_destroy_node(n);
}
