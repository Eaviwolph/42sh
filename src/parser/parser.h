#ifndef PARSER_H
#define PARSER_H

#include <setjmp.h> // lib that allow gotos

#include "../tree/tree.h"
#include "dtoken.h"
#include "extendedgetline.h"

// Define is parser or lexer is running for DEBUGGING
#define DEBUG_PARSER 0
#define DEBUG_LEXER 0

// used just like macros
enum
{
    TOKEN_COUNT = 23,
    KEYWORD_COUNT = 15,
    FD_MAX = 32765,
    REGISTER_REDUCE_SIZE = 200,
    REGISTER_DEFAULT_SIZE = 50,
};

struct token token_cache;

typedef enum type token_id;

struct parser
{
    int error;
    struct lexer *lexer;
    jmp_buf stack;
    struct node **regnodes;
    size_t regsize;
    size_t regpos;
};

struct parser *parser_init(int fd);

struct node *parse(struct dtoken *tokens, struct dalias *s);

int is_prefix(struct token t);

#endif
