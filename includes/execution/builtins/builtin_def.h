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

#ifndef BUILTIN_DEF_H
# define BUILTIN_DEF_H

# include <stdbool.h>
# include "builtins.h"

typedef enum				e_builtin_id
{
	CD_BUID = 0,
	ECHO_BUID,
	EXIT_BUID,
	SETENV_BUID,
	UNSETENV_BUID,
	SET_BUID,
	UNSET_BUID,
	EXPORT_BUID,
	HISTORY_BUID,
	ENV_BUID
}							t_builtin_id;

typedef struct				s_builtin_def
{
	t_builtin_id const			id;
	char const *const			name;
	t_builtin const				builtin;
}							t_builtin_def;

# define BUILTIN_DEF_COUNT 8

t_builtin_def const			*get_builtin_defs(void);
t_builtin_def const			*get_matching_builtin(char const *str);

void						print_builtin_def(t_builtin_def const *def);
void						print_builtin_defs(void);

#endif
