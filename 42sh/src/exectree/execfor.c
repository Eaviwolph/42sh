#include <stdlib.h>

#include "../tools/tools.h"
#include "exectree.h"

void execfor(struct node_for n, struct shell *s)
{
    for (int i = 0; n.vals[i]; i++)
    {
        char *name = mystrdup(n.var);
        dvar_add_var(s->var, name, mystrdup(n.vals[i]));

        exectree(n.command, s);

        dvar_remove_elm(s->var, n.var);
    }
}