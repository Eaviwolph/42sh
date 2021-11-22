/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 21:31:42 by pilespin          #+#    #+#             */
/*   Updated: 2015/10/09 16:49:58 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int sp;
	int sp_tmp;

	sp_tmp = 0;
	sp = 0;
	while (*s)
	{
		if (sp_tmp == 1 && *s == c)
			sp_tmp = 0;
		if (sp_tmp == 0 && *s != c)
		{
			sp_tmp = 1;
			sp++;
		}
		s++;
	}
	return (sp);
}

char		**ft_strsplit(char const *s, char c)
{
	int		sp;
	char	**tab;
	int		i;
	int		j;
	int		start;

	if ((s == 0) || (c == 0))
		return (NULL);
	sp = ft_count_words(s, c);
	tab = (char **)memalloc_or_die((sizeof(char *) * (sp + 1)));
	i = 0;
	j = -1;
	while (++j < sp)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_strsub(s, start, i - start);
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
