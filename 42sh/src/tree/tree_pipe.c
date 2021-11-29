#include "tree.h"

struct node *tree_pipe_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = PIPE;
    node->data.pipenode.left = lhs;
    node->data.pipenode.right = rhs;
    return node;
}

void tree_pipe_print(struct node *node, FILE *fs)
{
    if (node->type != PIPE)
        return;
    fprintf(fs, "pipe ");
    tree_print_node(node->data.pipenode.left, fs);
    tree_print_node(node->data.pipenode.right, fs);
}

void tree_pipe_destroy_node(struct node *node)
{
    if (node->type != PIPE)
        return;
    free(node);
}

void tree_pipe_destroy(struct node *node)
{
    if (node->type != PIPE)
        return;
    tree_destroy(node->data.pipenode.left);
    tree_destroy(node->data.pipenode.right);
    free(node);
}
