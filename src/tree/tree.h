#ifndef TREE_H
#define TREE_H

#include <stdio.h>

#include "../common/macro.h"

struct node_if
{
    struct node *condition;
    struct node *c_then;
    struct node *c_else;
};

struct node_for
{
    char *var;
    char **vals;
    struct node *command;
};

struct node_while
{
    struct node *condition;
    struct node *command;
};

struct node_cmd
{
    char **pref;
    size_t sizep;
    char **argv;
    size_t sizea;
};

struct node_funcdec
{
    char *name;
    struct node *body;
};

struct node_case_item
{
    char **pattern;
    struct node *exec;
    struct node_case_item *next;
};

struct node_case
{
    char *word;
    struct node_case_item *items;
};

struct node_bin
{
    struct node *left;
    struct node *right;
};

enum red_type
{
    R_LESS, // <
    R_LESSAND, // <&
    R_GREAT, // >
    R_GREATAND, // >&
    R_DGREAT, // >>
    R_LESSGREAT, // <>
    R_CLOBBER, // >|
    R_DLESS, // <<
    R_DLESSDASH // <<-
};

struct node_red
{
    size_t size;
    enum red_type *type;
    int *fd;
    char **word;
    struct node *mhs;
};

enum node_type
{
    IF, // exec
    FOR, // exec
    CASE, // exec
    WHILE, // exec
    CMD, // exec
    AND, // exec
    OR, // exec
    SUBSHELL, //exec
    FUNCDEC, //exec
    BANG, // exec
    PIPE, // exec
    SEPAND,
    SEP, // exec
    RED
};

union node_data
{
    struct node_if ifnode;
    struct node_for fornode;
    struct node_case casenode;
    struct node_while whilenode;
    struct node_cmd cmdnode;
    struct node_funcdec funcdecnode;
    struct node_red rednode;
    struct node_bin binnode; // pipe, and, or, bang, sep, sepand, subshell
};

struct node
{
    enum node_type type;
    union node_data data;
};

void tree_print_node(struct node *tree_ref, FILE *stream);

struct node *tree_if_create(struct node *c, struct node *c_t, struct node *c_e);
void tree_if_print(struct node *node, FILE *stream);
void tree_if_destroy(struct node *n);

struct node *tree_for_create(char *var, char **vals, struct node *command);
void tree_for_print(struct node *n, FILE *stream);
void tree_for_destroy(struct node *n);

struct node *tree_while_create(struct node *condition, struct node *command);
void tree_while_print(struct node *n, FILE *stream);
void tree_while_destroy(struct node *n);

struct node *tree_cmd_create(void);
void tree_cmd_pref(struct node *node, char *word);
void tree_cmd_argv(struct node *node, char *argv);
void tree_cmd_print(struct node *node, FILE *stream);
void tree_cmd_destroy(struct node *node);

struct node *tree_and_create(struct node *left_node, struct node *right_node);
void tree_and_print(struct node *node, FILE *fs);
void tree_and_destroy(struct node *node);

struct node *tree_or_create(struct node *left, struct node *right);
void tree_or_print(struct node *node, FILE *fs);
void tree_or_destroy(struct node *node);

struct node *tree_subshell_create(struct node *child);
void tree_subshell_print(struct node *node, FILE *fs);
void tree_subshell_destroy(struct node *node);

struct node *tree_funcdec_create(char *name, struct node *body);
void tree_funcdec_print(struct node *node, FILE *fs);
void tree_funcdec_destroy(struct node *node);

struct node *tree_case_create(char *word);
void tree_case_add_item(struct node *node, char **pattern, struct node *exec);
void tree_case_print(struct node *node, FILE *fs);
void tree_case_destroy_node(struct node *node);
void tree_case_destroy(struct node *node);

struct node *tree_bang_create(struct node *child);
void tree_bang_print(struct node *node, FILE *fs);
void tree_bang_destroy(struct node *node);

struct node *tree_pipe_create(struct node *lhs, struct node *rhs);
void tree_pipe_print(struct node *node, FILE *fs);
void tree_pipe_destroy(struct node *node);

struct node *tree_sepand_create(struct node *lhs, struct node *rhs);
void tree_sepand_print(struct node *node, FILE *fs);
void tree_sepand_destroy(struct node *node);

struct node *tree_sep_create(struct node *lhs, struct node *rhs);
void tree_sep_print(struct node *node, FILE *fs);
void tree_sep_destroy(struct node *node);

struct node *tree_red_create(void);
void tree_red_add(struct node *node, enum red_type type, int fd, char *word);
void tree_red_print(struct node *node, FILE *fs);
void tree_red_destroy(struct node *node);

void tree_destroy(struct node *tree);

#endif /* TREE_H */
