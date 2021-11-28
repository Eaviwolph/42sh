#include "lexerhandler.h"

// Order is very important for correct recognition !
static const struct token operators[] = {
    { LNEWL, "\n" }, { LAND, "&&" },
    { LSEPAND, "&" },   { LOR, "||" },
    { LPIPE, "|" },     { LDSEMI, ";;" },
    { LSEMI, ";" },      { LSSDASH, "<<-" },
    { LDLESS, "<<" },   { LLESSGREAT, "<>" },
    { LLESSAND, "<&" }, { LLESS, "<" },
    { LDGREAT, ">>" },  { LGREATAND, ">&" },
    { LLOBBER, ">|" }, { LGREAT, ">" },
    { LPAO, "(" },   { LPAC, ")" },
    { LNONE, NULL }
};

struct quote
{
    const char *start;
    const size_t lenstart;
    const char *stop;
    const size_t lenstop;
};

static const struct quote quotes[] = {
    { "\"", 1, "\"", 1 }, { "'", 1, "'", 1 },    { "`", 1, "`", 1 },
    { "${", 2, "}", 1 },  { "$((", 2, "))", 2 }, { "$(", 2, ")", 1 },
    { NULL, 0, NULL, 0 },
};


static void token_set(struct token *token, enum type id, char *s)
{
    if (token->op == LWORD)
        free(token->val);
    token->op = id;
    token->val = s;
}

static void token_move(struct token *src, struct token *dst)
{
    *dst = *src;
    src->op = LNONE;
    src->val = NULL;
}

static void lexer_eattoken(struct lexer *lexer)
{
    // if last char was read free buffer
    if (lexer->buf && lexer->buf_pos == lexer->buf_size)
    {
        free(lexer->buf);
        lexer->buf = NULL;
        lexer->buf_size = 0;
    }
    // read a line if buf is empty
    if (!lexer->buf_size && !lexer->eof
        && (lexer->buf = exgetline(lexer->stream)))
    {
        lexer->buf_size = strlen(lexer->buf);
        lexer->buf_pos = 0;
    }
    // if eof is read, bye bye
    if (!lexer->buf)
    {
        lexer->eof = 1;
        token_set(&lexer->current, LEOF, "EOF");
        return;
    }
    // cut a slice of stream
    while (!lexer_cut(lexer))
        ;
    ; // retry again
}

static int lexer_cut(struct lexer *lexer)
{
    const char *buf = lexer->buf;
    char *tokstr;
    size_t *buf_pos = &lexer->buf_pos, token_start, token_pos;
    int end_found = 0;
    char backed = 0, quoted = 0;
    const struct quote *quote = NULL;

    // Rationale: Search begin of token
    // eat separators (" ",\t, \v)
    while (buf[*buf_pos] && is_sep(buf[*buf_pos]))
        ++*buf_pos;
    // eat comment
    if (buf[*buf_pos] == '#')
        while (buf[*buf_pos] && buf[*buf_pos] != '\n')
            ++*buf_pos;
    // check if first chars is an operator
    if (is_operator(buf + *buf_pos, buf_pos, &lexer->current))
        return 1;
    token_start = token_pos = *buf_pos;
    // Rationale: Search end of token
    for (; buf[token_pos]; ++token_pos)
    {
        // backslah newline => eatline
        if ((backed || quoted) && buf[token_pos] == '\n'
            && buf[token_pos + 1] == '\0')
            return lexer_eatline(lexer);
        // backed, go to next char
        else if (backed)
            backed = 0;
        // check end of quoting
        else if (quoted && is_quote_stop(buf, &token_pos, quote))
            quoted = 0;
        // quotin not ended !
        else if (quoted)
            continue;
        // if backslash go in state backed
        else if (!backed && buf[token_pos] == '\\')
            backed = 1;
        // if sep, a token was found !
        else if (is_sep(buf[token_pos]))
            end_found = 1;
        // if it's an operator cut
        else if (is_operator(buf + token_pos, NULL, NULL))
            end_found = 1;
        // check to start quoting
        else if (!quoted && is_quote_start(buf, &token_pos, &quote))
            quoted = 1;
        if (end_found)
            break;
    }
    lexer->buf_pos = token_pos; // update real lexer position buffer
    tokstr = strndup(buf + token_start, token_pos - token_start);
    token_set(
        &lexer->current,
        ((buf[token_pos] == '>' || buf[token_pos] == '<') && isdigitstr(tokstr))
            ? LIONUMBER
            : LWORD,
        tokstr);
    return 1;
}

static int is_operator(const char *buf, size_t *buf_pos, struct token *token)
{
    for (register int i = 0; operators[i].id != LNONE; ++i)
        if (!strncmp(buf, operators[i].str, operators[i].len))
        {
            if (buf_pos)
                *buf_pos += operators[i].len;
            if (token)
                token_set(token, operators[i].id, operators[i].str);
            return 1;
        }
    return 0;
}

