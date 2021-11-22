/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/01 12:43:27 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/01 15:13:04 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	double	retv;
	int		tmp;
	char	*virg;
	char	*virg2;

	tmp = ft_atoi(str);
	virg = ft_strchr(str, '.');
	retv = 0;
	if (virg && ft_strlen(virg) >= 2)
	{
		virg2 = ft_strdup(virg + 1);
		retv = ft_atoi(virg2);
		retv /= ft_pow(10, ft_strlen(virg2));
		ft_strdel(&virg2);
	}
	if (tmp < 0)
		return (tmp - retv);
	else
		return (tmp + retv);
}
