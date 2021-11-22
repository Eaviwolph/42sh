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
#include "shell_env.h"
#include "abstract_list.h"

static size_t	get_number_of_exported(void)
{
	t_variable	*e;
	size_t		size;

	e = get_shell_env()->variables;
	size = 0;
	while (e)
	{
		if (e->exported == true)
			size++;
		e = e->next;
	}
	return (size);
}

static bool		is_in_assignment(t_variable *assignments, char *name)
{
	if (!assignments || ft_strlen(name) <= 0)
		return (false);
	while (assignments)
	{
		if (!ft_strcmp(assignments->name, name))
		{
			return (true);
		}
		assignments = assignments->next;
	}
	return (false);
}

static size_t	number_in_assignment(t_variable *e, t_variable *assignments)
{
	size_t	nb;

	if (!e || !assignments)
		return (0);
	nb = 0;
	while (e)
	{
		if (is_in_assignment(assignments, e->name))
			nb++;
		e = e->next;
	}
	return (nb);
}

static char		**create_envp(t_variable *e, size_t size)
{
	size_t		i;
	char		**envp;

	if (!e)
		return (NULL);
	envp = memalloc_or_die(sizeof(char *) * (size + 1));
	i = 0;
	while (e)
	{
		if (e->exported == true)
		{
			envp[i] = ft_strjoinf(e->name, ft_strjoin("=", e->value), 2);
			i++;
			envp[i] = NULL;
		}
		e = e->next;
	}
	return (envp);
}

char			**get_variables_for_execution(t_variable *assignments)
{
	size_t		size;
	size_t		reassigned;
	char		**envp;
	t_variable	*e;

	e = copy_variable(get_shell_env()->variables);
	size = get_number_of_exported();
	reassigned = number_in_assignment(e, assignments);
	if (assignments)
		size += list_count((t_abstract_list *)assignments) - reassigned;
	if (!size)
	{
		delete_all_variables(&e);
		return (NULL);
	}
	while (assignments)
	{
		setenv_as(&e, assignments->name, assignments->value, true);
		assignments = assignments->next;
	}
	envp = create_envp(e, size);
	delete_all_variables(&e);
	return (envp);
}
