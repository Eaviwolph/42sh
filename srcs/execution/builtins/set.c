/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:52:51 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:52:52 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_def.h"
#include <libft.h>
#include <signal.h>
#include "shell_env.h"
#include "abstract_list.h"
#include "init/init.h"

int		builtin_set(int argc, char **argv)
{
	t_variable	**env;

	env = &get_shell_env()->variables;
	if (argc == 1)
	{
		display_variables(false);
		return (STATUS_SUCCESS);
	}
	else if (argc == 2 || argc == 3)
	{
		if (ft_strchr(argv[1], '='))
		{
			ft_dprintf(STDERR_FILENO, "It's forbidden to use '='\n");
			return (STATUS_FAILURE);
		}
		if (setenv_as(env, argv[1], argv[2], false) == STATUS_SUCCESS)
			return (STATUS_SUCCESS);
	}
	else
		ft_dprintf(STDERR_FILENO, "Usage: set <key> <value>\n");
	return (STATUS_FAILURE);
}
