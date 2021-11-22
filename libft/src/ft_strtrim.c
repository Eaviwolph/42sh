/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 18:14:59 by pilespin          #+#    #+#             */
/*   Updated: 2016/02/19 15:29:07 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	int		end;

	len = ft_strlen(s);
	if (s == NULL || len <= 0)
		return (NULL);
	i = 0;
	while (s[i] == 9 || s[i] == 10 || s[i] == 32)
		i++;
	end = len - 1;
	while (end >= 0 && (s[end] == 9 || s[end] == 10 || s[end] == 32))
		end--;
	if (end < 0)
		end = 0;
	return (ft_strsub(s, i, end - i + 1));
}
