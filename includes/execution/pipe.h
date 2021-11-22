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

#ifndef PIPE_H
# define PIPE_H

# include "utils.h"
# include "errors.h"
# include <unistd.h>
# include <libft.h>

# define FORKED_IN_CHILD ((pid_t)0)

typedef struct		s_pipe
{
	int		fds[2];
}					t_pipe;

typedef struct		s_pipeline_state
{
	t_pipe					*prev_pipe;
	t_pipe					*next_pipe;
	bool					last_cmd;
	pid_t					last_pid;
	int						last_ret;
}					t_pipeline_state;

pid_t				enter_subshell(void);
t_pipe				*create_pipe(void);
void				delete_pipe(t_pipe **p);
int					pipe_get_read_fd(t_pipe const *p);
int					pipe_get_write_fd(t_pipe const *p);
void				create_next_pipe(t_pipeline_state *state);
void				overwrite_fd(int src, int overwrited);
int					pipe_me_in(t_pipeline_state *state);

#endif
