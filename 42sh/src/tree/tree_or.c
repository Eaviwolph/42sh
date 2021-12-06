#include "tree.h"

struct node *tree_or_create(struct node *left, struct node *right)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = OR;
    node->data.binnode.left = left;
    node->data.binnode.right = right;
    return node;
}

void tree_or_print(struct node *node, FILE *file)
{
    if (node->type != OR)
        return;

    tree_print_node(node->data.binnode.left, file);
    fprintf(file, "|| ");
    tree_print_node(node->data.binnode.right, file);
    fflush(file);
}

void tree_or_destroy_node(struct node *node)
{
    if (node->type != OR)
        return;
    free(node);
}

void tree_or_destroy(struct node *node)
{
    if (node->type != OR)
        return;
    tree_destroy(node->data.binnode.left);
    tree_destroy(node->data.binnode.right);
    free(node);
}
