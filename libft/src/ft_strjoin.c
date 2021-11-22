/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 15:16:40 by pilespin          #+#    #+#             */
/*   Updated: 2016/02/21 00:07:08 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if ((ft_strlen(s1) + ft_strlen(s2)) < 1)
		return (NULL);
	res = memalloc_or_die((sizeof(char)) *
		(ft_strlen(s1) + ft_strlen(s2) + 1));
	i = -1;
	j = 0;
	if (s1)
	{
		while (s1[++i])
			res[j++] = s1[i];
		i = -1;
	}
	if (s2)
	{
		while (s2[++i])
			res[j++] = s2[i];
	}
	res[j] = '\0';
	return (res);
}
