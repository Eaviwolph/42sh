#include <fnmatch.h>

#include "../tools/tools.h"
#include "exectree.h"

static int testpat(char **pats, char *str, struct shell *s)
{
    size_t i = 0;
    while (pats[i])
    {
        char *p = varstrrep(mystrdup(pats[i]), s->var);
        if (fnmatch(p, str, 0) == 0)
        {
            free(p);
            return 1;
        }
        free(p);
        i++;
    }
    return 0;
}

void execcase(struct node_case n, struct shell *s)
{
    struct node_case_item *h = n.items;
    char *w = varstrrep(mystrdup(n.word), s->var);
    while (h && testpat(h->pattern, w, s) == 0)
    {
        h = h->next;
    }
    if (h)
    {
        exectree(h->exec, s);
    }
    free(w);
}