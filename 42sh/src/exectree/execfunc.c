#include "../functions/dfunc.h"
#include "../variables/var.h"
#include "exectree.h"

void exefuncdec(struct node_funcdec n, struct shell *s)
{
    dfunc_add_fun(s->fun, n);
}

/*static struct dvar *functmpvars(char **argv, size_t len, struct shell *s)
{

}*/

int execfunc(struct node_cmd n, struct shell *s)
{
    struct node_funcdec fun = dfunc_find(s->fun, n.argv[0]);
    if (!fun.name)
    {
        return 0;
    }
    exectree(fun.body, s);
    return 1;
}