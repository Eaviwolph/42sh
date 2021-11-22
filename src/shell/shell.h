/*
** shell.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 16 20:03:53 2006 Seblu
** Last update Thu Nov 16 16:54:53 2006 seblu
*/

#ifndef SHELL_H_
# define SHELL_H_

# include "../common/constant.h"
# include "alias.h"
# include "var.h"
# include "option.h"
# include "func.h"

typedef struct	shell
{
  s_var			*var;
  s_func		*func;
  s_alias		*alias;
  s_option		*option;
  char			*name;
  int			status;
} s_shell;

const char		*get_prompt(e_prompt pty);

/*!
** Show a prompt on stderr is current shell is a plug on a tty
**
** @param pty prompt type (PS1, PS2, PS4)
*/
void			show_prompt(e_prompt pty);

extern s_shell		*shell;

#endif /* !SHELL_H_ */
