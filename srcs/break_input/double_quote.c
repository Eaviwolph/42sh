/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:53:41 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 14:53:56 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quoting.h"
#include "substitution.h"
#include <libft.h>
#include "errors.h"
#include "shell_env.h"

char const	*find_double_quote_end(t_tokenizer_state *state)
{
	char const	*it;
	char		nc;

	it = state->current_char + 1;
	while (*it != '\0')
	{
		nc = *(it + 1);
		if (*it == '`')
			it = find_substitution_end(it + 1);
		if (get_error())
			break ;
		if (*it == '\\' && (nc == '`' || nc == '"' || nc == '\\' || nc == '\n'))
			it++;
		else if (*it == '"')
			return (it);
		it++;
	}
	if (get_error() != UNMATCHED_BACKQUOTE)
		set_error(UNMATCHED_DOUBLE_QUOTE);
	get_shell_env()->last_unmatched = get_error();
	return (NULL);
}

bool		is_double_quoted(t_tokenizer_state *state)
{
	char c;
	char nc;

	if (state->double_quote_end >= state->current_char)
	{
		c = *state->current_char;
		if (c == '`')
			return (false);
		else if (c == '\\')
		{
			nc = *(state->current_char + 1);
			if (nc == '`' || nc == '"' || nc == '\\' || nc == '\n')
				return (false);
		}
		return (true);
	}
	else
		return (false);
}
