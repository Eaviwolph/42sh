/*
** option.h for 42sh
**
** Made by Seblu
** Login  <seblu@epita.fr>
**
** Started on  Tue Mar 21 18:50:03 2006 Seblu
** Last update Wed Nov 15 13:35:32 2006 seblu
*/

#ifndef OPTION_H_
# define OPTION_H_

#define DEBUG_OPTION 0

enum { OPTION_COUNT = 10 };

typedef struct option
{
  signed char	item[OPTION_COUNT];
  char		*command;
} s_option;

/*
** ==============
** FILE: option.c
** ==============
*/

/*!
** Create a new options structure
**
** @return A new options structure
*/
s_option	*option_init(void);

/*!
** Set default shell options
**
** @param opt option struct
*/
void		option_set_default(s_option *shopt);

/*!
** Set a shell option
**
** @param shopt structure to apply
** @param name name of the option to set
**
** @return 0 on failure, else 1
*/
int		option_set(s_option *shopt, const char *name);

/*!
** Unset a shell option
**
** @param shopt structure to apply
** @param name name of the option to unset
**
** @return 0 on failure, else 1
*/
int		option_unset(s_option *shopt, const char *name);

/*!
** Tell if an option is set. if option nane is not set return -1
**
** @param shopt structure where find
** @param name name to find
**
** @return 0 if unset, 1 if set and -1 if not exist
*/
int		option_is_set(const s_option *shopt, const char *name);

/*!
** Return a list of know opt
**
** @return list of opt
*/
const char	**opt_get();

/*
** =====================
** FILE: getoption.c
** =====================
*/

/*!
** Parse the command line and set options
**
** @param opt shell opt structure to set with options
** @param argc program argc
** @param argv program argv
*/
void		getoptions(s_option *opt, int argc, char **argv);

#endif
