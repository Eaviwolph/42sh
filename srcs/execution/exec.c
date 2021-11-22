/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:55:26 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:55:44 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "exec.h"
#include "tabenv.h"
#include <unistd.h>
#include <paths.h>

/*
** Retrieve env vars
** retrieve PATH
** if PATH not assign: use default value '/bin:/usr/bin'
** execute
** free memory
*/

void	pre_exec(t_simple_command *cmd)
{
	char	*spath;
	char	**path;
	char	**env;

	env = get_variables_for_execution(cmd->assignments);
	if ((spath = ft_strdup(get_tenv(env, "PATH"))) == NULL)
		spath = ft_strdup(_PATH_DEFPATH);
	path = ft_strsplit(spath, ':');
	ft_strdel(&spath);
	execute(cmd->argv, env, path);
	ft_freetabchar(path);
	ft_freetabchar(env);
}

/*
** Search for executable in PATH paths.
** if found, execute it.
** else if contains '/':
** Execute direct given path like '/bin/ls' or './42sh'
** exit the fork if the no execution because execution stop the fork
** if found nothing: throw a message
*/

void	execute(char **cmd, char **env, char **path)
{
	int		i;
	char	*p_exec;

	i = -1;
	if (ft_strchr(cmd[0], '/') != NULL)
		exec_if_perm_ok(cmd[0], cmd, env);
	else if (path != NULL)
		while (path[++i] != NULL)
		{
			p_exec = ft_strjoinf(path[i], ft_strjoin("/", cmd[0]), 2);
			exec_if_perm_ok(p_exec, cmd, env);
			ft_strdel(&p_exec);
		}
	set_underscore(cmd);
	error_message(cmd[0], "no such command", 127);
}

/*
** Check file exist.
** Check permissions and executions rights on the file.
** If it's ok, execute it.
** Execute it and exit fork.
** Else: error message
*/

void	exec_if_perm_ok(char *path, char **cmd, char **env)
{
	if (access(path, F_OK) != -1)
	{
		if (access(path, X_OK) != -1)
		{
			add_path_to_env(path, env);
			execve(path, &cmd[0], env);
		}
		else
			error_message(path, "no rights to execute it", 126);
	}
}

void	error_message(char *one, char *two, int ret)
{
	ft_dprintf(2, ">%s: %s: %s.\n", SHNAME, one, two);
	exit(ret);
}
