/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:09:04 by asenat            #+#    #+#             */
/*   Updated: 2017/06/28 16:01:47 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "variable.h"
#include "range.h"
#include "utils.h"
#include "break_input/quoting.h"
#include "expansion.h"

static bool	next_dollar_sign(char const *word, t_range *delimit, char *quoted)
{
	while (word[delimit->start])
	{
		handle_quotes(word[delimit->start], quoted);
		if (word[delimit->start] == '\\')
			delimit->start++;
		else if (word[delimit->start] == '$' && !(*quoted & IS_QU_SIMPLE) \
				&& word[delimit->start + 1] && \
				!is_posix_blank(word[delimit->start + 1]))
			return (true);
		delimit->start++;
	}
	return (false);
}

static void	goto_parameter_end(char *word, t_range *delimit)
{
	delimit->end++;
	while (word[delimit->end] && word[delimit->end] != '\\' \
			&& !is_posix_blank(word[delimit->end]) \
			&& !is_quote(word[delimit->end]) && word[delimit->end] != '$'
			&& word[delimit->end] != '`'
			&& word[delimit->end] != '\n')
		delimit->end++;
}

static void	replace_by_variable(char **word, char *parameter, t_uint *start)
{
	char	*replace;

	replace = get_variable(parameter + 1);
	*start = find_and_replace(word, parameter, replace, *start);
	ft_strdel(&replace);
}

static bool	is_special_parameter(char c)
{
	if (ft_strchr("?$", c))
		return (true);
	return (false);
}

/*
** $VAR replaced by variable if found, by en empty string if not
** $ can be quoted with simple quotes or a backslash
*/

char		*parameter_expansion(char const *word)
{
	t_range	limit;
	char	quoted;
	char	*result;
	char	*param;

	result = ft_strdup(word);
	quoted = 0;
	ft_bzero(&limit, sizeof(t_range));
	while (result && limit.start < ft_strlen(result))
	{
		if (next_dollar_sign(result, &limit, &quoted))
		{
			limit.end = limit.start;
			if (is_special_parameter(result[limit.start + 1]))
				limit.end = limit.start + 2;
			else
				goto_parameter_end(result, &limit);
			param = ft_strsub(result, limit.start, limit.end - limit.start);
			replace_by_variable(&result, param, &limit.start);
			ft_strdel(&param);
		}
		else
			limit.start++;
	}
	return (result);
}
