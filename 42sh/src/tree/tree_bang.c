#include "tree.h"

struct node *tree_bang_create(struct node *child)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node_bang));
    node->type = BANG;
    node->data.bangnode.left = child;
    node->data.bangnode.right = NULL;
    return node;
}

void tree_bang_print(struct node *node, FILE *fs, unsigned int *node_id)
{
    unsigned int lhs_id, cur_id;

    if (node->type != BANG)
        return;
    fprintf(fs, "%u [label = \"!\"];\n", cur_id = *node_id);
    lhs_id = ++*node_id;
    tree_print_node(node->data.bangnode.left, fs);
    fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
}

void tree_bang_destroy_node(struct node *node)
{
    if (node->type != BANG)
        return;
    free(node);
}

void tree_bang_destroy(struct node *node)
{
    if (node->type != BANG)
        return;
    tree_destroy(node->data.bangnode.left);
    free(node);
}
