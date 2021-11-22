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
#include "history/history_def.h"
#include "utils.h"

void		close_history(t_editor *ed)
{
	free(ed->history_saved_current_string);
	ed->history_saved_current_string = NULL;
	ed->in_history = false;
	ed->history_current = NULL;
}

EV_CB_RET	ev_history_up(t_editor *ed)
{
	if (!ed->in_history)
	{
		ed->history_current = ed->history;
		ft_strdel(&ed->history_saved_current_string);
		ed->history_saved_current_string = get_string_from_list(ed->string);
	}
	else if (ed->history_current->prev)
	{
		ed->history_current = ed->history_current->prev;
	}
	if (ed->history_current)
	{
		ed->in_history = true;
		ed->need_refresh = true;
		change_string(ed, ed->history_current->line);
	}
}

EV_CB_RET	ev_history_down(t_editor *ed)
{
	if (!ed->in_history)
	{
		ed->history_current = ed->history;
		ft_strdel(&ed->history_saved_current_string);
		ed->history_saved_current_string = get_string_from_list(ed->string);
	}
	if (ed->history_current)
	{
		ed->in_history = true;
		ed->need_refresh = true;
		if (ed->history_current)
			ed->history_current = ed->history_current->next;
		if (ed->history_current)
		{
			change_string(ed, ed->history_current->line);
		}
		else
		{
			change_string(ed, ed->history_saved_current_string);
			close_history(ed);
		}
	}
}
