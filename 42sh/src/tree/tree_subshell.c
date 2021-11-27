#include "tree.h"


struct node *tree_subshell_create(struct node *child)
{
    struct node *node;

    secmalloc(node, sizeof(struct node));
    node->type = SUBSHELL;
    node->data.subshnode.left = child;
    node->data.subshnode.right = NULL;
    return node;
}

void tree_subshell_print(struct node *node, FILE *fs, unsigned int *node_id)
{
    unsigned int left;
    unsigned int cur_id;

    if (node->type != SUBSHELL)
        return;

    fprintf(fs, "%u [label = \"()\"];\n", cur_id = *node_id);
    left = ++*node_id;
    ast_print_node(node->data.subshnode.left, fs, node_id);
    fprintf(fs, "%u -> %u\n", cur_id, left);
}

void tree_subshell_destruct_node(struct node *node)
{
    if (node->type != SUBSHELL)
        return;
    free(node);
}

void tree_subshell_destruct(struct node *node)
{
    if (node->type != SUBSHELL)
        return;
    ast_destruct(node->data.subshnode.left);
    free(node);
}
