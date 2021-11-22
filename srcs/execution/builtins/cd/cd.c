/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 16:28:59 by asenat            #+#    #+#             */
/*   Updated: 2017/06/27 18:27:29 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/builtins/cd.h"

static char		*parse_options(t_uchar *opt_addr, int argc, char **argv)
{
	char	*str;

	(void)argc;
	*opt_addr = '\0';
	if (*argv == NULL)
		return (NULL);
	argv++;
	while ((str = *argv) != NULL)
	{
		if (str[0] == '-' && (str[1] == 'L' || str[1] == 'P'))
			*opt_addr = str[1];
		else
			return (ft_strdup(str));
		argv++;
	}
	return (NULL);
}

int				builtin_cd(int argc, char **argv)
{
	char	*directory;
	char	*curpath;
	char	*current_pwd;
	t_uchar	opt;
	int		ret;

	current_pwd = getcwd(NULL, 0);
	curpath = NULL;
	directory = parse_options(&opt, argc, argv);
	if (directory == NULL && go_home(current_pwd, &directory) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strequ(directory, "-"))
	{
		free(directory);
		ft_strdel(&current_pwd);
		return (cd_oldpwd());
	}
	handle_special_cases(&curpath, directory);
	ret = go_standard(directory, &curpath, &current_pwd, opt);
	free(curpath);
	free(directory);
	ft_strdel(&current_pwd);
	return ((ret != 0) ? 2 : 0);
}
