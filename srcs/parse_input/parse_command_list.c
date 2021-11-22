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

static bool		last_is_semi(t_token const *tokens)
{
	t_token const *last;

	if (tokens == NULL)
		return (false);
	last = (t_token const *)list_get_last_const(
		(t_abstract_list const *)tokens);
	if (last->type->id == SEMI_TOKID)
		return (true);
	else
		return (false);
}

static void		parse_cmd_list_sub(size_t splited_len, t_token **splited,
	t_command_list *result, t_command_list **it)
{
	size_t			u;

	u = 0;
	while (u < splited_len)
	{
		if (splited[u] == NULL)
		{
			set_error(UNEXPECTED_SEMI);
			delete_command_list(&result);
			break ;
		}
		(*it) = memalloc_or_die(sizeof(t_command_list));
		(*it)->and_or_list = parse_and_or_list(splited[u]);
		if (get_error() != NO_ERROR)
		{
			delete_command_list(&result);
			break ;
		}
		it = &(*it)->next;
		u++;
	}
}

t_command_list	*parse_command_list(t_token const *tokens)
{
	t_command_list	*result;
	t_token			**splited;
	size_t			splited_len;
	t_token			*trimed;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	trimed = trim_newlines(tokens);
	splited = split_tokens_at(trimed, SEMI_TOKID, &splited_len);
	result = NULL;
	if (splited_len > 1 || splited[0] != NULL)
	{
		if (last_is_semi(trimed))
			splited_len--;
		parse_cmd_list_sub(splited_len, splited, result, &result);
		if (get_shell_env()->last_unmatched == UNEXPECTED_IF && splited_len > 0)
			get_shell_env()->last_unmatched = NO_ERROR;
	}
	delete_all_tokens(&trimed);
	delete_tokens_array(splited, splited_len);
	return (result);
}
