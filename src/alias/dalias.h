#ifndef dalias_H
#define dalias_H

#include <stddef.h>

struct dalias_item
{
    char *name;
    char *data;
    struct dalias_item *next;
    struct dalias_item *prev;
};

struct dalias
{
    size_t size;
    struct dalias_item *head;
    struct dalias_item *tail;
};

// Threshold 1.
struct dalias *dalias_init(void);
void dalias_print(const struct dalias *list);
int dalias_push_front(struct dalias *list, char *name, char *element);
int dalias_push_back(struct dalias *list, char *name, char *element);
size_t dalias_size(const struct dalias *list);

// Threshold 2.
char *dalias_get(struct dalias *list, size_t index);
int dalias_insert_at(struct dalias *list, char *name, char *element, size_t index);
char *dalias_find(const struct dalias *list, char *name);
void dalias_remove_at(struct dalias *list, size_t index);
int dalias_remove_bname(struct dalias *list, char *name);

// Threshold 3.
void dalias_concat(struct dalias *list1, struct dalias *list2);
int dalias_add_alias(struct dalias *list, char *name, char *element);
int dalias_replace_alias(struct dalias *list, char *name, char *element);
void dalias_destroy(struct dalias *list);

#endif // dalias_H
