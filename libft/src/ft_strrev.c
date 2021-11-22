/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 21:36:55 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/15 13:18:56 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(const char *s1)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (s1 && ft_strlen(s1) > 0)
	{
		i = ft_strlen(s1);
		str = (char *)memalloc_or_die(sizeof(char) * (i + 1));
		j = i - 1;
		i = 0;
		str[j] = '\0';
		while (j >= 0)
		{
			str[i] = s1[j];
			i++;
			j--;
		}
		return (str);
	}
	return (ft_strdup(""));
}
