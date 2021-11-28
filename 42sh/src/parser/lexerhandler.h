#ifndef LEXERHANDLER_H
#define LEXERHANDLER_H

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../common/macro.h"
#include "dtoken.h"
#include "extendedgetline.h"
#include "../common/function.h"

#define LNONE (69)
#define LEOF (72)

struct lexer
{
    struct token current; // working token
    struct token previous;
    FILE *fs;
    char eof;
    char *buf;
    size_t buf_size; // without \0
    size_t buf_pos;
    struct line *stream;
};

struct lexer *lexer_init(int fd);

void lexer_flush(struct lexer *lexer);

struct token lexer_gettoken(struct lexer *lexer);

struct token lexer_lookahead(struct lexer *lexer);

struct token lexer_lookahead2(struct lexer *lexer);

struct token lexer_getheredoc(struct lexer *lexer, const char *delim);

#endif