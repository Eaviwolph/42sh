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
#include <libft.h>

EV_CB_RET	ev_cursor_up(t_editor *ed)
{
	t_vec2i pos;
	char	*s;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y - 1);
	s = get_string_from_list(ed->string);
	if (ed->cursor_position > 0 && s[ed->cursor_position - 1] == '\n' && pos.x)
		ed->cursor_position--;
	free(s);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}

EV_CB_RET	ev_cursor_down(t_editor *ed)
{
	t_vec2i pos;
	char	*s;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = find_index_at_vector(ed, pos.x, pos.y + 1);
	s = get_string_from_list(ed->string);
	if (ed->cursor_position > 0 && s[ed->cursor_position - 1] == '\n' && pos.x)
		ed->cursor_position--;
	free(s);
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}
