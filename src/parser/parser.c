/*
** parser.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:56:07 2006 Seblu
** Last update Thu Nov 23 14:24:39 2006 seblu
*/

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

/*
** ============
** DECLARATIONS
** ============
*/

static s_ast_node *regnode(s_parser *parser, s_ast_node *node);

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
static s_ast_node *parse_input(s_parser *parser);
static s_ast_node *parse_list(s_parser *parser);
static s_ast_node *parse_andor(s_parser *parser);
static s_ast_node *parse_pipeline(s_parser *parser);
static s_ast_node *parse_command(s_parser *parser);
static s_ast_node *parse_simplecommand(s_parser *parser);
static s_ast_node *parse_shellcommand(s_parser *parser);
static s_ast_node *parse_rulefor(s_parser *parser);
static s_ast_node *parse_rulewhile(s_parser *parser);
static s_ast_node *parse_ruleuntil(s_parser *parser);
static s_ast_node *parse_ruleif(s_parser *parser);
static s_ast_node *parse_rulecase(s_parser *parser);
static s_ast_node *parse_compound_list(s_parser *parser);
static s_ast_node *parse_pipeline_command(s_parser *parser);
static s_ast_node *parse_funcdec(s_parser *parser);
static s_ast_node *parse_elseclause(s_parser *parser);
static s_ast_node *parse_dogroup(s_parser *parser);
static void parse_caseclause(s_parser *parser, s_ast_node *casenode);
static void parse_caseitem(s_parser *parser, s_ast_node *casenode);
static int parse_prefix(s_parser *parser, s_ast_node *cmd, s_ast_node **red);
static int parse_element(s_parser *parser, s_ast_node *cmd, s_ast_node **red);
static void parse_redirection(s_parser *parser, s_ast_node **reds);
static int is_keyword(const s_token t);

/*!
** Notify a parse error
**
** @param parser parser where error appear
** @param t token near of the error
*/
static void parse_error(s_parser *parser, s_token t);

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
    while (lexer_lookahead(parser->lexer).id == TOK_NEWLINE)                   \
    {                                                                          \
        lexer_gettoken(parser->lexer);                                         \
        show_prompt(PROMPT_PS2);                                               \
    }

/*
** ===========
** DEFINITIONS
** ===========
*/

static const s_token keyword_table[] = {
    { TOK_WORD, "!", 1 },     { TOK_WORD, "{", 1 },
    { TOK_WORD, "}", 1 },     { TOK_WORD, "if", 2 },
    { TOK_WORD, "in", 2 },    { TOK_WORD, "fi", 2 },
    { TOK_WORD, "do", 2 },    { TOK_WORD, "then", 4 },
    { TOK_WORD, "else", 4 },  { TOK_WORD, "elif", 4 },
    { TOK_WORD, "done", 4 },  { TOK_WORD, "case", 4 },
    { TOK_WORD, "esac", 4 },  { TOK_WORD, "while", 5 },
    { TOK_WORD, "until", 5 }, { TOK_WORD, "function", 8 }
};

s_parser *parser_init(int fd)
{
    s_parser *new;

    secmalloc(new, sizeof(s_parser));
    new->lexer = lexer_init(fd);
    new->error = 0;
    new->regnodes = NULL;
    new->regsize = new->regpos = 0;
    return new;
}

static s_ast_node *regnode(s_parser *parser, s_ast_node *node)
{
    if (!node)
        return node;
    if (parser->regpos >= parser->regsize)
    {
        parser->regsize += 50;
        secrealloc(parser->regnodes, parser->regnodes,
                   parser->regsize * sizeof(s_ast_node));
    }
    parser->regnodes[parser->regpos] = node;
    ++parser->regpos;
    return node;
}

