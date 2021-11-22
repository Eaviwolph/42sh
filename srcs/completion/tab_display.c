/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:23:08 by asenat            #+#    #+#             */
/*   Updated: 2017/06/27 15:44:32 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "completion.h"
#include "ansii_colors.h"
#include "put_on_tty.h"
#include <term.h>

static void		recover_curs(t_editor *ed, int line)
{
	int col;

	while (line--)
		putstr_on_tty(ed->term->move_up);
	col = (ed->cursor_position + ed->prompt_size) % ed->term->width;
	putstr_on_tty(ed->term->move_cursor_begining);
	while (col--)
		putstr_on_tty(ed->term->move_right);
}

static void		print_one(int pad, int tot, char *str, int lst_index)
{
	int			x;
	t_tabinfo	*inf;

	x = tot - pad;
	(void)lst_index;
	tputs(tgetstr("do", 0), 1, ft_rputchar);
	while (x-- > 0)
		tputs(tgetstr("nd", 0), 1, ft_rputchar);
	inf = get_tabinfo();
	if (inf->select_mode && lst_index == inf->selected_index)
		tputs(tgetstr("mr", 0), 1, ft_rputchar);
	if (!str)
		return ;
	if (*(str + ft_strlen(str) - 1) == '/')
		putstr_on_tty(BLUE);
	print_pad(pad, str);
	putstr_on_tty(RESET);
}

static int		line_needed(t_strlist *files, t_editor *ed, int line)
{
	int			pad;
	int			tot;
	int			i;
	t_strlist	*tmp;

	if ((size_t)line > list_count((t_abstract_list*)files)
			|| line >= ed->term->rows)
		return (-1);
	tmp = files;
	tot = 0;
	while (files)
	{
		pad = getpad(files, line) + 4;
		tot += pad;
		if (tot >= ed->term->width)
			return (line_needed(tmp, ed, line + 1));
		i = -1;
		while (++i < line)
			(files) ? files = files->next : 0;
	}
	return (line);
}

static int		true_display(t_strlist *files, t_editor *ed)
{
	int		pad;
	int		i;
	int		tot;
	int		lst_index;

	tot = 0;
	lst_index = 0;
	putstr_on_tty(ed->term->clear_line);
	if ((get_tabinfo()->nb_lines = line_needed(files, ed, 1)) == -1)
		return (-1);
	while (files)
	{
		pad = getpad(files, get_tabinfo()->nb_lines) + 4;
		tot += pad;
		i = -1;
		while (++i < get_tabinfo()->nb_lines)
		{
			print_one(pad, tot, (files) ? files->str : 0, lst_index);
			(files) ? files = files->next : 0;
			lst_index++;
		}
		recover_curs(ed, get_tabinfo()->nb_lines);
	}
	return (1);
}

void			tab_display(t_editor *ed, char *line, t_tabinfo *info)
{
	int save;

	if ((save = list_count((t_abstract_list*)info->list)) == 1)
	{
		tab_close(ed, line);
		ed->last_event = -1;
	}
	else if (save == 0)
		clear_tabinfo();
	else
	{
		save = ed->cursor_position;
		while (ed->cursor_position < ed->string_size)
			ev_cursor_right(ed);
		if (true_display(info->list, ed) == -1)
		{
			putstr_on_tty(ed->term->move_down);
			putstr_on_tty("Window too small");
			recover_curs(ed, 1);
		}
		save = ed->cursor_position - save;
		while (save--)
			ev_cursor_left(ed);
		ed->need_refresh = 0;
	}
}
