#include "../tools/tools.h"
#include "tree.h"

struct node *tree_funcdec_create(char *name, struct node *body)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = FUNCDEC;
    node->data.funcdecnode.name = mystrdup(name);
    node->data.funcdecnode.body = body;
    return node;
}

void tree_funcdec_print(struct node *node, FILE *fs)
{
    fprintf(fs, "%s (){ ", node->data.funcdecnode.name);
    tree_print_node(node->data.funcdecnode.body, fs);
    fprintf(fs, "}");
}

void tree_funcdec_destroy(struct node *node)
{
    free(node);
}
