#include "tree.h"

struct node *tree_or_create(struct node *left, struct node *right)
{
    s_ast_node *node;

    secmalloc(node, sizeof(struct node));
    node->type = OR;
    node->data.ornode.left = left;
    node->data.ornode.right = right;
    return node;
}

void tree_or_print(struct node *node, FILE *file, unsigned int *node_id)
{
    unsigned int left_id, right_id, cur_id;

    if (node->type != OR)
        return;

    fprintf(file, "%u [label = \"||\"];\n", cur_id = *node_id);
    left_id = ++*node_id;
    tree_print_node(node->data.ornode.left, file, node_id);
    fprintf(file, "%u -> %u\n", cur_id, left_id);
    right_id = *node_id;
    tree_print_node(node->data.ornode.right, file, node_id);
    fprintf(file, "%u -> %u\n", cur_id, right_id);
}

void tree_or_destroy_node(struct node *node)
{
    if (node->type != OR)
        return;
    free(node);
}

void tree_or_destroy(struct node *node)
{
    if (node->type != OR)
        return;
    tree_destroy(node->data.ornode.left);
    tree_destroy(node->data.ornode.right);
    free(node);
}
