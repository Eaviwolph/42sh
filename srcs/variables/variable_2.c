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

bool		variable_is_overwritable(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			if (v->overwrite)
				return (true);
			return (false);
		}
		v = v->next;
	}
	return (false);
}

bool		set_variable_for_export(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			v->exported = true;
			return (true);
		}
		v = v->next;
	}
	return (false);
}

void		free_variable(t_variable *list)
{
	if (list)
	{
		free(list->name);
		free(list->value);
		free(list);
	}
}

void		delete_variable(t_variable **var)
{
	free_variable(*var);
	*var = NULL;
}
