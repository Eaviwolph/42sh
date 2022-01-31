#include "tree.h"

struct node *tree_sep_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SEP;
    node->data.binnode.left = lhs;
    node->data.binnode.right = rhs;
    return node;
}

void tree_sep_print(struct node *node, FILE *fs)
{
    fprintf(fs, "sep ");
    tree_print_node(node->data.binnode.left, fs);
    tree_print_node(node->data.binnode.right, fs);
}

void tree_sep_destroy(struct node *node)
{
    tree_destroy(node->data.binnode.left);
    tree_destroy(node->data.binnode.right);
    free(node);
}
