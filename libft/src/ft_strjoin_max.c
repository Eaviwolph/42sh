/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/09 22:48:28 by pilespin          #+#    #+#             */
/*   Updated: 2015/03/09 23:27:08 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_max(int nbr_arg, char *str, ...)
{
	va_list	ap;
	int		i;
	char	*tmp;

	if (nbr_arg < 2)
		return (NULL);
	va_start(ap, str);
	tmp = ft_strdup(str);
	i = -1;
	while (++i < nbr_arg - 1)
		tmp = ft_strjoinf(tmp, va_arg(ap, char*), 1);
	return (tmp);
}
