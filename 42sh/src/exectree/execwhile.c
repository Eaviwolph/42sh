#include <stdlib.h>

#include "../tools/tools.h"
#include "exectree.h"

void execwhile(struct node_while n, struct shell *s)
{
    while(1)
    {
        exectree(n.condition, s);
        int r = atoi(dvar_find(s->var, "?"));
        if (r)
            return;
        exectree(n.command, s);
    }
}