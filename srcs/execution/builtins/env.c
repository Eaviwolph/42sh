/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:53:33 by asenat            #+#    #+#             */
/*   Updated: 2017/06/27 12:38:19 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../execute_pipeline.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <paths.h>

/*
** retrive '-i' option
** if '-i' empty var env, set e as NULL
** else: retrive current env var
** do a backup of env var
** use new env
** restore previous env var
*/

#define STATUS_WRONG_USAGE 125

int			builtin_env(int argc, char **argv, t_simple_command *cmd)
{
	char		*opt;
	t_variable	*e;
	t_variable	*save;

	if ((opt = get_options_core(argc, argv)) == (char *)-1)
		return (STATUS_FAILURE);
	if (check_only_allowed_option(opt, "i") == false)
	{
		ft_dprintf(STDERR_FILENO, "Usage: env [-i] name[=word]…\n");
		return (STATUS_WRONG_USAGE);
	}
	e = ft_strchr(opt, 'i') != NULL ? NULL : \
		copy_variable(get_shell_env()->variables);
	save = get_shell_env()->variables;
	ft_strdel(&opt);
	get_shell_env()->variables = e;
	run_env(argc, argv, cmd);
	delete_all_variables(&(get_shell_env()->variables));
	get_shell_env()->variables = save;
	if (get_error() == ENV_EXEC_ERR)
		set_last_exit_status(get_last_exit_status());
	return (STATUS_SUCCESS);
}

/*
** pass options
** add env var specified as argument
** if not last arg: execute last arguments with options: mv position of exec
** else: display env var
*/

void		run_env(int argc, char **argv, t_simple_command *cmd)
{
	int		i;
	char	**split;
	char	**fre;

	i = 1;
	while (i < argc && argv[i][0] == '-')
		if (argv[i++][1] == '-')
			break ;
	while (i < argc && ft_strchr(argv[i], '=') != NULL)
	{
		split = ft_strsplit(argv[i++], '=');
		setenv_as(&get_shell_env()->variables, split[0], split[1], true);
		ft_freetabchar(split);
	}
	if (argc > i)
	{
		fre = cmd->argv;
		cmd->argv = ft_tabdup(&(cmd->argv[i]));
		ft_freetabchar(fre);
		execute_simple_command(cmd, 0);
		if (get_last_exit_status())
			set_error(ENV_EXEC_ERR);
	}
	else
		display_variables(true);
}
