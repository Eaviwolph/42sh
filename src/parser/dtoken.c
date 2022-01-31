#include "dtoken.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

void print_tok(struct token t);

struct dtoken *dtoken_init(void)
{
    struct dtoken *l = malloc(sizeof(struct dtoken));
    if (l)
    {
        l->size = 0;
        l->i = 0;
        l->head = NULL;
        l->tail = NULL;
    }
    return l;
}

int dtoken_push_front(struct dtoken *list, struct token element)
{
    struct dtoken_item *i = malloc(sizeof(struct dtoken_item));
    if (i)
    {
        i->data = element;
        i->next = list->head;
        if (list->head)
            list->head->prev = i;
        if (!list->tail)
            list->tail = i;
        i->prev = NULL;
        i->data.aliased = 0;
        list->head = i;
        list->size++;
        return 1;
    }
    return 0;
}

int dtoken_push_back(struct dtoken *list, struct token element)
{
    struct dtoken_item *i = malloc(sizeof(struct dtoken_item));
    if (i)
    {
        i->data = element;
        i->prev = list->tail;
        if (list->tail)
            list->tail->next = i;
        if (!list->head)
            list->head = i;
        i->next = NULL;
        i->data.aliased = 0;
        list->tail = i;
        list->size++;
        return 1;
    }
    return 0;
}

struct token dtoken_remove_at(struct dtoken *list, size_t index)
{
    size_t i = 0;
    struct dtoken_item *h = list->head;
    while (h && i < index)
    {
        h = h->next;
        i++;
    }
    struct token tok;
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
        tok = h->data;
        free(h);
        list->size--;
    }
    return tok;
}

void eat_newlines(struct dtoken *list)
{
    struct dtoken_item *h = list->head;
    size_t i = 0;
    while (h && i < list->i)
    {
        h = h->next;
        i++;
    }
    while (h && h->data.op == LNEWL)
    {
        h = h->next;
        list->i++;
    }
}

static int is_unalias(struct dtoken_item *h)
{
    while (h && h->prev && h->prev->data.op == LWORD)
    {
        h = h->prev;
    }
    if (h && strcmp(h->data.val, "unalias") == 0)
    {
        return 1;
    }
    return 0;
}

struct dtoken *rep_tok_alias(struct dtoken *list, struct dalias *s)
{
    size_t i = 0;
    struct dtoken_item *h = list->head;
    while (h && i < list->i)
    {
        h = h->next;
        i++;
    }
    if (h && is_unalias(h))
    {
        h->data.aliased = 1;
    }
    if (h && !h->data.aliased)
    {
        char *al = dalias_find(s, h->data.val);
        if (al)
        {
            struct dtoken *d = dtoken_init();
            char quoted = '\0';
            d = str_to_dtoken(d, al, &quoted);
            struct dtoken_item *h2 = d->head;
            while (h2)
            {
                h2->data.aliased = 1;
                h2 = h2->next;
            }
            if (d->size)
            {
                if (h->prev)
                    h->prev->next = d->head;
                else
                    list->head = d->head;
                d->head->prev = h->prev;
                if (h->next)
                    h->next->prev = d->tail;
                else
                    list->tail = d->tail;
                d->tail->next = h->next;
                list->size += d->size - 1;
                free(h->data.val);
                free(h);
                free(d);
            }
            else
            {
                struct token tok = dtoken_remove_at(list, i);
                free(tok.val);
                free(d);
            }
        }
    }
    return list;
}

struct token peak_token_2(struct dtoken *list, struct dalias *s)
{
    list = rep_tok_alias(list, s);
    size_t i = 0;
    struct dtoken_item *h = list->head;
    while (h && i < list->i)
    {
        h = h->next;
        i++;
    }
    if (h && h->next)
    {
        return h->next->data;
    }
    struct token t;
    t.op = LEOF;
    t.val = NULL;
    return t;
}

struct token peak_token(struct dtoken *list, struct dalias *s)
{
    list = rep_tok_alias(list, s);
    size_t i = 0;
    struct dtoken_item *h = list->head;
    while (h && i < list->i)
    {
        h = h->next;
        i++;
    }
    if (h)
        return h->data;
    struct token t;
    t.op = LEOF;
    t.val = NULL;
    return t;
}

