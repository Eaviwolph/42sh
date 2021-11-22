/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_tabchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 19:10:13 by pilespin          #+#    #+#             */
/*   Updated: 2015/03/14 20:07:17 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_make_tabchar(int size)
{
	int		i;
	char	**tab;

	tab = (char **)memalloc_or_die(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
		tab[i] = ft_strdup("");
	tab[i] = NULL;
	return (tab);
}
