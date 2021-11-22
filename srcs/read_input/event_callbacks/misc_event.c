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

#include "event_callback_def.h"
#include "abstract_list.h"
#include "read_input/termcap/init_deinit.h"
#include <libft.h>

EV_CB_RET	ev_newline(t_editor *ed)
{
	ev_cursor_end(ed);
	close_history(ed);
	add_to_string(ed, '\n');
	clear_selected_pos(ed);
	refresh_line(ed);
}

EV_CB_RET	ev_cancel(t_editor *ed)
{
	(void)ed;
}

EV_CB_RET	ev_exit(t_editor *ed)
{
	if (ed->string_size == 0 && get_shell_env()->last_unmatched == NO_ERROR)
	{
		write(STDOUT_FILENO, "\x0A", 1);
		ft_close_termcaps();
		builtin_exit(0, NULL);
	}
}

EV_CB_RET	ev_delete(t_editor *ed)
{
	void **p;

	if (ed->cursor_position <= 0)
		return ;
	ed->need_refresh = true;
	ev_cursor_left(ed);
	p = list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
	free(p);
}

EV_CB_RET	ev_delete_right(t_editor *ed)
{
	void **p;

	ed->need_refresh = true;
	p = list_pop_at_pos(ed->cursor_position, (t_abstract_list **)&ed->string);
	free(p);
}
