/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 12:29:38 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/18 12:31:39 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_utime(void)
{
	int				sec;
	double			micro;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	sec = tv.tv_sec;
	micro = tv.tv_usec;
	micro /= 1000000;
	micro += sec;
	return (micro);
}
