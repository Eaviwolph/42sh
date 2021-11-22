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

static void			parse_pipeline_sub(size_t splited_len, t_token **splited,
		t_simple_command *result, t_simple_command **it)
{
	size_t				u;
	t_token				*trimed;

	u = 0;
	while (u < splited_len)
	{
		trimed = trim_newlines(splited[u]);
		if (trimed == NULL)
		{
			set_error(UNEXPECTED_PIPE);
			if (u == splited_len - 1)
				get_shell_env()->last_unmatched = UNEXPECTED_PIPE;
			delete_pipeline(&result);
			break ;
		}
		(*it) = parse_simple_command(trimed);
		delete_all_tokens(&trimed);
		if (get_error() != NO_ERROR)
		{
			delete_pipeline(&result);
			break ;
		}
		it = &(*it)->next;
		u++;
	}
}

t_simple_command	*parse_pipeline(t_token const *tokens)
{
	t_simple_command	*result;
	t_token				**splited;
	size_t				splited_len;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	splited = split_tokens_at(tokens, OR_TOKID, &splited_len);
	result = NULL;
	parse_pipeline_sub(splited_len, splited, result, &result);
	delete_tokens_array(splited, splited_len);
	return (result);
}
