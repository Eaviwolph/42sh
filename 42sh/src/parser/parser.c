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
        t.op == LIONUMBER; // number juste before '>' or '<'
}

int is_redirection(struct token t)
{
    return t.op >= LGREAT && t.op <= LDLESS;
}

static const char *keyword_table[] = { "!",    "{",     "}",     "if",
                                       "in",   "fi",    "do",    "then",
                                       "else", "elif",  "done",  "case",
                                       "esac", "while", "until", "function" };

static int is_keyword(const struct token t)
{
    if (t.op == LWORD)
        for (int i = 0; i < KEYWORD_COUNT; ++i)
            if (!strcmp(t.val, keyword_table[i]))
                return 1;
    return 0;
}



static struct node *parse_compound_list(struct dtoken *parser)
{
    struct node *lhs;
    struct token tok, tok2;

    // eat newlines
    eat_newline();
    // parse andor
    lhs = parse_andor(parser);
    // looking for ';' or '&' or '\n
    tok = peak_token(parser);
    if (tok.op == LSEMI || tok.op == LSEPAND || tok.op == LNEWL)
    {
        get_token(parser);
        if (tok.op == LNEWL)
            show_prompt(TYPEIN_PS2);
        eat_newline();
        // check for and_or
        tok2 = peak_token(parser);
        // false condition
        if (tok2.op == LDSEMI || tok2.op == LPAC || tok2.op == LSEMI
            || tok2.op == LSEPAND || tok2.op == LEOF
            || (tok2.op == LWORD
                && (!strcmp(tok2.val, "}") || !strcmp(tok2.val, "do")
                    || !strcmp(tok2.val, "fi") || !strcmp(tok2.val, "done")
                    || !strcmp(tok2.val, "else") || !strcmp(tok2.val, "elif")
                    || !strcmp(tok2.val, "esac") || !strcmp(tok2.val, "then"))))
            return (tok.op == LSEMI || tok.op == LNEWL)
                ? lhs
                : tree_sepand_create(lhs, NULL);
        else
            return (tok.op == LSEMI || tok.op == LNEWL)
                ? tree_sep_create(lhs, parse_compound_list(parser))
                : tree_sepand_create(lhs, parse_compound_list(parser));
    }
    return lhs;
}

static void parse_redirection(struct dtoken *parser, struct node **reds)
{
    struct token token;
    long int fd = -1;
    enum red_type redtype;

    if (*reds == NULL)
        *reds = tree_red_create();
    // retrieve redirection fd if exist
    if ((token = peak_token(parser)).op == LIONUMBER)
    {
        get_token(parser);
        errno = 0;
        fd = strtol(token.val, NULL, 10);
        if (errno || fd < 0 || fd > FD_MAX)
            errx(1, "Error parsing");
    }
    // retrieve redirection type
    token = get_token(parser);
    switch (token.op)
    {
    case LGREAT:
        redtype = R_GREAT;
        if (fd == -1)
            fd = 1;
        break;
    case LDGREAT:
        redtype = R_DLESS;
        if (fd == -1)
            fd = 1;
        break;
    case LDLESSDASH:
        redtype = R_DLESSDASH;
        if (fd == -1)
            fd = 0;
        break;
    case LDLESS:
        redtype = R_DLESS;
        if (fd == -1)
            fd = 0;
        break;
    case LLESSGREAT:
        redtype = R_LESSGREAT;
        if (fd == -1)
            fd = 0;
        break;
    case LLESSAND:
        redtype = R_LESSAND;
        if (fd == -1)
            fd = 0;
        break;
    case LLESS:
        redtype = R_LESS;
        if (fd == -1)
            fd = 0;
        break;
    case LLOBBER:
        redtype = R_CLOBBER;
        if (fd == -1)
            fd = 1;
        break;
    case LGREATAND:
        redtype = R_GREATAND;
        if (fd == -1)
            fd = 1;
        break;
    default:
        errx(1, "Error parsing");
        redtype = 0; // to avoid warning about redtype may be unitialized
    }
    // retrieve redirection word
    token = get_token(parser);
    if (token.op == LWORD)
        tree_red_add(*reds, redtype, fd, token.val);
    else
        errx(1, "Error parsing");
}

