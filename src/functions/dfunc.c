#include "dfunc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dfunc_replace_fun(struct dfunc *list, struct node_funcdec fun)
{
    size_t i = 0;
    struct dfunc_item *h = list->head;
    while (h && strcmp(h->fun.name, fun.name) != 0)
    {
        h = h->next;
        i++;
    }
    if (h)
    {
        tree_destroy(h->fun.body);
        free(h->fun.name);
        h->fun = fun;
        return 1;
    }
    return 0;
}

int dfunc_push_front(struct dfunc *list, struct node_funcdec fun)
{
    struct dfunc_item *i = malloc(sizeof(struct dfunc_item));
    if (i)
    {
        i->fun = fun;
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

int dfunc_push_back(struct dfunc *list, struct node_funcdec fun)
{
    struct dfunc_item *i = malloc(sizeof(struct dfunc_item));
    if (i)
    {
        i->fun = fun;
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

struct node_funcdec fundfunc_get(struct dfunc *list, size_t index)
{
    size_t i = 0;
    struct dfunc_item *h = list->head;
    while (h && i < index)
    {
        h = h->next;
        i++;
    }
    if (h && i == index)
        return h->fun;
    struct node_funcdec fun;
    fun.name = NULL;
    fun.body = NULL;
    return fun;
}

int dfunc_insert_at(struct dfunc *list, struct node_funcdec fun, size_t index)
{
    if (index == 0)
        return dfunc_push_front(list, fun);
    else if (index == list->size)
        return dfunc_push_back(list, fun);
    else if (index < list->size)
    {
        struct dfunc_item *e = malloc(sizeof(struct dfunc_item));
        if (e)
        {
            size_t i = 0;
            struct dfunc_item *h = list->head;
            while (h && i < index)
            {
                h = h->next;
                i++;
            }
            if (h && i == index)
            {
                e->fun = fun;
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

void dfunc_remove_at(struct dfunc *list, size_t index)
{
    size_t i = 0;
    struct dfunc_item *h = list->head;
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
        free(h);
        list->size--;
    }
}

void dfunc_concat(struct dfunc *list1, struct dfunc *list2)
{
    struct dfunc_item *end_1 = list1->tail;

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