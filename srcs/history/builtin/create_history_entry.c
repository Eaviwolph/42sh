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

t_history		*create_history_entry(char *line)
{
	t_history *new;

	if (line && ft_strcmp(line, "\n"))
	{
		new = (t_history *)memalloc_or_die(sizeof(t_history));
		new->line = ft_strdup(line);
		new->appended = false;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	return (NULL);
}
