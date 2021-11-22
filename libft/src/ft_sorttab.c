/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorttab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:20:29 by pilespin          #+#    #+#             */
/*   Updated: 2015/02/18 18:23:03 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sorttab(char **tab)
{
	int j;
	int i;
	int var;

	j = 1;
	i = 0;
	var = 42;
	if (tab[i] == NULL)
		return ;
	while (var == 42)
	{
		var = 0;
		j = 1;
		i = 0;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				ft_swap_char(tab, i, j);
				var = 42;
			}
			j++;
			i++;
		}
	}
}
