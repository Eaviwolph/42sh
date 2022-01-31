#include "dalias.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dalias_replace_alias(struct dalias *list, char *name, char *element)
{
    size_t i = 0;
    struct dalias_item *h = list->head;
    while (h && strcmp(h->name, name) != 0)
    {
        h = h->next;
        i++;
    }
    if (h)
    {
        free(name);
        free(h->data);
        h->data = element;
        return 1;
    }
    return 0;
}

int dalias_push_front(struct dalias *list, char *name, char *element)
{
    struct dalias_item *i = malloc(sizeof(struct dalias_item));
    if (i)
    {
        i->data = element;
        i->name = name;
        i->next = list->head;
        if (list->head)
            list->head->prev = i;
        if (!list->tail)
            list->tail = i;
        i->prev = NULL;
        list->head = i;
        list->size++;
        return 1;
    }
    return 0;
}

int dalias_push_back(struct dalias *list, char *name, char *element)
{
    struct dalias_item *i = malloc(sizeof(struct dalias_item));
    if (i)
    {
        i->data = element;
        i->name = name;
        i->prev = list->tail;
        if (list->tail)
            list->tail->next = i;
        if (!list->head)
            list->head = i;
        i->next = NULL;
        list->tail = i;
        list->size++;
        return 1;
    }
    return 0;
}

char *dalias_get(struct dalias *list, size_t index)
{
    size_t i = 0;
    struct dalias_item *h = list->head;
    while (h && i < index)
    {
        h = h->next;
        i++;
    }
    if (h && i == index)
        return h->data;
    return NULL;
}

int dalias_insert_at(struct dalias *list, char *name, char *element,
                     size_t index)
{
    if (index == 0)
        return dalias_push_front(list, name, element);
    else if (index == list->size)
        return dalias_push_back(list, name, element);
    else if (index < list->size)
    {
        struct dalias_item *e = malloc(sizeof(struct dalias_item));
        if (e)
        {
            size_t i = 0;
            struct dalias_item *h = list->head;
            while (h && i < index)
            {
                h = h->next;
                i++;
            }
            if (h && i == index)
            {
                e->data = element;
                e->name = name;
                h->prev->next = e;
                e->next = h;
                e->prev = h->prev;
                h->prev = e;
                list->size++;
                return 1;
            }
        }
    }
    return 0;
}

void dalias_remove_at(struct dalias *list, size_t index)
{
    size_t i = 0;
    struct dalias_item *h = list->head;
    while (h && i < index)
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

int dalias_remove_bname(struct dalias *list, char *name)
{
    struct dalias_item *h = list->head;
    while (h && strcmp(h->name, name) != 0)
    {
        h = h->next;
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
        return 1;
    }
    return 0;
}

void dalias_concat(struct dalias *list1, struct dalias *list2)
{
    struct dalias_item *end_1 = list1->tail;

    list1->tail = list2->tail;
    if (end_1)
        end_1->next = list2->head;
    if (list2->head)
        list2->head->prev = end_1;

    list1->size += list2->size;

    list2->head = NULL;
    list2->tail = NULL;
    list2->size = 0;
}
