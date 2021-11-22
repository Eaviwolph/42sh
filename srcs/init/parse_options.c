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

#include "shell_env.h"

void	parse_options(int argc, char **argv, t_shell_env *shell_env)
{
	if (argc > 1 && ft_strequ(argv[1], "-c"))
	{
		if (argc > 2)
		{
			shell_env->command_string = ft_strdup(argv[2]);
		}
		else
		{
			ft_putendl_fd("42sh: usage: -c command_string", 2);
			exit(2);
		}
	}
}
