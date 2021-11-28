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
#include "../shell/shell.h"
#include "getline.h"

static struct node *regnode(struct parser *parser, struct node *node);

/*!
** Parse an input, following the Grammar rule input
** input:       list '\n'
**		list EOF
**		| '\n'
**		| EOF
**
** @param parser parser struct
**
** @return parent ast node, for execution
*/
static struct node *parse_input(struct parser *parser);
static struct node *parse_list(struct parser *parser);
static struct node *parse_andor(struct parser *parser);
static struct node *parse_pipeline(struct parser *parser);
static struct node *parse_command(struct parser *parser);
static struct node *parse_simplecommand(struct parser *parser);
static struct node *parse_shellcommand(struct parser *parser);
static struct node *parse_rulefor(struct parser *parser);
static struct node *parse_rulewhile(struct parser *parser);
static struct node *parse_ruleuntil(struct parser *parser);
static struct node *parse_ruleif(struct parser *parser);
static struct node *parse_rulecase(struct parser *parser);
static struct node *parse_compound_list(struct parser *parser);
static struct node *parse_pipeline_command(struct parser *parser);
static struct node *parse_funcdec(struct parser *parser);
static struct node *parse_elseclause(struct parser *parser);
static struct node *parse_dogroup(struct parser *parser);
static void parse_caseclause(struct parser *parser, struct node *casenode);
static void parse_caseitem(struct parser *parser, struct node *casenode);
static int parse_prefix(struct parser *parser, struct node *cmd, struct node **red);
static int parse_element(struct parser *parser, struct node *cmd, struct node **red);
static void parse_redirection(struct parser *parser, struct node **reds);
static int is_keyword(const struct token t);

/*!
** Notify a parse error
**
** @param parser parser where error appear
** @param t token near of the error
*/
static void parse_error(struct parser *parser, struct token t);

/*
** ===========
** MACROS
** ===========
*/

#if DEBUG_PARSER == 1
#    define debugmsg(msg) fprintf(stderr, "debug: %s\n", (msg))
#else
#    define debugmsg(msg)
#endif

#define is_assignment(t) ((*(t).str != '=') && (strchr((t).str, '=') != NULL))

#define eat_newline()                                                          \
    while (lexer_lookahead(parser->lexer).id == LNEWL)                   \
    {                                                                          \
        lexer_gettoken(parser->lexer);                                         \
        show_prompt(TYPEIN_PS2);                                               \
    }

/*
** ===========
** DEFINITIONS
** ===========
*/

static const struct token keyword_table[] = {
    { LWORD, "!", 1 },     { LWORD, "{", 1 },
    { LWORD, "}", 1 },     { LWORD, "if", 2 },
    { LWORD, "in", 2 },    { LWORD, "fi", 2 },
    { LWORD, "do", 2 },    { LWORD, "then", 4 },
    { LWORD, "else", 4 },  { LWORD, "elif", 4 },
    { LWORD, "done", 4 },  { LWORD, "case", 4 },
    { LWORD, "esac", 4 },  { LWORD, "while", 5 },
    { LWORD, "until", 5 }, { LWORD, "function", 8 }
};

struct parser *parser_init(int fd)
{
    struct parser *new;

    safe_malloc(new, sizeof(struct parser));
    new->lexer = lexer_init(fd);
    new->error = 0;
    new->regnodes = NULL;
    new->regsize = new->regpos = 0;
    return new;
}

static struct node *regnode(struct parser *parser, struct node *node)
{
    if (!node)
        return node;
    if (parser->regpos >= parser->regsize)
    {
        parser->regsize += 50;
        safe_realloc(parser->regnodes, parser->regnodes,
                   parser->regsize * sizeof(struct node));
    }
    parser->regnodes[parser->regpos] = node;
    ++parser->regpos;
    return node;
}

