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
#include "init/init.h"
#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "history/builtin/history.h"
#include "errors.h"
#include "utils.h"

static void	init_variables_list(t_shell_env *shell_env)
{
	extern char	**environ;
	char		**line;
	t_variable	*var;
	size_t		i;

	i = -1;
	while (environ[++i])
	{
		line = ft_strsplit(environ[i], '=');
		if (line && ft_tablen(line) == 2 &&
			ft_strlen(line[0]) > 0 && ft_strlen(line[1]) > 0)
		{
			var = create_variable(line[0], line[1], true, true);
			list_push_back((t_abstract_list**)&shell_env->variables\
				, (t_abstract_list*)var);
		}
		ft_freetabchar(line);
	}
}

static char	*get_path_to_ftsh(char const *ftsh_name)
{
	char		*cwd;

	if (ftsh_name == NULL)
		fatal_error("NULL ptr fed to get_path_to_ftsh()");
	if (ftsh_name[0] == '/')
		return (ft_strdup(ftsh_name));
	if (ftsh_name[0] == '.' && ftsh_name[1] == '/')
		ftsh_name += 2;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		fatal_error("getcwd(NULL, 0) failed in get_path_to_ftsh()");
	return (ft_strjoinf(cwd, ft_strjoin("/", ftsh_name), 3));
}

static void	set_histfile(t_shell_env *shell_env)
{
	char	*tmp;

	tmp = ft_strsub(shell_env->path_to_42sh, 0, \
		ft_strlen(shell_env->path_to_42sh) - ft_strlen(SHNAME) - 1);
	shell_env->history.histfile = ft_strjoin(tmp, "/.");
	ft_strdel(&tmp);
	tmp = ft_strjoin(shell_env->history.histfile, SHNAME);
	ft_strdel(&shell_env->history.histfile);
	shell_env->history.histfile = ft_strjoin(tmp, "_history");
	ft_strdel(&tmp);
}

static void	set_as_appended(t_history *history)
{
	while (history)
	{
		history->appended = true;
		history = history->next;
	}
}

void		init(int ac, char **av)
{
	t_shell_env		*shell_env;

	set_error(NO_ERROR);
	shell_env = get_shell_env();
	ft_bzero(shell_env, sizeof(t_shell_env));
	ft_bzero(&shell_env->history, sizeof(t_sh_history));
	if ((shell_env->tty_fd = open("/dev/tty", O_WRONLY)) == -1)
		shell_env->tty_fd = 1;
	shell_env->path_to_42sh = get_path_to_ftsh(av[0]);
	init_variables_list(shell_env);
	set_default_variables();
	parse_options(ac, av, shell_env);
	set_histfile(shell_env);
	load_history(shell_env, shell_env->history.histfile, 0);
	set_as_appended(shell_env->history.list);
	shell_env->should_run = true;
}
