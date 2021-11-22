/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 17:57:27 by asenat            #+#    #+#             */
/*   Updated: 2017/06/27 18:26:34 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/builtins/cd.h"

bool		last_is_slash(char const *str)
{
	if (str == NULL)
		return (false);
	return (str[ft_strlen(str) - 1] == '/');
}

bool		first_comp_is_dot_or_dotdot(char const *str)
{
	if ((str[0] == '.' && (str[1] == '/' || str[1] == '\0'))
			|| (str[0] == '.' && str[1] == '.' && (str[2] == '/'
					|| str[2] == '\0')))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

int			go_home(char *current_pwd, char **directory)
{
	char *home;

	home = get_variable("HOME");
	if (home == NULL || home[0] == '\0')
	{
		ft_putendl_fd("42sh: cd: HOME not set", 2);
		ft_strdel(&current_pwd);
		ft_strdel(&home);
		return (EXIT_FAILURE);
	}
	else
		*directory = home;
	return (0);
}

int			go_standard(char *directory, char **curpath,
		char **current_pwd, t_uchar opt)
{
	char	*new_pwd;
	int		ret;

	if (opt != 'P')
	{
		set_curpath_from_pwd(curpath);
		strfreeswap(curpath, canonicalize_path(*curpath));
		if (*curpath == NULL)
		{
			free(directory);
			ft_strdel(current_pwd);
			return (EXIT_SUCCESS);
		}
		save_the_day(curpath, directory, *current_pwd);
	}
	ret = chdir(*curpath);
	new_pwd = getcwd(0, 0);
	(ret == -1) ? print_errno_error(errno, "cd", *curpath) : 0;
	if (ret != -1)
	{
		set_variable("OLDPWD", *current_pwd, true);
		set_variable("PWD", new_pwd, true);
		ft_strdel(&new_pwd);
	}
	return (ret);
}

void		handle_special_cases(char **curpath, char *directory)
{
	if (directory[0] == '/')
		*curpath = ft_strdup(directory);
	else
	{
		if (!first_comp_is_dot_or_dotdot(directory))
			*curpath = find_cdpath(directory);
		if (*curpath == NULL)
			*curpath = ft_strdup(directory);
	}
}
