#include "dtoken.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dtoken *dtoken_init(void)
{
    struct dtoken *l = malloc(sizeof(struct dtoken));
    if (l)
    {
        l->size = 0;
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
    else if (strcmp(t, "in") == 0)
        return LIN;
    else if (strcmp(t, "until") == 0)
        return LUNTIL;
    else if (strcmp(t, "case") == 0)
        return LCASE;
    else if (strcmp(t, "esac") == 0)
        return LESAC;
    else if (strcmp(t, "<<-") == 0)
        return LDLESSDASH;
    else if (strcmp(t, "<<") == 0)
        return LDLESS;
    else
        return LWORD;
}

enum type char_to_type2(char *t)
{
    if (strcmp(t, "while") == 0)
        return LWHILE;

    else if (strcmp(t, "and") == 0)
        return LAND;
    else if (strcmp(t, "or") == 0)
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
    else if (strcmp(t, "{") == 0)
        return LACOO;
    else if (strcmp(t, "}") == 0)
        return LACOC;

    else if (strcmp(t, "if") == 0)
        return LIF;
    else if (strcmp(t, "then") == 0)
        return LTHEN;
    else if (strcmp(t, "else") == 0)
        return LELSE;
    else if (strcmp(t, "fi") == 0)
        return LFI;

    else if (strcmp(t, "for") == 0)
        return LFOR;
    else if (strcmp(t, "do") == 0)
        return LDO;
    else if (strcmp(t, "done") == 0)
        return LDONE;
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
    else if (e == LIN)
        printf("IN");
    else if (e == LUNTIL)
        printf("UNTIL");
    else if (e == LCASE)
        printf("LCASE");
    else if (e == LESAC)
        printf("LESAC");
    else if (e == LDLESSDASH)
        printf(".<<-");
    else if (e == LDLESS)
        printf(".<<");
    else
        printf("+%s+", t.val);
}

void print_tok2(struct token t)
{
    enum type e = t.op;
    if (e == LWHILE)
        printf("WHILE");

    else if (e == LAND)
        printf(".&&");
    else if (e == LOR)
        printf(".||");

    else if (e == LSEMI)
        printf(".;");
    else if (e == LDSEMI)
        printf(".;;");
    else if (e == LNEWL)
        printf("\n");
    else if (e == LPIPE)
        printf(".|");
    else if (e == LSEPAND)
        printf("&");
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
    else if (e == LACOO)
        printf("{");
    else if (e == LACOC)
        printf("}");

    else if (e == LIF)
        printf("IF");
    else if (e == LTHEN)
        printf("THEN");
    else if (e == LELSE)
        printf("ELSE");
    else if (e == LFI)
        printf("FI");

    else if (e == LFOR)
        printf("FOR");
    else if (e == LDO)
        printf("DO");
    else if (e == LDONE)
        printf("DONE");
    else
        print_tok2(t);
}

void print_dtoken(struct dtoken *l)
{
    struct dtoken_item *t = l->head;
    while (t)
    {
        print_tok(t->data);
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
