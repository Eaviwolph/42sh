/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/17 15:36:03 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/13 23:03:15 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **s1)
{
	int		i;
	char	**tab;

	if (s1)
	{
		i = ft_tablen((char **)s1);
		tab = (char **)memalloc_or_die(sizeof(char *) * (i + 1));
		i = -1;
		while (s1[++i])
			tab[i] = ft_strdup(s1[i]);
		tab[i] = NULL;
		return (tab);
	}
	return (NULL);
}
