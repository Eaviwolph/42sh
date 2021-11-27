#include "tree.h"

struct node *tree_pipe_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    secmalloc(node, sizeof(struct node));
    node->type = PIPE;
    node->data.pipenode.left = lhs;
    node->data.pipenode.right = rhs;
    return node;
}

void tree_pipe_print(struct node *node, FILE *fs, unsigned int *node_id)
{
    unsigned int lhs_id, rhs_id, cur_id;

    if (node->type != PIPE)
        return;
    fprintf(fs, "%u [label = \"|\"];\n", cur_id = *node_id);
    lhs_id = ++*node_id;
    ast_print_node(node->data.pipenode.left, fs, node_id);
    fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
    rhs_id = *node_id;
    ast_print_node(node->data.pipenode.right, fs, node_id);
    fprintf(fs, "%u -> %u\n", cur_id, rhs_id);
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
    ast_destruct(node->data.pipenode.left);
    ast_destruct(node->data.pipenode.right);
    free(node);
}
