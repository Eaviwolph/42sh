/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 15:06:26 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/15 13:19:12 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	j = 0;
	i = 0;
	if (s2[0] == 0)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		if (s1[i] == s2[j])
			j++;
		if (s2[j] == '\0')
			return ((char *)&s1[i - j + 1]);
		i++;
	}
	return (NULL);
}
