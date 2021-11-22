/*
** prompt.c for 42sh in /home/seblu
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 02:27:59 2006 Seblu
** Last update Wed Oct 18 21:08:51 2006 seblu
*/

#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "../common/macro.h"

/*!
** Return a prompt given by PS1, PS2, PS4 or the default if not set
**
** @param type
**
** @return
*/
const char	*get_prompt(e_prompt pty)
{
  static char	prompt[80];
  //fixme
  if (pty == PROMPT_PS1) {
    strncpy(prompt, shell->name, 78);
    strcpy(prompt + strlen(shell->name), "$ ");
  }
  else if (pty == PROMPT_PS2)
    strcpy(prompt, "> ");
  else if (pty == PROMPT_PS4)
    return strcpy(prompt, "");
  return prompt;
}

//todo gestion des variables !
void		show_prompt(e_prompt pty)
{
  if (!isinteractive())
    return;
  fflush(stderr);
  switch (pty) {
  default:
  case PROMPT_PS1:
    fprintf(stderr, "%s$ ", shell->name);
    break;
  case PROMPT_PS2:
    fprintf(stderr, "> ");
    break;
  case PROMPT_PS4:
    fprintf(stderr, "+ ");
    break;
  }
  fflush(stderr);
}
