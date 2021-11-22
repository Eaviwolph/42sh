/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 20:01:31 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/27 15:44:03 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*dst2;
	const char	*src2;

	dst2 = dst;
	src2 = src;
	while (n--)
	{
		*dst2++ = *src2;
		if (*src2 == (char)c)
			return (dst2);
		src2++;
	}
	return (NULL);
}
