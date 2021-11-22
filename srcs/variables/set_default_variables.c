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
#include "variable.h"

/*
** The underscore variable expands to the last argument to the previous command,
** after expansion.
** It is also set to the full pathname of each command executed and
** placed in the environment.
** exported to that command.
*/

void		add_path_to_env(char *path, char **env)
{
	int		i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (*env[i] == '_' && env[i][1] == '=')
			{
				ft_strdel(&env[i]);
				env[i] = ft_strjoin("_=", path);
				return ;
			}
			i++;
		}
	}
}

void		set_underscore(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		i++;
	if (i > 0)
		i--;
	set_variable("_", words[i], false);
}

static void	set_shlvl(void)
{
	char	*tmp;
	int		shlvl;

	if ((tmp = get_variable("SHLVL")))
	{
		shlvl = ft_atoi(tmp);
		ft_strdel(&tmp);
		tmp = ft_itoa(shlvl + 1);
		set_variable("SHLVL", tmp, false);
		ft_strdel(&tmp);
	}
	else
		set_variable("SHLVL", "1", false);
}

void		set_default_variables(void)
{
	char	*tmp;

	tmp = ft_itoa(getpid());
	set_variable("$", tmp, false);
	ft_strdel(&tmp);
	set_variable("?", "0", false);
	set_variable("SHELL", SHNAME, false);
	set_shlvl();
	set_variable("_", get_shell_env()->path_to_42sh, false);
	tmp = getcwd(NULL, 0);
	set_variable("PWD", tmp, false);
	ft_strdel(&tmp);
}
