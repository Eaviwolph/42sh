/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:06:50 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 17:07:26 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <stdlib.h>
#include "strlist.h"
#include "abstract_list.h"
#include <libft.h>
#include "errors.h"
#include "utils.h"

static t_strlist	*expand_cmd_word(t_strlist *result, char *str,
				t_strlist *it, char *tmp)
{
	tmp = parameter_expansion(str);
	ft_strdel(&str);
	str = tmp;
	if (!str)
		return (NULL);
	tmp = command_substition(str);
	ft_strdel(&str);
	if (!tmp)
		return (NULL);
	set_error(NO_ERROR);
	result = field_splitting(tmp);
	ft_strdel(&tmp);
	it = result;
	while (it != NULL)
	{
		quote_removal(&it->str);
		it = it->next;
	}
	return (result);
}

static char			*expand_assignment(char const *str)
{
	char *tmp;

	tmp = parameter_expansion(str);
	if (!tmp)
		return (NULL);
	strfreeswap(&tmp, command_substition(tmp));
	if (!tmp)
		return (NULL);
	set_error(NO_ERROR);
	quote_removal(&tmp);
	return (tmp);
}

void				expand_assignments_values(t_variable *assignments)
{
	while (assignments != NULL)
	{
		strfreeswap(&assignments->value, expand_assignment(assignments->value));
		assignments = assignments->next;
	}
}

void				expand_cmd_words(char ***words_addr)
{
	char		**words;
	t_strlist	*fields;
	t_strlist	*word_list;

	words = *words_addr;
	word_list = NULL;
	while (*words != (char*)NULL)
	{
		if (*words == NULL)
			fields = NULL;
		else
			fields = expand_cmd_word(NULL, tilde_expansion(*words), NULL, NULL);
		list_concat((t_abstract_list**)&word_list, (t_abstract_list*)fields);
		words++;
	}
	ft_freetabchar(*words_addr);
	*words_addr = strlist_to_strarray(word_list);
	strlist_delete(&word_list);
	if (*words_addr && **words_addr)
		set_error(NO_ERROR);
}
