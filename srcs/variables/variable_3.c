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

#include "shell_env.h"
#include "utils.h"
#include "abstract_list.h"

void		delete_all_variables(t_variable **var)
{
	t_variable	*it;
	t_variable	*tmp;

	it = *var;
	while (it)
	{
		tmp = it->next;
		free_variable(it);
		it = tmp;
	}
	*var = NULL;
}

int			pop_variable_by_name(t_variable **list, char *name)
{
	t_variable *lst;
	t_variable **addr;

	lst = *list;
	addr = list;
	while (lst)
	{
		if (!ft_strcmp(lst->name, name))
		{
			*addr = lst->next;
			free_variable(lst);
			return (STATUS_SUCCESS);
		}
		addr = &(*addr)->next;
		lst = *addr;
	}
	return (STATUS_FAILURE);
}

t_variable	*copy_variable(t_variable *e)
{
	t_variable	*tmp;
	t_variable	*new;

	tmp = NULL;
	while (e)
	{
		new = create_variable(e->name, e->value, e->exported, e->overwrite);
		list_push_back((t_abstract_list**)&tmp, (t_abstract_list*)new);
		e = e->next;
	}
	return (tmp);
}
