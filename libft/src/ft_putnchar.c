/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:14:00 by pilespin          #+#    #+#             */
/*   Updated: 2015/02/18 18:19:52 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar(int x, char c)
{
	int i;

	if (x > 0)
	{
		i = -1;
		while (++i < x)
			write(1, &c, 1);
	}
}
