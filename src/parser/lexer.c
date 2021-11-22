/*
** lexer.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 04:36:53 2006 Seblu
** Last update Fri Nov 17 15:51:32 2006 seblu
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "parser.h"
#include "getline.h"
#include "../shell/shell.h"
#include "../common/function.h"
#include "../common/macro.h"

/*
** Token recognition rationale:
** - Separator are chars which used to cut token but which are deleted.
** - Operators are chars which used to cut token and which are returned as token.
** - Quotes are chars which must be return entierrely.
** - Others are chars considered like words.
*/

/*
** ============
** DECLARATIONS
** ============
*/

// Order is very important for correct recognition !
static const s_token	operators[] =
  {
    {TOK_NEWLINE, "\n", 1},
    {TOK_AND, "&&", 2},
    {TOK_SEPAND, "&", 1},
    {TOK_OR, "||", 2},
    {TOK_PIPE, "|", 1},
    {TOK_DSEMI, ";;", 2},
    {TOK_SEP, ";", 1},
    {TOK_DLESSDASH, "<<-", 3},
    {TOK_DLESS, "<<", 2},
    {TOK_LESSGREAT, "<>", 2},
    {TOK_LESSAND, "<&", 2},
    {TOK_LESS, "<", 1},
    {TOK_DGREAT, ">>", 2},
    {TOK_GREATAND, ">&", 2},
    {TOK_CLOBBER, ">|", 2},
    {TOK_GREAT, ">", 1},
    {TOK_LPAREN, "(", 1},
    {TOK_RPAREN, ")", 1},
    {TOK_NONE, NULL, 0}
  };

typedef struct		quote
{
  const char		*start;
  const size_t		lenstart;
  const char		*stop;
  const size_t		lenstop;
} s_quote;

static const s_quote	quotes[] =
  {
    {"\"", 1, "\"", 1},
    {"'", 1, "'", 1},
    {"`", 1, "`", 1},
    {"${", 2, "}", 1},
    {"$((", 2, "))", 2},
    {"$(", 2, ")", 1},
    {NULL, 0, NULL, 0},
  };

/*!
** Check if @arg buf + *buf_pos point on the start of quote sequence.
** @warning Recognition start at buf + *buf_pos !
**
** @param buf a string buffer
** @param buf_pos position in the buffer, which is incremented if found to point on
** the last char of the quote !
** @param quote quote type found
**
** @return true (!0) if a quote is found, else false (0)
*/
static int	is_quote_start(const char *buf, size_t *buf_pos, const s_quote **quote);

/*!
** Check if @arg buf + *buf_pos point on the stop of quote sequence.
** @warning Recognition start at buf + *buf_pos !
**
** @param buf a string buffer
** @param buf_pos position in the buffer, which is incremented if found to point on
** the last char of the quote !
** @param quote quote type to found
**
** @return true (!0) if a quote is found, else false (0)
*/
static int	is_quote_stop(const char *buf, size_t *buf_pos, const s_quote *quote);

/*!
** Return a predicat about c is a separator
**
** @param c Must be a character
**
** @return true if c is a separator
*/
#define		is_sep(c) ((c) == ' ' || (c) == '\t')

/*!
** Check if the buffer point to an operator. Il it's true and buf_pos is
** not NULL, *buf_pos is correctly incremented to point on the next token
** @warning Recgnition start at buf !
**
** @param buf a string buffer where recognition start
** @param buf_pos buffer position to increment correctly if operator is found
** @param token reconized token operator
**
** @return true (!0) if find, else false (0)
*/
static int	is_operator(const char *buf, size_t *buf_pos, s_token *token);

/*!
** Read lexer's stream, and return the next token.
**
** @param lex lexer struct
*/
static void	lexer_eattoken(s_lexer *lex);

/*!
** This function is only call when the end of a line occur in
** a quote or after a backslash
**
** @param lexer lexer struct
**
** @return 1 if can read a line, 0 if eof
*/
static int	lexer_eatline(s_lexer *lexer);

