#include "tree.h"

struct node *tree_and_create(struct node *left_node, struct node *right_node)
{
    struct node *node;

    secmalloc(node, sizeof(struct node));
    node->type = AND;
    node->data.andnode.left = left_node;
    node->data.andnode.left = right_node;
    return node;
}

void tree_and_print(struct node *node, FILE *fs, unsigned int *node_id)
{
    unsigned int left_id, right_id, cur_id;

    if (node->type != AND)
        return;
    fprintf(fs, "%u [label = \"&&\"];\n", cur_id = *node_id);
    left_id = ++*node_id;
    ast_print_node(node->data.andnode.left, fs, node_id);
    fprintf(fs, "%u -> %u\n", cur_id, left_id);
    right_id = *node_id;
    ast_print_node(node->data.andnode.right, fs, node_id);
    fprintf(fs, "%u -> %u\n", cur_id, right_id);
}

void tree_and_destroy_node(struct node *node)
{
    if (node->type != AND)
        return;
    free(node);
}

void tree_and_destroy(struct node *node)
{
    if (node->type != AND)
        return;
    tree_destroy(node->data.andnode.left);
    tree_destroy(node->data.andnode.right);
    free(node);
}
