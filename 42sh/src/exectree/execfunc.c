#include "../functions/dfunc.h"
#include "../variables/var.h"
#include "exectree.h"

void exefuncdec(struct node_funcdec n, struct shell *s)
{
    dfunc_add_fun(s->fun, n);
}

void functmpvars(char **argv, size_t len, struct shell *s)
{
    (void)argv;
    (void)len;
    (void)s;
    struct dvar_item *v = s->var->head;
    size_t i = 0;
    while (v && v->data[0] != '@')
    {
        v = v->next;
        i++;
    }
    struct dvar *l2 = dvar_split_at(s->var, i);
    printf("\nl2 = \n");
    dvar_print(l2);
    printf("\ns->var = \n");
    dvar_print(s->var);
}

int execfunc(struct node_cmd n, struct shell *s)
{
    struct node_funcdec fun = dfunc_find(s->fun, n.argv[0]);
    if (!fun.name)
    {
        return 0;
    }
    dvar_print(s->var);
    functmpvars(NULL, 2, s);

    exectree(fun.body, s);
    return 1;
}