static struct node *parse_funcdec(struct dtoken *parser)
{
    struct token tok;
    char *funcname;
    struct node *body;
    struct node *reds = NULL;

    tok = get_token(parser);
    if (tok.op == LWORD && !strcmp(tok.val, "function")) // WORD
    {
        free(tok.val);
        tok = get_token(parser);
    }
    if (tok.op != LWORD)
        errx(1, "Error parsing");
    funcname = tok.val;
    if (get_token(parser).op != LPAO) // (
        errx(1, "Error parsing");
    if (get_token(parser).op != LPAC) // )
        errx(1, "Error parsing");
    eat_newline(); // eat infinite \n
    body = parse_shellcommand(parser); // shell_command
    return tree_funcdec_create(funcname, body);
}

static struct node *parse_shellcommand(struct dtoken *t)
{
    struct token token;
    struct node *node;

    token = peak_token(t);
    if (!strcmp(token.val, "if")) // if
        node = parse_rule_if(t);
    else if (!strcmp(token.val, "for")) // for
        node = parse_rule_for(t);
    else if (!strcmp(token.val, "while")) // while
        node = parse_rule_while(t);
    else if (!strcmp(token.val, "until")) // until
        node = parse_rule_until(t);
    else if (!strcmp(token.val, "case")) // case
        node = parse_rule_case(t);
    else if (!strcmp(token.val, "{")) // {
    {
        get_token(t);
        node = parse_compound_list(t); // compound_list
        if ((token = get_token(t)).op != LWORD || strcmp(token.val, "}")) // }
            errx(1, "Error parsing");
    }
    else if (token.op == LPAO) // (
    {
        get_token(t);
        node = tree_subshell_create(parse_compound_list(t)); // complist
        if ((token = get_token(t)).op != LPAC) // )
            errx(1, "Error parsing");
    }
    else
        errx(1, "Error parsing");
    // parse redirection (because of command)
    struct token tok = peak_token(t);
    struct node *reds = NULL;
    while (is_redirection(tok))
        parse_redirection(t, &reds);
    if (reds) // if a redirection is caught
    {
        reds->data.rednode.mhs = node;
        node = reds;
    }
    return node;
}

static int parse_element(struct node *t, struct node *cmd, struct node **red)
{
    struct token token;
    int found = 0;
    int first = 1;

    for (;;)
    {
        token = peak_token(cmd);
        if (is_redirection(token))
        {
            parse_redirection(t, red);
            ++found;
        }
        else if (token.op == LWORD && first && !is_keyword(token))
        {
            first = 0;
            // FIXME: gestion des alias
            tree_cmd_add_argv(cmd, get_token(t).val);
            ++found;
        }
        else if (token.op == LWORD && !first)
            tree_cmd_add_argv(cmd, get_token(t).val);
        else
            break;
    }
    return found;
}

static int parse_prefix(struct node *t, struct node *cmd, struct node **red)
{
    struct token token;
    int found = 0;

    for (;;)
    {
        token = peak_token(t);
        if (is_redirection(token)) // redirection
        {
            parse_redirection(t, red);
            ++found;
        }
        else if (is_assignment(token)) // ASSIGNMENT_WORD
        {
            tree_cmd_add_prefix(cmd, get_token(t).val);
            ++found;
        }
        else
            break;
    }
    return found;
}

static struct node *parse_simple_command(struct dtoken *t)
{
    struct node *cmd;
    struct node *red = NULL;
    int found = 0;

    cmd = tree_cmd_create();
    // red holds the redirection tree
    found += parse_prefix(t, cmd, &red); // (prefix) + or (prefix)*
    found += parse_element(t, cmd, &red); // (element)+
    if (!found)
        errx(1, "Error Parsing");
    if (red)
    {
        // put in rednode in
        red->data.rednode.mhs = cmd;
        cmd = red;
    }
    return cmd;
}

struct node *parse_command(struct dtoken *t)
{
    struct token token;

    token = peak_token(t);
    if (is_shellcmd(token))
        return parse_shellcommand(t); // shell_command
    else if (token.op == LWORD
             && (!strcmp(token.val, "function") || peak_token_2(t).op == LPAO))
        return parse_funcdec(t); // funcdec
    else if (is_prefix(token) || token.op == LWORD)
        return parse_simplecommand(t); // simple_command
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