static void parse_error(struct parser *parser, struct token t)
{
    if (t.id == LEOF)
        fprintf(stderr, "%s: syntax error: unexpected end of file.\n",
                shell->name);
    else
        fprintf(stderr, "%s: syntax error near unexpected token `%s'.\n",
                shell->name, t.str);
    parser->error = 1;
    shell->status = ERROR_ONPARSING;
    if (parser->regnodes)
        for (register int i = 0; parser->regnodes[i]; ++i)
            ast_destruct_node(parser->regnodes[i]);
    lexer_flush(parser->lexer);
    longjmp(parser->stack, 1);
}

struct node *parse(struct parser *parser)
{
    parser->regpos = 0;
    parser->error = 0;
    // prevent of too big register ast size
    if (parser->regsize >= REGISTER_REDUCE_SIZE)
        safe_realloc(parser->regnodes, parser->regnodes,
                   (parser->regsize = REGISTER_DEFAULT_SIZE)
                       * sizeof(struct node));
    // return from parse_error (return !0)
    if (setjmp(parser->stack))
        return NULL;
    show_prompt(TYPEIN_PS1);
#if DEBUG_LEXER == 1
    // test lexer mode
    for (;;)
    {
        struct token tok = lexer_gettoken(parser->lexer);
        printf("Returned token: %d [%s]\n", tok.id,
               (*tok.str == '\n') ? "\\n" : tok.str);
        if (tok.id == LEOF)
            exit(69);
        if (tok.id == LNEWL)
            show_prompt(TYPEIN_PS1);
    }
#endif
    return parse_input(parser);
}

static struct node *parse_input(struct parser *parser)
{
    struct token token;
    struct node *buf;

    debugmsg("parse_input");
    token = lexer_lookahead(parser->lexer);
    if (token.id == LEOF)
        return NULL;
    if (token.id == LNEWL)
    {
        token = lexer_gettoken(parser->lexer);
        return NULL;
    }
    buf = parse_list(parser);
    token = lexer_gettoken(parser->lexer);
    if (token.id != LEOF && token.id != LNEWL)
        parse_error(parser, token);
    return buf;
}

static struct node *parse_list(struct parser *parser)
{
    struct token token, token2;
    struct node *lhs;
    struct node *rhs;

    debugmsg("parse_list");
    lhs = parse_andor(parser);
    token = lexer_lookahead(parser->lexer);
    if (token.id == LSEMI || token.id == LSEPAND)
    {
        lexer_gettoken(parser->lexer);
        if ((token2 = lexer_lookahead(parser->lexer)).id == LNEWL
            || token2.id == LEOF)
            return regnode(
                parser,
                (token.id == LSEMI ? lhs : ast_sepand_create(lhs, NULL)));
        rhs = parse_list(parser);
        if (token.id == LSEMI)
            return regnode(parser, ast_sep_create(lhs, rhs));
        else
            return regnode(parser, ast_sepand_create(lhs, rhs));
    }
    return lhs;
}

static struct node *parse_andor(struct parser *parser)
{
    struct token token;
    struct node *lhs;
    struct node *rhs;

    debugmsg("parse_andor");
    lhs = parse_pipeline(parser);
    token = lexer_lookahead(parser->lexer);
    if (token.id == LAND || token.id == LOR)
    {
        lexer_gettoken(parser->lexer);
        eat_newline();
        rhs = parse_andor(parser);
        if (token.id == LAND)
            return regnode(parser, ast_and_create(lhs, rhs));
        else
            return regnode(parser, ast_or_create(lhs, rhs));
    }
    return lhs;
}

static struct node *parse_pipeline(struct parser *parser)
{
    struct token token;
    struct node *node, *lhs;
    int banged = 0;

    debugmsg("parse_pipeline");
    token = lexer_lookahead(parser->lexer);
    if (token.id == LWORD && !strcmp(token.str, "!"))
    {
        lexer_gettoken(parser->lexer);
        banged = 1;
    }
    lhs = parse_command(parser);
    if ((token = lexer_lookahead(parser->lexer)).id == LPIPE)
        node = regnode(parser,
                       ast_pipe_create(lhs, parse_pipeline_command(parser)));
    else
        node = lhs;
    if (banged)
        return regnode(parser, ast_bang_create(node));
    return node;
}

