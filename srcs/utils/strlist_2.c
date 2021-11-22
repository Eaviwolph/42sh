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

#include "strlist.h"
#include <libft.h>
#include "abstract_list.h"

char		**strlist_to_strarray(t_strlist const *list)
{
	char		**result;
	char		**it;
	size_t		array_size;

	array_size = list_count((t_abstract_list const*)list);
	result = memalloc_or_die(sizeof(char*) * (array_size + 1));
	it = result;
	while (list != NULL)
	{
		*it = ft_strdup(list->str);
		it++;
		list = list->next;
	}
	result[array_size] = NULL;
	return (result);
}

void		strlist_delete(t_strlist **strlist_addr)
{
	t_strlist	*it;
	t_strlist	*next;

	it = *strlist_addr;
	while (it != NULL)
	{
		next = it->next;
		free(it->str);
		free(it);
		it = next;
	}
	*strlist_addr = NULL;
}

void		strlist_append(t_strlist **strlist_addr, char const *str)
{
	t_strlist	*it;
	t_strlist	*new_elem;

	new_elem = strlist_construct(str);
	if (*strlist_addr == NULL)
	{
		*strlist_addr = new_elem;
		return ;
	}
	it = *strlist_addr;
	while (it->next != NULL)
		it = it->next;
	it->next = new_elem;
}
