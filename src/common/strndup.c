/*
** strndup.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu Aug  3 05:56:28 2006 Seblu
** Last update Fri Aug 25 03:49:08 2006 Seblu
*/

#include <string.h>
#include <stdlib.h>
#include "macro.h"

char            *strndup(const char *str, size_t n)
{
  size_t        length;
  size_t        max_length;
  size_t        i;
  char          *new;

  max_length = n;
  if ((length = strlen(str)) > max_length)
    length = max_length;
  secmalloc(new, (length + 1) * sizeof (char));
  for (i = 0; i < length; ++i)
    new[i] = str[i];
  new[length] = 0;
  return new;
}
