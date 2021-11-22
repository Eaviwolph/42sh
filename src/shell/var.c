/*
** var.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 13:55:46 2006 seblu
** Last update Thu Nov 23 11:35:56 2006 seblu
*/

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "var.h"
#include "../common/macro.h"
#include "../common/function.h"

s_var			*var_init(void)
{
  s_var			*var;

  secmalloc(var, sizeof (s_var));
  var->count = 0;
  var->size = VAR_DEFAULT_SIZE;
  secmalloc(var->table, var->size * sizeof (s_var_item));
  return var;
}

int			var_add(s_var *var, const char *name, const char *value)
{
  assert(var && name && value);
  //check for add or update
  for (register size_t i = 0; i < var->count; ++i)
    if (!strcmp(name, var->table[i].name)) {
      //update time
      free(var->table[i].value);
      var->table[i].value = strdup(value);
      return 1;
    }
  //add time
  ++var->count;
  if (var->size < var->count) {
    var->size += VAR_PADDING;
    secrealloc(var->table, var->table, var->size * sizeof (s_var_item));
  }
  var->table[var->count - 1].name = strdup(name);
  var->table[var->count - 1].value = strdup(value);
  return 0;
}

int			var_exist(s_var *var, const char *name)
{
  assert(var && name);
  for (register size_t i = 0; i < var->count; ++i)
    if (!strcmp(name, var->table[i].name))
      return 1;
  return 0;
}

const char		*var_get(const s_var *var, const char *name)
{
  assert(name && var);
  for (size_t i = 0; i < var->count; ++i) {
    if (!(var->table[i].name))
      continue;
    if (!strcmp(var->table[i].name, name))
      return var->table[i].value;
  }
  return NULL;
}

int			var_del(s_var *var, const char *name)
{
  register size_t	i;

  assert(var && name);
  for (i = 0; i < var->count; ++i)
    if (!strcmp(name, var->table[i].name))
      break;
  if (i >= var->count)
    return 0;
  free(var->table[i].name);
  free(var->table[i].value);
  var->table[i] = var->table[--var->count];
  if (var->size - var->count > 2 * VAR_PADDING) {
    var->size -= VAR_PADDING;
    secrealloc(var->table, var->table, var->size * sizeof (s_var_item));
  }
  return 1;
}
