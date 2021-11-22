/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42shTeam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:35:21 by 42shTeam          #+#    #+#             */
/*   Updated: 2017/05/03 15:35:21 by 42shTeam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "execution/builtins/builtins.h"
# include "variable.h"
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include "uint.h"
# include "errors.h"
# include <errno.h>
# include "utils.h"
# include "strlist.h"
# include <limits.h>

char			*canonicalize_path(char const *path);
bool			comp_is_directory(t_strlist *start, t_strlist *end);
void			remove_dots(t_strlist **cmpnts_addr);
bool			comp_is_dot_dot(char const *comp);
bool			comp_is_dot(char const *comp);
t_strlist		*break_components(char const *path);

int				go_home(char *cur_pwd, char **directory);
int				go_standard(char *directory, char **curpath,
					char **current_pwd, t_uchar opt);
void			handle_special_cases(char **curpath, char *directory);
bool			first_comp_is_dot_or_dotdot(char const *str);
bool			last_is_slash(char const *str);
BUILTIN_RET		cd_oldpwd(void);
char			*find_cdpath(char const *directory);
char			*test_cdpath(char const *dir, char const *path);
void			save_the_day(char **curpath_addr, char const *directory,
					char const *pwd);
void			set_curpath_from_pwd(char **str_addr);

#endif
