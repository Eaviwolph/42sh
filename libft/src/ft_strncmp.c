/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 19:35:36 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/28 13:41:22 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	aa;
	unsigned char	bb;

	if (s1 && s2 && n)
	{
		i = -1;
		while (s1[++i] && s2[i] && i < n - 1)
		{
			aa = s1[i];
			bb = s2[i];
			if (((aa && bb) == '\0') || (n <= 0))
				return (0);
			if (aa != bb)
			{
				if ((aa - bb) > 0)
					return (1);
				if ((aa - bb) < 0)
					return (-1);
				break ;
			}
		}
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
