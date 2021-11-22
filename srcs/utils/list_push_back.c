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

#include "abstract_list.h"

void	list_push_back(t_abstract_list **list, t_abstract_list *new)
{
	t_abstract_list *tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	list_push_at_pos(size_t pos, t_abstract_list **list,
		t_abstract_list *new)
{
	t_abstract_list	*lst;
	size_t			i;

	if (*list == NULL)
		*list = new;
	else
	{
		lst = *list;
		if (pos == 0)
		{
			new->next = *list;
			*list = new;
		}
		else if (pos > 0)
		{
			i = 0;
			while (lst->next && i < pos - 1)
			{
				i++;
				lst = lst->next;
			}
			new->next = lst->next;
			lst->next = new;
		}
	}
}

void	**list_pop_at_pos(size_t pos, t_abstract_list **list)
{
	t_abstract_list	*lst;
	t_abstract_list	**addr;
	size_t			i;

	lst = *list;
	addr = list;
	i = 0;
	while (lst)
	{
		if (i == pos)
		{
			*addr = lst->next;
			return ((void**)lst);
		}
		addr = &(*addr)->next;
		lst = *addr;
		i++;
	}
	return (NULL);
}
