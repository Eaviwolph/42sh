#ifndef DFUNC_H
#define DFUNC_H

#include <stddef.h>

#include "../tree/tree.h"

struct dfunc_item
{
    struct node_funcdec fun;
    struct dfunc_item *next;
    struct dfunc_item *prev;
};

struct dfunc
{
    size_t size;
    struct dfunc_item *head;
    struct dfunc_item *tail;
};

// Threshold 1.
struct dfunc *dfunc_init(void);
int dfunc_push_front(struct dfunc *list, struct node_funcdec fun);
int dfunc_push_back(struct dfunc *list, struct node_funcdec fun);
size_t dfunc_size(const struct dfunc *list);

// Threshold 2.
struct node_funcdec fundfunc_get(struct dfunc *list, size_t index);
int dfunc_insert_at(struct dfunc *list, struct node_funcdec fun, size_t index);
struct node_funcdec dfunc_find(const struct dfunc *list, char *name);
void dfunc_remove_at(struct dfunc *list, size_t index);

// Threshold 3.
void dfunc_concat(struct dfunc *list1, struct dfunc *list2);
int dfunc_add_fun(struct dfunc *list, struct node_funcdec fun);
int dfunc_replace_fun(struct dfunc *list, struct node_funcdec fun);
void dfunc_destroy(struct dfunc *list);

#endif // dfunc_H
