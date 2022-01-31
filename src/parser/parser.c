#include "parser.h"

#include <assert.h>
#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/function.h"
#include "../common/macro.h"
#include "../shell/shell.h"
#include "../tree/tree.h"
#include "dtoken.h"

int is_shellcmd(struct token token)
{
    return token.op == LPAO
        || (token.op == LWORD
            && (!strcmp(token.val, "for") || !strcmp(token.val, "while")
                || !strcmp(token.val, "if") || !strcmp(token.val, "until")
                || !strcmp(token.val, "{") || !strcmp(token.val, "case")));
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
    return (t.op >= LGREAT && t.op <= LDLESS) || t.op == LIONUMBER;
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

static struct node *parse_compound_list(struct dtoken *parser,
                                        struct dalias *s);
struct node *parse_and_or(struct dtoken *t, struct dalias *s);
static struct node *parse_shell_command(struct dtoken *t, struct dalias *s);

static void parse_case_item(struct dtoken *parser, struct node *casenode,
                            struct dalias *s)
{
    struct token tok;
    char **pattern = NULL;
    struct node *exec = NULL;

    tok = get_token(parser, s);
    // check for a '(' before pattern list
    if (tok.op == LPAO)
        tok = get_token(parser, s);
    // retrieve pattern list
    if (tok.op != LWORD)
        errx(2, "Parse Error 6");
    pattern = string_array_append(pattern, tok.val);
    while ((tok = peak_token(parser, s)).op == LPIPE)
    {
        get_token(parser, s);
        if ((tok = get_token(parser, s)).op != LWORD)
            errx(2, "Parse Error 7");
        pattern = string_array_append(pattern, tok.val);
    }
    // check for ')'
    if ((tok = get_token(parser, s)).op != LPAC)
        errx(2, "Parse Error 8");
    // eat newline
    eat_newlines(parser);
    if ((tok = peak_token(parser, s)).op != LDSEMI
        && !(tok.op == LWORD && !strcmp(tok.val, "esac")))
        exec = parse_compound_list(parser, s);
    tree_case_add_item(casenode, pattern, exec);
}

static void parse_case_clause(struct dtoken *parser, struct node *casenode,
                              struct dalias *s)
{
    struct token tok;

    do
    {
        parse_case_item(parser, casenode, s);
        tok = peak_token(parser, s);
        if (tok.op == LDSEMI)
        {
            get_token(parser, s);
            eat_newlines(parser);
            tok = peak_token(parser, s);
        }
        if (tok.op == LWORD && !strcmp(tok.val, "esac"))
            return;
    } while (1);
}

static struct node *parse_do_group(struct dtoken *parser, struct dalias *s)
{
    struct token tok;
    struct node *exec;

    // do
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "do"))
        errx(2, "Parse Error 9");
    // exec part
    exec = parse_compound_list(parser, s);
    // done
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "done"))
        errx(2, "Parse Error 10");
    return exec;
}

static struct node *parse_else_clause(struct dtoken *parser, struct dalias *s)
{
    struct token tok;

    tok = get_token(parser, s);
    if (tok.op == LWORD && !strcmp(tok.val, "else"))
    {
        return parse_compound_list(parser, s);
    }
    else if (tok.op == LWORD && !strcmp(tok.val, "elif"))
    {
        struct node *cond, *cond_true, *cond_false;

        // if
        cond = parse_compound_list(parser, s);
        // then
        tok = get_token(parser, s);
        if (tok.op != LWORD || strcmp(tok.val, "then"))
            errx(2, "Parse Error 11");
        cond_true = parse_compound_list(parser, s);
        // elses
        tok = peak_token(parser, s);
        if (tok.op == LWORD
            && (!strcmp(tok.val, "else") || !strcmp(tok.val, "elif")))
            cond_false = parse_else_clause(parser, s);
        else
            cond_false = NULL;
        return tree_if_create(cond, cond_true, cond_false);
    }
    else
        errx(2, "Parse Error 12");
    assert(0);
    return NULL;
}

static struct node *parse_rule_if(struct dtoken *parser, struct dalias *s)
{
    struct token tok;
    struct node *cond;
    struct node *cond_true;
    struct node *cond_false;

    // if
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "if"))
        errx(2, "Parse Error 1");
    cond = parse_compound_list(parser, s);
    // then
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "then"))
        errx(2, "Parse Error 2");
    cond_true = parse_compound_list(parser, s);
    // elses
    tok = peak_token(parser, s);
    if (tok.op == LWORD
        && (!strcmp(tok.val, "else") || !strcmp(tok.val, "elif")))
        cond_false = parse_else_clause(parser, s);
    else
        cond_false = NULL;
    // fi
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "fi"))
        errx(2, "Parse Error 3");
    // create if node
    return tree_if_create(cond, cond_true, cond_false);
}
static struct node *parse_rule_case(struct dtoken *parser, struct dalias *s)
{
    struct token tok;
    struct node *casenode = NULL; // NULL if no case_clause
    char *varname;

