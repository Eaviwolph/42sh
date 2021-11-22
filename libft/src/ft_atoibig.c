/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 19:50:39 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/16 19:52:26 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	ft_puiss(long long d)
{
	long long nb;
	long long i;

	nb = 1;
	i = 1;
	while (i < d)
	{
		nb = nb * 10;
		i++;
	}
	return (nb);
}

static long long	ft_atoi_suite(long long i, long long lon, long long res,
									char *str)
{
	while (str[i])
	{
		if (str[lon] >= 48 && str[lon] <= 57)
			lon++;
		else
			str[i] = '\0';
		i++;
	}
	if (str[0] == '-')
		i = 1;
	else
		i = 0;
	res = 0;
	if ((((long long)str[i] >= 48) && ((long long)str[i] <= 57)) ||
			((long long)str[0] == 45))
	{
		while (i < lon)
		{
			res = res + (((long long)str[i] - 48) * ft_puiss(lon - i));
			i++;
		}
	}
	if (str[0] == '-')
		res = -res;
	return (res);
}

long long			ft_atoibig(const char *str)
{
	long long		i;
	long long		lon;
	long long		res;
	char			*strr;

	res = 0;
	strr = ft_strdup(str);
	i = 0;
	while (((strr[i] >= 9) && (strr[i] <= 13)) || (strr[i] == 32))
		strr++;
	if ((strr[0] == 45) || (strr[0] == 43))
		if ((strr[1] < 48) || (strr[1] > 57))
			return (0);
	if (strr[0] == 43)
		strr++;
	lon = 0;
	i = 0;
	if (strr[0] == 45)
	{
		i++;
		lon++;
	}
	res = ft_atoi_suite(i, lon, res, strr);
	return (res);
}
