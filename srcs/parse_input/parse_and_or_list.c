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

#include "parse_syntax_tree.h"
#include "syntax_tree.h"
#include "utils.h"
#include "abstract_list.h"
#include <libft.h>
#include "errors.h"
#include "shell_env.h"

static t_token		**do_the_split(t_token const *tokens, size_t *len_addr)
{
	t_token_id		ids[2];

	ids[0] = AND_IF_TOKID;
	ids[1] = OR_IF_TOKID;
	return (split_tokens_mult(tokens, ids, 2, len_addr));
}

static t_ao_type	cut_ao_type(t_token **it)
{
	if ((*it) == NULL)
		return (AO_END);
	while ((*it) && (*it)->next)
		it = &(*it)->next;
	if ((*it)->type->id == AND_IF_TOKID)
	{
		delete_token(it);
		return (AO_AND);
	}
	else if ((*it)->type->id == OR_IF_TOKID)
	{
		delete_token(it);
		return (AO_OR);
	}
	else
		return (AO_END);
}

void				set_unexpected_if(t_and_or_list **result, \
								size_t splitted_len, size_t u)
{
	set_error(UNEXPECTED_IF);
	if (u == splitted_len - 1)
		get_shell_env()->last_unmatched = UNEXPECTED_IF;
	delete_and_or_list(result);
}

t_and_or_list		*parse_and_or_list_run(t_and_or_list *result, size_t u,\
				t_token **splited, size_t splited_len)
{
	t_and_or_list	**it;
	t_token			*trimed;

	it = &result;
	while (u < splited_len)
	{
		(*it) = memalloc_or_die(sizeof(t_and_or_list));
		(*it)->separation_type = cut_ao_type(splited + u);
		if ((trimed = trim_newlines(splited[u])) == NULL)
		{
			set_unexpected_if(&result, splited_len, u);
			break ;
		}
		(*it)->pipeline = parse_pipeline(trimed);
		delete_all_tokens(&trimed);
		if (get_error() != NO_ERROR)
		{
			delete_and_or_list(&result);
			break ;
		}
		it = &(*it)->next;
		u++;
	}
	delete_tokens_array(splited, splited_len);
	return (result);
}

t_and_or_list		*parse_and_or_list(t_token const *tokens)
{
	t_token			**splited;
	size_t			splited_len;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	splited = do_the_split(tokens, &splited_len);
	return (parse_and_or_list_run(NULL, 0, splited, splited_len));
}
