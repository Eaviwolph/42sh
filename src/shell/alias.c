/*
** alias.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug 23 00:39:17 2006 Seblu
** Last update Thu Nov 23 11:24:39 2006 seblu
*/

#include <string.h>
#include <assert.h>
#include "alias.h"
#include "../common/macro.h"

/*
** ===========
** DEFINITIONS
** ===========
*/

s_alias		*alias_init(void)
{
  s_alias	*new;

  secmalloc(new, sizeof (s_alias));
  new->count = 0;
  new->size = ALIAS_DEFAULT_SIZE;
  secmalloc(new->table, new->size * sizeof (s_alias_item));
  return new;
}

int		alias_add(s_alias *alias, const char *name, const char *value)
{
  int		ret;

  assert(alias && name);
  ret = alias_del(alias, name);
  ++alias->count;
  if (alias->size < alias->count) {
    alias->size += ALIAS_PADDING;
    secrealloc(alias->table, alias->table, alias->size * sizeof (s_alias_item));
  }
  alias->table[alias->count - 1].name = strdup(name);
  alias->table[alias->count - 1].value = strdup(value);
  return ret;
}

int		alias_del(s_alias *alias, const char *name)
{
  register size_t	i;

  assert(alias && name);
  for (i = 0; i < alias->count; ++i)
    if (!strcmp(name, alias->table[i].name))
      break;
  if (i >= alias->count)
    return 0;
  free(alias->table[i].name);
  free(alias->table[i].value);
  alias->table[i] = alias->table[--alias->count];
  if (alias->size - alias->count > 2 * ALIAS_PADDING) {
    alias->size -= ALIAS_PADDING;
    secrealloc(alias->table, alias->table, alias->size * sizeof (s_alias_item));
  }
  return 1;
}
