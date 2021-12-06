#include "tree.h"

struct node *tree_sepand_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SEPAND;
    node->data.binnode.left = lhs;
    node->data.binnode.right = rhs;
    return node;
}

void tree_sepand_print(struct node *node, FILE *fs)
{
    fprintf(fs, "sepand ");
    tree_print_node(node->data.binnode.left, fs);
    tree_print_node(node->data.binnode.right, fs);
}

void tree_sepand_destroy(struct node *node)
{
    tree_destroy(node->data.binnode.left);
    tree_destroy(node->data.binnode.right);
    free(node);
}
