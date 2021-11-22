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

static bool				is_xbd_name_char(char c, size_t u)
{
	if (u == 0 && ft_isdigit(c))
		return (false);
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

bool					is_xbd_name(char const *str)
{
	size_t	i;
	char	c;

	i = 0;
	while ((c = str[i]) != '\0')
	{
		if (!is_xbd_name_char(c, i))
			return (false);
		i++;
	}
	return (true);
}

static char const		*find_assignment_equal(char const *str)
{
	char	c;
	size_t	u;

	u = 0;
	while ((c = str[u]) != '\0')
	{
		if (!is_xbd_name_char(c, u))
		{
			if (c == '=' && u != 0)
				return (str + u);
			else
				return (NULL);
		}
		u++;
	}
	return (NULL);
}

static t_variable		*create_assignment(t_token const *token)
{
	char const	*equal_pos;
	char		*name;
	char		*value;
	t_variable	*result;

	equal_pos = find_assignment_equal(token->str);
	if (equal_pos == NULL)
		return (NULL);
	name = strdup_until(token->str, equal_pos);
	value = ft_strdup(equal_pos + 1);
	result = create_variable(name, value, false, true);
	free(name);
	free(value);
	return (result);
}

t_variable				*parse_assignments(t_token const *tokens\
											, t_token **remains)
{
	t_variable	*result;
	t_variable	**next_addr;

	*remains = NULL;
	result = NULL;
	next_addr = &result;
	while (tokens != NULL)
	{
		*next_addr = create_assignment(tokens);
		if (*next_addr == NULL)
		{
			*remains = copy_all_tokens(tokens);
			break ;
		}
		next_addr = &(*next_addr)->next;
		tokens = tokens->next;
	}
	return (result);
}
