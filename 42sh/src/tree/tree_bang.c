#include "tree.h"

struct node *tree_bang_create(struct node *child)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node_bang));
    node->type = BANG;
    node->data.bangnode.left = child;
    node->data.bangnode.right = NULL;
    return node;
}

void tree_bang_print(struct node *node, FILE *fs)
{
    if (node->type != BANG)
        return;
    fprintf(fs, "bang ");
    tree_print_node(node->data.bangnode.left, fs);
}

void tree_bang_destroy_node(struct node *node)
{
    if (node->type != BANG)
        return;
    free(node);
}

void tree_bang_destroy(struct node *node)
{
    if (node->type != BANG)
        return;
    tree_destroy(node->data.bangnode.left);
    free(node);
}
