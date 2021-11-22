/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 17:50:38 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/10 17:50:46 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t i;
	size_t ok;

	ok = 0;
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			ok = i + 1;
		i++;
	}
	if (ok > 0)
		return ((char *)s + (ok - 1));
	return (NULL);
}
