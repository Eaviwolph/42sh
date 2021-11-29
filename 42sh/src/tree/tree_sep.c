#include "tree.h"

struct node *tree_sep_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SEP;
    node->data.sepnode.left = lhs;
    node->data.sepnode.right = rhs;
    return node;
}

void tree_sep_print(struct node *node, FILE *fs)
{
    if (node->type != SEP)
        return;
    fprintf(fs, "sep ");
    tree_print_node(node->data.sepnode.left, fs);
    if (node->data.sepnode.right)
    {
        tree_print_node(node->data.sepnode.right, fs);
    }
}

void tree_sep_destroy_node(struct node *node)
{
    if (node->type != SEP)
        return;
    free(node);
}

void tree_sep_destroy(struct node *node)
{
    if (node->type != SEP)
        return;
    tree_destroy(node->data.sepnode.left);
    tree_destroy(node->data.sepnode.right);
    free(node);
}
