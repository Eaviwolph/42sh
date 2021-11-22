/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:10:04 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 17:10:44 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "variable.h"
#include <libft.h>
#include "utils.h"

static bool		has_tilde_prefix(char const *word)
{
	if (*word++ == '~' && (!*word || *word == '/'))
		return (true);
	return (false);
}

char			*tilde_expansion(char const *word)
{
	char	*home_path;
	char	*result;

	if (has_tilde_prefix(word))
	{
		if ((home_path = get_variable("HOME")))
		{
			result = ft_strjoin(home_path, word + 1);
			ft_strdel(&home_path);
			quote_word(&result);
		}
		else
			result = ft_strdup(word);
	}
	else
		result = (ft_strdup(word));
	return (result);
}
