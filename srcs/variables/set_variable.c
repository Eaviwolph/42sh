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

#include <libft.h>
#include "shell_env.h"

void			set_variable(char const *var, char const *val, bool overwrite)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, var) == 0)
		{
			free(env->value);
			env->value = ft_strdup(val);
			return ;
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	if (env)
		env->next = create_variable(var, val, false, overwrite);
	else
	{
		get_shell_env()->variables = create_variable(var, val, false
			, overwrite);
	}
}

void			set_assignments(t_variable *assignments, bool export)
{
	while (assignments)
	{
		setenv_as(&get_shell_env()->variables, assignments->name,
					assignments->value, export);
		assignments = assignments->next;
	}
}
