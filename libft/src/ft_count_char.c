/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_absint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 16:39:48 by pilespin          #+#    #+#             */
/*   Updated: 2015/05/31 17:47:01 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char(char *str, char car)
{
	int i;
	int nbr;

	if (str)
	{
		nbr = 0;
		i = -1;
		while (str[++i])
		{
			if (str[i] == car)
				nbr++;
		}
		return (nbr);
	}
	return (0);
}
