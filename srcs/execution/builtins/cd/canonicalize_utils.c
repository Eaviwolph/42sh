/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalize_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 17:49:21 by asenat            #+#    #+#             */
/*   Updated: 2017/06/24 17:11:27 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/builtins/cd.h"

t_strlist	*break_components(char const *path)
{
	char const	*start;
	t_strlist	*cmpnts;
	char		*tmp;

	start = path;
	cmpnts = NULL;
	while (start != NULL)
	{
		while (*path != '\0' && *path != '/')
			path++;
		while (*path != '\0' && *path == '/')
			path++;
		tmp = strdup_until(start, path);
		strlist_append(&cmpnts, tmp);
		free(tmp);
		if (*path == '\0')
			start = NULL;
		else
			start = path;
	}
	return (cmpnts);
}

bool		comp_is_dot(char const *comp)
{
	if (ft_strnequ(comp, "./", 2) || ft_strequ(comp, "."))
		return (true);
	else
		return (false);
}

bool		comp_is_dot_dot(char const *comp)
{
	if (ft_strnequ(comp, "../", 3) || ft_strequ(comp, ".."))
		return (true);
	else
		return (false);
}

void		remove_dots(t_strlist **cmpnts_addr)
{
	t_strlist	*component;

	component = *cmpnts_addr;
	while (component != NULL)
	{
		if (comp_is_dot(component->str))
		{
			*cmpnts_addr = component->next;
			component->next = NULL;
			strlist_delete(&component);
		}
		else
			cmpnts_addr = &component->next;
		component = *cmpnts_addr;
	}
}

bool		comp_is_directory(t_strlist *start, t_strlist *end)
{
	char	*str;
	bool	result;

	str = strlist_to_str_until(start, end->next);
	if (is_directory(str))
		result = true;
	else
		result = false;
	free(str);
	return (result);
}
