/*
** builtin.h for 42sh in /home/seblu/svn/42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Nov 12 16:46:24 2006 Seblu
** Last update Fri Nov 17 13:01:45 2006 seblu
*/

#ifndef BUILTIN_H_
# define BUILTIN_H_

typedef int	(*f_builtin)(char *argv[]);

/*!
** Says if @var name is a builtin.
**
** @param name builtin name
**
** @return boolean existance
*/
int		is_a_builtin(const char *name);

/*!
** Return a pointer on a builtin function
**
** @param name builtin name
**
** @return pointer on the builtin function @var name
*/
f_builtin	get_builtin(const char *name);

/*!
** Builtin Change Directory
**
** @param argv argument vector
**
** @return success status
*/
int		builtin_cd(char *argv[]);

/*!
** Echo show all element on her line
**
** @param argc number of argument given
**
** @return sucess status
*/
int		builtin_echo(char *argv[]);

/*!
** This builtin change local setting of the shell
**
** @param argv argument vector
**
** @return success status
*/
int		builtin_shopt(char *argv[]);

/*!
** Builtin exit :)
**
** @param argv argument vector
**
** @return success status
*/
int		builtin_exit(char *argv[]);

/*!
** Set or show aliases.
**
** @param argv argument vector
**
** @return 0 on succes, or 1 if no alias found
*/
int		builtin_alias(char *argv[]);

/*!
** Unset one or more aliases
**
** @param argv argument vector
**
** @return 0 on success, or 1 if no alias found
*/
int		builtin_unalias(char *argv[]);


int		builtin_source(char *argv[]);
int		builtin_set(char *argv[]);
int		builtin_unset(char *argv[]);
int		builtin_exec(char *argv[]);
int		builtin_export(char *argv[]);



/*
** Bonus builtin
*/
/* int	builtin_simpledot(char *argv[], struct s_42sh *sh); */
/* int	builtin_doubledot(char *argv[], struct s_42sh *sh); */
/* int	builtin_set(char *argv[], struct s_42sh *sh); */
/* int	builtin_varlist(char *argv[], struct s_42sh *sh); */
/* int	builtin_funclist(char *argv[], struct s_42sh *sh); */
/* int	builtin_exec(char *argv[], struct s_42sh *sh); */
/* int	builtin_history(char *argv[], struct s_42sh *sh); */

#endif /* ! BUILTIN_H_ */
