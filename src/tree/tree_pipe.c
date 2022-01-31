#include "tree.h"

struct node *tree_pipe_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = PIPE;
    node->data.binnode.left = lhs;
    node->data.binnode.right = rhs;
    return node;
}

void tree_pipe_print(struct node *node, FILE *fs)
{
    if (node->type != PIPE)
        return;
    fprintf(fs, "pipe ");
    tree_print_node(node->data.binnode.left, fs);
    tree_print_node(node->data.binnode.right, fs);
}

void tree_pipe_destroy(struct node *node)
{
    if (node->type != PIPE)
        return;
    tree_destroy(node->data.binnode.left);
    tree_destroy(node->data.binnode.right);
    free(node);
}
