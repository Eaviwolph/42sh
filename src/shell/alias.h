/*
** alias.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Aug 23 00:32:09 2006 Seblu
** Last update Thu Nov 23 11:24:08 2006 seblu
*/

#ifndef ALIAS_H_
# define ALIAS_H_

# include <stddef.h>

enum {
  ALIAS_DEFAULT_SIZE = 5,
  ALIAS_PADDING = 5
};

typedef struct alias_item
{
  char		*name;
  char		*value;
} s_alias_item;

typedef struct alias
{
  size_t	size;
  size_t	count;
  s_alias_item	*table;
} s_alias;

/*!
** Create a new aliases database
**
** @return new alias database
*/
s_alias		*alias_init(void);

/*!
** Add an alias into an alias database
**
** @param aliases alias database
** @param name new alias name
** @param value new alias value
*/
int		alias_add(s_alias *alias, const char *name, const char *value);

/*!
** Remove an alias into an alias database
**
** @param aliases alias database
** @param name alias name to remove
**
** @return true, if alias was delete from database, else false
*/
int		alias_del(s_alias *alias, const char *name);

#endif
