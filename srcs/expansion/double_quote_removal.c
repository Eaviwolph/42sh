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

#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "utils.h"
#include "break_input/quoting.h"
#include "expansion.h"

static bool	backslash_shall_retain_meaning(char next_char)
{
	if (next_char == '$'
		|| next_char == SIMPLE_QUOTE
		|| next_char == DOUBLE_QUOTE
		|| next_char == BACKSLASH
		|| next_char == '\n')
		return (true);
	else
		return (false);
}

static char	*find_double_quotes_end_and_remove_backslashes(char *str)
{
	char current_char;

	while ((current_char = str[0]) != DOUBLE_QUOTE && current_char != '\0')
	{
		if (current_char == BACKSLASH && backslash_shall_retain_meaning(str[1]))
			erase_char(str);
		str++;
	}
	if (current_char == '\0')
		fatal_error("couldn't find matching double quote during quote removal");
	return (str);
}

char		*remove_double_quotes(char *str)
{
	erase_char(str);
	str = find_double_quotes_end_and_remove_backslashes(str);
	erase_char(str);
	return (str);
}
