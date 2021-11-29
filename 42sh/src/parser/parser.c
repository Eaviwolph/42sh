#include "parser.h"

#include <assert.h>
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

// rec aux of pipeline to process rec on ('|' ('\n')* command)*
static struct node *parse_pipeline_command(struct dtoken *t)
{
    struct token token;
    struct node *lhs;

    if ((token = get_token(t)).op != LPIPE) // needs to have a pipe !
        errx(1, "PARSE ERROR\n");
    eat_newline(t); // eat infinite \n
    lhs = parse_command(t); // command
    if ((token = peak_token(t)).op == LPIPE)
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
    token = peak_token(t);
    if (token.op == LPIPE) // optional ( | ... )* doing rec on
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
    token = get_token(t);
    if (token.op == LAND || token.op == LOR) // (('&&'|'||') ('\n')* pipeline)*
    { // rec
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
        if (middle.op == LSEMI) //
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
    if (!tokens->head || tokens->head->data.op == LNEWL) // \n EOF sole
        return NULL;

    struct node *buffer; // list
    buffer = parse_list(tokens);

    struct token token; // \n EOF
    token = get_token(tokens);
    if (tokens->head && tokens->head->data.op != LNEWL)
        printf("ERROR PARSE\n");
    return buffer;
}

struct node *parse(struct dtoken *tokens)
{
    return parse_input(tokens);
}