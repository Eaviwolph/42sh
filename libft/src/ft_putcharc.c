/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 12:48:04 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/18 12:48:33 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcharc(int color, int background, char str)
{
	if (color >= 0 && color <= 7)
	{
		ft_putstr("\033[");
		ft_putnbr(color + 30);
		if (background >= 0 && background <= 7)
		{
			ft_putstr(";");
			ft_putnbr(background + 40);
		}
		ft_putstr("m");
		ft_putchar(str);
		ft_putstr("\033[0m");
	}
}