static void parse_error(s_parser *parser, s_token t)
{
    if (t.id == TOK_EOF)
        fprintf(stderr, "%s: syntax error: unexpected end of file.\n",
                shell->name);
    else
        fprintf(stderr, "%s: syntax error near unexpected token `%s'.\n",
                shell->name, t.str);
    parser->error = 1;
    shell->status = ERROR_PARSE;
    if (parser->regnodes)
        for (register int i = 0; parser->regnodes[i]; ++i)
            ast_destruct_node(parser->regnodes[i]);
    lexer_flush(parser->lexer);
    longjmp(parser->stack, 1);
}

s_ast_node *parse(s_parser *parser)
{
    parser->regpos = 0;
    parser->error = 0;
    // prevent of too big register ast size
    if (parser->regsize >= REGISTER_REDUCE_SIZE)
        secrealloc(parser->regnodes, parser->regnodes,
                   (parser->regsize = REGISTER_DEFAULT_SIZE)
                       * sizeof(s_ast_node));
    // return from parse_error (return !0)
    if (setjmp(parser->stack))
        return NULL;
    show_prompt(PROMPT_PS1);
#if DEBUG_LEXER == 1
    // test lexer mode
    for (;;)
    {
        s_token tok = lexer_gettoken(parser->lexer);
        printf("Returned token: %d [%s]\n", tok.id,
               (*tok.str == '\n') ? "\\n" : tok.str);
        if (tok.id == TOK_EOF)
            exit(69);
        if (tok.id == TOK_NEWLINE)
            show_prompt(PROMPT_PS1);
    }
#endif
    return parse_input(parser);
}

static s_ast_node *parse_input(s_parser *parser)
{
    s_token token;
    s_ast_node *buf;

    debugmsg("parse_input");
    token = lexer_lookahead(parser->lexer);
    if (token.id == TOK_EOF)
        return NULL;
    if (token.id == TOK_NEWLINE)
    {
        token = lexer_gettoken(parser->lexer);
        return NULL;
    }
    buf = parse_list(parser);
    token = lexer_gettoken(parser->lexer);
    if (token.id != TOK_EOF && token.id != TOK_NEWLINE)
        parse_error(parser, token);
    return buf;
}

static s_ast_node *parse_list(s_parser *parser)
{
    s_token token, token2;
    s_ast_node *lhs;
    s_ast_node *rhs;

    debugmsg("parse_list");
    lhs = parse_andor(parser);
    token = lexer_lookahead(parser->lexer);
    if (token.id == TOK_SEP || token.id == TOK_SEPAND)
    {
        lexer_gettoken(parser->lexer);
        if ((token2 = lexer_lookahead(parser->lexer)).id == TOK_NEWLINE
            || token2.id == TOK_EOF)
            return regnode(
                parser,
                (token.id == TOK_SEP ? lhs : ast_sepand_create(lhs, NULL)));
        rhs = parse_list(parser);
        if (token.id == TOK_SEP)
            return regnode(parser, ast_sep_create(lhs, rhs));
        else
            return regnode(parser, ast_sepand_create(lhs, rhs));
    }
    return lhs;
}

static s_ast_node *parse_andor(s_parser *parser)
{
    s_token token;
    s_ast_node *lhs;
    s_ast_node *rhs;

    debugmsg("parse_andor");
    lhs = parse_pipeline(parser);
    token = lexer_lookahead(parser->lexer);
    if (token.id == TOK_AND || token.id == TOK_OR)
    {
        lexer_gettoken(parser->lexer);
        eat_newline();
        rhs = parse_andor(parser);
        if (token.id == TOK_AND)
            return regnode(parser, ast_and_create(lhs, rhs));
        else
            return regnode(parser, ast_or_create(lhs, rhs));
    }
    return lhs;
}

static s_ast_node *parse_pipeline(s_parser *parser)
{
    s_token token;
    s_ast_node *node, *lhs;
    int banged = 0;

    debugmsg("parse_pipeline");
    token = lexer_lookahead(parser->lexer);
    if (token.id == TOK_WORD && !strcmp(token.str, "!"))
    {
        lexer_gettoken(parser->lexer);
        banged = 1;
    }
    lhs = parse_command(parser);
    if ((token = lexer_lookahead(parser->lexer)).id == TOK_PIPE)
        node = regnode(parser,
                       ast_pipe_create(lhs, parse_pipeline_command(parser)));
    else
        node = lhs;
    if (banged)
        return regnode(parser, ast_bang_create(node));
    return node;
}

