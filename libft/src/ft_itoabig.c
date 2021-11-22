/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/16 19:10:48 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/18 13:35:55 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_retourne(char *src, long long lon)
{
	char		*dest;
	long long	i;
	long long	j;

	dest = (char *)memalloc_or_die(lon + 1);
	j = lon;
	i = 0;
	dest[lon] = '\0';
	while (i < lon)
	{
		dest[i] = src[j - 1];
		i++;
		j--;
	}
	return (dest);
}

static long long	ft_compte_la_longueur(long long c)
{
	long long		i;
	long long		lon;

	i = 1;
	if (c < 0)
	{
		i++;
		c = -c;
	}
	lon = c;
	while (lon >= 10)
	{
		lon = lon / 10;
		i++;
	}
	return (i);
}

char				*ft_itoabig(long long c)
{
	long long	lon;
	char		*str;
	char		*dst;
	long long	cc;
	long long	i;

	if (c < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	cc = c;
	lon = ft_compte_la_longueur(c);
	str = (char *)memalloc_or_die(lon + 1);
	if (c < 0)
		c = -c;
	i = 0;
	while (i < lon)
	{
		str[i] = (c % 10) + 48;
		c = c / 10;
		i++;
	}
	if (cc < 0)
		str[i - 1] = '-';
	dst = ft_retourne(str, lon);
	return (dst);
}
