/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 11:49:34 by pilespin          #+#    #+#             */
/*   Updated: 2016/02/26 18:12:54 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int i;
	int j;
	int k;

	if (!s1)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	i = -1;
	while (s1[++i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] == s2[j] && s2[j])
			{
				k++;
				j++;
			}
			if (s2[j] == '\0')
				return ((char *)s1 + i);
		}
	}
	return (NULL);
}
