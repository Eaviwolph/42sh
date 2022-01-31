#include "tree.h"

struct node *tree_bang_create(struct node *child)
{
    struct node *node;

    safe_calloc(node, 1, sizeof(struct node));
    node->type = BANG;
    node->data.binnode.left = child;
    return node;
}

void tree_bang_print(struct node *node, FILE *fs)
{
    fprintf(fs, "! ");
    tree_print_node(node->data.binnode.left, fs);
}

void tree_bang_destroy(struct node *node)
{
    tree_destroy(node->data.binnode.left);
    free(node);
}
