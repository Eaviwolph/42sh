/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:00:28 by asenat            #+#    #+#             */
/*   Updated: 2017/06/28 13:07:20 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input/syntax_tree.h"
#include "errors.h"
#include "utils.h"
#include <libft.h>
#include "execute_syntax_tree.h"
#include "pipe.h"
#include "exec.h"
#include "redirection.h"
#include "expansion/expansion.h"
#include "errno.h"
#include <signal.h>

t_error_id	execute_file(t_simple_command *cmd, size_t lvl)
{
	t_error_id	ret;

	(void)lvl;
	if (cmd->argv[0] == NULL)
		fatal_error("NULL argv[0] fed to execute_file");
	if (enter_subshell() == FORKED_IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		pre_exec(cmd);
		print_errno_error(errno, cmd->argv[0], NULL);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait_for_children();
		if (cmd->argv && cmd->argv[0])
			set_variable("_", cmd->argv[ft_tablen(cmd->argv) - 1], false);
		else
		{
			set_assignments(cmd->assignments, false);
			set_variable("_", NULL, false);
		}
		ret = get_last_exit_status();
	}
	return (ret);
}

t_error_id	execute_simple_command(t_simple_command *cmd, size_t lvl)
{
	t_error_id	ret;
	int			*stdin_out_backup;

	ret = NO_ERROR;
	if (cmd != NULL)
	{
		expand_cmd_words(&cmd->argv);
		if ((ret = get_error()) != NO_ERROR)
			return (ret);
		stdin_out_backup = save_stdin_stdout();
		ret = redirect(cmd->redirections, stdin_out_backup);
		expand_assignments_values(cmd->assignments);
		if (ret == NO_ERROR && cmd->argv[0] == NULL)
			set_assignments(cmd->assignments, false);
		if (ret != NO_ERROR || cmd->argv[0] == NULL)
			return (ret);
		ret = execute_builtin(cmd, lvl + 1);
		if (ret == NO_SUCH_BUILTIN)
			ret = execute_file(cmd, lvl + 1);
		restore_stdin_stdout(stdin_out_backup);
	}
	return (ret);
}

t_error_id	execute_pipeline(t_simple_command *pipeline, size_t lvl)
{
	t_error_id			ret;
	t_pipeline_state	pipeline_state;

	if (pipeline == NULL)
		return (NO_ERROR);
	if (pipeline->next == NULL)
		return (execute_simple_command(pipeline, lvl));
	ft_bzero(&pipeline_state, sizeof(t_pipeline_state));
	ret = NO_ERROR;
	while (pipeline != NULL)
	{
		if (pipeline->next == NULL)
			pipeline_state.last_cmd = true;
		if (pipe_me_in(&pipeline_state) == FORKED_IN_CHILD)
		{
			if ((ret = execute_simple_command(pipeline, lvl + 1)) == NO_ERROR)
				exit(EXIT_SUCCESS);
			else
				exit(EXIT_FAILURE);
		}
		pipeline = pipeline->next;
	}
	wait_for_last_child(pipeline_state.last_pid);
	kill(0, SIGINT);
	return (ret);
}
