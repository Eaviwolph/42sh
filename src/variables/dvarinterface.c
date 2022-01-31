#include "dvar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct dvar *dvar_init(void)
{
    struct dvar *l = malloc(sizeof(struct dvar));
    if (l)
    {
        l->size = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}

void dvar_print(const struct dvar *list)
{
    struct dvar_item *h = list->head;
    while (h)
    {
        printf("%s = %s\n", h->name, h->data);
        h = h->next;
    }
}

char *dvar_find(const struct dvar *list, char *name)
{
    size_t i = 0;
    struct dvar_item *h = list->head;
    while (h && strcmp(h->name, name) != 0)
    {
        h = h->next;
        i++;
    }
    if (h)
        return h->data;
    return NULL;
}

void dvar_remove_elm(struct dvar *list, char *elm)
{
    size_t i = 0;
    struct dvar_item *h = list->head;
    while (h && strcmp(elm, h->name) != 0)
    {
        h = h->next;
        i++;
    }
    if (h)
    {
        if (h->prev)
            h->prev->next = h->next;
        else
            list->head = h->next;
        if (h->next)
            h->next->prev = h->prev;
        else
            list->tail = h->prev;
        free(h->data);
        free(h->name);
        free(h);
        list->size--;
    }
}

int dvar_add_var(struct dvar *list, char *name, char *element)
{
    return dvar_replace_var(list, name, element)
        || dvar_push_back(list, name, element);
}

static void dvar_item_destroy(struct dvar_item *h)
{
    if (h)
    {
        dvar_item_destroy(h->next);
        free(h->data);
        free(h->name);
        free(h);
    }
}

void dvar_destroy(struct dvar *list)
{
    dvar_item_destroy(list->head);
    free(list);
}