/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 11:52:17 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/24 17:19:30 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*casts;

	if ((n > 0) && (s))
	{
		casts = (unsigned char *)s;
		i = 0;
		while (i < n)
		{
			if (casts[i] == (unsigned char)c)
				return ((unsigned char *)casts + i);
			i++;
		}
	}
	return (NULL);
}
