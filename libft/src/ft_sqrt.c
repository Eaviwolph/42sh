/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 22:37:25 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/01 23:05:35 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_sqrt(double nbr)
{
	double preci;
	double inf;
	double sup;
	double tmp;

	preci = 0.00000001;
	inf = 0;
	sup = nbr;
	tmp = nbr / 2;
	while ((tmp * tmp >= nbr + preci) || (tmp * tmp <= nbr - preci))
	{
		if (tmp * tmp >= nbr)
			sup = tmp;
		else
			inf = tmp;
		tmp = (inf + sup) / 2;
	}
	return (tmp);
}