    // check for token 'case'
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "case"))
        errx(2, "Parse Error 13");
    // get varname
    if ((tok = get_token(parser, s)).op != LWORD)
        errx(2, "Parse Error 14");
    varname = tok.val;
    // eat newline
    eat_newlines(parser);
    // check for token 'in'
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "in"))
        errx(2, "Parse Error 15");
    // eat newline
    eat_newlines(parser);
    // parse case body
    tok = peak_token(parser, s);
    if ((tok.op == LWORD && strcmp(tok.val, "esac")) || tok.op == LPAO)
    {
        casenode = tree_case_create(varname);
        parse_case_clause(parser, casenode, s);
    }
    // check for token 'esac'
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "esac"))
        errx(2, "Parse Error 16");
    return casenode;
}

static struct node *parse_rule_until(struct dtoken *parser, struct dalias *s)
{
    struct node *cond;
    struct token tok;

    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "until")) // until
        errx(2, "Error Parsing 17");
    cond = tree_bang_create(parse_compound_list(parser, s)); // inverse
    return tree_while_create(cond, parse_do_group(parser, s)); // while
}

static struct node *parse_rule_while(struct dtoken *parser, struct dalias *s)
{
    struct node *cond;
    struct token tok;

    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "while")) // while
        errx(2, "Parse Error 18");
    cond = parse_compound_list(parser, s); // condition
    return tree_while_create(cond, parse_do_group(parser, s)); // do_group
}

static struct node *parse_rule_for(struct dtoken *parser, struct dalias *s)
{
    struct token tok;
    char *varname;
    char **values = NULL;

    // for
    tok = get_token(parser, s);
    if (tok.op != LWORD || strcmp(tok.val, "for"))
        errx(2, "Parsing Error 19");
    // varname
    tok = get_token(parser, s);
    if (tok.op != LWORD)
        errx(2, "Parsing Error 20");
    varname = tok.val;
    // eat infinite newlines
    eat_newlines(parser);
    // check for in
    if ((tok = peak_token(parser, s)).op == LWORD && !strcmp(tok.val, "in"))
    {
        tok = get_token(parser, s);
        do
        { // add each word into "values"
            ;
            if (peak_token(parser, s).op == LNEWL)
                break;
            if ((tok = get_token(parser, s)).op != LWORD)
                errx(2, "Parsing Error 21");
            values = string_array_append(values, tok.val);
        } while ((tok = peak_token(parser, s)).op == LWORD);
        // check for ';' or '\n'
        if ((tok = get_token(parser, s)).op != LSEMI && tok.op != LNEWL)
            errx(2, "Parsing Error 22");
        // eat infinite newlines
        eat_newlines(parser);
    }
    // parse the command
    return tree_for_create(varname, values, parse_do_group(parser, s));
}

static struct node *parse_compound_list(struct dtoken *parser, struct dalias *s)
{
    struct node *lhs;
    struct token tok, tok2;

    // eat infinite newlines
    eat_newlines(parser);
    // parse and_or
    lhs = parse_and_or(parser, s);
    // looking for ';' or '&' or '\n
    tok = peak_token(parser, s);
    if (tok.op == LSEMI || tok.op == LSEPAND || tok.op == LNEWL)
    {
        get_token(parser, s);
        if (tok.op == LNEWL)
        {
            // printf("MAKE PROMPT.C>");
            // fflush(stdout); // show_prompt(parser);
        }
        // eat infinite newlines
        eat_newlines(parser);
        // check for and_or
        tok2 = peak_token(parser, s);
        // false condition
        if (tok2.op == LDSEMI || tok2.op == LPAC || tok2.op == LSEMI
            || tok2.op == LSEPAND || tok2.op == LEOF
            || (tok2.op == LWORD
                && (strcmp(tok2.val, "function") && is_keyword(tok2))))
            return (tok.op == LSEMI || tok.op == LNEWL) // new line = new tree
                ? lhs
                : tree_sepand_create(lhs, NULL);
        else // smart recursion
            return (tok.op == LSEMI || tok.op == LNEWL)
                ? tree_sep_create(lhs, parse_compound_list(parser, s))
                : tree_sepand_create(lhs, parse_compound_list(parser, s));
    }
    return lhs;
}

static void parse_redirection(struct dtoken *parser, struct node **reds,
                              struct dalias *s)
{
    struct token token;
    long int fd = -1;
    enum red_type redtype;