static s_ast_node *parse_pipeline_command(s_parser *parser)
{
    s_token token;
    s_ast_node *lhs;

    debugmsg("parse_pipeline_command");
    if ((token = lexer_gettoken(parser->lexer)).id != TOK_PIPE)
        parse_error(parser, token);
    eat_newline();
    lhs = parse_command(parser);
    if ((token = lexer_lookahead(parser->lexer)).id == TOK_PIPE)
        return regnode(parser,
                       ast_pipe_create(lhs, parse_pipeline_command(parser)));
    return lhs;
}

static s_ast_node *parse_command(s_parser *parser)
{
    s_token token;

    debugmsg("parse_command");
    token = lexer_lookahead(parser->lexer);
    if (token.id == TOK_LPAREN
        || (token.id == TOK_WORD
            && (!strcmp(token.str, "for") || !strcmp(token.str, "while")
                || !strcmp(token.str, "if") || !strcmp(token.str, "until")
                || !strcmp(token.str, "{") || !strcmp(token.str, "case"))))
        return parse_shellcommand(parser);
    else if ((token.id == TOK_WORD && !strcmp(token.str, "function"))
             || (token.id == TOK_WORD
                 && lexer_lookahead2(parser->lexer).id == TOK_LPAREN))
        return parse_funcdec(parser);
    else if (token.id >= TOK_DLESSDASH && token.id <= TOK_WORD)
        return parse_simplecommand(parser);
    else
        parse_error(parser, token);
    assert(0);
    return NULL;
}

