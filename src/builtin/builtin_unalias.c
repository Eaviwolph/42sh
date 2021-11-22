/*
** builtin_unalias.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Nov 16 17:18:24 2006 seblu
** Last update Fri Nov 17 12:41:53 2006 seblu
*/

#include <assert.h>
#include "builtin.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "../shell/shell.h"

static int	getoption(char *argv[], int *argp, int *p);

int		builtin_unalias(char *argv[])
{
  int		argp;
  char		*carg;
  int		all = 0;
  int		ret = 0;

  assert(argv && argv[0]);
  if (!getoption(argv, &argp, &all))
    return 2;
  if (argv[1] == NULL || all)
    for (size_t i = 0; i < shell->alias->count; ++i)
      alias_del(shell->alias, shell->alias->table[i].name);
  for (; (carg = argv[argp]); ++argp) {
    if (!alias_del(shell->alias, argv[argp])) {
      printf("%s: unalias: %s: not found.\n", shell->name, argv[argp]);
      ret = 1;
    }
  }
  return ret;
}

static int	getoption(char *argv[], int *argp, int *p)
{
  char		*carg;

  for (*argp = 1; (carg = argv[*argp]); ++*argp)
    if (*carg == '-')
      for (++carg; *carg; ++carg)
	if (*carg == 'a')
	  *p = 1;
	else {
	  fprintf(stderr, "%s: unalias: -%c: invalid option.\n",
		  shell->name, *carg);
	  fprintf(stderr, "unalias: usage: unalias [-a] name [name ...]\n");
	  return 0;
	}
    else
      break;
  return 1;
}
