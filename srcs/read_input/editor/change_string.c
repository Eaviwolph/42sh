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

#include "read_input/editor/editor.h"
#include "abstract_list.h"

void	change_string(t_editor *ed, char *line)
{
	char	*trimed;

	clear_selected_pos(ed);
	list_free((t_abstract_list **)&ed->string);
	trimed = ft_strtrim(line);
	str_to_list_in_editor(ed, trimed);
	ed->string_size = list_count((t_abstract_list *)ed->string);
	ed->cursor_position = ed->string_size;
	free(trimed);
}
