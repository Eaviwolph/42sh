/*
** getline.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug  2 01:25:01 2006 Seblu
** Last update Tue Oct 17 09:51:30 2006 seblu
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../common/macro.h"
#include "getline.h"

/*!
** Secure layer over strlen
**
** @param s the string
**
** @return lenght of the string
*/
#define sstrlen(s) ((s) == NULL ? 0 : strlen(s))

/*
** Append a string to the buffer string
*/
static void     buf_str(char **str, char *append, unsigned n)
{
  unsigned      ln;
  unsigned      i;
  unsigned      j;

  ln = sstrlen(*str);
  secrealloc(*str, *str, (ln + n + 1) * sizeof (char));
  for (i = ln, j = 0; i < ln + n; i++, j++)
    (*str)[i] = append[j];
  (*str)[ln + n] = 0;
}

s_getline	*getline_open(int fd)
{
  s_getline	*new_buf;

  secmalloc(new_buf, sizeof (s_getline));
  new_buf->fd = fd;
  new_buf->size = 0;
  new_buf->offset = 0;
  return new_buf;
}

void            getline_close(s_getline *buf, int closefd)
{
  if (closefd)
    close(buf->fd);
  free(buf);
}

char            *getline(s_getline *buf)
{
  char          *string = NULL;
  int           i;

  do
  {
    for (i = buf->offset; i < buf->size; i++)
      {
        if (buf->data[i] == '\n')
          {
            buf_str(&string, buf->data + buf->offset, i - buf->offset + 1);
            buf->offset = i + 1;
            return string;
          }
      }
    if (buf->size - buf->offset > 0)
      buf_str(&string, buf->data + buf->offset, buf->size - buf->offset);
    buf->offset = 0;
    buf->size = read(buf->fd, buf->data, GETLINE_BUF_SIZE);
    if (buf->size < 0)
      buf->size = 0;
  }
  while (buf->size > 0);
  return string;
}
