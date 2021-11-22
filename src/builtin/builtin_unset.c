/*
** builtin_unset.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu May 11 09:36:06 2006 Seblu
** Last update Fri Nov 17 13:09:29 2006 seblu
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../shell/var.h"
#include "../shell/func.h"
#include "../shell/shell.h"

int		builtin_unset(char *argv[])
{
  int		f = 0;
  int		v = 1;

  assert(argv);
  for (int i = 0; argv[i]; ++i)
    if (!strcmp(argv[i], "-v"))
      v = 1;
    else if (!strcmp(argv[i], "-f"))
      f = 1;
  for (int i = 0; argv[i]; ++i)
    if (argv[i][0] == '-')
      continue;
    else {
      if (v) var_del(shell->var, argv[i]);
      if (f) func_del(shell->func, argv[i]);
    }
  return 0;
}