static s_ast_node *parse_simplecommand(s_parser *parser)
{
    s_ast_node *cmd;
    s_ast_node *red = NULL;
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

static int parse_element(s_parser *parser, s_ast_node *cmd, s_ast_node **red)
{
    s_token token;
    int found = 0;
    int first = 1;

    debugmsg("parse_element");
    for (;;)
    {
        token = lexer_lookahead(parser->lexer);
        if (token.id >= TOK_DLESSDASH && token.id <= TOK_IONUMBER)
        {
            parse_redirection(parser, red);
            ++found;
        }
        else if (token.id == TOK_WORD && first && !is_keyword(token))
        {
            first = 0;
            // FIXME: gestion des alias
            ast_cmd_add_argv(cmd, lexer_gettoken(parser->lexer).str);
            ++found;
        }
        else if (token.id == TOK_WORD && !first)
            ast_cmd_add_argv(cmd, lexer_gettoken(parser->lexer).str);
        else
            break;
    }
    return found;
}

static int parse_prefix(s_parser *parser, s_ast_node *cmd, s_ast_node **red)
{
    s_token token;
    int found = 0;

    debugmsg("parse_prefix");
    for (;;)
    {
        token = lexer_lookahead(parser->lexer);
        if (token.id >= TOK_DLESSDASH && token.id <= TOK_IONUMBER)
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

static s_ast_node *parse_shellcommand(s_parser *parser)
{
    s_token token;
    s_ast_node *node;

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
        if ((token = lexer_gettoken(parser->lexer)).id != TOK_WORD
            || strcmp(token.str, "}"))
            parse_error(parser, token);
        return node;
    }
    else if (token.id == TOK_LPAREN)
    {
        lexer_gettoken(parser->lexer);
        node =
            regnode(parser, ast_subshell_create(parse_compound_list(parser)));
        if ((token = lexer_gettoken(parser->lexer)).id != TOK_RPAREN)
            parse_error(parser, token);
        return node;
    }
    else
        parse_error(parser, token);
    assert(0);
    return NULL;
}

static s_ast_node *parse_funcdec(s_parser *parser)
{
    s_token tok;
    char *funcname;
    s_ast_node *body;
    s_ast_node *reds = NULL;

    debugmsg("parse_funcdec");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id == TOK_WORD && !strcmp(tok.str, "function"))
    {
        free(tok.str);
        tok = lexer_gettoken(parser->lexer);
    }
    if (tok.id != TOK_WORD)
        parse_error(parser, tok);
    funcname = tok.str;
    if (lexer_gettoken(parser->lexer).id != TOK_LPAREN)
        parse_error(parser, tok);
    if (lexer_gettoken(parser->lexer).id != TOK_RPAREN)
        parse_error(parser, tok);
    eat_newline();
    body = parse_shellcommand(parser);
    // parse redirection
    while ((tok = lexer_lookahead(parser->lexer)).id >= TOK_DLESSDASH
           && tok.id <= TOK_IONUMBER)
        parse_redirection(parser, &reds);
    if (reds)
    {
        reds->body.child_red.mhs = body;
        body = reds;
    }
    return regnode(parser, ast_funcdec_create(funcname, body));
}

static void parse_redirection(s_parser *parser, s_ast_node **reds)
{
    s_token token;
    long int fd = -1;
    e_red_type redtype;

    debugmsg("parse_redirection");
    if (*reds == NULL)
        *reds = regnode(parser, ast_red_create());
    // retrieve redirection fd if exist
    if ((token = lexer_lookahead(parser->lexer)).id == TOK_IONUMBER)
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
    case TOK_GREAT:
        redtype = R_GREAT;
        if (fd == -1)
            fd = 1;
        break;
    case TOK_DGREAT:
        redtype = R_DLESS;
        if (fd == -1)
            fd = 1;
        break;
    case TOK_DLESSDASH:
        redtype = R_DLESSDASH;
        if (fd == -1)
            fd = 0;
        break;
    case TOK_DLESS:
        redtype = R_DLESS;
        if (fd == -1)
            fd = 0;
        break;
    case TOK_LESSGREAT:
        redtype = R_LESSGREAT;
        if (fd == -1)
            fd = 0;
        break;
    case TOK_LESSAND:
        redtype = R_LESSAND;
        if (fd == -1)
            fd = 0;
        break;
    case TOK_LESS:
        redtype = R_LESS;
        if (fd == -1)
            fd = 0;
        break;
    case TOK_CLOBBER:
        redtype = R_CLOBBER;
        if (fd == -1)
            fd = 1;
        break;
    case TOK_GREATAND:
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
    if (token.id == TOK_WORD)
        ast_red_add(*reds, redtype, fd, token.str);
    else
        parse_error(parser, token);
}

static s_ast_node *parse_compound_list(s_parser *parser)
{
    s_ast_node *lhs;
    s_token tok, tok2;

    debugmsg("parse_compound_list");
    // eat newline
    eat_newline();
    // parse andor
    lhs = parse_andor(parser);
    // looking for ';' or '&' or '\n
    tok = lexer_lookahead(parser->lexer);
    if (tok.id == TOK_SEP || tok.id == TOK_SEPAND || tok.id == TOK_NEWLINE)
    {
        lexer_gettoken(parser->lexer);
        if (tok.id == TOK_NEWLINE)
            show_prompt(PROMPT_PS2);
        eat_newline();
        // check for and_or
        tok2 = lexer_lookahead(parser->lexer);
        // false condition
        if (tok2.id == TOK_DSEMI || tok2.id == TOK_RPAREN || tok2.id == TOK_SEP
            || tok2.id == TOK_SEPAND || tok2.id == TOK_EOF
            || (tok2.id == TOK_WORD
                && (!strcmp(tok2.str, "}") || !strcmp(tok2.str, "do")
                    || !strcmp(tok2.str, "fi") || !strcmp(tok2.str, "done")
                    || !strcmp(tok2.str, "else") || !strcmp(tok2.str, "elif")
                    || !strcmp(tok2.str, "esac") || !strcmp(tok2.str, "then"))))
            return (tok.id == TOK_SEP || tok.id == TOK_NEWLINE)
                ? lhs
                : regnode(parser, ast_sepand_create(lhs, NULL));
        else
            return (tok.id == TOK_SEP || tok.id == TOK_NEWLINE)
                ? regnode(parser,
                          ast_sep_create(lhs, parse_compound_list(parser)))
                : regnode(parser,
                          ast_sepand_create(lhs, parse_compound_list(parser)));
    }
    return lhs;
}

static s_ast_node *parse_rulefor(s_parser *parser)
{
    s_token tok;
    char *varname;
    char **values = NULL;

    debugmsg("parse_rulefor");
    // check for token 'for'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "for"))
        parse_error(parser, tok);
    free(tok.str);
    // varname
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD)
        parse_error(parser, tok);
    varname = tok.str;
    // eat newline
    eat_newline();
    // check for in
    if ((tok = lexer_lookahead(parser->lexer)).id == TOK_WORD
        && !strcmp(tok.str, "in"))
    {
        tok = lexer_gettoken(parser->lexer);
        free(tok.str);
        do
        {
            if ((tok = lexer_gettoken(parser->lexer)).id != TOK_WORD)
                parse_error(parser, tok);
            values = strvectoradd(values, tok.str);
        } while ((tok = lexer_lookahead(parser->lexer)).id == TOK_WORD);
        // check for ';' or '\n'
        if ((tok = lexer_gettoken(parser->lexer)).id != TOK_SEP
            && tok.id != TOK_NEWLINE)
            parse_error(parser, tok);
        // eat newline
        eat_newline();
    }
    return regnode(parser,
                   ast_for_create(varname, values, parse_dogroup(parser)));
}

