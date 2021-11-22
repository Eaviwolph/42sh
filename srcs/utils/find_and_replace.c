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

#include <libft.h>
#include "utils.h"
#include "errors.h"

int		find_and_replace(char **str, char *to_find, char *replace, t_uint start)
{
	char	*tmp;
	char	*tmp2;
	t_uint	i;

	if ((tmp = str_in_str(to_find, *str, start, false)))
	{
		i = tmp - *str;
		if (i > 0)
		{
			tmp2 = ft_strsub(*str, 0, i);
			tmp = ft_strjoin(tmp2, replace);
			ft_strdel(&tmp2);
		}
		else
			tmp = ft_strdup(replace);
		tmp2 = ft_strsub(*str, i + ft_strlen(to_find), \
				ft_strlen(*str) - (i + ft_strlen(to_find)));
		ft_strdel(str);
		*str = ft_strjoin(tmp, tmp2);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		return (i + ft_strlen(replace));
	}
	return (-1);
}
