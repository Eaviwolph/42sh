/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_moving.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:16:12 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:16:14 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static void		increase_tabindex(int inc)
{
	t_tabinfo	*inf;
	int			len;

	inf = get_tabinfo();
	len = list_count((t_abstract_list*)inf->list);
	inf->selected_index += inc;
	if (inf->selected_index >= len)
		inf->selected_index -= len;
	else if (inf->selected_index < 0)
		inf->selected_index += len;
}

void			tab_down(t_editor *ed, char *line)
{
	increase_tabindex(1);
	tab_display(ed, line, get_tabinfo());
}

void			tab_up(t_editor *ed, char *line)
{
	increase_tabindex(-1);
	tab_display(ed, line, get_tabinfo());
}

void			tab_right(t_editor *ed, char *line)
{
	increase_tabindex(get_tabinfo()->nb_lines);
	tab_display(ed, line, get_tabinfo());
}

void			tab_left(t_editor *ed, char *line)
{
	increase_tabindex(-get_tabinfo()->nb_lines);
	tab_display(ed, line, get_tabinfo());
}
