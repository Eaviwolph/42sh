/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/18 12:43:16 by pilespin          #+#    #+#             */
/*   Updated: 2017/06/23 14:44:19 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrc(int color, int background, char *str, int fd)
{
	if (color >= 0 && color <= 7)
	{
		ft_putstr_fd("\033[", fd);
		ft_putnbr_fd(color + 30, fd);
		if (background >= 0 && background <= 7)
		{
			ft_putstr_fd(";", fd);
			ft_putnbr_fd(background + 40, fd);
		}
		ft_putstr_fd("m", fd);
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\033[0m", fd);
	}
}

/*
**	0 : noir ;
**	1 : rouge ;
**	2 : vert ;
**	3 : jaune ;
**	4 : bleu ;
**	5 : rose ;
**	6 : cyan ;
** 	7 : gris.
*/
