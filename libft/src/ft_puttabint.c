/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttabint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 14:53:55 by pilespin          #+#    #+#             */
/*   Updated: 2015/03/02 20:33:31 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_len_max(int **tab)
{
	int	i;
	int	j;
	int max;
	int tmp;

	max = 0;
	i = 0;
	j = 0;
	while (tab[i])
	{
		j = 0;
		while (j < tab[i][0])
		{
			tmp = ft_intlen(tab[i][j++]);
			if (tmp > max)
				max = tmp;
		}
		i++;
	}
	return (max);
}

void		ft_puttabint(int **tab)
{
	int max;
	int i;
	int j;

	max = ft_count_len_max(tab);
	i = 0;
	j = 0;
	while (tab[i])
	{
		ft_putnbr(tab[i][0]);
		ft_putstr("| ");
		j = 0;
		while (j < tab[i][0])
		{
			if (j > 0)
				ft_putnchar((max - ft_intlen(tab[i][j])) + 1, ' ');
			ft_putnbr(tab[i][j + 1]);
			j++;
		}
		i++;
		ft_putstr("\n");
	}
}