    // setup reds to be able to hold redirections
    if (*reds == NULL)
        *reds = tree_red_create();
    // IONUMBER
    if ((token = peak_token(parser, s)).op == LIONUMBER)
    {
        get_token(parser, s);
        errno = 0;
        fd = strtol(token.val, NULL, 10);
        if (errno || fd < 0 || fd > FD_MAX)
            errx(2, "Error parsing 24");
    }
    // redirection name '<<' >' '|>'...
    token = get_token(parser, s);
    switch (token.op)
    {
    case LGREAT:
        redtype = R_GREAT;
        if (fd == -1)
            fd = 1;
        break;
    case LDGREAT:
        redtype = R_DGREAT;
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
        errx(2, "Error parsing 25");
        redtype = 0; // to avoid warning about redtype may be unitialized
    }
    // word
    token = get_token(parser, s);

    if (token.op == LWORD)
        tree_red_add(*reds, redtype, fd, token.val);
    else
        errx(2, "Error parsing 26");
}

static struct node *parse_funcdec(struct dtoken *parser, struct dalias *s)
{
    struct token tok;
    char *funcname;
    struct node *body;

    tok = get_token(parser, s);
    if (tok.op == LWORD && !strcmp(tok.val, "function")) // WORD
    {
        tok = get_token(parser, s);
    }
    if (tok.op != LWORD)
        errx(2, "Error parsing 27");
    funcname = tok.val;
    if (get_token(parser, s).op != LPAO) // (
        errx(2, "Error parsing 28");
    if (get_token(parser, s).op != LPAC) // )
        errx(2, "Error parsing 29");
    eat_newlines(parser); // eat infinite \n
    body = parse_shell_command(parser, s); // shell_command
    return tree_funcdec_create(funcname, body);
}

static struct node *parse_shell_command(struct dtoken *t, struct dalias *s)
{
    struct token token;
    struct node *node;

    token = peak_token(t, s);
    if (!strcmp(token.val, "if")) // if
        node = parse_rule_if(t, s);
    else if (!strcmp(token.val, "for")) // for
        node = parse_rule_for(t, s);
    else if (!strcmp(token.val, "while")) // while
        node = parse_rule_while(t, s);
    else if (!strcmp(token.val, "until")) // until
        node = parse_rule_until(t, s);
    else if (!strcmp(token.val, "case")) // case
        node = parse_rule_case(t, s);
    else if (!strcmp(token.val, "{")) // {
    {
        get_token(t, s);
        node = parse_compound_list(t, s); // compound_list
        if ((token = get_token(t, s)).op != LWORD
            || strcmp(token.val, "}")) // }
            errx(2, "Error parsing 30");
    }
    else if (token.op == LPAO) // (
    {
        get_token(t, s);
        node = tree_subshell_create(parse_compound_list(t, s)); // complist
        if ((token = get_token(t, s)).op != LPAC) // )
            errx(2, "Error parsing 31");
    }
    else
        errx(2, "Error parsing 32");
    // parse redirection (because of command)
    struct token tok = peak_token(t, s);
    struct node *reds = NULL;
    while (is_redirection(tok))
        parse_redirection(t, &reds, s);
    if (reds) // if a redirection is caught
    {
        reds->data.rednode.mhs = node;
        node = reds;
    }
    return node;
}

static int parse_element(struct dtoken *t, struct node *cmd, struct node **red,
                         struct dalias *s)
{
    struct token token;
    int found = 0;
    int first = 1;

    for (;;)
    {
        token = peak_token(t, s);
        if (is_redirection(token))
        {
            parse_redirection(t, red, s);
            ++found;
        }
        else if (token.op == LWORD && first && !is_keyword(token))
        {
            first = 0;
            // FIXME: gestion des alias
            tree_cmd_argv(cmd, get_token(t, s).val);
            ++found;
        }
        else if (token.op == LWORD && !first)
            tree_cmd_argv(cmd, get_token(t, s).val);
        else
            break;
    }
    return found;
}

#define is_var_assignment(t)                                                   \
    ((*(t).val != '=') && (strchr((t).val, '=') != NULL))

static int parse_prefix(struct dtoken *t, struct node *cmd, struct node **red,
                        struct dalias *s)
{
    struct token token;
    int found = 0;

    for (;;)
    {
        token = peak_token(t, s);
        if (is_redirection(token)) // redirection
        {
            parse_redirection(t, red, s);
            ++found;
        }
        else if (is_var_assignment(token)) // ASSIGNMENT_WORD
        {
            tree_cmd_pref(cmd, get_token(t, s).val);
            ++found;
        }
        else
            break;
    }
    return found;
}

