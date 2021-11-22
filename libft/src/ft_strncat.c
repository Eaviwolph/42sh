/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 17:29:58 by pilespin          #+#    #+#             */
/*   Updated: 2014/11/07 17:34:56 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t j;

	i = ft_strlen(s1);
	j = 0;
	while (s2[j] && j < n)
		s1[i++] = s2[j++];
	s1[i] = '\0';
	return (s1);
}
