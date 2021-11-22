/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/03 14:18:29 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/16 15:18:35 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoaf(double nbr)
{
	char	*dst;
	char	*first;
	char	*second;
	long	precision;

	precision = 1000000000;
	first = ft_itoa(nbr);
	dst = NULL;
	nbr = (nbr - ft_atoi(first));
	if (nbr < 0)
		nbr = -nbr;
	nbr = nbr * precision;
	nbr = nbr + 000000000000.1;
	second = ft_itoa((int)nbr);
	if (first && second)
	{
		dst = ft_strjoinf(first, ".", 1);
		dst = ft_strjoinf(dst, second, 3);
	}
	return (dst);
}
