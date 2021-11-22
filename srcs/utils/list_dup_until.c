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
#include "utils.h"
#include <libft.h>

t_abstract_list	*list_dup_until(t_abstract_list const *list
	, t_abstract_list const *stop, size_t elem_size)
{
	t_abstract_list	*result;
	t_abstract_list	**it;

	result = NULL;
	it = &result;
	while (list != NULL && list != stop)
	{
		*it = memalloc_or_die(elem_size);
		ft_memcpy(*it, list, elem_size);
		(*it)->next = NULL;
		it = &(*it)->next;
		list = list->next;
	}
	return (result);
}
