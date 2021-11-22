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

#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include "uint.h"
#include "errors.h"
#include "utils.h"
#include "execution/signal_error_exec.h"
#include <signal.h>

static void	handle_wait_status(int wstatus)
{
	t_uchar	estatus;

	if (WIFEXITED(wstatus))
	{
		estatus = WEXITSTATUS(wstatus);
		set_last_exit_status(estatus);
		if (estatus != EXIT_SUCCESS)
			set_error(CHILD_FAILURE);
	}
	if (WIFSIGNALED(wstatus))
	{
		estatus = WTERMSIG(wstatus);
		if (estatus != SIGINT)
			ft_dprintf(STDERR_FILENO, "%s: error signal -%d --%s\n",
				SHNAME, wstatus, get_signal_error(wstatus));
		set_last_exit_status(estatus + 128);
	}
}

void		wait_for_children(void)
{
	int		wstatus;

	set_error(NO_ERROR);
	wstatus = 0;
	while (wait(&wstatus) != -1 && errno != ECHILD)
		;
	handle_wait_status(wstatus);
}

void		wait_for_last_child(pid_t last_child_pid)
{
	int		wstatus;

	set_error(NO_ERROR);
	wstatus = 0;
	while (waitpid(last_child_pid, &wstatus, 0) != last_child_pid && !errno)
		;
	handle_wait_status(wstatus);
}