static struct node *parse_pipeline_command(struct parser *parser)
{
    struct token token;
    struct node *lhs;

    debugmsg("parse_pipeline_command");
    if ((token = lexer_gettoken(parser->lexer)).id != LPIPE)
        parse_error(parser, token);
    eat_newline();
    lhs = parse_command(parser);
    if ((token = lexer_lookahead(parser->lexer)).id == LPIPE)
        return regnode(parser,
                       ast_pipe_create(lhs, parse_pipeline_command(parser)));
    return lhs;
}

static struct node *parse_command(struct parser *parser)
{
    struct token token;

    debugmsg("parse_command");
    token = lexer_lookahead(parser->lexer);
    if (token.id == LPAO
        || (token.id == LWORD
            && (!strcmp(token.str, "for") || !strcmp(token.str, "while")
                || !strcmp(token.str, "if") || !strcmp(token.str, "until")
                || !strcmp(token.str, "{") || !strcmp(token.str, "case"))))
        return parse_shellcommand(parser);
    else if ((token.id == LWORD && !strcmp(token.str, "function"))
             || (token.id == LWORD
                 && lexer_lookahead2(parser->lexer).id == LPAO))
        return parse_funcdec(parser);
    else if (token.id >= LDLESSDASH && token.id <= LWORD)
        return parse_simplecommand(parser);
    else
        parse_error(parser, token);
    assert(0);
    return NULL;
}

static struct node *parse_simplecommand(struct parser *parser)
{
    struct node *cmd;
    struct node *red = NULL;
    int found = 0;

    debugmsg("parse_simplecommand");
    cmd = regnode(parser, ast_cmd_create());
    found += parse_prefix(parser, cmd, &red);
    found += parse_element(parser, cmd, &red);
    if (!found)
        parse_error(parser, lexer_lookahead(parser->lexer));
    if (red)
    {
        red->body.child_red.mhs = cmd;
        cmd = red;
    }
    return cmd;
}

static int parse_element(struct parser *parser, struct node *cmd, struct node **red)
{
    struct token token;
    int found = 0;
    int first = 1;

    debugmsg("parse_element");
    for (;;)
    {
        token = lexer_lookahead(parser->lexer);
        if (token.id >= LDLESSDASH && token.id <= LIONUMBER)
        {
            parse_redirection(parser, red);
            ++found;
        }
        else if (token.id == LWORD && first && !is_keyword(token))
        {
            first = 0;
            // FIXME: gestion des alias
            ast_cmd_add_argv(cmd, lexer_gettoken(parser->lexer).str);
            ++found;
        }
        else if (token.id == LWORD && !first)
            ast_cmd_add_argv(cmd, lexer_gettoken(parser->lexer).str);
        else
            break;
    }
    return found;
}

static int parse_prefix(struct parser *parser, struct node *cmd, struct node **red)
{
    struct token token;
    int found = 0;

    debugmsg("parse_prefix");
    for (;;)
    {
        token = lexer_lookahead(parser->lexer);
        if (token.id >= LDLESSDASH && token.id <= LIONUMBER)
        {
            parse_redirection(parser, red);
            ++found;
        }
        else if (is_assignment(token))
        {
            ast_cmd_add_prefix(cmd, lexer_gettoken(parser->lexer).str);
            ++found;
        }
        else
            break;
    }
    return found;
}

static struct node *parse_shellcommand(struct parser *parser)
{
    struct token token;
    struct node *node;

