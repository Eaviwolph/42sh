/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:02:03 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 16:04:23 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

void			create_next_pipe(t_pipeline_state *state)
{
	state->next_pipe = create_pipe();
	if (state->next_pipe == NULL)
	{
		ft_putendl_fd("42sh: failed to create pipe", 2);
		exit(EXIT_FAILURE);
	}
}

void			overwrite_fd(int src, int overwrited)
{
	int		ret;

	ret = dup2(src, overwrited);
	if (ret < 0)
	{
		print_errno_error(errno, "dup2 failed in overwrite_fd", "");
		exit(EXIT_FAILURE);
	}
}

static void		pipe_me_in_2(t_pipeline_state *state, pid_t fork_ret)
{
	if (fork_ret == FORKED_IN_CHILD)
	{
		if (state->prev_pipe != NULL)
			overwrite_fd(pipe_get_read_fd(state->prev_pipe), STDIN_FILENO);
		if (state->next_pipe != NULL)
			overwrite_fd(pipe_get_write_fd(state->next_pipe), STDOUT_FILENO);
		delete_pipe(&state->prev_pipe);
	}
	else
	{
		delete_pipe(&state->prev_pipe);
		state->prev_pipe = state->next_pipe;
		state->next_pipe = NULL;
		state->last_pid = fork_ret;
	}
}

int				pipe_me_in(t_pipeline_state *state)
{
	pid_t	fork_ret;

	if (state == NULL)
	{
		ft_putendl_fd("42sh: fed null ptr(s) to pipe_me_in", 2);
		exit(EXIT_FAILURE);
	}
	if (state->next_pipe != NULL)
	{
		ft_putendl_fd("42sh: state->next_pipe set while at pipe_me_in", 2);
		exit(EXIT_FAILURE);
	}
	if (!state->last_cmd)
		create_next_pipe(state);
	fork_ret = enter_subshell();
	pipe_me_in_2(state, fork_ret);
	return (fork_ret);
}
