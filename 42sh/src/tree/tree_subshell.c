#include "tree.h"


struct node *tree_subshell_create(struct node *child)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SUBSHELL;
    node->data.subshnode.left = child;
    node->data.subshnode.right = NULL;
    return node;
}

void tree_subshell_print(struct node *node, FILE *fs)
{
    if (node->type != SUBSHELL)
        return;

    fprintf(fs, "( ");
    tree_print_node(node->data.subshnode.left, fs);
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
    tree_destroy(node->data.subshnode.left);
    free(node);
}
