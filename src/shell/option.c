/*
** opt_shopt.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Mar 21 19:00:38 2006 Seblu
** Last update Fri Nov 17 14:36:27 2006 seblu
*/

/*
** ============
** DECLARATIONS
** ============
*/

#include <string.h>
#include "option.h"
#include "../shell/shell.h"
#include "../common/macro.h"

static const char *opts_table[OPTION_COUNT] = {
  "xpg_echo",
  "dotglob",
  "extglob",
  "nocaseglob",
  "nullglob",
  "expand_aliases",
  "ast_print",
  "readline",
  "noclobber",
};

/*
** ===========
** DEFINITIONS
** ===========
*/

s_option	*option_init(void)
{
  s_option	*new;

  secmalloc(new, sizeof (s_option));
  new->command = NULL;
  return new;
}

void		option_set_default(s_option *shopt)
{
  //unset all
  for (int i = 0; i < OPTION_COUNT; ++i)
    shopt->item[i] = 0;
  //set those which are on by default
  option_set(shopt, "readline");
}

int		option_set(s_option *shopt, const char *name)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i])) {
      shopt->item[i] = 1;
      return 1;
    }
  return 0;
}

int		option_unset(s_option *shopt, const char *name)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i]))
    {
      shopt->item[i] = 0;
      return 1;
    }
  return 0;
}

int		option_is_set(const s_option *shopt, const char *name)
{
  register int	i;

  for (i = 0; opts_table[i]; ++i)
    if (!strcmp(name, opts_table[i]))
      return shopt->item[i];
  return -1;
}

const char	**opt_get()
{
  return opts_table;
}
