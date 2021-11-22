/*
** builtin_alias.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Nov 16 17:18:24 2006 seblu
** Last update Thu Nov 23 11:23:49 2006 seblu
*/

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "../shell/shell.h"

static int	show_alias(const char *name);
static int	getoption(char *argv[], int *argp, int *p);

int		builtin_alias(char *argv[])
{
  int		argp;
  char		*carg;
  char		*equal;
  int		all = 0;
  int		ret = 0;

  assert(argv && argv[0]);
  if (!getoption(argv, &argp, &all))
    return 2;
  if (argv[1] == NULL || all)
    for (size_t i = 0; i < shell->alias->count; ++i)
      printf("alias %s='%s'\n", shell->alias->table[i].name,
	     shell->alias->table[i].value);
  for (; (carg = argv[argp]); ++argp) {
    if (!(equal = strchr(carg, '=')))
      ret = show_alias(carg) || ret;
    else {
      *equal = 0;
      alias_add(shell->alias, carg, equal + 1);
      *equal = '=';
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
	if (*carg == 'p')
	  *p = 1;
	else {
	  fprintf(stderr, "%s: alias: -%c: invalid option.\n",
		  shell->name, *carg);
	  fprintf(stderr, "alias: usage: alias [-p] [name[=value]] ... ]\n");
	  return 0;
	}
    else
      break;
  return 1;
}

static int	show_alias(const char *name)
{
  for (size_t i = 0; i < shell->alias->count; ++i)
    if (!strcmp(shell->alias->table[i].name, name)) {
      printf("alias %s='%s'\n", shell->alias->table[i].name,
	     shell->alias->table[i].value);
      return 0;
  }
  printf("%s: alias: %s: not found.\n", shell->name, name);
  return 1;
}
