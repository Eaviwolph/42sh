/*
** func.h for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 14:52:22 2006 seblu
** Last update Thu Nov 23 11:26:57 2006 seblu
*/

#ifndef FUNC_H_
# define FUNC_H_

# include <assert.h>
# include "../ast/ast.h"

enum {
  FUNC_DEFAULT_SIZE = 5,
  FUNC_PADDING = 5
};

typedef struct	func_item
{
  char		*name;
  s_ast_node	*body;
} s_func_item;

typedef struct	func
{
  s_func_item	*table;
  size_t	count;
  size_t	size;
} s_func;

/*!
** Init a function structure.
**
** @return a malloced func structure
*/
s_func		*func_init(void);

/*!
** Return if @var name is a function.
**
** @param func func struct
** @param name function name
**
** @return boolean existance
*/
int		func_exist(s_func *func, const char *name);

/*!
** Add a function.
** @warning @var name and @var body are not copied.
** Not free/modify it after adding function.
** Return a boolean which explain if function @var name
** has been deleted before insertion.
** Think to delete reference in the tree, his destruction
** will destroy @var name and @var body.
**
** @param func func struct
** @param name func name
** @param body func body
**
** @return an boolean already exist function information
*/
int		func_add(s_func *func, char *name, s_ast_node *body);

/*!
** Delete a function and destroy is AST.
**
** @param func func struct
** @param name func name to deleted
**
** @return Boolean delete success
*/
int		func_del(s_func *func, const char *name);

/*!
** Return the function body of a function.
**
** @param func func struct
** @param name func name
**
** @return ast node to corresponding to the function
*/
s_ast_node	*func_get(s_func *func, const char *name);

#endif
