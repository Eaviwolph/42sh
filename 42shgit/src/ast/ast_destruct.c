/*
** ast_destruct.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 23:11:01 2006 Seblu
** Last update Tue Oct 17 16:43:29 2006 seblu
*/

#include "ast.h"

typedef void (*destruct_fct)(s_ast_node *);

struct ast_destruct_switch
{
    e_node_type type;
    destruct_fct fct;
};

struct ast_destruct_switch destruction_table[NODE_TYPE_COUNT] = {
    { T_IF, ast_if_destruct },
    { T_FOR, ast_for_destruct },
    { T_WHILE, ast_while_destruct },
    { T_CMD, ast_cmd_destruct },
    { T_AND, ast_and_destruct },
    { T_OR, ast_or_destruct },
    { T_SUBSHELL, ast_subshell_destruct },
    { T_FUNCDEC, ast_funcdec_destruct },
    { T_BANG, ast_bang_destruct },
    { T_PIPE, ast_pipe_destruct },
    { T_SEPAND, ast_sepand_destruct },
    { T_SEP, ast_sep_destruct },
    { T_CASE, ast_case_destruct },
    { T_RED, ast_red_destruct }
};

struct ast_destruct_switch destruction_node_table[NODE_TYPE_COUNT] = {
    { T_IF, ast_if_destruct_node },
    { T_FOR, ast_for_destruct_node },
    { T_WHILE, ast_while_destruct_node },
    { T_CMD, ast_cmd_destruct_node },
    { T_AND, ast_and_destruct_node },
    { T_OR, ast_or_destruct_node },
    { T_SUBSHELL, ast_subshell_destruct_node },
    { T_FUNCDEC, ast_funcdec_destruct_node },
    { T_BANG, ast_bang_destruct_node },
    { T_PIPE, ast_pipe_destruct_node },
    { T_SEPAND, ast_sepand_destruct_node },
    { T_SEP, ast_sep_destruct_node },
    { T_CASE, ast_case_destruct_node },
    { T_RED, ast_red_destruct_node }
};

void ast_destruct(s_ast_node *ast)
{
    if (ast == NULL)
        return;
    for (register int i = 0; i < NODE_TYPE_COUNT; ++i)
        if (destruction_table[i].type == ast->type)
        {
            (destruction_table[i].fct)(ast);
            return;
        }
}

void ast_destruct_node(s_ast_node *ast)
{
    if (ast == NULL)
        return;
    for (register int i = 0; i < NODE_TYPE_COUNT; ++i)
        if (destruction_node_table[i].type == ast->type)
        {
            (destruction_node_table[i].fct)(ast);
            return;
        }
}
