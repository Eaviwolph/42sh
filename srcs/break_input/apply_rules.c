/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:43:42 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 16:57:20 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>
#include "utils.h"
#include <libft.h>
#include "abstract_list.h"
#include "tokenizer.h"
#include "utils.h"
#include "quoting.h"
#include "substitution.h"
#include "errors.h"

static bool		is_operator_part(t_tokenizer_state *state)
{
	char		*str;
	bool		result;
	char const	*start;

	if (state->op_start != NULL)
		start = state->op_start;
	else
		start = state->current_char;
	str = strdup_until(start, state->current_char + 1);
	if (get_matching_operator(str) != NULL)
		result = true;
	else
		result = false;
	free(str);
	return (result);
}

void			apply_rules(t_tokenizer_state *state)
{
	char c;

	c = *state->current_char;
	if (state->op_start != NULL && !is_quoted(state)
		&& is_operator_part(state))
	{
		state->current_char++;
		return ;
	}
	if (state->op_start != NULL && !is_operator_part(state))
	{
		delimit_token(state);
		return ;
	}
	if (is_quote(c) && !is_quoted(state))
	{
		apply_quoting(state);
		return ;
	}
	if (apply_rules_2(state) == false || apply_rules_3(state, c) == false)
		return ;
}

bool			apply_rules_2(t_tokenizer_state *state)
{
	if (!is_quoted(state) && is_substitution_start(state->current_char))
	{
		if (state->word_start == NULL)
			state->word_start = state->current_char;
		state->current_char =
			find_substitution_end(state->current_char + 1) + 1;
		return (false);
	}
	if (!is_quoted(state) && is_operator_part(state))
	{
		delimit_token(state);
		state->op_start = state->current_char;
		state->current_char++;
		return (false);
	}
	return (true);
}

bool			apply_rules_3(t_tokenizer_state *state, char c)
{
	if (!is_quoted(state) && is_posix_blank(c))
	{
		delimit_token(state);
		state->current_char++;
		return (false);
	}
	if (state->word_start != NULL)
	{
		state->current_char++;
		return (false);
	}
	if (c == '#')
	{
		while (*(state->current_char) != '\0'
			&& *(state->current_char) != '\n')
			state->current_char++;
		return (false);
	}
	state->word_start = state->current_char;
	state->current_char++;
	return (true);
}
