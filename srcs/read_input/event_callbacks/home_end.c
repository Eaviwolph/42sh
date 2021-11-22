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

EV_CB_RET	ev_cursor_home(t_editor *ed)
{
	t_vec2i		pos;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = 0;
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}

EV_CB_RET	ev_cursor_end(t_editor *ed)
{
	t_vec2i		pos;

	ed->need_refresh = true;
	pos = get_cursor_vector(ed);
	ed->cursor_position = ed->string_size;
	move_cursor_to(pos, get_cursor_vector(ed), ed->term);
	ed->pos = get_cursor_vector(ed);
}