    debugmsg("parse_shellcommand");
    token = lexer_lookahead(parser->lexer);
    if (!strcmp(token.str, "if"))
        return parse_ruleif(parser);
    else if (!strcmp(token.str, "for"))
        return parse_rulefor(parser);
    else if (!strcmp(token.str, "while"))
        return parse_rulewhile(parser);
    else if (!strcmp(token.str, "until"))
        return parse_ruleuntil(parser);
    else if (!strcmp(token.str, "case"))
        return parse_rulecase(parser);
    else if (!strcmp(token.str, "{"))
    {
        lexer_gettoken(parser->lexer);
        node = parse_compound_list(parser);
        if ((token = lexer_gettoken(parser->lexer)).id != LWORD
            || strcmp(token.str, "}"))
            parse_error(parser, token);
        return node;
    }
    else if (token.id == LPAO)
    {
        lexer_gettoken(parser->lexer);
        node =
            regnode(parser, ast_subshell_create(parse_compound_list(parser)));
        if ((token = lexer_gettoken(parser->lexer)).id != LPAC)
            parse_error(parser, token);
        return node;
    }
    else
        parse_error(parser, token);
    assert(0);
    return NULL;
}

static struct node *parse_funcdec(struct parser *parser)
{
    struct token tok;
    char *funcname;
    struct node *body;
    struct node *reds = NULL;

    debugmsg("parse_funcdec");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id == LWORD && !strcmp(tok.str, "function"))
    {
        free(tok.str);
        tok = lexer_gettoken(parser->lexer);
    }
    if (tok.id != LWORD)
        parse_error(parser, tok);
    funcname = tok.str;
    if (lexer_gettoken(parser->lexer).id != LPAO)
        parse_error(parser, tok);
    if (lexer_gettoken(parser->lexer).id != LPAC)
        parse_error(parser, tok);
    eat_newline();
    body = parse_shellcommand(parser);
    // parse redirection
    while ((tok = lexer_lookahead(parser->lexer)).id >= LDLESSDASH
           && tok.id <= LIONUMBER)
        parse_redirection(parser, &reds);
    if (reds)
    {
        reds->body.child_red.mhs = body;
        body = reds;
    }
    return regnode(parser, ast_funcdec_create(funcname, body));
}

static void parse_redirection(struct parser *parser, struct node **reds)
{
    struct token token;
    long int fd = -1;
    e_red_type redtype;

    debugmsg("parse_redirection");
    if (*reds == NULL)
        *reds = regnode(parser, ast_red_create());
    // retrieve redirection fd if exist
    if ((token = lexer_lookahead(parser->lexer)).id == LIONUMBER)
    {
        lexer_gettoken(parser->lexer);
        errno = 0;
        fd = strtol(token.str, NULL, 10);
        if (errno || fd < 0 || fd > FD_MAX)
            parse_error(parser, token);
    }
    // retrieve redirection type
    token = lexer_gettoken(parser->lexer);
    switch (token.id)
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
    case LCLOBBER:
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
        parse_error(parser, token);
        redtype = 0; // to avoid warning about redtype may be unitialized
    }
    // retrieve redirection word
    token = lexer_gettoken(parser->lexer);
    if (token.id == LWORD)
        ast_red_add(*reds, redtype, fd, token.str);
    else
        parse_error(parser, token);
}

static struct node *parse_compound_list(struct parser *parser)
{
    struct node *lhs;
    struct token tok, tok2;

    debugmsg("parse_compound_list");
    // eat newline
    eat_newline();
    // parse andor
    lhs = parse_andor(parser);
    // looking for ';' or '&' or '\n
    tok = lexer_lookahead(parser->lexer);
    if (tok.id == LSEMI || tok.id == LSEPAND || tok.id == LNEWL)
    {
        lexer_gettoken(parser->lexer);
        if (tok.id == LNEWL)
            show_prompt(TYPEIN_PS2);
        eat_newline();
        // check for and_or
        tok2 = lexer_lookahead(parser->lexer);
        // false condition
        if (tok2.id == LDSEMI || tok2.id == LPAC || tok2.id == LSEMI
            || tok2.id == LSEPAND || tok2.id == LEOF
            || (tok2.id == LWORD
                && (!strcmp(tok2.str, "}") || !strcmp(tok2.str, "do")
                    || !strcmp(tok2.str, "fi") || !strcmp(tok2.str, "done")
                    || !strcmp(tok2.str, "else") || !strcmp(tok2.str, "elif")
                    || !strcmp(tok2.str, "esac") || !strcmp(tok2.str, "then"))))
            return (tok.id == LSEMI || tok.id == LNEWL)
                ? lhs
                : regnode(parser, ast_sepand_create(lhs, NULL));
        else
            return (tok.id == LSEMI || tok.id == LNEWL)
                ? regnode(parser,
                          ast_sep_create(lhs, parse_compound_list(parser)))
                : regnode(parser,
                          ast_sepand_create(lhs, parse_compound_list(parser)));
    }
    return lhs;
}

