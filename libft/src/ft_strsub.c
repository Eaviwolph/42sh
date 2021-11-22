/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 13:56:39 by pilespin          #+#    #+#             */
/*   Updated: 2016/02/20 14:35:17 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;

	if (len <= 0 || (s == NULL) || start >= ft_strlen(s))
		return (NULL);
	res = memalloc_or_die((sizeof(char *)) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[i] && (size_t)i < len)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	if (ft_strlen(res) == 0)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
