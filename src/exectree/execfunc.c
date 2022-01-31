#include <err.h>
#include <string.h>

#include "../functions/dfunc.h"
#include "../tools/tools.h"
#include "../variables/var.h"
#include "exectree.h"

void exefuncdec(struct node_funcdec n, struct shell *s)
{
    dfunc_add_fun(s->fun, n);
}

static struct dvar *getvars(int len, char *args[])
{
    char **names = NULL;
    char **vars = NULL;
    if (len > 0)
    {
        names = calloc(len, sizeof(char *));
        vars = calloc(len, sizeof(char *));
    }
    for (int i = 0; i < len; i++)
    {
        names[i] = calloc(11, sizeof(char));
        vars[i] = calloc(strlen(args[i]) + 1, sizeof(char));
        int j = 0;
        while (args[i][j])
        {
            vars[i][j] = args[i][j];
            j++;
        }
        snprintf(names[i], 10, "%d", i);
    }
    struct dvar *d = initvars(names, vars, len);
    free(names);
    free(vars);
    return d;
}

void functmpvars(struct node_funcdec fun, char **argv, size_t len,
                 struct shell *s)
{
    struct dvar_item *v = s->var->head;
    size_t i = 0;
    while (v && v->name[0] != '@')
    {
        v = v->next;
        i++;
    }
    struct dvar *l2 = dvar_split_at(s->var, i + 1);
    struct dvar *fsh = getvars(len, argv);

    dvar_add_var(fsh, mystrdup("0"), mystrdup(dvar_find(s->var, "0")));
    dvar_concat(fsh, l2);
    dvar_destroy(l2);

    struct dvar *save = s->var;
    s->var = fsh;

    exectree(fun.body, s);
    v = s->var->head;
    i = 0;
    while (v && v->name[0] != '@')
    {
        v = v->next;
        i++;
    }
    l2 = dvar_split_at(s->var, i + 1);
    dvar_concat(save, l2);
    s->var = save;
    dvar_destroy(fsh);
    dvar_destroy(l2);
}

int execfunc(struct node_cmd n, struct shell *s)
{
    n.argv[0] = varstrrep(n.argv[0], s->var);
    if (!n.argv[0])
        errx(2, "Syntax error");
    struct node_funcdec fun = dfunc_find(s->fun, n.argv[0]);
    if (!fun.name)
    {
        return 0;
    }
    for (size_t i = 1; i < n.sizea; i++)
    {
        n.argv[i] = varstrrep(n.argv[i], s->var);
        if (!n.argv[i])
        {
            errx(2, "Syntax error");
        }
    }
    functmpvars(fun, n.argv, n.sizea, s);
    return 1;
}