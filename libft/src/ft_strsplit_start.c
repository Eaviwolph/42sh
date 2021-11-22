/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 17:43:07 by pilespin          #+#    #+#             */
/*   Updated: 2015/03/03 18:39:21 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strsplit_start(char const *s, char c, int start)
{
	char	**tab2;
	char	**tab;
	int		i;

	if ((s == 0) || (c == 0))
		return (NULL);
	tab = ft_strsplit(s, c);
	tab2 = (char **)memalloc_or_die(sizeof(char *) * ft_tablen(tab) + 1);
	i = -1;
	while (tab[++i])
		tab2[i] = ft_strdup(tab[start++]);
	tab2[i] = NULL;
	ft_freetabchar(tab);
	return (tab2);
}
