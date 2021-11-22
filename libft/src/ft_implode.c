/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 22:41:21 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/15 12:25:19 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_implode(char **tab)
{
	int		i;
	char	*str;

	str = (char *)memalloc_or_die(sizeof(char) * (ft_tablen(tab) + 1));
	i = -1;
	if (!str)
		return (NULL);
	while (tab[++i])
	{
		str = ft_strjoinf(str, tab[i], 1);
		if (tab[i + 1])
			str = ft_strjoinf(str, " ", 1);
	}
	return (str);
}
