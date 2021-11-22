/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 18:47:57 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/11 19:46:00 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*castdst;
	char	*castsrc;

	castdst = (char *)dst;
	castsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		castdst[i] = castsrc[i];
		i++;
	}
	dst = castdst;
	return (dst);
}
