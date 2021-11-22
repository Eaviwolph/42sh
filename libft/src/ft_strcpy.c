/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:05:33 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/28 12:18:14 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	lon;

	if (dst && src)
	{
		lon = ft_strlen(src);
		i = 0;
		while (i < lon)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
