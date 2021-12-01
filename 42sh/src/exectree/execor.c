#include "exectree.h"

void execor(struct node_or n, struct shell *s)
{
    exectree(n.left, s);
    int r = atoi(dvar_find(s->var, "?"));
    if (r)
    {
        exectree(n.right, s);
        return;
    }
    while (n.right->type == OR)
        n = n.right->data.ornode;
    if (n.right->type == AND)
        exectree(n.right->data.andnode.right, s);
}