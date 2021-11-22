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

#ifndef EVENT_CALLBACKS_H
# define EVENT_CALLBACKS_H

# include "read_input/editor/editor.h"

# define EV_CB_RET void
# define EV_CB_ARGS t_editor *ed

typedef EV_CB_RET	(*t_event_callback)(t_editor *ed);

void	ev_cursor_right(t_editor *ed);
void	ev_newline(t_editor *ed);
void	ev_cursor_left(t_editor *ed);
void	ev_cursor_right(t_editor *ed);
void	ev_cursor_up(t_editor *ed);
void	ev_cursor_down(t_editor *ed);
void	ev_cursor_home(t_editor *ed);
void	ev_cursor_end(t_editor *ed);
void	ev_wrd_r(t_editor *ed);
void	ev_wrd_l(t_editor *ed);
void	ev_history_up(t_editor *ed);
void	ev_history_down(t_editor *ed);
void	ev_copy(t_editor *ed);
void	ev_cut(t_editor *ed);
void	ev_paste(t_editor *ed);
void	ev_cancel(t_editor *ed);
void	ev_exit(t_editor *ed);
void	ev_delete(t_editor *ed);
void	ev_delete_right(t_editor *ed);
void	ev_tab(t_editor *ed);

#endif
