#include <stdlib.h>
#include <string.h>

#include "../tools/tools.h"
#include "exectree.h"

void execwhile(struct node_while n, struct shell *s)
{
    while (1)
    {
        exectree(n.condition, s);
        int r = atoi(dvar_find(s->var, "?"));
        if (r)
            return;
        dvar_add_var(s->var, mystrdup("loop_status"), mystrdup("run"));
        char *v = dvar_find(s->var, "loop_status");
        if (!(v && !strcmp(v, "continue")))
            exectree(n.command, s);
        v = dvar_find(s->var, "loop_status");
        if (v && !strcmp(v, "break"))
            break;
    }
}