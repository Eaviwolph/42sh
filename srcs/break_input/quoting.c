/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:02:59 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:03:08 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quoting.h"
#include <libft.h>
#include "errors.h"
#include "shell_env.h"

static char const	*find_simple_quote_end(t_tokenizer_state *state)
{
	char const *it;

	set_error(NO_ERROR);
	it = state->current_char + 1;
	while (*it != '\0')
	{
		if (*it == '\'')
			return (it);
		it++;
	}
	set_error(UNMATCHED_SINGLE_QUOTE);
	get_shell_env()->last_unmatched = UNMATCHED_SINGLE_QUOTE;
	return (NULL);
}

void				apply_quoting(t_tokenizer_state *state)
{
	if (*state->current_char == '\\')
		state->last_backslash = state->current_char;
	else if (*state->current_char == '\'')
		state->simple_quote_end = find_simple_quote_end(state);
	else if (*state->current_char == '"')
		state->double_quote_end = find_double_quote_end(state);
}

bool				is_quoted(t_tokenizer_state *state)
{
	if (state->last_backslash != NULL
		&& (state->current_char == state->last_backslash
				|| state->current_char - 1 == state->last_backslash))
		return (true);
	if (state->simple_quote_end >= state->current_char)
		return (true);
	if (is_double_quoted(state))
		return (true);
	return (false);
}

bool				is_quote(char c)
{
	if (c == '\'' || c == '"' || c == '\\')
		return (true);
	return (false);
}
