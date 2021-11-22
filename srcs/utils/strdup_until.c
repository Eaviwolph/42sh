/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42shTeam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:35:21 by 42shTeam          #+#    #+#             */
/*   Updated: 2017/05/03 15:35:21 by 42shTeam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>
#include <libft.h>

char			*strdup_until(char const *src, char const *stop)
{
	char	*result;
	size_t	len;

	if (stop == NULL)
		len = ft_strlen(src);
	else
		len = stop - src;
	result = memalloc_or_die(sizeof(char) * (len + 1));
	ft_strncpy(result, src, len);
	result[len] = '\0';
	return (result);
}
