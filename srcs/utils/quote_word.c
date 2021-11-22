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

#include "utils.h"
#include "abstract_list.h"
#include "read_input/editor/editor.h"

static void		add_quoted_backslash(char **word, size_t first)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strsub(*word, 0, first);
	tmp2 = ft_strjoin(tmp, "'\\'");
	ft_strdel(&tmp);
	tmp3 = ft_strdup(&(*word)[first]);
	tmp = ft_strjoin(tmp2, tmp3);
	ft_strdel(word);
	ft_strdel(&tmp2);
	ft_strdel(&tmp3);
	*word = ft_strdup(tmp);
	ft_strdel(&tmp);
}

/*
**	adds simple-quoted backslashes to quote simple quotes
*/

static void		quote_quotes(char **word)
{
	char	*tmp;
	int		i;

	i = -3;
	while (i < (int)ft_strlen(*word))
	{
		if (!(tmp = ft_strchr(*word + i + 3, '\'')))
			break ;
		i = tmp - *word + 1;
		add_quoted_backslash(word, tmp - *word);
	}
}

/*
**	simple-quotes word
*/

void			quote_word(char **word)
{
	char	*tmp;

	quote_quotes(word);
	tmp = ft_strjoin("\'", *word);
	ft_strdel(word);
	*word = ft_strjoin(tmp, "\'");
	ft_strdel(&tmp);
}
