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
#include "read_input/event_callbacks/event_callback_def.h"

bool		if_on_multiline(t_editor *ed)
{
	char	*str;
	int		nb;

	str = get_string_from_list(ed->string);
	nb = ft_count_char(str, '\n');
	free(str);
	if (nb > 1)
		return (true);
	return (false);
}
