/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/13 17:02:40 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/23 21:00:36 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puiss(int d)
{
	int nb;
	int i;

	nb = 1;
	i = 1;
	while (i < d)
	{
		nb = nb * 10;
		i++;
	}
	return (nb);
}

static int	ft_atoi_suite(int i, int lon, int res, char *str)
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
	if ((((int)str[i] >= 48) && ((int)str[i] <= 57)) || ((int)str[0] == 45))
	{
		while (i < lon)
		{
			res = res + (((int)str[i] - 48) * (ft_puiss(lon - i)));
			i++;
		}
	}
	if (str[0] == '-')
		res = -res;
	return (res);
}

static int	del_and_return(char **str)
{
	ft_strdel(str);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		lon;
	int		res;
	char	*strr;

	res = 0;
	strr = ft_strdup(str);
	i = 0;
	while (((strr[i] >= 9) && (strr[i] <= 13)) || (strr[i] == 32))
		strr++;
	if ((strr[0] == 45) || (strr[0] == 43))
		if ((strr[1] < 48) || (strr[1] > 57))
			return (del_and_return(&strr));
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
	free(strr);
	return (res);
}
