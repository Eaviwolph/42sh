#include <stdlib.h>

#include "../tools/tools.h"
#include "exectree.h"

void execfor(struct node_for n, struct shell *s)
{
    for (int i = 0; n.vals[i]; i++)
    {
        char *str = calloc(12, sizeof(char));
        dvar_add_var(s->var, mystrdup(n.var), str);

        struct node *t = n.command;
        exectree(t, s);

        dvar_remove_elm(s->var, n.var);
    }
}