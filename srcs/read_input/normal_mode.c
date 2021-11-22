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

#include <libft.h>
#include <signal.h>
#include "read_input/editor/editor.h"
#include "read_input/event_callbacks/event_callback_def.h"
#include "read_input/termcap/init_deinit.h"
#include "control_character.h"
#include "completion.h"

static void		add_buffer_to_string(t_editor *ed, char buf[])
{
	size_t	i;

	i = -1;
	while (buf[++i])
	{
		if (ft_isprint(buf[i]) || buf[i] == '\t')
			add_to_string(ed, buf[i]);
	}
}

static void		handle_etx(t_editor *ed)
{
	if (get_shell_env()->last_unmatched)
		get_shell_env()->del_input = true;
	get_shell_env()->last_unmatched = NO_ERROR;
	print_control_char_notation(ETX);
	ev_cursor_end(ed);
	putstr_on_tty("\n");
	change_string(ed, "");
	ed->pos = get_cursor_vector(ed);
	ed->need_refresh = true;
	ed->last_event = 0;
	clear_down(ed);
	ft_strdel(&ed->history_saved_current_string);
}

static bool		handle_control_char(t_editor *ed, char buf[])
{
	if (buf[0] == ETX && buf[1] == NUL)
	{
		handle_etx(ed);
		return (true);
	}
	return (false);
}

static bool		handle_callback(t_editor *ed, char buf[])
{
	t_event_callback_def const	*def;

	def = get_matching_event_callback(buf);
	if (def)
	{
		def->callback(ed);
		ed->last_event = (ed->last_event != -1) ? def->id : 0;
		if (def->id == NEWLINE_EVID)
			return (true);
	}
	else
	{
		ed->last_event = 0;
		close_history(ed);
		add_buffer_to_string(ed, buf);
	}
	return (false);
}

char			*start_normal_mode(t_editor *ed)
{
	char						buf[EVENT_STR_MAX_LEN + 1];
	int							ret;

	put_line(ed);
	while ((ret = read(0, buf, EVENT_STR_MAX_LEN)) > 0 && ed->in_edition)
	{
		buf[ret] = '\0';
		if (handle_control_char(ed, buf))
		{
			ft_close_termcaps();
			return (NULL);
		}
		if (handle_callback(ed, buf))
			break ;
		refresh_line(ed);
	}
	ft_close_termcaps();
	return (get_string_from_list(ed->string));
}
