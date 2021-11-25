#include "tree.h"

struct node *tree_while_create(struct node *condition, struct node *command)
{
    struct node *n;
    secmalloc(n, sizeof(struct node));
    n->type = WHILE;
    n->data.whilenode.condition = condition;
    n->data.whilenode.command = command;
    return n;
}

void tree_while_print(struct node *n, FILE *stream)
{
    if (n->type != WHILE)
        return;
    tree_print_node(n->data.whilenode.command, stream);
    tree_print_node(n->data.whilenode.condition, stream);
    fprintf(stream, "while { ");
}

void tree_while_destroy_node(struct node *n)
{
    if (n->type != WHILE)
        return;
    free(n);
}

void tree_while_destroy(struct node *n)
{
    if (n->type != WHILE)
        return;
    tree_destroy(n->data.whilenode.command);
    tree_destroy(n->data.whilenode.condition);
    free(n);
}