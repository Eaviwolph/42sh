#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dalias.h"

struct dalias *dalias_init(void)
{
    struct dalias *l = malloc(sizeof(struct dalias));
    if (l)
    {
        l->size = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}

void dalias_print(const struct dalias *list)
{
    struct dalias_item *h = list->head;
    while (h)
    {
        printf("%s = %s\n", h->name, h->data);
        h = h->next;
    }
}

char *dalias_find(const struct dalias *list, char *name)
{
    size_t i = 0;
    struct dalias_item *h = list->head;
    while (h && strcmp(h->name, name) != 0)
    {
        h = h->next;
        i++;
    }
    if (h)
        return h->data;
    return NULL;
}

int dalias_add_alias(struct dalias *list, char *name, char *element)
{
    return dalias_replace_alias(list, name, element)
        || dalias_push_back(list, name, element);
}

static void dalias_item_destroy(struct dalias_item *h)
{
    if (h)
    {
        dalias_item_destroy(h->next);
        free(h->data);
        free(h->name);
        free(h);
    }
}

void dalias_destroy(struct dalias *list)
{
    dalias_item_destroy(list->head);
    free(list);
}