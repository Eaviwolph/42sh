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
#include <libft.h>
#include "put_on_tty.h"

static void	highlighted_core(char *line, size_t cur, size_t start, size_t len)
{
	char *begin;
	char *middle;
	char *end;

	begin = NULL;
	middle = NULL;
	end = NULL;
	if (start && cur >= start)
	{
		begin = ft_strsub(line, 0, start);
		middle = ft_strsub(line, start, cur - start);
		end = ft_strsub(line, cur, len - cur);
	}
	else if (start && cur < start)
	{
		begin = ft_strsub(line, 0, cur);
		middle = ft_strsub(line, cur, start - cur);
		end = ft_strsub(line, start, len - start);
	}
	putstr_on_tty(begin);
	ft_putstrc(4, 3, middle, get_shell_env()->tty_fd);
	putstr_on_tty(end);
	free(begin);
	free(middle);
	free(end);
}

void		put_highlighted_line(t_editor *ed, char *line)
{
	size_t	cur;
	size_t	start;
	size_t	offset;
	size_t	len;

	len = ft_strlen(line);
	if (!line || len <= 0)
		return ;
	offset = ft_strlen(ed->prompt);
	start = ed->selected_string_start + offset;
	cur = ed->cursor_position + offset;
	if (ed->in_selection)
	{
		highlighted_core(line, cur, start, len);
	}
	else
	{
		putstr_on_tty(line);
	}
}
