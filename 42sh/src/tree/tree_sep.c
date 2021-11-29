#include "tree.h"

struct node *tree_sep_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SEP;
    node->data.sepnode.left = lhs;
    node->data.sepnode.right = rhs;
    return node;
}

void tree_sep_print(struct node *node, FILE *fs, unsigned int *node_id)
{
    unsigned int lhs_id, rhs_id, cur_id;
    if (node->type != SEP)
        return;
    fprintf(fs, "%u [label = \";\"];\n", cur_id = *node_id);
    lhs_id = ++*node_id;
    tree_print_node(node->data.sepnode.left, fs);
    fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
    if (node->data.sepnode.right)
    {
        rhs_id = *node_id;
        tree_print_node(node->data.sepnode.right, fs);
        fprintf(fs, "%u -> %u\n", cur_id, rhs_id);
    }
}

void tree_sep_destroy_node(struct node *node)
{
    if (node->type != SEP)
        return;
    free(node);
}

void tree_sep_destroy(struct node *node)
{
    if (node->type != SEP)
        return;
    tree_destroy(node->data.sepnode.left);
    tree_destroy(node->data.sepnode.right);
    free(node);
}
