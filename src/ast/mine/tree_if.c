#include "tree.h"

struct node *tree_if_create(struct node *c, struct node *c_t, struct node *c_e)
{
    struct node *new;
    secmalloc(new, sizeof(struct node));
    new->data.ifnode.c_then = c_t;
    new->data.ifnode.c_else = c_e;
    new->type = IF;
    new->data.ifnode.condition = c;
    return new;
}

void tree_if_print(struct node *node, FILE *stream)
{
    if (node->type != IF)
        return;
    // if exists
    if (node->data.ifnode.condition)
    {
        fprintf(stream, "if { ");
        tree_print_node(node->data.ifnode.condition, stream);
    }
    // then exists
    if (node->data.ifnode.c_then)
    {
        fprintf(stream, "then { ");
        tree_print_node(node->data.ifnode.c_then, stream);
    }
    // else exists
    if (node->data.ifnode.c_else)
    {
        fprintf(stream, "else { ");
        tree_print_node(node->data.ifnode.c_else, stream);
    }
}

void tree_if_destroy_node(struct node *n)
{
    if (n->type != IF)
        return;
    free(n);
}

void tree_if_destroy(struct node *n)
{
    if (n->type != IF)
        return;
    tree_if_destroy(n->data.ifnode.condition);
    tree_if_destroy(n->data.ifnode.c_then);
    tree_if_destroy(n->data.ifnode.c_else);
    free(n);
}