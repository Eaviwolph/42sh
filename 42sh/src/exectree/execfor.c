#include <stdlib.h>
#include <string.h>

#include "../tools/tools.h"
#include "exectree.h"

void execfor(struct node_for n, struct shell *s)
{
    if (!n.vals)
        return;
    for (int i = 0; n.vals[i]; i++)
    {
        char *name = mystrdup(n.var);
        dvar_add_var(s->var, name, mystrdup(n.vals[i]));

        dvar_add_var(s->var, mystrdup("loop_status"), mystrdup("run"));
        char *v = dvar_find(s->var, "loop_status");
        if (!(v && !strcmp(v, "continue")))
            exectree(n.command, s);
        v = dvar_find(s->var, "loop_status");
        if (v && !strcmp(v, "break"))
            break;

        dvar_remove_elm(s->var, n.var);
    }
}