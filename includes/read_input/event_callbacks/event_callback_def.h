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

#ifndef EVENT_CALLBACK_DEF_H
# define EVENT_CALLBACK_DEF_H

# include <stdbool.h>
# include "event_callbacks.h"
# include "put_on_tty.h"

typedef enum				e_event_id
{
	NEWLINE_EVID = 0,
	CURSOR_LEFT_EVID,
	CURSOR_RIGHT_EVID,
	CURSOR_UP_EVID,
	CURSOR_DOWN_EVID,
	CURSOR_HOME_EVID,
	CURSOR_END_EVID,
	CURSOR_WORD_RIGHT_EVID,
	CURSOR_WORD_LEFT_EVID,
	HISTORY_UP_EVID,
	HISTORY_DOWN_EVID,
	COPY_EVID,
	CUT_EVID,
	PASTE_EVID,
	CANCEL_EVID,
	EXIT_EVID,
	DELETE_EVID,
	DELETE_RIGHT_EVID,
	TAB_EVID
}							t_event_id;

typedef struct				s_event_callback_def
{
	t_event_id const		id;
	char const *const		name;
	char const *const		str;
	t_event_callback const	callback;
}							t_event_callback_def;

# define EVENT_CALLBACK_DEF_COUNT 21
# define EVENT_STR_MAX_LEN 6

t_event_callback_def const	*get_event_callback_defs(void);
t_event_callback_def const	*get_matching_event_callback(
	char const *str);

void						print_event_callback_defs(void);

#endif
