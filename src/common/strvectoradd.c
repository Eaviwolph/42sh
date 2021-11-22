/*
** strvectoradd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:59:48 2006 Seblu
** Last update Thu Oct 12 16:30:05 2006 seblu
*/

#include <stdlib.h>
#include "macro.h"

char		**strvectoradd(char **vector, char *str)
{
  size_t	vector_size = 0;

  if (str == NULL)
    return vector;
  if (vector)
    for (vector_size = 0; vector[vector_size]; ++vector_size)
      ;
  ++vector_size;
  secrealloc(vector, vector, (vector_size + 1) * sizeof (char *));
  vector[vector_size - 1] = str;
  vector[vector_size] = NULL;
  return vector;
}