struct token get_token(struct dtoken *list, struct dalias *s)
{
    list = rep_tok_alias(list, s);
    size_t i = 0;
    struct dtoken_item *h = list->head;
    while (h && i < list->i)
    {
        h = h->next;
        i++;
    }
    list->i++;
    if (h)
        return h->data;
    struct token t;
    t.op = LEOF;
    t.val = NULL;
    return t;
}

int is_end(struct dtoken *list, struct dalias *s)
{
    list = rep_tok_alias(list, s);
    struct token t = peak_token(list, s);
    if (t.op == LEOF)
        return 1;
    return t.op == LNEWL;
}

enum type char_to_type3(char *t)
{
    if (strcmp(t, "<&") == 0)
        return LLESSAND;
    else if (strcmp(t, ">>") == 0)
        return LDGREAT;
    else if (strcmp(t, "<>") == 0)
        return LLESSGREAT;
    else if (strcmp(t, ">|") == 0)
        return LLOBBER;
    else if (strcmp(t, "<<-") == 0)
        return LDLESSDASH;
    else if (strcmp(t, "<<") == 0)
        return LDLESS;
    else
        return LWORD;
}

enum type char_to_type2(char *t)
{
    if (strcmp(t, "&&") == 0)
        return LAND;
    else if (strcmp(t, "||") == 0)
        return LOR;

    else if (strcmp(t, ";") == 0)
        return LSEMI;
    else if (strcmp(t, ";;") == 0)
        return LDSEMI;
    else if (strcmp(t, "\n") == 0)
        return LNEWL;
    else if (strcmp(t, "|") == 0)
        return LPIPE;
    else if (strcmp(t, "&") == 0)
        return LSEPAND;
    else if (strcmp(t, ">") == 0)
        return LGREAT;
    else if (strcmp(t, "<") == 0)
        return LLESS;
    else if (strcmp(t, ">&") == 0)
        return LGREATAND;
    else
        return char_to_type3(t);
}

enum type char_to_type(char *t)
{
    if (strcmp(t, ")") == 0)
        return LPAC;
    else if (strcmp(t, "(") == 0)
        return LPAO;
    else
        return char_to_type2(t);
}

void print_tok3(struct token t)
{
    enum type e = t.op;
    if (e == LLESSAND)
        printf(".<&");
    else if (e == LDGREAT)
        printf(".>>");
    else if (e == LLESSGREAT)
        printf(".<>");
    else if (e == LLOBBER)
        printf(".>|");
    else if (e == LDLESSDASH)
        printf(".<<-");
    else if (e == LDLESS)
        printf(".<<");
    else if (e == LEOF)
        printf(".EOF\n");
    else if (e == LIONUMBER)
        printf("IO_%s_IO", t.val);
    else
        printf("+%s+", t.val);
}

void print_tok2(struct token t)
{
    enum type e = t.op;

    if (e == LAND)
        printf(".&&");
    else if (e == LOR)
        printf(".||");

    else if (e == LSEMI)
        printf(".;");
    else if (e == LDSEMI)
        printf(".;;");
    else if (e == LNEWL)
        printf("NEWL ");
    else if (e == LPIPE)
        printf(".|");
    else if (e == LSEPAND)
        printf(".&");
    else if (e == LGREAT)
        printf(".>");
    else if (e == LLESS)
        printf(".<");
    else if (e == LGREATAND)
        printf(".>&");
    else
        print_tok3(t);
}

void print_tok(struct token t)
{
    enum type e = t.op;
    if (e == LPAC)
        printf(")");
    else if (e == LPAO)
        printf("(");
    else
        print_tok2(t);
}

void print_dtoken(struct dtoken *l)
{
    struct dtoken_item *t = l->head;
    while (t)
    {
        print_tok(t->data);
        if (t->data.op != LNEWL && t->data.op != LEOF)
            printf(" ");
        t = t->next;
    }
}

struct dtoken *dtoken_add(struct dtoken *l, char *t)
{
    struct token e;
    e.val = t;
    e.op = char_to_type(t);
    dtoken_push_back(l, e);
    return l;
}

void destroy_dtoken_item(struct dtoken_item *l)
{
    if (l)
    {
        destroy_dtoken_item(l->next);
        free(l->data.val);
        free(l);
    }
}

void destroy_dtoken(struct dtoken *l)
{
    destroy_dtoken_item(l->head);
    free(l);
}
