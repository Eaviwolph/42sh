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

#include "utils.h"
#include "abstract_list.h"
#include "read_input/editor/editor.h"

static void		add_quote_at_pos(t_string **l_str, size_t pos)
{
	t_string	*new;

	new = memalloc_or_die(sizeof(t_string));
	new->c = '\'';
	new->next = NULL;
	list_push_at_pos(pos, (t_abstract_list **)l_str, (t_abstract_list *)new);
}

/*
** quotes each word delimited by space, tab or \n
*/

static void		quote_per_word_loop(t_string *l_str, t_string *beg, int pos)
{
	while (l_str)
	{
		if (is_posix_blank(l_str->c) || l_str->c == '\n')
		{
			add_quote_at_pos(&beg, pos);
			pos++;
			while (is_posix_blank(l_str->c) || l_str->c == '\n')
			{
				l_str = l_str->next;
				pos++;
			}
			add_quote_at_pos(&beg, pos);
			pos++;
		}
		l_str = l_str->next;
		pos++;
	}
}

void			quote_per_word(char **str)
{
	t_string	*l_str;
	t_string	*beg;
	int			pos;

	pos = 0;
	quote_word(str);
	l_str = str_to_list(*str);
	beg = l_str;
	quote_per_word_loop(l_str, beg, pos);
	ft_strdel(str);
	*str = get_string_from_list(beg);
	free_string(beg);
}
