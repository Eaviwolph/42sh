/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:04:10 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:04:14 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "token.h"
#include <libft.h>
#include "break_input/lexer.h"
#include "abstract_list.h"

t_token		*construct_token(char const *str, char delim)
{
	t_token	*token;

	token = memalloc_or_die(sizeof(t_token));
	token->type = get_token_def(TOKEN_TOKID);
	token->str = ft_strdup(str);
	lex_me(token, delim);
	return (token);
}

size_t		count_token_type(t_token const *tokens, t_token_id type)
{
	if (tokens == NULL)
		return (0);
	else if (tokens->type->id == type)
		return (count_token_type(tokens->next, type) + 1);
	else
		return (count_token_type(tokens->next, type));
}

size_t		count_token_types(t_token const *tokens
	, t_token_id const *types, size_t nbr_types)
{
	if (tokens == NULL)
		return (0);
	else if (token_is_one_of_types(tokens, types, nbr_types))
		return (count_token_types(tokens->next, types, nbr_types) + 1);
	else
		return (count_token_types(tokens->next, types, nbr_types));
}

bool		token_is_one_of_types(t_token const *token, t_token_id const *types
	, size_t nbr_types)
{
	while (nbr_types > 0)
	{
		nbr_types--;
		if (token->type->id == types[nbr_types])
			return (true);
	}
	return (false);
}

void		delete_tokens_array(t_token **tokens_array, size_t len)
{
	if (tokens_array == NULL)
		return ;
	while (len > 0)
	{
		len--;
		delete_all_tokens(tokens_array + len);
	}
	free(tokens_array);
}
