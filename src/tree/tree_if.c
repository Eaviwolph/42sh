#include "tree.h"

struct node *tree_if_create(struct node *c, struct node *c_t, struct node *c_e)
{
    struct node *new;
    safe_calloc(new, 1, sizeof(struct node));
    new->data.ifnode.c_then = c_t;
    new->data.ifnode.c_else = c_e;
    new->type = IF;
    new->data.ifnode.condition = c;
    return new;
}

void tree_if_print(struct node *node, FILE *stream)
{
    if (node->data.ifnode.condition)
    {
        fprintf(stream, "if { ");
        fflush(stream);
        tree_print_node(node->data.ifnode.condition, stream);
        fprintf(stream, "};\n");
        fflush(stream);
    }
    if (node->data.ifnode.c_then)
    {
        fprintf(stream, "then { ");
        fflush(stream);
        tree_print_node(node->data.ifnode.c_then, stream);
        fprintf(stream, "};\n");
        fflush(stream);
    }
    if (node->data.ifnode.c_else)
    {
        fprintf(stream, "else { ");
        fflush(stream);
        tree_print_node(node->data.ifnode.c_else, stream);
        fprintf(stream, "};\n");
        fflush(stream);
    }
}

void tree_if_destroy(struct node *n)
{
    tree_destroy(n->data.ifnode.condition);
    tree_destroy(n->data.ifnode.c_then);
    tree_destroy(n->data.ifnode.c_else);
    free(n);
}