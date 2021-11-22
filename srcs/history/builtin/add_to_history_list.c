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

#include "history.h"

void			add_to_history_list(t_history **list, t_history *new)
{
	t_history *tmp;

	if (new)
	{
		if (*list == NULL)
			*list = new;
		else
		{
			tmp = *list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
		}
	}
}
