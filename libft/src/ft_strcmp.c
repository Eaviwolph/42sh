/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 18:04:09 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/28 13:29:22 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	a;
	unsigned char	b;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1[i] && s2[i])
	{
		a = s1[i];
		b = s2[i];
		if ((a && b) == '\0')
			return (0);
		if (a != b)
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
