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

#include <libft.h>
#include <term.h>
#include <termios.h>
#include <curses.h>

#include "utils.h"
#include "abstract_list.h"
#include "shell_env.h"

#include "read_input/editor/editor.h"
#include "read_input/event_callbacks/event_callback_def.h"
#include "read_input/termcap/init_deinit.h"

#include "history/history_def.h"
#include "variable.h"

t_editor	*get_editor(void)
{
	static t_editor ed;

	return (&ed);
}

void		init_editor(void)
{
	t_editor	*new;

	new = get_editor();
	ft_bzero(new, sizeof(t_editor));
	new->term = init_term();
	new->history = get_shell_env()->history.list;
	new->prompt = gen_prompt();
	new->prompt_size = ft_strlen(new->prompt);
	list_goto_last((t_abstract_list **)&new->history);
}

void		add_to_string(t_editor *ed, char c)
{
	t_string *new;

	ed->need_refresh = true;
	new = memalloc_or_die(sizeof(t_string));
	new->c = c;
	if (!ed->string)
	{
		ed->string = new;
	}
	else
	{
		list_push_at_pos(ed->cursor_position,
				(t_abstract_list **)&ed->string, (t_abstract_list *)new);
	}
	ed->cursor_position++;
	ed->string_size++;
}

char		*get_string_from_list(t_string *s)
{
	char	*str;
	size_t	i;

	str = memalloc_or_die(list_count((t_abstract_list*)s) + 1);
	i = 0;
	while (s)
	{
		str[i] = s->c;
		i++;
		s = s->next;
	}
	str[i] = '\0';
	return (str);
}

void		free_string(t_string *s)
{
	t_string *tmp;

	while (s)
	{
		tmp = s->next;
		free(s);
		s = tmp;
	}
}
