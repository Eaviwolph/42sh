/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:01:50 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 16:01:58 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>

pid_t				enter_subshell(void)
{
	pid_t		fork_ret;

	fork_ret = fork();
	if (fork_ret < 0)
	{
		ft_putendl_fd("42sh: failed to fork", 2);
		exit(EXIT_FAILURE);
	}
	return (fork_ret);
}

t_pipe				*create_pipe(void)
{
	t_pipe		*p;
	int			ret;

	p = memalloc_or_die(sizeof(t_pipe));
	ret = pipe(p->fds);
	if (ret != 0)
		ft_memdel((void**)&p);
	return (p);
}

void				delete_pipe(t_pipe **p)
{
	if (p == NULL)
	{
		ft_putendl_fd("42sh: unexpected null t_pipe** in delete_pipe", 2);
		exit(EXIT_FAILURE);
	}
	if ((*p) == NULL)
		return ;
	close((*p)->fds[0]);
	close((*p)->fds[1]);
	ft_memdel((void**)p);
}

int					pipe_get_read_fd(t_pipe const *p)
{
	if (p == NULL)
		return (-1);
	return (p->fds[0]);
}

int					pipe_get_write_fd(t_pipe const *p)
{
	if (p == NULL)
		return (-1);
	return (p->fds[1]);
}
