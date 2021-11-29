#include "tree.h"

struct node *tree_sepand_create(struct node *lhs, struct node *rhs)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = SEPAND;
    node->data.sepandnode.left = lhs;
    node->data.sepandnode.right = rhs;
    return node;
}

void tree_sepand_print(struct node *node, FILE *fs, unsigned int *node_id)
{
    unsigned int lhs_id, rhs_id, cur_id;

    if (node->type != SEPAND)
        return;
    fprintf(fs, "%u [label = \"&\"];\n", cur_id = *node_id);
    lhs_id = ++*node_id;
    tree_print_node(node->data.sepandnode.left, fs);
    fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
    if (node->data.sepandnode.right)
    {
        rhs_id = *node_id;
        tree_print_node(node->data.sepandnode.right, fs);
        fprintf(fs, "%u -> %u\n", cur_id, rhs_id);
    }
}

void tree_sepand_destroy_node(struct node *node)
{
    if (node->type != SEPAND)
        return;
    free(node);
}

void tree_sepand_destroy(struct node *node)
{
    if (node->type != SEPAND)
        return;
    tree_destroy(node->data.sepandnode.left);
    tree_destroy(node->data.sepandnode.right);
    free(node);
}
