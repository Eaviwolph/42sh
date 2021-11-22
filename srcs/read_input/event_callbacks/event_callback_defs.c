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

#include <stdlib.h>
#include "event_callback_def.h"
#include "uint.h"
#include "libft.h"

t_event_callback_def const	*get_event_callback_defs(void)
{
	static t_event_callback_def const defs[EVENT_CALLBACK_DEF_COUNT] =
	{{ NEWLINE_EVID, "NEWLINE", "\n", ev_newline },
		{ CURSOR_LEFT_EVID, "CURSOR_LEFT", "\x1b[D", ev_cursor_left },
		{ CURSOR_RIGHT_EVID, "CURSOR_RIGHT", "\x1b[C", ev_cursor_right },
		{ CURSOR_UP_EVID, "CURSOR_UP", "\x1b\x5b\x35\x7e", ev_cursor_up },
		{ CURSOR_UP_EVID, "CURSOR_UP", "\x1b[1;5A", ev_cursor_up },
		{ CURSOR_DOWN_EVID, "CURSOR_DOWN", "\x1b[1;5B", ev_cursor_down },
		{ CURSOR_DOWN_EVID, "CURSOR_DOWN", "\x1b\x5b\x36\x7e", ev_cursor_down },
		{ CURSOR_HOME_EVID, "CURSOR_HOME", "\x1b[H", ev_cursor_home },
		{ CURSOR_END_EVID, "CURSOR_END", "\x1b[F", ev_cursor_end },
		{ CURSOR_WORD_RIGHT_EVID, "CURSOR_WORD_RIGHT", "\x1b[1;5C", ev_wrd_r },
		{ CURSOR_WORD_LEFT_EVID, "CURSOR_WORD_LEFT", "\x1b[1;5D", ev_wrd_l },
		{ HISTORY_UP_EVID, "HISTORY_UP", "\x1b[A", ev_history_up },
		{ HISTORY_DOWN_EVID, "HISTORY_DOWN", "\x1b[B", ev_history_down },
		{ COPY_EVID, "COPY", "\x2", ev_copy },
		{ CUT_EVID, "CUT", "\xb", ev_cut },
		{ PASTE_EVID, "PASTE", "\x10", ev_paste },
		{ CANCEL_EVID, "CANCEL", "\x3", ev_cancel },
		{ EXIT_EVID, "EXIT", "\x4", ev_exit },
		{ DELETE_EVID, "DELETE", "\x7f", ev_delete },
		{ DELETE_RIGHT_EVID, "DELETE_RIGHT", "\x1b[3~", ev_delete_right },
		{ TAB_EVID, "TAB", "\x9", ev_tab }
	};

	return (defs);
}

t_event_callback_def const	*get_matching_event_callback(char const *str)
{
	t_uint						u;
	t_event_callback_def const	*defs;

	defs = get_event_callback_defs();
	u = 0;
	while (u < EVENT_CALLBACK_DEF_COUNT)
	{
		if (defs[u].str != NULL &&
			ft_strncmp(defs[u].str, str, ft_strlen(defs[u].str)) == 0)
			return (defs + u);
		u++;
	}
	return (NULL);
}
