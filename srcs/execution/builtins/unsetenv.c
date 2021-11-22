/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:52:29 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:52:35 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "init/init.h"

int		builtin_unsetenv(int argc, char **argv)
{
	t_variable	**env;
	size_t		i;

	env = &get_shell_env()->variables;
	if (argc > 1)
	{
		i = 0;
		while (argv[++i])
		{
			if (unsetenv_as(env, argv[i]) == STATUS_FAILURE)
			{
				return (STATUS_FAILURE);
			}
		}
		return (STATUS_SUCCESS);
	}
	else
		ft_dprintf(STDERR_FILENO, "Usage: unsetenv <key> …\n");
	return (STATUS_FAILURE);
}

int		unsetenv_as(t_variable **env, char *name)
{
	if (env && ft_strlen(name) > 0)
	{
		if (ft_strchr(name, '='))
		{
			ft_dprintf(STDERR_FILENO, "It's forbidden to use '='\n");
			return (STATUS_FAILURE);
		}
		if (variable_is_overwritable(*env, name))
		{
			if (pop_variable_by_name(env, name) == STATUS_SUCCESS)
			{
				return (STATUS_SUCCESS);
			}
		}
		else
			return (STATUS_SUCCESS);
	}
	return (STATUS_FAILURE);
}
