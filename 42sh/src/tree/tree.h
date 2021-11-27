#ifndef TREE_H
#define TREE_H

// typedef c'est un alias

// node_type (type)
//   the enum for all types
// node_item (body)
//      contains the data for each type, but only one is used
//      data types are:
//          if_node (cond, cond_true, cond_false) these are all nodes
//          for_node (varname*, values**, *exec) exec is a node pointer
//          NOT AN AST NODE
//          case_item (**pattern, *exec, *next) exec and next are node pointers
//          case_node (*word, *items) items is a case_item (upper)
//          while_node (*cond, *next) are nodes
//          red_node (size, RED_TYPE type, *fd, **word, *mhs)
//              red_type is an enum  of diff reds "< <& >.."
//          cmd_node (**argv, **prefix) list of strings
//          bin_node (*lhs, *rhs) node used for a tree of operators (BANG, PIPE, SEP..)
//          funcdec_node (*name, *body) body is a ast node

// NODE_TYPE_COUNT = 14

// ast_node est le type des noeuds (type, body)

// each node_item have a
//  -create node
//  -print tree
//  -destruct node
//  -destruct tree

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
    char **argv;
    char **pref;
};

struct node_and
{
    struct node *left;
    struct node *right;
};

struct node_or
{
    struct node *left;
    struct node *right;
};

struct node_subsh
{
    struct node *left;
    struct node *right;
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
  struct case_item *next;
};

struct node_case
{
  char *word;
  struct case_item *items;
};

struct node_bang
{
    struct node *left;
    struct node *right;
};

struct node_pipe
{
    struct node *left;
    struct node *right;
};

struct node_sepand
{
    struct node *left;
    struct node *right;
};

struct node_sep
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
} ;

typedef struct node_red
{
    size_t size;
    enum red_type *type;
    int *fd;
    char **word;
    struct node *mhs;
};

enum node_type
{
    IF,
    FOR,
    CASE,
    WHILE,
    CMD,
    AND,
    OR,
    SUBSHELL,
    FUNCDEC,
    BANG,
    PIPE,
    SEPAND,
    SEP,
    RED
};
#define NODE_TYPE_COUNT 14

union node_data
{
    struct node_if ifnode;
    struct node_for fornode;
    struct node_case casenode;
    struct node_while whilenode;
    struct node_cmd cmdnode;
    struct node_and andnode;
    struct node_or ornode;
    struct node_subsh subshnode;
    struct node_funcdec funcdecnode;
    struct node_bang bangnode;
    struct node_pipe pipenode;
    struct node_sepand sepandnode;
    struct node_sep sepnode;
    struct node_red rednode;
};

struct node
{
    enum node_type type;
    union node_data data;
};

void tree_print_node(struct node * tree_ref, FILE *stream);

void tree_if_print(struct node *node, FILE *stream);
void tree_if_destroy_node(struct node *n);
void tree_if_destroy(struct node *n);

void tree_for_print(struct node *n, FILE *stream);
void tree_for_destroy_node(struct node *n);
void tree_for_destroy(struct node *n);

void tree_while_print(struct node *n, FILE *stream);
void tree_while_destroy_node(struct node *n);
void tree_while_destroy(struct node *n);

void tree_cmd_pref(struct node *node, char *word);
void tree_cmd_argv(struct node *node, char *argv);
void tree_cmd_print(struct node *node, FILE *stream);
void tree_cmd_destroy_node(struct node *node);
void tree_cmd_destroy(struct node *node);

void tree_and_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_and_destroy_node(struct node *node);
void tree_and_destroy(struct node *node);

void tree_or_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_or_destroy_node(struct node *node);
void tree_or_destroy(struct node *node);

void tree_subshell_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_subshell_destroy_node(struct node *node);
void tree_subshell_destroy(struct node *node);

void tree_funcdec_print(struct node *node, FILE *fs, unsigned *node_id);
void tree_funcdec_destroy_node(struct node *node);
void tree_funcdec_destroy(struct node *node);

void tree_case_add_item(struct node *node, char **pattern, struct node *exec);
void tree_case_print(struct node *node, FILE *fs, unsigned *node_id);
void tree_case_destroy_node(struct node *node);
void tree_case_destroy(struct node *node);

void tree_bang_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_bang_destroy_node(struct node *node);
void tree_bang_destroy(struct node *node);

void tree_pipe_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_pipe_destroy_node(struct node *node);
void tree_pipe_destroy(struct node *node);

void tree_sepand_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_sepand_destroy_node(struct node *node);
void tree_sepand_destroy(struct node *node);

void tree_sep_print(struct node *node, FILE *fs, unsigned int *node_id);
void tree_sep_destroy_node(struct node *node);
void tree_sep_destroy(struct node *node);

void tree_red_add(struct node *node, enum red_type type, int fd, char *word);
void tree_red_print(struct node *node, FILE *fs, unsigned *node_id);
void tree_red_destroy_node(struct node *node);
void tree_red_destroy(struct node *node);

void tree_destroy(struct node *tree);
void tree_destroy_node(struct node *tree);

#endif /* TREE_H */