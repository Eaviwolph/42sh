/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 18:58:38 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/03 15:11:57 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_retourne(char *src, int lon)
{
	char	*dest;
	int		i;
	int		j;

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

static int		ft_compte_la_longueur(int c)
{
	int		i;
	int		lon;

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

char			*ft_itoa(int c)
{
	int		lon;
	char	*str;
	char	*dst;
	int		cc;
	int		i;

	if (c == -2147483648)
		return (ft_strdup("-2147483648"));
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
	free(str);
	return (dst);
}
