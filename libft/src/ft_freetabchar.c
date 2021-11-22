/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetabchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 19:29:25 by pilespin          #+#    #+#             */
/*   Updated: 2015/09/15 23:52:28 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetabchar(char **as)
{
	int i;

	i = -1;
	if (as)
	{
		while (as[++i])
		{
			free(as[i]);
			as[i] = NULL;
		}
		free(as);
		as = NULL;
	}
}
