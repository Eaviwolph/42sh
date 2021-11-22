/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_escape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:12:00 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:13:28 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "libft.h"

static int		get_res_len(char *s, char *to_escape)
{
	int i;
	int y;

	i = 0;
	while (*s)
	{
		y = -1;
		while (to_escape[++y])
			if (to_escape[y] == *s)
				i++;
			else if (*s == '\n')
				i += 3;
		i++;
		s++;
	}
	return (i);
}

static char		is_toescape(char c, char *to_escape)
{
	while (*to_escape)
	{
		if (c == *to_escape)
			return (*to_escape);
		to_escape++;
	}
	if (c == '\n')
		return (c);
	return (0);
}

char			*str_escape(char *s, char *to_escape)
{
	char	*ret;
	int		i;
	char	c;

	if (!s || !(ret = ft_strnew(get_res_len(s, to_escape))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if ((c = is_toescape(*s, to_escape)) == '\n')
		{
			ft_strcpy(ret + i, "'\\n'");
			i += 4;
			s++;
		}
		else if (c)
		{
			ret[i++] = '\\';
			ret[i++] = *s++;
		}
		else
			ret[i++] = *s++;
	}
	return (ret);
}
