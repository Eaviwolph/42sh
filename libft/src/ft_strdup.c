/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:32:17 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/18 13:11:24 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*str;

	i = 0;
	if (s1)
	{
		i = ft_strlen(s1);
		str = (char *)memalloc_or_die(sizeof(char) * (i + 1));
		i = 0;
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
