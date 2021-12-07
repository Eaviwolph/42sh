#ifndef DVAR_H
#define DVAR_H

#include <stddef.h>

struct dvar_item
{
    char *name;
    char *data;
    struct dvar_item *next;
    struct dvar_item *prev;
};

struct dvar
{
    size_t size;
    struct dvar_item *head;
    struct dvar_item *tail;
};

// Threshold 1.
struct dvar *dvar_init(void);
void dvar_print(const struct dvar *list);
int dvar_push_front(struct dvar *list, char *name, char *element);
int dvar_push_back(struct dvar *list, char *name, char *element);
size_t dvar_size(const struct dvar *list);

// Threshold 2.
char *dvar_get(struct dvar *list, size_t index);
int dvar_insert_at(struct dvar *list, char *name, char *element, size_t index);
char *dvar_find(const struct dvar *list, char *name);
void dvar_remove_at(struct dvar *list, size_t index);
void dvar_remove_elm(struct dvar *list, char *elm);

// Threshold 3.
void dvar_concat(struct dvar *list1, struct dvar *list2);
int dvar_add_var(struct dvar *list, char *name, char *element);
int dvar_replace_var(struct dvar *list, char *name, char *element);
void dvar_destroy(struct dvar *list);
struct dvar *dvar_split_at(struct dvar *list, size_t index);

#endif // dvar_H
