#include "tree.h"

struct node *tree_while_create(struct node *condition, struct node *command)
{
    struct node *n;
    safe_malloc(n, sizeof(struct node));
    n->type = WHILE;
    n->data.whilenode.condition = condition;
    n->data.whilenode.command = command;
    return n;
}

void tree_while_print(struct node *n, FILE *stream)
{
    fprintf(stream, "while cond:");
    tree_print_node(n->data.whilenode.command, stream);
    fprintf(stream, "\ndo\n");
    tree_print_node(n->data.whilenode.condition, stream);
    fprintf(stream, "\ndone\n");
}

void tree_while_destroy(struct node *n)
{
    tree_destroy(n->data.whilenode.command);
    tree_destroy(n->data.whilenode.condition);
    free(n);
}