/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:07:33 by asenat            #+#    #+#             */
/*   Updated: 2017/06/29 13:15:44 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "strlist.h"
#include <stdlib.h>
#include <libft.h>
#include "range.h"
#include "utils.h"
#include "abstract_list.h"
#include "break_input/quoting.h"

static void		end_of_quote(char const *word, t_range *delimit)
{
	char	quote;

	quote = word[delimit->end];
	delimit->end++;
	if (quote == '\\')
		return ;
	if (word && delimit->end > 0 && ft_strlen(word) >= (size_t)(delimit->end))
	{
		while (word[delimit->end] && (word[delimit->end] != quote \
			|| (word[delimit->end - 1] && word[delimit->end - 1] == '\\')))
			delimit->end++;
	}
}

static void		skip_posix_blanks(char const *word, int *i)
{
	while (word[*i] && (is_posix_blank(word[*i]) || word[*i] == '\n'))
		(*i)++;
}

static void		add_field(char const *word, t_strlist **result,
					t_range *delimit)
{
	char		*tmp;

	tmp = ft_strsub(word, delimit->start, delimit->end - delimit->start);
	strlist_append(result, tmp);
	skip_posix_blanks(word, &delimit->end);
	delimit->start = delimit->end;
	ft_strdel(&tmp);
}

/*
**	scan the results of expansions and substitutions
** 	that did not occur in double-quotes and split into fields
*/

t_strlist		*field_splitting(char const *word)
{
	t_strlist	*result;
	t_range		delimit;

	result = NULL;
	ft_bzero(&delimit, sizeof(t_range));
	while (word[delimit.start])
	{
		while (word[delimit.end] && !is_posix_blank(word[delimit.end]) \
			&& word[delimit.end] != '\n')
		{
			if (is_quote(word[delimit.end]))
				end_of_quote(word, &delimit);
			if (word[delimit.end])
				delimit.end++;
		}
		add_field(word, &result, &delimit);
	}
	return (result);
}
