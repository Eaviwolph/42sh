/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 13:49:14 by pilespin          #+#    #+#             */
/*   Updated: 2015/02/19 14:09:08 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len_max(char ***tab)
{
	int	i;
	int	j;
	int max;
	int tmp;

	max = 0;
	i = 0;
	j = 0;
	while (tab[j])
	{
		i = 0;
		while (tab[j][i])
		{
			tmp = ft_strlen(tab[j][i++]);
			if (tmp > max)
				max = tmp;
		}
		j++;
	}
	return (max);
}

void		ft_puttab3(char ***tab)
{
	int	i;
	int	j;
	int max;

	max = ft_count_len_max(tab);
	i = 0;
	j = 0;
	while (tab[j])
	{
		i = 0;
		while (tab[j][i])
		{
			ft_putstr(tab[j][i]);
			ft_putnchar((max - ft_strlen(tab[j][i++])) + 1, ' ');
		}
		ft_putchar('\n');
		j++;
	}
}
