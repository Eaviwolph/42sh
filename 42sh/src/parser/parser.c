#include "parser.h"

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/function.h"
#include "../common/macro.h"
#include "../tree/tree.h"
#include "dtoken.h"

struct token get_token(struct dtoken *list)
{
    return dtoken_remove_at(list, 0);
}

struct token peak_token(struct dtoken *list) // list musn't be empty!
{
    return list->head->data;
}

struct token peak_token_2(struct dtoken *list) // list musn't be empty!
{
    return list->head->next->data;
}

void eat_newlines(struct dtoken *list)
{
    while (list->head && list->head->data.op == LNEWL)
        dtoken_remove_at(list, 0);
}

int is_end(struct dtoken *list)
{
    if (!list->head)
        return 1;
    struct token t = peak_token(list);
    return t.op == LNEWL;
}

int is_shellcmd(struct token t)
{
    return t.op == LPAO || t.op == LFOR || t.op == LWHILE || t.op == LIF
        || t.op == LUNTIL || t.op == LACOO || t.op == LCASE;
}

int is_prefix(struct token t)
{
    return t.op == LDLESSDASH || // <<- HAHAH
        t.op == LDLESS || // <<
        t.op == LLESSGREAT || // <>
        t.op == LLESSAND || // <&
        t.op == LLESS || // <
        t.op == LDGREAT || // >>
        t.op == LGREATAND || // >&
        t.op == LLOBBER || // >|
        t.op == LGREAT || // >
        t.op == LIONUMBER || // number juste before '>' or '<'
        t.op == LWORD; // all others HIHI
}

struct node *parse_command(struct dtoken *t)
{
    struct token token;

    token = peak_token(t);
    if (is_shellcmd(token))
        return parse_shellcommand(t);
    else if (token.op == LWORD
             && (!strcmp(token.val, "function") || peak_token_2(t).op == LPAO))
        return parse_funcdec(t);
    else if (is_prefix(token))
        return parse_simplecommand(t);
    else
        errx(1, "Error parsing");
    assert(0);
    return NULL;
}

// rec aux of pipeline to process rec on ('|' ('\n')* command)*
static struct node *parse_pipeline_command(struct dtoken *t)
{
    struct token token;
    struct node *lhs;

    token = get_token(t);
    if (token.op != LPIPE) // needs to have a pipe !
        errx(1, "PARSE ERROR\n");
    eat_newlines(t); // eat infinite \n
    lhs = parse_command(t); // command
    token = peak_token(t);
    if (token.op == LPIPE)
        // if pipe / then : rec / else : done
        return tree_pipe_create(lhs, parse_pipeline_command(t));
    return lhs;
}

struct node *parse_pipeline(struct dtoken *t)
{
    int banged = 0;

    struct token token;
    token = peak_token(t);
    if (token.op == LWORD && !strcmp(token.val, "!")) // !
    {
        get_token(t);
        banged = 1;
    }
    struct node *lhs;
    lhs = parse_command(t); // command
    struct node *result;
    if (peak_token(t).op == LPIPE) // optional ( | ... )* doing rec on
                                   // ('|' ('\n')* command)*
        result = tree_pipe_create(lhs, parse_pipeline_command(t));
    else
        result = lhs;
    if (banged)
        return tree_bang_create(result);
    return result;
}

struct node *parse_and_or(struct dtoken *t)
{
    struct node *lhs;
    lhs = parse_pipeline(t); // pipeline
    struct token token;
    token = peak_token(t);
    if (token.op == LAND || token.op == LOR) // (('&&'|'||') ('\n')* pipeline)*
    { // rec
        get_token(t);
        eat_newlines(t); // (\n)*
        struct node *rhs;
        rhs = parse_and_or(t); // pipeline (recursive)
        if (token.op == LAND)
            return tree_and_create(lhs, rhs);
        else
            return tree_or_create(lhs, rhs);
    }
    return lhs;
}

struct node *parse_list(struct dtoken *t)
{
    struct node *left;
    left = parse_and_or(t); // and_or

    struct token middle = peak_token(t); // ((; | &) and_or)*
    if (middle.op == LSEMI || middle.op == LSEPAND)
    {
        middle = get_token(t);
        if (is_end(t)) // know if [; | &] or ((; | &) and_or)*
            return middle.op == LSEMI ? left : tree_sepand_create(left, NULL);
        struct node *right = parse_list(t); // very smart !! simplifies w/ rec
        if (middle.op == LSEMI)
            return tree_sep_create(left, right);
        else
            return tree_sepand_create(left, right);
    }

    return left;
}

struct node *parse_input(struct dtoken *tokens)
{
    if (!tokens)
        return NULL;
    struct token token;
    if (!tokens->head || peak_token(tokens).op == LNEWL) // \n EOF sole
    {
        token = get_token(tokens);
        return NULL;
    }
    struct node *buffer; // list
    buffer = parse_list(tokens);

    token = get_token(tokens); // \n EOF
    if (tokens->head && tokens->head->data.op != LNEWL)
        errx(1, "ERROR PARSE\n");
    return buffer;
}

struct node *parse(struct dtoken *tokens)
{
    return parse_input(tokens);
}