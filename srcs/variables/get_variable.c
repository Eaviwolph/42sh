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

char	*get_variable(char *var)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env)
	{
		if (ft_strcmp(env->name, var) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	display_variables(bool only_exported)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	if (only_exported)
	{
		while (env)
		{
			if (env->exported == true)
				ft_printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
	else
	{
		while (env)
		{
			ft_printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
}
