#include <string.h>

#include "exectree.h"

void execsep(struct node_bin n, struct shell *s)
{
    exectree(n.left, s);
    char *v = dvar_find(s->var, "loop_status");
    if (v && (!strcmp(v, "break") || !strcmp(v, "continue")))
        return;
    if (n.right)
        exectree(n.right, s);
}