/*!
** Cut a token in one or more line.
**
** @param lexer lexer struct
**
*/
static int	lexer_cut(s_lexer *lexer);

/*!
** Correctly set a token. In first, it call macro token_free to
** desallow memory if it's a word.
**
** @param token token to set
** @param id new token id
** @param s new token string
*/
static void	token_set(s_token *token, e_tokenid id, char *s);

/*!
** Move a token to another. Token source, will become token
** NONE.
**
** @param src source token
** @param dst destination token
*/
static void	token_move(s_token *src, s_token *dst);

/*
** ===========
** DEFINITIONS
** ===========
*/

s_lexer		*lexer_init(int fd)
{
  s_lexer	*new;

  secmalloc(new, sizeof (s_lexer));
  new->stream = getline_open(fd);
  new->buf = NULL;
  new->buf_size = new->buf_pos = 0;
  //dont use token_set, because it make comparaison on uninitialized values
  new->previous.id = new->current.id = TOK_NONE;
  new->previous.str = new->current.str = NULL;
  new->previous.len = new->current.len = 0;
  new->eof = 0;
  return new;
}

void		lexer_flush(s_lexer *lexer)
{
  token_set(&lexer->previous, TOK_NONE, NULL);
  token_set(&lexer->current, TOK_NONE, NULL);
  if (lexer->buf)
    free(lexer->buf);
  lexer->buf = NULL;
  lexer->buf_size = lexer->buf_pos = 0;
}

s_token		lexer_lookahead(s_lexer *lexer)
{
  if (lexer->previous.id == TOK_NONE && lexer->current.id == TOK_NONE)
    lexer_eattoken(lexer);
  return (lexer->previous.id != TOK_NONE) ? lexer->previous : lexer->current;
}

s_token		lexer_lookahead2(s_lexer *lexer)
{
  if (lexer->current.id == TOK_NONE)
    lexer_eattoken(lexer);
  if (lexer->previous.id == TOK_NONE) {
    token_move(&lexer->current, &lexer->previous);
    lexer_eattoken(lexer);
  }
  return lexer->current;
}

s_token		lexer_gettoken(s_lexer *lexer)
{
  s_token	buf;
  s_token	*victim;

  if (lexer->previous.id != TOK_NONE)
    victim = &lexer->previous;
  else
    victim = &lexer->current;
  if (lexer->current.id == TOK_NONE)
    lexer_eattoken(lexer);
  token_move(victim, &buf);
  return buf;
}

s_token		lexer_getheredoc(s_lexer *lexer, const char *delim)
{
  s_token	token;
  char		*buf = NULL;
  char		*line;

  if (lexer->eof) {
    //don't use token_set because it's not for new token
    token.id = TOK_EOF;
    token.str = "EOF";
    token.len = 3;
    return token;
  }
  show_prompt(PROMPT_PS2);
  do {
    line = getline(lexer->stream);
    if (line == NULL) {
      lexer->eof = 1;
      break;
    }
    buf = strmerge(2, buf, line);
  }
  while (strcmp(line, delim));
  //don't use token set because token is unitialized!
  token.id = TOK_WORD;
  token.str = buf;
  token.len = strlen(buf);
  return token;
}

static void	token_set(s_token *token, e_tokenid id, char *s)
{
  if (token->id == TOK_WORD)
    free(token->str);
  token->id = id;
  token->str = s;
  if (s) token->len = strlen(s);
  else token->len = 0;
}

static void	token_move(s_token *src, s_token *dst)
{
  *dst = *src;
  src->id = TOK_NONE;
  src->str = NULL;
  src->len = 0;
}

