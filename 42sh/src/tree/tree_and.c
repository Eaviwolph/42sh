#include "tree.h"

struct node *tree_and_create(struct node *left_node, struct node *right_node)
{
    struct node *node;

    safe_calloc(node, 1, sizeof(struct node));
    node->type = AND;
    node->data.binnode.left = left_node;
    node->data.binnode.right = right_node;
    return node;
}

void tree_and_print(struct node *node, FILE *fs)
{
    if (node->type != AND)
        return;
    tree_print_node(node->data.binnode.left, fs);
    fprintf(fs, "&& ");
    tree_print_node(node->data.binnode.right, fs);
    fflush(fs);
}

void tree_and_destroy_node(struct node *node)
{
    if (node->type != AND)
        return;
    free(node);
}

void tree_and_destroy(struct node *node)
{
    if (node->type != AND)
        return;
    tree_destroy(node->data.binnode.left);
    tree_destroy(node->data.binnode.right);
    free(node);
}
