#include "tree.h"

struct node *tree_if_create(struct node *c, struct node *c_t, struct node *c_e)
{
    struct node *new;
    safe_malloc(new, sizeof(struct node));
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
        fflush(stream);
        tree_print_node(node->data.ifnode.condition, stream);
        fprintf(stream, "}; ");
        fflush(stream);
    }
    // then exists
    if (node->data.ifnode.c_then)
    {
        fprintf(stream, "then { ");
        fflush(stream);
        tree_print_node(node->data.ifnode.c_then, stream);
        fprintf(stream, "}; ");
        fflush(stream);
    }
    // else exists
    if (node->data.ifnode.c_else)
    {
        fprintf(stream, "else { ");
        fflush(stream);
        tree_print_node(node->data.ifnode.c_else, stream);
        fprintf(stream, "}; ");
        fflush(stream);
    }
}

void tree_if_destroy_node(struct node *n)
{
    if (!n || n->type != IF)
        return;
    free(n);
}

void tree_if_destroy(struct node *n)
{
    if (!n || n->type != IF)
        return;
    tree_destroy(n->data.ifnode.condition);
    tree_destroy(n->data.ifnode.c_then);
    tree_destroy(n->data.ifnode.c_else);
    free(n);
}