static struct node *parse_rulefor(struct parser *parser)
{
    struct token tok;
    char *varname;
    char **values = NULL;

    debugmsg("parse_rulefor");
    // check for token 'for'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "for"))
        parse_error(parser, tok);
    free(tok.str);
    // varname
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD)
        parse_error(parser, tok);
    varname = tok.str;
    // eat newline
    eat_newline();
    // check for in
    if ((tok = lexer_lookahead(parser->lexer)).id == LWORD
        && !strcmp(tok.str, "in"))
    {
        tok = lexer_gettoken(parser->lexer);
        free(tok.str);
        do
        {
            if ((tok = lexer_gettoken(parser->lexer)).id != LWORD)
                parse_error(parser, tok);
            values = strvectoradd(values, tok.str);
        } while ((tok = lexer_lookahead(parser->lexer)).id == LWORD);
        // check for ';' or '\n'
        if ((tok = lexer_gettoken(parser->lexer)).id != LSEMI
            && tok.id != LNEWL)
            parse_error(parser, tok);
        // eat newline
        eat_newline();
    }
    return regnode(parser,
                   ast_for_create(varname, values, parse_dogroup(parser)));
}

static struct node *parse_rulewhile(struct parser *parser)
{
    struct node *cond;
    struct token tok;

    debugmsg("parse_rulewhile");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "while"))
        parse_error(parser, tok);
    free(tok.str);
    cond = parse_compound_list(parser);
    return regnode(parser, ast_while_create(cond, parse_dogroup(parser)));
}

static struct node *parse_ruleuntil(struct parser *parser)
{
    struct node *cond;
    struct token tok;

    debugmsg("parse_ruleuntil");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "until"))
        parse_error(parser, tok);
    free(tok.str);
    cond = regnode(parser, ast_bang_create(parse_compound_list(parser)));
    return regnode(parser, ast_while_create(cond, parse_dogroup(parser)));
}

static struct node *parse_ruleif(struct parser *parser)
{
    struct token tok;
    struct node *cond;
    struct node *cond_true;
    struct node *cond_false;

    debugmsg("parse_rule_if");
    // if
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "if"))
        parse_error(parser, tok);
    free(tok.str);
    cond = parse_compound_list(parser);
    // then
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "then"))
        parse_error(parser, tok);
    free(tok.str);
    cond_true = parse_compound_list(parser);
    // elses
    tok = lexer_lookahead(parser->lexer);
    if (tok.id == LWORD
        && (!strcmp(tok.str, "else") || !strcmp(tok.str, "elif")))
        cond_false = parse_elseclause(parser);
    else
        cond_false = NULL;
    // fi
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "fi"))
        parse_error(parser, tok);
    free(tok.str);
    // create if node
    return regnode(parser, ast_if_create(cond, cond_true, cond_false));
}

static struct node *parse_elseclause(struct parser *parser)
{
    struct token tok;

    debugmsg("parse_elseclause");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id == LWORD && !strcmp(tok.str, "else"))
    {
        free(tok.str);
        return parse_compound_list(parser);
    }
    else if (tok.id == LWORD && !strcmp(tok.str, "elif"))
    {
        struct node *cond, *cond_true, *cond_false;

        free(tok.str);
        // if
        cond = parse_compound_list(parser);
        // then
        tok = lexer_gettoken(parser->lexer);
        if (tok.id != LWORD || strcmp(tok.str, "then"))
            parse_error(parser, tok);
        free(tok.str);
        cond_true = parse_compound_list(parser);
        // elses
        tok = lexer_lookahead(parser->lexer);
        if (tok.id == LWORD
            && (!strcmp(tok.str, "else") || !strcmp(tok.str, "elif")))
            cond_false = parse_elseclause(parser);
        else
            cond_false = NULL;
        return regnode(parser, ast_if_create(cond, cond_true, cond_false));
    }
    else
        parse_error(parser, tok);
    assert(0);
    return NULL;
}

