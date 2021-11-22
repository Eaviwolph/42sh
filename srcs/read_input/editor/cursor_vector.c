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
#include "editor.h"

static long	return_value(t_editor *ed, char *str, int i)
{
	long	ret;

	ret = i - ed->prompt_size;
	if (ret > (long)(ft_strlen(str) - ed->prompt_size))
		ret = (long)(ft_strlen(str) - ed->prompt_size);
	if (ret <= 0)
		ret = 0;
	free(str);
	return (ret);
}

size_t		find_index_at_vector(t_editor *ed, int ox, int oy)
{
	char	*str;
	size_t	i;
	t_vec2i	vec;

	str = ft_strjoinf(ed->prompt, get_string_from_list(ed->string), 2);
	vec.x = 0;
	vec.y = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (vec.y > oy || (vec.y == oy && vec.x >= ox))
			break ;
		if (vec.x >= ed->term->width - 1 || str[i] == '\n')
		{
			vec.y++;
			if (vec.x >= ed->term->width - 1 && str[i] == '\n')
				vec.y++;
			vec.x = 0;
		}
		else
			vec.x++;
		i++;
	}
	return (return_value(ed, str, i));
}

t_vec2i		get_cursor_vector(t_editor *ed)
{
	char			*str;
	size_t			i;
	t_vec2i			vec;

	str = ft_strjoinf(ed->prompt, get_string_from_list(ed->string), 2);
	vec.x = 0;
	vec.y = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (i >= ed->cursor_position + ed->prompt_size)
			break ;
		if (vec.x >= ed->term->width - 1 || str[i] == '\n')
		{
			vec.y++;
			if (vec.x >= ed->term->width - 1 && str[i] == '\n')
				vec.y++;
			vec.x = 0;
		}
		else
			vec.x++;
		i++;
	}
	free(str);
	return (vec);
}
