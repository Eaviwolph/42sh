/*
** builtin_exit.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Nov 12 16:48:50 2006 Seblu
** Last update Wed Nov 15 15:20:00 2006 seblu
*/

#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "../shell/shell.h"
#include "../common/macro.h"

int	builtin_exit(char *argv[])
{
  long	i;
  char	*endptr;

  assert(argv && argv[0]);
  if (!argv[1])
    exit(shell->status);
  if (argv[2]) {
    fprintf(stderr, "42sh : exit : too many arguments\n");
    return 1;
  }
  i = strtol(argv[1], &endptr, 10);
  if (isinteractive())
    fprintf(stderr, "exit\n");
  if (*endptr)
    fprintf(stderr, "42sh: exit: %s: numeric argument required\n", argv[1]);
  exit((!*endptr) ? i : 255);
  return 1;
}
