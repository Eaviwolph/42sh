#include <stdlib.h>

#include "../tools/tools.h"
#include "exectree.h"

void execbang(struct node_bin n, struct shell *s)
{
    exectree(n.left, s);
    int r = atoi(dvar_find(s->var, "?"));
    r = !r;
    char *str = calloc(12, sizeof(char));
    str = myitoa(r, str);
    dvar_add_var(s->var, mystrdup("?"), str);
}