static s_ast_node *parse_rulewhile(s_parser *parser)
{
    s_ast_node *cond;
    s_token tok;

    debugmsg("parse_rulewhile");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "while"))
        parse_error(parser, tok);
    free(tok.str);
    cond = parse_compound_list(parser);
    return regnode(parser, ast_while_create(cond, parse_dogroup(parser)));
}

static s_ast_node *parse_ruleuntil(s_parser *parser)
{
    s_ast_node *cond;
    s_token tok;

    debugmsg("parse_ruleuntil");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "until"))
        parse_error(parser, tok);
    free(tok.str);
    cond = regnode(parser, ast_bang_create(parse_compound_list(parser)));
    return regnode(parser, ast_while_create(cond, parse_dogroup(parser)));
}

static s_ast_node *parse_ruleif(s_parser *parser)
{
    s_token tok;
    s_ast_node *cond;
    s_ast_node *cond_true;
    s_ast_node *cond_false;

    debugmsg("parse_rule_if");
    // if
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "if"))
        parse_error(parser, tok);
    free(tok.str);
    cond = parse_compound_list(parser);
    // then
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "then"))
        parse_error(parser, tok);
    free(tok.str);
    cond_true = parse_compound_list(parser);
    // elses
    tok = lexer_lookahead(parser->lexer);
    if (tok.id == TOK_WORD
        && (!strcmp(tok.str, "else") || !strcmp(tok.str, "elif")))
        cond_false = parse_elseclause(parser);
    else
        cond_false = NULL;
    // fi
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "fi"))
        parse_error(parser, tok);
    free(tok.str);
    // create if node
    return regnode(parser, ast_if_create(cond, cond_true, cond_false));
}

static s_ast_node *parse_elseclause(s_parser *parser)
{
    s_token tok;

    debugmsg("parse_elseclause");
    tok = lexer_gettoken(parser->lexer);
    if (tok.id == TOK_WORD && !strcmp(tok.str, "else"))
    {
        free(tok.str);
        return parse_compound_list(parser);
    }
    else if (tok.id == TOK_WORD && !strcmp(tok.str, "elif"))
    {
        s_ast_node *cond, *cond_true, *cond_false;

        free(tok.str);
        // if
        cond = parse_compound_list(parser);
        // then
        tok = lexer_gettoken(parser->lexer);
        if (tok.id != TOK_WORD || strcmp(tok.str, "then"))
            parse_error(parser, tok);
        free(tok.str);
        cond_true = parse_compound_list(parser);
        // elses
        tok = lexer_lookahead(parser->lexer);
        if (tok.id == TOK_WORD
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

static s_ast_node *parse_dogroup(s_parser *parser)
{
    s_token tok;
    s_ast_node *exec;

    debugmsg("parse_dogroup");
    // do
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "do"))
        parse_error(parser, tok);
    free(tok.str);
    // exec part
    exec = parse_compound_list(parser);
    // done
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "done"))
        parse_error(parser, tok);
    free(tok.str);
    return exec;
}

