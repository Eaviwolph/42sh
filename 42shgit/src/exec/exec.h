/*
** execution.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Mar 30 16:02:07 2006 Seblu
** Last update Fri Nov 17 14:27:55 2006 seblu
*/

#ifndef EXEC_H_
# define EXEC_H_

# include <assert.h>
# include "../ast/ast.h"
# include "../shell/shell.h"

# define DEBUG_EXEC 0

/*!
** Exec an ast node. Call an exec function according node type
**
** @param node node to execute.
*/
void		exec_node(s_ast_node *node);

/*!
** Execute a command.
**
** @param cmd command to execute
*/
void		exec_cmd(s_cmd_node *cmd);

/*!
** Execute a command in a pipeline. This call preserve for too
** many system call fork Take care, this must be called after a fork
**
** @param cmd command to execute
*/
void		exec_piped_cmd(s_cmd_node *cmd);

void		exec_case(s_case_node *node);

void		exec_for(s_for_node *node);

void		exec_and(s_bin_node *node);
void		exec_or(s_bin_node *node);
void		exec_bang(s_bin_node *node);
void		exec_if(s_if_node *node);
void		exec_pipe(s_bin_node *node);
void		exec_red(s_red_node *node);
void		exec_while(s_while_node *node);

/*!
** Execute a task list
**
** @param node task list
*/
void		exec_sep(s_bin_node *node);

/*!
** Execute a task in background
**
** @param node backgroudn task node
*/
void		exec_sepand(s_bin_node *node);

/*!
** Execute a function declaration.
** Register this function.
**
** @param node function to register
*/
void		exec_funcdec(s_funcdec_node *node);

/*!
** Execute a subshell
**
** @param node node to treat
*/
void		exec_subshell(s_bin_node *node);

#endif
