#include "tree.h"


struct node *tree_subshell_create(struct node *child)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SUBSHELL;
    node->data.binnode.left = child;
    node->data.binnode.right = NULL;
    return node;
}

void tree_subshell_print(struct node *node, FILE *fs)
{
    if (node->type != SUBSHELL)
        return;

    fprintf(fs, "( ");
    tree_print_node(node->data.binnode.left, fs);
}

void tree_subshell_destroy_node(struct node *node)
{
    if (node->type != SUBSHELL)
        return;
    free(node);
}

void tree_subshell_destroy(struct node *node)
{
    if (node->type != SUBSHELL)
        return;
    tree_destroy(node->data.binnode.left);
    free(node);
}