static struct node *parse_dogroup(struct parser *parser)
{
    struct token tok;
    struct node *exec;

    debugmsg("parse_dogroup");
    // do
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "do"))
        parse_error(parser, tok);
    free(tok.str);
    // exec part
    exec = parse_compound_list(parser);
    // done
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "done"))
        parse_error(parser, tok);
    free(tok.str);
    return exec;
}

static struct node *parse_rulecase(struct parser *parser)
{
    struct token tok;
    struct node *casenode = NULL; // NULL if no case_clause
    char *varname;

    debugmsg("parse_rulecase");
    // check for token 'case'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "case"))
        parse_error(parser, tok);
    free(tok.str);
    // get varname
    if ((tok = lexer_gettoken(parser->lexer)).id != LWORD)
        parse_error(parser, tok);
    varname = tok.str;
    // eat newline
    eat_newline();
    // check for token 'in'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "in"))
        parse_error(parser, tok);
    free(tok.str);
    // eat newline
    eat_newline();
    // parse case body
    tok = lexer_lookahead(parser->lexer);
    if ((tok.id == LWORD && strcmp(tok.str, "esac")) || tok.id == LPAO)
    {
        casenode = regnode(parser, ast_case_create(varname));
        parse_caseclause(parser, casenode);
    }
    // check for token 'esac'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != LWORD || strcmp(tok.str, "esac"))
        parse_error(parser, tok);
    free(tok.str);
    return casenode;
}

static void parse_caseclause(struct parser *parser, struct node *casenode)
{
    struct token tok;

    debugmsg("parse_caseclause");
    do
    {
        parse_caseitem(parser, casenode);
        tok = lexer_lookahead(parser->lexer);
        if (tok.id == LDSEMI)
        {
            lexer_gettoken(parser->lexer);
            eat_newline();
            tok = lexer_lookahead(parser->lexer);
        }
        if (tok.id == LWORD && !strcmp(tok.str, "esac"))
            return;
    } while (1);
}

static void parse_caseitem(struct parser *parser, struct node *casenode)
{
    struct token tok;
    char **pattern = NULL;
    struct node *exec = NULL;

    debugmsg("parse_caseitem");
    tok = lexer_gettoken(parser->lexer);
    // check for a '(' before pattern list
    if (tok.id == LPAO)
        tok = lexer_gettoken(parser->lexer);
    // retrieve pattern list
    if (tok.id != LWORD)
        parse_error(parser, tok);
    pattern = strvectoradd(pattern, tok.str);
    while ((tok = lexer_lookahead(parser->lexer)).id == LPIPE)
    {
        lexer_gettoken(parser->lexer);
        if ((tok = lexer_gettoken(parser->lexer)).id != LWORD)
            parse_error(parser, tok);
        pattern = strvectoradd(pattern, tok.str);
    }
    // check for ')'
    if ((tok = lexer_gettoken(parser->lexer)).id != LPAC)
        parse_error(parser, tok);
    // eat newline
    eat_newline();
    if ((tok = lexer_lookahead(parser->lexer)).id != LDSEMI
        && !(tok.id == LWORD && !strcmp(tok.str, "esac")))
        exec = parse_compound_list(parser);
    ast_case_add_item(casenode, pattern, exec);
}

static int is_keyword(const struct token t)
{
    if (t.id == LWORD)
        for (register int i = 0; i < KEYWORD_COUNT; ++i)
            if (!strcmp(t.str, keyword_table[i].str))
                return 1;
    return 0;
}