static  void	lexer_eattoken(s_lexer *lexer)
{
  //if last char was read free buffer
  if (lexer->buf && lexer->buf_pos == lexer->buf_size) {
    free(lexer->buf);
    lexer->buf = NULL;
    lexer->buf_size = 0;
  }
  //read a line if buf is empty
  if (!lexer->buf_size && !lexer->eof && (lexer->buf = getline(lexer->stream))) {
    lexer->buf_size = strlen(lexer->buf);
    lexer->buf_pos = 0;
  }
  //if eof is read, bye bye
  if (!lexer->buf) {
    lexer->eof = 1;
    token_set(&lexer->current, TOK_EOF, "EOF");
    return;
  }
  //cut a slice of stream
  while (!lexer_cut(lexer))
    ;; //retry again
}

static int	lexer_eatline(s_lexer *lexer)
{
  char		*buf, *buf2;

  assert(lexer->buf);
  buf = lexer->buf;
  //remove \n if a \ is present before him
  if (lexer->buf_size > 1 && buf[lexer->buf_size - 2] == '\\')
    buf[lexer->buf_size - 2] = 0;
  //show incomplet recognition prompt
  show_prompt(PROMPT_PS2);
  //retrieve a new line
  if (!(buf2 = getline(lexer->stream))) {
    lexer->eof = 1;
    token_set(&lexer->current, TOK_EOF, "EOF");
    return 1;
  }
  lexer->buf = strmerge(2, buf, buf2);
  lexer->buf_size = strlen(lexer->buf);
  free(buf);
  free(buf2);
  return 0;
}

static int	lexer_cut(s_lexer *lexer)
{
  const char	*buf = lexer->buf;
  char		*tokstr;
  size_t	*buf_pos = &lexer->buf_pos, token_start, token_pos;
  int		end_found = 0;
  char		backed = 0, quoted = 0;
  const s_quote	*quote = NULL;

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
  for (; buf[token_pos]; ++token_pos) {
    // backslah newline => eatline
    if ((backed || quoted) && buf[token_pos] == '\n' && buf[token_pos + 1] == '\0')
      return lexer_eatline(lexer);
    // backed, go to next char
    else if (backed) backed = 0;
    // check end of quoting
    else if (quoted && is_quote_stop(buf, &token_pos, quote)) quoted = 0;
    // quotin not ended !
    else if (quoted) continue;
    // if backslash go in state backed
    else if (!backed && buf[token_pos] == '\\') backed = 1;
    // if sep, a token was found !
    else if (is_sep(buf[token_pos])) end_found = 1;
    // if it's an operator cut
    else if (is_operator(buf + token_pos, NULL, NULL)) end_found = 1;
    // check to start quoting
    else if (!quoted && is_quote_start(buf, &token_pos, &quote)) quoted = 1;
    if (end_found) break;
  }
  lexer->buf_pos = token_pos; //update real lexer position buffer
  tokstr = strndup(buf + token_start, token_pos - token_start);
  token_set(&lexer->current, ((buf[token_pos] == '>' || buf[token_pos] == '<')
	    && isdigitstr(tokstr)) ? TOK_IONUMBER : TOK_WORD, tokstr);
  return 1;
}

static int	is_operator(const char *buf, size_t *buf_pos, s_token *token)
{
  for (register int i = 0; operators[i].id != TOK_NONE; ++i)
    if (!strncmp(buf, operators[i].str, operators[i].len)) {
      if (buf_pos)
	*buf_pos += operators[i].len;
      if (token)
	token_set(token, operators[i].id, operators[i].str);
      return 1;
    }
  return 0;
}

static int	is_quote_start(const char *buf, size_t *buf_pos, const s_quote **quote)
{
  for (register int i = 0; quotes[i].start; ++i)
    if (!strncmp(buf + *buf_pos, quotes[i].start, quotes[i].lenstart)) {
      *buf_pos +=  quotes[i].lenstart - 1;
      if (quote)
	*quote = quotes + i;
      return 1;
    }
  return 0;
}

static int	is_quote_stop(const char *buf, size_t *buf_pos, const s_quote *quote)
{
  assert(quote);
  if (!strncmp(buf + *buf_pos, quote->stop, quote->lenstop)) {
    *buf_pos +=  quote->lenstop - 1;
    return 1;
  }
  return 0;
}
