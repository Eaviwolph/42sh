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
#include "macro/macro.h"

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
    //struct node_case casenode;
    struct node_while whilenode;
    /*struct node_cmd cmdnode;
    struct node_and amdnode;
    struct node_or ornode;
    struct node_subsh subshnode;
    struct node_funcdec funcdecnode;
    struct node_bang bangnode;
    struct node_pipe pipenode;
    struct node_sepand sepandnode;
    struct node_sep sepnode;
    struct nodered rednode;*/
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

void tree_destroy(struct node *tree);
void tree_destroy_node(struct node *tree);

#endif /* TREE_H */