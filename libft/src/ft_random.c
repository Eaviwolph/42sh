/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 12:37:59 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/18 12:38:21 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_random(int min, int max)
{
	int				tmp;
	struct timeval	tv;
	static int		toto = 0;

	if (min > max)
	{
		tmp = min;
		min = max;
		max = tmp;
	}
	gettimeofday(&tv, NULL);
	if (!toto++)
		srand(tv.tv_usec);
	return ((rand() % ((max - min) + 1) + min));
}
