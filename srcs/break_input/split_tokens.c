/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:03:12 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:03:22 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "utils.h"
#include "abstract_list.h"
#include <libft.h>

t_token			**split_tokens_at(t_token const *tokens, t_token_id delim
	, size_t *len_addr)
{
	t_token			**result;
	t_token const	*slice_start;
	size_t			u;

	*len_addr = count_token_type(tokens, delim) + 1;
	result = memalloc_or_die(sizeof(t_token*) * (*len_addr));
	slice_start = tokens;
	u = 0;
	while (tokens != NULL)
	{
		if (tokens->type->id == delim)
		{
			result[u] = tokens_dup_until(slice_start, tokens);
			slice_start = tokens->next;
			u++;
		}
		tokens = tokens->next;
	}
	result[u] = tokens_dup_until(slice_start, tokens);
	return (result);
}

t_token			**split_tokens_mult(t_token const *tokens
	, t_token_id *delims, size_t nbr_delims, size_t *len_addr)
{
	t_token			**result;
	t_token const	*slice_start;
	size_t			u;

	*len_addr = count_token_types(tokens, delims, nbr_delims) + 1;
	result = memalloc_or_die(sizeof(t_token*) * (*len_addr));
	slice_start = tokens;
	u = 0;
	while (tokens != NULL)
	{
		if (token_is_one_of_types(tokens, delims, nbr_delims))
		{
			result[u] = tokens_dup_until(slice_start, tokens->next);
			slice_start = tokens->next;
			u++;
		}
		tokens = tokens->next;
	}
	result[u] = tokens_dup_until(slice_start, tokens);
	return (result);
}
