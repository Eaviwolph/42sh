/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_core_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 16:28:54 by asenat            #+#    #+#             */
/*   Updated: 2017/06/29 17:12:45 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/builtins/cd.h"

void			set_curpath_from_pwd(char **str_addr)
{
	char	*path;

	if (str_addr == NULL || *str_addr == NULL)
		fatal_error("NULL ptr fed to set_curpath_from_pwd");
	if ((*str_addr)[0] == '/')
		return ;
	path = getcwd(0, 0);
	if (!last_is_slash(path))
		path = ft_strjoinf(path, "/", 1);
	*str_addr = ft_strjoinf(path, *str_addr, 3);
}

void			save_the_day(char **curpath_addr, char const *directory,
					char const *pwd)
{
	char	*str;

	if (curpath_addr == NULL || *curpath_addr == NULL)
		fatal_error("NULL ptr fed to save_the_day");
	if (!(ft_strlen(*curpath_addr) + 1 > PATH_MAX &&
				ft_strlen(directory) + 1 <= PATH_MAX))
		return ;
	if (!last_is_slash(pwd))
		str = ft_strjoin(pwd, "/");
	else
		str = ft_strdup(pwd);
	if (!ft_strstr(*curpath_addr, str))
		return ;
	strfreeswap(curpath_addr, ft_strdup((*curpath_addr) + ft_strlen(str)));
	free(str);
}

char			*test_cdpath(char const *dir, char const *path)
{
	char	*result;

	result = NULL;
	if (!(path == NULL || path[0] == '\0'))
	{
		if (last_is_slash(path))
			result = ft_strdup(path);
		else
			result = ft_strjoin(path, "/");
		result = ft_strjoinf(result, dir, 1);
	}
	else
		result = ft_strjoin("./", dir);
	if (result != NULL && !is_directory(result))
		ft_strdel(&result);
	return (result);
}

char			*find_cdpath(char const *directory)
{
	char	*cdpath;
	char	**slices;
	char	*str;
	size_t	u;

	cdpath = get_variable("CDPATH");
	if (cdpath == NULL)
		cdpath = ft_strdup("");
	slices = ft_strsplit(cdpath, ':');
	u = 0;
	str = NULL;
	while (u == 0 || slices[u] != NULL)
	{
		str = test_cdpath(directory, slices[u]);
		if (str != NULL)
			break ;
		if (u == 0 && slices[u] == NULL)
			break ;
		u++;
	}
	free(cdpath);
	ft_freetabchar(slices);
	return (str);
}

BUILTIN_RET		cd_oldpwd(void)
{
	BUILTIN_RET	ret;
	char		*oldpwd;
	char		*s;

	oldpwd = get_variable("OLDPWD");
	if (oldpwd == NULL)
	{
		ft_putendl_fd("42sh: cd -: OLDPWD not set", 2);
		return (EXIT_FAILURE);
	}
	ret = builtin_cd(2, (char*[]){"cd", oldpwd, NULL});
	if (ret == EXIT_SUCCESS)
	{
		ft_putendl(s = getcwd(0, 0));
		ft_strdel(&s);
	}
	free(oldpwd);
	return (ret);
}
