#include "exectree.h"

void execand(struct node_and *n, struct shell *s)
{
    exectree(n->left, s);
    int r = atoi(dvar_find(s->var, "?"));
    if (!r)
    {
        exectree(n->right, s);
    }
    else
    {
        while (n->right->type == AND)
            n = &n->right->data.andnode;
        if (n->right->type == OR)
            exectree(n->right->data.andnode.right, s);
    }
}