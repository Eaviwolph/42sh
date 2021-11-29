#include "tree.h"

struct node *tree_sepand_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SEPAND;
    node->data.sepandnode.left = lhs;
    node->data.sepandnode.right = rhs;
    return node;
}

void tree_sepand_print(struct node *node, FILE *fs)
{
    if (node->type != SEPAND)
        return;
    fprintf(fs, "sepand ");
    tree_print_node(node->data.sepandnode.left, fs);
    if (node->data.sepandnode.right)
    {
        tree_print_node(node->data.sepandnode.right, fs);
    }
}

void tree_sepand_destroy_node(struct node *node)
{
    if (node->type != SEPAND)
        return;
    free(node);
}

void tree_sepand_destroy(struct node *node)
{
    if (node->type != SEPAND)
        return;
    tree_destroy(node->data.sepandnode.left);
    tree_destroy(node->data.sepandnode.right);
    free(node);
}
