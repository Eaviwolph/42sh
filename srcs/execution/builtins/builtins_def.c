/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_def.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:51:43 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:51:46 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_def.h"
#include <stdlib.h>
#include "uint.h"
#include <libft.h>

/*
**     ID			NAME	HANDLER FUNCTION
*/

t_builtin_def const			*get_builtin_defs(void)
{
	static t_builtin_def const defs[BUILTIN_DEF_COUNT] =
	{{ CD_BUID, "cd", builtin_cd },
		{ ECHO_BUID, "echo", builtin_echo },
		{ EXIT_BUID, "exit", builtin_exit },
		{ SETENV_BUID, "setenv", builtin_setenv },
		{ UNSETENV_BUID, "unsetenv", builtin_unsetenv },
		{ SET_BUID, "set", builtin_set },
		{ EXPORT_BUID, "export", builtin_export },
		{ UNSET_BUID, "unset", builtin_unset }
	};

	return (defs);
}

t_builtin_def const			*get_matching_builtin(char const *str)
{
	t_uint				u;
	t_builtin_def const	*defs;

	if (str != NULL)
	{
		defs = get_builtin_defs();
		u = 0;
		while (u < BUILTIN_DEF_COUNT)
		{
			if (defs[u].name != NULL && ft_strequ(defs[u].name, str))
				return (defs + u);
			u++;
		}
	}
	return (NULL);
}
