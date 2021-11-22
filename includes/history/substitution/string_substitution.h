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

#ifndef STRING_SUBSTITUTION_H
# define STRING_SUBSTITUTION_H

# include "libft.h"
# include "shell_env.h"
# include "errors.h"
# include "utils.h"
# include "abstract_list.h"

# include "history_substitutions.h"
# include "read_input/editor/editor_struct.h"
# include "read_input/editor/editor.h"

/*
**			substitute_str.c
*/

void	substitute_str(char *modifier, char **str, t_uint *i,
			bool repeat);
void	substitute_words_str(char *modifiers, char **str, t_uint *i);
void	replace_and_repeat(t_str_subst *subst, char **str);

/*
**			delimit_substitution
*/

char	*get_delimited_str(char *modifier, char delimiter, t_uint *i);
void	take_out_backslashes(char **str, char delimiter);

#endif
