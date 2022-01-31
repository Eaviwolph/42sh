#ifndef DTOKEN_H
#define DTOKEN_H

#include <stddef.h>
#include "../alias/alias.h"

enum type
{
    LPAC, // )
    LPAO, // (

    LAND, // &&
    LOR, // ||

    LSEMI, // ;
    LDSEMI, // ;;
    LNEWL, // \n
    LPIPE, // |
    LSEPAND, // &
    LGREAT, // >
    LLESS, // <
    LGREATAND, // >&
    LLESSAND, // <&
    LDGREAT, // >>
    LLESSGREAT, // <>
    LLOBBER, // >|
    LDLESSDASH, // <<-
    LDLESS, // <<

    LIONUMBER, // io

    LWORD,
    LEOF,
};

struct token
{
    enum type op;
    char *val;
    int aliased;
};

struct dtoken_item
{
    struct token data;
    struct dtoken_item *next;
    struct dtoken_item *prev;
};

struct dtoken
{
    size_t size;
    size_t i;
    struct dtoken_item *head;
    struct dtoken_item *tail;
};

#include "../shell/shell.h"

// Threshold 1.
struct dtoken *dtoken_init(void);
int dtoken_push_front(struct dtoken *list, struct token element);
int dtoken_push_back(struct dtoken *list, struct token element);
struct token dtoken_remove_at(struct dtoken *list, size_t index);
void destroy_dtoken(struct dtoken *l);
struct dtoken *dtoken_add(struct dtoken *l, char *t);
void print_dtoken(struct dtoken *l);
struct token get_token(struct dtoken *list, struct dalias *s);
struct token peak_token(struct dtoken *list, struct dalias *s);
struct token peak_token_2(struct dtoken *list, struct dalias *s);
int is_end(struct dtoken *list, struct dalias *s);
void eat_newlines(struct dtoken *list);

#endif // dtoken_H
