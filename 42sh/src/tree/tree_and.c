#include "tree.h"

struct node *tree_and_create(struct node *left_node, struct node *right_node)
{
    struct node *node;

    safe_calloc(node, 1, sizeof(struct node));
    node->type = AND;
    node->data.andnode.left = left_node;
    node->data.andnode.left = right_node;
    return node;
}

void tree_and_print(struct node *node, FILE *fs)
{
    if (node->type != AND)
        return;
    fprintf(fs, "&& ");
    tree_print_node(node->data.andnode.left, fs);
    tree_print_node(node->data.andnode.right, fs);
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
    tree_destroy(node->data.andnode.left);
    tree_destroy(node->data.andnode.right);
    free(node);
}