static int is_quote_start(const char *buf, size_t *buf_pos,
                          const struct quote **quote)
{
    for (register int i = 0; quotes[i].start; ++i)
        if (!strncmp(buf + *buf_pos, quotes[i].start, quotes[i].lenstart))
        {
            *buf_pos += quotes[i].lenstart - 1;
            if (quote)
                *quote = quotes + i;
            return 1;
        }
    return 0;
}

static int is_quote_stop(const char *buf, size_t *buf_pos, const struct quote *quote)
{
    assert(quote);
    if (!strncmp(buf + *buf_pos, quote->stop, quote->lenstop))
    {
        *buf_pos += quote->lenstop - 1;
        return 1;
    }
    return 0;
}

static int lexer_cut(struct lexer *lexer)
{
    const char *buf = lexer->buf;
    char *tokstr;
    size_t *buf_pos = &lexer->buf_pos, token_start, token_pos;
    int end_found = 0;
    char backed = 0, quoted = 0;
    const struct quote *quote = NULL;

    // Rationale: Search begin of token
    // eat separators (" ",\t, \v)
    while (buf[*buf_pos] && is_sep(buf[*buf_pos]))
        ++*buf_pos;
    // eat comment
    if (buf[*buf_pos] == '#')
        while (buf[*buf_pos] && buf[*buf_pos] != '\n')
            ++*buf_pos;
    // check if first chars is an operator
    if (is_operator(buf + *buf_pos, buf_pos, &lexer->current))
        return 1;
    token_start = token_pos = *buf_pos;
    // Rationale: Search end of token
    for (; buf[token_pos]; ++token_pos)
    {
        // backslah newline => eatline
        if ((backed || quoted) && buf[token_pos] == '\n'
            && buf[token_pos + 1] == '\0')
            return lexer_eatline(lexer);
        // backed, go to next char
        else if (backed)
            backed = 0;
        // check end of quoting
        else if (quoted && is_quote_stop(buf, &token_pos, quote))
            quoted = 0;
        // quotin not ended !
        else if (quoted)
            continue;
        // if backslash go in state backed
        else if (!backed && buf[token_pos] == '\\')
            backed = 1;
        // if sep, a token was found !
        else if (is_sep(buf[token_pos]))
            end_found = 1;
        // if it's an operator cut
        else if (is_operator(buf + token_pos, NULL, NULL))
            end_found = 1;
        // check to start quoting
        else if (!quoted && is_quote_start(buf, &token_pos, &quote))
            quoted = 1;
        if (end_found)
            break;
    }
    lexer->buf_pos = token_pos; // update real lexer position buffer
    tokstr = strndup(buf + token_start, token_pos - token_start);
    token_set(
        &lexer->current,
        ((buf[token_pos] == '>' || buf[token_pos] == '<') && isdigitstr(tokstr))
            ? LIONUMBER
            : LWORD,
        tokstr);
    return 1;
}

struct lexer *lexer_init(int fd)
{
    struct lexer *new;

    safe_malloc(new, sizeof(struct lexer));
    new->stream = exgetline_start(fd);
    new->buf = NULL;
    new->buf_size = new->buf_pos = 0;
    // dont use token_set, because it make comparaison on uninitialized values
    new->previous.op = new->current.op = LNONE;
    new->previous.val = new->current.val = NULL;
    new->eof = 0;
    return new;
}

void lexer_flush(struct lexer *lexer)
{
    token_set(&lexer->previous, LNONE, NULL);
    token_set(&lexer->current, LNONE, NULL);
    if (lexer->buf)
        free(lexer->buf);
    lexer->buf = NULL;
    lexer->buf_size = lexer->buf_pos = 0;
}

struct token lexer_lookahead(struct lexer *lexer)
{
    if (lexer->previous.op == LNONE && lexer->current.op == LNONE)
        lexer_eattoken(lexer);
    return (lexer->previous.op != LNONE) ? lexer->previous : lexer->current;
}

struct token lexer_lookahead2(struct lexer *lexer)
{
    if (lexer->current.op == LNONE)
        lexer_eattoken(lexer);
    if (lexer->previous.op == LNONE)
    {
        token_move(&lexer->current, &lexer->previous);
        lexer_eattoken(lexer);
    }
    return lexer->current;
}

struct token lexer_gettoken(struct lexer *lexer)
{
    struct token buf;
    struct token *victim;

    if (lexer->previous.op != LNONE)
        victim = &lexer->previous;
    else
        victim = &lexer->current;
    if (lexer->current.op == LNONE)
        lexer_eattoken(lexer);
    token_move(victim, &buf);
    return buf;
}

struct token lexer_getheredoc(struct lexer *lexer, const char *delim)
{
    struct token token;
    char *buf = NULL;
    char *line;

    if (lexer->eof)
    {
        // don't use token_set because it's not for new token
        token.op = LEOF;
        token.val = "EOF";
        return token;
    }
    show_prompt(TYPEIN_PS2);
    do
    {
        line = exgetline(lexer->stream);
        if (line == NULL)
        {
            lexer->eof = 1;
            break;
        }
        buf = strmerge(2, buf, line);
    } while (strcmp(line, delim));
    // don't use token set because token is unitialized!
    token.op = LWORD;
    token.val = buf;
    return token;
}