static s_ast_node *parse_rulecase(s_parser *parser)
{
    s_token tok;
    s_ast_node *casenode = NULL; // NULL if no case_clause
    char *varname;

    debugmsg("parse_rulecase");
    // check for token 'case'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "case"))
        parse_error(parser, tok);
    free(tok.str);
    // get varname
    if ((tok = lexer_gettoken(parser->lexer)).id != TOK_WORD)
        parse_error(parser, tok);
    varname = tok.str;
    // eat newline
    eat_newline();
    // check for token 'in'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "in"))
        parse_error(parser, tok);
    free(tok.str);
    // eat newline
    eat_newline();
    // parse case body
    tok = lexer_lookahead(parser->lexer);
    if ((tok.id == TOK_WORD && strcmp(tok.str, "esac")) || tok.id == TOK_LPAREN)
    {
        casenode = regnode(parser, ast_case_create(varname));
        parse_caseclause(parser, casenode);
    }
    // check for token 'esac'
    tok = lexer_gettoken(parser->lexer);
    if (tok.id != TOK_WORD || strcmp(tok.str, "esac"))
        parse_error(parser, tok);
    free(tok.str);
    return casenode;
}

static void parse_caseclause(s_parser *parser, s_ast_node *casenode)
{
    s_token tok;

    debugmsg("parse_caseclause");
    do
    {
        parse_caseitem(parser, casenode);
        tok = lexer_lookahead(parser->lexer);
        if (tok.id == TOK_DSEMI)
        {
            lexer_gettoken(parser->lexer);
            eat_newline();
            tok = lexer_lookahead(parser->lexer);
        }
        if (tok.id == TOK_WORD && !strcmp(tok.str, "esac"))
            return;
    } while (1);
}

static void parse_caseitem(s_parser *parser, s_ast_node *casenode)
{
    s_token tok;
    char **pattern = NULL;
    s_ast_node *exec = NULL;

    debugmsg("parse_caseitem");
    tok = lexer_gettoken(parser->lexer);
    // check for a '(' before pattern list
    if (tok.id == TOK_LPAREN)
        tok = lexer_gettoken(parser->lexer);
    // retrieve pattern list
    if (tok.id != TOK_WORD)
        parse_error(parser, tok);
    pattern = strvectoradd(pattern, tok.str);
    while ((tok = lexer_lookahead(parser->lexer)).id == TOK_PIPE)
    {
        lexer_gettoken(parser->lexer);
        if ((tok = lexer_gettoken(parser->lexer)).id != TOK_WORD)
            parse_error(parser, tok);
        pattern = strvectoradd(pattern, tok.str);
    }
    // check for ')'
    if ((tok = lexer_gettoken(parser->lexer)).id != TOK_RPAREN)
        parse_error(parser, tok);
    // eat newline
    eat_newline();
    if ((tok = lexer_lookahead(parser->lexer)).id != TOK_DSEMI
        && !(tok.id == TOK_WORD && !strcmp(tok.str, "esac")))
        exec = parse_compound_list(parser);
    ast_case_add_item(casenode, pattern, exec);
}

static int is_keyword(const s_token t)
{
    if (t.id == TOK_WORD)
        for (register int i = 0; i < KEYWORD_COUNT; ++i)
            if (!strcmp(t.str, keyword_table[i].str))
                return 1;
    return 0;
}