static struct node *parse_simple_command(struct dtoken *t, struct dalias *s)
{
    struct node *cmd;
    struct node *red = NULL;
    int found = 0;

    cmd = tree_cmd_create();
    // red holds the redirection tree
    found += parse_prefix(t, cmd, &red, s); // (prefix) + or (prefix)*
    found += parse_element(t, cmd, &red, s); // (element)+
    if (!found)
        errx(2, "Error Parsing 35");
    if (red)
    {
        // put in rednode in
        red->data.rednode.mhs = cmd;
        cmd = red;
    }
    return cmd;
}

struct node *parse_command(struct dtoken *t, struct dalias *s)
{
    struct token token;

    token = peak_token(t, s);
    if (is_shellcmd(token))
        return parse_shell_command(t, s); // shell_command
    else if (token.op == LWORD
             && (!strcmp(token.val, "function")
                 || peak_token_2(t, s).op == LPAO))
        return parse_funcdec(t, s); // funcdec
    else if (is_prefix(token) || token.op == LWORD)
        return parse_simple_command(t, s); // simple_command
    else
        errx(2, "Error parsing 36");
    assert(0);
    return NULL;
}

// rec aux of pipeline to process rec on ('|' ('\n')* command)*
static struct node *parse_pipeline_command(struct dtoken *t, struct dalias *s)
{
    struct token token;
    struct node *lhs;

    token = get_token(t, s);
    if (token.op != LPIPE) // needs to have a pipe !
        errx(2, "PARSE ERROR\n");
    eat_newlines(t); // eat infinite \n
    lhs = parse_command(t, s); // command
    token = peak_token(t, s);
    if (token.op == LPIPE)
        // if pipe / then : rec / else : done
        return tree_pipe_create(lhs, parse_pipeline_command(t, s));
    return lhs;
}

struct node *parse_pipeline(struct dtoken *t, struct dalias *s)
{
    int banged = 0;

    struct token token;
    token = peak_token(t, s);
    if (token.op == LWORD && !strcmp(token.val, "!")) // !
    {
        get_token(t, s);
        banged = 1;
    }
    struct node *lhs;
    lhs = parse_command(t, s); // command
    struct node *result;
    if (peak_token(t, s).op == LPIPE) // optional ( | ... )* doing rec on
                                      // ('|' ('\n')* command)*
        result = tree_pipe_create(lhs, parse_pipeline_command(t, s));
    else
        result = lhs;
    if (banged)
        return tree_bang_create(result);
    return result;
}

struct node *parse_and_or(struct dtoken *t, struct dalias *s)
{
    struct node *lhs;
    lhs = parse_pipeline(t, s); // pipeline
    struct token token;
    token = peak_token(t, s);
    if (token.op == LAND || token.op == LOR) // (('&&'|'||') ('\n')* pipeline)*
    { // rec
        get_token(t, s);
        eat_newlines(t); // (\n)*
        struct node *rhs;
        rhs = parse_and_or(t, s); // pipeline (recursive)
        if (token.op == LAND)
            return tree_and_create(lhs, rhs);
        else
            return tree_or_create(lhs, rhs);
    }
    return lhs;
}

struct node *parse_list(struct dtoken *t, struct dalias *s)
{
    struct node *left;
    left = parse_and_or(t, s); // and_or

    struct token middle = peak_token(t, s); // ((; | &) and_or)*
    if (middle.op == LSEMI || middle.op == LSEPAND)
    {
        middle = get_token(t, s);
        if (is_end(t, s)) // know if [; | &] or ((; | &) and_or)*
            return middle.op == LSEMI ? left : tree_sepand_create(left, NULL);
        struct node *right =
            parse_list(t, s); // very smart !! simplifies w/ rec
        if (middle.op == LSEMI)
            return tree_sep_create(left, right);
        else
            return tree_sepand_create(left, right);
    }

    return left;
}

struct node *parse_input(struct dtoken *tokens, struct dalias *s)
{
    if (!tokens)
        return NULL;
    if (peak_token(tokens, s).op == LEOF
        || peak_token(tokens, s).op == LNEWL) // \n EOF sole
    {
        get_token(tokens, s);
        return NULL;
    }
    struct node *buffer; // list
    buffer = parse_list(tokens, s);

    struct token t = peak_token(tokens, s); // \n EOF
    if (t.op != LEOF && t.op != LNEWL)
        errx(2, "Error parsing 40");
    return buffer;
}

struct node *parse(struct dtoken *tokens, struct dalias *s)
{
    eat_newlines(tokens);
    struct node *r = parse_input(tokens, s);
    return r;
}