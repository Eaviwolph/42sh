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

t_variable	*create_variable(char const *name, char const *value,
	bool exported, bool overwrite)
{
	t_variable *v;

	v = memalloc_or_die(sizeof(t_variable));
	v->name = ft_strdup(name);
	v->value = ft_strdup(value);
	v->exported = exported;
	v->overwrite = overwrite;
	v->is_variable = true;
	v->is_function = false;
	v->next = NULL;
	return (v);
}

bool		is_a_variable(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			if (v->is_variable)
				return (true);
			return (false);
		}
		v = v->next;
	}
	return (false);
}

bool		is_a_function(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			if (v->is_function)
				return (true);
			return (false);
		}
		v = v->next;
	}
	return (false);
}

void		print_variable(t_variable *v)
{
	while (v)
	{
		ft_printf("Name: \"%s\"	", v->name);
		ft_printf("Value: \"%s\"	", v->value);
		if (v->is_variable)
			ft_printf("VARIABLE	");
		if (v->is_function)
			ft_printf("FUNCTION	");
		if (v->exported)
			ft_printf("FOR EXPORT	");
		if (v->overwrite)
			ft_printf("OVERWRITE	");
		ft_printf("\n");
		v = v->next;
	}
}

bool		variable_exist(t_variable *v, char *name)
{
	while (v)
	{
		if (!ft_strcmp(v->name, name))
		{
			return (true);
		}
		v = v->next;
	}
	return (false);
}
