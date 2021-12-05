/*
** parser.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 00:49:50 2006 Seblu
** Last update Sun Nov 12 02:55:47 2006 seblu
*/

#ifndef PARSER_H_
# define PARSER_H_

# include <setjmp.h>
# include "../ast/ast.h"
# include "getline.h"

// Define is parser or lexer is running for DEBBUGING
# define DEBUG_PARSER 0
# define DEBUG_LEXER 0

enum {
  TOKEN_COUNT = 23,
  KEYWORD_COUNT = 15,
  FD_MAX = 32765,
  REGISTER_REDUCE_SIZE = 200,
  REGISTER_DEFAULT_SIZE = 50,
};

typedef enum		tokenid
  {
    TOK_NONE,
    TOK_NEWLINE,	// \n
    TOK_EOF,		// EOF
    TOK_AND,		// &&
    TOK_SEPAND,		// &
    TOK_OR,		// ||
    TOK_PIPE,		// |
    TOK_DSEMI,		// ;;
    TOK_SEP,		// ;
    TOK_LPAREN,		// (
    TOK_RPAREN,		// )
    TOK_DLESSDASH,	// <<- HAHAH
    TOK_DLESS,		// <<
    TOK_LESSGREAT,	// <>
    TOK_LESSAND,	// <&
    TOK_LESS,		// <
    TOK_DGREAT,		// >>
    TOK_GREATAND,	// >&
    TOK_CLOBBER,	// >|
    TOK_GREAT,		// >
    TOK_IONUMBER,	// number juste before '>' or '<'
    TOK_WORD		// all others HIHI
  } e_tokenid;

typedef struct		token
{
  e_tokenid		id;
  char			*str;
  size_t		len;
} s_token;

typedef struct		lexer
{
  s_token		current; //working token
  s_token		previous;
  FILE			*fs;
  char			eof;
  char			*buf;
  size_t		buf_size; //without \0
  size_t		buf_pos;
  s_getline		*stream;
} s_lexer;

typedef struct		parser
{
  int			error;
  s_lexer		*lexer;
  jmp_buf		stack;
  s_ast_node		**regnodes;
  size_t		regsize;
  size_t		regpos;
} s_parser;

/*
** ==============
** FILE: parser.c
** ==============
*/

/*!
** Parser initialization
**
** @param fs file stream to read
**
** @return the new struct
*/
s_parser		*parser_init(int fd);

/*!
** Do a parse pass
**
** @param parser the parser where we do this parse
**
** @return ast_to_execute
*/
s_ast_node		*parse(s_parser *parser);

/*
** =============
** FILE: lexer.c
** =============
*/

/*!
** Lexer initialization
**
** @param fs file stream to read
**
** @return the new struct
*/
s_lexer			*lexer_init(int fd);

/*!
** Flush current information of position in the line,
** size of the line, and free line buffer. This is call
** by the parser after an error.
** Flush don't reset eof flag !
**
** @param lexer lexer to flush
*/
void			lexer_flush(s_lexer *lexer);

/*!
** Return the next token and destroy it
** @warning The token MUST be freed !
**
** @param lexer lexer structure
**
** @return the next token
*/
s_token			lexer_gettoken(s_lexer *lexer);

/*!
** Return the next token without destruction of it.
** @warning The token string MUST NOT be freed !
**
** @param lexer lexer structure
**
** @return the look ahead token
*/
s_token			lexer_lookahead(s_lexer *lexer);

/*!
** Return the next next token without destruction of it.
** @warning The token string MUST NOT be freed !
** This is a possibility will come from LL1 lexer.
**
** @param lexer lexer structure
**
** @return the look ahead token
*/
s_token			lexer_lookahead2(s_lexer *lexer);

/*!
** Parse input as a here-document (describe is XSI)
**
** @param lexer current lexer
*/
s_token			lexer_getheredoc(s_lexer *lexer, const char *delim);

#endif
