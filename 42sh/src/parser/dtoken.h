#ifndef DTOKEN_H
#define DTOKEN_H

#include <stddef.h>

enum type
{
    LPAC, // )
    LPAO, // (
    LACOC, // }
    LACOO, // {
    LBANG, // !

    LIF,  // if
    LTHEN,  // then
    LELSE, // else
    LFI, // fi

    LFOR, // for
    LIN, // in
    LDO, // do
    LDONE, // done
    LWHILE, // while

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

    LUNTIL, // until
    LCASE, // until
    LESAC, // esac

    // PUT IONUMBER HERE

    LWORD,
    LEOF,
};

struct token
{
    enum type op;
    char *val;
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
    struct dtoken_item *head;
    struct dtoken_item *tail;
};

// Threshold 1.
struct dtoken *dtoken_init(void);
int dtoken_push_front(struct dtoken *list, struct token element);
int dtoken_push_back(struct dtoken *list, struct token element);
struct token dtoken_remove_at(struct dtoken *list, size_t index);
void destroy_dtoken(struct dtoken *l);
struct dtoken *dtoken_add(struct dtoken *l, char *t);
void print_dtoken(struct dtoken *l);

#endif // dtoken_H
