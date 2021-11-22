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
#include "completion.h"
#include <libft.h>

static int	is_first_word(char *str, int pos)
{
	int letter_found;

	letter_found = 0;
	while (pos-- && *str)
	{
		if (*str == ' ' && letter_found)
			return (0);
		else if (*str != ' ')
			letter_found = 1;
		++str;
	}
	return (1);
}

EV_CB_RET	ev_tab(t_editor *ed)
{
	char	*line;
	char	*path;
	int		first_w;

	if (ed->in_selection || !ed->string)
		return ;
	line = get_string_from_list(ed->string);
	first_w = is_first_word(line, ed->cursor_position);
	while (line[ed->cursor_position] != ' ' && line[ed->cursor_position])
		ev_cursor_right(ed);
	path = get_cur_word(ed->cursor_position, line);
	if (first_w && !ft_strchr(path, '/'))
		choice_tab(ed, line, path, 1);
	else
		choice_tab(ed, line, path, 0);
	ft_strdel(&line);
}
