/*
** var.h for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 13:54:14 2006 seblu
** Last update Thu Nov 23 11:41:04 2006 seblu
*/

#ifndef VAR_H_
# define VAR_H_

# include <stddef.h>

enum {
  VAR_DEFAULT_SIZE = 25,
  VAR_PADDING = 10,
};

typedef struct	var_item
{
  char		*value;
  char		*name;
} s_var_item;

/*!
** The variable structure
**  - table: The table of variables
**  - count: The number of variables
**  - size: The size of the table (mem alloced)
*/
typedef struct	var
{
  s_var_item	*table;
  size_t	count;
  size_t	size;
} s_var;

/*!
** Create a malloced variable structure
**
** @return new variable structure
*/
s_var		*var_init(void);

/*!
** Get a variable in a var struct
**
** @param var variable struct
** @param name variable name
**
** @return value of the variable, NULL if not exist
*/
const char	*var_get(const s_var *var, const char *name);

/*!
** Add a variable to a variable contener
**
** @param var contener of variable
** @param name variable name to add
** @param value variable value to add
**
** @return true if variable already exist else false
*/
int		var_add(s_var *var, const char *name, const char *value);

/*!
** Delete a variable from a variable contener
**
** @param var contener name
** @param name variable to destroy
**
** @return boolean del success (i.e. if exist or not)
*/
int		var_del(s_var *var, const char *name);

#endif /* ! VAR_H_ */
