/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:55:48 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 16:55:03 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_syntax_tree.h"
#include "utils.h"
#include <libft.h>
#include "variable.h"
#include <stdio.h>

static char		*get_backup_var(t_variable *env_backup, char *name)
{
	t_variable	*env;
	char		*val;

	val = NULL;
	env = get_shell_env()->variables;
	get_shell_env()->variables = env_backup;
	val = get_variable(name);
	if (!val && variable_exist(env_backup, name))
		val = ft_strnew(1);
	get_shell_env()->variables = env;
	return (val);
}

static void		set_env_exec(t_variable **env_backup, t_variable *assignments)
{
	*env_backup = copy_variable(get_shell_env()->variables);
	set_assignments(assignments, true);
}

static void		restore_env(t_variable *env_backup, t_variable *assignments)
{
	char		*val;

	while (assignments)
	{
		val = get_backup_var(env_backup, assignments->name);
		if (val)
			setenv_as(&get_shell_env()->variables, assignments->name,
					val, true);
		else
			unsetenv_as(&get_shell_env()->variables, assignments->name);
		ft_strdel(&val);
		assignments = assignments->next;
	}
}

static int		exec_builtin_corpse(t_simple_command *cmd, t_error_id *ret,
					t_variable **env_backup, t_builtin_def const **builtin)
{
	set_variable("_", cmd->argv[0], false);
	if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		set_env_exec(env_backup, cmd->assignments);
		*ret = builtin_env(ft_tablen(cmd->argv), cmd->argv, cmd);
	}
	else
	{
		*builtin = get_matching_builtin(cmd->argv[0]);
		if (*builtin == NULL)
			return (NO_SUCH_BUILTIN);
		set_env_exec(env_backup, cmd->assignments);
		if ((*builtin)->builtin == NULL)
			return (NO_SUCH_BUILTIN);
		*ret = (*builtin)->builtin(ft_tablen(cmd->argv), cmd->argv);
		set_variable("_", cmd->argv[ft_tablen(cmd->argv) - 1], false);
	}
	if (!is_special_builtin(cmd->argv[0]))
		restore_env(*env_backup, cmd->assignments);
	delete_all_variables(env_backup);
	return (NO_ERROR);
}

t_error_id		execute_builtin(t_simple_command *cmd, size_t lvl)
{
	t_error_id				ret;
	t_builtin_def const		*builtin;
	t_variable				*env_backup;

	(void)lvl;
	if (cmd->argv[0] == NULL)
		fatal_error("NULL argv[0] fed to execute_builtin");
	ret = NO_ERROR;
	if (cmd != NULL)
		if (exec_builtin_corpse(cmd, &ret, &env_backup, &builtin)
				== NO_SUCH_BUILTIN)
			return (NO_SUCH_BUILTIN);
	if (get_error() != ENV_EXEC_ERR)
		set_last_exit_status(ret);
	if (ret != 0)
		ret = CHILD_FAILURE;
	return (ret);
}
