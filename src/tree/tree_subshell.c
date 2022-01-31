#include "tree.h"

struct node *tree_subshell_create(struct node *child)
{
    struct node *node;

    safe_calloc(node, 1, sizeof(struct node));
    node->type = SUBSHELL;
    node->data.binnode.left = child;
    return node;
}

void tree_subshell_print(struct node *node, FILE *fs)
{
    fprintf(fs, "( ");
    tree_print_node(node->data.binnode.left, fs);
}

void tree_subshell_destroy(struct node *node)
{
    tree_destroy(node->data.binnode.left);
    free(node);
}
