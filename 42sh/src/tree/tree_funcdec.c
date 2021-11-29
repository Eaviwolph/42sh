#include "tree.h"

struct node *tree_funcdec_create(char *name, struct node *body)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = FUNCDEC;
    node->data.funcdecnode.name = name;
    node->data.funcdecnode.body = body;
    return node;
}

void tree_funcdec_print(struct node *node, FILE *fs, unsigned *node_id)
{
    unsigned int lhs_id;
    unsigned int cur_id;

    if (node->type != FUNCDEC)
        return;
    fprintf(fs, "%u [label = \"FuncDec\\nname: %s\"];\n", cur_id = *node_id,
            node->data.funcdecnode.name);
    lhs_id = ++*node_id;
    tree_print_node(node->data.funcdecnode.body, fs);
    fprintf(fs, "%u -> %u\n", cur_id, lhs_id);
}

void tree_funcdec_destroy_node(struct node *node)
{
    if (node->type != FUNCDEC)
        return;
    if (node->data.funcdecnode.name)
        free(node->data.funcdecnode.name);
    free(node);
}

void tree_funcdec_destroy(struct node *node)
{
    if (node->type != FUNCDEC)
        return;
    if (node->data.funcdecnode.name)
        free(node->data.funcdecnode.name);
    if (node->data.funcdecnode.body)
        tree_destroy(node->data.funcdecnode.body);
    free(node);
}
