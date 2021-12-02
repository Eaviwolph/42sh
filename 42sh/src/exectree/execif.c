#include "exectree.h"

void execif(struct node_if n, struct shell *s)
{
    exectree(n.condition, s);
    int r = atoi(dvar_find(s->var, "?"));
    if (!r)
    {
        exectree(n.c_then, s);
        return;
    }
    if (n.c_else)
        exectree(n.c_else, s);
}