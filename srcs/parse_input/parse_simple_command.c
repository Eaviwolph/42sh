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
#include "abstract_list.h"
#include "utils.h"
#include <libft.h>
#include "errors.h"
#include "variable.h"

static char			**parse_argv(t_token const *tokens)
{
	char	**result;
	size_t	len;
	char	**it;

	len = list_count((t_abstract_list*)tokens);
	result = memalloc_or_die(sizeof(char*) * (len + 1));
	it = result;
	while (tokens != NULL)
	{
		*it = ft_strdup(tokens->str);
		it++;
		tokens = tokens->next;
	}
	*it = NULL;
	return (result);
}

t_simple_command	*parse_simple_command(t_token const *tokens)
{
	t_simple_command	*result;
	t_token				*remains;
	t_token				*remains2;

	set_error(NO_ERROR);
	if (tokens == NULL)
		return (NULL);
	result = memalloc_or_die(sizeof(t_simple_command));
	remains = NULL;
	result->redirections = parse_redirections(tokens, &remains);
	if (get_error() == NO_ERROR)
	{
		result->assignments = parse_assignments(remains, &remains2);
		if (get_error() == NO_ERROR)
			result->argv = parse_argv(remains2);
		delete_all_tokens(&remains2);
	}
	delete_all_tokens(&remains);
	if (get_error() != NO_ERROR)
	{
		delete_pipeline(&result);
		result = NULL;
	}
	return (result);
}
