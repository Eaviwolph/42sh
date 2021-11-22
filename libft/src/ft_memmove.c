/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/11 21:06:35 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/28 11:42:06 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst && src)
	{
		if (src <= dst)
			while (len--)
				((unsigned char*)dst)[len] = ((unsigned char*)src)[len];
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
