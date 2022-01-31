#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dfunc.h"

struct dfunc *dfunc_init(void)
{
    struct dfunc *l = malloc(sizeof(struct dfunc));
    if (l)
    {
        l->size = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}

struct node_funcdec dfunc_find(const struct dfunc *list, char *name)
{
    size_t i = 0;
    struct dfunc_item *h = list->head;
    while (h && strcmp(h->fun.name, name) != 0)
    {
        h = h->next;
        i++;
    }
    if (h)
        return h->fun;
    struct node_funcdec fun;
    fun.name = NULL;
    fun.body = NULL;
    return fun;
}

int dfunc_add_fun(struct dfunc *list, struct node_funcdec fun)
{
    return dfunc_replace_fun(list, fun) || dfunc_push_back(list, fun);
}

static void dfunc_item_destroy(struct dfunc_item *h)
{
    if (h)
    {
        dfunc_item_destroy(h->next);
        tree_destroy(h->fun.body);
        free(h->fun.name);
        free(h);
    }
}

void dfunc_destroy(struct dfunc *list)
{
    dfunc_item_destroy(list->head);
    free(list);
}