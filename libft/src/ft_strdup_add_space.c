/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_add_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/03 19:48:40 by pilespin          #+#    #+#             */
/*   Updated: 2015/10/26 16:40:15 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_add_space(char *s)
{
	int		i;
	int		j;
	char	*str;
	char	*str2;

	i = 0;
	if (s)
	{
		i = ft_strlen(s);
		str = (char *)memalloc_or_die(sizeof(char) * ((i * 2) + 3));
		i = -1;
		j = -1;
		while (s[++i])
		{
			str[++j] = s[i];
			str[++j] = ' ';
		}
		str[++j] = '\0';
		str2 = ft_strdup(str);
		ft_strdel(&str);
		return (str2);
	}
	return (NULL);
}
